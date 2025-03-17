#ifndef _H_W
#define _H_W
#include "../../main.h"

void run();
void test();
/*==============What we learned today!=====================*/
// TODO: Sort algorithm
// Insert sort
template <class T>
void insertSort(T *pD, int N, std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    for (T *p = pD + 1, *p1, *pE = pD + N; p != pE; ++p) {
        T temp(std::move(*p));
        p1 = p - 1;
        while (cmpOp(temp, *p1) && pD <= p1) {
            *(p1 + 1) = std::move(*p1);
            --p1;
        }
        *(p1 + 1) = std::move(temp);
    }
}

// Shell sort
template <class T>
void insertSort(T *pD, int N, int step, 
                std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    for (T *p = pD + st, *p1, *pE = pD + N; p < pE; p += step) {
        T temp(std::move(*p));
        p1 = p - step;
        while (cmpOp(temp, *p1) && pD <= p1) {
            *(p1 + step) = std::move(*p1);
            p1 -= step;
        }
        *(p1 + step) = std::move(temp);
    }
}

template <class T>
void shellSort(T *pD, int N,
                std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    int A[100] {1}, nS = 1;
    while (A[nS - 1] < N) {A[nS] = A[nS - 1] * 2 + 1; ++nS;}
    for (--nS; nS >= 0; --nS) {
        int step = A[nS - 1];
        for (int i = 0; i < step; ++i) {
            insertSort(pD + i, N - i, step, cmpOp);
        
        }
    }
}

template <class T>
void selectionSort(T *pD, int N,
                    std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    for (T *p = pD, *pE = pD + N, *p1, *pSel; p != pE; ++p) {
        pSel = p;
        for (p1 = p + 1; p1 != pE; ++p1) {
            if (comOp(*p1, *pSel)) pSel = p1;
        }
        if (pSel != p) {
            T temp(std::move(*p));
            *p = std::move(*pSel);
            *pSel = std::move(temp);
        }
    }
}

template <class T>
void bubbleSort(T *pD, int N,
                    std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    for (T *p = pD, *pE = pD + N - 1; p != pE; --pE) {
        for (T *p1 = p; p1 < pE; ++p1) {
            if (comOp(*p1 + 1, *p1)) {
                T temp(std::move(*p1));
                *p1 = std::move(*(p1 + 1));
                *(p1 + 1) = std::move(temp);
            }
        }
    }
}

template <class T>
void mergeSort(T *pD, int N,
                    std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    if (N < 2) return;
    mergeSort(pD, N / 2, cmpOp);
    mergeSort(pD + N / 2, N - N / 2, cmpOp);
    T *pTemp = new T[N - N / 2];
    for (T *p = pD, *pL = pTemp, *pE = pD + N / 2; p != pE; ++p, ++pL) {
        *pL = std::move(*p);
    }
    T *p = pD, *pR = pD + N / 2, *pL = pTemp, *pLE = pTemp + N / 2, *pE = pD + N;
    while (pL != pLE && pR != pE) {
        if (cmpOp(*pL, *pR)) {
            *p++ = std::move(*pL++);
            else *p++ = std::move(*pR++);
        }
    }
    while (pL != pLE) {
        *p++ = std::move(*pL++);      
    }
    
    delete [] pTemp;
}

template <class T>
void quickSort(T *pD, int N,
                    std::function<bool(T &, T &)> cmpOp = [](T &a, T &b) -> bool { return a < b; }) {
    if (N < 2) return;
    T *pivot = pD + N / 2;
    T *pL = pD, *pR = pD + N - 1;
    while (pL < pR) {
        while (pL < pR && cmpOp(*pL, *pivot)) ++pL;
        while (pL < pR && cmpOp(*pivot, *pR)) --pR;
        if (pL != pR) {
            if (pivot == pL) pivot = pR;
            if (pivot == pR) pivot = pL;
            T temp(std::move(*pL));
            *pL = std::move(*pR);
            *pR = std::move(temp);
        }
    }
    if (pL != pivot) {
        T temp(std::move(*pL));
        *pL = std::move(*pivot);
        *pivot = std::move(temp);
    }
    quickSort(pD, pL - pD, cmpOp);
    quickSort(pL + 1, pD + N - pL - 1, cmpOp);
}
#endif