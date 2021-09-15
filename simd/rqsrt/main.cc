#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <string>
<<<<<<< HEAD
#include <cmath>
=======
>>>>>>> 596fc6394454ab5125d7761506c9347a00834a87
#include <immintrin.h>

constexpr size_t ArraySize = 56*96;
constexpr size_t LoopSize = 10000;

alignas(32) float SrcArray[ArraySize];
alignas(32) float SqrtArray[ArraySize];
alignas(32) float RSqrtArray[ArraySize];

template<typename Func>
double TimeAndRun(const std::string &name, Func fun){
    auto begin = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < LoopSize; ++j){
        fun();
        // std::cout << j << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d = end - begin;
    auto ret = d.count();
    std::cout << name << ": " << ret << "s" <<std::endl;
    return ret;
}

void RSqrtKernel(void){
    __m256 a0, a1, a2, a3, a4, a5, a6;
    __m256 b0, b1, b2, b3, b4, b5, b6;
    __m256 const three_half = _mm256_set1_ps(1.5f);
    __m256 const half = _mm256_set1_ps(0.5f);

    float const *psrc = SrcArray;
    float *pdst = RSqrtArray;
    for (size_t i = 0; i < ArraySize; i+=56){
        a0 = _mm256_load_ps(psrc); 
        a1 = _mm256_load_ps(psrc+8);
        a2 = _mm256_load_ps(psrc+16);
        a3 = _mm256_load_ps(psrc+24);
        a4 = _mm256_load_ps(psrc+32);
        a5 = _mm256_load_ps(psrc+40);
        a6 = _mm256_load_ps(psrc+48);

        //b = 0.5x
        b0 = _mm256_mul_ps(a0, half);
        b1 = _mm256_mul_ps(a1, half);
        b2 = _mm256_mul_ps(a2, half);
        b3 = _mm256_mul_ps(a3, half);
        b4 = _mm256_mul_ps(a4, half);
        b5 = _mm256_mul_ps(a5, half);
        b6 = _mm256_mul_ps(a6, half);

        //a = 1/sqrt(x)
        a0 = _mm256_rsqrt_ps(a0);
        a1 = _mm256_rsqrt_ps(a1);
        a2 = _mm256_rsqrt_ps(a2);
        a3 = _mm256_rsqrt_ps(a3);
        a4 = _mm256_rsqrt_ps(a4);
        a5 = _mm256_rsqrt_ps(a5);
        a6 = _mm256_rsqrt_ps(a6);

        //b = 0.5xa
        b0 = _mm256_mul_ps(b0, a0);
        b1 = _mm256_mul_ps(b1, a1);
        b2 = _mm256_mul_ps(b2, a2);
        b3 = _mm256_mul_ps(b3, a3);
        b4 = _mm256_mul_ps(b4, a4);
        b5 = _mm256_mul_ps(b5, a5);
        b6 = _mm256_mul_ps(b6, a6);

        //b = 1.5 - 0.5xa^2
        b0 = _mm256_fnmadd_ps(b0, a0, three_half);
        b1 = _mm256_fnmadd_ps(b1, a1, three_half);
        b2 = _mm256_fnmadd_ps(b2, a2, three_half);
        b3 = _mm256_fnmadd_ps(b3, a3, three_half);
        b4 = _mm256_fnmadd_ps(b4, a4, three_half);
        b5 = _mm256_fnmadd_ps(b5, a5, three_half);
        b6 = _mm256_fnmadd_ps(b6, a6, three_half);

        //a' = a * (1.5 - 0.5*xa^2)
        a0 = _mm256_mul_ps(a0, b0);
        a1 = _mm256_mul_ps(a1, b1);
        a2 = _mm256_mul_ps(a2, b2);
        a3 = _mm256_mul_ps(a3, b3);
        a4 = _mm256_mul_ps(a4, b4);
        a5 = _mm256_mul_ps(a5, b5);
        a6 = _mm256_mul_ps(a6, b6);

        _mm256_stream_ps(pdst, a0);
        _mm256_stream_ps(pdst+8, a1);
        _mm256_stream_ps(pdst+16, a2);
        _mm256_stream_ps(pdst+24, a3);
        _mm256_stream_ps(pdst+32, a4);
        _mm256_stream_ps(pdst+40, a5);
        _mm256_stream_ps(pdst+48, a6);

        psrc += 56;
        pdst += 56;
    }
}

