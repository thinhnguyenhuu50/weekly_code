#include "w8.h"

void run() { test(); }

void test() { cout << "hello from week 8!" << endl; }

void expand(string &s, size_t left, size_t right) {
    if (s[left - 1] == '0') {
        s.erase(left - 1, s.find_first_of(")", left) - left + 2);
        return;
    }
    if (s[left - 1] == '1') {
        s.erase(left - 1, 2);
        s.erase(s.find_first_of(")", left), 1);
        return;
    }
    s.insert(s.find_first_of(")", left), s.substr(left + 1, right - left - 1));
    s[left - 1]--;
    expand(s, left, right);
}

string expand(string s) {
    size_t left = s.find_last_of("(");
    size_t right = s.find_first_of(")", left);
    
    if (left == string::npos) {
        return s;
    }
    expand(s, left, right);
    s = expand(s);
    return s;
}