

#ifndef FINAL_PROJECT_POOLLAYER_H
#define FINAL_PROJECT_POOLLAYER_H

#include "Data.h"

template <typename T>
class PoolLayer: public Layer<T>{
private:
    int size;
    int stride;
    Data<T> *inputData;
    T maxPool(int currentChannel, int currentRow, int currentColumn);
    T avlPool(int currentChannel, int currentRow, int currentColumn);
    T minPool(int currentChannel, int currentRow, int currentColumn);
public:
    enum Type
    {
        MAX, MIN, AVE
    };
    Type type;
    PoolLayer(Type type, int size, int stride);
    void setInputData(Data<T> *inputData);
    Data<T> startPrograming();
};

template <typename T>
PoolLayer<T>::PoolLayer(Type type, int size, int stride): Layer<T>(Layer<T>::POOL) {
    this->type=type;
    this->size=size;
    this->stride=stride;
}

template <typename T>
void PoolLayer<T>::setInputData(Data<T> *inputData) {
    this->inputData=inputData;
}

template <typename T>
Data<T> PoolLayer<T>::startPrograming() {
    int outSizeR=(inputData->getRow_num()-size)/this->stride+1;
    int outSizeC=(inputData->getColumn_num()-size)/this->stride+1;
    Data<T> outData(inputData->getDim_x(),inputData->getDim_y(),outSizeR,outSizeC);
    switch (type) {


        case MAX:
            for (int t = 0; t < inputData->getDim_y(); t++) {
                for (int i = 0; i < inputData->getRow_num(); i += size) {
                    for (int j = 0; j < inputData->getRow_num(); j += size) {
                        T currentNum = maxPool(t, i, j);
                        outData.setDataFromPosition(0, t, i / size, j / size, currentNum);
                    }
                }
            }
            break;
        case AVE:
            for (int t = 0; t < inputData->getDim_y(); t++) {
                for (int i = 0; i < inputData->getRow_num(); i += size) {
                    for (int j = 0; j < inputData->getRow_num(); j += size) {
                        T currentNum = avlPool(t, i, j);
                        outData.setDataFromPosition(0, t, i / size, j / size, currentNum);
                    }
                }
            }
            break;
        case MIN:
            for (int t = 0; t < inputData->getDim_y(); t++) {
                for (int i = 0; i < inputData->getRow_num(); i += size) {
                    for (int j = 0; j < inputData->getRow_num(); j += size) {
                        T currentNum = minPool(t, i, j);
                        outData.setDataFromPosition(0, t, i / size, j / size, currentNum);
                    }
                }
            }
            break;
        default:
            throw MyException("Unknown Type of PoolFunction!");
    }
    return outData;
}

template <typename T>
T PoolLayer<T>::maxPool(int currentCannel, int currentRow, int currentColumn) {
    T result=-1;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(inputData->getDataFromPosition(0,currentCannel,currentRow+i,currentColumn+j)>result){
                result=inputData->getDataFromPosition(0,currentCannel,currentRow+i,currentColumn+j);
            }
        }
    }
    return result;
}

template <typename T>
T PoolLayer<T>::avlPool(int currentCannel, int currentRow, int currentColumn) {
    T result=0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(inputData->getDataFromPosition(0,currentCannel,currentRow+i,currentColumn+j)>result){
                result+=inputData->getDataFromPosition(0,currentCannel,currentRow+i,currentColumn+j);
            }
        }
    }
    return result/(size*size);
}

template <typename T>
T PoolLayer<T>::minPool(int currentCannel, int currentRow, int currentColumn) {
    T result=1;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(inputData->getDataFromPosition(0,currentCannel,currentRow+i,currentColumn+j)<result){
                result=inputData->getDataFromPosition(0,currentCannel,currentRow+i,currentColumn+j);
            }
        }
    }
    return result;
}



#endif //FINAL_PROJECT_POOLLAYER_H
