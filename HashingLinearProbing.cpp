#include "AVLTree.h"
#include <fstream>
#include <vector>
using namespace std;

class Hash
{
    int bucket;
    AVLTree<string> *table;

public:
    Hash(const int &V)
    {
        this->bucket = V;
        table = new AVLTree<string>[bucket];
    }
    void insertItem(const string &key)
    {
        if (key[0] >= 97 && key[0] <= 122)
            table[int(key[0] - 97)].insert(key);
        else
        {
            cout << "Input Out Of Bounds, Try Again!\n";
            return;
        }
    }
    void searchItem(const string &key)
    {
        if (key[0] >= 97 && key[0] <= 122)
        {
            int index = hashFunction(key);
            table[index].find(key);
        }
        else
        {
            cout << "Input Out Of Bounds, Try Again!\n";
            return;
        }
    }
    void deleteItem(const string &key)
    {
        int index = hashFunction(key);
        table[index].remove(key);
        cout << "String Successfully Removed!\n";
    }
    void displayHash()
    {
        for (int i = 0; i < bucket; i++)
        {
            cout << char(i + 97) << ' ';
            table[i].display();
            cout << '\n';
        }
    }

private:
    int hashFunction(const string &x)
    {
        return ((int(x[0]) - 97) % bucket);
    }
};

int main()
{
    string line;
    vector<string> lines;
    srand(time(0));
    ifstream file("wordlist.10000.txt");
    while (getline(file, line))
        lines.push_back(line);
    file.close();
    Hash obj(26);
    int randomNumber, opt;
Loop:
    cout << "0. Import Random 100 Strings\n1. Insert A String\n2. Delete String\n3. Search String\n4. Display\n5. Exit\n";
    cout << "Option > ";
    cin >> opt;
    switch (opt)
    {
    case 0:
    {
        system("clear");
        for (int i = 0; i < 100; i++)
        {
            randomNumber = rand() % lines.size();
            obj.insertItem(lines[randomNumber]);
        }
        cout << "Import Successfull!\n";
        break;
    }
    case 1:
    {
        system("clear");
        cout << "Enter String: ";
        cin >> line;
        obj.insertItem(line);
        break;
    }
    case 2:
    {
        system("clear");
        cout << "Enter String: ";
        cin >> line;
        obj.deleteItem(line);
        break;
    }
    case 3:
    {
        system("clear");
        cout << "Enter String: ";
        cin >> line;
        obj.searchItem(line);
        break;
    }
    case 4:
        system("clear");
        obj.displayHash();
        break;
    case 5:
        exit(0);
        break;
    default:
        cout << "Input Out Of Bounds, Please Try Again!\n";
        break;
    }
    goto Loop;
    return 0;
}