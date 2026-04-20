#include <iostream>
#include <chrono>
#include <cstdlib>
#include "Order.h"
#include "OrderBook.h"

using namespace std;
using namespace chrono;

int main()
{
    OrderBook ob;

    int totalOrders = 100000;

    auto start = high_resolution_clock::now();

    for(int i = 1; i <= totalOrders; i++)
    {
        string side;

        if(i % 2 == 0)
            side = "BUY";
        else
            side = "SELL";

        double price = 495 + rand() % 11;   // 495 to 505
        int qty = 1 + rand() % 100;

        ob.addOrder(Order(i, side, price, qty, i));
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nTotal Orders Processed: " << totalOrders << endl;
    cout << "Execution Time: " << duration.count() << " ms" << endl;

    double ops = totalOrders / (duration.count() / 1000.0);

    cout << "Orders Per Second: " << ops << endl;

    return 0;
}