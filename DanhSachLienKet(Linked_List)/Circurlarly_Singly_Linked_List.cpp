#include <iostream>
using namespace std;

struct node{
    int data;
    node* pNext;
};

typedef node* ptrNode;

struct list{
    ptrNode pHead;
    ptrNode pTail;
};

ptrNode createNode (int x){
    ptrNode newNode = new node;
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}

void initList(list &list){
    list.pHead = list.pTail = NULL;
}

bool isEmpty(list list){
    return ( list.pHead == NULL);
}

//Tìm phần tử trên DS vòng
ptrNode searchNode(list list, int x){
    if (!isEmpty(list)){
        ptrNode temp = list.pHead;
        do{
            if (temp->data == x){
                return temp;
                break;
            }
            temp = temp->pNext;
        }while(temp != list.pHead);
    }
    return NULL;
}

//Thêm phần tử vào đầu
void insertHead(list &list, int x){
    ptrNode newNode = createNode(x);
    if (isEmpty(list)){
        list.pHead = list.pTail = newNode;
        list.pTail->pNext = list.pHead;
    }
       
    else{
        list.pTail->pNext = newNode;
        newNode->pNext = list.pHead;
        list.pHead = newNode;
    }
}

//Thêm phần tử vào cuối
void insertTail(list &list, int x){
    ptrNode newNode = createNode(x);
    if( isEmpty(list) ){
        list.pHead = list.pTail = newNode;
        list.pTail->pNext = list.pHead;
    }
    else{
        list.pTail->pNext = newNode;
        newNode->pNext = list.pHead;
        list.pTail = newNode;
    }
}
//Thêm phần tử sau 1 Node
void insertAfter(list &list, ptrNode currNode, int x){
    ptrNode newNode = createNode(x);
    if (isEmpty(list)){
        list.pHead = list.pTail = newNode;
        list.pTail->pNext = list.pHead;
    }
    else if (currNode != NULL){
        // currNode -> newNode
        newNode->pNext = currNode->pNext;
        currNode->pNext = newNode;
        //Nếu currNode là Node cuối (list.pTail)
        if (currNode == list.pTail)
            list.pTail = newNode;
    }
}

//Xóa phần tử ở đầu
void deleteHead(list &list){
    if(isEmpty(list))
        return;
    //Nếu DS chỉ có 1 Node
    else if(list.pHead == list.pTail)
        list.pHead = list.pTail = NULL;
    else{
        ptrNode deleteNode = list.pHead;
        list.pHead = list.pHead->pNext;
        list.pTail->pNext = list.pHead;

        deleteNode->pNext = NULL;
        delete deleteNode;
    }
}

//Xóa phần tử đứng sau 1 Node
void deleteAfter(list &list, ptrNode currNode){
    if(isEmpty(list))
        return;
    //Nếu DS chỉ có 1 Node
    else if(list.pHead == list.pTail)
        list.pHead = list.pTail = NULL;
    else if (currNode != NULL){
        ptrNode deleteNode = currNode->pNext;
        currNode->pNext = deleteNode->pNext;
        //Nếu chỉ có 2 Node
        if (list.pHead == list.pTail)
            list.pTail->pNext = list.pHead;
        
        deleteNode->pNext = NULL;
        delete deleteNode;
    }
}

void deleteList(list &list){
    ptrNode tempNode1 = list.pHead;
    ptrNode tempNode2;
    do{
        tempNode2 = tempNode1;
        tempNode1 = tempNode1->pNext;
        delete tempNode2;
    }while(tempNode1 != list.pHead);
    list.pHead = list.pTail = NULL;
}

//In DSLK
void printList(list list){
    if (isEmpty(list))
        return;
    else{
        ptrNode temp = list.pHead;
        do{
            cout << temp->data << " ";
            temp = temp->pNext;
        }while(temp != list.pHead);
    }
    cout << endl;
}

void checkPositive(int &n){
    while(n <= 0){
        cout << "So duong da nhao khong hop le. Hay nhap lai: ";
        cin >> n;
    }
}

int main(){
    int n;
    string choice;
    list l;
    initList(l);

    system("cls");
    cout << "=================DANH SACH LIEN KET(DON)================\n";
    cout << "Dau tien hay nhap vao so luong node: ";
    cin >> n;
    checkPositive(n);
    cout << "========================================================\n";
    for (int i = 0; i < n; i++){
        int data;
        cout << "Nhap du lieu cua Node " << i + 1 << " : ";
        cin >> data;
        insertTail(l,data);
    }


   
    while (choice != "0"){
        system("cls");
        cout << "=================DANH SACH LIEN KET(DON)================\n";
        cout << "So luong Node hien co: " << n << endl;
        cout << "DSLK da nhap: ";
        printList(l);
        cout << "==========================MENU==========================\n";
        cout << "1. Them Node vao dau DSLK.\n";
        cout << "2. Them Node vao cuoi DSLK.\n";
        cout << "3. Them Node vao sau 1 Node.\n";
        cout << "4. Xoa Node o dau DSLK.\n";
        cout << "5. Xoa Node dung sau 1 Node.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "==========================END===========================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cout << "------------------------------------------------\n";
        if (choice == "1"){
            int data;
            cout << "Nhap vao du lieu cua Node: ";
            cin >> data;
            insertHead(l,data);
            n++;
            cout << "Da them Node vao dau DSLK.\n";
        }
        else if (choice == "2"){
            int data;
            cout << "Nhap vao du lieu cua Node: ";
            cin >> data;
            insertTail(l,data);
            n++;
            cout << "Da them Node vao cuoi DSLK.\n";
        }
        else if (choice == "3"){
            int x,data;
            cout << "Nhap vao du lieu Node muon them dang sau: ";
            cin >> x;
            cout << "Nhap vao du lieu Node muon them dang sau: ";
            cin >> data;
            insertAfter(l,searchNode(l,x),data);
           
        }
        else if (choice == "4"){
            if (isEmpty(l) == 0){
                deleteHead(l);
                n--;
                cout << "Da xoa Node o dau DSLK.\n";
            }
            else
                cout << "DSLK trong nen khong xoa Node nao duoc.\n";
            
        }
        else if (choice == "5"){
            int x,data;
            cout << "Nhap vao du lieu Node muon xoa dang sau: ";
            cin >> x;
            deleteAfter(l,searchNode(l,x));
        }
        else if (choice == "0"){
            cout << "Thoat chuong trinh.\n";
            exit(0);
        }
        else
            cout << "Lua chon khong hop le.\n";

        
        system("pause");
    }

    deleteList(l);
    return 0;
}