#include <iostream>

template<bool debug>
void PrintT(const int &x){
    std::cout << x << std::endl;
}

extern template void PrintT<false>(const int &);
extern template void PrintT<true> (const int &);