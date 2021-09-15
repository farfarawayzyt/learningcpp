#include "./t.h"


template void PrintT<false>(const int &x);
template void PrintT<true>  (const int &x);