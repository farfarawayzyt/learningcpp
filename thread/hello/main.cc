#include <thread>
#include <iostream>

void SayHello(){
    std::cout << "Hello Multithreadings!" << std::endl;
}

int main(void){
    std::thread t(SayHello);
    t.join();
    return 0;
}