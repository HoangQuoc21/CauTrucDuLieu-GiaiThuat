#include <iostream>
using namespace std;

// CÂY NHỊ PHÂN TÌM KIẾM: 
//-Xét bất kỳ cây con. Với mỗi Node, tất cả phần tử bên trái sẽ nhỏ hơn Node đó. Tất cả cây con bên phải sẽ lớn hơn Node đó

typedef struct NODE{
    int key;
    NODE *pLeft, *pRight;
}TNode;
typedef TNode *Tree;


void NLR(Tree root){
    if (root){
        cout << root->key << " ";
        NLR(root->pLeft);
        NLR(root->pRight);
    }
}

void LNR(Tree root){
    if (root){
        LNR(root->pLeft);
        cout << root->key << " ";
        LNR(root->pRight);
    }
}

void LRN(Tree root){
    if (root){
        LRN(root->pLeft);
        LRN(root->pRight);
        cout << root->key << " ";
    }
}

TNode* searchNode(Tree root, int x){
    if (root){
        if(root->key == x)
            return root;
        else if (x < root->key)
            return searchNode(root->pLeft, x);
        else
            return searchNode(root->pRight, x);
    }
    return NULL;
}

TNode* createNode(int x){
    TNode* newNode = new TNode;
    newNode->key = x;
    newNode->pLeft = newNode->pRight = NULL;
    return newNode;
}

void insert1(TNode* &root,int x){
    if(!root){
        TNode* newNode = createNode(x);
        root = newNode;
    }
    if (x < root->key)
        insert1(root->pLeft,x);
    else if (x > root->key)
        insert1(root->pRight,x);
}

TNode* insert2(TNode* root, int x){
    if(!root)
        return createNode(x);
    if (root->key > x)
        root->pLeft = insert2(root->pLeft,x);
    else if (root->key < x)
        root->pRight = insert2(root->pRight,x);
    return root;
}

void insertNode(Tree &root, int x){
    if(root){
        if (root->key == x)
            return;
        else if (x < root->key)
            return insertNode(root->pLeft,x);
        else
            return insertNode(root->pRight, x);
    }
    root = new TNode;
    root->key = x;
    root->pLeft = root->pRight = NULL;
}

//Phần tử thế mạng: phần tử nhỏ nhất bên cây phải con/ phần tử lớn nhất bên cây trái con (code thì chỉ có thể tìm nhỏ nhất bên phải)
void searchStandFor(Tree &deleteNode, Tree &standForNode){
    if (standForNode->pLeft)
        searchStandFor(deleteNode, standForNode->pLeft);
    else{
        deleteNode->key = standForNode->key;
        deleteNode = standForNode;
        standForNode = standForNode->pRight;
    }    
}

void deleteNode(Tree &root, int x){
    if(!root)
        return;
    if (root->key > x)
        return deleteNode(root->pLeft, x);
    else if (root->key < x)
        return deleteNode(root->pRight, x);
    else{
        //Nếu tìm thấy Node chứa x
        TNode* deleteNode = root;
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

void removeTree(Tree &root){
    if(root){
        removeTree(root->pLeft);
        removeTree(root->pRight);
        delete (root);
    }
}

void printMax(Tree root){
    while(root->pRight)
        root = root->pRight;
    cout << root->key << endl;
}

void printLeaf(NODE* p){
    if (!p)
        return;
    if (p->pLeft == NULL && p->pRight == NULL)
        cout << p->key;
    printLeaf(p->pLeft);
    printLeaf(p->pRight);
}

void print1Child(NODE* p){
    if (!p)
        return;
    if((p->pLeft && !p->pRight) || (!p->pLeft && p->pRight))
        cout <<p->key;
    print1Child(p->pLeft);
    print1Child(p->pRight);
}

void printSilbing(NODE* p, int x){
    if (!p)
        return;
    if(p->pLeft->key == x)
        cout << p->pRight->key;
    else if (p->pRight->key == x)
        cout << p->pLeft->key;
    printSilbing(p->pLeft,x);
    printSilbing(p->pRight,x);
}

int countNode(NODE* p){
    if (!p)
        return 0;
    int c = 0;
    c = c+1;
    int a = countNode(p->pLeft);
    int b = countNode(p->pRight);
    return a+b+c;
}

int height(NODE* p){
    if (!p)
        return -1;
    //Chiều cao bắt đầu từ 0
    int a = height(p->pLeft);
    int b = height(p->pRight);
    return (max(a,b)+1);
}

int count1Odd1Even(NODE* p){
    if (!p)
        return 0;
    int c = 0;
    if ((p->pLeft->key%2 == 0 && p->pRight->key%2 != 0) || (p->pLeft->key%2 != 0 && p->pRight->key%2 == 0))
        c++;
    int a = count1Odd1Even(p->pLeft);
    int b = count1Odd1Even(p->pRight);
    return a+b+c;
}

void modifyMaxHeap(int a[], int i, int n){
    int maxIndex = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if (left < n && a[left] > a[maxIndex])
        maxIndex = left;
    if (right < n && a[right] > a[maxIndex])
        maxIndex = right;
    if (maxIndex != i){
        swap(a[i], a[maxIndex]);
        modifyMaxHeap(a,maxIndex,n);
    }
}

int findMaxValue(NODE* root){
    if (!root->pRight)
        return root->key;
    return findMaxValue(root->pRight);
}

int findMinValue(NODE* root){
    if (!root->pLeft)
        return root->key;
    return findMinValue(root->pLeft);
}

bool isBST(NODE* root, int minValue, int maxValue){
    if (root == NULL)
        return true;

    if (root->key < minValue || root->key > maxValue)
        return false;
    
    return isBST(root->pLeft, minValue, root->key - 1) && isBST(root->pRight,root->key + 1, maxValue);
}

void rotateRight(NODE* a){
    NODE* b = a->pLeft;
    NODE* T2 = b->pRight;
    b->pRight = a;
    a->pLeft = T2;
    a = b;
}

bool isBalanced(NODE* p){
    if (abs(height(p->pLeft) - height(p->pRight)) <= 1)
        return true;
    return false;
}

int main(){
    system("cls");
    int nNode;
    cout << "nNode: ";
    cin >> nNode;
    Tree tree = NULL;
    for (int i = 0; i < nNode; i++){
        int data;
        cout << "Node " << i << " = ";
        cin >> data;
        insert1(tree, data);
    }
    while(1){
        system("cls");
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