#include "List.h"

template <typename T>
struct Link {
    T data;
    Link *next;
    Link(const T& value): data(value), next(nullptr) {}
};

template <typename T>
class LinkedList: public List<T>{
private:
    Link<T>* start;
public:
    LinkedList(): start(nullptr){}
    ~LinkedList(){
        clear();
    }

    T& operator[](size_t index) {
        if (index < size()) {
            Link<T>* cur = start;
            for (size_t i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return cur->data;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    const T& operator[](size_t index) const {
        if (index < size()) {
            Link<T>* cur = start;
            for (size_t i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return cur->data;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    void push_back(const T& value) override {
        Link<T>* newLink = new Link<T>(value);
        if (!start) {
            start = newLink;
        } else {
            Link<T>* cur = start;
            while (cur->next) {
                cur = cur->next;
            }
            cur->next = newLink;
        }
    }

    void insert(size_t pos, const T& value) override {
        if (pos == 0) {
            Link<T>* newLink = new Link<T>(value);
            newLink->next = start;
            start = newLink;
        } else {
            Link<T>* cur = start;
            for (size_t i = 0; i < pos - 1 && cur; ++i) {
                cur = cur->next;
            }
            if (cur) {
                Link<T>* newLink = new Link<T>(value);
                newLink->next = cur->next;
                cur->next = newLink;
            }
        }
    }

    void erase(size_t pos) override {
        if (pos == 0) {
            if (start) {
                Link<T>* temp = start;
                start = start->next;
                delete temp;
            }
        } else {
            Link<T>* cur = start;
            for (size_t i = 0; i < pos - 1 && cur && cur->next; ++i) {
                cur = cur->next;
            }
            if (cur && cur->next) {
                Link<T>* temp = cur->next;
                cur->next = cur->next->next;
                delete temp;
            }
        }
    }

    size_t size() const override {
        size_t count = 0;
        Link<T>* cur = start;
        while (cur) {
            ++count;
            cur = cur->next;
        }
        return count;
    }

    void clear() {
        while (start) {
            Link<T>* temp = start;
            start = start->next;
            delete temp;
        }
    }
};
