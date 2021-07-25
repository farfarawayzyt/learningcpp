#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

class TinyEvent{
private:
    bool isSet_;
    mutable std::mutex m_;
    std::condition_variable cv_;
public:
    TinyEvent():isSet_(false) {};
    
    bool IsSet() const {
        std::lock_guard<std::mutex> guard(m_);
        return isSet_;
    }

    void Clear() {
        std::lock_guard<std::mutex> guard(m_);
        isSet_ = false;
    }

    void Set(){
        std::lock_guard<std::mutex> guard(m_);
        isSet_ = true;
        cv_.notify_all();
    }

    void Wait(){
        std::unique_lock<std::mutex> guard(m_);
        cv_.wait(guard, [this]{return isSet_;});
    }
};

void WaitOnEvent(TinyEvent &event){
    event.Wait();
    cout << "Wait pass from " << std::this_thread::get_id() << endl;
}

int main(void){
    TinyEvent e;

    std::thread t1(WaitOnEvent, std::ref(e));
    std::thread t2(WaitOnEvent, std::ref(e));

    cout << "Threads created" << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    e.Set();
    t1.join();
    t2.join();

    return 0;
}