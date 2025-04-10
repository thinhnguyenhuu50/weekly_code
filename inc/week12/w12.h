#ifndef _H_W12
#define _H_W12
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
class BinTree {
protected:
    struct Node {
        T data;
        Node *pLeft, *pRight;
        Node(const T &val) : data(val), pLeft(nullptr), pRight(nullptr) {}
        Node(T &&val) : data(std::move(val)), pLeft(nullptr), pRight(nullptr) {}
    };
    Node *pRoot;
    std::function<bool(const T &, const T &)> lessCmp, greaterCmp, eqCmp;
    void clear(Node *pR) {
        if (pR->pLeft)
            clear(pR->pLeft);
        if (pR->pRight)
            clear(pR->pRight);
        delete pR;
    }

    void remove(Node *&pR, const T &key) {
        if (!pR)
            return;
        if (eqCmp(key, pR->data)) {
            if (pR->pLeft && pR->pRight) {
                Node *p = pR->pRight;
                while (p->pLeft)
                    p = p->pLeft;
                pR->data = p->data;
                remove(pR->pRight, p->data);
            } else if (pR->pLeft) {
                Node *p = pR;
                pR = pR->pLeft;
                delete p;
            } else if (pR->pRight) {
                Node *p = pR;
                pR = pR->pRight;
                delete p;
            } else {
                delete pR;
                pR = nullptr;
            }
        } else if (lessCmp(key, pR->data)) {
            remove(pR->pLeft, key);
        } else {
            remove(pR->pRight, key);
        }
    }

    void traverseNLR(Node *pR, std::function<void(const T &)> op) const {
        op(pR->data);
        if (pR->pLeft)
            traverseNLR(pR->pLeft, op);
        if (pR->pRight)
            traverseNLR(pR->pRight, op);
    }
    void traverseNRL(Node *pR, std::function<void(const T &)> op) const {
        op(pR->data);
        if (pR->pRight)
            traverseNRL(pR->pRight, op);
        if (pR->pLeft)
            traverseNRL(pR->pLeft, op);
    }
    void traverseLNR(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pLeft)
            traverseLNR(pR->pLeft, op);
        op(pR->data);
        if (pR->pRight)
            traverseLNR(pR->pRight, op);
    }
    void traverseLRN(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pLeft)
            traverseLRN(pR->pLeft, op);
        if (pR->pRight)
            traverseLRN(pR->pRight, op);
        op(pR->data);
    }
    void traverseRNL(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pRight)
            traverseRNL(pR->pRight, op);
        op(pR->data);
        if (pR->pLeft)
            traverseRNL(pR->pLeft, op);
    }
    void traverseRLN(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pRight)
            traverseRLN(pR->pRight, op);
        if (pR->pLeft)
            traverseRLN(pR->pLeft, op);
        op(pR->data);
    }

public:
    BinTree(std::function<bool(const T &, const T &)> lessFn = [](const T &key, const T &node) -> bool { return key < node; }, std::function<bool(const T &, const T &)> greaterFn = [](const T &key, const T &node) -> bool { return key > node; }, std::function<bool(const T &, const T &)> eqFn = [](const T &key, const T &node) -> bool { return key == node; })
        : lessCmp(lessFn), greaterCmp(greaterFn), eqCmp(eqFn), pRoot(nullptr) {
    }
    virtual ~BinTree() { clear(); }

    bool isEmpty() const { return !pRoot; }
    void clear() {
        if (pRoot)
            clear(pRoot);
        pRoot = nullptr;
    }

    void insert(const T &val) {
        Node **p = &pRoot;
        while (*p) {
            if (greaterCmp(val, (*p)->data))
                p = &((*p)->pRight);
            else
                p = &((*p)->pLeft);
        }
        *p = new Node(val);
    }
    void insert(T &&val) {
    }

    void remove(const T &key) {
        remove(pRoot, key);
    }

    T *find(const T &key) {
        Node *p = pRoot;
        while (p) {
            if (eqCmp(key, p->data))
                return &p->data;
            else if (lessCmp(key, p->data))
                p = p->pLeft;
            else
                p = p->pRight;
        }
        return nullptr;
    }
    List<void *> &findAll(const T &) {
    }

    void traverseBF(std::function<void(const T &)> op) const {
        queue<Node *> q;
        if (pRoot)
            q.push(pRoot);
        while (!q.empty()) {
            Node *pR = q.front();
            q.pop();
            op(pR->data);
            if (pR->pLeft)
                q.push(pR->pLeft);
            if (pR->pRight)
                q.push(pR->pRight);
        }
    }

    void traverseNLR(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseNLR(pRoot, op);
    }
    void traverseNRL(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseNRL(pRoot, op);
    }
    void traverseLNR(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseLNR(pRoot, op);
    }
    void traverseLRN(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseLRN(pRoot, op);
    }
    void traverseRNL(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseRNL(pRoot, op);
    }
    void traverseRLN(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseRLN(pRoot, op);
    }
};


