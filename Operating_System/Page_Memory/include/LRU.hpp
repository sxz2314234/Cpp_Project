#include <ctime>
#include "page.hpp"

class LRU
{
    static int page_count;
    page *page_value;
    LRU *next;

    void set_clock();
    LRU *find_min_clock() const;
    LRU *find(const LRU *) const;
    void push(LRU *);

public:
    LRU(page *p_v = nullptr, LRU *n = nullptr) : page_value(p_v), next(n){};
    ~LRU();

    void set_page_count(int);
    void update(LRU *);
    void show() const;
};