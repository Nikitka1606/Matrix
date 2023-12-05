#include <iostream>

template <typename T>
class List {
public:
    virtual ~List() {}
    virtual void push_back(const T& value) = 0;
    virtual void insert(size_t pos, const T& value) = 0;
    virtual void erase(size_t pos) = 0;
    virtual size_t size() const = 0;
};
