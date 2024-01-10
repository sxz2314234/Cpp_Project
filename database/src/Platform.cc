#include "Platform.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

void Mysql::Set_Mysql_par(const char *host, const char *user, const char *pwd, const char *database, size_t port, const char *socket, size_t flag)
{
    _mysqlhost = host;
    _mysqluser = user;
    _mysqlpwd = pwd;
    _mysqldatabase = database;
    _mysqlport = port;
    _socket = socket;
    _client_flag = flag;
}

void Mysql::Mysql_Initial()
{
    _mysql = nullptr;
    _mysql = mysql_init(_mysql);
    if (_mysql != nullptr)
    {
        if (!mysql_real_connect(_mysql, _mysqlhost, _mysqluser, _mysqlpwd,
                                _mysqldatabase, _mysqlport,
                                _socket, _client_flag))
        {
            std::cout << mysql_error(_mysql) << std::endl;
            throw std::runtime_error("Connection failed: " + std::string(mysql_error(_mysql)));
        }
    }
    else
        throw std::runtime_error("mysql_init() failed");
}

void Mysql::Mysql_Query()
{
    if (mysql_query(_mysql, "select * from commodities"))
    {
        throw std::runtime_error("Query execution failed: " + std::string(mysql_error(_mysql)));
    }
    else
        _result = mysql_store_result(_mysql);

    if (!_result)
    {
        throw std::runtime_error("mysql_store_result() failed");
    }
}

Mysql::~Mysql()
{
    mysql_free_result(_result);
    mysql_close(_mysql);
}

platform::platform(Mysql &accounts) : approved_queue(), task_queue(), result(), field_names()
{
    if (accounts._result)
    {
        int num = mysql_num_fields(accounts._result);

        for (int i = 0; i < num; ++i)
        {
            MYSQL_FIELD *_field = mysql_fetch_field(accounts._result);
            std::cout << "Column: " << i + 1 << " "
                      << "Name: " << _field->name << " "
                      << "Type: " << _field->type << " "
                      << "Length: " << _field->length << std::endl;
            field_names.push_back(_field->name);
        }

        int nums = mysql_num_rows(accounts._result);
        for (int i = 0; i < nums; ++i)
        {
            MYSQL_ROW _row = mysql_fetch_row(accounts._result);
            std::string main_key = _row[0];
            result[main_key] = new std::vector<std::string>();
            for (int i = 1; i < num; ++i)
            {
                result[main_key]->push_back(_row[i]);
            }
        }
    }
    else
        throw std::runtime_error("Result Error: There is no result in it.");
}

using scenario = Order::OrderCase;

void platform::produce_order(Order&obj)
{
    // Order obj;

    // std::cout << "What is your name?" << std::endl;
    std::string cname;
    // std::cin >> cname;
    cname=obj.get_user_name();

    // std::cout << "Which goods do you want to buy? " << std::endl;
    std::string goods_name;
    // std::cin >> goods_name;
    goods_name=obj.get_product_name();

    size_t price = standard_price(goods_name);

    obj.set_user_name(cname);
    obj.set_product_name(goods_name);
    obj.set_user_pay(price);

    task_queue.push(obj);
}

size_t platform::standard_price(std::string &consumption)
{
    auto it = result.find(consumption);

    if (it == result.end())
    {
        return 0;
    }

    return std::stoul((*(it->second))[1]);
}

void platform::check_task_queue()
{
    // Here you can do everything you want,
    // if you need to check the order.
    approved_queue = task_queue;
}

void platform::show() const
{
    for (auto it = field_names.begin(); it != field_names.end(); ++it)
        std::cout << *it << "   ";

    std::cout << std::endl;

    for (auto it = result.begin(); it != result.end(); ++it)
    {
        std::cout << it->first;
        std::vector<std::string> temp_result = *(it->second);

        for (auto it = temp_result.begin(); it != temp_result.end(); ++it)
            std::cout << "    " << *it << "   ";
        std::cout << std::endl;
    }
}