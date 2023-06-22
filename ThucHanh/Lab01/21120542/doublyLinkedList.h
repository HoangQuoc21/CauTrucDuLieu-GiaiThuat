#include <iostream>
using namespace std;
//I. DOUBLY LINKED LIST
struct DNODE {
    int key;
    DNODE* pNext;
    DNODE* pPrev;
};

struct list {
    DNODE* pHead;
    DNODE* pTail;
};

bool isEmpty(list* L){
    return ((L->pHead == NULL) && (L->pTail == NULL));
}

DNODE* createDNode(int data){
    DNODE* newNode = new DNODE;
    if (newNode){
        newNode->key = data;
        newNode->pNext = NULL;
        newNode->pPrev = NULL;
        return newNode;
    }
    return NULL;
}

list* createList(DNODE* pNode){
    list* newList = new list;
    if (newList && pNode){
        newList->pHead = newList->pTail = pNode;
        return newList;
    } 
    return NULL;
}

bool addHead(list* &L, int data){
    DNODE* newNode = createDNode(data);
    if (newNode){
        if (isEmpty(L))
            L->pHead = L->pTail = newNode;
        else{
            L->pHead->pPrev = newNode;
            newNode->pNext = L->pHead;
            L->pHead = newNode;
        }
        return true;
    }
    return false;
}

bool addTail(list* &L, int data){
    DNODE* newNode = createDNode(data);
    if (newNode){
        if (isEmpty(L))
            L->pHead = L->pTail = newNode;
        else{
            newNode->pPrev = L->pTail;
            L->pTail->pNext = newNode;
            L->pTail = newNode;
        }
        return true;
    }
    return false;
}

void removeHead(list* &L){
    DNODE* deleteNode = L->pHead;
    if (L->pHead == L->pTail)
        L->pHead = L->pTail = NULL;
    else{
        L->pHead = L->pHead->pNext;
        L->pHead->pPrev = NULL;
    }
    delete deleteNode;
}

void removeTail(list* &L){
    DNODE* deleteNode = L->pTail;
    if(L->pHead == L->pTail)
        L->pHead = L->pTail = NULL;
    else{
        L->pTail = L->pTail->pPrev;
        L->pTail->pNext = NULL;
    }
    delete deleteNode;
}

void removeAll(list* &L){
    DNODE* tempNode1;
    DNODE* tempNode2 = L->pHead;
    while(tempNode2){
        tempNode1 = tempNode2;
        tempNode2 = tempNode2->pNext;
        delete tempNode1;
    }
    L->pHead = L->pTail = NULL;
}

int countVal(list *L, int val){
    int count = 0;
    DNODE* tempNode = L->pHead;
    while(tempNode){
        if(tempNode->key == val)
            count++;
        tempNode = tempNode->pNext;
    }
    return count;
}

void removeBefore(list* L, int val){
    if(!isEmpty(L)){
        if (L->pHead->pNext->key == val)
            removeHead(L);
        DNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            //tempNode -> deleteNode -> valNode
            if (tempNode->pNext->pNext->key == val){
                DNODE* deleteNode = tempNode->pNext;
                DNODE* valNode = deleteNode->pNext;
                tempNode->pNext = valNode;
                valNode->pPrev = tempNode;
                delete deleteNode;
            }
            tempNode = tempNode->pNext;
        }
    }
}

void removeAfter(list* L, int val){
    if(!isEmpty(L)){
        if (L->pTail->pPrev->key == val)
            removeTail(L);
        DNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            //tempNode -> deleteNode -> nextNode
            if(tempNode->key == val){
                DNODE* deleteNode = tempNode->pNext;
                DNODE* nextNode = deleteNode->pNext;
                tempNode->pNext = nextNode;
                nextNode->pPrev = deleteNode;
                delete deleteNode;
            }
            tempNode = tempNode->pNext;
        }
    }
}

int countElements(list* L){
    int count = 0;
    if(!isEmpty(L)){
        DNODE* tempNode = L->pHead;
        while(tempNode){
            count++;
            tempNode = tempNode->pNext;
        }
    }
    return count;
}

//QUY ƯỚC: vị trí (index) trong danh sách liên kết bắt đầu từ 0;
bool checkPos(list* L, int pos){
    if (!isEmpty(L))
        return (pos >=0 && (pos < countElements(L)));
    return false;
}

bool addPos(list* &L, int data, int pos){
    if (pos == 0)
        return addHead(L, data);
    else{
        //thêm Node sau 1 Node
        int curIndex = 1;
        DNODE* tempNode = L->pHead;
        while(curIndex < pos ){
            tempNode = tempNode->pNext;
            curIndex++;
        }
        DNODE* addNode = createDNode(data);
        DNODE* nextNode = tempNode->pNext;
        //tempNode -> addNode -> nextNode
        if(addNode){
            tempNode->pNext = addNode;
            addNode->pPrev = tempNode;
            addNode->pNext = nextNode;
            nextNode->pPrev = addNode;
            return true;
        }
    }
    return false;
}

