#include <future>
#include <thread>
#include <chrono>
#include <iostream>

using std::cout;
using std::endl;


int main(void){
    std::future<int> the_answer = std::async([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        return 42;
    });

    cout << "we got future" << endl;
    cout << "now we wait" << endl;

    cout << "the answer is " << the_answer.get() << endl;

    return 0;
}