#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
using namespace std;

struct Order {
    int id;
    string side;     // BUY or SELL
    double price;
    int quantity;
    long timestamp;

    Order(int i, string s, double p, int q, long t) {
        id = i;
        side = s;
        price = p;
        quantity = q;
        timestamp = t;
    }
};

#endif