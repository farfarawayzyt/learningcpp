#include <utility>
#include <functional>
#include <unordered_map>

class Foo{
friend std::hash<Foo>;
private:
    int x_;

};

namespace std{
template<>
struct hash<Foo>
{   
    size_t operator()(const Foo &obj) const {
        return std::hash<int>()(obj.x_); 
    }
};

}

int main(void){
    std::unordered_map<Foo, int> m;
    
    
    return 0;
}