#include <iostream>
#include "../include/LRU.hpp"

int LRU::page_count = 0;

LRU *LRU::find(const LRU *target) const
{
    if (next == nullptr)
        return nullptr;

    LRU *ptr = next;
    while (ptr != nullptr)
    {
        if (ptr->page_value->get_page_num() != target->page_value->get_page_num())
            ptr = ptr->next;
        else
            break;
    }
    if (ptr != nullptr)
        return ptr;
    else
        return nullptr;
}

LRU *LRU::find_min_clock() const
{
    LRU *fast = next;
    LRU *low = nullptr;
    LRU *min_clock = next;
    LRU *min_clock_addr = nullptr;

    while (fast != nullptr)
    {
        low = fast;
        fast = fast->next;

        if (fast != nullptr && min_clock->page_value->get_time() > fast->page_value->get_time())
        {
            min_clock_addr = low;
            min_clock = fast;
        }
    }
    return min_clock_addr;
}

void LRU::set_clock()
{
    page_value->set_clock();
}

void LRU::update(LRU *ptr)
{
    std::cout << "Now the page " << ptr->page_value->get_page_num() << " wants to enter" << std::endl;
    LRU *target = find(ptr);
    if (target != nullptr)
    {
        target->set_clock();
        return;
    }

    if (page_count)
    {
        if (next == nullptr)
        {
            next = ptr;
            page_count--;
            return;
        }

        ptr->next = next;
        next = ptr;
        page_count--;
        return;
    }

    target = find_min_clock();
    if (target != nullptr)
        target->push(ptr);
    else
    {
        LRU *temp = next;
        ptr->next = next->next;
        next = ptr;
        delete temp->page_value;
    }
}

LRU::~LRU()
{
    LRU *fast = next;
    LRU *low = nullptr;
    while (fast != nullptr)
    {
        low = fast;
        fast = fast->next;
        delete low->page_value;
        delete low;
    }
}

void LRU::push(LRU *target)
{
    target->next = next->next;
    next = target;
}
void LRU::show() const
{
    LRU *iter = next;
    while (iter != nullptr)
    {
        iter->page_value->show();
        iter = iter->next;
    }
}

void LRU::set_page_count(int i)
{
    page_count = i;
}