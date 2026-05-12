#pragma once

#include <unordered_map>

#include "ContentsProtocol.h"

struct IngameData
{

public:
	IngameData()
		: _gold(0)
		, _item {}
		, _itemCount(0)
	{

	}

private:
	bool IsWinner(void) const
	{
		if (_itemCount >= 5)
		{
			return true;
		}

		int uniqueItemCount = 0;

		for (int iCnt = 0; iCnt < MAX_ITEM_TYPES; ++iCnt)
		{
			if (_item[iCnt] >= 3)
			{
				return true;
			}

			if (_item[iCnt] > 0)
			{
				uniqueItemCount++;
			}
		}

		if (uniqueItemCount >= MAX_ITEM_TYPES)
		{
			return true;
		}

		return false;
	}

	void AddItem(int index)
	{
		_item[index]++;
		_itemCount++;
	}

private:
	int _gold;
	int _item[MAX_ITEM_TYPES];

private:
	int _itemCount;

	friend class Player;
};