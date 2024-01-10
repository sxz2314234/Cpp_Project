#ifndef _HASH_ORDER_SRC
#define _HASH_ORDER_SRC

#include "Hash_Orders.hpp"
#include <iostream>

template <class T>
void hash_orders<T>::build_client(std::string name)
{
    user_order[name] = new vector<T>();
}

template <class T>
void hash_orders<T>::insert_order(std::string &name, T &task)
{
    auto client_order = user_order.find(name);

    if (client_order == user_order.end())
    {
        std::cout << "There is no this order." << std::endl;
        return;
    }

    client_order->second->push_back(task);
}

template <class T>
hash_orders<T>::~hash_orders()
{
    for (auto it=user_order.begin();it!=user_order.end();++it)
        delete it->second;
}

template <class T>
void hash_orders<T>::erase_order(std::string &name)
{
    auto it = find_client(name);
    user_order.erase(it);
}

template <class T>
vector<T> &hash_orders<T>::get_orders(std::string name) const
{
    auto order = user_order.find(name);

    if (order == user_order.end())
    {
        throw std::runtime_error("There is no this client's orders");
    }
    return *(order->second);
}

#endif