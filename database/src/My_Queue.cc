#include "My_Queue.hpp"
#include <stdexcept>

using iterator = my_queue::iterator;

Order &my_queue::operator[](int i) const
{
    iterator temp = iterator(head);

    for (int count = 0; count < i && temp != nullptr; ++count)
        temp++;

    if (temp != nullptr)
        return temp->order;
    else
    {
        throw std::runtime_error("Boundry_error");
    }
}

iterator &iterator::operator++()
{
    ++it;
    return *this;
}

iterator iterator::operator++(int)
{
    iterator temp = *this;
    ++it;

    return temp;
}

iterator &iterator::operator=(const iterator &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    it = new Task;
    it->order = obj->order;
    it->next = obj->next;

    return *this;
}

iterator::~iterator()
{
    delete it;
}

void my_queue::push(const Order &obj)
{
    if (empty())
    {
        head = new Task(obj);
        rear = head;
        count++;
        return;
    }

    rear->next = new Task(obj);
    rear = rear->next;
    count++;
}

void my_queue::pop()
{
    if (empty())
    {
        std::cout << "The queue is empty" << std::endl;
        return;
    }

    Task *temp = head;
    head = head->next;
    delete temp;
}

my_queue::~my_queue()
{
    Task *temp;
    if (!empty())
    {
        while (head != rear)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    delete rear;
}

my_queue &my_queue::operator=(const my_queue &_queue)
{
    if (this == &_queue)
    {
        return *this;
    }

    head = _queue.head;
    rear = _queue.rear;
    count = _queue.count;

    return *this;
}
