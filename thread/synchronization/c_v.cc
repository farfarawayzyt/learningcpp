#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

bool flag = false;
std::mutex m;
std::unique_lock<std::mutex> ul(m);
std::condition_variable cv;

void set_flag(){
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    flag = true;
    cv.notify_one();
}

int main(){
    std::thread t(set_flag);

    cv.wait(ul, []{return flag;});

    cout << "Wait passed!\n";

    t.join();

    return 0;
}
