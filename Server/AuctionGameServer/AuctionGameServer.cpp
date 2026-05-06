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
	
}