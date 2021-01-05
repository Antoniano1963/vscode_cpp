#pragma once

#ifndef FINAL_PROJECT_LAYER_H
#define FINAL_PROJECT_LAYER_H

#include "Data.h"

template <typename T>
class Layer{
public:
    enum LayerType
    {
        POOL, CONV, RELU, FUCN, UNKNOW
    };
    LayerType type;
    Layer(LayerType type);

    LayerType getType(){return this->type;};
    virtual void startPrograming1(){return;};
    virtual Data<T> startPrograming(){
        return Data<T>(1,1,1,1);
    };
    virtual void setInputData(Data<T> * inputData){return;};
    virtual T * startPrograming2(){
        return new T (0);
    };

};

#endif //FINAL_PROJECT_LAYER_H

template<typename T>
Layer<T>::Layer(LayerType type){
    this->type=type;
}

