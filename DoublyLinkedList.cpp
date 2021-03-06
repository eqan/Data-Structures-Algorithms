#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next = NULL, *prev = NULL;
};

node *head = NULL;

node *createNode(const int &x)
{
    node *temp = new node;
    temp->data = x;
    return temp;
}

class DoublyLinkedList
{
public:
    void insertNode(const int &n)
    {
        node *temp, *traverse;
        temp = createNode(n);
        if (head == NULL)
            head = temp;
        else
        {
            traverse = head;
            while (traverse->next != NULL)
                traverse = traverse->next;
            traverse->next = temp;
            temp->next = NULL;
            temp->prev = traverse;
        }
    }
    void addAfter(const int &n, const int &index)
    {
        node *temp, *traverse;
        temp = createNode(n);
        if (head == NULL)
            head = temp;
        else
        {
            traverse = head;
            while (traverse->data != index && traverse->next != NULL)
                traverse = traverse->next;
            temp->prev = traverse;
            temp->next = traverse->next;
            traverse->next->prev = temp;
            traverse->next = temp;
        }
    }
    void deleteBegin()
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }
    void deleteEnd()
    {
        node* temp = head;
        temp->prev->next = NULL;
        free(temp);
    }
    void deleteBetween(const int& index)
    {
        node* traverse, *temp;
        traverse = head;
        while(traverse->data != index)
        {
            temp = traverse->next;
            traverse->next = traverse->next;
            temp->next->prev = traverse;
            free(temp);
        }
    }
    void Print()
    {
        node *temp = head;
        printf("Forward: ");
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }

    void ReversePrint()
    {
        node *temp = head;
        if (temp == NULL)
            return;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        printf("Reverse: ");
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->prev;
        }
        printf("\n");
    }
};

int main()
{
    DoublyLinkedList obj;
    // Calling an Insert and printing list both in forward as well as reverse direction.
    obj.insertNode(2);
    obj.Print();
    obj.ReversePrint();
    obj.insertNode(4);
    obj.Print();
    obj.ReversePrint();
    obj.insertNode(6);
    obj.Print();
    obj.ReversePrint();
    obj.insertNode(8);
    obj.Print();
    obj.ReversePrint();
    obj.addAfter(10, 6);
    obj.Print();
    obj.ReversePrint();
    obj.deleteBegin();
    obj.Print();
    obj.ReversePrint();
}