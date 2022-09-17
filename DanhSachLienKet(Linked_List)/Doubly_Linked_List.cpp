#include <iostream>
using namespace std;
 
struct Node  {
    int data;
    Node* pNext;
    Node* pPrev;
};

typedef Node* ptrNode;

struct Dlist{
    ptrNode pHead;
    ptrNode pTail;
};
 


void initList(Dlist &list){
    list.pHead = list.pTail = NULL;
}
 

ptrNode createNode(int x) {
    ptrNode newNode = new Node;
    newNode->data = x;
    newNode->pPrev = NULL;
    newNode->pNext = NULL;
    return newNode;
};

bool isEmpty(Dlist list){
    return (list.pHead == NULL);
}
 

void insertHead(Dlist &list, int x){
    ptrNode newNode = createNode(x);
    if(isEmpty(list)) {
        list.pHead = newNode;
        list.pTail = newNode;
        return;
    }
    list.pHead->pPrev = newNode;
    newNode->pNext = list.pHead;
    list.pHead = newNode;
}
 

void insertTail(Dlist &list, int x) {
    ptrNode newNode = createNode(x);
    if(isEmpty(list)) {
        list.pHead = newNode;
        list.pTail = newNode;
        return;
    }
    list.pTail->pNext = newNode;
    newNode->pPrev = list.pTail;
    list.pTail = newNode;
}

void insertAfter(Dlist &list, ptrNode currNode, int x){
    if (currNode == list.pTail)
        insertTail(list,x);
    else{
        //currNode -> addNode -> afterNode
        ptrNode addNode = createNode(x);
        ptrNode afterNode = currNode->pNext;

        currNode->pNext = addNode;
        addNode->pPrev = currNode;
        addNode->pNext = afterNode;
        afterNode->pPrev = addNode;
    }
} 

void insertBefore(Dlist &list, ptrNode currNode, int x){
    if (currNode == list.pHead)
        insertHead(list, x);
    else{
        //beforeNode <- addNode <- currNode
        ptrNode addNode =  createNode(x);
        ptrNode beforeNode = currNode->pPrev;

        currNode->pPrev = addNode;
        addNode->pNext = currNode;
        addNode->pPrev = beforeNode;
        beforeNode->pNext = addNode;
    }
}

void removeHead(Dlist &list) {
    if(isEmpty(list)) {
        return;
    }
    list.pHead = list.pHead->pNext;
    list.pHead->pPrev = NULL;
}
 

void removeTail(Dlist &list) {
    if(isEmpty(list)) {
        return;
    }
    list.pTail = list.pTail->pPrev;
    list.pTail->pNext = NULL;
}

void removeAfter(Dlist &list,ptrNode currNode){
    if (currNode->pNext == list.pTail)
        removeTail(list);
    else{
    //currNode -> deleteNode -> nextNode
        ptrNode deleteNode = currNode->pNext;
        ptrNode nextNode = currNode->pNext->pNext;

        currNode->pNext = nextNode;
        nextNode->pPrev = currNode;
        deleteNode->pNext = deleteNode->pPrev = NULL;
        delete deleteNode;
    }
}

void removeBefore(Dlist &list,ptrNode currNode){
    if(currNode->pPrev == list.pHead)
        removeHead(list);
    else{
        //beforeNode <- deleteNode <- currNode
        ptrNode deleteNode = currNode->pPrev;
        ptrNode beforeNode = currNode->pPrev->pPrev;

        currNode->pPrev = beforeNode;
        beforeNode->pNext = currNode;
        deleteNode->pPrev = deleteNode->pNext = NULL;
        delete deleteNode;
    }
}

void removeNode(Dlist &list, int k){
    if (k == list.pHead->data)
        removeHead(list);
    else if (k == list.pTail->data)
        removeTail(list);
    else{
        ptrNode currNode = list.pHead;
        while(currNode){
            if(currNode->data ==k){
                //beforeNode -> currNode -> afterNode;
                ptrNode beforeNode = currNode->pPrev;
                ptrNode afterNode = currNode->pNext;
               
                beforeNode->pNext = afterNode;
                afterNode->pPrev = beforeNode;
                currNode->pNext = currNode->pPrev = NULL;
                delete currNode;
                return;
            }
            currNode = currNode->pNext;
        }
    }
}

