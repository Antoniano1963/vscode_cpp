//
// Created by Antoniano on 2021/1/3.
//

#ifndef FINAL_PROJECT_INPUTLAYER_H
#define FINAL_PROJECT_INPUTLAYER_H
#include <opencv2/opencv.hpp>
#include<string>
#include "Data.h"
using namespace std;

template <typename T>
class InputLayer{
private:
    cv::Mat img;
    string path;
public:
    InputLayer(string path);
    Data<T> startPrograming();
};

template <typename T>
InputLayer<T>::InputLayer(string path) {
    this->path=path;
}

template <typename T>
Data<T> InputLayer<T>::startPrograming() {
    this->img=cv::imread(this->path, cv::ImreadModes::IMREAD_COLOR);
    int currentChannel=img.channels();
    int currentRow=img.rows;
    int currentCol=img.cols;
    Data<T> outData(1,currentChannel,currentRow,currentCol);
    for(int t=0;t<currentChannel;t++){
        for(int i=0;i<currentRow;i++){
            for(int j=0;j<currentCol;j++){
                T currentData=img.at<cv::Vec3b>(i,j)[t]/float(255);
                outData.setDataFromPosition(0,2-t,i,j,currentData);
            }
        }
    }
    return outData;

}


#endif //FINAL_PROJECT_INPUTLAYER_H
