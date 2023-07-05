#include <iostream>
#include "AVLTree.h"

int main(){
    NODE* pRoot = NULL;

    //=== Vài TH Nhập tự động trước 1 số node (Nếu muốn, thầy hãy mở khóa những dòng dưới và chỉnh sửa ạ) ====
    //-- Case1: --
    // int nNode = 13;
    // int a[13] = {45,36,15,29,57,78,60,83,79,96,20,99,97};
    // -- Case2: --
    // int nNode = 11;
    // int a[11] = {33,14,15,92,64,35,79,27,38,105,99};
    // -- Case3: --
    // int nNode = 10;
    // int a[10] = {22,1,13,11,24,33,18,42,31,32};

    //-- 2 dòng dưới đây để tự động thêm node dựa theo case ở trên --
    // for (int i = 0; i < nNode; i++)
    //     Insert(pRoot, a[i]);

    while(1){
        string choice;
        system("cls");
        cout << "*******************************************************\n";
        cout << "*                HOME WORK 3: AVL TREE                *\n";
        cout << "*******************************************************\n";
        cout << "-Cay da nhap in theo tien thu tu: ";
        NLR(pRoot);
        cout << "\n-Cay da nhap in theo trung thu tu: ";
        LNR(pRoot);
        cout << "\n-Cay da nhap in theo hau thu tu: ";
        LRN(pRoot);
        cout << "\n-Cay da nhap in theo muc: ";
        LevelOrder(pRoot);
        if (countNode(pRoot) == 0)
            cout << "\n-Cay hien tai chua co Node nao het.\n";
        else{
            cout << "\n-Cay hien tai co " << countNode(pRoot) << " Node.\n";
            if (isAVL(pRoot))
                cout << "-Day la cay AVL.\n";
            else
                cout << "-Day khong phai la cay AVL.\n";
        }
        cout << "======================== MENU ========================\n";
        cout << "1. Them 1 Node vao cay.\n";
        cout << "2. Xoa 1 Node khoi cay.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "======================== END =========================\n";
        cout << "Nhap vao lua chon cua ban: ";
        cin >> choice;
        cout << "-------------------------------------------------------\n";
        if (choice == "1"){
            int data;
            cout << "Nhap vao gia tri muon them vao cay: ";
            cin >> data;
            if (isExsited(pRoot, data))
                cout << "Da ton tai gia tri " << data << " san trong cay nen khong can them.\n";
            else{
                cout << "Da them Node mang gia tri " << data << " vao cay.\n";
                Insert(pRoot, data);
            }  
        }
        else if (choice == "2"){
            int data;
            cout << "Nhap vao gia tri muon xoa khoi cay: ";
            cin >> data;
            if (isExsited(pRoot,data)){
                cout << "Da xoa Node mang gia tri " << data << " khoi cay.\n";
                Remove(pRoot,data);  
            }
            else
                cout << "Khong ton tai gia tri " << data << " de xoa trong cay.\n";
        }
        else if (choice == "0"){
            cout << "Thoat chuong trinh.\n";
            break;
        }
        else
            cout << "Lua chon khong hop le.\n";
        
        system("pause");
    }

    destroyTree(pRoot);
    return 0;
}