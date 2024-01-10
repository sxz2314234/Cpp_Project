#pragma once
#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <unistd.h>
#include <Platform.hpp>
#include<vector>

using namespace std;

class My_Order_Manage
{

public:
    My_Order_Manage();

    // 登记订单
    bool Register_Order(platform&);

    // 分配工种号
    bool Assign_number();

    // 准备订货
    bool Order_goods();

    // 通知生产部门
    void Notice_product();

    ~My_Order_Manage()
    {
        if (conn != nullptr)
        {
            mysql_close(conn);
        }
    }

private:
    vector<string> orderqueue;
    
    MYSQL *conn;    // 连接句柄
    MYSQL_RES *res; // 结果集指针
    MYSQL_ROW row; // 行数据类型

    string ip;
    string username;
    string password;
    string dbname;
    unsigned short port;

};
