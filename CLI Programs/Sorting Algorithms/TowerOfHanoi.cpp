#include <iostream>
#include <math.h>
using namespace std;
typedef struct Stack
{
    int size;
    int top;
    int *arr;
} Stack_Node;

Stack_Node *Create_stack(int size)
{
    Stack_Node *stack = new Stack;
    stack->size = size;
    stack->top = -1;
    stack->arr = new int[size];
    return stack;
}
// Function to check stack is full or not
bool Check_Full(Stack_Node *stack)
{
    if (stack->top == stack->size - 1)
        return true;
    else
        return false;
}

// Function to check stack is empty or not
bool Check_Empty(Stack_Node *stack)
{
    if (stack->top == -1)
        return true;
    else
        return false;
}
// Function to Push the element in stack
void push(Stack_Node *stack, int element)
{
    if (Check_Full(stack))
        return;

    stack->arr[++stack->top] = element;
}
// Function to Pop the element and return Popped element
int pop(Stack_Node *stack)
{
    if (Check_Empty(stack))
        return -1;

    return (stack->arr[stack->top--]);
}

// Function to Print the Movement of Discs
void Move_Disc(int disc, char from_Rod, char to_Rod)

{

    cout << "Move the disc " << disc << " "
         << "from Rod '" << from_Rod << "' to Rod '" << to_Rod << "'" << endl;
}

void Move_Disc_Helper(struct Stack *source, struct Stack *dest, char s, char d)
{
    int top1 = pop(source);
    int top2 = pop(dest);
    if (top1 == -1)
    {
        push(source, top2);
        Move_Disc(top2, d, s);
    }
    else if (top2 == -1)

    {
        push(dest, top1);
        Move_Disc(top1, s, d);
    }
    else if (top1 > top2)
    {
        push(source, top1);
        push(source, top2);
        Move_Disc(top2, d, s);
    }
    else
    {
        push(dest, top2);
        push(dest, top1);
        Move_Disc(top1, s, d);
    }
}

void TowerOfHanoi(int number_of_discs, struct Stack *source, struct Stack *aux, struct Stack *dest)

{
    char s = 'S', d = 'D', a = 'A';

    //  if n is even swap aux and dest
    if (number_of_discs % 2 == 0)
    {
        char var = d;
        d = a;
        a = var;
    }

    int number_of_moves = pow(2, number_of_discs) - 1;
    for (int i = number_of_discs; i >= 1; i--)
    {
        push(source, i);
    }

    // iteration of each i upto number of moves
    for (int i = 1; i <= number_of_moves; i++)
    {
        if (i % 3 == 0)
            Move_Disc_Helper(aux, dest, a, d);
        else if (i % 3 == 1)
            Move_Disc_Helper(source, dest, s, d);
        else if (i % 3 == 2)
            Move_Disc_Helper(source, aux, s, a);
    }
}

int main()

{
    int number_of_discs;
    cin >> number_of_discs;

    Stack_Node *source;
    Stack_Node *dest;
    Stack_Node *aux;

    // Creating 3 stacks for the three Rods
    source = Create_stack(number_of_discs);
    aux = Create_stack(number_of_discs);
    dest = Create_stack(number_of_discs);

    TowerOfHanoi(number_of_discs, source, aux, dest);

    // delete dynamically allocated memory stacks
    delete source;
    delete aux;
    delete dest;
    return 0;
}