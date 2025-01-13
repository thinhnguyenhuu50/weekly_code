#ifndef _H_W3
#define _H_W3
#include "../../main.h"
void test();

struct BaseObj {
    virtual void foo() = 0; // Pointer to a function
    virtual ~BaseObj() {}
};

struct AType : public BaseObj {
    int *p;
    void foo() {
        cout << "obj A;\n" << endl;
    }
    AType() {} // default constructor

    AType(const AType& b) {} // copy constructor -> void pass by value as creating a new object -> dead loop
    AType & operator=(const AType& b) {} // copy assignment operator

    AType(AType&& a): p(a.p) {a,p = nullptr;} // move constructor
};

struct BType : public BaseObj {
    void foo() {
        cout << "obj B;\n" << endl;
    }
};




// TODO: List 
template <class T>
class List {
public:
    List() {}
    ~List() {}

    virtual int getSize() = 0;
    virtual bool isEmpty() = 0;
    virtual T& operator[](int idx) = 0;

    virtual void insert(const T&, int idx) = 0;
    virtual void insert(T&&, int idx) = 0;
    virtual void push_back(const T&) = 0;
    virtual void remove(int idx) = 0;
    virtual T* find(const T& key) = 0;
    virtual int findInx(const T& key) = 0;
    virtual List<T*>& findAll(const T& key) = 0;
    virtual List<int>& findAllIdx(const T& key) = 0;
    virtual List<T>& concat(List<T>& b) = 0;
    virtual void swap(int dix1, int idx2) = 0;
    virtual void revert() = 0;
    virtual List<T>& inject(const List<T>&, int idx) = 0;
    virtual List<T>& clone(int idx1, int idx2) = 0;

    // virtual void traverse(void (*op)(T &)) = 0; //not enough generall
    virtual void traverse(std::function<void (T&)>) = 0; 
    // => Design is very important
};



#endif