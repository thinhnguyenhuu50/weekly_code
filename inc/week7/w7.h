#ifndef _H_W7
#define _H_W7

#include "../../main.h"
struct DSA_Exception {
    int errCode;
    string desc;
    void *pData;
};

#define ARR_LIST_BLOCK 32

void run();
void test();

template <class T> class List {
  public:
    List() {}
    virtual ~List() {}

    // fundamental methods
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual T &operator[](int idx) = 0;

    virtual void insert(const T &, int idx) = 0;
    virtual void insert(T &&, int idx) = 0;
    virtual void push_back(const T &) = 0;
    virtual void remove(int idx) = 0;

    virtual T *find(
        const T &key,
        std::function<bool(const T &, const T &)>
            equal = // Providing default functions
        [](const T &k, const T &v) -> bool {
            return k == v;
        }) = 0; // lambda function: no name, default return ==
    virtual int findInx(
        const T &key,
        std::function<bool(const T &, const T &)>
            equal = // Providing default functions
        [](const T &k, const T &v) -> bool { return k == v; }) = 0;
    virtual List<void *> &findAll(
        const T &key,
        std::function<bool(const T &, const T &)>
            equal = // Providing default functions
        [](const T &k, const T &v) -> bool { return k == v; }) = 0;
    virtual List<int> &findAllIdx(
        const T &key,
        std::function<bool(const T &, const T &)>
            equal = // Providing default functions
        [](const T &k, const T &v) -> bool { return k == v; }) = 0;

    virtual List<T> &concat(List<T> &b) = 0;
    virtual void swap(int dix1, int idx2) = 0;
    virtual void revert() = 0;
    virtual List<T> &inject(const List<T> &, int idx) = 0;
    virtual List<T> &clone(int idx1 = 0, int idx2 = -1) = 0;

    // virtual void traverse(void (*op)(T &)) = 0; //not enough generall
    virtual void traverse(std::function<void(const T &)>) const = 0;
    // => Design is very important
};

