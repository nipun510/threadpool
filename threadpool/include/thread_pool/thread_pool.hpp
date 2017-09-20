
#include<future>
#include <vector>
#include <iostream>
#include <memory>
#include <queue>
#include <functional>

class thread_pool
{
public:
    thread_pool(std::size_t s):workers_size(s),stop(false)
    {
        
        for(std::size_t i = 0; i < workers_size; ++i)
        {
            workers.emplace_back(
                [this]
                {
                    for(;;)
                    {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(queue_mutex);
                            condition.wait(lock, [this]{return this->stop || !this->tasks.empty();});
                            if(this->stop && this->tasks.empty())
                            {
                                return;
                            }
                            task = std::move(this->tasks.front());
                            tasks.pop();
                        }
                        task();
                    }
                }
            );
        } 
    }

    template<class F, class ...Args>
    auto submit(F &&f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using result_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<result_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<result_type> result = task->get_future();
        auto  fun = [task]()
                    {(*task)();};
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.push(fun);
        }
        condition.notify_one();
        return result;
    }

    ~thread_pool()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(auto & worker: workers)
        {
            worker.join();
        }

    }
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()> > tasks;
    std::mutex queue_mutex;
    std::size_t workers_size;
    bool stop;
     std::condition_variable condition;
};

