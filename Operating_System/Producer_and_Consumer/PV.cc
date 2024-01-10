#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include "condition_variable"
#include <random>
#include <memory>

using namespace std;

class task
{
    int num1;
    int num2;
    char op;

public:
    task(int n1, int n2, char op3) : num1(n1), num2(n2), op(op3){};
    task() : num1(0), num2(0), op('*'){};

    int operator()() { return run(); }
    int run();
    void get(int &n1, int &n2, char &op3);
};

void task::get(int &n1, int &n2, char &op3)
{
    n1 = num1;
    n2 = num2;
    op3 = op;
}

int task::run()
{
    int result = 0;
    switch (op)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 <= 0)
        {
            cout << "This division must be bigger than 0. " << endl;
            result = -1;
        }
        else
            result = num1 / num2;
        break;

    case '%':
        if (num2 <= 0)
        {
            cout << "mod error, abort" << endl;
            result = -1;
        }
        else
            result = num1 % num2;
        break;

    default:
        cout << "Invalied operation: " << op << endl;
        break;
    }
    return result;
}

template <class T>
class blockqueue
{
    mutex mt;
    condition_variable cv;
    queue<T> b_queue;

public:
    blockqueue() = default;

    void P(T &&);
    shared_ptr<T> V();
};

template <class T>
void blockqueue<T>::P(T &&t)
{
    unique_lock<mutex> lk(mt);
    b_queue.push(t);
    cv.notify_one();
}

template <class T>
shared_ptr<T> blockqueue<T>::V()
{
    shared_ptr<T> t;
    unique_lock<mutex> lk(mt);
    while (b_queue.empty())
        cv.wait(lk);

    t = make_shared<T>(b_queue.front());
    b_queue.pop();
    return t;
}

blockqueue<task> bqueue;

const string ops = "+-*%/";
mutex global_mutex;
void producer()
{
    chrono::milliseconds dura(1000); // 定一个1秒的时间

    while (true)
    {
        int num1 = rand() % 50;
        int num2 = rand() % 30;
        char op = ops[rand() % ops.size()];

        bqueue.P(task(num1, num2, op));

        unique_lock<mutex> lk(global_mutex);
        cout << "生产者生产: ";
        cout << num1 << op << num2 << "= ?";
        cout << endl;
        lk.unlock();
        this_thread::sleep_for(dura);
    }
}

void consumer()
{
    int num1, num2;
    int result;
    char op;

    while (true)
    {
        shared_ptr<task> t = bqueue.V();

        t->get(num1, num2, op);
        result = (*t)();

        unique_lock<mutex> lk(global_mutex);
        cout << "消费者消费: ";
        cout << num1 << op << num2 << " = " << result << endl;
        lk.unlock();
    }
}

int main()
{
    thread t1(producer);
    thread t3(producer);
    thread t2(consumer);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}