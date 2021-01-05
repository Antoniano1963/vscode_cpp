
#ifndef FINAL_PROJECT_CONV_H
#define FINAL_PROJECT_CONV_H

#include "Data.h"
#include "Layer.h"
#include "MyException.h"
template <typename T>
class Conv:public Layer<T>{
private:
    int in_channels;
    int out_channels;
    int kernel_size;
    int stride;
    int padding;
    Data<T> *inputData;
    Data<T> *Filter;
    T *bais;
public:
    Conv(int in_channels,int out_channels,int kernel_size,int stride, int padding);
    void setInputData(Data<T> *inputData);
    void setFilter(Data<T> *Filter);
    void setBais(T *bais);
    Data<T> startPrograming();
    T getConvNum(int currentChannel, int currentRowNum, int currentColumnNum);
    int getPadding();


};

template <typename T>
Conv<T>::Conv(int in_channels, int out_channels, int kernel_size, int stride, int padding):Layer<T>(Layer<T>::CONV) {
    this->in_channels=in_channels;
    this->out_channels=out_channels;
    this->kernel_size=kernel_size;
    this->stride=stride;
    this->padding=padding;
}

template <typename T>
void Conv<T>::setBais(T *bais) {
    this->bais=bais;
}

template <typename T>
void Conv<T>::setInputData(Data<T> *inputData) {
    this->inputData=inputData;

}

template <typename T>
void Conv<T>::setFilter(Data<T> *Filter) {
    this->Filter=Filter;
}

template <typename T>
Data<T> Conv<T>::startPrograming() {
    inputData->setPadding(this->padding);
    int outSizeR=(inputData->getRow_num()-kernel_size)/this->stride+1;
    int outSizeC=(inputData->getColumn_num()-Filter->getRow_num())/this->stride+1;
    if(Filter->getDim_x()!=out_channels){
        throw MyException("The channel of Filter is not equals to out_channels");
    }
    if(Filter->getDim_y()!=inputData->getDim_y()){
        throw MyException("The Y channel of Filter is not equals to Y channel of inputData");
    }
    if(Filter->getRow_num()!=this->kernel_size||Filter->getColumn_num()!=this->kernel_size){
        throw MyException("The Filter size is not equal to the kernel_size");
    }
    if(inputData->getDim_y()!=in_channels){
        throw MyException("The channel of inputData is not equals to the in_channel");
    }
    Data<T> outData(1,this->out_channels,outSizeR,outSizeC);
    for(int i=0;i<this->out_channels;i++){
        for(int j=this->kernel_size/2;j<inputData->getRow_num()-kernel_size/2;j+=stride){
            for(int k=this->kernel_size/2;k<inputData->getColumn_num()-kernel_size/2;k+=stride ){
                T currentResult=getConvNum(i,j,k);
                outData.setDataFromPosition(0,i,(j-kernel_size/2)/stride,(k-kernel_size/2)/stride,currentResult);
            }
        }
    }
    return outData;
}

template <typename T>
T Conv<T>::getConvNum(int currentChannel, int currentRowNum, int currentColumnNum) {
    T result=0;
    for(int i=0;i<this->in_channels;i++){
        for(int j=-1;j<2;j++){
            for(int k=-1;k<2;k++){
                T num1 = inputData->getDataFromPosition(0, i, currentRowNum + j, currentColumnNum + k);
                T num2 = Filter->getDataFromPosition(currentChannel, i, kernel_size/2 + j, kernel_size/2 + k);
                result += num1 * num2;
            }
        }
    }
    result+=this->bais[currentChannel];
    return result;
}

template <typename T>
int Conv<T>::getPadding() {
    return this->padding;
}


#endif //FINAL_PROJECT_CONV_H