template <class T> class ArrList : public List<T> {
  protected:
    T *pD;
    int nE, cap;

  public:
    ArrList() : cap(0), nE(0), pD(nullptr) {}
    ArrList(int N) : cap(N), nE(0), pD(nullptr) { resize(N); }
    ~ArrList() { clear(); }

    void resize(int N) {
        int newCap = (N + ARR_LIST_BLOCK - 1) / ARR_LIST_BLOCK * ARR_LIST_BLOCK;
        T *pN = new T[newCap];
        if (pD) {
            if (nE > newCap)
                nE = newCap;
            T *pSrc = pD, *pDst = pN;
            for (int i = 0; i < nE; i++)
                *pDst++ = std::move(*pSrc++);
            delete[] pD;
        }
        pD = pN;
        cap = newCap;
    }

    int getSize() const { return nE; }
    bool isEmpty() const { return !nE; }
    void clear() {
        if (pD)
            delete[] pD;
        pD = nullptr;
    }
    T &operator[](int idx) { // PreCond: index must be valid
        if (idx < 0 || idx >= nE)
            throw DSA_Exception{-100, "IArrList<T>::operator[]: invalid index",
                                nullptr};
        return pD[idx];
    }

    void insert(const T &val, int idx) {
        if (nE >= cap)
            resize(nE + 1);
        T *p = pD + nE, *pIdx = pD + idx;
        for (; p != pIdx; p--)
            *p = std::move(*(p - 1));
        *p = val;
        nE++;
    }

    void insert(T &&val, int idx) {
        if (nE >= cap)
            resize(nE + 1);
        T *p = pD + nE, *pIdx = pD + idx;
        for (; p != pIdx; p--)
            *p = std::move(*(p - 1));
        *p = std::move(val);
        nE++;
    }

    void push_back(const T &val) { insert(val, nE); }

    void remove(int idx) {
        T *p = pD + idx, *pE = pD + nE - 1;
        for (; p != pE; p++)
            *p = std::move(*(p + 1));
        nE--;
    }

    T *find(
        const T &key,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {
        for (T *p = pD, *pE = pD + nE; p != pE; p++)
            if (equal(key, *p))
                return p;
        return nullptr;
    }
    int findInx(
        const T &key,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {
        for (T *p = pD, *pE = pD + nE; p != pE; p++)
            if (equal(key, *p))
                return (p - pD);
        return -1;
    }
    List<void *> &findAll(
        const T &key,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {
        ArrList<void *> *pIdxL = new ArrList<void *>;
        for (T *p = pD, *pE = pD + nE; p != pE; p++)
            if (equal(key, *p))
                pIdxL->push_back(p);
        return *pIdxL;
    }
    List<int> &findAllIdx(
        const T &key,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {
        ArrList<void *> *pIdxL = new ArrList<void *>;
        for (T *p = pD, *pE = pD + nE; p != pE; p++)
            if (equal(key, *p))
                pIdxL->push_back(reinterpret_cast<void *>(static_cast<intptr_t>(
                    p - pD))); // I don't remember how teacher fix this error so
                               // I let Copilot fix it using such a huge hammer
        return *pIdxL;
    }

    List<T> &concat(List<T> &b) {
        resize(nE + b.getSize());
        T *p = pD + nE;
        // for (int i = 0; i < b.getSize(); i++) *p++ = b[i]; // Bad for linked
        // list, O(N)
        b.traverse([&p](const T &val) {
            *p++ = val;
        }); // capture in lambda, more effective
        nE += b.getSize();
        return *this;
    }
    void swap(int idx1, int idx2) { // preCond: idx1, idx2 are valid
        T tmp(std::move(pD[idx1]));
        pD[idx1] = std::move(pD[idx2]);
        pD[idx2] = std::move(tmp);
    }
    void revert() {
        for (int i = nE / 2 - 1; i > -1; i--)
            swap(i, nE - 1 - i);
    }
    List<T> &inject(const List<T> &b, int idx) {
        resize(nE + b.getSize());
        for (T *p = pD + nE + b.getSize() - 1,
               *pIdx = pD + idx + b.getSize() - 1;
             p != pIdx; --p)
            ;
        *p = std::move(*(p - b.getSize()));
        T *p = pD + idx;
        b.traverse([&p](const T &val) { *p++ = val; });
        nE += b.getSize();
        return *this;
    }
    List<T> &clone(int idx1 = 0, int idx2 = -1) {
        if (idx2 < 0)
            idx2 = nE;
        List<T> *pL = new ArrList<T>{idx2 - idx1};
        for (int i = idx1; i < idx2; i++)
            pL->push_back(pD[i]);
        return *pL;
    }

    void traverse(std::function<void(const T &)> op) const {
        for (const T *p = pD, *pE = pD + nE; p != pE;)
            op(*p++);
    }
};

template <typename T> class L1List : public List<T> {
  protected:
    struct Node {
        T data;
        Node *pNext;
        Node(const T &val, Node8 pN = nullptr) : data(val), pNext(P_NOWAIT) {}
        Node(T &&val) : data(std::move(val)), pNext(nullptr) {}
    };
    Node *pHead;
    int nE;

  public:
    L1List() : pHead(nullptr), nE(0) {}
    ~L1List() { clear(); }

    void getSize() const { return nE; }
    bool isEmpty() const { return !nE; }
    void clear() {
        while (pHead) {
            Node *p = pHead;
            pHead = pHead->pNext;
            delete p;
        }
        nE = 0;
    }
    T &operator[](int idx) {
        for (Node *p = pHead; p&&idx;idx--,  p = p->pNext);
        if (p) return p->data;
        else throw new DSA_Exception{-100, "L1List<T>::operator[]: invalid index", nullptr};
    }
    void insert(const T &val, int idx) {
        Node **p = &pHead;
        while (*p && idx) {
            p = &((*p)->pNext);
            idx--;
        }
        *p = new Node(val, *p);
        ++nE;
    }
    void insert(T &&val, int idx) {
        Node **p = &pHead;
        while (*p && idx) {
            p = &((*p)->pNext);
            idx--;
        }
        *p = new Node(std::move(val), *p);
        ++nE;
    }
    void push_back(const T &val) { insert(val, nE); }
    void remove (int idx) {
        Node **p = &pHead;
        while (*p && idx) {
            p = &((*p)->pNext);
            idx--;
        }
        if (*p) {
            Node *pDel = *p;
            *p = pDel->pNext;
            delete pDel;
            --nE;
        }
    }
    T *find(const T &key, std::function<bool(const T &, const T &)> equal = [](const T &k, const T &v) -> bool { return k == v; }) {
        for (Node *p = pHead; p; p = p->pNext) {
            if (equal(key, p->data)) return &p->data;
        }
        return nullptr;
    }
    int findInx(const T &key, std::function<bool(const T &, const T &)> equal = [](const T &k, const T &v) -> bool { return k == v; }) {
        int idx = 0;
        for (Node *p = pHead; p; p = p->pNext, idx++) {
            if (equal(key, p->data)) return idx;
        }
        return -1;
    }
    List<void *> &findAll(const T &key, std::function<bool(const T &, const T &)> equal = [](const T &k, const T &v) -> bool { return k == v; }) {
        ArrList<void *> *pIdxL = new ArrList<void *>;
        for (Node *p = pHead; p; p = p->pNext) {
            if (equal(key, p->data)) pIdxL->push_back(&p->data);
        }
        return *pIdxL;
    }
    List<int> &findAllIdx(const T &key, std::function<bool(const T &, const T &)> equal = [](const T &k, const T &v) -> bool { return k == v; }) {
        ArrList<int *> *pIdxL = new ArrList<int *>;
        int idx = 0;
        for (Node *p = pHead; p; p = p->pNext, idx++) {
            if (equal(key, p->data)) pIdxL->push_back(idx);
        }
        return *pIdxL;
    }
    List<T> &concat(List<T> &b) {
        Node **p = &pHead;
        while (*p) p = &((*p)->pNext);
        b.traverse([&p](T &val) {
            *p = new Node(val, nullptr);
            p = &((*p)->pNext);
        });
        nE += b.getSize();
        return *this;
    }
    void swap(int idx1, int idx2) {
        // if (idx2 < idx1) swap(idx2, idx1);
        if (idx2 - idx1 == 1) {
            Node **p = &pHead;
            int idx = idx1;
            while (*p && idx) { p = &((*p)->pNext); idx--; }
            Node *p1 = *p, *p2 = p1->pNext, *p3 = p2->pNext;
            *p = p2; p2->pNext = p1; p1->pNext = p3;
        }
        else {
            Node **pp1 = &pHead;
            int idx = idx1;
            while (*pp1 && idx) { pp1 = &((*pp1)->pNext); idx--; }
            Node **pp3 = pp1;
            idx += idx2 - idx1;
            while (*pp3 && idx) { pp3 = &((*pp3)->pNext); idx--; }
            Node *p1 = *pp1, *p2 = p1->pNext, *p3 = *pp3;
            
            p1->pNext = p3->pNext; *pp3 = p1;
            p3->pNext = p2; *pp1 = p3;
        }
    }
    void revert() {
        Node *pNL = nullptr;
        while (pHead) {
            Node *p = pHead;
            pHead = pHead->pNext;
            p->pNext = pNL;
            pNL = p;
        }
        pHead = pNL;
    }
    List<T> &inject(const List<T> &b, int idx) {
        Node **p = &pHead;
        while (*p && idx) { p = &((*p)->pNext); idx--; }
        Node *pT = *p;
        b.traverse([&p](T&val) {
            *p = new Node(val);
            p = &((*p)->pNext);
        });
        *p = pT;
        nE += b.getSize();
        return *this;
    }
    List<T> &clone(int idx1 = 0, int idx2 = -1) {
        if (idx2 < 0) idx2 = nE;
        List<T> *pL = new L1List<T>;
        Node *p = pHead; int idx = idx1;
        while (p && idx) {idx--; p = p->pNext;} 
        for (int i = idx1; i < idx2; i++) {
            pL->insert(p->data, 0);
            p = p->pNext;
        }
        pL->revert();
        return *pL;
    }
    void traverse(std::function<void(const T &)> op) const {
        for (Node *p = pHead; p; p = p->pNext) op(p->data);
    }
};
#endif