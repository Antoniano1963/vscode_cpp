#include <iostream>
#include <chrono>
#include "matoperation.hpp"
using namespace std;

int main(int argc, char ** argv)
{
    size_t nSize = 200000000;
    float * p1 = new float[nSize]();
    float * p2 = new float[nSize]();
    float result = 0.0f;

    p1[2] = 2.3f;
    p2[2] = 3.0f;
    p1[nSize-1] = 2.0f;
    p2[nSize-1] = 1.1f;

    auto start = std::chrono::steady_clock::now();
    result = dotproduct1(p1, p2, nSize);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "dotproduct1 1 result = " << result
         << ", duration = " << duration << std::endl;

    start = std::chrono::steady_clock::now();
    result = dotproduct1(p1, p2, nSize);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "dotproduct1 2 result = " << result
         << ", duration = " << duration << std::endl;


    start = std::chrono::steady_clock::now();
    result = dotproduct2(p1, p2, nSize);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "dotproduct2 result = " << result
         << ", duration = " << duration << std::endl;


    start = std::chrono::steady_clock::now();
    result = dotproduct3(p1, p2, nSize);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "dotproduct3 result = " << result
         << ", duration = " << duration << std::endl;

    start = std::chrono::steady_clock::now();
    result = dotproduct4(p1, p2, nSize);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "dotproduct4 result = " << result
         << ", duration = " << duration << std::endl;

    delete []p1;
    delete []p2;

    return 0;
}