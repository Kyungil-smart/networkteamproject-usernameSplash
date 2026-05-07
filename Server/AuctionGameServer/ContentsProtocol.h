#pragma once

#define PLAYER_MAX 10000
#define ROOM_MAX 10000

#define NICKNAME_LEN 20
#define ROOMNAME_LEN 20

enum class ePacketType : short
{
#pragma region OutGameProtocol

	///
	/// Out Game Protocol (Login, Lobby, Room)
	///

	/*
		로그인 요청
		{
			WORD Type
			WCHAR Nickname[20]
		}
	*/
	PACKET_CS_AUCTION_REQ_LOGIN = 0,

	/*
		로그인 응답
		{
			WORD Type

			BYTE Status		// 0 : 성공, 1 : 실패
			INT64 PlayerId	// 서버로부터 부여받는 Player의 ID
		}
	*/
	PACKET_SC_AUCTION_RES_LOGIN,

	/*
		방 생성 요청
		{
			WORD Type

			WCHAR RoomName[20]
		}
	*/
	PACKET_CS_AUCTION_REQ_ROOM_CREATE,

	/*
		방 생성 응답
		{
			WORD Type

			BYTE Status		// 0 : 성공, 1 : 실패
			INT64 RoomId
		}
	*/
	PACKET_SC_AUCTION_RES_ROOM_CREATE,

	/*
		방 참가 요청
		{
			WORD Type

			INT64 RoomId
		}
	*/
	PACKET_CS_AUCTION_REQ_ROOM_JOIN,

	/*
		방 참가 응답
		{
			WORD Type

			BYTE Status		// 0 : 성공, 1 : 실패(인원 꽉 참), 2 : 실패(이미 사라진 방)
			INT64 RoomId
		}
	*/
	PACKET_SC_AUCTION_RES_ROOM_JOIN,

	/*
		방 참가 플레이어 목록 응답
		{
			WORD Type

			int PlayerNum

			INT64 PlayerId
			WCHAR NickName[20]
			BYTE IsReady
			...
		}
	*/
	PACKET_SC_AUCTION_RES_ROOM_PLAYER_LIST,

	/*
		신규 Player 방 참가 응답
		{
			WORD Type

			INT64 PlayerId
			WCHAR NickName[20]
		}
	*/
	PACKET_SC_AUCTION_RES_ROOM_NEW_PLAYER,

	/*
		방 목록 요청 (Lobby에서 새로고침하는 방식)
		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_ROOM_LIST,

	/*
		방 목록 응답
		{
			WORD Type

			int RoomNum		//방 개수

			INT64 RoomId
			WCHAR RoomName[20]
			int RoomPlayerNum
			...
		}
	*/
	PACKET_SC_AUCTION_RES_ROOM_LIST,

	/*
		플레이어 준비 요청
		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_PLAYER_READY,

	/*
		플레이어 준비 응답 (브로드캐스트)
		{
			WORD Type

			INT64 PlayerId
		}
	*/
	PACKET_SC_AUCTION_RES_PLAYER_READY,

	/*
		플레이어 준비 해제 요청
		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_PLAYER_UNREADY,

	/*
		플레이어 준비 해제 응답	(브로드캐스트)
		{
			WORD Type

			INT64 PlayerID
		}
	*/
	PACKET_SC_AUCTION_RES_PLAYER_UNREADY,

	/*
		플레이어 방 퇴장 요청

		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_PLAYER_ROOM_EXIT,

	/*
		플레이어 방 퇴장 응답 (브로드캐스트)
		{
			WORD Type
			INT64 PlayerID
		}
	*/
	PACKET_SC_AUCTION_RES_PLAYER_ROOM_EXIT,

	/*
		호스트(방장) 변경 응답	(호스트가 퇴장할 시 서버가 방장을 변경하고 통보함)
		{
			WORD Type
			INT64 PlayerID			// (Host Player의 ID)
		}
	*/
	PACKET_SC_AUCTION_RES_HOST_CHANGE,

	/*
		호스트(방장) 플레이어 게임 시작 요청
		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_HOST_GAME_START,

	/*
		호스트(방장) 플레이어 게임 시작 응답	(브로드캐스트하고 일제히 InGame으로 넘어감)
		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_HOST_GAME_START,

	/*
		클라이언트의 인게임 Scene Load 완료 통지
		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_INGAME_LOAD_COMPLETE,
#pragma endregion

#pragma region InGameProtocol

	///
	/// In Game Protocol
	/// 
	
	/*
		게임 시작 알림
		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_GAME_START,

	/*
		Round 시작 알림
		{
			WORD Type

			int RoundNum
		}
	*/
	PACKET_SC_AUCTION_RES_ROUND_START,

	/*
		경매 아이템 공개
		{
			WORD Type

			int ItemType
		}
	*/
	PACKET_SC_AUCTION_RES_OPEN_ITEM,

	/*
		경매 참여 요청
		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_JOIN_BIDDING,

	/*
		경매 참여 완료 응답
		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_JOIN_BIDDING,

	/*
		경매 참여자 공개

		{
			WORD Type

			int PlayerNum

			INT64 PlayerId
			BYTE IsJoined
			(반복)
		}
	*/
	PACKET_SC_AUCTION_RES_BIDDING_JOINED_PLAYER_LIST,

	/*
		입찰 요청
		{
			WORD Type

			int CurPrice
			int Increment
		}
	*/
	PACKET_CS_AUCTION_REQ_BID,

	/*
		입찰 응답
		{
			WORD Type

			BYTE Status		// 0 : 성공, 1 : 실패
		}
	*/
	PACKET_SC_AUCTION_RES_BID,

	/*
		입찰 공지 (브로드캐스팅)
		{
			WORD Type

			int CurPrice
		}
	*/
	PACKET_SC_AUCTION_RES_NOTICE_NEW_BID,

	/*
		경매 종료

		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_END_BIDDING,
	
	/*
		낙찰 처리 (낙찰자에게 아이템 전달, 돈 차감)

		{
			WORD Type

			int ItemType
			int Price
		}
	*/
	PACKET_SC_AUCTION_RES_HANDLE_BID_WINNER,

	/*
		승리 플레이어 알림
		승리 플레이어가 보유한 아이템들을 보여줌

		{
			WORD Type

			INT64 PlayerID

			int ItemNum
			int ItemType
		}
	*/
	PACKET_SC_AUCTION_RES_NOTICE_WINNER,

	/*
		게임 종료 처리

		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_GAME_OVER,

	/*
		게임 탈주 요청

		{
			WORD Type
		}
	*/
	PACKET_CS_AUCTION_REQ_QUIT_GAME,

	/*
		게임 탈주 응답 (탈주자를 Lobby로 보냄)

		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_QUIT_GAME,

	/*
		게임 탈주 알림 (다른 플레이어들에게 탈주 알림)

		{
			WORD Type

			INT64 PlayerId
		}
	*/
	PACKET_SC_AUCTION_RES_NOTICE_SOMEONE_QUIT,

	/*
		Player 상태 갱신 (이 패킷을 각 Player들에게 보내줌, 클라 갱신용)
		{
			WORD Type

			int PlayerGold
			int ItemNum
			int ItemType[ItemNum]
		}
	*/
	PACKET_SC_AUCTION_RES_UPDATE_PLAYER_STATE,
#pragma endregion
};