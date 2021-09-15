#include <iostream>
#include <memory>

class Outer{
public:
    struct Inner{
        std::unique_ptr<int> upInt_;

        Inner(){}
        Inner(Inner &&rhs):upInt_(std::move(rhs.upInt_)){std::cout << "Inner Move Constructor Called!";}
        Inner &operator=(Inner &&rhs){upInt_ = std::move(rhs.upInt_); std::cout << "Inner Move Assignment Called"; return *this;}
    };

    Inner iobj_;

    // Inner &GetIobj() {return iobj_;}
    Inner &&GetIobjRvalueRef() {return std::move(iobj_);}
};

int main(void){
    Outer a;
    a.iobj_.upInt_.reset(new int {5});

    Outer b;
    b.iobj_ = a.GetIobjRvalueRef();

    return 0;
}