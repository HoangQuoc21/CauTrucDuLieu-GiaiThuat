#include <iostream>
using namespace std;
//I. SINGLY LINKED LIST
struct SNODE {
    int key;
    SNODE* pNext;
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
    }
    delete deleteNode;
}

void removeTail(list* &L){
    SNODE* deleteNode = L->pTail;
    if(L->pHead == L->pTail)
        L->pHead = L->pTail = NULL;
    else{
        SNODE* tempNode = L->pHead;
        while(tempNode->pNext != deleteNode)
            tempNode = tempNode->pNext;
        tempNode->pNext = NULL;
        L->pTail = tempNode;
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

void removeBefore(list* L, int val){
    if(!isEmpty(L)){
        if (L->pHead->pNext->key == val)
            removeHead(L);
        SNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext && tempNode->pNext->pNext){
            //tempNode -> deleteNode -> valNode
            if (tempNode->pNext->pNext->key == val){
                SNODE* deleteNode = tempNode->pNext;
                tempNode->pNext = tempNode->pNext->pNext;
                delete deleteNode;
            }
            tempNode = tempNode->pNext;
        }
        if (countElements(L) == 2 && countVal(L, val) == 2)
            removeHead(L);
    }
}

void removeAfter(list* L, int val){
    if(!isEmpty(L)){
        SNODE* tempNode = L->pHead;
        while(tempNode && tempNode->pNext){
            if (tempNode->key == val && tempNode->pNext == L->pTail)
                removeTail(L);
            //tempNode -> deleteNode
            else if(tempNode->key == val){
                SNODE* deleteNode = tempNode->pNext;
                tempNode->pNext = deleteNode->pNext;
                delete deleteNode;
            }
            tempNode = tempNode->pNext;
        }
    }
}

//QUY ƯỚC: vị trí (index) trong danh sách liên kết bắt đầu từ 0;
bool checkPos(list* L, int pos){
    if (!isEmpty(L))
        return (pos >= 0 && (pos < countElements(L)));
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
        while(curIndex < pos ){
            tempNode = tempNode->pNext;
            curIndex++;
        }
        SNODE* addNode = createNode(data);
        if(addNode){
            addNode->pNext = tempNode->pNext;
            tempNode->pNext = addNode;
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
        SNODE* deleteNode = tempNode->pNext;
        tempNode->pNext = deleteNode->pNext;
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
                addNode->pNext = tempNode->pNext;
                tempNode->pNext = addNode;
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
            //tempNode -> addNode 
            if(tempNode->key == val){
                SNODE* addNode = createNode(data);
                addNode->pNext = tempNode->pNext;
                tempNode->pNext = addNode;
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
    while(tempNode){
        if(tempNode->pNext)
            cout << tempNode->key << " -> ";
        else
            cout << tempNode->key;
        tempNode = tempNode->pNext;
    }
}

list* reverseList(list* L){
    if(!isEmpty(L)){
        SNODE* prevNode = NULL;
        SNODE* currNode = L->pHead;
        SNODE* nextNode = NULL;
        while(currNode){
            nextNode = currNode->pNext;
            currNode->pNext = prevNode;
            prevNode = currNode;
            currNode = nextNode;
        }
        L->pTail = L->pHead;
        L->pHead = prevNode;
    }
    return L;
}

void removeDuplicate(list* &L){
    SNODE* tempNode1 = L->pHead, *tempNode2, *dupNode;
    while(tempNode1 && tempNode1->pNext){
        tempNode2 = tempNode1;
        while(tempNode2->pNext){
            if(tempNode1->key == tempNode2->pNext->key){
                if (tempNode2->pNext == L->pTail)
                    removeTail(L);
                else{
                    dupNode = tempNode2->pNext;
                    tempNode2->pNext = tempNode2->pNext->pNext;
                    delete dupNode;
                } 
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
                SNODE* deleteNode = tempNode->pNext;
                tempNode->pNext = tempNode->pNext->pNext;
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

//II. STACK
struct Stack{
    SNODE* top;
};

//Khởi tạo stack
void initStack(Stack &stack, int firstKey){
    SNODE* firstNode = createNode(firstKey);
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
    SNODE* newNode = createNode(x);
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

//III. QUEUE
struct Queue{
    SNODE* pHead;
    SNODE* pTail;
};

//Khởi tạo hàng đợi
void initQueue(Queue &queue, int firstKey){
    SNODE* firstNode = createNode(firstKey);
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
    SNODE* newNode = createNode(x);
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

//Đếm số phần tử trong stack
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

//================== SLL MENU FUNCTIONS ================
void singlyLinkedList(){
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
        cout << "==================== SINGLY LINKED LIST =================\n";
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
        cout << "0. Tro lai MAIN MENU.\n";
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
                if (removeElement(list, val))
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
        cout << "*                              WEEK3                           *\n";
        cout << "****************************************************************\n";
        cout << "============================ MAIN MENU =========================\n";
        cout << "1. LINKED LIST MENU.\n";
        cout << "2. STACK MENU.\n";
        cout << "3. QUEUE MENU.\n";
        cout << "0. THOAT THUONG TRINH.\n";
        cout << "============================== END ============================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        if (choice == "1")
            singlyLinkedList();
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