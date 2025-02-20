#include "w8.h"
template <class T>
void print(List<T> *pL) {
    cout << "Data: ";
    pL->traverse([](const int &val) { std::cout << setw(5) << val; });
    cout << endl;
}

template <class T>
void testBasic(List<T> *pL) {
    for (int i = 0; i < 10; ++i)
        pL->push_back(rand() % 100);
    cout << setw(40) << "Add randomly 10 values \n";
    print(pL);

    cout << "Size = " << pL->getSize() << endl;

    cout << "Is empty? " << (pL->isEmpty() ? "YES" : "NO") << endl;

    cout << "Remove the 5th index" << endl;
    pL->remove(5);
    print(pL);

    cout << "Clear the list!" << endl;
    pL->clear();
    cout << "Is empty? " << (pL->isEmpty() ? "YES" : "NO") << endl;

    cout << "Add 10 random values again" << endl;
    for (int i = 0; i < 10; ++i)
        pL->push_back(rand() % 100);
    print(pL);
    cout << "(*pL)[3] = " << (*pL)[3] << endl; // Reminder: pL is a pointer and it is not implicitly converted
    cout << "Make some changes using operator []" << endl;
    (*pL)[3] = 100;
    cout << "Now (*pL)[3] = " << (*pL)[3] << " and..." << endl;
    print(pL);

    cout << "Insert 100 at the head" << endl;
    pL->insert(100, 0);
    print(pL);
}

template <class T>
void testAdvanced(List<T> *pL) {
    for (int i = 0; i < 10; ++i)
        pL->push_back(rand() % 100);
    print(pL);
    int *pInt = pL->find(69);
    *pInt = 100;
    cout << "Change 69 into 100" << endl;
    print(pL);

    cout << "Index of value 24 = " << pL->findIdx(24) << endl;

    cout << "Swap index 1 and index 2" << endl;
    pL->swap(1, 2);
    print(pL);

    cout << "Swap index 4 and index 8" << endl;
    pL->swap(4, 8);
    print(pL);

    cout << "Revert the list!" << endl;
    pL->revert();
    print(pL);

    List<int> *pL1 = new L1List<int>;
    for (int i = 0; i < 5; ++i) {
        pL1->push_back(rand() % 100);
    }

    cout << "Inject a list having 5 elements into 3 index" << endl;
    print(pL1);
    print(pL);
    pL->inject(*pL1, 3);
    print(pL);

    cout << "Create new list and clone from the original." << endl;
    List<int> *pL2 = &pL->clone(3);
    print(pL2);
}
void run() {
    List<int> *pL = new L1List<int>;
    testAdvanced(pL);
    // testBasic(pL);
    delete pL;
}

void test() {
    cout << "hello from week 8!" << endl;
}
