#include "Auction.h"

Auction::Auction()
	: _price(0)
	, _topBidder(nullptr)
	, _state(eAuctionState::READY)
	, _endTick(GetTickCount64() + AUCTION_READY_WAITTIME)
{
	// ePacketType::PACKET_SC_AUCTION_RES_ROUND_START;
}

void Auction::ChooseAuctionItem(void)

{
	static std::random_device rd;
	static std::mt19937 gen { rd() };
	static discrete_distribution<int> dist { {COIN_PROB, COIN_PROB, COIN_PROB, COIN_PROB, JOKER_PROB} };

	_item = (eItem)dist(gen);

	//ePacketType::PACKET_SC_AUCTION_RES_OPEN_ITEM;
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
		FinishAuction();
		break;
	default:
		break;
	}

}

void Auction::RegisterSingleParticipant(Player* player)
{
	if (_state != eAuctionState::REGISTRATION)
	{
		return;
	}

	_participants.insert(player);

	//ePacketType::PACKET_SC_AUCTION_RES_JOIN_BIDDING;

	return;
}

void Auction::RegisterMultiParticipants(const vector<Player*>& participants)
{
	if (_state != eAuctionState::REGISTRATION)
	{
		return;
	}

	for (Player* participant : participants)
	{
		_participants.insert(participant);
	}

	return;
}

void Auction::NoticeParticipants(void) const
{
	for (Player* player : _participants)
	{
		// Make Packet
	}
	//ePacketType::PACKET_SC_AUCTION_RES_BIDDING_JOINED_PLAYER_LIST;
	return;
}


bool Auction::TryBid(Player* bidPlayer, const int incrementAmount)
{
	if (_state != eAuctionState::PROGRESS)
	{
		return;
	}

	if (_participants.find(bidPlayer) == _participants.end())
	{
		//ePacketType::PACKET_SC_AUCTION_RES_BID; // 실패
		return false;
	}

	if (bidPlayer == _topBidder)
	{
		//ePacketType::PACKET_SC_AUCTION_RES_BID; // 실패
		return false;
	}

	_topBidder = bidPlayer;
	_price += incrementAmount;

	_endTick += GetTickCount64() + AUCTION_PROGRESS_ADDITIONAL_WAITTIME;

	//ePacketType::PACKET_SC_AUCTION_RES_BID; //성공
	//ePacketType::PACKET_SC_AUCTION_RES_NOTICE_NEW_BID; // 전체공지

	return true;
}

void Auction::FinishAuction(void) const
{
	//ePacketType::PACKET_SC_AUCTION_RES_END_BIDDING;
	//ePacketType::PACKET_SC_AUCTION_RES_HANDLE_BID_WINNER
	//ePacketType::PACKET_SC_AUCTION_RES_NOTICE_WINNER;
}