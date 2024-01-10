#ifndef _PAY_SYSTEM
#define _PAY_SYSTEM

#include "Hash_Orders.hpp"
#include "Order.hpp"
#include "My_Queue.hpp"
#include "Platform.hpp"
#include <map>
#include <string>
#include <stdexcept>

class pay_system
{
    hash_orders<Order> pay_order;            // 每个用户所购买的商品的信息
    map<std::string, Order> pay_total_money; // 每个用户一共所需支付的钱

    size_t sum(std::string name); // 计算每个用户总共所需付的钱
public:
    pay_system(platform &); // 由支付平台中的合格订单进行初始化
    pay_system() = delete;
    ~pay_system() = default;

    Order pay_money(std::string &);     // 支付钱
    Order &set_order_status(Order &);   // 根据所支付的钱,设定账单的状态
    void handle_case(Order &);          // 根据订单状态处理,处理订单
    void complete_order(std::string &); // 完成订单之后,将订单从订单记录中消除
    void show(std::string &);           // 展示顾客购买订单的相关信息
    void write_bill();
    int order_count()const{return pay_total_money.size();}
};

#endif