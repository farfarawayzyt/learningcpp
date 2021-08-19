#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class Queue{
private:
    struct Node{
        std::shared_ptr<T> data;
        std::unique_ptr<Node> next;
    };
    std::unique_ptr<Node> head_;
    std::mutex head_mutex_;
    Node *tail_;
    std::mutex tail_mutex_;
    std::condition_variable data_cond_;

    Node *get_tail() {
        std::lock_guard<std::mutex> tail_guard(tail_mutex_);
        return tail_;
    }
    
    std::unique_ptr<Node> pop_head(){
        std::unique_ptr<Node> old_head = std::move(head_);
        head_ = std::move(old_head->next);
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data(){
        std::unique_lock<std::mutex> head_guard(head_mutex_);
        data_cond_.wait(head_guard, [this]{return head_.get() != get_tail();});
        return std::move(head_guard);
    }

    std::unique_ptr<Node> wait_pop_head(){
        std::unique_lock<std::mutex> head_guard(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<Node> try_pop(){
        std::lock_guard<std::mutex> head_guard(head_mutex_);
        if (head_.get() == get_tail()){
            return std::unique_ptr<Node>();
        }
        return pop_head();
    }

    // 仅有try_pop时的实现
    // std::unique_ptr<Node> pop_head(){
    //     std::lock_guard<std::mutex> head_guard(head_mutex_);
    //     //get_tail中对tail_mutex_的使用，确保了下述判断如果通过，则链表中至少有一个元素
    //     //也就是说head和tail没有指向同一个object
    //     if (head_.get() == get_tail()){
    //         return nullptr;
    //     }
    //     std::unique_ptr<Node> old_head = std::move(head_);
    //     head_ = std::move(old_head->next);
    //     return old_head;
    // }

public:
    Queue(): head_(new Node), tail_(head_.get()){}
    Queue(Queue const &other) = delete;
    Queue& operator=(Queue const &other) = delete;

    // std::shared_ptr<T> try_pop(){
    //     std::unique_ptr<Node> old_head = pop_head();
    //     return old_head ? old_head->data : std::shared_ptr<T>();
    // }

    std::shared_ptr<T> wait_and_pop(){
        std::unique_ptr<Node> const old_head = wait_pop_head();
        return old_head->data;
    }

    std::unique_ptr<Node> try_pop_head(){
        std::lock_guard<std::mutex> head_guard(head_mutex_);
        if (head_.get() == get_tail()){
            return std::unique_ptr<Node>();
        }
        return pop_head();
    }

    void push(T new_value){
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<Node> p(new Node);
        Node *const new_tail = p.get();
        {
            std::lock_guard<std::mutex> tail_guard(tail_mutex_);
            tail_->data = new_data;
            tail_->next = std::move(p);
            tail_=new_tail;
        }
        data_cond_.notify_one();
    }
};