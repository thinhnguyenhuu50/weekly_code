#include "w3.h"

void run() {
    test();
    List<int> *pL = new ArrList<int>;
    for (int i = 0; i < 10; ++i) pL->push_back(rand() % 100);
    pL ->traverse([](int& val) {std::cout << setw(5) << val;}); cout << endl;
    pL->insert(-1, 5);
    pL ->traverse([](int& val) {std::cout << setw(5) << val;}); cout << endl;
    pL->remove(pL->findInx(44));
    pL ->traverse([](int& val) {std::cout << setw(5) << val;}); cout << endl;
    float s = 0, ss = 0;
    pL->traverse([&s, &ss](int& val) {s += val; ss += val*val;}); 
    cout << "average = " << double(s/pL->getSize()) << ", std = " << (double)(ss/pL->getSize() - (s * s/pL->getSize()*pL->getSize())) << endl;
    delete pL;
}

void test() {
    std::cout << "Hello from week3" << std::endl;
}

