#include <future>
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

void setValue(std::promise<int> &p){
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    p.set_value(45);
}

void getValue(std::promise<int> &p){
    auto f = p.get_future();
    cout << f.get() << endl;
}

int main(void){
    std::promise<int> p;
    auto f = p.get_future();

    std::thread t1(setValue, std::ref(p));
    t1.detach();

    cout << f.get() << endl;

    std::promise<int> q;
    std::thread t2(getValue, std::ref(q));
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    q.set_value(42);
    t2.join();


    return 0;
}