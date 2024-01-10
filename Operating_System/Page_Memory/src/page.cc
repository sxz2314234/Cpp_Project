#include<iostream>
#include"../include/page.hpp"

int page::get_page_num()const
{
    return page_num;
}

clock_t page::get_time()const
{
    return time;
}

void page::show()const
{
    std::cout<<"The page is "<<get_page_num()<<"\n"
    <<"And its time entering the memory is "<<get_time()<<std::endl;
}
