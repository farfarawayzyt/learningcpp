#include <memory>

template<typename T>
class Queue{
private:
    struct Node{
        T data_;
        std::unique_ptr<Node> next_;
        Node(T data):data_(std::move(data)){}
    };
    std::unique_ptr<Node> head_;
    Node *tail_;
public:
    Queue(): tail_(nullptr) {}
    Queue(const Queue &other) = delete;
    Queue& operator=(const Queue &other) = delete;
    std::shared_ptr<T> try_pop(){
        if(!head_){
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(
            std::make_shared<T>(std::move(head_->data_)));
        std::unique_ptr<Node> const old_head = std::move(head_);
        head_ = std::move(old_head->next);
        if (!head_)
            tail_ = nullptr;
        return res;
    }
};