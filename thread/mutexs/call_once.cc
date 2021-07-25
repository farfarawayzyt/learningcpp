#include <mutex>
#include <iostream>
#include <memory>

using namespace std;

shared_ptr<int> res = nullptr;

mutex m;
void InitProtectedByMutex(){
    unique_lock<mutex> guard(m);
    res = make_shared<int>(5);
    cout << "res with value: " << *res << " initialized by protection of mutex!" << endl;
    guard.unlock();
}

once_flag res_flag;
void InitProtectedByCallOnce(){
    call_once(res_flag, [&]{res.reset(new int{4});});
}

int main(void){
    InitProtectedByMutex();
    res.reset();

    InitProtectedByCallOnce();
    cout << "res with value: " << *res << " initialized by protection of mutex!" << endl;
    res.reset();

    return 0;
}