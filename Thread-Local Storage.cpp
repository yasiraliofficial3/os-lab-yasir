#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

queue<function<void()>> tasks;

mutex queue_mtx;
condition_variable cv;

bool stop = false;

void worker()
{
    while (true)
    {
        function<void()> task;

        {
            unique_lock<mutex> lock(queue_mtx);

            cv.wait(lock, [] {
                return stop || !tasks.empty();
            });

            if (stop && tasks.empty())
                return;

            task = move(tasks.front());

            tasks.pop();
        }

        task();
    }
}

int main()
{
    vector<thread> workers;

    for (int i = 0; i < 3; i++)
    {
        workers.emplace_back(worker);
    }

    for (int i = 1; i <= 5; i++)
    {
        {
            lock_guard<mutex> lock(queue_mtx);

            tasks.push([i] {
                cout << "Executing Task "
                     << i << endl;
            });
        }

        cv.notify_one();
    }

    {
        lock_guard<mutex> lock(queue_mtx);
        stop = true;
    }

    cv.notify_all();

    for (auto& t : workers)
    {
        t.join();
    }

    return 0;
}