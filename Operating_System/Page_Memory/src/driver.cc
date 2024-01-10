#include"../include/LRU.hpp"
#include"../include/page.hpp"
#include<iostream>
#include<ctime>
#include<random>
#include<memory>

void page_swap_arg(int);

int main()
{
    std::cout<<"How much page frames do you want? "<<std::endl;
    int count=0;
    std::cin>>count;
    page_swap_arg(count);
    return 0;
}

void page_swap_arg(int count)
{
    std::shared_ptr<LRU>swap=std::make_shared<LRU>();
    swap->set_page_count(count);
    while(true)
    {
        LRU* temp=new LRU(new page(rand()%6,clock()));
        
        swap->update(temp);
        swap->show();
        std::cout<<std::endl;
    }
}