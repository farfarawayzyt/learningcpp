#include <iostream>

class Foo{
    int x_;
public:
    Foo(){x_ = ++x; std::cout << x_ << " constructed!" << std::endl;}
    Foo(const Foo&){x_ = ++x; std::cout << x_ << " copy constructed!" << std::endl;}
    static int x;
    static Foo GetObject(){return Foo();}
    ~Foo(){std::cout << x_ << " destructed!" << std::endl;}
};

int Foo::x = 0;

int main(void){
    Foo obj = Foo::GetObject();

    return 0;
}