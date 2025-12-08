// isape817 rasda103

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <algorithm>


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

  unsigned size() const;

private:
    void siftUp(unsigned index);
    void siftDown(unsigned index);
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue() : vector_array(), strictly_larger_operator() {
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    siftUp(size() - 1);
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    if (size() > 0)
        return vector_array[0];
    else
        return 0;
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    std::swap(vector_array[0], vector_array[vector_array.size() - 1]);
    vector_array.pop_back();

    if (!empty()) {
        siftDown(0);
    }
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::siftUp(unsigned index) {
    while (index > 0) {
        unsigned parent = (index - 1) / 2;

        if (!strictly_larger_operator(vector_array[parent], vector_array[index])) {
            // Parent has higher priority than child
            break;
        }

        std::swap(vector_array[parent], vector_array[index]); // Move it updwards
        index = parent;
    }
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::siftDown(unsigned index) {
    unsigned arraySize = size();

    while (true) {
        unsigned left = index * 2 + 1;
        unsigned right = index * 2 + 2;
        unsigned smallest = index;

        if (left < arraySize && strictly_larger_operator(vector_array[smallest], vector_array[left])) {
            smallest = left;
        }
        if (right < arraySize && strictly_larger_operator(vector_array[smallest], vector_array[right])) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }

        std::swap(vector_array[index], vector_array[smallest]);
        index = smallest;
    }
}


template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
