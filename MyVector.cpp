#include "MyVector.h"

template<typename T>
void  MyVector<T>::push_back(const T &value) {
    if (elementsCount == capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < elementsCount; ++i) {
            newData[i] = currentContainer[i];
        }
        delete[] currentContainer;
        currentContainer = newData;
        newData = nullptr;
    }
    elementsCount++;
    currentContainer[elementsCount] = value;
}

template<typename T>
void MyVector<T>::erase(size_t index) {
    if (index >= elementsCount){
        throw std::out_of_range("Index out of range");
    }

    for (int i = 0; i < elementsCount - 1; i++){
        currentContainer[i] = currentContainer[i + 1];
    }
    elementsCount--;
}

template<typename T>
size_t MyVector<T>::size(){
    return elementsCount;
}

template<typename T>
T& MyVector<T>::operator[](size_t index){
    if (index >= elementsCount){
        throw std::out_of_range("Index out of range");
    }
    return currentContainer[index];
}

template<typename T>
MyVector<T>::~MyVector(){
    if (currentContainer) delete[] currentContainer;
}
