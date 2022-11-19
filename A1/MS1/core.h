#pragma once
#define MIN -3
#define MAX 11
#define VALIDCHAR 6
#define PHONENUMBER 10

// -----------------------------------------
// Tester Function Prototypes

void test01_inputInt(void);
void test02_inputIntPositive(void);
void test03_inputIntRange(void);
void test04_inputIntRange(void);
void test05_inputCharOption(void);
void test06_inputCString(void);
void test07_inputCString(void);
void test08_inputCString(void);
void test09_displayPhone(void);

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//1.
int inputInt(void);

//2.
int inputIntPositive(void);

//3.
int inputIntRange(int min, int max);

//4.
char inputCharOption(const char	validChar[VALIDCHAR+1]); //size?

//5.
void inputCString(char givenString[], int minLen, int maxLen);

//6.
void displayFormattedPhone(const char phoneNum[]);