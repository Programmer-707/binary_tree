#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

using namespace std;

struct Node1
{
public:
    int data = 0;
    Node1* left = nullptr;
    Node1* right = nullptr;

    ~Node1()
    {
        delete left;
        delete right;
    }
};

class Binary_Search_Tree
{
private:
    Node1* root = nullptr;
    void DisplayRecursive(Node1 *);
    Node1* SearchRecursive(Node1 *, int);

public:
    ~Binary_Search_Tree() {delete root;}

    Node1* getRoot(){ return root; }
    void setRoot( Node1* p ){ root = p; }

    Node1* Insert( Node1*, int );
    void display();
    bool Search(int);

};

void Binary_Search_Tree::DisplayRecursive(Node1* b)
{
    if (b)
    {
        DisplayRecursive(b->left);
        cout << b->data << ", ";
        DisplayRecursive(b->right);
    }
}

void Binary_Search_Tree::display()
{
    DisplayRecursive(root);
}

Node1* Binary_Search_Tree::Insert(Node1 *b, int element)
{
    Node1* t;
    if (b == nullptr)
    {
        t = new Node1;
        t->data = element;
        t->left = nullptr;
        t->right = nullptr;
        return t;
    }

    if (element < b->data)
    {
        b->left = Insert(b->left, element);
    }
    else if (element > b->data)
    {
        b->right = Insert(b->right, element);
    }
    return b;  // key == p->data?

}

Node1* Binary_Search_Tree::SearchRecursive(Node1 *b, int element)
{
    if (b == nullptr)
    {
        return nullptr;
    }

    if (element == b->data)
    {
        return b;
    }
    else if (element < b->data)
    {
        return SearchRecursive(b->left, element);
    }
    else
    {
        return SearchRecursive(b->right, element);
    }
}

bool Binary_Search_Tree::Search(int element)
{
    auto found = SearchRecursive(root, element);
    return (found != nullptr);
}


#endif // BST_H_INCLUDED
