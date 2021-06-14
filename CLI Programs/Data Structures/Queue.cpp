#include <iostream>

using namespace std;

class Queue
{
    int size, *arr, rear, front;

public:
    Queue(const int &size) : size(size)
    {
        arr = new int[size];
        rear = front = -1;
    }
    bool isEmpty()
    {
        if (rear == front == -1)
            return true;
        else
            return false;
    }
    bool isFull()
    {
        if ((rear + 1) % size == front)
            return true;
        else
            return false;
    }
    void Enqueue(const int &data)
    {
        if (isFull())
        {
            printf("Queue is full!\n");
            return;
        }
        else if (isEmpty())
        {
            front = rear = 0;
            return;
        }
        else
            rear = (rear + 1) % size;
        arr[rear] = data;
    }
    void dequeue()
    {
        if (isEmpty())
        {
            printf("Queue is Empty!\n");
            return;
        }
        else if (front == rear)
            front = rear = -1;
        else
        {
            cout << front << " has been dequeued!\n";
            front = (front + 1) % size;
        }
    }
    void display()
    {
        if (isEmpty())
        {
            printf("Queue is Empty!\n");
            return;
        }
        for (int i = front; i < rear; i++)
            cout << arr[i] << " \n";
    }
};

int main()
{
    Queue obj(5);
    for (int i = 0; i < 5; i++)
        obj.Enqueue(i);
    obj.dequeue();
    obj.display();
}