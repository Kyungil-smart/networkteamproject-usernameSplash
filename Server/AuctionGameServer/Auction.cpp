#include "Auction.h"

Auction::Auction()
	: _price(0)
	, _topBidder(nullptr)
	, _state(eAuctionState::READY)
	, _endTick(GetTickCount64() + AUCTION_READY_WAITTIME)
{
}

void Auction::ChooseAuctionItem(void)

{
	static std::random_device rd;
	static std::mt19937 gen { rd() };
	static discrete_distribution<int> dist { {COIN_PROB, COIN_PROB, COIN_PROB, COIN_PROB, JOKER_PROB} };

	_item = (eItem)dist(gen);
}

void Auction::Update(void)
{
	if (GetTickCount64() < _endTick)
	{
		return;
	}

	switch (_state)
	{
	case eAuctionState::READY:
		ChooseAuctionItem();
		_state = eAuctionState::OPEN;
		_endTick = GetTickCount64() + AUCTION_OPEN_WAITTIME;
		break;
	case eAuctionState::OPEN:
		_state = eAuctionState::REGISTRATION;
		_endTick = GetTickCount64() + AUCTION_REGISTRATION_WAITTIME;
		break;
	case eAuctionState::REGISTRATION:
		_state = eAuctionState::PROGRESS;
		_endTick = GetTickCount64() + AUCTION_PROGRESS_WAITTIME;
		break;
	case eAuctionState::PROGRESS:
		_state = eAuctionState::FINISHED;
		_endTick = GetTickCount64() + AUCTION_FINISHED_WAITTIME;
		break;
	case eAuctionState::FINISHED:
		break;
	default:
		break;
	}

}

void Auction::RegisterParticipants(const vector<Player*>& participants)
{
	for (Player* participant : participants)
	{
		_participants.insert(participant);
	}

	return;
}

bool Auction::TryBid(Player* bidPlayer, const int incrementAmount)
{
	if (_participants.find(bidPlayer) == _participants.end())
	{
		return false;
	}

	if (bidPlayer == _topBidder)
	{
		return false;
	}

	_topBidder = bidPlayer;
	_price += incrementAmount;

	_endTick += GetTickCount64() + AUCTION_PROGRESS_ADDITIONAL_WAITTIME;

	return true;
}

void Auction::FinishAuction(void)
{
	//ePacketType::PACKET_SC_AUCTION_RES_END_BIDDING;
	//ePacketType::PACKET_SC_AUCTION_RES_HANDLE_BID_WINNER
	//ePacketType::PACKET_SC_AUCTION_RES_NOTICE_WINNER;
}