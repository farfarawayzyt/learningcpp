#include <future>
#include <thread>
#include <iostream>

using std::cout;
using std::endl;

int addOne(int &x){
    return x++;
}

int main(void){
    int x;
    std::packaged_task<int(int &)> task(addOne);
    auto f = task.get_future();

    std::thread t1(std::move(task), std::ref(x));

    cout << f.get() << " " << x << endl;
    t1.join();

    return 0;
}