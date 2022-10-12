#include <iostream>
using namespace std;

typedef struct Node* ptrNode;

struct Node{
    int data;
    ptrNode pNext;
};

struct Queue{
    ptrNode pHead;
    ptrNode pTail;
};

ptrNode createNode (int x){
    ptrNode newNode = new Node;
    if (newNode == NULL){
        cout << "Khong du bo nho.\n";
        return NULL;
    }
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode; 
}

//Khởi tạo hàng đợi
void initQueue(Queue &queue){
    queue.pHead = NULL;
    queue.pTail = NULL;
}

//Kiểm tra hàng đợi rỗng
bool isEmpty (Queue queue){
    if (queue.pHead == NULL)
        return true;
    else
        return false;
}

//Đẩy phần tử mới vào hàng đợi (Push)
//Phần tử mới luôn được thêm vào cuối hàng đợi
void Push(Queue &queue, int x){
    ptrNode newNode = createNode(x);
    if (isEmpty(queue) == true){
        queue.pHead = newNode;
        queue.pTail = newNode;
    }
    else{
        queue.pTail->pNext = newNode;
        queue.pTail = newNode;
    }
}

//Lấy phần tử ở đỉnh hàng đợi ra(Pop)
int Pop(Queue &queue){
    int x;
    ptrNode tempNode = NULL;
    if (isEmpty(queue) != true){
        tempNode = queue.pHead;
        x = tempNode->data;
        queue.pHead = queue.pHead->pNext;
        delete tempNode;
        if (queue.pHead == NULL){
            queue.pTail == NULL;
        }
    }
    return x;
}

//Đọc nội dung phần tử ở đỉnh hàng đợi (Top)
int Top (Queue queue){
    if (isEmpty(queue) == true)
        return 0;
    else{
        return queue.pHead->data;
    }
}
//Hủy hàng đợi
void deleteQueue(Queue &queue){
    ptrNode tempNode1;
    ptrNode tempNode2 = queue.pHead;
    while (tempNode2){
        tempNode1 = tempNode2;
        tempNode2 = tempNode1->pNext;
        delete tempNode1;
    }
    queue.pHead = queue.pTail = NULL;
}

//In hàng đợi
void printQueue (Queue queue){
    ptrNode tempNode1, tempNode2, tempNode3;
    tempNode1 = tempNode2 = tempNode3 = queue.pHead;
    while (tempNode1 != NULL){
        cout << "--";
        tempNode1 = tempNode1->pNext;
    }
    cout << endl;
    while (tempNode2 != NULL){
        cout << tempNode2->data << " ";
        tempNode2 = tempNode2->pNext;
    }
    cout << endl;
    while (tempNode3 != NULL){
        cout << "--";
        tempNode3 = tempNode3->pNext;
    }
    cout << endl;
}
int main(){
    Queue queue;
    initQueue(queue);
    string choice;
    while (choice != "0"){
        system("cls");
        cout << "============================ HANG DOI ==========================\n";
        cout << "Hang doi da nhap: \n";
        printQueue(queue);
        cout << "============================== MENU ============================\n";
        cout << "1. Push (Enqueue) mot phan tu vao hang doi.\n";
        cout << "2. Pop (Dequeue) phan tu o dau hang doi ra.\n";
        cout << "3. Doc noi dung phan tu o dau hang doi.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "=============================== END ============================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cout << "--------------------------------\n";

        if (choice == "1"){
            int data;
            cout << "Hay nhap vao gia tri cua phann tu muon Push: ";
            cin >> data;
            Push(queue,data);
            cout << "Da Push phan tu len dau hang doi.\n";
        }
        else if (choice == "2"){
            Pop(queue);
            cout << "Da Pop phan tu o dau hang doi ra.\n";
        }
        else if (choice == "3"){
            cout << "Noi dung phan tu o dau hang doi la: " << Top(queue) << endl;;
        }
        else if (choice == "0"){
            cout << "Thoat chuong trinh.\n";
            exit(0);
        }
        else 
            cout << "Lua chon khong hop le.\n";

        system("pause");
    }

    deleteQueue(queue);
    return 0;
}