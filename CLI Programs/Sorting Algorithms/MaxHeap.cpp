#include <iostream>

using namespace std;

class MaxHeap
{
    int *arr, capacity, heapSize;

public:
    MaxHeap(const int &capacity) : heapSize(0), capacity(capacity) { arr = new int[capacity]; }
    inline int insertNode(const int &data)
    {
        if (heapSize == capacity) // ? Checks if the array is now full
            return -1;
        heapSize++;
        int index = heapSize - 1;
        arr[index] = data;
        heapify(index);
        return 0;
    }
    void display(const int &index)
    {
        cout << "Current Array: ";
        for (int i = 0; i < heapSize; i++)
            cout << arr[i] << ' ';
    }
    void selectionSort()
    {
        int min, temp;
        for (int i = 0; i < heapSize - 1; i++)
        {
            min = i;
            for (int j = i + 1; j < heapSize; j++)
                if (arr[j] < arr[min])
                    min = j;
        swap(arr[i], arr[min]);
        }
    }

private:
    // NOTE Circular Array Type Implementation
    inline int parent(const int &index)
    {
        if (arr[index] != '\0' && ((index - 1) / 2) < heapSize && (index - 1) / 2 > -1)
            return ((index - 1) / 2);
        return -1;
    }
    // END Note
    void heapify(int &index) // ? Simple function to iteratively check and sort the array
    {
        while (arr[parent(index)] < arr[index] && arr[index] != '\0' && arr[parent(index)] != '\0' && index > -1 && index < heapSize)
            swap(arr[index], arr[parent(index)]), index = parent(index);
    }
};
static void mainMenu()
{
    int capacity, opt, number;
    cout << "Enter Total Capacity: ";
    cin >> capacity;
    MaxHeap obj(capacity);
loop:
    obj.display(0);
    cout << "\n0. Insert Node\n1. Sort In Ascending\n2. Exit\n";
    cout << "Option > ";
    cin >> opt;
    switch (opt)
    {
    case 0:
        system("clear");
        cout << "Enter Data: ";
        cin >> number;
        if (obj.insertNode(number) == -1)
            cout << "Array is Full!\n";
        break;
    case 1:
        obj.selectionSort();
        break;
    case 2:
        exit(0);
        break;
    default:
        cout << "[-] The Option is out of bounds, Please try again\n";
        break;
    }
    goto loop;
}

int main()
{
    mainMenu();
}