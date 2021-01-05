#include <iostream>
#include "Data.h"
#include "Conv.h"
#include "ReLuLayer.h"
#include "PoolLayer.h"
#include "FullConnectLayer.h"
#include "cmath"
#include "face_binary_cls.h"
#include "Control.h"
int main() {

    Data<float> conv_wei0(conv0_weight,16,3,3,3);
    Data<float> conv_wei1(conv1_weight,32,16,3,3);
    Data<float> conv_wei2(conv2_weight,32,32,3,3);

    Conv<float> conv1(3,16,3,2,1);
    conv1.setFilter(&conv_wei0);
    conv1.setBais(conv0_bias);
    ReLuLayer<float> *reLuLayer0=new ReLuLayer<float>(ReLuLayer<float>::RELU);
    PoolLayer<float> poolLayer0(PoolLayer<float>::MAX,2,2);
    Conv<float> conv2(16,32,3,1,0);
    conv2.setFilter(&conv_wei1);
    conv2.setBais(conv1_bias);
    ReLuLayer<float> *reLuLayer1=new ReLuLayer<float>(ReLuLayer<float>::RELU);
    PoolLayer<float> poolLayer1(PoolLayer<float>::MAX,2,2);
    Conv<float> conv3(32,32,3,2,1);
    conv3.setFilter(&conv_wei2);
    conv3.setBais(conv2_bias);
    ReLuLayer<float> *reLuLayer2=new ReLuLayer<float>(ReLuLayer<float>::RELU);
    FullConnectLayer<float> fullConnectLayer0(2,2048);
    fullConnectLayer0.setWeights(fc0_weight);
    fullConnectLayer0.setBais(fc0_bias);

    vector<Layer<float>*> processQueue={static_cast<Layer<float>*>(&conv1),static_cast<Layer<float>*>(reLuLayer0),static_cast<Layer<float>*>(&poolLayer0),static_cast<Layer<float>*>(&conv2),static_cast<Layer<float>*>(reLuLayer1),static_cast<Layer<float>*>(&poolLayer1),static_cast<Layer<float>*>(&conv3),static_cast<Layer<float>*>(reLuLayer2),static_cast<Layer<float>*>(&fullConnectLayer0)};

    Control<float> model1(9);
    model1.setProcessingQueue(processQueue);

    float *result;
    try{
        model1.startProcessing("C:\\cpp\\Clion\\Final_project\\samples\\bg01.jpg");
    } catch (MyException e) {
        cout<<e.wrong<<endl;

    }
    result=model1.getResult();
    cout << "source from: " << "C:\\cpp\\Clion\\Final_project\\samples\\bg01.jpg" << endl;
    printf("bg score: %6f, face score: %6f.",exp(result[0])/(exp(result[0])+exp(result[1])),exp(result[1])/(exp(result[0])+exp(result[1])));
    cout<<endl;

    try{
        model1.startProcessing("C:\\cpp\\Clion\\Final_project\\samples\\face.jpg");
    } catch (MyException e) {
        cout<<e.wrong<<endl;

    }
    result=model1.getResult();
    cout << "source from: " << "C:\\cpp\\Clion\\Final_project\\samples\\face.jpg" << endl;
    printf("bg score: %6f, face score: %6f.",exp(result[0])/(exp(result[0])+exp(result[1])),exp(result[1])/(exp(result[0])+exp(result[1])));
    cout<<endl;

    try{
        model1.startProcessing("C:\\cpp\\Clion\\Final_project\\samples\\bg.jpg");
    } catch (MyException e) {
        cout<<e.wrong<<endl;

    }
    result=model1.getResult();
    cout << "source from: " << "C:\\cpp\\Clion\\Final_project\\samples\\bg.jpg" << endl;
    printf("bg score: %6f, face score: %6f.",exp(result[0])/(exp(result[0])+exp(result[1])),exp(result[1])/(exp(result[0])+exp(result[1])));
    cout<<endl;

    try{
        model1.startProcessing("C:\\cpp\\Clion\\Final_project\\samples\\face_woman00.jpg");
    } catch (MyException e) {
        cout<<e.wrong<<endl;

    }
    result=model1.getResult();
    cout << "source from: " << "C:\\cpp\\Clion\\Final_project\\samples\\face_woman00.jpg" << endl;
    printf("bg score: %6f, face score: %6f.",exp(result[0])/(exp(result[0])+exp(result[1])),exp(result[1])/(exp(result[0])+exp(result[1])));
    cout<<endl;

}
