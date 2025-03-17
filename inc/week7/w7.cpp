#include "w7.h"

void run() {
    test();
    List<int> *pL = new ArrList<int>, *pL2;
    for (int i = 0; i < 10; ++i) pL->push_back(rand() % 100);
    pL2 = &(pL->clone());


    for (auto i : (*pL)) cout << setw(5) << i; cout << endl;
    for (auto bIter = pL->begin(), eIter = pL->end(); bIter != eIter; ++bIter) cout << setw(8) << *bIter; cout << endl;


    pL ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;
    pL->insert(-1, 5);
    pL ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;

    pL->remove(pL->findInx(24));
    cout << "pL: "; pL ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;
    cout << "pL2: "; pL2 ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;
    
    pL->inject(*pL2, 2);
    cout << "pL: "; pL ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;

    List<int> *pIdx = &(pL->findAllIdx(24));
    cout << "pIdx: "; pIdx ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;

    pIdx->traverse([pL](int idx) {(*pL)[idx] = -1;});
    cout << "pL: "; pL ->traverse([](const int& val) {std::cout << setw(5) << val;}); cout << endl;

    delete pIdx;
    delete pL;
}

void test() {
    cout << "hello from week 7!" << endl;
}