void removePos(list* &L, int pos){
    if(pos == 1)
        removeHead(L);
    else if(pos == countElements(L))
        removeTail(L);
    else{
        //Xóa Node sau 1 Node
        int curIndex = 1;
        DNODE* tempNode = L->pHead;
        while(curIndex < pos -1 ){
            tempNode = tempNode->pNext;
            curIndex++;
        }
        //tempNode -> deleteNode -> nextNode
        DNODE* deleteNode = tempNode->pNext;
        DNODE* nextNode = deleteNode->pNext;
        tempNode->pNext = nextNode;
        nextNode->pPrev = tempNode;
        delete deleteNode;
    }
}

bool addBefore(list* L, int data, int val){
    if(!isEmpty(L) && (countVal(L,val) != 0)){
        DNODE* tempNode = L->pHead;
        while(tempNode->pNext){
            //tempNode -> addNode -> valNode
            if(tempNode->pNext->key == val){
                DNODE* addNode = createDNode(data);
                DNODE* valNode = tempNode->pNext;
                tempNode->pNext = addNode;
                addNode->pPrev = tempNode;
                addNode->pNext = valNode;
                valNode->pPrev = addNode;
                tempNode = tempNode->pNext->pNext;
            }
            else
                tempNode = tempNode->pNext;
        }
        if (L->pHead->key == val)
            return addHead(L, data);
        return true;
    }
    return false;
}

bool addAfter(list* L, int data, int val){
    if(!isEmpty(L) && (countVal(L,val) != 0)){
        DNODE* tempNode = L->pHead;
        while(tempNode){
            //tempNode -> addNode -> nextNode
            if(tempNode->key == val){
                DNODE* addNode = createDNode(data);
                DNODE* nextNode = tempNode->pNext;
                tempNode->pNext = addNode;
                addNode->pPrev = tempNode;
                addNode->pNext = nextNode;
                nextNode->pPrev = addNode;
                tempNode = tempNode->pNext->pNext;
            }
            else
                tempNode = tempNode->pNext;
        }
        if (L->pTail->key == val)
            return addTail(L, data);
        return true;
    }
    return false;
}

void printList(list* L){
    DNODE* tempNode = L->pHead;
    cout << "DSLK da nhap in xuoi( -> ): \n";
    while(tempNode){
        if (tempNode->pNext == NULL)
            cout << tempNode->key;
        else{
            cout << tempNode->key << " <-> ";
        }
        tempNode = tempNode->pNext;
    }
}

list* reverseList(list* L){
    if(!isEmpty(L)){
        L->pTail = L->pHead;
        // prevNode <-> currNode
        DNODE* prevNode = NULL;
        DNODE* currNode = L->pHead;
        while(currNode){
            prevNode = currNode->pPrev;
            currNode->pPrev = currNode->pNext;
            currNode->pNext = prevNode;
            currNode = currNode->pPrev;
        }
        if (prevNode)
            L->pHead = prevNode->pPrev;
    }
    return L;
}

void removeDuplicate(list* &L){
    DNODE* tempNode1 = L->pHead, *tempNode2;
    while(tempNode1 && tempNode1->pNext){
        tempNode2 = tempNode1;
        while(tempNode2->pNext){
            if(tempNode1->key == tempNode2->pNext->key){
                DNODE* dupNode = tempNode2->pNext;
                DNODE* nextNode = dupNode->pNext;
                //tempNode2 -> dupNode -> nextNode
                tempNode2->pNext = nextNode;
                nextNode->pPrev = tempNode2;
                delete dupNode;
            }
            else
                tempNode2 = tempNode2->pNext;
        }
        tempNode1 = tempNode1->pNext;
    }
}

bool removeElement(list* &L, int key){
    if (countVal(L, key) == 1 && countElements(L) == 1){
        removeHead(L);
        return true;
    }
    if(!isEmpty(L) && (countVal(L, key) != 0)){
        DNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            if (tempNode->pNext->key == key){
                //tempNode -> deleteNode -> nextNode
                DNODE* deleteNode = tempNode->pNext;
                DNODE* nextNode = deleteNode->pNext;
                tempNode->pNext = nextNode;
                nextNode->pPrev = tempNode;
                delete deleteNode;
            }
            else 
                tempNode = tempNode->pNext;
        }
        if(L->pHead->key == key)
            removeHead(L);
        if(L->pTail->key == key)
            removeTail(L);
        return true;
    }
    return false;
}