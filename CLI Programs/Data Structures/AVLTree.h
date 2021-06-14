#include <iostream>
#include <string>
using namespace std;

template <class T>
class AVLTree
{
private:
    class node
    {
    public:
        T data;
        node *right, *left;
        int height;

        node(T x)
        {
            data = x;
            right = NULL;
            left = NULL;
            height = 0;
        }
    };

    node *rootNode;
    // NOTE Single Rotations
    void leftRotation(node *&r)
    {
        bool t = false;
        if (r == rootNode)
            t = true;
        node *a, *b, *bleft;
        a = r;
        b = r->right;
        bleft = b->left;

        r = b;
        b->left = a;
        a->right = bleft;

        a->height = 1 + max(height(a->left), height(a->right));
        b->height = 1 + max(height(b->left), height(b->right));
        if (t)
            rootNode = b;
    }

    void rightRotation(node *&r)
    {
        bool t = false;
        if (r == rootNode)
            t = true;
        node *a, *b, *bright;
        a = r;
        b = r->left;
        bright = b->right;

        r = b;
        b->right = a;
        a->left = bright;

        a->height = 1 + max(height(a->left), height(a->right));
        b->height = 1 + max(height(b->left), height(b->right));
        if (t)
            rootNode = b;
    }

    // NOTE Double Rotations
    void rightLeftRotation(node *&r)
    {
        rightRotation(r->right);
        leftRotation(r);
    }

    void leftRightRotation(node *&r)
    {
        leftRotation(r->left);
        rightRotation(r);
    }

    void push_back(const T &x, node *&r)
    {
        if (r == NULL)
            r = new node(x);
        else
        {
            if (x > r->data)
            {
                push_back(x, r->right);

                if (height(r->right) > height(r->left) + 1)
                {
                    if (height(r->right->right) > height(r->right->left))
                        leftRotation(r);
                    else
                        rightLeftRotation(r);
                }
            }
            else
            {
                push_back(x, r->left);
                if (height(r->left) > height(r->right) + 1)
                {
                    if (height(r->left->left) > height(r->left->right))
                        rightRotation(r);
                    else
                        leftRightRotation(r);
                }
            }
        }
        r->height = 1 + max(height(r->right), height(r->left));
    }

    void balance(node *&search)
    {
        if (height(search->right) > height(search->left) + 1)
        {
            if (height(search->right) - height(search->left) == 2)
                leftRotation(search);
            else
            {
                if (height(search->right->right) > height(search->right->left))
                    leftRotation(search);
                else
                    rightLeftRotation(search);
            }
        }
        if (height(search->left) > height(search->right) + 1)
        {
            if (height(search->left) - height(search->right) == 2)
                rightRotation(search);
            else
            {
                if (height(search->left->left) > height(search->left->right))
                    rightRotation(search);
                else
                    leftRightRotation(search);
            }
        }
    }
    // bool search(const T &x, node *r)
    // {
    //     if (r == NULL)
    //         return false;
    //     else if (r->data == x)
    //         return true;
    //     else
    //     {
    //         search(x, r->left);
    //         search(x, r->right);
    //     }
    //     return false;
    // }
    bool search(const T &x, node *&r)
    {
        if (r == NULL)
            return false;
        else if (r->data == x)
            return true;
        // else if (x < r->data)
        search(x, r->left);
        // else if (x > r->data)
        search(x, r->right);
        return false;
    }

    void pop(const T &x, node *&search)
    {
        if (search == NULL)
        {
            cout << "Not Found!\n";
            return;
        }
        else if (search->data == x)
        {
            if (search->left == NULL && search->right == NULL)
            {
                search = NULL;
                return;
            }
            else if (search->left == NULL && search->right != NULL)
            {
                node *r = search->right;
                search->data = search->right->data;
                search->left = search->right->left;
                search->right = search->right->right;
                delete r;
            }
            else if (search->left != NULL && search->right == NULL)
            {
                node *l = search->left;
                search->data = search->left->data;
                search->right = search->left->right;
                search->left = search->left->left;
                delete l;
            }
            else if (search->left != NULL && search->right != NULL)
            {
                node *max = findMax(search->left);
                node *smax = findSecondMax(search->left);
                search->data = max->data;
                if (smax != NULL)
                {
                    bool t = false;
                    if (search->left == smax)
                        t = true;
                    smax->right = max->left;
                    balance(smax);
                    if (t)
                        search->left = smax;
                }
                if (max == search->left)
                    search->left = search->left->left;

                delete max, smax;
            }
        }
        else if (x < search->data)
            pop(x, search->left);
        else if (x > search->data)
            pop(x, search->right);
        balance(search);
    }

    void display(node *r)
    {
        if (r == NULL)
            return;
        else
        {
            display(r->left);
            cout << r->data << " -> ";
            display(r->right);
        }
    }

    int height(node *r)
    {
        if (r == NULL)
            return -1;
        else
            return 1 + max(height(r->right), height(r->left));
    }

public:
    AVLTree()
    {
        rootNode = NULL;
    }

    void insert(const T &x)
    {
        push_back(x, rootNode);
    }
    void find(const T &x)
    {
        node *traverseNode = rootNode;
        if (search(x, traverseNode))
            cout << "Entity Found!\n";
        else
            cout << "Entity Not Found!\n";
    }

    void remove(const T &x)
    {
        node *search = rootNode;
        pop(x, search);
    }

    void display()
    {
        display(rootNode);
    }

    int computeHeight()
    {
        return height(rootNode);
    }

private:
    node *findMax(node *h)
    {
        node *max;
        if (h->right == NULL)
            return h;
        else
            max = findMax(h->right);
        return max;
    }
    node *findSecondMax(node *h)
    {
        node *smax;
        if (h->right == NULL)
            return NULL;
        if (h->right->right == NULL)
            return h;
        else
            smax = findSecondMax(h);
        return smax;
    }
};