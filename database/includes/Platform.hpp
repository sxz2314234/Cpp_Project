#ifndef _PLATFORM
#define _PLATFORM

#include "Order.hpp"
#include "My_Queue.hpp"
#include <map>
#include <string>
#include <vector>
#include <mysql/mysql.h>

class Mysql
{
    MYSQL *_mysql;
    MYSQL_RES *_result;
    friend class platform;

    const char *_mysqlhost;
    const char *_mysqluser;
    const char *_mysqlpwd;
    const char *_mysqldatabase;
    size_t _mysqlport;
    const char *_socket;
    size_t _client_flag;

public:
    Mysql(){};
    Mysql(const Mysql &) = delete;
    ~Mysql();

    void Set_Mysql_par(const char *, const char *, const char *,
                       const char *, size_t port = 0,
                       const char *_socket = "NULL", size_t cflag = 0);
    void Mysql_Initial();
    void Mysql_Query();
};

class platform
{
    my_queue approved_queue;
    my_queue task_queue;
    std::map<std::string, std::vector<std::string> *> result;
    std::vector<std::string> field_names;

public:
    platform(Mysql &);

    void produce_order(Order &);
    size_t standard_price(std::string &);
    void check_task_queue();
    my_queue* get_approved_queue() { return &approved_queue; }
    std::vector<std::string> &get_field_names() { return field_names; }

    void show() const;
};

#endif