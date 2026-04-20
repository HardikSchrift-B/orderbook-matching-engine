#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <queue>
#include "Order.h"

using namespace std;

class OrderBook
{
public:

    map<double, queue<Order>, greater<double>> buyBook;
    map<double, queue<Order>> sellBook;

    void addOrder(Order order)
    {
        if(order.side == "BUY")
        {
            matchBuy(order);
        }
        else
        {
            matchSell(order);
        }
    }

    void matchBuy(Order order)
    {
        while(order.quantity > 0 && !sellBook.empty())
        {
            auto bestSell = sellBook.begin();

            if(bestSell->first <= order.price)
            {
                Order seller = bestSell->second.front();

                int tradedQty = min(order.quantity, seller.quantity);

                cout << "TRADE EXECUTED: "
                     << tradedQty
                     << " @ "
                     << seller.price
                     << endl;

                order.quantity -= tradedQty;
                seller.quantity -= tradedQty;

                bestSell->second.pop();

                if(seller.quantity > 0)
                {
                    bestSell->second.push(seller);
                }

                if(bestSell->second.empty())
                {
                    sellBook.erase(bestSell);
                }
            }
            else
            {
                break;
            }
        }

        if(order.quantity > 0)
        {
            buyBook[order.price].push(order);
        }
    }

    void matchSell(Order order)
    {
        while(order.quantity > 0 && !buyBook.empty())
        {
            auto bestBuy = buyBook.begin();

            if(bestBuy->first >= order.price)
            {
                Order buyer = bestBuy->second.front();

                int tradedQty = min(order.quantity, buyer.quantity);

                cout << "TRADE EXECUTED: "
                     << tradedQty
                     << " @ "
                     << buyer.price
                     << endl;

                order.quantity -= tradedQty;
                buyer.quantity -= tradedQty;

                bestBuy->second.pop();

                if(buyer.quantity > 0)
                {
                    bestBuy->second.push(buyer);
                }

                if(bestBuy->second.empty())
                {
                    buyBook.erase(bestBuy);
                }
            }
            else
            {
                break;
            }
        }

        if(order.quantity > 0)
        {
            sellBook[order.price].push(order);
        }
    }

    void cancelOrder(int id)
    {
        for(auto it = buyBook.begin(); it != buyBook.end(); it++)
        {
            queue<Order> temp;
            bool found = false;

            while(!it->second.empty())
            {
                Order o = it->second.front();
                it->second.pop();

                if(o.id == id)
                {
                    found = true;
                    continue;
                }

                temp.push(o);
            }

            it->second = temp;

            if(found)
            {
                cout << "\nOrder " << id << " Cancelled.\n";
                return;
            }
        }

        for(auto it = sellBook.begin(); it != sellBook.end(); it++)
        {
            queue<Order> temp;
            bool found = false;

            while(!it->second.empty())
            {
                Order o = it->second.front();
                it->second.pop();

                if(o.id == id)
                {
                    found = true;
                    continue;
                }

                temp.push(o);
            }

            it->second = temp;

            if(found)
            {
                cout << "\nOrder " << id << " Cancelled.\n";
                return;
            }
        }

        cout << "\nOrder ID not found.\n";
    }

    void displayBook()
    {
        cout << "\n===== BUY BOOK =====" << endl;

        for(auto level : buyBook)
        {
            queue<Order> q = level.second;

            while(!q.empty())
            {
                Order o = q.front();
                q.pop();

                cout << "BUY "
                     << o.quantity
                     << " @ "
                     << o.price
                     << endl;
            }
        }

        cout << "\n===== SELL BOOK =====" << endl;

        for(auto level : sellBook)
        {
            queue<Order> q = level.second;

            while(!q.empty())
            {
                Order o = q.front();
                q.pop();

                cout << "SELL "
                     << o.quantity
                     << " @ "
                     << o.price
                     << endl;
            }
        }
    }
};

#endif