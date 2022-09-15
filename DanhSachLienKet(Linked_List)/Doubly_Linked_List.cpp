#include <iostream>
using namespace std;

typedef struct Node* ptrNode;

struct Node{
    int data;
    ptrNode pNext;
    ptrNode pPrev;
};

struct DList{
    ptrNode pHead;
    ptrNode pTail;
};

void initDList(DList &list){
    list.pHead == NULL;
    list.pTail == NULL;
}

bool isEmpty(DList &list){
    if (list.pHead == NULL)
        return true;
    return false;
}

ptrNode createNode(int x){
    ptrNode newNode = new Node;
    if (newNode == NULL)
        return NULL;
    newNode->data = x;
    newNode->pNext = NULL;
    newNode->pPrev = NULL;
    return newNode;   
}



void insertHead(DList &list, int x){
    ptrNode newNode = createNode(x);
    if (isEmpty(list) == true)
        list.pHead = list.pTail = newNode;
    else{
        newNode->pNext = list.pHead;
        list.pHead->pPrev = newNode;
        list.pHead = newNode;
    }
}

void insertTail(DList &list, int x){
    ptrNode newNode = createNode(x);
    if (isEmpty(list) == true)
        list.pHead = list.pTail = newNode;
    else{
        list.pTail->pNext = newNode;
        newNode->pPrev = list.pTail;
        list.pTail = newNode;
    }
}

void insertAfter(DList &list, ptrNode baseNode, int x){
    if (list.pTail == baseNode)
        insertTail(list, x);
    else{
        ptrNode newNode = createNode(x);
        ptrNode nextNode = baseNode->pNext;
        baseNode->pNext = newNode;
        newNode->pPrev = baseNode;
        newNode->pNext = nextNode;
        if (nextNode!=NULL)
            nextNode->pPrev = newNode;
    }
}

void insertBefore(DList &list, ptrNode baseNode, int x){
    if (list.pHead == baseNode)
        insertHead(list, x);
    else{
        ptrNode newNode = createNode(x);
        ptrNode prevNode = baseNode->pPrev;

        prevNode->pNext = newNode;
        newNode->pPrev = prevNode;
        newNode->pNext = baseNode;
        baseNode->pPrev = newNode;
    }
}

void removeHead(DList &list){
    if (isEmpty(list))
        return;
    else{
        ptrNode temp = list.pHead;
        list.pHead = list.pHead->pNext;
        list.pHead->pPrev = NULL;
        delete temp;
        if (list.pHead == NULL) 
            list.pTail = NULL;
        else
            list.pTail->pNext = NULL;
    }
}

void removeTail(DList &list){
    if (isEmpty(list))
        return;
    else{
        ptrNode temp = list.pTail;
        list.pTail = list.pTail->pPrev;
        list.pTail->pNext = NULL;
        delete temp;
        if (list.pHead == NULL)
            list.pTail == NULL;
        else
            list.pHead->pPrev == NULL;
    }
}

void removeAfter(DList &list,ptrNode beforeNode){
    if (isEmpty(list) || beforeNode == NULL)
        return;
    else if (beforeNode->pNext == list.pTail)
        removeTail(list);
    else{
        // beforeNode -> deleteNode -> AfterNode
        ptrNode deleteNode = beforeNode->pNext;
        ptrNode afterNode = beforeNode->pNext->pNext;

        beforeNode->pNext = afterNode;
        afterNode->pPrev = beforeNode;
        deleteNode->pNext = deleteNode->pPrev = NULL;

        delete deleteNode;
    }

}

void removeBefore(DList &list,ptrNode afterNode){
    if (isEmpty(list) || afterNode == NULL)
        return;
    else if(afterNode->pPrev == list.pHead)
        removeHead(list);
    else{
        // beforeNode -> deleteNode -> AfterNode
        ptrNode deleteNode = afterNode->pPrev;
        ptrNode beforeNode = afterNode->pPrev->pPrev;

        afterNode->pPrev = beforeNode;
        beforeNode->pNext = afterNode;
        deleteNode->pNext = deleteNode->pPrev = NULL;

        delete deleteNode;
    }
}

void removeNode(DList &list, int k){
    if (k == list.pHead->data)
        removeHead(list);
    else if (k == list.pTail->data)
        removeTail(list);
    else{
        // beforeNode -> deleteNode -> AfterNode
        ptrNode deleteNode = list.pHead;
        //Tìm node của khóa k
        while(deleteNode->data != k)
            deleteNode = deleteNode->pNext;

        //Nếu không tìm thấy k
        if (deleteNode == NULL)
            return ;
        else{
            ptrNode beforeNode = deleteNode->pPrev;
            ptrNode afterNode = deleteNode->pNext;

            beforeNode->pNext = afterNode;
            afterNode->pPrev = beforeNode;
            deleteNode->pNext = beforeNode->pPrev = NULL;

        delete deleteNode;
        }
    }
}

void destroyDList(DList &list){
    if (isEmpty(list))
        return;
    else{
         ptrNode temp1 = list.pHead;
        ptrNode temp2;
        //temp2 -> temp1 -> NULL
        while(temp1->pNext != NULL){
            temp2 = temp1;
            temp1 = temp1->pNext;
            delete temp2;
        }
    list.pHead = list.pTail = NULL;
    }
}

void printList(DList list){
    ptrNode temp = list.pHead;
    while(temp){
        cout << temp->data << " <-> ";
        temp = temp->pNext;
    }
    cout << endl;
}

void checkPositive (int &number){
    while (number <= 0){
        cout << "So duong da nhap khong hop le. Hay nhap lai: ";
        cin >> number;
    }
}

int main(){
    string choice;
    DList list;
    int nNode;

    //initDList(list);

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
        cout << "DSLK da nhap: ";
        printList(list);
        system("pause");
    }
    destroyDList(list);
    return 0;
}