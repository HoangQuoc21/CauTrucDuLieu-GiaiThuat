#include <iostream>
using namespace std;

struct SNODE{
    int key;
    SNODE* pNext;
};

SNODE* createSNode(int key){
    SNODE* newNode = new SNODE;
    if (newNode){
        newNode->key = key;
        newNode->pNext = NULL;
        return newNode;
    }
    return NULL;
}

//I. STACK
struct Stack{
    SNODE* top;
};

//Khởi tạo stack
void initStack(Stack &stack, int firstKey){
    SNODE* firstNode = createSNode(firstKey);
    stack.top = firstNode;
}

//Kiểm tra stack có rỗng
bool isSEmpty (Stack stack){
    if (stack.top == NULL)
        return true;
    else
        return false;
}

//Push: đẩy 1 phần tử vào stack
void Push (Stack &stack, int x){
    SNODE* newNode = createSNode(x);
    if (newNode != NULL){
        if (isSEmpty(stack) == true)
            stack.top = newNode;
        else{
            newNode->pNext = stack.top;
            stack.top = newNode; 
        }
    }
}

//Pop: Lấy phần tử từ đỉnh stack
int Pop(Stack &stack){
    if (isSEmpty(stack) == true)
        return 0;
    else{
        SNODE* tempNode = stack.top;
        int data = tempNode->key;
        stack.top = tempNode->pNext;
        delete tempNode;
        return data;
    }
}

//Đếm số phần tử trong stack
int countEStack(Stack stack){
    SNODE* tempNode = stack.top;
    int count = 0;
    while(tempNode){
        count++;
        tempNode = tempNode->pNext;
    } 
    return count;
}

//Hủy ngăn xếp
void deleteStack (Stack &stack){
    SNODE* tempNode = stack.top;
    while (stack.top != NULL){
        stack.top = tempNode->pNext;
        delete tempNode;
        tempNode = stack.top;
    }
}

//In ngăn xếp
void printStack(Stack stack){
    SNODE* tempNode = stack.top;
    while (tempNode != NULL){
        if (tempNode->pNext == NULL){
            cout << "\t\t      | " << tempNode->key <<" |" << endl;
        }
        else    
            cout << "\t\t      | " << tempNode->key <<" |" << endl;
        tempNode = tempNode->pNext;
    }
}

//II. QUEUE
struct Queue{
    SNODE* pHead;
    SNODE* pTail;
};

//Khởi tạo hàng đợi
void initQueue(Queue &queue, int firstKey){
    SNODE* firstNode = createSNode(firstKey);
    queue.pHead = queue.pTail = firstNode;
}

//Kiểm tra hàng đợi rỗng
bool isQEmpty (Queue queue){
    if (queue.pHead == NULL)
        return true;
    else
        return false;
}

//Đẩy phần tử mới vào hàng đợi (Push)
//Phần tử mới luôn được thêm vào cuối hàng đợi
void Enqueue(Queue &queue, int x){
    SNODE* newNode = createSNode(x);
    if (isQEmpty(queue) == true){
        queue.pHead = newNode;
        queue.pTail = newNode;
    }
    else{
        queue.pTail->pNext = newNode;
        queue.pTail = newNode;
    }
}

//Lấy phần tử ở đỉnh hàng đợi ra(Pop)
int Dequeue(Queue &queue){
    int x;
    SNODE* tempNode = NULL;
    if (isQEmpty(queue) != true){
        tempNode = queue.pHead;
        x = tempNode->key;
        queue.pHead = queue.pHead->pNext;
        delete tempNode;

        if (queue.pHead == NULL)
            queue.pTail == NULL;
    }
    return x;
}

//Đếm số phần tử trong queue
int countEQueue(Queue queue){
    SNODE* tempNode = queue.pHead;
    int count = 0;
    while(tempNode){
        count++;
        tempNode = tempNode->pNext;
    } 
    return count;
}

//Hủy hàng đợi
void deleteQueue(Queue &queue){
    SNODE* tempNode1;
    SNODE* tempNode2 = queue.pHead;
    while (tempNode2){
        tempNode1 = tempNode2;
        tempNode2 = tempNode1->pNext;
        delete tempNode1;
    }
    queue.pHead = queue.pTail = NULL;
}

//In hàng đợi
void printQueue (Queue queue){
    SNODE* tempNode1, *tempNode2, *tempNode3;
    tempNode1 = tempNode2 = tempNode3 = queue.pHead;
    cout << "\t";
    while (tempNode1 != NULL){
        cout << "--";
        tempNode1 = tempNode1->pNext;
    }
    cout << endl;
    cout << "\t";
    while (tempNode2 != NULL){
        cout << tempNode2->key << " ";
        tempNode2 = tempNode2->pNext;
    }
    cout << endl;
    cout << "\t";
    while (tempNode3 != NULL){
        cout << "--";
        tempNode3 = tempNode3->pNext;
    }
    cout << endl;
}