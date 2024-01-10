#include "Pay_System.hpp"
#include<fstream>

using scenario = Order::OrderCase;

pay_system::pay_system(platform &pf) : pay_order(), pay_total_money()
{
    // 得到产生的合格订单
    my_queue* approved = pf.get_approved_queue();

    // 创建用户
    for (auto it = approved->begin(); it != approved->end(); it = it->next)
    {
        Order temp_order = it->order;
        std::string temp_name = temp_order.get_user_name();
        pay_order.build_client(temp_name);
        pay_total_money[temp_name] = Order();
    }
    for (auto it = approved->begin(); it != approved->end(); it = it->next)
    {
        Order temp_order = it->order;
        std::string temp_order_name = temp_order.get_user_name();

        // 得到每个用户的账单
        pay_order.insert_order(temp_order_name, temp_order);
    }

    for (auto it = pay_total_money.begin(); it != pay_total_money.end(); ++it)
    {
        std::string name = it->first;

        // 得到每个用户的所需要付的总账单
        Order total;
        size_t price = sum(name);

        total.set_user_name(name);
        total.set_product_name(std::string("Total"));
        total.set_user_pay(price);

        it->second = total;
    }
}

size_t pay_system::sum(std::string name)
{
    vector<Order> order;
    try
    {
        order = pay_order.get_orders(name);
    }
    catch (const std::runtime_error &e)
    {
        return 0;
    }

    size_t sum_money = 0;
    for (auto item : order)
        sum_money += item.get_user_price();
    return sum_money;
}

Order pay_system::pay_money(std::string &name)
{
    size_t order = sum(name);

    if (order == 0)
    {
        std::cout<<"There is no such order."<<std::endl;
        return Order();
    }

    std::cout << "Let's start to pay the money, the total is " << order << std::endl;
    size_t the_paied;
    std::cout << "Please pay: " << std::endl;
    std::cin >> the_paied;
    pay_total_money[name].set_user_pay(the_paied);
    return pay_total_money[name];
}

Order &pay_system::set_order_status(Order &target)
{
    size_t real_price = sum(target.get_user_name());

    int pviot = target.check_order(real_price);

    if (pviot == 0)
    {
        target.set_order_status(scenario::ApproveOrder);
        return target;
    }
    else if (pviot < 0)
    {
        target.set_order_status(scenario::NoPayError);
        target.set_user_pay(-pviot);
        return target;
    }

    else
    {
        target.set_order_status(scenario::MoneyOverFlow);
        target.set_user_pay(pviot);
        return target;
    }
}

void pay_system::handle_case(Order &target)
{
    std::cout << "Now, the owner of the order is " << target.get_user_name() << std::endl;
    std::cout << std::endl;
    scenario status = target.get_order_status();

    switch (status)
    {
    case scenario::EmptyError:
        std::cout << "The shop doesn't sell the goods." << std::endl;
        std::cout << "So you can get another the commodity.";
        break;

    case scenario::MoneyOverFlow:
        std::cout << "I will give change to you. " << std::endl;
        std::cout << "The change is " << target.get_user_price() << std::endl;
        break;

    case scenario::NoPayError:
    {
        size_t second_pay = 0;
        while (target.get_order_status() != scenario::ApproveOrder)
        {
            std::cout<<std::endl;
            std::cout << "The order underpaied."
                      << "You should still pay " << target.get_user_price() << std::endl;
            cin >> second_pay;
            if (second_pay == target.get_user_price())
            {
                target.set_order_status(scenario::ApproveOrder);
                target.set_user_pay(second_pay);
            }
            else
                continue;
        }
    }
    break;

    case scenario::ApproveOrder:
        std::cout << "This order has been approved" << std::endl;
        break;

    default:
        std::cout << "The order's status gets an error." << std::endl;
        break;
    }

    std::cout<<"Thank you. Goodbye!!!"<<std::endl;
    std::cout<<std::endl;
}

void pay_system::complete_order(std::string &name)
{
    std::cout << "Start remove the client's order" << std::endl;

    delete pay_order.find_client(name)->second;

    pay_total_money.erase(name);
}

void pay_system::show(std::string &name)
{
    auto orders = pay_order.find_client(name);

    if (orders == pay_order.end())
    {
        std::cout << "Hey, Sir.\n"
                  << "There is no your order." << std::endl;
        return;
    }

    std::cout << "Hello, " << name << std::endl;
    std::cout << "Here are your goods buied in this shop" << std::endl;
    for (auto i = orders->second->begin(); i != orders->second->end(); ++i)
        std::cout << i->get_product_name() << " ";

    std::cout << std::endl;
    std::cout << "So, the total money you should pay is: " << sum(name) << std::endl;
}

void pay_system::write_bill()
{
    const char* filename="bill.txt";
    std::ofstream fout(filename,std::ios::app);

    if(!fout.is_open())
    {
        std::cout<<"Can not open the file!!!"<<std::endl;
        return ;
    }

    int count=1;
    for(auto it=pay_total_money.begin();it!=pay_total_money.end();++it)
    {
        vector<Order> temp_order=pay_order.get_orders(std::string(it->first));
        fout<<"        ------订单发票: "<<count++<<"号------"<<std::endl;
        fout<<"         用户: "<<it->first<<std::endl;
        fout<<"         购买的物品: ";
        for(auto it2=temp_order.begin();it2!=temp_order.end();++it2)
        {
            fout<<it2->get_product_name()<<" ";
        }
        fout<<std::endl;
        fout<<"         所以您一共消费了: "<<it->second.get_user_price()<<std::endl;
        fout<<std::endl;
    }

    fout.close();
}