#pragma once

#include "Protocol.h"
#include "ContentsProtocol.h"
#include "IngameData.h"

enum class ePlayerState
{
	LOBBY,
	ROOM,
	INGAME,
};

using PlayerID = unsigned __int64;

class Player
{
public :
	Player(const SessionID sessionId, const PlayerID playerId)
		: _state(ePlayerState::LOBBY)
		, _sessionId(sessionId)
		, _playerId(playerId)
		, _roomId(-1)
		, _nickname(L"\0")
		, _ingameData{}
	{

	}

	bool IsWinner(void) const
	{
		return _ingameData.IsWinner();
	}

	void AddItem(int index)
	{
		_ingameData.AddItem(index);

		return;
	}

	void GainGold(int amount)
	{
		_ingameData._gold += amount;

		return;
	}

	void SpendGold(int amount)
	{
		if (_ingameData._gold >= amount)
		{
			_ingameData._gold -= amount;
		}

		return;
	}

	bool HasEnoughGold(int amount) const
	{
		return _ingameData._gold >= amount;
	}

private:
	ePlayerState _state;
	
	SessionID _sessionId;
	PlayerID _playerId;
	RoomID _roomId;

	Nickname _nickname;

	IngameData _ingameData;
};