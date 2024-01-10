#ifndef _ORDER
#define _ORDER

#include <iostream>

class Order
{
public:
    enum class OrderCase
    {
        EmptyError,   // 所需要支付的账单不存在该用户
        NoPayError,   // 用户支付的钱比所需支付的钱少
        ApproveOrder, // 用户支付的钱正好为所需支付的钱
        Pending,      // 账单的初始状态
        MoneyOverFlow // 需要找钱
    };

private:
    std::string product_name; // 产品名
    std::string user_name;    // 顾客名
    OrderCase order_status;   // 订单状态
    size_t user_pay;          // 用户所需支付的钱

public:
    Order() : product_name("*"), user_name("*"), order_status(OrderCase::Pending), user_pay(0){};
    Order(const char *pn, const char *un, OrderCase status = OrderCase::Pending, size_t up = 0) : product_name(pn), user_name(un), order_status(status), user_pay(up){};

    Order(const Order &);

    void set_product_name(std::string pn) { product_name = pn; }
    void set_user_name(std::string un) { user_name = un; }
    void set_user_pay(size_t up) { user_pay = up; }
    void set_order_status(OrderCase status) { order_status = status; }

    std::string get_product_name() const { return product_name; }
    size_t get_user_price() const { return user_pay; }
    std::string get_user_name() const { return user_name; }
    OrderCase get_order_status() const { return order_status; }

    void show();
    int check_order(const size_t &obj) { return int(user_pay - obj); }
    Order& operator=(const Order&);
};

#endif