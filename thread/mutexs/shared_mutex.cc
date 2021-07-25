#include <shared_mutex>
#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

shared_mutex s_m;

void read_func(){
    shared_lock<shared_mutex> sl(s_m);
    cout << "Get read lock, thread_id:" << this_thread::get_id() << "\n";
    this_thread::sleep_for(1000ms);
    cout << "Release read lock, thread_id:" << this_thread::get_id() << "\n";
}



int main(void){
    thread t1(read_func);
    thread t2(read_func);
    t1.join();
    t2.join();
    return 0;
}