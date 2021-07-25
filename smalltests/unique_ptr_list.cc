#include <memory>
#include <iostream>

struct Node{
    int x_;
    std::unique_ptr<Node> next_;
    Node(int x, std::unique_ptr<Node> next):x_(x), next_(std::move(next)){}
    Node(int x): Node(x, nullptr) {}
    ~Node() {std::cout << x_ << " destructed!\n";}
};

int main(void){
    auto a = std::make_unique<Node>(2);
    auto b = std::make_unique<Node>(3, std::move(a));
    
    {
        b = std::move(b->next_);
        std::cout << "oops\n";
    }
    // std::cout << b->x_ << std::endl;


    return 0;
}