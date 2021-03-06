#include <iostream>
using namespace std;

struct Student
{
    string name, address;
    float marks;
};

class HashMap
{
    Student *arr;
    int capacity;

public:
    HashMap(const int &capacity) : capacity(capacity)
    {
        arr = new Student[capacity];
        for (int i = 0; i < capacity; i++)
            arr[i].marks = -1;
    }
    void insert(const Student &key)
    {
        Student temp = key;
        int hashIndex = hashCode(key.marks);
        if (arr[hashIndex].marks == -1)
            arr[hashIndex] = temp;
        else
        {
            for (int j = 0; j < capacity; j++)
            {
                int t = (hashIndex + j * j) % capacity;
                if (arr[t].marks == -1)
                {
                    arr[t] = temp;
                    break;
                }
            }
        }
        cout << "Data Added Successfully!\n";
    }

    void deleteEntry(const string &key, const int &marks)
    {
        int hashIndex = hashCode(marks);
        for (int j = 0; j < capacity; j++)
        {
            int t = (hashIndex + j * j) % capacity;
            if (arr[t].name == key)
            {
                arr[t].name = "";
                arr[t].marks = -1;
                arr[t].address = "";
                break;
            }
        }
        cout << "Data Deleted Successfully!\n";
        return;
    }

    void searchEntry(const string &key)
    {
        for (int i = 0; i < capacity; i++)
        {
            if (arr[i].name == key)
            {
                cout << i << ". " << arr[i].name << ' ' << arr[i].marks << ' ' << arr[i].address << '\n';
                return;
            }
        }
        cout << "Entry Not Found!\n";
        return;
    }
    void display() const
    {
        for (int i = 0; i < capacity; i++)
            if (arr[i].marks != -1)
                cout << i << ". " << arr[i].name << ' ' << arr[i].marks << ' ' << arr[i].address << '\n';
    }

private:
    int hashCode(int key)
    {
        return key % capacity;
    }
};

int main()
{
    int capacity, value, opt;
    Student student;
    cout << "Enter Capacity: ";
    cin >> capacity;
    HashMap *h = new HashMap(capacity);
Loop:
    cout << "0. Input Student\n1. Delete Student\n2. Search Student\n3. Display Students\n4. Exit\n";
    cout << "Option > ";
    cin >> opt;
    switch (opt)
    {
    case 0:
    {
        system("clear");
        cout << "Enter Name: ";
        cin >> student.name;
        cout << "Enter MarKs: ";
        cin >> student.marks;
        cout << "Enter Address: ";
        cin >> student.address;
        if (student.marks >= 0 && student.marks <= 100)
            h->insert(student);
        else
            cout << "Invalid Marks Bound, Keep the marks input between 0 to 100!\n";
        break;
    }
    case 1:
    {
        system("clear");
        cout << "Enter Name: ";
        cin >> student.name;
        cout << "Enter MarKs: ";
        cin >> student.marks;
        h->deleteEntry(student.name, student.marks);
        break;
    }
    case 2:
        system("clear");
        cout << "Enter Name: ";
        cin >> student.name;
        h->searchEntry(student.name);
        break;
    case 3:
        system("clear");
        h->display();
        break;
    case 4:
        exit(0);
        break;

    default:
        cout << "Input Out of Bounds, Please Try Again!\n";
        break;
    }
    goto Loop;
    return 0;
}
