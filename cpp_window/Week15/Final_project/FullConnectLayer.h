//
// Created by Antoniano on 2021/1/4.
//

#ifndef FINAL_PROJECT_FULLCONNECTLAYER_H
#define FINAL_PROJECT_FULLCONNECTLAYER_H

#include "Data.h"

template <typename T>
class FullConnectLayer: public Layer<T>{
private:
    Data<T> * inputData;
    T * Weights;
    T * Bais;
    int channels;
    int size;
    T getCurrentChannelResult(int currentChannel);
public:
    FullConnectLayer(int channels,int size);
    void setInputData(Data<T> * inputData);
    void setWeights(T * Weights);
    void setBais(T *bias);
    T * startPrograming2();
};

template <typename T>
FullConnectLayer<T>::FullConnectLayer(int channels,int size):Layer<T>(Layer<T>::FUCN) {
    this->size=size;
    this->channels=channels;
}

template <typename T>
void FullConnectLayer<T>::setInputData(Data<T> *inputData) {
    this->inputData=inputData;
}

template <typename T>
void FullConnectLayer<T>::setWeights(T *Weights) {
    this->Weights=Weights;
}

template <typename T>
void FullConnectLayer<T>::setBais(T *bias) {
    this->Bais=bias;
}

template <typename T>
T * FullConnectLayer<T>::startPrograming2() {
    T * outData=new T[channels];
    for(int i=0;i<channels;i++){
        outData[i]=getCurrentChannelResult(i);
    }
    return outData;

}

template <typename T>
T FullConnectLayer<T>::getCurrentChannelResult(int currentChannel) {
    int index=currentChannel*size;
    T result=0;
    for(int p=0;p<inputData->getDim_x();p++){
        for(int t=0;t<inputData->getDim_y();t++){
            for(int i=0;i<inputData->getRow_num();i++){
                for(int j=0;j<inputData->getColumn_num();j++){
                    result+=inputData->getDataFromPosition(p,t,i,j)*this->Weights[index];
                    index++;
                }
            }
        }
    }
    result+=Bais[currentChannel];
    return result;
}

#endif //FINAL_PROJECT_FULLCONNECTLAYER_H
