#include "AuctionGameServer.h"

AuctionGameServer::AuctionGameServer()
{

}

AuctionGameServer::~AuctionGameServer()
{
	IServer::Terminate();
}

bool AuctionGameServer::Initialize()
{
	srand(0);

	wprintf(L"# Auction Game Server Start\n");

	//todo
	/*
		Player pool 초기화
		job pool 초기화
		room pool 초기화

		player, room manager
	*/

	_jobQueue = new queue<Job*>();

	InitializeSRWLock(&_jobQueueLock);
	InitializeConditionVariable(&_jobQueueCV);

	_updateThread = (HANDLE)_beginthreadex(NULL, 0, UpdateThread, this, 0, nullptr);
	if (_updateThread == NULL)
	{
		wprintf(L"# Begin Update Thread Failed\n");
		return false;
	}

	//_monitorThread = (HANDLE)_beginthreadex(NULL, 0, MonitorThread, this, 0, NULL);
	//if (_monitorThread == NULL)
	//{
	//	wprintf(L"# Begin Monitor Thread Failed\n");
	//	return false;
	//}


	if (IServer::Initialize(SERVER_ADDRESS, SERVER_PORT, TOTAL_THREAD, RUNNING_THREAD, true, true, SESSION_MAX) == false)
	{
		return false;
	}

	wprintf(L"# Auction Game Server is Initialized");
}

void AuctionGameServer::OnInitialize(void)
{

}

bool AuctionGameServer::OnConnectionRequest(const wchar_t* ip, const short port)
{
	// Filter banned user
	return true;
}

void AuctionGameServer::OnAccept(const SessionID sessionId)
{
	// Accept Job Enqueue
}

void AuctionGameServer::OnRelease(const SessionID sessionId)
{
	// Release Job Enqueue
}

void AuctionGameServer::OnRecv(const SessionID sessionId, SPacket* packet)
{
	// Contents Job Enqueue
}

void AuctionGameServer::OnError(const int errorCode, const wchar_t* errorMsg)
{
	wprintf(L" # Auction Game Server OnError : %s", errorMsg);
}

unsigned int WINAPI AuctionGameServer::UpdateThread(void* arg)
{
	AuctionGameServer* instance = (AuctionGameServer*)arg;

	while (true)
	{
		instance->GetQueuedJobMessages();
	}

	return 0;
}

unsigned int WINAPI AuctionGameServer::MonitorThread(void* arg)
{
	AuctionGameServer* instance = (AuctionGameServer*)arg;

	while (true)
	{
		// Todo...
	}

	return 0;
}

void AuctionGameServer::GetQueuedJobMessages(void)
{
	DWORD desired = 0;

	while (true)
	{
		Job* job = nullptr;

		AcquireSRWLockExclusive(&_jobQueueLock);

		while (_jobQueue->empty())
		{
			SleepConditionVariableSRW(&_jobQueueCV, &_jobQueueLock, INFINITE, 0);
		}

		job = _jobQueue->front();
		_jobQueue->pop();

		ReleaseSRWLockExclusive(&_jobQueueLock);

		if (job->_type == eJobType::SYSTEM)
		{
			if (job->_sysType == eSysType::ACCEPT)
			{
				HandleAccept(job->_sessionId);
			}
			else if (job->_sysType == eSysType::RELEASE)
			{
				HandleRelease(job->_sessionId);
			}
			else if (job->_sysType == eSysType::TIMEOUT)
			{
				HandleTimeout();
			}
			else if (job->_sysType == eSysType::TERMINATE)
			{
				break;
			}
			else
			{
				// Wrong Packet
			}
		}
		else if (job->_type == eJobType::CONTENT)
		{
			HandleRecv(job->_sessionId, job->_packet);
		}

		// Todo : Release Job to Job Pool
		// Job::Free(job);
	}
}

void AuctionGameServer::HandleAccept(const SessionID sessionId)
{
	// Create Player
}

void AuctionGameServer::HandleRelease(const SessionID sessionId)
{
	// Disconnect Player and Remove Player Object
}

void AuctionGameServer::HandleTimeout(void)
{
	// Check Timeout for All Players
}

void AuctionGameServer::HandleRecv(const SessionID sessionId, SPacket* packet)
{
	// Search Player and Update LastRecvTime

	short msgTypeTemp;
	(*packet) >> msgTypeTemp;

	// Todo : Find Player by SessionId

	ePacketType msgType = (ePacketType)msgTypeTemp;

	switch (msgType)
	{
	case ePacketType::PACKET_CS_AUCTION_REQ_LOGIN:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_ROOM_CREATE:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_ROOM_JOIN:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_ROOM_LIST:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_PLAYER_READY:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_PLAYER_UNREADY:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_PLAYER_ROOM_EXIT:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_HOST_GAME_START:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_INGAME_LOAD_COMPLETE:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_JOIN_BIDDING:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_BID:
		break;
	case ePacketType::PACKET_CS_AUCTION_REQ_QUIT_GAME:
		break;
	default:
		break;
	}
}