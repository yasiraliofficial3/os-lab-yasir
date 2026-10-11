#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtxA;
mutex mtxB;

void transfer_funds()
{
    // Lock both mutexes safely
    lock(mtxA, mtxB);

    // Take ownership of the already locked mutexes
    lock_guard<mutex> lockA(mtxA, adopt_lock);
    lock_guard<mutex> lockB(mtxB, adopt_lock);

    cout << "Both locks acquired safely." << endl;
    cout << "Executing transaction..." << endl;
}

int main()
{
    thread t1(transfer_funds);
    thread t2(transfer_funds);

    t1.join();
    t2.join();

    cout << "Transaction completed." << endl;

    return 0;
}