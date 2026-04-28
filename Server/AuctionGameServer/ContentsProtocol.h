#pragma once

#define PLAYER_MAX 10000

#define NICKNAME_LEN 20
#define ROOMNAME_LEN 20

enum class ePacketType
{
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
			INT64 PlayerId
		}
	*/
	PACKET_SC_AUCTION_RES_LOGIN,

	/*
		방 생성 요청
		{
			WORD Type

			INT64 PlayerId
			WCHAR RoomName[20]
		}
	*/
	PACKET_CS_AUCTION_REQ_ROOM_CREATE,

	/*
		방 생성 응답
		{
			WORD Type

			BYTE Status		// 0 : 성공, 1 : 실패
			INT64 PlayerId
			INT64 RoomId
		}
	*/
	PACKET_SC_AUCTION_RES_ROOM_CREATE,

	/*
		방 참가 요청
		{
			WORD Type

			INT64 PlayerId
			INT64 RoomId
		}
	*/
	PACKET_CS_AUCTION_REQ_ROOM_JOIN,

	/*
		방 참가 응답
		{
			WORD Type

			BYTE Status		// 0 : 성공, 1 : 실패(인원 꽉 참), 2 : 실패(이미 사라진 방)
			INT64 PlayerId
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

			INT64 PlayerId
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

			INT64 PlayerId
		}
	*/
	PACKET_CS_AUCTION_REQ_PLAYER_READY,

	/*
		플레이어 준비 응답
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

			INT64 PlayerID
		}
	*/
	PACKET_CS_AUCTION_REQ_PLAYER_UNREADY,

	/*
		플레이어 준비 해제 응답
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
			INT64 PlayerID
		}
	*/
	PACKET_CS_AUCTION_REQ_PLAYER_ROOM_EXIT,

	/*
		플레이어 방 퇴장 응답
		{
			WORD Type
			INT64 PlayerID
		}
	*/
	PACKET_SC_AUCTION_RES_PLAYER_ROOM_EXIT,

	/*
		호스트(방장) 변경 응답
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
			INT64 PlayerId
		}
	*/
	PACKET_CS_AUCTION_REQ_HOST_GAME_START,

	/*
		호스트(방장) 플레이어 게임 시작 응답
		{
			WORD Type
		}
	*/
	PACKET_SC_AUCTION_RES_HOST_GAME_START,
};