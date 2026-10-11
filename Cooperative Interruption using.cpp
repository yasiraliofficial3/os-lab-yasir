#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
using namespace std;

const int NUM_PHILOSOPHERS = 5;

vector<mutex> forks(NUM_PHILOSOPHERS);

void dine(int philosopher_id)
{
    int left_fork_id = philosopher_id;
    int right_fork_id =
        (philosopher_id + 1) % NUM_PHILOSOPHERS;

    int first = min(left_fork_id, right_fork_id);
    int second = max(left_fork_id, right_fork_id);

    unique_lock<mutex> l1(forks[first]);
    unique_lock<mutex> l2(forks[second]);

    cout << "Philosopher "
         << philosopher_id
         << " is eating." << endl;

    this_thread::sleep_for(
        chrono::milliseconds(500));

    cout << "Philosopher "
         << philosopher_id
         << " finished eating." << endl;
}

int main()
{
    vector<thread> philosophers;

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosophers.emplace_back(dine, i);
    }

    for (auto& philosopher : philosophers)
    {
        philosopher.join();
    }

    return 0;
}