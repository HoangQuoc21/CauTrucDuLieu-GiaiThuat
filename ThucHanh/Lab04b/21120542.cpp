#include <iostream>
#include <queue>
using namespace std;
#define LH = -1; //Cây con trái cao hơn
#define EH = 0; //Hai cây con cao bằng nhau
#define RH = 1; //Cây con phải cao hơn

struct AVLNODE{
    int key;
    AVLNODE* pLeft;
    AVLNODE* pRight;
    int height;
};

AVLNODE* createAVLNODE(int data){
    AVLNODE* newNode = new AVLNODE;
    newNode->pLeft = newNode->pRight = NULL;
    int height = 1;
    return newNode;
}

//Chiều cao của cây (height) Nếu cây chỉ có 1 AVLNODE thì chiều cao là 1
//Hàm lấy chiều cao của 1 AVLNode
int Height(AVLNODE* node){
    if (!node)
        return 0;
    return node->height;
}

// Balance: Chỉ số cân bằng. tính bằng độ cao cây con phải trừ độ cao cây con trái
//Hàm xác định chỉ số cân bằng tại AVLNode đang xét
int getBalance(AVLNODE* node){
    if(!node)
        return 0;
    return Height(node->pLeft) - Height(node->pRight); 
}

//Quay cây phải, đơn bước
void rightRotate(AVLNODE* &y){
    AVLNODE* x = y->pLeft;
    AVLNODE* T2 = x->pRight;

    //Quay
    x->pRight = y;
    y->pLeft = T2;

    //Cập nhật lại chiều cao
    y->height = max(Height(y->pLeft), Height(y->pRight)) + 1;
    x->height = max(Height(x->pLeft), Height(x->pRight)) + 1;

    //Trả node mới lại
    y = x;
}
//VD quay phải:
//          y                                      x 
//         / \                                   /   \
//        x   T4      Right Rotate (y)          z      y
//       / \          - - - - - - - - ->      /  \    /  \ 
//      z   T2                               T1  T3  T2  T4
//     / \
//   T1   T3 

//Quay cây trái, đơn bước
void leftRotate(AVLNODE* &x){
    AVLNODE* y = x->pRight;
    AVLNODE* T2 = y->pLeft;

    //Quay
    y->pLeft = x;
    x->pRight = T2;

    //Cập nhật lại chiều cao
    x->height = max(Height(x->pLeft), Height(x->pRight)) + 1;
    y->height = max(Height(y->pLeft), Height(y->pRight)) + 1;

    //Trả node mới lại
    x = y;
}
//VD quay trái:
//    x                               y
//  /  \                            /   \ 
// T1   y     Left Rotate(x)       x      z
//     /  \   - - - - - - - ->    / \    / \
//    T2   z                     T1  T2 T3  T4
//        / \
//      T3  T4


void InsertAVL(AVLNODE* &pRoot, int x){
    if (!pRoot){
        AVLNODE* newNode = createAVLNODE(x);
        pRoot = newNode;
    }
    if (x < pRoot->key)
        InsertAVL(pRoot->pLeft,x);
    else if (x > pRoot->key)
        InsertAVL(pRoot->pRight,x);
    
    int balance = getBalance(pRoot);

    //mất cân bằng trái trái
    if (balance > 1 && x < pRoot->pLeft->key)
        rightRotate(pRoot);

    //mất cân bằng phải phải
    if (balance < -1 && x > pRoot->pRight->key)
        leftRotate(pRoot);

    //mất cân bằng trái phải
    if (balance > 1 && x > pRoot->pLeft->key){
        leftRotate(pRoot->pLeft);
        rightRotate(pRoot);
    }

    //mất cân bằng phải trái
    if (balance < -1 && x < pRoot->pRight->key){
        rightRotate(pRoot->pRight);
        leftRotate(pRoot);
    }
}

void RemoveAVL(AVLNODE* &pRoot, int x){

}

// bool isAVL(AVLNODE* pRoot){

// }

void LevelOrder(AVLNODE* pRoot){
    if(!pRoot)
        return;

    queue<AVLNODE*> nodeQueue;
    nodeQueue.push(pRoot);
    while(!nodeQueue.empty()){
        AVLNODE* currNode = nodeQueue.front();
        cout << currNode->key << " ";
        nodeQueue.pop();
        if (currNode->pLeft)
            nodeQueue.push(currNode->pLeft);
        if (currNode->pRight)
            nodeQueue.push(currNode->pRight);
    }
}

void preOrder(AVLNODE *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->pLeft);
        preOrder(root->pRight);
    }
}


int main(){
    cout << "hehe\n";
    AVLNODE* pRoot = NULL;
    InsertAVL(pRoot, 10);
    InsertAVL(pRoot, 20);
    InsertAVL(pRoot, 30);
    InsertAVL(pRoot, 40);
    InsertAVL(pRoot, 50);
    InsertAVL(pRoot, 55);
    cout << "haha" << endl;
    preOrder(pRoot);
    return 0;
}