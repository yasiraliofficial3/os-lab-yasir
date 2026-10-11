#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

atomic<bool> stop_requested(false);

void worker()
{
    while (!stop_requested)
    {
        cout << "Worker is running..." << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "Worker received stop request." << endl;
    cout << "Worker is exiting safely." << endl;
}

int main()
{
    thread my_thread(worker);

    // Let the worker run for some time
    this_thread::sleep_for(chrono::seconds(3));

    // Request the worker to stop
    cout << "Main: Requesting worker to stop..." << endl;

    stop_requested = true;

    // Wait for the worker to finish
    my_thread.join();

    cout << "Main: Worker stopped successfully." << endl;

    return 0;
}