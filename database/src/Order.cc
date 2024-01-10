#include "Order.hpp"
#include <stdexcept>

void Order::show()
{
    std::cout << "The owner of this Order is " << user_name << std::endl;
    std::cout << "The product'name is " << product_name << std::endl;
    std::cout << "Its price is " << user_pay << std::endl;
}

Order::Order(const Order &obj)
{
    product_name = obj.product_name;
    user_name = obj.user_name;
    order_status = obj.order_status;
    user_pay = obj.user_pay;
}

Order& Order::operator=(const Order&obj)
{
    if(this==&obj)
    {
        return *this;
    }

    product_name = obj.product_name;
    user_name = obj.user_name;
    order_status = obj.order_status;
    user_pay = obj.user_pay;
    return *this;
}