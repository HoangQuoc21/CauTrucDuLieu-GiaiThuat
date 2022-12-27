#include <iostream>
#include "BiSearchTree.h"
using namespace std;
#define COUNT 10

int main(){
    system("cls");
    cout << "*******************************************************\n";
    cout << "*                     HOME WORK 2                     *\n";
    cout << "*******************************************************\n";

    //===== Nhập giá trị các Node thủ công: =====
    // int nNode;
    // cout << "-Nhap vao so luong node cua cay (nNode >= 0): ";
    // cin >> nNode;
    // int *Nodes = new int [nNode];
    // for (int i = 0; i < nNode; i++){
    //     cout << "-Node " << i << ": ";
    //     cin >> Nodes[i];
    // }
    //== Khóa 8 dòng trên và dòng 43 để sử dụng test case cứng ==

    //===== Test case cứng(Mở khóa 2 dòng dưới đây): ====== 
    int nNode = 20;
    int Nodes[100] = {9,5,3,20,60,81,14,4,7,56,13,1,15,8,6,100,99,101,102,103};
    //                   ___9___
    //                 /        \
    //                5         20
    //             /    \     /    \
    //           3      7    14    60
    //          / \   / \   / \   /  \ 
    //         1   4 6   8 13 15 56  81
    //                                \
    //                                100
    //                                / \ 
    //                              99  101
    //                                    \
    //                                    102
    //                                       \
    //                                       103
    TNODE* pRoot = createTree(Nodes, nNode);
    //delete [] Nodes;
    while(1){
        string choice;
        system("cls");
        cout << "*******************************************************\n";
        cout << "*                     HOME WORK 2                     *\n";
        cout << "*******************************************************\n";
        cout << "================= BINARY SEARCHING TREE ===============\n";
        cout << "-------------------------------------------------------\n";
        ProcessTree(pRoot,0);
        cout << "-------------------------------------------------------\n";
        cout << "-Cay da nhap in theo tien thu tu: ";
        NLR(pRoot);
        cout << endl;
        cout << "-Cay da nhap in theo trung thu tu: ";
        LNR(pRoot);
        cout << endl;
        cout << "-Cay da nhap in theo hau thu tu: ";
        LRN(pRoot);
        cout << endl;
        cout << "-Cay da nhap in theo muc: ";
        LevelOrder(pRoot);
        cout << endl;
        cout << "-------------------------------------------------------\n";
        cout << "-Chieu cao cua cay: " << Height(pRoot) << endl;
        cout << "-So Node cua cay: " << countNode(pRoot) << endl;
        cout << "-Tong gia tri cac Node trong cay la: " << sumNode(pRoot) << endl;
        cout << "-So la cua cay: " << countLeaf(pRoot) << endl;
        cout << "-------------------------------------------------------\n";
        if (isBST(pRoot)){
            cout << "-Day la cay nhi phan tim kiem.\n";
            if (isFullBST(pRoot))
                cout << "-Day la cay nhi phan tim kiem du.\n";
            else
                cout << "-Day khong phai la cay nhi phan tim kiem du.\n";
        }
        else
            cout << "-Day khong phai la cay nhi phan tim kiem.\n";
        cout << "======================== MENU ========================\n";
        cout << "1. Them 1 Node vao cay.\n";
        cout << "2. Xoa 1 Node khoi cay.\n";
        cout << "3. Dem so Node mang gia tri nho hon gia tri nhap vao.\n";
        cout << "4. Dem so Node mang gia tri lon hon gia tri nhap vao.\n";
        cout << "5. Tinh muc cua Node mang gia tri nhap vao.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "======================== END =========================\n";
        cout << "Nhap vao lua chon cua ban: ";
        cin >> choice;
        cout << "-------------------------------------------------------\n";
        if (choice == "1"){
            int data;
            cout << "Nhap vao gia tri muon them vao cay: ";
            cin >> data;
            if (!Search(pRoot,data)){
                Insert(pRoot, data);
                cout << "Da them Node mang gia tri " << data << " vao cay.\n";
            }
            else 
                cout << "Da ton tai Node mang gia tri " << data << " trong cay.\n";
        }
        else if (choice == "2"){
            int data;
            cout << "Nhap vao gia tri muon xoa khoi cay: ";
            cin >> data;
            if(Search(pRoot,data)){
                Remove(pRoot,data);  
                cout << "Da xoa Node mang gia tri " << data << " khoi cay.\n"; 
            }
            else
                cout << "Khong ton tai Node mang gia tri " << data << " de xoa khoi cay.\n";
             
        }
        else if (choice == "3"){
            int data;
            cout << "Nhap vao gia tri muon dem so luong Node mang gia tri nho hon: ";
            cin >> data;
            cout << "So luong Node mang gia tri nho hon " << data << " la: " << countLess(pRoot, data) << endl;
        }
        else if (choice == "4"){
            int data;
            cout << "Nhap vao gia tri muon dem so luong Node mang gia tri lon hon: ";
            cin >> data;
            cout << "So luong Node mang gia tri lon hon " << data << " la: " << countGreater(pRoot, data) << endl;
        }
        else if (choice == "5"){
            int data;
            cout << "Nhap vao gia tri cua Node muon tim muc: ";
            cin >> data;
            TNODE* targetNode = Search(pRoot, data);
            int nodeLevel = Level(pRoot, targetNode);
            if (nodeLevel == -1)
                cout << "Khong co Node mang gia tri " << data << " de tim muc.\n";
            else
                cout << "Muc cua Node mang gia tri " << data << " la: " << nodeLevel << endl;
        }
        else if (choice == "0"){
            cout << "Thoat chuong trinh.\n";
            break;
        }
        else
            cout << "Lua chon khong hop le.\n";
        system("pause");
    }
    removeTree(pRoot);
    return 0;
}