#include"Queue.hpp"

template<class T>
Queue<T>::point::point(T*obj,point*f,point*b):object(obj),front(f),back(b)
{};

template<class T>
Queue<T>::point::~point()
{
    delete object;
}

template<class T>
typename Queue<T>::point* Queue<T>::point::get_point()
{
    return object;
}

template<class T>
void Queue<T>::point::push_front(point* temp)
{
    if(front==nullptr)
    {
        front=temp;
        temp->back=this;
    }
    else
    {
        point* the_front=front;
        the_front->back=temp;
        temp->front=the_front;
        the_front->back=this;
    }
}

template<class T>
void Queue<T>::point::pop_back()
{
    this=this->front;
    delete this->back;
}

template<class T>
Queue<T>::Queue():permission(false)
{
    qfront=nullptr;
    qback=nullptr;
    int count=0;
}

template<class T>
void Queue<T>::push(T*obj)
{   
    if(qfront==nullptr)
    {
        point* p=new point(obj);
        qfront=p;
        qback=qfront;
        ++count;
    }
    else
    {
        point temp=new point(obj);
        qfront->push_front(temp);
        qfront=temp;
        ++count;
    }
    permission.store(true,std::memory_order_acquire);
}

template<class T>
void Queue<T>::pop(T* obj)
{
    while(permission.load(std::memory_order_consume));
    
    obj=qback->get_point();

}