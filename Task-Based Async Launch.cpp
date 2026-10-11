#include <iostream>
#include <thread>
using namespace std;

thread_local int txn_id = 0;

void run()
{
    txn_id++;

    cout << "Thread ID: "
         << this_thread::get_id()
         << ", Transaction ID: "
         << txn_id << endl;
}

int main()
{
    thread t1(run);
    thread t2(run);
    thread t3(run);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}