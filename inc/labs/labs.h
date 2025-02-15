#ifndef _H_LABS
#define _H_LABS
#include "../../main.h"

void run();
void test();
/*==============labs=====================*/
void expand(string &s, size_t left, size_t right);
string expand(string s);
void printHailstone(int number);
int myArrayToInt(char *str, int n) ;
int findGCD(int a, int b);
int findLCM(int a, int b);
void removeBracket(string &s, size_t left);
int mininumBracketAdd(string s);
void reverseSentence(const string &s, string &result, size_t left);
string reverseSentence(string s);
/*==============What we learned today!=====================*/
#endif