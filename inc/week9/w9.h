#ifndef _H_W9
#define _H_W9
#include "../../main.h"

void run();
void test();
/*==============What we learned today!=====================*/
template <class T>
class fwIterBase {
public:
    fwIterBase() {}
    virtual ~fwIterBase() {}
    virtual fwIterBase<T>* clone() = 0;
    virtual T& operator*() = 0;
    virtual fwIterBase<T>& operator+(unsigned int offset) = 0;
    virtual fwIterBase<T>& operator++() = 0; //prefix
    virtual fwIterBase<T>& operator++(int) = 0; // postfix
    virtual fwIterBase<T>& operator=(const fwIterBase<T>&) = 0;
    virtual bool operator==(const fwIterBase<T>&) = 0;
    virtual bool operator!=(const fwIterBase<T>&) = 0;
};   

template <class T>
class fwIterator {
    protected:
        fwIterBase<T> *ptr;
    public:
    fwIterator() : ptr(nullptr) {}
    fwIterator(fwIterBase<T> *p) : ptr(p) {}
    fwIterator(const fwIterator<T>& i) : ptr(i.ptr->clone()) {}
    fwiterator(fwiterator<T>&& i) : ptr(i.ptr) { i.ptr = nullptr; }
    ~fwIterator() { if (ptr) delete ptr; }

    T& operator*() { return ptr->operator*(); }
    fwIterator<T> operator+(unsigned int offset) {
        fwiterator<T>  i(*this);
        *(i.ptr) = i.ptr->operator+(offset); // giá trị trả về có tạm thời??
        return i;
    }
    fwIterator<T>& operator++() {
        ++(*ptr);
        return *this;
    }
    fwIterator<T>& operator++(int) {
        fwiterator<T> i(*this);
        ++(*ptr);
        return i;
    } // ++i faster
    fwIterator<T>& operator=(const fwIterator<T>& i) {
        if (ptr) delete ptr;
        ptr = i.ptr->clone();
        return *this;
    }
    bool operator==(const fwIterator<T>& i) {
        return (*ptr == (*i.ptr));
    }
    bool operator!=(const fwIterator<T>& i) {
        return (*ptr != (*i.ptr));
    }
};
#endif