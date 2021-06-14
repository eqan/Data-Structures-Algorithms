#include <iostream>

using namespace std;

struct node
{
    int data;
    node *left = NULL;
    node *right = NULL;
};

node *rootNode = NULL;
node *createNode(const int &data)
{
    node *tempNode;
    tempNode = new node;
    tempNode->data = data;
    return tempNode;
}

class AVL
{
public:
    static int countNode;
    node *inputNode(node *traverseNode, const int &data)
    {
        if (traverseNode == NULL)
        {
            countNode++;
            cout << "Data has been successfully added!\n";
            traverseNode = createNode(data);
            return traverseNode;
        }
        else if (data <= traverseNode->data)
        {
            traverseNode->left = inputNode(traverseNode->left, data);
            traverseNode = balanceTree(traverseNode);
        }
        else
        {
            traverseNode->right = inputNode(traverseNode->right, data);
            traverseNode = balanceTree(traverseNode);
        }
        return traverseNode;
    }
    inline int height(node *tempNode)
    {
        if (tempNode != NULL)
        {
            int leftHeight = height(tempNode->left);
            int rightHeight = height(tempNode->right);
            return (max(leftHeight, rightHeight) + 1); // ? Returining the largest height
        }
        return 0;
    }
    inline int heightDifference(node *tempNode)
    {
        if (tempNode != NULL)
        {
            int leftHeight = height(tempNode->left);
            int rightHeight = height(tempNode->right);
            return (leftHeight - rightHeight); // ? Returning the balance between the 2 heights
        }
        return 0;
    }
    // NOTE Single Rotations
    inline node *rrRotation(node *parentNode)
    {
        node *tempNode = parentNode->right;
        parentNode->right = tempNode->left; // ? Assuming that maybe there ’s a left node in the parent ’s right
        tempNode->left = parentNode;
        return tempNode;
    }
    inline node *llRotation(node *parentNode)
    {
        node *tempNode = parentNode->left;
        parentNode->left = tempNode->right; // ? Assuming that maybe there ’s a right node in the parent ’s left
        tempNode->right = parentNode;
        return tempNode;
    }
    // NOTE Double Rotations
    node *lrRotation(node *parentNode)
    {
        node *tempNode = parentNode->left;
        parentNode->left = rrRotation(tempNode);
        return (llRotation(parentNode));
    }
    node *rlRotation(node *parentNode)
    {
        node *tempNode = parentNode->right;
        parentNode->right = llRotation(tempNode);
        return (rrRotation(parentNode));
    }
    node *balanceTree(node *rootNode)
    {
        int balanceFactor = heightDifference(rootNode);
        // NOTE Left Side Balancing
        if (balanceFactor > 1)
        {
            if (heightDifference(rootNode->left) > 0)
                rootNode = llRotation(rootNode);
            else
                rootNode = lrRotation(rootNode);
        }
        else if (balanceFactor < -1)
        {
            if (heightDifference(rootNode->right) > 0)
                rootNode = rlRotation(rootNode);
            else
                rootNode = rrRotation(rootNode);
        }
        cout << "[+] Tree has been successfully balanced !\n";
        return rootNode;
    }
    int calculateLeafNodes(node *traverseNode)
    {
        if (traverseNode == NULL)
            return 0;
        if (traverseNode->left == NULL && traverseNode->right == NULL)
            return 1;
        return (calculateLeafNodes(traverseNode->left) + calculateLeafNodes(traverseNode->right));
    }
    node *smallestNode(node *index)
    {
        while (index->left != NULL)
            index = index->left;
        return index;
    }
    node *deleteNode(node *traverseNode, const int &data)
    {
        if (traverseNode == NULL)
            return traverseNode;
        else if (data < traverseNode->data)
            traverseNode->left = deleteNode(traverseNode->left, data);
        else if (data >= traverseNode->data)
            traverseNode->right = deleteNode(traverseNode->right, data);
        else if (traverseNode->data == data)
        {
            if (traverseNode->left == NULL && traverseNode->right == NULL)
            {
                free(traverseNode);
            }
            else if (traverseNode->left == NULL)
            {
                node *temp = traverseNode;
                traverseNode = traverseNode->right;
                free(traverseNode);
            }
            else if (traverseNode->right == NULL)
            {
                node *temp = traverseNode;
                traverseNode = traverseNode->left;
                free(traverseNode);
            }
            else
            {
                node *temp = smallestNode(traverseNode->right);
                traverseNode->data = temp->data;
                traverseNode->right = deleteNode(traverseNode->right, temp->data);
            }
        }
    }
    void inorderTraversal(node *traverseNode)
    {

        if (traverseNode == NULL)
            return;
        inorderTraversal(traverseNode->left);
        cout << traverseNode->data << ' ';
        inorderTraversal(traverseNode->right);
    }
    void preorderTraversal(node *traverseNode)
    {
        if (traverseNode == NULL)
            return;
        cout << traverseNode->data << ' ';
        inorderTraversal(traverseNode->left);
        inorderTraversal(traverseNode->right);
    }
    void postorderTraversal(node *traverseNode)
    {
        if (traverseNode == NULL)
            return;
        inorderTraversal(traverseNode->left);
        inorderTraversal(traverseNode->right);
        cout << traverseNode->data << ' ';
    }
};
int AVL::countNode = 0;

int main()
{
    int n;
    AVL obj;
loop:
    cout << "0. Input Node\n1. Print All Orders\n2. Exit\n";
    cout << "Option: ";
    cin >> n;
    switch (n)
    {
    case 0:
        cout << "Enter Data: ";
        cin >> n;
        rootNode = obj.inputNode(rootNode, n);
        printf("\nTotal Leaf Nodes: %d\n", obj.calculateLeafNodes(rootNode));
        break;
    case 1:
    {
        node *traverseNode = rootNode;
        cout << "Inorder Traversal: ";
        obj.inorderTraversal(traverseNode);
        cout << '\n';
        cout << "Preorder Traversal: ";
        obj.preorderTraversal(traverseNode);
        cout << '\n';
        cout << "Postorder Traversal: ";
        obj.postorderTraversal(traverseNode);
        cout << '\n';
        break;
    }
    case 2:
        exit(1);
        break;
    default:
        cout << "You have exceeded the number of options, please try again!\n";
        break;
    }
    goto loop;
}
