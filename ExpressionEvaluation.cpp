#include "ExpressionEvaluation.h"

template <typename T>
inline void Stack<T>::push(const T &data)
{
    node *tempNode = createNode(data);
    tempNode->nextNode = headNode;
    headNode = tempNode;
}

template <typename T>
inline T Stack<T>::pop()
{
    if (isEmpty() == true)
    {
        std::cout << "Stack is Empty\n";
        exit(1);
    }
    node *temp = headNode;
    headNode = headNode->nextNode;
    T popped = temp->data;
    free(temp);
    return popped;
}
template <typename T>
bool Stack<T>::isEmpty() const
{
    if (headNode == NULL)
        return true;
    else
        return false;
}
template <typename T>
inline void Stack<T>::display(const string &name) const
{
    cout << "Stored " << name << " Array: ";
    node *tempNode = headNode;
    while (tempNode != NULL)
    {
        cout << tempNode->data << " ";
        tempNode = tempNode->nextNode;
    }
    cout << '\n';
}
template <typename T>
inline T Stack<T>::top()
{
    return headNode->data;
}
inline void StringConversions::inputString()
{
    cout << "Enter Expression[Enter Space & Then Input Expression]: ";
    cin.ignore();
    getline(cin, input);
}
string StringConversions::convertToPostfix()
{
    Stack<char> operatorStack;
    output = "";
    for (int i = 0; i < input.length(); i++)
    {
        if (isOperator(input[i]))
        {
            while (!operatorStack.isEmpty() && operatorStack.top() != '(' && evaluateHigherPrecedence(operatorStack.top(), input[i]))
            {
                output += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(input[i]);
        }
        else if (isOperand(input[i]))
            output += input[i];

        else if (input[i] == '(')
            operatorStack.push(input[i]);

        else if (input[i] == ')')
        {
            while (!operatorStack.isEmpty() && operatorStack.top() != '(')
            {
                output += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
    }

    while (!operatorStack.isEmpty())
    {
        output += operatorStack.top();
        operatorStack.pop();
    }
    cout << "Converted To Postfix Successfully\n";
    return output;
}
string StringConversions::convertToInfix()
{
    Stack<string> operandStack;
    output = "";
    for (int i = input.length() - 1; i >= 0; i--)
    {
        if (isOperator(input[i]))
        {
            string op1 = operandStack.top();
            operandStack.pop();
            string op2 = operandStack.top();
            operandStack.pop();
            string temp = "(" + op1 + input[i] + op2 + ")";
            operandStack.push(temp);
        }
        else
            operandStack.push(string(1, input[i]));
    }
    output = operandStack.top();
    cout << "Converted To Infix Successfully\n";
    return output;
}
string StringConversions::convertToPrefix()
{
    Stack<char> operatorStack;
    Stack<char> operandStack;
    output = "";
    for (int i = 0; i < input.length(); i++)
    {
        if (isOperator(input[i]))
        {
            while (!operatorStack.isEmpty() && operatorStack.top() != '(' && evaluateHigherPrecedence(operatorStack.top(), input[i]))
            {
                output += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(input[i]);
        }
        else if (isOperand(input[i]))
            operandStack.push(input[i]);

        else if (input[i] == '(')
            operatorStack.push(input[i]);

        else if (input[i] == ')')
        {
            while (!operatorStack.isEmpty() && operatorStack.top() != '(')
            {
                output += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
            while (!operandStack.isEmpty())
            {
                output += operandStack.top();
                operandStack.pop();
            }
        }
    }

    while (!operatorStack.isEmpty())
    {
        output += operatorStack.top();
        operatorStack.pop();
    }
    cout << "Converted To Prefix Successfully\n";
    return output;
}
bool StringConversions::isOperand(const char &data) const
{
    if (data >= '0' && data <= '9')
        return true;
    else if (data >= 'a' && data <= 'z')
        return true;
    else if (data >= 'A' && data <= 'Z')
        return true;
    else
        return false;
}

bool StringConversions::isOperator(const char &data) const //Ignoring Brackets as there is no use in the end
{
    if (data == '+' || data == '-' || data == '*' || data == '/' || data == '^')
        return true;
    else
        return false;
}

int StringConversions::getOperatorPrecedence(const char &Operator) const //Ignoring Brackets as there is no use in the end
{
    if (Operator == '^')
        return 3;
    else if (Operator == '*' || Operator == '%' || Operator == '/')
        return 2;
    else if (Operator == '+' || Operator == '-')
        return 1;
    else
        return 0;
}

int StringConversions::evaluateHigherPrecedence(const char &Operator1, const char &Operator2) const
{
    int precedenceOperator1 = getOperatorPrecedence(Operator1), precedenceOperator2 = getOperatorPrecedence(Operator2);
    return (precedenceOperator1 == precedenceOperator2) ? true : (precedenceOperator1 > precedenceOperator2) ? true : false;
}

inline void StringConversions::displayCurrentOutput()
{
    cout << "The Current OutPut is: " << output << '\n';
}
int StringEvaluation::evaluateExpression(char &Operator, int &operand1, int &operand2)
{
    switch (Operator)
    {
    case '+':
        return (operand1 + operand2);
        break;
    case '-':
        return (operand1 - operand2);
        break;
    case '*':
        return (operand1 * operand2);
        break;
    case '/':
        return (operand1 / operand2);
        break;
    case '%':
        return (operand1 % operand2);
        break;
    case '^':
        return (pow(operand1, operand2));
        break;
    Default:
        cout << "Unknown Operand Found!\n";
        break;
    }
    return -1;
}
int StringEvaluation::evaluatePostfix(string &expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        if (isOperand(expression[i]))
        {
            cout << "Enter Value For '" << expression[i] << "' Variable: ";
            cin >> value;
            S.push(value);
        }
        else if (isOperator(expression[i]))
        {
            operand1 = S.top();
            S.pop();
            operand2 = S.top();
            S.pop();
            result = evaluateExpression(expression[i], operand1, operand2);
            S.push(result);
        }
    }
    return S.top();
}
int StringEvaluation::evaluatePrefix(string &expression)
{
    for (int i = (expression.length() - 1); i >= 0; i--)
    {
        if (isOperand(expression[i]))
        {
            cout << "Enter Value For '" << expression[i] << "' Variable: ";
            cin >> value;
            S.push(value);
        }
        else if (isOperator(expression[i]))
        {
            operand1 = S.top();
            S.pop();
            operand2 = S.top();
            S.pop();
            result = evaluateExpression(expression[i], operand1, operand2);
            S.push(result);
        }
    }
    return S.top();
}
int StringConversions::checkTypeOfExpression()
{
    if (isOperator(input[0]))
        return 0;
    else if (isOperator(input[input.length()]))
        return 1;
    else
        return 2;
}
inline void StringConversions::menuForConversion()
{
    char ans;
    switch (checkTypeOfExpression())
    {
    case 0:
        cout << "This is a Prefix Expression!\n";
        cout << "Do you want to convert it to Postfix[Press '0'] or Infix[Press '1']: ";
        cout << "Option: ";
        cin >> ans;
        (ans == '0') ? (convertToPostfix()) : (convertToInfix());
        break;
    case 1:
        cout << "This is a Postfix Expression!\n";
        cout << "Do you want to convert it to Prefix[Press '0'] or Infix[Press '1']: ";
        cout << "Option: ";
        cin >> ans;
        (ans == '0') ? (convertToPrefix()) : (convertToInfix());
        break;
    case 2:
        cout << "This is an Infix Expression!\n";
        cout << "Do you want to convert it to Prefix[Press '0'] or Postfix[Press '1']: ";
        cout << "Option: ";
        cin >> ans;
        (ans == '0') ? (convertToPrefix()) : (convertToPostfix());
        break;
    }
}
inline void StringEvaluation::mainMenu()
{
    int finalResult;
    char opt;
    string outputExpression;
    inputString();
loop:
    cout << "0. Evaluate Postfix Expression\n1. Evaluate Prefix Expression\n2. Check The Type\n3. Check and Convert\n4. Display Current Stored Output\n5. Exit\n";
    cout << "Option: ";
    cin >> opt;
    switch (opt)
    {
    case '0':
        outputExpression = convertToPostfix();
        cout << "Evaluated PostFix Expression: " << outputExpression << '\n';
        finalResult = evaluatePostfix(outputExpression);
        cout << "Calculated Result: " << finalResult << '\n';
        break;
    case '1':
        outputExpression = convertToPrefix();
        cout << "Evaluated Prefix Expression: " << outputExpression << '\n';
        finalResult = evaluatePrefix(outputExpression);
        cout << "Calculated Result: " << finalResult << '\n';
        break;
    case '2':
        switch (checkTypeOfExpression())
        {
        case 0:
            cout << "This is a Prefix Expression!\n";
            break;
        case 1:
            cout << "This is a Postfix Expression!\n";
            break;
        case 2:
            cout << "This is an Infix Expression!\n";
            break;
        }
        break;
    case '3':
        menuForConversion();
        break;
    case '4':
        displayCurrentOutput();
        break;
    case '5':
        exit(1);
        break;
    default:
        cout << "Exceeded the number of options please try again\n";
        break;
    }
    goto loop;
}