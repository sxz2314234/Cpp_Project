#include "Platform.hpp"
#include "Pay_System.hpp"
#include "Order_Manager.hpp"
#include <iostream>

void produce(platform &);

int main()
{
    Mysql system;
    system.Set_Mysql_par("localhost", "sxz", "123", "sxz", 3306, NULL, 0);
    system.Mysql_Initial();

    system.Mysql_Query();
    // system.show_Mysql();

    platform stage(system);
    stage.show();
    produce(stage);
    stage.check_task_queue();

    My_Order_Manage order_manager;
    order_manager.Register_Order(stage);
    order_manager.Assign_number();
    order_manager.Order_goods();
    order_manager.Notice_product();

    std::cout << std::endl;

    pay_system paysystem(stage);

    std::string name;
    for (int i = 0; i < paysystem.order_count(); ++i)
    {
        std::cout << "Please enter the client name you want to know: " << std::endl;
        std::cin >> name;

        Order handle_order = paysystem.pay_money(name);
        if (handle_order.get_user_name() != "*")
        {
            paysystem.set_order_status(handle_order);
            paysystem.handle_case(handle_order);
        }
    }

    std::cout << "\n------开始打印发票------" << std::endl;
    std::cout << "请稍等......" << std::endl;
    paysystem.write_bill();
    std::cout << "订单已经打印完成,请查看......" << std::endl;

    paysystem.complete_order(name);
    return 0;
}

void produce(platform &st)
{
    Order temp_order;
    std::string client_name;
    std::string client_goods;

    std::cout << "What's your name? " << std::endl;
    cin >> client_name;
    std::cout << "Which goods do you want to buy? " << std::endl;
    cin >> client_goods;
    temp_order.set_user_name(client_name);
    temp_order.set_product_name(client_goods);
    st.produce_order(temp_order);

    while (true)
    {
        std::cout << std::endl;

        std::cout << "Would you want to buy some others?\n"
                  << "If yes, please enter y.If no, then enter n." << std::endl;

        char reply;
        cin >> reply;
        cin.get();

        if (reply == 'y')
        {
            std::cout << "Which goods do you want to buy? " << std::endl;
            cin >> client_goods;
            temp_order.set_user_name(client_name);
            temp_order.set_product_name(client_goods);
            st.produce_order(temp_order);
            continue;
        }
        else
        {
            std::cout << "Is there any body who wants to buy some things?\n"
                      << "If you want to buy, please enter y;Otherwise enter n." << std::endl;
            cin >> reply;
            cin.get();

            if (reply == 'y')
            {
                std::cout << "What's your name? " << std::endl;
                cin >> client_name;
                std::cout << "Which goods do you want to buy? " << std::endl;
                cin >> client_goods;
                temp_order.set_user_name(client_name);
                temp_order.set_product_name(client_goods);
                st.produce_order(temp_order);
                continue;
            }
            else
                break;
        }
    }
}