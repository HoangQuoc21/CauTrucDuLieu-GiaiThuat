#include <iostream>
#include "BiSearchTree.h"
using namespace std;

//Câu 01:
//Phần tử tại vị trí idx sẽ được di chuyển lên đầu hàng đợi
void updatePQ(int pQ[], int n, int idx){
    if (n == 1)
        return;
    else{
        int min = idx;
        int k = 2 * idx + 1;
        int j = 2 * idx + 2;
        if (k < n && pQ[k] < pQ[min])
            min = k;
        if ( j < n && pQ[j] < pQ[min])
            min = j;
        if (min != idx){
            swap(pQ[idx], pQ[min]);
            updatePQ(pQ, n, min);
        }
    }
}

void add_node(int pQ[],int &length, int new_data) {
    if (length == 0) {
        pQ[0] = new_data;
        length += 1;
    } else {
        pQ[length] = new_data;
        length += 1;
        for (int i = length / 2 - 1; i >= 0; i--) {
        updatePQ(pQ, length, i);
        }
    }
}


//Câu 03:
void searchDel(TNODE* &root, int k){
    //TNODE* base = root;
    TNODE* curr = root;
    TNODE* prev = NULL;

    //Tìm phần tử chứa khóa k
    while(curr && curr->key != k){
        prev = curr;
        if (k < curr->key)
            curr = curr->pLeft;
        else
            curr = curr->pRight;
    }

    //Ko thấy thì return
    if (!curr)
        return;
    
    //Xóa node có 1 con
    if (!curr->pLeft || !curr->pRight){
        TNODE* newCurr;
        //Nếu node có node con phải
        if (!curr->pLeft)
            newCurr = curr->pRight;
        //Nếu node có node con trái
        else
            newCurr = curr->pLeft;
        
        //Nếu node xóa là node root
        if (!prev){
            root = newCurr;
            return;
        }

        //Cập nhật cái cây con sau khi xóa node k
        if (curr == prev->pLeft)
            prev->pLeft = newCurr;
        else 
            prev->pRight = newCurr;
        
        delete curr;
    }
    //Xóa Node có 2 con
    else{
        TNODE* p = NULL;
        TNODE* temp;
        
        //Tìm phần tử thế mạng (node trái nhất bên cây con phải)
        temp = curr->pRight;
        while(temp->pLeft){
            p = temp;
            temp = temp->pLeft;
        }


        if (p)
            p->pLeft = temp->pRight;
        else
            curr->pRight = temp->pRight;
        
        curr->key = temp->key;
        delete temp;
    }
}



int main(){
    system("cls");
    int length = 0;
    int pQ[10];
    for (int i = 9; i >= 0; i--)
        add_node(pQ,length,i);

    for (int i = 0; i < length; i++)
        cout << pQ[i] << " ";

    //int n = 10;
    //int a[10] = {21,64,8,9,11,100,99,5,2,67};
    //TNODE* root = NULL;
    // root = createTree(a,n);
    // while(1){
    //     system("cls");
    //     LevelOrder(root);
    //     int k;
    //     cout << "k: ";
    //     cin >> k;
    //     searchDel(root,k);
    //     cout << "-----------------------------------\n";
    //     LevelOrder(root);
    //     system("pause");
    // }
    
    return 0;
}