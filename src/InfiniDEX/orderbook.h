// Copyright (c) 2017-2018 The Infinex Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <vector>
#include <map>

class COrderBook;
class COrderBookManager;

typedef std::map<uint64_t, COrderBook> PriceOrderBook; //price and order data
extern std::map<int, PriceOrderBook> orderBidBook; //trade pair and bid data
extern std::map<int, PriceOrderBook> orderAskBook; //trade pair and ask data
extern COrderBookManager orderBookManager;


class COrderBook
{
private:
	std::vector<unsigned char> vchSig;

public:
	uint64_t nOrderPrice;
	uint64_t nQuantity;
	uint64_t nAmount;
	uint64_t nLastUpdateTime;

	COrderBook(uint64_t nOrderPrice, uint64_t nQuantity, uint64_t nAmount, uint64_t nLastUpdateTime) :
		nOrderPrice(nOrderPrice),
		nQuantity(nQuantity),
		nAmount(nAmount),
		nLastUpdateTime(nLastUpdateTime)
	{}

	COrderBook() :
		nOrderPrice(0),
		nQuantity(0),
		nAmount(0),
		nLastUpdateTime(0)
	{}

};

class COrderBookManager
{
private:
	std::vector<unsigned char> vchSig;
	uint64_t GetAdjustedTime();
	bool InsertNewBidOrder(int TradePairID, uint64_t Price, int64_t Qty);
	bool InsertNewAskOrder(int TradePairID, uint64_t Price, int64_t Qty);

public:
	void AdjustBidQuantity(int TradePairID, uint64_t Price, int64_t Qty);
	void AdjustAskQuantity(int TradePairID, uint64_t Price, int64_t Qty);
	void UpdateBidOrder(int TradePairID, uint64_t Price, uint64_t Quantity);
	void UpdateAskOrder(int TradePairID, uint64_t Price, uint64_t Quantity);	
	void CheckForTradePossibility(int TradePairID);
};
#endif