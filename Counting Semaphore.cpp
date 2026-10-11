#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

class Semaphore
{
private:
    int count;
    mutex mtx;
    condition_variable cv;

public:
    Semaphore(int permits)
    {
        count = permits;
    }

    void acquire()
    {
        unique_lock<mutex> lock(mtx);

        while (count == 0)
        {
            cv.wait(lock);
        }

        count--;
    }

    void release()
    {
        unique_lock<mutex> lock(mtx);

        count++;

        cv.notify_one();
    }
};

// Maximum 3 threads can execute at the same time
Semaphore sem(3);

void task(int id)
{
    sem.acquire();

    cout << "Task " << id << " is executing." << endl;

    this_thread::sleep_for(chrono::seconds(2));

    cout << "Task " << id << " finished." << endl;

    sem.release();
}

int main()
{
    vector<thread> threads;

    for (int i = 1; i <= 6; i++)
    {
        threads.push_back(thread(task, i));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    return 0;
}