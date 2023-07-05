#pragma once
#include <iostream>
#include <queue>
using namespace std;

//Cấu trúc Node của cây AVL
struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

//1. Hàm Tạo Node
NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->height = 1;
    newNode->pLeft = newNode->pRight = NULL;
    newNode->key = data;
    return newNode;
}

//Hàm tìm chiều cao của Node truyền vào
int height(NODE* Node){
    if (Node == NULL)
        return 0;
    return Node->height;
}

//Hàm xoay phải
void rightRotate(NODE* &y){
    NODE* x = y->pLeft;
    NODE* T2 = x->pRight;

    //Xoay
    x->pRight = y;
    y->pLeft = T2;

    //Cập nhật lại chiều cao
    y->height = max(height(y->pLeft), height(y->pRight)) + 1;
    x->height = max(height(x->pLeft), height(x->pRight)) + 1;

    //Cập nhật con trỏ gốc
    y = x;
}
//VD xoay phải:
//          y                                      x 
//         / \                                   /   \
//        x   T3        rightRotate(y)          z      y
//       / \          - - - - - - - - ->      /  \    /  \ 
//      z   T2                               T0  T1  T2  T3
//     / \
//   T0   T1

//Hàm xoay trái
void leftRotate(NODE*& x){
    NODE* y = x->pRight;
    NODE* T2 = y->pLeft;

    //Xoay
    y->pLeft = x;
    x->pRight = T2;

    //Cập nhật lại chiều cao
    x->height = max(height(x->pLeft), height(x->pRight)) + 1;
    y->height = max(height(y->pLeft), height(y->pRight)) + 1;

    //Cập nhật con trỏ gốc
    x = y;
}
//VD xoay trái:
    //   x                                y
    //  /  \                            /   \ 
    // T1   y      leftRotate(x)       x      z
    //     /  \   - - - - - - - ->    / \    / \
    //    T2   z                     T1  T2 T3  T4
    //        / \
    //      T3  T4

//Hàm trả về chỉ số cân bằng của Node truyền vào (tính bằng: chiều cao cây con trái - chiều cao cây con phải)
int getBalance(NODE* Node){
    if (Node == NULL)
        return 0;
    return height(Node->pLeft) - height(Node->pRight);
}
//balance = 0 => 2 cây con cân bằng
//balance = 1 => cân bằng lệch trái (cây con trái cao hơn)
//balance = -1 => cân bằng lệch phải (cây con phải cao hơn)

//2. Hàm thêm 1 Node vào cây
void Insert(NODE* &pRoot, int x){
    // Có các bước:
    // B1: Thêm Node vào như cây BST
    if (pRoot == NULL)
        pRoot = createNode(x);

    if (x < pRoot->key)
        Insert(pRoot->pLeft, x);
    else if (x > pRoot->key)
        Insert(pRoot->pRight, x);
    else
        return;

    // B2: cập nhật lại chiều cao cho Node gốc
    pRoot->height = max(height(pRoot->pLeft),height(pRoot->pRight)) + 1;

    // B3: Tìm chỉ số cân bằng để xem cây có bị mất cân bằng không
    int balance = getBalance(pRoot);

    //Nếu mất cân bằng, có 4 trường hợp có thể xảy ra:

    // -TH1: mất cân bằng trái trái (xoay phải cây gốc)
    if (balance > 1 && x < pRoot->pLeft->key){
        cout << pRoot->key << " Mat can bang trai trai.\n";
        rightRotate(pRoot);
        return;
    }
        
    // -TH2: mất cân bằng phải phải (xoay trái cây gốc)
    if (balance < -1 && x > pRoot->pRight->key){
        cout << pRoot->key << " Mat can bang phai phai.\n";
        leftRotate(pRoot);
        return;
    }
        
    // -TH3: mất cân bằng trái phải (xoay trái cây con trái - xoay phải cây gốc)
    if (balance > 1 && x > pRoot->pLeft->key ){
        cout << pRoot->key << " Mat can bang trai phai.\n";
        leftRotate(pRoot->pLeft);
        rightRotate(pRoot);
        return;
    }

    // -TH4: mất cân bằng phải trái (xoay phải cây con phải - xoay trái cây gốc)
    if (balance < -1 && x < pRoot->pRight->key ){
        cout << pRoot->key << " Mat can bang phai trai.\n";
        rightRotate(pRoot->pRight);
        leftRotate(pRoot);
        return;
    }
}

//Lấy phần tử thế mạng là phần tử phải nhất bên cây con trái
NODE* maxValueNode(NODE* node){
    NODE* current = node;
    while (current->pRight != NULL)
        current = current->pRight;

    return current;
}

