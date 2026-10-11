#include <iostream>
#include <future>
using namespace std;

int heavy_computation_function(int value)
{
    int result = 0;

    for (int i = 0; i < value; i++)
    {
        result += i;
    }

    return result;
}

int main()
{
    future<int> fut =
        async(launch::async,
              heavy_computation_function,
              100000);

    cout << "Main thread continues working..." << endl;

    int final_result = fut.get();

    cout << "Final result: "
         << final_result << endl;

    return 0;
}