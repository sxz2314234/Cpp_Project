#pragma once

#include <map>
#include <vector>
#include <utility>
#include <string>

using namespace std;

template <class T>
class hash_orders
{
    map<std::string, vector<T> *> user_order;

public:
    using _map = map<std::string, vector<T> *>;

    hash_orders() : user_order(){};
    ~hash_orders();

    bool empty() const { return user_order.empty(); }
    void build_client(std::string);
    typename _map::iterator find_client(std::string &name) { return user_order.find(name); }
    void insert_order(std::string &, T &);
    void erase_order(std::string &);
    vector<T> &get_orders(std::string name) const;

    typename _map::iterator end(){return user_order.end();}
};

#include "../src/Hash_Orders.cc"