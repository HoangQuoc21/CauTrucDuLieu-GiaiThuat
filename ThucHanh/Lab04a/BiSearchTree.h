#include <iostream>
#include <climits>
#include <queue>
#include <cmath>
using namespace std;
#define COUNT 10

struct TNODE{
    int key;
    TNODE* pLeft;
    TNODE* pRight;
};

//1. Initialize a NODE from a given value:
TNODE* createNode(int data){
    TNODE* newNode = new TNODE;
    newNode->key = data;
    newNode->pLeft = newNode->pRight = NULL;
    return newNode;
}

//2. Add a NODE with given value into a given Binary Search Tree:
void Insert(TNODE* &pRoot, int x){
    if(!pRoot){
        TNODE* newNode = createNode(x);
        pRoot = newNode;
    }
    if (x < pRoot->key)
        Insert(pRoot->pLeft,x);
    else if (x > pRoot->key)
        Insert(pRoot->pRight,x);
}

//3. Pre-order Traversal:
void NLR(TNODE* pRoot){
    if (!pRoot)
        return;
    else{
        cout << pRoot->key << " ";
        NLR(pRoot->pLeft);
        NLR(pRoot->pRight);
    }
}

//4. In-order Traversal:
void LNR(TNODE* pRoot){
    if(pRoot){
        LNR(pRoot->pLeft);
        cout << pRoot->key << " ";
        LNR(pRoot->pRight);
    }
}

//5. Post-order Traversal:
void LRN(TNODE* pRoot){
    if(pRoot){
        LRN(pRoot->pLeft);
        LRN(pRoot->pRight);
        cout << pRoot->key << " ";
    }
}
//6. Level-order Traversal:
void LevelOrder(TNODE* pRoot){
    if(!pRoot)
        return;

    queue<TNODE*> nodeQueue;
    nodeQueue.push(pRoot);
    while(!nodeQueue.empty()){
        TNODE* currNode = nodeQueue.front();
        cout << currNode->key << " ";
        nodeQueue.pop();
        if (currNode->pLeft)
            nodeQueue.push(currNode->pLeft);
        if (currNode->pRight)
            nodeQueue.push(currNode->pRight);
    }
}

//7. Calculate the height of a given Binary Tree;
// Nếu cây có 1 node thì chiều cao là 1
int Height(TNODE* pRoot){
    if (!pRoot)
        return 0;
    int a = Height(pRoot->pLeft);
    int b = Height(pRoot->pRight);
    return (max(a,b)+1);
}

//8. Count the number of NODE from a given Binary Tree:
int countNode(TNODE* pRoot){
    if (!pRoot)
        return 0;
    int c = 1;
    int a = countNode(pRoot->pLeft);
    int b = countNode(pRoot->pRight);
    return a + b + c;
}

//9. Calculate the total value of all NODEs from a given Binary Tree:
int sumNode(TNODE* pRoot){
    if (!pRoot)
        return 0;
    int c = pRoot->key;
    int a = sumNode(pRoot->pLeft);
    int b = sumNode(pRoot->pRight);
    return a + b + c;
}

//10. Find and return a NODE with given value from a given Binary Search Tree:
TNODE* Search(TNODE* pRoot, int x){
    if (!pRoot)
        return NULL;
    TNODE* searchForNode;
    if (pRoot->key == x)
        searchForNode =  pRoot;
    else if (pRoot->key < x)
        searchForNode = Search(pRoot->pRight,x);
    else if (pRoot->key > x)
        searchForNode = Search(pRoot->pLeft,x);
    return searchForNode;
}

//11. Remove a NODE with given value from a given Binary Search Tree:
void searchStandFor(TNODE* &deleteNode, TNODE* &standForNode){
    if (standForNode->pLeft)
        searchStandFor(deleteNode, standForNode->pLeft);
    else{
        deleteNode->key = standForNode->key;
        deleteNode = standForNode;
        standForNode = standForNode->pRight;
    }    
}