void deleteList(Dlist &list){
    ptrNode temp1 = list.pHead;
    ptrNode temp2;
    while(temp1!= NULL){
        temp2 = temp1;
        temp1 = temp1->pNext;
        delete temp2;
    }
    list.pHead = list.pTail = NULL;
}
 


void Print(Dlist list){
    ptrNode temp = list.pHead;
    cout << "DSLK da nhap in xuoi( -> ): \n";
    while(temp){
        if (temp->pNext == NULL)
            cout << temp->data;
        else{
            cout << temp->data << " <-> ";
        }
        temp = temp->pNext;
    }
    cout << endl;
}
 

void ReversePrint(Dlist list) {
    ptrNode temp = list.pTail;
    if(temp == NULL) return; // empty list, exit
    // Traversing backward using prev pointer
    cout << "DSLK da nhap in nguoc( -> ): \n";
    while(temp){
        if (temp->pPrev == NULL)
            cout << temp->data;
        else{
            cout << temp->data << " <-> ";
        }
        temp = temp->pPrev;
    }
    cout << endl;
}

void checkPositive(int &number){
    while (number <= 0){
        cout << "So da nhap khong hop le. Hay nhap lai: ";
        cin >> number;
    }
}
 
int main() {
    

    Dlist list;
    initList(list);
    string choice;
    int nNode;

    system("cls");
    cout << "=================DANH SACH LIEN KET(DOI)================\n";
    cout << "Dau tien hay nhap vao so luong node: ";
    cin >> nNode;
    checkPositive(nNode);
    cout << "========================================================\n";
    for (int i = 0; i < nNode; i++){
        int data;
        cout << "Nhap du lieu cua Node " << i + 1 << " : ";
        cin >> data;
        insertTail(list,data);
    }
    while(choice != "0"){
        system("cls");
        cout << "=================DANH SACH LIEN KET(DOI)================\n";
        cout << "So luong Node hien co: " << nNode << endl;
        Print(list);
        //Quốc lười thêm option vào MENU :D 
        cout << "==========================MENU==========================\n";
        cout << "1. Them Node vao dau DSLK.\n";
        cout << "2. Them Node vao cuoi DSLK.\n";
        cout << "3. \n";
        cout << "4. Xoa Node o dau DSLK.\n";
        cout << "5. Xoa Node o cuoi DSLK.\n";
        cout << "6.\n";
        cout << "7.\n";
        cout << "8. In nguoc DSLK da nhap.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "==========================END===========================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cout << "------------------------------------------------\n";
        if(choice == "1"){
            int data;
            cout << "Nhap vao du lieu cua Node: ";
            cin >> data;
            insertHead(list,data);
            nNode++;
            cout << "Da them Node vao dau DSLK.\n";
        }
        else if (choice == "2"){
            int data;
            cout << "Nhap vao du lieu cua Node: ";
            cin >> data;
            insertTail(list,data);
            nNode++;
            cout << "Da them Node vao cuoi DSLK.\n";
        }
        else if (choice == "3"){
            
        }
        else if (choice == "4"){
            if (isEmpty(list) == 0){
                removeHead(list);
                nNode--;
                cout << "Da xoa Node o dau DSLK.\n";
            }
            else
                cout << "DSLK trong nen khong xoa Node nao duoc.\n";
        }
        else if (choice == "5"){
            if (isEmpty(list) == 0){
                removeTail(list);
                nNode--;
                cout << "Da xoa Node o dau DSLK.\n";
            }
            else
                cout << "DSLK trong nen khong xoa Node nao duoc.\n";
        }
        else if (choice == "6"){

        }
        else if (choice == "7"){

        }
        else if (choice == "8")
            ReversePrint(list);
        else if (choice == "0"){

        }
        else 
            cout << "Lua chon khong hop le.\n";

        system("pause");
    }
   
 
    
    deleteList(list);
    return 0;
}