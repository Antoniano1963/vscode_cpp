#pragma once
#ifndef FINAL_PROJECT_DATA_H
#define FINAL_PROJECT_DATA_H

#include<iostream>
#include <atomic>
#include<mutex>
#include<string>
using namespace std;

template <typename T>
class Data {
private:
    mutex *mu;
    int Dim_x,Dim_y;
    int row_num, column_num;
    long size;
    T *matrixdata;
    int *refcount;
    int padding;
public:
    Data(T *data,int Dim_x=1,int Dim_y=1,int row_num=1,int column_num=1);
    Data(int Dim_x=1,int Dim_y=1,int row_num=1,int column_num=1);
    Data(const Data &rhs);
    ~Data();
    Data &operator=(const Data &rhs);
    void Display();
    T getDataFromPosition(int Dim_x,int Dim_y,int row_num, int column_num);
    int getRow_num();
    int getColumn_num();
    int getDim_x();
    int getDim_y();
    int getPadding();
    void setPadding(int padding);
    void setDataFromPosition(int Dim_x,int Dim_y,int row_num, int column_num,T value);
    void addDataFromPosition(int Dim_x,int Dim_y,int row_num, int column_num,T value);
    long getSize();

};


template <typename T>
Data<T>::Data(T *data, int Dim_x, int Dim_y, int row_num, int column_num) {
    this->size = row_num * column_num * Dim_x * Dim_y;
    this->column_num = column_num;
    this->row_num = row_num;
    this->Dim_x=Dim_x;
    this->Dim_y=Dim_y;
    this->matrixdata=data;
    this->padding=0;
    this->mu = new mutex();
    if (this->size > 0) {
        this->refcount = new int(2);
    }
    else {
        this->matrixdata = NULL;
        cout << "The number you input is wrong";
    }
}

template <typename T>
Data<T>::Data(int Dim_x, int Dim_y, int row_num, int column_num) {
    this->size = row_num * column_num * Dim_x * Dim_y;
    this->column_num = column_num;
    this->row_num = row_num;
    this->Dim_x=Dim_x;
    this->Dim_y=Dim_y;
    this->padding=0;
    this->mu = new mutex();
    if (this->size > 0) {
        this->matrixdata=new T[this->size];
        for(int i=0;i<this->size;i++){
            this->matrixdata[i]=0;
        }
        this->refcount = new int(2);
    }
    else {
        this->matrixdata = NULL;
        cout << "The number you input is wrong";
    }
}

template <typename T>
Data<T>::Data(const Data<T> &rhs) {
    this->matrixdata = rhs.matrixdata;
    this->column_num = rhs.column_num;
    this->row_num = rhs.row_num;
    this->Dim_y=rhs.Dim_y;
    this->Dim_x=rhs.Dim_x;
    this->size = rhs.size;
    this->mu = rhs.mu;
    this->padding=rhs.padding;
    (*mu).lock();
    this->refcount = rhs.refcount;
    *(this->refcount)=(*this->refcount)+1;
    (*mu).unlock();
}
template <typename T>
Data<T>::~Data(){
    (*mu).lock();
    if (*(this->refcount) < 2) {
        delete[] this->matrixdata;
        delete this->refcount;
    }
    else {
        (*this->refcount)=(*this->refcount)-1;
    }
    (*mu).unlock();
}

template <typename T>
Data<T> &Data<T> ::operator=(const Data &rhs){
    if (this != &rhs) {
        this->column_num = rhs.column_num;
        this->row_num = rhs.row_num;
        this->Dim_x=rhs.Dim_x;
        this->Dim_y=rhs.Dim_y;
        this->matrixdata = rhs.matrixdata;
        this->mu = rhs.mu;
        this->padding=rhs.padding;
        (*mu).lock();
        this->refcount = rhs.refcount;
        (*this->refcount)++;
        (*mu).unlock();
    }
    return *this;
}


template <typename T>
ostream &operator<< (ostream &os, Data<T> &rhs){
    cout<<"Dim_x = "<<rhs.Dim_x<<"  Dim_y = "<<rhs.Dim_y<<endl;
    cout<<"row_num = "<<rhs.row_num<<"  column_num = "<<rhs.column_num;
    for(int i=0;i<rhs.Dim_x;i++){
        cout<<"Dim_x : "<<i<<endl;
        for(int j=0;j<rhs.Dim_y;j++){
            cout<<"Dim_y : "<<j<<endl;
            for(int k=0;k<rhs.getRow_num();k++){
                os << "| ";
                for(int p=0;p<rhs.getColumn_num();p++){
                    os << rhs.getDataFromPosition(i,j,k,p)<<' ';
                }
            }
            os<<"|"<<endl;
        }
    }
    return os;
}

template <typename T>
T Data<T>::getDataFromPosition(int Dim_x, int Dim_y, int row_num, int column_num) {
    if(row_num<this->padding||row_num>=(this->row_num+this->padding)||column_num<this->padding||column_num>=(this->column_num+this->padding)){
        return 0;
    }
    return this->matrixdata[Dim_x*this->Dim_y*this->row_num*this->column_num+Dim_y*this->row_num*this->column_num+(row_num-padding)*this->column_num+(column_num-padding)];
}

template <typename T>
int Data<T>::getRow_num() {
    int num= this->row_num+this->padding*2;
    return num;
}

template <typename T>
int Data<T>::getColumn_num() {
    int num =this->column_num+this->padding*2;
    return num;
}

template <typename T>
void Data<T>::setPadding(int padding) {
    this->padding=padding;
}

template <typename T>
int Data<T>::getDim_x() {
    return this->Dim_x;
}
template <typename T>
int Data<T>::getDim_y() {
    return this->Dim_y;
}

template <typename T>
int Data<T>::getPadding() {
    return this->padding;
}

template <typename T>
void Data<T>::Display() {
    for(int i=0;i<this->getDim_x();i++){
        cout<<"Dim_x : "<<i<<endl;
        //cout<<endl;
        for(int j=0;j<this->getDim_y();j++){
            cout<<"Dim_y : "<<j<<endl;
            //cout<<endl;
            for(int k=0;k<this->getRow_num();k++){
                cout << "| ";
                for(int p=0;p<this->getColumn_num();p++){
                    cout << this->getDataFromPosition(i,j,k,p)<<' ';
                }
                cout<<"|"<<endl;
                //cout<<endl;
            }
        }
    }
}

template <typename T>
void Data<T>::addDataFromPosition(int Dim_x, int Dim_y, int row_num, int column_num, T value) {
    if(row_num<this->padding||row_num>this->row_num||column_num<this->padding||column_num>this->column_num){
        cout<<"Wrong"<<endl;
        return ;
    }
    this->matrixdata[Dim_x*this->Dim_y*this->row_num*this->column_num+Dim_y*this->row_num*this->column_num+(row_num-padding)*this->column_num+(column_num-padding)]+=value;
}

template <typename T>
void Data<T>::setDataFromPosition(int Dim_x, int Dim_y, int row_num, int column_num, T value) {
    if(row_num<this->padding||row_num>this->row_num||column_num<this->padding||column_num>this->column_num){
        cout<<"Wrong"<<endl;
        return ;
    }
    this->matrixdata[Dim_x*this->Dim_y*this->row_num*this->column_num+Dim_y*this->row_num*this->column_num+(row_num-padding)*this->column_num+(column_num-padding)]=value;
}


#endif //FINAL_PROJECT_DATA_H
