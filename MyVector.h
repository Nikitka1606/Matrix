#include <stdexcept>
template<typename T>
class MyVector{
private:
    size_t elementsCount;
    size_t capacity;
    T* currentContainer;
public:
    //MyVector() : currentContainer(nullptr), elementsCount(0) {};
    MyVector() : currentContainer(nullptr), capacity(0), elementsCount(0) {};
    void push_back(const T& value);
    void erase(size_t index);
    size_t size();
    T& operator[](size_t index);
    ~MyVector();
};