//3. Hàm xóa 1 Node ra khỏi cây AVL
void Remove(NODE* &pRoot, int x){
    //Gồm các bước: 
    // B1: xóa 1 Node như cây BST
    if (pRoot == NULL)
        return;

    if (x < pRoot->key)
        Remove(pRoot->pLeft, x);

    else if (x > pRoot->key)
        Remove(pRoot->pRight, x);

    // x == pRoot->key
    else{
        //Trường hợp node muốn xóa có 1 con hoặc không có con 
        if ((pRoot->pLeft == NULL) || (pRoot->pRight == NULL)){
            NODE* deleteNode = pRoot->pLeft ? pRoot->pLeft : pRoot->pRight;

            //TH không có con 
            if (deleteNode == NULL){
                deleteNode = pRoot;
                pRoot = NULL;
            }
            //Trường hợp có 1 con
            else  
                *pRoot = *deleteNode;  
            
            delete deleteNode;
        }
        else{
            //Tìm phần tử thế mạng
            NODE* standingNode = maxValueNode(pRoot->pLeft);

            //Đưa giá trị của phần tử thế mạng lên node xóa
            pRoot->key = standingNode->key;

            //Xóa phần tử thế mạng
            Remove(pRoot->pLeft, standingNode->key);
        }
    }

    //Nếu cây chỉ còn 1 Node thì return 
    if (pRoot == NULL)
        return;

    // B2: cập nhật chiều cao của Node gốc 
    pRoot->height = max(height(pRoot->pLeft),height(pRoot->pRight)) + 1;

    // B3: Tìm chỉ số cân bằng để xem cây có bị mất cân bằng không
    int balance = getBalance(pRoot);

    //Nếu mất cân bằng, có 4 trường hợp có thể xảy ra:

    // -TH1: mất cân bằng trái trái (xoay phải cây gốc)
    if (balance > 1 && getBalance(pRoot->pLeft) >= 0 ){
        cout << pRoot->key << " Mat can bang trai trai.\n";
        rightRotate(pRoot);
        return;
    }
        
    // -TH2: mất cân bằng phải phải (xoay trái cây gốc)
    if (balance < -1 && getBalance(pRoot->pRight) <= 0 ){
        cout << pRoot->key << " Mat can bang phai phai.\n";
        leftRotate(pRoot);
        return;
    }
        
    // -TH3: mất cân bằng trái phải (xoay trái cây con trái - xoay phải cây gốc)
    if (balance > 1 && getBalance(pRoot->pLeft) < 0 ){
        cout << pRoot->key << " Mat can bang trai phai.\n";
        leftRotate(pRoot->pLeft);
        rightRotate(pRoot);
        return;
    }

    // -TH4: mất cân bằng phải trái (xoay phải cây con phải - xoay trái cây gốc)
    if (balance < -1 && getBalance(pRoot->pRight) > 0){
        cout << pRoot->key << " Mat can bang phai trai.\n";
        rightRotate(pRoot->pRight);
        leftRotate(pRoot);
        return;
    }
}

// Duyệt tiền thứ tự
void NLR(NODE* pRoot){
    if (!pRoot)
        return;
    else{
        cout << pRoot->key << " ";
        NLR(pRoot->pLeft);
        NLR(pRoot->pRight);
    }
}

// Duyệt trung thứ tự
void LNR(NODE* pRoot){
    if(pRoot){
        LNR(pRoot->pLeft);
        cout << pRoot->key << " ";
        LNR(pRoot->pRight);
    }
}

// Duyệt hậu thứ tự
void LRN(NODE* pRoot){
    if(pRoot){
        LRN(pRoot->pLeft);
        LRN(pRoot->pRight);
        cout << pRoot->key << " ";
    }
}

// Duyệt theo mức
void LevelOrder(NODE* pRoot){
    if(!pRoot)
        return;

    queue<NODE*> nodeQueue;
    nodeQueue.push(pRoot);
    while(!nodeQueue.empty()){
        NODE* currNode = nodeQueue.front();
        cout << currNode->key << " ";
        nodeQueue.pop();
        if (currNode->pLeft)
            nodeQueue.push(currNode->pLeft);
        if (currNode->pRight)
            nodeQueue.push(currNode->pRight);
    }
}

//Hàm kiểm tra 1 giá trị có tồn tại trong cây AVL không
bool isExsited(NODE* pRoot, int x){
    if (!pRoot)
        return false;
    bool result;
    if (pRoot->key == x)
        result = true;
    else if (pRoot->key > x)
        result = isExsited(pRoot->pLeft, x);
    else if (pRoot->key < x)
        result = isExsited(pRoot->pRight, x);
    return result;
}

//4. Hàm kiểm tra cây có phải cây AVL không
bool isAVL(NODE* pRoot){
    if (!pRoot)
        return true;

    int lh = height(pRoot->pLeft);
    int rh = height(pRoot->pRight);

    return (abs(lh - rh) <= 1) && isAVL(pRoot->pLeft) && isAVL(pRoot->pRight);
}

// Hàm đếm số Node có trong cây
int countNode(NODE* pRoot){
    if (!pRoot) 
        return 0;
    
    int a = countNode(pRoot->pLeft);
    int b = countNode(pRoot->pRight);
    return 1 + a + b;
}

//Hàm hủy cây AVL
void destroyTree(NODE* &pRoot) {
    while (countNode(pRoot) != 0)
        Remove(pRoot, pRoot->key);
    pRoot = NULL;
}