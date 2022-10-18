#include <iostream>
#include "doublyLinkedList.h"
#include "stack_queue.h"
using namespace std;
//================== MENU FUNCTIONS ================
void doublyLinkedList(){
    system("cls");
    int nNode;
    cout << "==================== DOUBLY LINKED LIST =================\n";
    cout << "Nhap vao so so luong Node cua DSLK: ";
    cin >> nNode;
    DList* list;
    for (int i = 0; i < nNode; i++){
        int key;
        cout << "Nhap vao key cua Node " << i+1 << ": ";
        cin >> key;
        if (i == 0)
            list = createList(createDNode(key));
        else
            addTail(list, key);
    }
    while(1){
        string choice;
        system("cls");
        cout << "==================== DOUBLY LINKED LIST =================\n";
        cout << "So luong Node hien co: " << countElements(list) << endl;
        cout << "DSLK da nhap: ";
        printList(list);
        cout << "\n====================== DLL MENU ========================\n";
        cout << "1. Them Node vao DSLK:\n";
        cout << "\t1a.Them Node vao dau DSLK.\n";
        cout << "\t1b.Them Node vao cuoi DSLK.\n";
        cout << "\t1c.Them Node vao mot vi tri trong DSLK \n\t(vi tri trong DSLK nay bat dau tu 0).\n";
        cout << "\t1d.Them Node vao truoc mot Node trong DSLK.\n";
        cout << "\t1e.Them Node vao sau mot Node trong DSLK.\n";
        cout << "2. Xoa Node khoi DSLK:\n";
        cout << "\t2a. Xoa Node dau trong DSLK.\n";
        cout << "\t2b. Xoa Node cuoi trong DSLK.\n";
        cout << "\t2c. Xoa Node truoc mot Node trong DSLK.\n";
        cout << "\t2d. Xoa Node sau mot Node trong DSLK.\n";
        cout << "\t2e. Xoa Node tai mot vi tri trong DSLK.\n\t(vi tri trong DSLK nay bat dau tu 0).\n";
        cout << "\t2f. Xoa nhung Node co gia tri trung nhau trong DSLK.\n";
        cout << "\t2g. Xoa tat ca Node co gia tri duoc chon trong DSLK.\n";
        cout << "3. Dao nguoc DSLK.\n";
        cout << "0. Quay tro lai MAIN MENU.\n";
        cout << "========================= END ==========================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cout << "------------------------------------------------\n";
        if (choice == "1a"){
            int data;
            cout << "Nhap vao du lieu cua Node: ";
            cin >> data;
            if (addHead(list,data))
                cout << "Them Node vao dau DSLK thanh cong.\n";
            else
                cout << "Them Node vao dau DSLK khong thanh cong.\n";
        }
        else if (choice == "1b"){
            int data;
            cout << "Nhap vao du lieu cua Node: ";
            cin >> data;
            if (addTail(list,data))
                cout << "Them Node vao cuoi DSLK thanh cong.\n";
            else
                cout << "Them Node vao cuoi DSLK khong thanh cong.\n";
        }
        else if (choice == "1c"){
            if (isEmpty(list) == 0){
                int pos, data;
                cout << "-Nhap vao vi tri muon them Node: ";
                cin >> pos;
                while(!checkPos(list, pos)){
                    cout << "Vi tri khong hop le. Hay nhap lai: ";
                    cin >> pos;
                } 
                cout << "-Nhap vao gia tri cua Node muon them: ";
                cin >> data;
                if(addPos(list, data, pos))
                    cout << "Them Node vao vi tri " << pos << " thanh cong.\n";
                else
                    cout << "Them Node vao vi tri " << pos << " khong thanh cong.\n";
            }
            else
                cout << "DSLK hien dang trong. Hay them Node vao vi tri dau hoac cuoi DSLK truoc.\n";
        }
        else if (choice == "1d"){
            int data,val;
            cout << "Nhap vao du lieu cua Node muon them truoc: ";
            cin >> val;
            cout << "Nhap vao du lieu cua Node muon them: ";
            cin >> data;
            if (addBefore(list,data, val))
                cout << "Them Node " << data << " vao truoc Node " << val << " thanh cong.\n"; 
            else
                cout << "Them Node " << data << " vao truoc Node " << val << " khong thanh cong.\n"; 
        }
        else if (choice == "1e"){
             int data,val;
            cout << "Nhap vao du lieu cua Node muon them sau: ";
            cin >> val;
            cout << "Nhap vao du lieu cua Node muon them: ";
            cin >> data;
            if (addAfter(list,data, val))
                cout << "Them Node " << data << " vao sau Node " << val << " thanh cong.\n"; 
            else
                cout << "Them Node " << data << " vao sau Node " << val << " khong thanh cong.\n"; 
        }
        else if (choice == "2a"){
            if(!isEmpty(list)){
                removeHead(list);
                cout << "Da xoa Node o dau.\n";
            }
            else
                cout << "DSLK rong.\n";
        }
        else if (choice == "2b"){
            if (!isEmpty(list)){
                removeTail(list);
                cout << "Da xoa Node o cuoi.\n";
            }
            else
                cout << "DSLK rong.\n";
        }
        else if (choice == "2c"){
            int val;
            cout << "Nhap vao gia tri Node ban muon xoa truoc: ";
            cin >> val;
            if(countVal(list, val) == 0)
                cout << "Khong ton tai gia tri nay trong DSLK.\n";
            else if (countVal(list, val) == 1 && countElements(list) == 1)
                cout << "Chi co 1 Node mang gia tri " << val << " va chi co Node do ton tai trong DSLK.\n";
            else{
                removeBefore(list,val);
                cout << "Da xoa nhung Node truoc Node co gia tri " << val << endl;
            }
        }
        else if (choice == "2d"){
            int val;
            cout << "Nhap vao gia tri Node ban muon xoa sau: ";
            cin >> val;
            if(countVal(list, val) == 0)
                cout << "Khong ton tai Node mang gia tri nay trong DSLK.\n";
            else if (countVal(list, val) == 1 && countElements(list) == 1)
                cout << "Chi co 1 Node mang gia tri " << val << " va chi co Node do ton tai trong DSLK.\n";
            else{
                removeAfter(list,val);
                cout << "Da xoa nhung Node sau Node co gia tri " << val << endl;
            }
        }
        else if (choice == "2e"){
            int pos;
            cout << "Nhap vao vi tri Node ban muon xoa: ";
            cin >> pos;
            while(!checkPos(list, pos)){
                cout << "Vi tri khong hop le. Hay nhap lai: ";
                cin >> pos;
            }
            removePos(list, pos);
            cout << "Da thanh cong xoa Node tai vi tri " << pos << " khoi DSLK.\n";
        }
        else if (choice == "2f"){
            if (isEmpty(list))
                cout << "DSLK rong.\n";
            else{
                removeDuplicate(list);
                cout << "Da xoa nhung Node co gia tri trung nhau.\n";
            }
        }
        else if (choice == "2g"){
            int val;
            cout << "Nhap vao gia tri cua nhung Node ban muon xoa: ";
            cin >> val;
            if(countVal(list, val) == 0)
                cout << "Khong ton tai Node mang gia tri nay trong DSLK.\n";
            else{
                if (countVal(list, val) == 1 && countElements(list) == 1){
                    removeHead(list);
                    cout << "Da xoa thanh cong nhung Node co gia tri " << val << " khoi DSLK.\n";
                }
                else if (removeElement(list, val))
                    cout << "Da xoa thanh cong nhung Node co gia tri " << val << " khoi DSLK.\n";
                else
                    cout << "Da khong thanh cong xoa nhung Node co gia tri " << val << " khoi DSLK.\n";
            }
        }
        else if (choice == "3"){
            reverseList(list);
            cout << "Da dao nguoc DSLK.\n";
        }
        else if (choice == "0"){
            removeAll(list);
            delete list;
            break;
        }
        else
            cout << "Lua chon khong hop le.\n";
        system("pause");
    }
}

