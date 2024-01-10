#ifndef PAGE_
#define PAGE_

#include<ctime>

class page
{
    int page_num;
    clock_t time;

    public:
    page(int p,clock_t t):page_num(p),time(t){};
    
    int get_page_num()const;
    clock_t get_time()const;
    void set_clock(){time=clock();}
    void show()const;
};

#endif