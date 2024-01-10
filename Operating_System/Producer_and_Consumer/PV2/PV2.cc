#include <iostream>
#include <queue>
#include <future>
#include <string>
#include <random>

using namespace std;

const string op_strings = "+-*/%";

class task
{
    int num1;
    int num2;
    char op;

public:
    task(int n1 = rand() % 50, int n2 = rand() % 20, char op3 = op_strings[rand() % op_strings.size()]) : num1(n1), num2(n2), op(op3){};
    task(const task &) = delete;
    task &operator=(const task &) = delete;

    int operator()()
    {
        return run();
    }
    int run()
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

        case '/':
            if (num2 == 0)
            {
                cout << "The division must > 0. " << endl;
                break;
            }
            result = num1 / num2;
            break;

        case '*':
            result = num1 * num2;
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
    }
};
class Task_Queue
{
    int count;
    queue<task> task_queue;

    public:
    explicit Task_Queue(int c):count(c),task_queue(){};

    void P(task&);
    void V(task&);
};