template <class T>
class AVLTree {
protected:
    enum BalanceStatus {EH = 0, LH = -1, RH = 1};
    struct Node {
        T data;
        BalanceStatus b;
        Node *pLeft, *pRight;
        Node(const T &val, BalanceStatus _b = EH) : data(val), pLeft(nullptr), pRight(nullptr), b(_b) {}
        // Node(T &&val) : data(std::move(val)), pLeft(nullptr), pRight(nullptr) {}
    };
    Node *pRoot;
    std::function<bool(const T &, const T &)> lessCmp, greaterCmp, eqCmp;
    void clear(Node *pR) {
        if (pR->pLeft)
            clear(pR->pLeft);
        if (pR->pRight)
            clear(pR->pRight);
        delete pR;
    }

    void remove(Node *&pR, const T &key) {
        if (!pR)
            return;
        if (eqCmp(key, pR->data)) {
            if (pR->pLeft && pR->pRight) {
                Node *p = pR->pRight;
                while (p->pLeft)
                    p = p->pLeft;
                pR->data = p->data;
                remove(pR->pRight, p->data);
            } else if (pR->pLeft) {
                Node *p = pR;
                pR = pR->pLeft;
                delete p;
            } else if (pR->pRight) {
                Node *p = pR;
                pR = pR->pRight;
                delete p;
            } else {
                delete pR;
                pR = nullptr;
            }
        } else if (lessCmp(key, pR->data)) {
            remove(pR->pLeft, key);
        } else {
            remove(pR->pRight, key);
        }
    }

    void rotR(Node *&pR) {
        Node *p = pR;
        pR = p->pLeft;
        p->pLeft = pR->pRight;
        pR->pRight = p;
    }

    void rotL(Node *&pR) {
        Node *p = pR;
        pR = p->pRight;
        p->pRight = pR->pLeft;
        pR->pLeft = p;
    }

    bool insert (Node * & pR, const T& val) {
        if (!pR) {
            pR = new Node(val);
            return true;
        }
        if (lessCmp(val, pR->data)) {
            if (insert(pR->pLeft, val)) {
                if (pR->b == EH) {
                    pR->b = LH;
                    return true;
                } else if (pR->b == RH) {
                    pR->b = EH;
                    return false;
                } else {
                    if (pR->pLeft->b == EH) {
                        rotR(pR);
                        pR->b = RH;
                        pR->pRight->b = LH;
                        return true;
                    } else if (pR->pLeft->b == LH) {
                        rotR(pR);
                        pR->b = pR->pRight->b = EH;
                        return false;
                    } else {
                        rotL(pR->pLeft);
                        rotR(pR);
                        if (pR->b == EH) {
                            pR->pLeft->b = pR->pRight->b = EH;
                        } else if (pR->b == LH) {
                            pR->pRight->b = RH;
                            pR->pLeft->b = pR->b = EH;
                        } else {
                            pR->pLeft->b = LH;
                            pR->pRight->b = pR->b = EH;
                        }
                        return false;
                    }
                }
                
            }
            return false;
        } else {
            if (insert(pR->pRight, val)) {
                if (pR->b == EH) {
                    pR->b = RH;
                    return true;
                } else if (pR->b == LH) {
                    pR->b = EH;
                    return false;
                } else {
                    if (pR->pRight->b == EH) {
                        rotL(pR);
                        pR->b = LH;
                        pR->pLeft->b = RH;
                        return true;
                    } else if (pR->pRight->b == RH) {
                        rotL(pR);
                        pR->b = pR->pLeft->b = EH;
                        return false;
                    } else {
                        rotR(pR->pRight);
                        rotL(pR);
                        if (pR->b == EH) {
                            pR->pRight->b = pR->pLeft->b = EH;
                        } else if (pR->b == RH) {
                            pR->pLeft->b = LH;
                            pR->pRight->b = pR->b = EH;
                        } else {
                            pR->pRight->b = RH;
                            pR->pLeft->b = pR->b = EH;
                        }
                        return false;
                    }
                }
            }
            return false;
        }
    }

