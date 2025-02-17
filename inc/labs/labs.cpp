#include "labs.h"

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

// cau 7
void printHailstone(int number) {
    /*
     * STUDENT ANSWER
     */
    if (number == 1) {
        cout << number;
        return;
    }
    cout << number << ' ';
    if (number & 1) {
        printHailstone(number * 3 + 1);
    } else {
        printHailstone(number / 2);
    }
}

// cau 8

int myArrayToInt(char *str, int n) {
    /*
     * STUDENT ANSWER
     */
    if (n == 0) return 0;
    return (str[n - 1] - '0') + 10 * myArrayToInt(str, n - 1);
}

//cau 9

int findGCD(int a, int b) {
    /*
     * STUDENT ANSWER
     */
    if (b == 0) return a;
    return findGCD(b, a % b);
}

int findLCM(int a, int b)
{
    /*
     * STUDENT ANSWER
     */
    return a * b / findGCD(a, b);
}

// cau 10

void removeBracket(string &s, size_t left) {
    size_t right = s.find_first_of(")", left);
    
    // base case
    if (left == string::npos) {
        return;
    }
    // recursive case
    if (right != string::npos) {
        s.erase(right, 1);
        s.erase(left, 1);
    }
    removeBracket(s, s.find_last_of("(", left - 1));
}

int mininumBracketAdd(string s) {
    // STUDENT ANSWER
    removeBracket(s, s.find_last_of("("));
    return s.size();
}

// cau 11

void reverseSentence(const string &s, string& result, size_t left) {//left = 0 ->letter
    size_t space = s.find(' ', left);
    // base case
    if (space == string::npos) {
        result += s.substr(left);
        return;
    }
    // recursive case
    reverseSentence(s, result, space + 1);
    if (space == string::npos) space = s.size();
    result += " " + s.substr(left, space - left);
}

string reverseSentence(string s) {
    // STUDENT ANSWER
    string result = "";
    reverseSentence(s, result, 0);
    return result;
}
