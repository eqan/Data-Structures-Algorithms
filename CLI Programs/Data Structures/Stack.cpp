#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next = NULL;
};

node *head = NULL;

node *createNode(const int &x)
{
    node *temp = new node;
    temp->data = x;
    return temp;
}

class Stack
{
public:
    void push(const int &x)
    {
        node *temp = createNode(x);
        temp->next = head;
        head = temp;
    }

    node *pop()
    {
        node *temp = head;
        head = head->next;
        if (isEmpty(temp))
            return head;
        printf("%d has been popped!\n", temp->data);
        free(temp);
        return head;
    }

    bool isEmpty(node *headNode)
    {
        return (headNode == NULL) ? (true) : (false);
    }

    void print()
    {
        node *traverseNode = head;
        while (traverseNode != NULL)
        {
            traverseNode = pop(traverseNode);
        }
    }
};

int main()
{
    Stack obj;
    int i = 0;
    while (i != 10)
    {
        obj.push(i);
        i++;
    }
    obj.print();
}
