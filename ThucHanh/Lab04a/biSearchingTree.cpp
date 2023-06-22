#include <iostream>
using namespace std;

struct node{
    int key;
    node* pLeft, *pRight;
};

typedef node* TNode;

void NLR(TNode root){
    if (root){
        cout << root->key << " ";
        NLR(root->pLeft);
        NLR(root->pRight);
    }
}

void LNR(TNode root){
    if (root){
        LNR(root->pLeft);
        cout << root->key << " ";
        LNR(root->pRight);
    }
}

void LRN(TNode root){
    if (root){
        LRN(root->pLeft);
        LRN(root->pRight);
        cout << root->key << " ";
    }
}

TNode createNode(int x){
    TNode newNode = new node;
    newNode->key = x;
    newNode->pLeft = newNode->pRight = NULL;
    return newNode;
}

void insertNode(TNode &root, int x){
    if(!root){
        TNode newNode = createNode(x);
        root = newNode;
    }
    if (x < root->key)
        insertNode(root->pLeft,x);
    else if (x > root->key)
        insertNode(root->pRight,x);
}

void searchStandFor(TNode &deleteNode, TNode &standForNode){
    if (standForNode->pLeft)
        searchStandFor(deleteNode, standForNode->pLeft);
    else{
        deleteNode->key = standForNode->key;
        deleteNode = standForNode;
        standForNode = standForNode->pRight;
    }    
}

void deleteNode(TNode &root, int x){
    if(!root)
        return;
    if (root->key > x)
        return deleteNode(root->pLeft, x);
    else if (root->key < x)
        return deleteNode(root->pRight, x);
    else{
        //Nếu tìm thấy Node chứa x
        TNode deleteNode = root;
        //Node có 1 con
        if (!root->pLeft)
            root = root->pRight;
        else if (!root->pRight)
            root = root->pLeft;
        //Node có 2 con
        else{
            searchStandFor(deleteNode, root->pRight);
        }
        //Node ko có con nào;
        delete deleteNode;
    }
}

void printMax(TNode root){
    while(root->pRight)
        root = root->pRight;
    cout << root->key << endl;
}

void printMin(TNode root){
    while(root->pLeft)
        root = root->pLeft;
    cout << root->key << endl;
}

void printLeaf(TNode p){
    if (!p)
        return;
    if (p->pLeft == NULL && p->pRight == NULL)
        cout << p->key;
    printLeaf(p->pLeft);
    printLeaf(p->pRight);
}

void print1Child(TNode p){
    if (!p)
        return;
    if((p->pLeft && !p->pRight) || (!p->pLeft && p->pRight))
        cout <<p->key;
    print1Child(p->pLeft);
    print1Child(p->pRight);
}

void printSilbing(TNode p, int x){
    if (!p)
        return;
    if(p->pLeft->key == x)
        cout << p->pRight->key;
    else if (p->pRight->key == x)
        cout << p->pLeft->key;
    printSilbing(p->pLeft,x);
    printSilbing(p->pRight,x);
}

int countNode(TNode p){
    if (!p)
        return 0;
    int c = 0;
    c = c+1;
    int a = countNode(p->pLeft);
    int b = countNode(p->pRight);
    return a+b+c;
}

int height(TNode p){
    if (!p)
        return -1;
    //Chiều cao bắt đầu từ 0
    int a = height(p->pLeft);
    int b = height(p->pRight);
    return (max(a,b)+1);
}

int count1Odd1Even(TNode p){
    if (!p)
        return 0;
    int c = 0;
    if ((p->pLeft->key%2 == 0 && p->pRight->key%2 != 0) || (p->pLeft->key%2 != 0 && p->pRight->key%2 == 0))
        c++;
    int a = count1Odd1Even(p->pLeft);
    int b = count1Odd1Even(p->pRight);
    return a+b+c;
}

void removeTree(TNode &root){
    if(root){
        removeTree(root->pLeft);
        removeTree(root->pRight);
        delete (root);
    }
}

int main(){
    system("cls");
    int nNode;
    cout << "nNode: ";
    cin >> nNode;
    TNode tree = NULL;
    for (int i = 0; i < nNode; i++){
        int data;
        cout << "Node " << i << " = ";
        cin >> data;
        insertNode(tree, data);
    }
    while(1){
        system("cls");
        cout << "Cay da nhap: ";
        cout << "\nDuyet tien thu tu: ";
        NLR(tree);
        cout << "\nDuyet trung thu tu: ";
        LNR(tree);
        cout << "\nDuyet hau thu tu: ";
        LRN(tree);
        cout << endl;
        cout << "Xoa node: ";
        int deleteKey;
        cin >> deleteKey;
        deleteNode(tree,deleteKey);
        system("pause");
    }
    return 0;
}