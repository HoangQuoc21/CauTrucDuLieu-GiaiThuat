#include <iostream>
using namespace std;

typedef struct Node* ptrNode;

struct Node {
    int data;
    ptrNode pNext;
};

struct List {
    ptrNode pHead;
    ptrNode pTail;
};

void initList(List &l){
    l.pHead = NULL;
    l.pTail = NULL;
}

bool isEmpty(List &l){
    return (l.pHead == NULL && l.pTail == NULL);
}

ptrNode createNode(int x){
    ptrNode p = new Node;
    p->data = x;
    p->pNext = NULL;
    return p;
}

void insertHead(List &l, int x ){
    ptrNode p = createNode(x);
    if (isEmpty(l))
        l.pHead = l.pTail = p;
    else{
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

void insertTail(List &l, int x ){
    ptrNode p = createNode(x);
    if (isEmpty(l))
        l.pTail = l.pHead = p;
    else{
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

void insertAfter(List &l, ptrNode q, int x){
    ptrNode p = createNode(x);
    p->pNext = q->pNext;
    q->pNext = p;
    if (l.pTail == q)
        l.pTail = p;
}



void insertBefore(List &l, ptrNode q, int x){
    if (l.pHead == q)
        insertHead(l,x);
    else{
        ptrNode p = createNode(x);
        *p = *q;
        q->pNext = p;
        q->data = x;
        if(l.pTail == q)
            l.pTail = p;
    }
}

void print(List l){
    ptrNode p = l.pHead;
    while (p){
        if(p->pNext == NULL)
            cout << p->data;
        else
            cout << p->data << " -> ";
        p = p->pNext;
    }
    cout << endl;
    //for (ptrNode p = l.pHead; p; p = p->next)
        //cout << p->data << " ";
}

void deleteHead(List &l){
    if (l.pHead == l.pTail){
        delete l.pHead;
        l.pHead = l.pTail = NULL;
    }
    else{
        ptrNode p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
    }
    
}

void deleteTail (List &l){
    if (l.pHead == l.pTail){
        delete l.pTail;
        l.pHead = l.pTail = NULL;
    }
    else{
        ptrNode p = l.pHead;
        while (p->pNext != l.pTail)
            p = p->pNext;
        delete l.pTail;
        p->pNext = NULL;
        l.pTail = p;
    }
}

void deleteNode (List &l, ptrNode deletingNode){
    if (deletingNode == l.pHead)
        deleteHead(l);
    else if (deletingNode == l.pTail)
        deleteTail(l);
    else{
        ptrNode tempNode  = deletingNode->pNext;
        *deletingNode = *tempNode;
        delete tempNode;
    }   
}

void removebefore(List &list, ptrNode currNode){
    if (isEmpty(list) || currNode == NULL)
        return;
    else if (list.pHead->pNext == currNode)
        deleteHead(list);
    else{
        //beforeNode -> deleteNode -> currNode
        ptrNode beforeNode = list.pHead;
        ptrNode deleteNode;

        while(beforeNode->pNext->pNext == currNode)
            beforeNode = beforeNode->pNext;

        deleteNode = beforeNode->pNext;
        beforeNode->pNext = currNode;
        deleteNode->pNext = NULL;
        delete deleteNode;
    }
}

void deleteList(List &l){
    ptrNode tempNode1;
    ptrNode tempNode2 = l.pHead;
    while (tempNode2){
        tempNode1 = tempNode2;
        tempNode2 = tempNode1->pNext;
        delete tempNode1;
    }
    l.pHead = l.pTail = NULL;
}

ptrNode findItembyData (List l, int x){
    ptrNode p = l.pHead;
    while (p){
        if (p->data == x)
            break;
        p = p->pNext;
    }
    return p;
}

ptrNode findItemByIndex (List l, int i){
   ptrNode p = l.pHead;
   int temp = 0;
   while (p){
    if (temp == i)
        break;
    else{
        p = p->pNext;
        temp++;
    }
   }
   return p;
}

void checkPositive (int &number){
    while (number <= 0){
        cout << "So duong da nhap khong hop le. Hay nhap lai: ";
        cin >> number;
    }
}

void checkPosition(int &index, int n){
    if (index <= 0 || index > n ){
        cout << "Vi tri da nhap khong hop le. Hay nhap lai: ";
        cin >> index;
    }
}

int countNumberOfValue(List l, int x){
    ptrNode p = l.pHead;
    int count = 0;
    while(p){
        if (p->data == x)
            count++;
        p = p->pNext;
    }
    return count;
}

void createListFromArray(List &l, int a[], int n){
    for (int i = 0; i < n; i++){
        insertTail(l, a[i]);
    }
}

void create2NewLinkedList(List originalList, List &newList1, List &newList2){
    ptrNode temp = originalList.pHead;
    while(temp){
        //Lẻ
        if((temp->data %2) != 0)
            insertTail(newList1, temp->data);
        //Chẵn
        else
            insertTail(newList2, temp->data);
        temp = temp->pNext;
    }
}

void MoveToFront(ptrNode &Head, ptrNode &Tail, ptrNode MovingNode){
    if (MovingNode == Head)
        return;
    else if (MovingNode == Tail){
        ptrNode temp = Head;
        while(temp->pNext->pNext != NULL)
            temp = temp->pNext;
        temp->pNext = NULL;
        Tail = temp;
        MovingNode->pNext = Head;
        Head = MovingNode;
    }
    else{
        ptrNode temp = Head;
        while(temp->pNext != MovingNode)
            temp = temp->pNext;
        temp->pNext = temp->pNext->pNext;
        MovingNode ->pNext = Head;
        Head = MovingNode;
    }
}

void reverseList(List &list){
    if (isEmpty(list))
        return;
    else{
        ptrNode prevNode = NULL;
        ptrNode nextNode = NULL;
        ptrNode currNode = list.pHead;
        while(currNode){
            nextNode = currNode->pNext;
            currNode->pNext = prevNode;
            prevNode = currNode;
            currNode = nextNode;
        }
        list.pHead = prevNode;
    }
}

int countNode (List list){
    int count = 0;
    if (!isEmpty(list)){
        ptrNode tempNode = list.pHead;
        while(tempNode){
            count++;
            tempNode = tempNode->pNext;
        }
    }
    return count;
}

void findKNode(List list, int k){
    //Nếu tính vị trí của Node đầu tiên là 0
    if (k-1 < 0 || k - 1 >= countNode(list)|| isEmpty(list))
        return;
    else{
        int count = 0;
        ptrNode tempNode = list.pHead;
        while(count != k){
            tempNode = tempNode->pNext;
            count++;
        }
        cout << &tempNode;
    }
}


int main(){
    int n;
    string choice;
    List l;
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
        print(l);
        cout << "==========================MENU==========================\n";
        cout << "1. Them Node vao dau DSLK.\n";
        cout << "2. Them Node vao cuoi DSLK.\n";
        cout << "3. Them Node vao vi tri bat ki.\n";
        cout << "4. Xoa Node o dau DSLK.\n";
        cout << "5. Xoa Node o cuoi DSLK.\n";
        cout << "6. Xoa Node theo vi tri.\n";
        cout << "7. Xoa Node theo gia tri.\n";
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
            if (isEmpty(l) == 0){
                int index, data;
                cout << "-Nhap vao vi tri muon them Node: ";
                cin >> index;
                checkPosition(index,n);
                index = index - 1; 
                cout << "-Nhap vao gia tri cua Node muon them: ";
                cin >> data;
                insertBefore(l, findItemByIndex(l, index), data);
                n++;
                cout << "Da them Node vao vi tri " << index + 1 << ".\n";
            }
            else
                cout << "DSLK hien dang trong. Hay them Node vao vi tri dau hoac cuoi DSLK truoc.\n";
           
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
            if (isEmpty(l) == 0){
                deleteTail(l);
                n--;
                cout << "Da xoa Node o cuoi DSLK.\n";
            }
            else
                cout << "DSLK trong nen khong xoa Node nao duoc.\n";
 
        }
        else if (choice == "6"){
            if (isEmpty(l) == 0){
                int index;
                cout << "-Nhap vao vi tri Node muon xoa: ";
                cin >> index;
                checkPosition(index,n);
                index = index - 1;
                deleteNode(l, findItemByIndex(l,index));
                n--;
                cout << "Da xoa Node tai vi tri " << index + 1 << ".\n";
            }
            else
               cout << "DSLK trong nen khong xoa Node nao duoc.\n"; 
            
        }
        else if (choice == "7"){
            if (isEmpty(l) == 0){
                int data;
                cout << "-Nhap vao gia tri Node muon xoa: ";
                cin >> data;
                while (countNumberOfValue(l,data) == 0){
                    cout << "Khong co Node nao mang gia tri da nhap. Hay nhap lai: ";
                    cin >> data;
                }
                while (countNumberOfValue(l,data) > 0){
                    deleteNode(l, findItembyData(l,data));
                    n--;
                }
                cout << "Da xoa nhung Node co gia tri " << data << ".\n";
            }
            else
                cout << "DSLK trong nen khong xoa Node nao duoc.\n";  
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