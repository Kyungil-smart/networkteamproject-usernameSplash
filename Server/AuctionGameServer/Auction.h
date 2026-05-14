#pragma once

#include <unordered_set>
#include <vector>
#include <random>
#include <Windows.h>

#include "Player.h"
#include "ContentsProtocol.h"

// 라운드(경매)에 대한 객체
// 상품이 무엇인지 정하고
// 각 플레이어의 입찰(Bid)을 처리함.

using namespace std;

enum class eAuctionState {
	READY = 0,
	OPEN,
	REGISTRATION,
	PROGRESS,
	FINISHED
};

class Auction
{
public:
	Auction();

private:
	void ChooseAuctionItem(void);
	void Update(void);

public:
	void RegisterSingleParticipant(Player* player);
	void RegisterMultiParticipants(const vector<Player*>& participants);
	
private:
	void NoticeParticipants(void) const;

public:
	bool TryBid(Player* bidPlayer, const int incrementAmount);

private:
	void FinishAuction(void) const;

private:
	int _price;
	Player* _topBidder;
	eItem _item;

	unordered_set<Player*> _participants;

	eAuctionState _state;
	uint64_t _endTick;
};