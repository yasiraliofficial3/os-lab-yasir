#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex rw_mtx;
int data = 0;

void reader(int id)
{
    lock_guard<mutex> lock(rw_mtx);

    cout << "Reader " << id
         << " reads data: " << data << endl;
}

void writer(int id)
{
    lock_guard<mutex> lock(rw_mtx);

    data++;

    cout << "Writer " << id
         << " changed data to: " << data << endl;
}

int main()
{
    thread r1(reader, 1);
    thread r2(reader, 2);

    thread w1(writer, 1);

    thread r3(reader, 3);

    r1.join();
    r2.join();
    w1.join();
    r3.join();

    return 0;
}