#include <iostream>
#include <thread>
#include <functional>
using namespace std;

void worker(int val, int& ref)
{
    val = val + 10;
    ref = ref + 10;

    cout << "Value inside thread: " << val << endl;
    cout << "Reference inside thread: " << ref << endl;
}

int main()
{
    int x = 10;
    int y = 20;

    thread t(worker, x, ref(y));

    t.join();

    cout << "Original x: " << x << endl;
    cout << "Original y: " << y << endl;

    return 0;
}