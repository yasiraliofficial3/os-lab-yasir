#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class Barrier
{
private:
    int count;
    int total;
    mutex mtx;
    condition_variable cv;

public:
    Barrier(int numberOfThreads)
    {
        total = numberOfThreads;
        count = 0;
    }

    void wait()
    {
        unique_lock<mutex> lock(mtx);

        count++;

        if (count == total)
        {
            count = 0;
            cv.notify_all();
        }
        else
        {
            cv.wait(lock, [this]()
            {
                return count == 0;
            });
        }
    }
};

const int NUM_THREADS = 3;

Barrier sync_point(NUM_THREADS);

void worker(int id)
{
    cout << "Thread " << id
         << " completed Phase 1." << endl;

    // Wait for all threads
    sync_point.wait();

    cout << "Thread " << id
         << " started Phase 2." << endl;
}

int main()
{
    vector<thread> threads;

    for (int i = 1; i <= NUM_THREADS; i++)
    {
        threads.push_back(thread(worker, i));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    return 0;
}