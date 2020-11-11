#include<iostream>
#include<string>
#include<ctime>
#include<algorithm>
#include<thread>
#include<numeric>
#include<vector>
#include<functional>
void dot_product(const std::vector &v1, const std::vector &v2, int &result, 
int L, int R){
    for(int i = L; i < R; ++i){
        result += v1[i] * v2[i];
    }
}

int main(){
    int nr_elements = 100000;
    int nr_threads = 2;
    int result = 0;
    std::vector threads;

    //Fill two vectors with some constant values for a quick verification 
    // v1={1,1,1,1,...,1}以常量值填充两个向量，便于检验
    // v2={2,2,2,2,...,2}    
    // The result of the dot_product should be 200000 for this particular case
   //当前例子的点乘结果应为200000
    std::vector v1(nr_elements,1), v2(nr_elements,2);

    //Split nr_elements into nr_threads parts 把nr_elements份计算任务划分为 nr_threads 个部分
    std::vector limits = bounds(nr_threads, nr_elements);

    //Launch nr_threads threads: 启动 nr_threads 条线程
    for (int i = 0; i < nr_threads; ++i) {
        threads.push_back(std::thread(dot_product, std::ref(v1), std::ref(v2), 
std::ref(result), limits[i], limits[i+1]));
    }


    //Join the threads with the main thread 协同 线程组与主线程
    for(auto &t : threads){
        t.join();
    }

    //Print the result打印结果
    std::cout<<result<<std::endl;
 
    return 0;
}