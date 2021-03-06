#include <iostream>
#include <math.h>
#include <string>
using namespace std;

template<typename T>
class Stack // ! Deals With Characters Only
{
    struct node
    {
        T data;
        node *nextNode;
    };

    node *headNode = NULL;
    node *createNode(const T &data)
    {
        node *tempNode = new node;
        tempNode->nextNode = NULL;
        tempNode->data = data;
        return tempNode;
    };

public:
    inline void inputArr();
    inline T pop();
    inline T top();
    inline void push(const T &);
    bool isEmpty() const;
    bool isFull() const;
    inline void display(const string &) const;
};
class StringConversions
{
    string input, output;

protected:
    inline void inputString();
    string convertToPostfix();
    string convertToPrefix();
    string convertToInfix();
    bool isOperand(const char &) const;
    bool isOperator(const char &) const;
    int getOperatorPrecedence(const char &) const;
    int evaluateHigherPrecedence(const char &, const char &) const;
    int checkTypeOfExpression();
    inline void menuForConversion();
    inline void displayCurrentOutput();
};

class StringEvaluation : protected StringConversions
{
    int operand1, operand2, result, value;
    Stack<int> S;

public:
    inline void mainMenu();
    int evaluateExpression(char &, int &, int &);
    int evaluatePostfix(string &);
    int evaluatePrefix(string &);
    // bool compareExpressions(string &, string&);
};