    void traverseNLR(Node *pR, std::function<void(const T &)> op) const {
        op(pR->data);
        if (pR->pLeft)
            traverseNLR(pR->pLeft, op);
        if (pR->pRight)
            traverseNLR(pR->pRight, op);
    }
    void traverseNRL(Node *pR, std::function<void(const T &)> op) const {
        op(pR->data);
        if (pR->pRight)
            traverseNRL(pR->pRight, op);
        if (pR->pLeft)
            traverseNRL(pR->pLeft, op);
    }
    void traverseLNR(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pLeft)
            traverseLNR(pR->pLeft, op);
        op(pR->data);
        if (pR->pRight)
            traverseLNR(pR->pRight, op);
    }
    void traverseLRN(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pLeft)
            traverseLRN(pR->pLeft, op);
        if (pR->pRight)
            traverseLRN(pR->pRight, op);
        op(pR->data);
    }
    void traverseRNL(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pRight)
            traverseRNL(pR->pRight, op);
        op(pR->data);
        if (pR->pLeft)
            traverseRNL(pR->pLeft, op);
    }
    void traverseRLN(Node *pR, std::function<void(const T &)> op) const {
        if (pR->pRight)
            traverseRLN(pR->pRight, op);
        if (pR->pLeft)
            traverseRLN(pR->pLeft, op);
        op(pR->data);
    }

public:
    AVLTree(std::function<bool(const T &, const T &)> lessFn = [](const T &key, const T &node) -> bool { return key < node; }, std::function<bool(const T &, const T &)> greaterFn = [](const T &key, const T &node) -> bool { return key > node; }, std::function<bool(const T &, const T &)> eqFn = [](const T &key, const T &node) -> bool { return key == node; })
        : lessCmp(lessFn), greaterCmp(greaterFn), eqCmp(eqFn), pRoot(nullptr) {
    }
    virtual ~AVLTree() { clear(); }

    bool isEmpty() const { return !pRoot; }
    void clear() {
        if (pRoot)
            clear(pRoot);
        pRoot = nullptr;
    }

    void insert(const T &val) {
        Node **p = &pRoot;
        while (*p) {
            if (greaterCmp(val, (*p)->data))
                p = &((*p)->pRight);
            else
                p = &((*p)->pLeft);
        }
        *p = new Node(val);
    }
    void insert(T &&val) {
    }

    void remove(const T &key) {
        remove(pRoot, key);
    }

    T *find(const T &key) {
        Node *p = pRoot;
        while (p) {
            if (eqCmp(key, p->data))
                return &p->data;
            else if (lessCmp(key, p->data))
                p = p->pLeft;
            else
                p = p->pRight;
        }
        return nullptr;
    }
    List<void *> &findAll(const T &) {
    }

    void traverseBF(std::function<void(const T &)> op) const {
        queue<Node *> q;
        if (pRoot)
            q.push(pRoot);
        while (!q.empty()) {
            Node *pR = q.front();
            q.pop();
            op(pR->data);
            if (pR->pLeft)
                q.push(pR->pLeft);
            if (pR->pRight)
                q.push(pR->pRight);
        }
    }

    void traverseNLR(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseNLR(pRoot, op);
    }
    void traverseNRL(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseNRL(pRoot, op);
    }
    void traverseLNR(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseLNR(pRoot, op);
    }
    void traverseLRN(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseLRN(pRoot, op);
    }
    void traverseRNL(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseRNL(pRoot, op);
    }
    void traverseRLN(std::function<void(const T &)> op) const {
        if (pRoot)
            traverseRLN(pRoot, op);
    }
};
#endif