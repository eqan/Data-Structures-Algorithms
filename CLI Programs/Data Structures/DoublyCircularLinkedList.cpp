#include <iostream>
using namespace std;
struct node
{
    int data;
    node *next;
    node *prev;
};
node *headNode = NULL;
node *createNode(const int& data)
{
    node *n = new node;
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}
class linkedList
{
public:
    static int countNode, deletedNodesCount;
    void inputNode(const int &n)
    {
        node *tempNode;
        tempNode = createNode(n);
        if (headNode == NULL)
            headNode = tempNode;
        else
        {
            node *traverseNode;
            traverseNode = headNode;
            while (traverseNode->next != NULL)
                traverseNode = traverseNode->next;
            if (traverseNode->next == NULL && n == 0)
            {
                tempNode->prev = traverseNode;
                traverseNode->next = headNode;
                deleteNode();
            }
            if (traverseNode->next == NULL)
            {
                tempNode->prev = traverseNode;
                traverseNode->next = tempNode;
            }
        }
        countNode++;
    }
    inline void deleteNode()
    {
        int n, i = 0;
        cout << "Enter the number you want to delete: ";
        cin >> n;
        node *traverseNode = headNode;
        while(traverseNode != NULL && traverseNode->data != n && i <= countNode)
        {
            traverseNode = traverseNode->next;
            i++;
        }
        if (i > countNode)
        {
            cout << "Number not found in list!\n";
        }
        if (traverseNode->data == n)
        {
            traverseNode= traverseNode->next;
            deletedNodesCount++;
        }
        cout << "Do you want to delete another?[Press 0 to quit or 1 to continue]: ";
        cin >> n;
        (n == 1) ? (deleteNode()) : (display());
    }
    inline void display() const
    {
        node *traverseNode;
        traverseNode = headNode;
        cout << "Total Nodes: " << countNode-deletedNodesCount << '\n';
        int i = 0;
        while (traverseNode != NULL)
        {
            cout << i << ". " << traverseNode->data << '\n';
            traverseNode = traverseNode->next;
            i++;
        }
        exit(1);
    }
};

int linkedList::countNode = 0, linkedList::deletedNodesCount=0;

int main()
{
    int n;
    linkedList obj;
loop1:
    cout << "Enter a number[Press 0 to Stop Input]: ";
    cin >> n;
    obj.inputNode(n);
    goto loop1;
}
