#include<thread_pool/thread_pool.hpp>
#include<future>
#include <chrono>
#include <thread>

int fun(int a)
{
    std::cout << "yeah !!! fun called val => " << a  << std::endl;
    std::cout << "fun finished successfully" << std::endl;
    return a;
}

void fun2()
{
    std::cout << "just fun called" << std::endl;
}

int main()
{
    thread_pool t(4);
    std::future<int> f = t.submit(fun, 12);
    std::future<void> f2 = t.submit(fun2);
    std::cout <<  "value => " << f.get() << std::endl;

}