void Remove(TNODE* &pRoot, int x){
    if(!pRoot)
        return;
    else if (pRoot->key > x)
        Remove(pRoot->pLeft,x);
    else if (pRoot->key < x)
        Remove(pRoot->pRight, x);
    else{
        TNODE* deleteNode = pRoot;
        if (!pRoot->pLeft)
            pRoot = pRoot->pRight;
        else if (!pRoot->pRight)
            pRoot = pRoot->pLeft;
        else
            searchStandFor(deleteNode, pRoot->pRight);
        delete deleteNode;
    }
}

//12. Initialize a Binary Search Tree from a given array:
TNODE* createTree(int a[], int n){
    TNODE* pRoot = createNode(a[0]);
    for (int i = 1; i < n; i++)
        Insert(pRoot, a[i]);
    return pRoot;
}

//13. Completely remove a given Binary Search Tree:
void removeTree(TNODE* &pRoot){
    if (pRoot){
        removeTree(pRoot->pLeft);
        removeTree(pRoot->pRight);
        delete pRoot;
    }
}

//14. Calculate the height of a NODE with given value: (return -1 if value not exist)
int heightNode(TNODE* pRoot, int value){
    if (!pRoot)
        return -1;
    TNODE*TreeOfvalue=Search(pRoot,value);
    if(!TreeOfvalue)
        return-1;
    return Height(TreeOfvalue);
}

//15. * Calculate the level of a given NODE:
int Level(TNODE* pRoot, TNODE* p){
    if (!pRoot)
        return -1;
    if (!p)
        return -1;
    if (pRoot == p)
        return 1;
    int left=Level(pRoot->pLeft,p);
    int right=Level(pRoot->pRight,p);
    if( left == -1 && right == -1 )
        return -1;
    return 1 + max(left,right);
}

//16. * Count the number leaves from a given Binary Tree:
int countLeaf(TNODE* pRoot){
    if (!pRoot) 
        return 0;
    if (!pRoot->pLeft && !pRoot->pRight)
        return 1;
    return countLeaf(pRoot->pLeft) + countLeaf(pRoot->pRight);   
}

//17. * Count the number of NODE from a given Binary Search Tree which key value is less than a given value:
int countLess(TNODE* pRoot, int x){
    if(!pRoot)
        return 0;
    int c = 0;
    if (pRoot->key < x)
        c = 1;
    int a = countLess(pRoot->pLeft,x);
    int b = countLess(pRoot->pRight,x);
    return c + a + b;
}

//18. * Count the number of NODE from a given Binary Search Tree which key value is greater than a given value:
int countGreater(TNODE* pRoot, int x){
    if (!pRoot)
        return 0;
    int c = 0;
    if (pRoot->key > x)
        c = 1;
    int a = countGreater(pRoot->pLeft,x);
    int b = countGreater(pRoot->pRight,x);
    return c + a + b;
}

//19. * Determine if a given Binary Tree is Binary Search Tree:
bool isBSTRoot(TNODE* pRoot, int minValue, int maxValue){
    if (!pRoot)
        return true;
    if (pRoot->key < minValue || pRoot->key > maxValue)
        return false;
    return isBSTRoot(pRoot->pLeft, minValue, pRoot->key-1) && isBSTRoot(pRoot->pRight, pRoot->key+1, maxValue);
}

bool isBST(TNODE* pRoot){
    return isBSTRoot(pRoot, INT_MIN, INT_MAX);
}

//20. * Determine if a given Binary Tree is a Full Binary Search Tree:
bool isFullBST(TNODE* pRoot){
    if (!pRoot || !isBST(pRoot))
        return false;
    int height = Height(pRoot);
    return countLeaf(pRoot) == pow(2, height - 1);
}

//21. Mô tả 1 cây nhị phân theo chiều ngang
//space lúc đầu = 0
void ProcessTree(TNODE* root, int space){
    if(!root)
        return;

    space += COUNT;

    ProcessTree(root->pRight, space);
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->key << endl;

    ProcessTree(root->pLeft, space);
}