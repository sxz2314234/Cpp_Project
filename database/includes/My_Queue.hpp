#ifndef _MYQUEUE
#define _MYQUEUE

#include "Order.hpp"

class my_queue
{
public:
    struct Task
    {
        /* data */
        Order order;
        Task *next;

        Task() : order(), next(nullptr){};
        Task(const Order &o, Task *n = nullptr) : order(o), next(n){};
    };

    class iterator
    {
        Task *it;

    public:
        iterator() : it(nullptr){};
        iterator(Task *i) : it(i){};
        iterator(const iterator &i) : it(i.it){};
        ~iterator();
        Task operator*() const { return *it; }
        Task *operator->() const { return it; }

        iterator &operator++();
        iterator operator++(int);

        bool operator!=(const iterator &obj) const { return it != obj.it; }
        iterator &operator=(const iterator &);
    };

private:
    Task *head;
    Task *rear;
    int count;

public:
    my_queue() : head(nullptr), rear(nullptr), count(0){};
    ~my_queue();

    bool empty() const { return count == 0; }
    Task *begin() const { return head; }
    Task *end() const { return rear->next; }

    void push(const Order &);
    Order &front() const { return head->order; }
    void pop();
    Order &back() const { return rear->order; }
    Order &operator[](int) const;
    my_queue &operator=(const my_queue &);
};

#endif