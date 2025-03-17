#ifndef _H_W8
#define _H_W8
#include "../../main.h"

void run();
void test();
/*==============What we learned today!=====================*/
template <class T>
class List {
public:
    List() {}
    virtual ~List() {}

    virtual fwIterator<T> begin() = 0;
    virtual fwIterator<T> end() = 0;

    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual T &operator[](int) = 0;

    virtual void insert(const T &, int) = 0;
    virtual void insert(T &&, int) = 0;
    virtual void push_back(const T &) = 0;
    virtual void remove(int) = 0;

    virtual T *find(
        const T &,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) = 0;
    virtual int findIdx(
        const T &,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) = 0;
    virtual List<void *> &findAll(
        const T &,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) = 0;
    virtual List<int> &findAllIdx(
        const T &,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) = 0;

    virtual List<T> &concat(List<T> &) = 0;
    virtual void swap(int, int) = 0;
    virtual void revert() = 0;
    virtual List<T> &inject(const List<T> &, int) = 0;
    virtual List<T> &clone(int = 0, int = -1) = 0;

    virtual void traverse(std::function<void(const T &)>) const = 0;
};

template <class T>
class L1List : public List<T> {
protected:
    struct Node {
        T data;
        Node *pNext;
        Node(const T &val, Node *pN = nullptr) : data(val), pNext(pN) {}
        Node(T &&val) : data(std::move(val), pNext(nullptr)) {}
    };
    Node *pHead;
    int nE;
    void move(Node **&p, int step) {
        while (*p && step) {
            p = &((*p)->pNext);
            step--;
        }
    }
    void swap(Node **&a, Node **&b) {
        Node *temp = std::move(*a);
        *a = std::move(*b);
        *b = std::move(temp);
    }

public:
    L1List() : pHead(nullptr), nE(0) {}
    ~L1List() { clear(); }

    int getSize() const { return nE; }
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
        Node *p = pHead;
        while (p && idx) {
            idx--;
            p = p->pNext;
        }
        if (p)
            return p->data;
        else
            throw "L1List::operator[]: Out of range!";
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

    void remove(int idx) {
        Node **p = &pHead;
        move(p, idx);
        if (*p) {
            Node *pDel = *p;
            *p = pDel->pNext;
            delete pDel;
            --nE;
        }
    }

    T *find(
        const T &key,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {
        for (Node *p = pHead; p; p = p->pNext) {
            if (equal(key, p->data))
                return &p->data;
        }
        return nullptr;
    }
    int findIdx(
        const T &key,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {
        int idx = 0;
        for (Node *p = pHead; p; p = p->pNext, ++idx) {
            if (equal(key, p->data)) {
                return idx;
            }
        }
        return -1;
    }
    List<void *> &findAll( // allocate memmory but don't delete?
        const T &,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {}
    List<int> &findAllIdx(
        const T &,
        std::function<bool(const T &, const T &)> equal =
            [](const T &k, const T &v) -> bool { return k == v; }) {}

    List<T> &concat(List<T> &b) {
    }
    void swap(int idx1, int idx2) {
        Node **p1 = &pHead, **p2 = nullptr;
        move(p1, idx1);
        p2 = p1;
        move(p2, idx2 - idx1);

        swap(p1, p2);
        move(p1, 1);
        move(p2, 1);
        swap(p1, p2);
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
        move(p, idx);
        Node *pT = *p;
        b.traverse([&p](const T &val){
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

        Node *p = pHead;
        for (int i = 0; p && (i < idx1); p = p->pNext, ++i);

        for (int i = idx1; i < idx2; ++i) {
            pL->push_back(p->data);
            p = p->pNext;
        }
        return *pL;
    }

    void traverse(std::function<void(const T &)> op) const {
        for (Node *p = pHead; p; p = p->pNext)
            op(p->data);
    }
};

#endif