void stack(){
    system("cls");
    Stack stack;
    int firstKey;
    cout << "Nhap vao gia tri Push vao dau tien cua Stack: ";
    cin >> firstKey;
    initStack(stack, firstKey);
    while (1){
        string choice;
        system("cls");
        cout << "====================== STACK ====================\n";
        cout << "So luong phan tu trong ngan xep: " << countEStack(stack) << endl;
        cout << "Ngan xep da nhap: \n";
        printStack(stack);
        cout << "=================== STACK MENU ==================\n";
        cout << "1. Push 1 phan tu vao ngan xep.\n";
        cout << "2. Pop phan tu o dinh ngan xep ra.\n";
        cout << "0. Quay tro lai MAIN MENU.\n";
        cout << "====================== END ======================\n";
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
            if (!isSEmpty(stack))
                cout << "Da Pop phan tu tren dinh ngan xep ra. Phan tu do co gia tri: " << Pop(stack) << endl;
            else
                cout << "Ngan xep rong.\n";
        }
        else if (choice == "0"){
            deleteStack(stack);
            break;
        }
        else
            cout << "Lua chon khong hop le.\n";
        system("pause");
    }
}

void queue(){
    Queue queue;
    int firstKey;
    system("cls");
    cout << "Nhap vao gia tri Enqueue vao dau tien cua Queue: ";
    cin >> firstKey;
    initQueue(queue, firstKey);
    while (1){
        string choice;
        system("cls");
        cout << "============================= QUEUQE ==========================\n";
        cout << "So luong phan tu trong hang doi: " << countEQueue(queue) << endl;
        cout << "Hang doi da nhap: \n";
        printQueue(queue);
        cout << "=========================== QUEUE MENU ========================\n";
        cout << "1. Enqueue (Push) mot phan tu vao hang doi.\n";
        cout << "2. Dequeue (Pop) phan tu o dau hang doi ra.\n";
        cout << "0. Quay tro lai MAIN MENU.\n";
        cout << "=============================== END ============================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cout << "--------------------------------\n";
        if (choice == "1"){
            int data;
            cout << "Hay nhap vao gia tri cua phann tu muon Push: ";
            cin >> data;
            Enqueue(queue,data);
            cout << "Da Enqueue phan tu len dau hang doi.\n";
        }
        else if (choice == "2"){
            if (!isQEmpty(queue))
                cout << "Da Dequeue phan tu o dau hang doi ra. Phan tu do co gia tri: "<< Dequeue(queue) << endl;
            else
                cout << "Hang doi rong.\n";
        }
        else if (choice == "0"){
            deleteQueue(queue);
            break;
        }
        else 
            cout << "Lua chon khong hop le.\n";
        system("pause");
    }
}

int main(){
    while(1){
        system("cls");
        string choice;
        cout << "****************************************************************\n";
        cout << "*                           HOME WORK 1                        *\n";
        cout << "****************************************************************\n";
        cout << "============================ MAIN MENU =========================\n";
        cout << "1. DOUBLY LINKED LIST MENU.\n";
        cout << "2. STACK MENU.\n";
        cout << "3. QUEUE MENU.\n";
        cout << "0. THOAT THUONG TRINH.\n";
        cout << "============================== END ============================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        if (choice == "1")
            doublyLinkedList();
        else if (choice == "2")
            stack();
        else if (choice == "3")
            queue();
        else if (choice == "0")
            exit(0);
        else
            cout << "Lua chon khong hop le.\n";
    }
}