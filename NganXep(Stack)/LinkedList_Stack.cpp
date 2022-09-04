#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct Node* ptrNode;

struct Node{
    int data;
    ptrNode pNext;
};

struct Stack{
    ptrNode top;
};

ptrNode createNode (int x){
    ptrNode newNode = new Node;
    if (newNode == NULL)
        return NULL;
    else{
        newNode->data = x;
        newNode->pNext = NULL;
        return newNode;
    } 
}

//Khởi tạo stack
void initStack(Stack &stack){
    stack.top = NULL;
}

//Kiểm tra stack rỗng/ đầy
bool isEmpty (Stack stack){
    if (stack.top == NULL)
        return true;
    else
        return false;
}

bool isFull (Stack stack){
    if (stack.top->pNext == NULL)
        return true;
    else
        return false;
}

//Push: Đẩy phần tử mới vào đỉnh stack (tương tụ thêm Node mới vào đầu DSLK đơn)
void Push (Stack &stack, int x){
    ptrNode newNode = createNode(x);
    if (newNode != NULL){
        if (isEmpty(stack) == true)
            stack.top = newNode;
        else{
            newNode->pNext = stack.top;
            stack.top = newNode; 
        }
    }
   
}

//Pop: Lấy phần tử từ đỉnh stack
int Pop(Stack &stack){
    if (isEmpty(stack) == true)
        return 0;
    else{
        ptrNode tempNode = stack.top;
        int data = tempNode->data;
        stack.top = tempNode->pNext;
        delete tempNode;
        return data;
    }
}

//Đọc nội dung đỉnh stack
int Top(Stack stack){
    if (isEmpty(stack) == true)  
        return 0;
    else
        return stack.top->data;
}

//Hủy ngăn xếp
void deleteStack (Stack &stack){
    ptrNode tempNode = stack.top;
    while (stack.top != NULL){
        stack.top = tempNode->pNext;
        delete tempNode;
        tempNode = stack.top;
    }
}

//In ngăn xếp
void printStack(Stack stack){
    ptrNode tempNode = stack.top;
    while (tempNode != NULL){
        if (tempNode->pNext == NULL){
            cout << "\t\t      | " << tempNode->data <<" |" << endl;
        }
        else    
            cout << "\t\t      | " << tempNode->data <<" |" << endl;
        tempNode = tempNode->pNext;
    }
}

int main(){
    string choice;
    Stack stack;
    initStack(stack);
    while (choice != "0"){
        system("cls");
        cout << "==================== Ngan Xep ==================\n";
        cout << "Ngan xep da nhap: \n";
        printStack(stack);
        cout << "===================== MENU =====================\n";
        cout << "1. Push 1 phan tu vao ngan xep.\n";
        cout << "2. Pop phan tu o dinh ngan xep ra.\n";
        cout << "3. Doc noi dung phan tu o dinh ngan xep.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "===================== END ======================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cout << "------------------------------------------------\n";
        if (choice == "1"){
            int data;
            cout << "Nhap vao du lieu phan tu muon Push: ";
            cin >> data;
            Push(stack, data);
            cout << "Da Push phan tu vao ngan xep.\n";
        }
        else if (choice == "2"){
            Pop(stack);
            cout << "Da Pop phan tu tren dinh ngan xep ra.\n";
        }
        else if (choice == "3"){
            cout << "Gia tri phan tu tren dinh ngan xep la: " << Top(stack) << endl;
        }
        else if (choice == "0"){
            cout << "Thoat chuong trinh.\n";
        }
        else
            cout << "Lua chon khong hop le.\n";

        system("pause");
    }

    deleteStack(stack);
    return 0;
}