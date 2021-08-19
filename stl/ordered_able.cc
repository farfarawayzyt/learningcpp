#include <map>
#include <iostream>

class Foo{
friend bool operator<(Foo const &lhs, Foo const &rhs);
friend std::ostream &operator<<(std::ostream& os, Foo const &rhs);
private:
    int x_;
    int y_;

};

class Foo2{
friend bool compareFoo2(Foo2 const &lhs, Foo2 const &rhs);
private:
    int z_;
};

bool operator<(Foo const &lhs, Foo const &rhs){
    return lhs.x_ < rhs.x_ || (lhs.x_ == rhs.x_ && lhs.y_ < rhs.y_);
}

std::ostream &operator<<(std::ostream &os, Foo const &rhs){
    os << rhs.x_ << " " << rhs.y_;
    return os;
}

bool compareFoo2(Foo2 const &lhs, Foo2 const &rhs){
    return lhs.z_ < rhs.z_;
}

int main(void){
    std::multimap<Foo, int> mm;
    mm.insert({Foo(), 1});
    mm.insert({Foo(), 2});
    auto obj = Foo();
    auto x = mm.lower_bound(Foo());
    auto y = mm.upper_bound(Foo());
    std::cout << x->first << x->second << std::endl;

    std::multimap<Foo2, int, decltype(compareFoo2) *> mm2(compareFoo2);

    return 0;
}