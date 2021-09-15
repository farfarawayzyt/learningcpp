#include <iostream>
#include <fstream>

class Foo{
private:
    int x = 1;
    std::ofstream ofs_{"histograms.txt"};
public:
    void WriteX(){
        ofs_ << x << "\n";
    }

    ~Foo(){
        ofs_.close();
    }
};

int main(){
    Foo obj;
    obj.WriteX();

    return 0;
}