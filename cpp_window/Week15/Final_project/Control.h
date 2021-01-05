

#ifndef FINAL_PROJECT_CONTROL_H
#define FINAL_PROJECT_CONTROL_H

#include "Data.h"
#include "Conv.h"
#include "InputLayer.h"
#include "ReLuLayer.h"
#include "PoolLayer.h"
#include "FullConnectLayer.h"
#include "Layer.h"
#include "MyException.h"

template <typename T>
class Control{
private:
    vector<Layer<T>*> processingQueue;
    Data<T> inputData;
    int processNum;
    T * result;
public:
    Control(int processNum);
    void setProcessingQueue(vector<Layer<T>*>);
    void startProcessing(string dataPath);
    T * getResult();
};

template <typename T>
Control<T>::Control(int processNum) {
    this->processNum=processNum;
}

template <typename T>
void Control<T>::setProcessingQueue(vector<Layer<T>*> processingQueue) {
    this->processingQueue=processingQueue;
}

template <typename T>
void Control<T>::startProcessing(string dataPath) {

    Data<T> currentData;
    InputLayer<float> input0(dataPath);
    currentData=input0.startPrograming();
    Layer<T> *currentProcessing;
    for(int i=0;i<this->processNum;i++){
        currentProcessing=this->processingQueue[i];
        switch (currentProcessing->type) {
            case (Layer<T>::LayerType::POOL): {
                PoolLayer<T> *currentPool = static_cast<PoolLayer<T> *>(currentProcessing);
                currentPool->setInputData(&currentData);
                currentData = currentPool->startPrograming();
                break;
            }
            case (Layer<T>::LayerType::CONV): {
                Conv<T> *currentConv = static_cast<Conv<T> *>(currentProcessing);
                currentConv->setInputData(&currentData);
                currentData = currentConv->startPrograming();
                break;
            }
            case Layer<T>::LayerType::RELU: {
                ReLuLayer<T> *currentRelu = static_cast<ReLuLayer<T> *>(currentProcessing);
                currentRelu->setInputData(&currentData);
                currentRelu->startPrograming1();
                break;
            }
            case Layer<T>::LayerType::FUCN: {
                FullConnectLayer<T> *currentFuC = static_cast<FullConnectLayer<T> *>(currentProcessing);
                currentProcessing->setInputData(&currentData);
                result = currentProcessing->startPrograming2();
                break;
            }
            default: {
                throw MyException("Unknown Type of Layer!");
            }
        }
    }



}

template <typename T>
T  * Control<T>::getResult() {
    return this->result;
}

#endif //FINAL_PROJECT_CONTROL_H
