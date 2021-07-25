#include <iostream>

using std::cout;
using std::endl;

class A{
private:
    int &x_;
public:
    A(int &x):x_(x){}
    explicit A(A &&other):x_(other.x_){}
    void printX(std::ostream &os){
        os << x_;
    }
};

int main(void){
    int x = 1;

    A m(x);
    m.printX(cout);
    cout << endl;

    A n(std::move(m));
    ++x;
    n.printX(cout);
    cout << endl;

    return 0;
}