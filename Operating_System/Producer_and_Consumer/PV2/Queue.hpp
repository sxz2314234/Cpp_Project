#include<atomic>

#ifndef QUEUE_
#define QUEUE_

template<class T>
class Queue
{
    class point
    {
        T* object;
        point* front;
        point* back;

        public:
        point(T*obj=nullptr,point* f=nullptr,point*b=nullptr);
        ~point();

        void push_front(point*);
        void pop_back();
        point* get_point();
    };
    
    std::atomic<bool> permission;
    point* qfront;
    point* qback;
    int count;

    public:
    Queue();
    Queue(const Queue<T>&)=delete;
    Queue& operator=(const Queue&)=delete;

    void push(T*);
    void pop(T*);
};

#endif