void SqrtKernel(void){
    __m256 a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;
    __m256 const ones = _mm256_set1_ps(1.0f);
    // std::cout << "enter sqrt kernel" << std::endl;

    float const *psrc = SrcArray;
    float *pdst = SqrtArray;
    for (size_t i = 0; i < ArraySize; i += 96){
        // std::cout << i << std::endl;
        a0 = _mm256_load_ps(psrc); 
        a1 = _mm256_load_ps(psrc+8);
        a2 = _mm256_load_ps(psrc+16);
        a3 = _mm256_load_ps(psrc+24);
        a4 = _mm256_load_ps(psrc+32);
        a5 = _mm256_load_ps(psrc+40);
        a6 = _mm256_load_ps(psrc+48);
        a7 = _mm256_load_ps(psrc+56);
        a8 = _mm256_load_ps(psrc+64);
        a9 = _mm256_load_ps(psrc+72);
        a10 = _mm256_load_ps(psrc+80);
        a11 = _mm256_load_ps(psrc+88);

        a0 = _mm256_sqrt_ps(a0);
        a1 = _mm256_sqrt_ps(a1);
        a2 = _mm256_sqrt_ps(a2);
        a3 = _mm256_sqrt_ps(a3);
        a4 = _mm256_sqrt_ps(a4);
        a5 = _mm256_sqrt_ps(a5);
        a6 = _mm256_sqrt_ps(a6);
        a7 = _mm256_sqrt_ps(a7);
        a8 = _mm256_sqrt_ps(a8);
        a9 = _mm256_sqrt_ps(a9);
        a10 = _mm256_sqrt_ps(a10);
        a11 = _mm256_sqrt_ps(a11);

        a0 = _mm256_div_ps(ones, a0);
        a1 = _mm256_div_ps(ones, a1);
        a2 = _mm256_div_ps(ones, a2);
        a3 = _mm256_div_ps(ones, a3);
        a4 = _mm256_div_ps(ones, a4);
        a5 = _mm256_div_ps(ones, a5);
        a6 = _mm256_div_ps(ones, a6);
        a7 = _mm256_div_ps(ones, a7);
        a8 = _mm256_div_ps(ones, a8);
        a9 = _mm256_div_ps(ones, a9);
        a10 = _mm256_div_ps(ones, a10);
        a11 = _mm256_div_ps(ones, a11);

        _mm256_stream_ps(pdst, a0);
        _mm256_stream_ps(pdst+8, a1);
        _mm256_stream_ps(pdst+16, a2);
        _mm256_stream_ps(pdst+24, a3);
        _mm256_stream_ps(pdst+32, a4);
        _mm256_stream_ps(pdst+40, a5);
        _mm256_stream_ps(pdst+48, a6);
        _mm256_stream_ps(pdst+56, a7);
        _mm256_stream_ps(pdst+64, a8);
        _mm256_stream_ps(pdst+72, a9);
        _mm256_stream_ps(pdst+80, a10);
        _mm256_stream_ps(pdst+88, a11);

        psrc += 96;
        pdst += 96;
    }
}

int main(void){
    std::default_random_engine e;
    std::uniform_real_distribution<float> dist(0.0001f, 1.0f);
    for (size_t i = 0; i < ArraySize; ++i){
        SrcArray[i] = dist(e);
    }

    TimeAndRun("Naive", SqrtKernel);
    TimeAndRun("Quake", RSqrtKernel);

    float max_diff = -0.0f;
    size_t max_idx = ArraySize + 1;
    for (size_t k = 0; k < ArraySize; ++k){
        float this_diff = std::fabs(RSqrtArray[k] - SqrtArray[k]);
        if (this_diff > max_diff){
            max_diff = this_diff;
            max_idx = k;
        }
    }

    std::cout << "MaxIdx: " << max_idx << ", MaxDiff: " << max_diff << "\n";
    std::cout << "Src[" << max_idx << "]: " << SrcArray[max_idx] << "\n";
    std::cout << "Rsqrt[" << max_idx << "]: " << RSqrtArray[max_idx] << "\n";
    std::cout << "Sqrt[" << max_idx << "]: " << SqrtArray[max_idx] << "\n";
 
    return 0;
}