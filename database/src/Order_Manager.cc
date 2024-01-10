#include "Order_Manager.hpp"
#include <iomanip>
#include <string>
#include <My_Queue.hpp>
#include <cstdlib> // 包含std::rand()函数

using namespace std;

My_Order_Manage::My_Order_Manage():orderqueue()
{
    ip = "127.0.0.1";
    username = "sxz";
    password = "123";
    dbname = "sxz";
    port = 3306;

    conn = mysql_init(nullptr);
    res = nullptr;

    mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk"); // 设置编码
    mysql_set_character_set(conn, "utf8");

    if (!mysql_real_connect(conn, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0)) // 连接
    {
        cout << "连接出错:" << mysql_error(conn) << endl;
        return;
    }
    else
    {
        cout << "连接成功！" << endl;
    }
}

const string number = "0123456789";
const string num = "12345";
bool My_Order_Manage::Register_Order(platform &pt) // 登记一个订单
{
    my_queue* reg = pt.get_approved_queue();

    string id;
    string name;
    string cname;
    string sql;

    for (auto it = reg->begin(); it != reg->end(); it = it->next)
    {
        cout << "登记订单: 请输入订单号 产品名 购买人姓名:" << endl;
        id = "";
        for (int i = 0; i < 5; ++i)
        {
            id += number[std::rand() % 10];
        }

        orderqueue.push_back(id);

        name = it->order.get_product_name();
        cname = it->order.get_user_name();

        cout << id << " " << name << " " << cname << endl;
        sql = "insert into orders(order_id,product_id,product_name,client_name) values('" + id + "'," + num[rand() % 5] + ",'" + name + "','" + cname + "');";

        if (mysql_query(conn, sql.c_str()))
        {
            cout << "添加失败:" << mysql_error(conn) << endl;
            return false;
        }
    }
    return true;
}

// 分配工种号
bool My_Order_Manage::Assign_number()
{

    // 显示一下表
    string sql = "select product_id,order_id from orders";

    // 选择订单ID分配工种号
    if (mysql_query(conn, "select * from orders;"))
    {
        cerr << "Error: " << mysql_error(conn) << endl;
        return false;
    }

    res = mysql_store_result(conn);   // 获取结果集
    int cols = mysql_num_fields(res); // 计算结果集中，列的个数

    cout << "\n现有的账单为:" << endl;

    while (row = mysql_fetch_row(res))
    {

        for (int i = 0; i < cols - 1; ++i)
        {
            cout << left << setw(10) << row[i];
        }
        cout << endl;
    }

    // 选择订单ID分配工种号
    if (mysql_query(conn, sql.c_str()))
    {
        cerr << "Error: " << mysql_error(conn) << endl;
        return false;
    }
    res = mysql_store_result(conn); // 获取结果集

    cout << "====================================================" << endl;
    cout << "            ------分配工号的规则------                " << endl;
    cout << "   序列:            商品:            工号:            " << endl;
    cout << "   001              薯片             1               " << endl;
    cout << "   002              面包             2               " << endl;
    cout << "   003              泡面             3               " << endl;
    cout << "   004              苹果             4               " << endl;
    cout << "   005              纸巾             5               " << endl;
    cout << "=====================================================" << endl;
    while (row = mysql_fetch_row(res))
    {
        switch (stoi(row[0]))
        {
        case 1:
        {
            cout << "现在开始为订单号为: " << row[1] << " 分配工号." << endl;

            if (mysql_query(conn, "update orders set assign_num=1 where product_id=1;"))
            {
                cerr << "Error: " << mysql_error(conn) << endl;
                return false;
            }
        }
        break;

        case 2:
        {
            cout << "现在开始为订单号为: " << row[1] << " 分配工号." << endl;

            if (mysql_query(conn, "update orders set assign_num=2 where product_id=2;"))
            {
                cerr << "Error: " << mysql_error(conn) << endl;
                return false;
            }
        }
        break;

        case 3:
        {
            cout << "现在开始为订单号为: " << row[1] << " 分配工号." << endl;

            if (mysql_query(conn, "update orders set assign_num=3 where product_id=3;"))
            {
                cerr << "Error: " << mysql_error(conn) << endl;
                return false;
            }
        }
        break;
        case 4:
        {
            cout << "现在开始为订单号为: " << row[1] << " 分配工号." << endl;

            if (mysql_query(conn, "update orders set assign_num=4 where product_id=4;"))
            {
                cerr << "Error: " << mysql_error(conn) << endl;
                return false;
            }
        }
        break;
        case 5:
        {
            cout << "现在开始为订单号为: " << row[1] << " 分配工号." << endl;

            if (mysql_query(conn, "update orders set assign_num=5 where product_id=5;"))
            {
                cerr << "Error: " << mysql_error(conn) << endl;
                return false;
            }
        }
        }
        cout << "  分配完毕!!!  " << endl;
    }

    // 释放结果集合mysql句柄
    mysql_free_result(res);
    return true;
}

// 准备订货
bool My_Order_Manage::Order_goods()
{
    cout<<"\n------现在开始准备订货------"<<endl;
    
    // 显示一下表
    if (mysql_query(conn, "select * from orders;"))
    {
        cerr << "Error: " << mysql_error(conn) << endl;
        return false;
    }
    res = mysql_store_result(conn);   // 获取结果集
    int cols = mysql_num_fields(res); // 计算结果集中，列的个数

    while (row = mysql_fetch_row(res))
    {

        for (int i = 0; i < cols; ++i)
        {
            cout << left << setw(10) << row[i];
        }
        cout << endl;
    }

    // mysql_free_result(res);

    for(auto it=orderqueue.begin();it!=orderqueue.end();++it)
    {
        cout << "现在订单id为: " <<*it<<endl;
    
        printf(" %s号订单准备订货中...\n", (*it).c_str());
        sleep(3);
        cout<<"订货成功!!!\n"<<endl;
    }
    
    return true;
}

// 通知生产部门
void My_Order_Manage::Notice_product()
{
    cout << endl;
    cout << "通知生产部门取走订单以生产" << endl;
    string id;       // 要删除的订单的id
    char flag = 'n'; // 是否继续的标志
    do
    { // 执行删除操作
        cout << "请输入要待取走的商品的编号:" << endl;
        cin >> id;
        char queren = 'n';
        cout<<"确认要取走编号为"<<id<<"的商品吗(y/n):"<<endl;
        cin >> queren;
        if (queren == 'y')
        {
            string deletesql; // 数据库插入语句
            // mysql_query(conn, "set id gbk"); // 设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
            deletesql = "delete from orders where order_id='" + id + "';";

            if (mysql_query(conn, deletesql.c_str())) // 执行SQL语句
            {
                cout << "订单取走失败！！！想继续删除吗(y/n):";
            }
            else
            {
                cout << "订单取走成功！！！想继续删除吗(y/n):";
            }
            // mysql_free_result(res);
        }

        cin >> flag;
        while (flag != 'y' && flag != 'n')
        {
            cout << "指令错误！！！！！<请输入y/n>" << endl;
            cin >> flag;
        }
    } while (flag == 'y');
}
