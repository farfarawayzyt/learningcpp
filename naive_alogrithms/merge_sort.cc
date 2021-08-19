#include "../utils.h"

using namespace std;

void _mergeSortMerge(vector<int> &A, size_t begin, size_t mid, size_t end){
    vector<int> buf(end-begin);
    size_t x = begin, y = mid, offset = 0;
    while (x < mid || y < end){
        int add;
        if (x == mid){
            add = A[y++];
        } else if (y == end){
            add = A[x++];
        } else if (A[x] <= A[y]){
            add = A[x++];
        } else {
            add = A[y++];
        }
        buf[offset++] = add;
    }
    for (size_t i = 0; i < end-begin; ++i){
        A[i+begin] = buf[i];
    }
}

void _mergeSortImpl(vector<int> &A, size_t begin, size_t end){
    if (begin + 1 >= end)
        return;
    size_t mid = (begin + end) / 2;
    _mergeSortImpl(A, begin, mid);
    _mergeSortImpl(A, mid, end);
    _mergeSortMerge(A, begin, mid, end);
}

void MergeSort1(vector<int> &A){
    _mergeSortImpl(A, 0, A.size());
}

// template<typename T>
// struct TinySpan{
//     using iteratorT = vector<int>::iterator;
//     iteratorT it;
//     size_t size;

//     TinySpan(vector<T>::iterator const &_it, size_t _size):it(_it), size(_size){}
//     T &operator[](size_t index) {return *(it+index);}
//     iteratorT begin() const {return it;}
//     iteratorT end() const {return it+size;}
// };

// void SpanMerge(TinySpan<int> const &lhs, TinySpan<int> const &rhs){
//     size_t sizeTotal = lhs.size + rhs.size, offset = 0;
//     vector<int> buf(sizeTotal);
//     TinySpan<int> bufSpan(buf.begin(), buf.size());
//     auto x = lhs.begin(), y = rhs.begin();
//     while (x != lhs.end() || y = )
// }

// void SpanMergeSort(TinySpan<int> const &span){
//     if (span.size <= 1){
//         return;
//     }

//     size_t sizeL = span.size / 2;
//     auto mid = span.it + sizeL;
//     SpanMergeSort({span.it, sizeL});
//     SpanMergeSort({mid, span.size - sizeL});

// }

int main(void){
    vector<int> A{1, 8, 0, 5, 2, 3, 7, 6, 4, 9};
    MergeSort1(A);

    return 0;
}