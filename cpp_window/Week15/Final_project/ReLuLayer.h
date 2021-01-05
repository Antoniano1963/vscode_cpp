

#ifndef FINAL_PROJECT_RELULAYER_H
#define FINAL_PROJECT_RELULAYER_H

#include "Data.h"

template <typename T>
class ReLuLayer: public Layer<T>{
    Data<T> *inputData;
    void funcDRELU();
    void funcRELU();
public:
    enum ReLuType{
        RELU,DRELU
    };
    ReLuType reLuType;
    void startPrograming1();
    ReLuLayer(ReLuType reLuType);
    void setInputData(Data<T> *inputData);
};

template <typename T>
ReLuLayer<T>::ReLuLayer(ReLuType reLuType):Layer<T>(Layer<T>::RELU) {
    this->reLuType=reLuType;
}

template <typename T>
void ReLuLayer<T>::setInputData(Data<T> *inputData) {
    this->inputData=inputData;
}

template <typename T>
void ReLuLayer<T>::startPrograming1() {
    switch (reLuType) {
        case DRELU:
            funcDRELU();
            break;
        case RELU:
            funcRELU();
            break;
        default:
            throw MyException("Unknown Type of ReLuFunction!");
    }
}

template <typename T>
void ReLuLayer<T>::funcDRELU() {
    for(int p=0;p<inputData->getDim_x();p++){
        for(int t=0;t<inputData->getDim_y();t++){
            for(int i=0;i<inputData->getRow_num();i++){
                for(int j=0;j<inputData->getColumn_num();j++){
                    if(inputData->getDataFromPosition(p,t,i,j)<0){
                        inputData->setDataFromPosition(p,t,i,j,0);
                    }else{
                        inputData->setDataFromPosition(p,t,i,j,1);
                    }
                }
            }
        }
    }

}

template <typename T>
void ReLuLayer<T>::funcRELU() {
    for(int p=0;p<inputData->getDim_x();p++){
        for(int t=0;t<inputData->getDim_y();t++){
            for(int i=0;i<inputData->getRow_num();i++){
                for(int j=0;j<inputData->getColumn_num();j++){
                    if(inputData->getDataFromPosition(p,t,i,j)<0){
                        inputData->setDataFromPosition(p,t,i,j,0);
                    }
                }
            }
        }
    }
}

#endif //FINAL_PROJECT_RELULAYER_H
