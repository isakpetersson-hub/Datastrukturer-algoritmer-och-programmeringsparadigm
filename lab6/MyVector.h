// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:

    T* storage;
    unsigned capacity, numberOfElements;

};

template<typename T>
MyVector<T>::MyVector(){
    storage = new T[1];
    capacity = 1;
    numberOfElements = 0;
}

template<typename T>
MyVector<T>::~MyVector(){
    // TODO: replace the code below with your code for this member
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if (numberOfElements == capacity) {
        capacity *= 2;
        T* newStorage = new T[capacity];
        std::copy(storage, storage + numberOfElements, newStorage);

        delete[] storage;
        storage = newStorage;
    }
    storage[numberOfElements] = e;
    numberOfElements++;
}

template<typename T>
void MyVector<T>::pop_back(){
    numberOfElements--;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    // TODO: replace the code below with your code for this member
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    delete[] storage;
    storage = new T[1];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return &storage[0];
}

template<typename T>
T* MyVector<T>::end(){
    return &storage[0] + numberOfElements;
}

#endif // MY_VECTOR_H
