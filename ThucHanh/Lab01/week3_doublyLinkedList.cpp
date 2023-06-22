#include <iostream>
using namespace std;
//IV. DOUBLY LINKED LIST
struct SNODE {
    int key;
    SNODE* pNext;
    SNODE* pPrev;
};

struct list {
    SNODE* pHead;
    SNODE* pTail;
};

bool isEmpty(list* L){
    return ((L->pHead == NULL) && (L->pTail == NULL));
}

SNODE* createNode(int data){
    SNODE* newNode = new SNODE;
    if (newNode){
        newNode->key = data;
        newNode->pNext = NULL;
        newNode->pPrev = NULL;
        return newNode;
    }
    return NULL;
}

list* createList(SNODE* pNode){
    list* newList = new list;
    if (newList && pNode){
        newList->pHead = newList->pTail = pNode;
        return newList;
    } 
    return NULL;
}

bool addHead(list* &L, int data){
    SNODE* newNode = createNode(data);
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
    SNODE* newNode = createNode(data);
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
    SNODE* deleteNode = L->pHead;
    if (L->pHead == L->pTail)
        L->pHead = L->pTail = NULL;
    else{
        L->pHead = L->pHead->pNext;
        L->pHead->pPrev = NULL;
    }
    delete deleteNode;
}

void removeTail(list* &L){
    SNODE* deleteNode = L->pTail;
    if(L->pHead == L->pTail)
        L->pHead = L->pTail = NULL;
    else{
        L->pTail = L->pTail->pPrev;
        L->pTail->pNext = NULL;
    }
    delete deleteNode;
}

void removeAll(list* &L){
    SNODE* tempNode1;
    SNODE* tempNode2 = L->pHead;
    while(tempNode2){
        tempNode1 = tempNode2;
        tempNode2 = tempNode2->pNext;
        delete tempNode1;
    }
    L->pHead = L->pTail = NULL;
}

int countVal(list *L, int val){
    int count = 0;
    SNODE* tempNode = L->pHead;
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
        SNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            //tempNode -> deleteNode -> valNode
            if (tempNode->pNext->pNext->key == val){
                SNODE* deleteNode = tempNode->pNext;
                SNODE* valNode = deleteNode->pNext;
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
        SNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            //tempNode -> deleteNode -> nextNode
            if(tempNode->key == val){
                SNODE* deleteNode = tempNode->pNext;
                SNODE* nextNode = deleteNode->pNext;
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
        SNODE* tempNode = L->pHead;
        while(tempNode){
            count++;
            tempNode = tempNode->pNext;
        }
    }
    return count;
}

//QUY ƯỚC: vị trí (index) trong danh sách liên kết bắt đầu từ 1;
bool checkPos(list* L, int pos){
    if (!isEmpty(L))
        return (pos > 0 && (pos <= countElements(L)));
    return false;
}

bool addPos(list* &L, int data, int pos){
    if (pos == 1)
        return addHead(L, data);
    else if (pos == countElements(L))
        return addTail(L, data);
    else{
        //thêm Node sau 1 Node
        int curIndex = 1;
        SNODE* tempNode = L->pHead;
        while(curIndex < pos -1  ){
            tempNode = tempNode->pNext;
            curIndex++;
        }
        SNODE* addNode = createNode(data);
        SNODE* nextNode = tempNode->pNext;
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
        SNODE* tempNode = L->pHead;
        while(curIndex < pos -1 ){
            tempNode = tempNode->pNext;
            curIndex++;
        }
        //tempNode -> deleteNode -> nextNode
        SNODE* deleteNode = tempNode->pNext;
        SNODE* nextNode = deleteNode->pNext;
        tempNode->pNext = nextNode;
        nextNode->pPrev = tempNode;
        delete deleteNode;
    }
}

bool addBefore(list* L, int data, int val){
    if(!isEmpty(L) && (countVal(L,val) != 0)){
        SNODE* tempNode = L->pHead;
        while(tempNode->pNext){
            //tempNode -> addNode -> valNode
            if(tempNode->pNext->key == val){
                SNODE* addNode = createNode(data);
                SNODE* valNode = tempNode->pNext;
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
        SNODE* tempNode = L->pHead;
        while(tempNode){
            //tempNode -> addNode -> nextNode
            if(tempNode->key == val){
                SNODE* addNode = createNode(data);
                SNODE* nextNode = tempNode->pNext;
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
    SNODE* tempNode = L->pHead;
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
        SNODE* prevNode = NULL;
        SNODE* currNode = L->pHead;
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
    SNODE* tempNode1 = L->pHead, *tempNode2;
    while(tempNode1 && tempNode1->pNext){
        tempNode2 = tempNode1;
        while(tempNode2->pNext){
            if(tempNode1->key == tempNode2->pNext->key){
                SNODE* dupNode = tempNode2->pNext;
                SNODE* nextNode = dupNode->pNext;
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
        SNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            if (tempNode->pNext->key == key){
                //tempNode -> deleteNode -> nextNode
                SNODE* deleteNode = tempNode->pNext;
                SNODE* nextNode = deleteNode->pNext;
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

//================== DLL MENU FUNCTIONS ================

int main(){
    system("cls");
    int nNode;
    cout << "Nhap vao so so luong Node cua DSLK: ";
    cin >> nNode;
    list* list;
    for (int i = 0; i < nNode; i++){
        int key;
        cout << "Nhap vao key cua Node " << i+1 << ": ";
        cin >> key;
        if (i == 0)
            list = createList(createNode(key));
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
        cout << "\n====================== SLL MENU ========================\n";
        cout << "1. Them Node vao DSLK:\n";
        cout << "\t1a.Them Node vao dau DSLK.\n";
        cout << "\t1b.Them Node vao cuoi DSLK.\n";
        cout << "\t1c.Them Node vao mot vi tri trong DSLK \n\t(vi tri trong DSLK nay bat dau tu 1).\n";
        cout << "\t1d.Them Node vao truoc mot Node trong DSLK.\n";
        cout << "\t1e.Them Node vao sau mot Node trong DSLK.\n";
        cout << "2. Xoa Node khoi DSLK:\n";
        cout << "\t2a. Xoa Node dau trong DSLK.\n";
        cout << "\t2b. Xoa Node cuoi trong DSLK.\n";
        cout << "\t2c. Xoa Node truoc mot Node trong DSLK.\n";
        cout << "\t2d. Xoa Node sau mot Node trong DSLK.\n";
        cout << "\t2e. Xoa Node tai mot vi tri trong DSLK.\n";
        cout << "\t2f. Xoa nhung Node co gia tri trung nhau trong DSLK.\n";
        cout << "\t2g. Xoa tat ca Node co gia tri duoc chon trong DSLK.\n";
        cout << "3. Dao nguoc DSLK.\n";
        cout << "0. Thoat chuong trinh.\n";
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
            exit(0);
        }
        else
            cout << "Lua chon khong hop le.\n";
        system("pause");
    }
}