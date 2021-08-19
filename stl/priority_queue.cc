#include <queue>
#include <vector>
#include <iostream>
#include <functional>

struct Entry{
    size_t a_;
    size_t b_;
    Entry(size_t a, size_t b):a_(a), b_(b) {}
};

std::ostream &operator<<(std::ostream &os, Entry const &rhs){
    os << rhs.a_ << " " << rhs.b_;
    return os;
}

bool operator<(Entry const &lhs, Entry const &rhs){
    return lhs.a_ < rhs.a_ || (lhs.a_ == rhs.a_ && lhs.b_ < rhs.b_);
}

template<typename valueT, typename containerT, typename compT>
void displayAndClear(std::priority_queue<valueT, containerT, compT> &pq){
    while (!pq.empty()){
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
}

int main(void){
    std::priority_queue<Entry> pq0;
    pq0.emplace(0, 1);
    pq0.emplace(1, 2);
    displayAndClear(pq0);

    std::priority_queue<Entry, std::vector<Entry>, bool (*)(Entry const &, Entry const &)> pq1(
        [](Entry const &lhs, Entry const &rhs){return !(lhs < rhs); });
    pq1.emplace(0, 1);
    pq1.emplace(1, 2);
    displayAndClear(pq1);

    return 0;
}