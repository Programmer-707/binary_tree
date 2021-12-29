#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

using namespace std;

struct Node {
public:
    Node* left= nullptr;
    int data= 0;
    Node* right= nullptr;
    int height= 0;

    //Node (int d, int h): data(d), height(h){};
    ~Node(){delete left; delete right;}
};

class AVL{
private:

    Node* SearchRecursive(Node *, int);
    void DisplayRecursive(Node* );
public:

    Node* root = nullptr;
    ~AVL(){ cout << "destructor AVL\n"; delete root;}

    Node* Insert(Node* p, int key);
    Node* LL_rotation(Node* p);
    Node* RR_rotation(Node* p);
    Node* LR_rotation(Node* p);
    Node* RL_rotation(Node* p);
    void Display(){ DisplayRecursive(root); }
    int Node_height(Node* p);
    int Balance_factor(Node* p);
    bool Search(int);



};

int AVL::Node_height(Node *p) {
    int hl;
    int hr;

    hl = (p && p->left) ? p->left->height : 0;
    hr = (p && p->right) ? p->right->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

int AVL::Balance_factor(Node *p) {
    int hl;
    int hr;

    hl = (p && p->left) ? p->left->height : 0;
    hr = (p && p->right) ? p->right->height : 0;

    return hl - hr;
}

Node* AVL::LL_rotation(Node *p) {
    Node* pl = p->left;
    Node* plr = pl->right;

    pl->right = p;
    p->left = plr;

    // Update height
    p->height = Node_height(p);
    pl->height = Node_height(pl);

    // Update root
    if (root == p){
        root = pl;
    }
    return pl;
}

Node* AVL::RR_rotation(Node *p) {
    Node* pr = p->right;
    Node* prl = pr->left;

    pr->left = p;
    p->right = prl;

    // Update height
    p->height = Node_height(p);
    pr->height = Node_height(pr);

    // Update root
    if (root == p){
        root = pr;
    }
    return pr;
}

Node* AVL::LR_rotation(Node *p) {
    Node* pl = p->left;
    Node* plr = pl->right;

    pl->right = plr->left;
    p->left = plr->right;

    plr->left = pl;
    plr->right = p;

    // Update height
    pl->height = Node_height(pl);
    p->height = Node_height(p);
    plr->height = Node_height(plr);

    // Update root
    if (p == root){
        root = plr;
    }
    return plr;
}

Node* AVL::RL_rotation(Node *p) {
    Node* pr = p->right;
    Node* prl = pr->left;

    pr->left = prl->right;
    p->right = prl->left;

    prl->right = pr;
    prl->left = p;

    // Update height
    pr->height = Node_height(pr);
    p->height = Node_height(p);
    prl->height = Node_height(prl);

    // Update root
    if (root == p){
        root = prl;
    }
    return prl;
}

Node* AVL::Insert(Node *p, int key) {
    Node* t;
    if (p == nullptr){
        t = new Node;
        t->data = key;
        t->left = nullptr;
        t->right = nullptr;
        t->height = 1;  // Starting height from 1 onwards instead of 0
        return t;
    }

    if (key < p->data){
        p->left = Insert(p->left, key);
    } else if (key > p->data){
        p->right = Insert(p->right, key);
    }

    // Update height
    p->height = Node_height(p);

    // Balance Factor and Rotation
    if (Balance_factor(p) == 2 && Balance_factor(p->left) == 1) {
        return LL_rotation(p);
    } else if (Balance_factor(p) == 2 && Balance_factor(p->left) == -1){
        return LR_rotation(p);
    } else if (Balance_factor(p) == -2 && Balance_factor(p->right) == -1){
        return RR_rotation(p);
    } else if (Balance_factor(p) == -2 && Balance_factor(p->right) == 1){
        return RL_rotation(p);
    }

    return p;
}

void AVL::DisplayRecursive(Node *p) {
    if (p){
        DisplayRecursive(p->left);
        cout << p->data << ", " << flush;
        DisplayRecursive(p->right);
    }
}

Node* AVL::SearchRecursive(Node *b, int element)
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

bool AVL::Search(int element)
{
    auto found = SearchRecursive(root, element);
    return (found != nullptr);
}


#endif // AVL_H_INCLUDED
