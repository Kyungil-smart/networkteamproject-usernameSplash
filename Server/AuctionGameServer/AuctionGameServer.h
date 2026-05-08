#pragma once

#include "Server.h"
#include "ContentsProtocol.h"
#include "Job.h"

#include <queue>
#include <synchapi.h>

#pragma comment(lib, "Synchronization.lib")

using namespace std;

class AuctionGameServer : public IServer
{
public:
	AuctionGameServer()
	{

	};

	~AuctionGameServer()
	{

	}

public:
	bool Initialize(void);
	void Terminate(void);

private:
	virtual void OnInitialize(void) override;
	virtual bool OnConnectionRequest(const wchar_t* ip, const short port) override;
	virtual void OnAccept(const SessionID sessionId) override;
	virtual void OnRelease(const SessionID sessionId) override;
	virtual void OnRecv(const SessionID sessionId, SPacket* packet) override;
	virtual void OnError(const int errorCode, const wchar_t* errorMsg) override;

private:
	static unsigned int WINAPI UpdateThread(void* arg);
	static unsigned int WINAPI MonitorThread(void* arg);

private:
	void GetQueuedJobMessages(void);

private:
	void HandleAccept(const SessionID sessionId);
	void HandleRelease(const SessionID sessionId);
	void HandleTimeout(void);
	void HandleRecv(const SessionID sessionId, SPacket* packet);

public:
	inline bool IsAlive(void) const
	{
		return _isAlive;
	}

private:
	bool _isAlive = true;
	HANDLE _updateThread = NULL;
	HANDLE _monitorThread = NULL;

private:
	 queue<Job*>* _jobQueue; // job queue
	 SRWLOCK _jobQueueLock;
	 CONDITION_VARIABLE _jobQueueCV;
};