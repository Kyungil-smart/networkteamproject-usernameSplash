
#include "Protocol.h"

class SPacket;

enum class eJobType
{
	NONE = 0,
	SYSTEM,
	CONTENT,
};

enum class eSysType
{
	NONE = 0,
	ACCEPT,
	RELEASE,
	TIMEOUT,
	TERMINATE,
};

class Job
{
public:
	Job()
		: _type(eJobType::NONE)
		, _sysType(eSysType::NONE)
		, _sessionId(-1)
		, _packet(nullptr)
	{

	}

	void Initialize(const eJobType type, const eSysType sysType, const SessionID sessionId, const SPacket* packet)
	{
		_type = type;
		_sysType = sysType;
		_sessionId = sessionId;
		_packet = const_cast<SPacket*>(packet);
	}

public:
	eJobType _type;
	eSysType _sysType;
	SessionID _sessionId;
	SPacket* _packet;
};