#include <iostream>

template <typename T>
class MyVector {
private:
    T *data;
    size_t capacity;
    size_t length;

public:
    MyVector() : data(nullptr), capacity(0), length(0) {}

    MyVector(size_t len, const T& value) : data(nullptr), capacity(len), length(len) {
        data = new T[capacity];
        for (size_t i = 0; i < length; ++i) {
            data[i] = value;
        }
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[capacity];
            for (size_t i = 0; i < length; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[length++] = value;
    }

    void erase(size_t index) {
        if (index >= 0 && index < length) {
            for (size_t i = index; i < length - 1; ++i) {
                data[i] = data[i + 1];
            }
            --length;
        }
        else{
            throw std::out_of_range("Index out of range in erase");
        }
    }

    size_t size() const {
        return length;
    }

    T& operator[](size_t index) {
        if (index >= 0 && index < length) {
            return data[index];
        }
        throw std::out_of_range("Index out of range");
    }
};