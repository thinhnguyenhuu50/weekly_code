#ifndef _H_W3
#define _H_W3
#include "../../main.h"

struct DSA_Exception {
    int errCode;
    string desc;
    void *pData;
};

#define ARR_LIST_BLOCK      32
void run();
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
class List :{
public:
    List() {}
    virtual ~List() {}

    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual T& operator[](int idx) = 0;

    virtual void insert(const T&, int idx) = 0;
    virtual void insert(T&&, int idx) = 0;
    virtual void push_back(const T&) = 0;
    virtual void remove(int idx) = 0;
    virtual T* find(const T& key, std::function<bool (const T& , const T&)> equal =
            [](const T& k, const T & v) -> bool {return k == v;}) = 0; //lambda function: no name, default return ==     
    virtual int findInx(const T& key) = 0;
    virtual List<void*>& findAll(const T& key) = 0;
    virtual List<int>& findAllIdx(const T& key) = 0;
    virtual List<T>& concat(List<T>& b) = 0;
    virtual void swap(int dix1, int idx2) = 0;
    virtual void revert() = 0;
    virtual List<T>& inject(const List<T>&, int idx) = 0;
    virtual List<T>& clone(int idx1, int idx2) = 0;

    // virtual void traverse(void (*op)(T &)) = 0; //not enough generall
    virtual void traverse const(std::function<void (T&)>) = 0; 
    // => Design is very important
};

template <class T>
class ArrList : public List<T> {
protected:
    T* pD;
    int nE, cap;
public:
    ArrList(): cap(0), nE(0), pD(nullptr) {}
    ArrList(int N): cap(N), nE(0), pD(nullptr) {resize(N);}
    ~ArrList() {clear();}

    void resize(int N) {
        int newCap = (N + ARR_LIST_BLOCK - 1) / ARR_LIST_BLOCK * ARR_LIST_BLOCK;
        T *pN = new T[newCap];
        if (pD) {
            if (nE > newCap) nE = newCap;
            T *pSrc = pD, *pDst = pN;
            for (int i = 0; i < nE; i++) *pDes++ = std::move(*pSrc++);
            delete[] pD;
        }
        pD = pN;
        cap = newCap;
    }
    int getSize() const {return nE;}
    bool isEmpty() const {return !nE;}
    void clear() { if (pD) delete[] pD; pD = nullptr;}
    T& operator[](int idx) { // PreCond: index must be valid
        if (idx < 0 || idx >= nE) throw DSA_Exception{-100, "IArrList<T>::operator[]: invalid index", nullptr};
        return pD[idx];
    }

    void insert(const T& val, int idx) {
        if (nE >= cap) resize(nE+1);
        T *p = pD + nE, *pIdx = pD + idx;
        for (; p != pIdx; p--) *p = std::move(*(p-1));
        *p = val;
        nE++;
    }
    void insert(T && val, int idx) {
        if (nE >= cap) resize(nE+1);
        T *p = pD + nE, *pIdx = pD + idx;
        for (; p != pIdx; p--) *p = std::move(*(p-1));
        *p = std::move(val);
        nE++;
    }
    void push_back(const T&) {insert(val, nE);}
    void remove(int idx) {
        T *p = pD + idx, *pE = pD + nE - 1;
        for (; p != pE; p++) *p = std::move(*(p+1));
        nE++;
    }
    virtual T* find(const T& key, std::function<bool (const T& , const T&)> eq =
            [](const T& k, const T & v) -> bool {return k == v;}) {
            for (T *p = pD; *pE = pD + nE; p++) if (eq(key, *p)) return p;
            return nullptr;
        }
    virtual int findInx(const T& key, std::function<bool (const T& , const T&)> eq =
        [](const T& k, const T & v) -> bool {return k == v;}) {
            for (T *p = pD; *pE = pD + nE; p++) if (eq(key, *p)) return (p - pD);
            return -1;  
    }
    virtual List<void*>& findAll(const T& key) {
        ArrList<void*> *pIdxL = new ArrList<void*>;
        for (T *p = pD; *pE = pD + nE; p++) if (eq(key, *p)) pIdxL->push_back(p);
        return *pIdxL;
    }
    List<int>& findAllIdx(const T& key) {
        ArrList<T*> *pIdxL = new ArrList<idx>;
        for (T *p = pD; *pE = pD + nE; p++) if (eq(key, *p)) pIdxL->push_back(p - pD);
        return *pIdxL;
    }
    List<T>& concat(List<T>& b) {
        resize(nE + b.getSize());
        T *p = pD + nE;
        // for (int i = 0; i < b.getSize(); i++) *p++ = b[i]; // Bad for linked list, O(N)
        b.traverse([&p](T& val) { *p++ = val;}); // capture in lambda, more effective
        return *this;
    }
    void swap(int dix1, int idx2) { //preCond: idx1, idx2 are valid
        T tmp(std::move(pD[idx1]));
        pD[dix1] = std::move(pD[idx2]);
        pD[idx2] = std::move(tmp);
    }
    void revert() {
        for (int i = nE/2 - 1; i > -; i--) swap(i, nE - 1 - i);
    }
    List<T>& inject(const List<T>&, int idx) {
        resize(nE + b.getSize());
        for (T *p = pD + nE + b.getSize(), *pIdx = pD + idx + b.getSize(); p!= pIdx; --p) *p = std::move(*(p - b.getSize()));
        T *p = pD + idx;
        b.traverse([&p](T& val) { *p = val;});
        return *this;
    }
    List<T>& clone(int idx1, int idx2) {
        List<T> *pL = new ArrList<T>{idx2 - idx1};
        for (int i = idx1; i < idx2; i++) pL->push_back(pD[i]);
        return *pL;
    }

    // virtual void traverse(void (*op)(T &)) //not enough generall
    void traverse(std::function<void (T&)>) const {
        for (T *p = pD, *pE = pD + nE; p != pE;) op(*p++);
    }
    // => Design is very important
    };



#endif