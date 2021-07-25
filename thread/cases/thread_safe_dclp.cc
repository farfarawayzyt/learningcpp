#include <atomic>
#include <mutex>

class Singleton;
std::atomic<Singleton *> Singleton::m_instance;
std::mutex Singleton::m_mutex;

class Singleton{
private:
    int x_;
    static std::atomic<Singleton *> m_instance;
    static std::mutex m_mutex;
public:
    Singleton(): x_(0) {}
    Singleton(int x): x_(x){}

    Singleton *Singleton::getInstance(){
        Singleton *tmp = m_instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acq_rel);
        
        if (tmp == nullptr){
            std::lock_guard<std::mutex> guard(Singleton::m_mutex);
            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr){
                tmp = new Singleton;
                std::atomic_thread_fence(std::memory_order_release);
                m_instance.store(tmp, std::memory_order_relaxed);
            }
        }
        return tmp;
    }
};