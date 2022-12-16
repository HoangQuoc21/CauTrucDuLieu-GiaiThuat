#include<iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <string>

using namespace std;

struct Animal
{
	string en;
	string vn;
	string ph;
	int loai;
};

struct NODE
{
	Animal data;
	NODE* pnext;
};

struct LinkedList
{
	NODE* pHead;
	NODE* pTail;
};

bool isEmpty(LinkedList* List){
    return (!List->pHead &&  !List->pTail);
}

NODE* createNode(string enlish, string pronoun, string vietnam, int loai){
    NODE* newNode = new NODE;
    newNode->data.en = enlish;
    newNode->data.vn = vietnam;
    newNode->data.ph = pronoun;
    newNode->data.loai = loai;
    newNode->pnext = NULL;
    return newNode;
}

void insertTail(LinkedList* List, string english, string pronoun, string vietnam, int loai ){
    NODE* newNode = createNode(english, pronoun, vietnam, loai);
    if (isEmpty(List)){
        List->pHead = List->pTail = newNode;
    }
    else{
        List->pTail->pnext = newNode;
        List->pTail = newNode;
    }
}

LinkedList* readAnimals(string filename)
{
    //CODE HERE
    ifstream fin(filename);
    if (!fin.is_open()){
        cout << "Can't open " << filename << endl;
        return NULL;
    }

    cout << filename << " opened.\n";
    LinkedList* AList = new LinkedList;
    AList->pHead = AList->pTail = NULL;
    while(!fin.eof()){
        string english;
        string vietnam;
        string pronoun;
        string loai;
        getline(fin,english);
        getline(fin,pronoun);
        getline(fin,vietnam);
        getline(fin, loai);
        insertTail(AList, english, pronoun, vietnam, stoi(loai));
        //cout << english << " " << pronoun << " " << vietnam << " " << stoi(loai) << endl;
    }
    fin.close();
    cout << "haha.\n";
    return AList;
}

void removeDuplicate(LinkedList* list)
{
    //CODE HERE
}


void printPaths(int** matrix, vector<int> &route, int len_route,  int i, int j, int M, int N)
{
    // MxN matrix
    if(M == 0 || N == 0)
    {
        return;
    }

    // if the last cell is reached
    if(i == M-1 && j == N-1)
    {
        // print the route
        for (int k = 0; k < len_route; k++)
        {
            cout << route[k] << " ";
        }
        cout << matrix[i][j] << endl;
        return;
    }

    // add the current cell to route
    route.push_back(matrix[i][j]);
    len_route += 1;

    // move down
    if (i + 1 < M)
    {
        printPaths(matrix, route, len_route, i+1, j, M, N);
    }
    
    // move right
    if (j + 1 < N)
    {
        printPaths(matrix, route, len_route, i, j+1, M, N);
    }

    // move diagonally
    if (i + 1 < M && j + 1 < N)
    {
        printPaths(matrix, route, len_route,  i+1, j+1, M, N);
    }

    // backtrack
    route.pop_back();
}


void CountAssignmentandComparision()
{
    
    int M = 3, N=3;
    int** matrix = new int*[M];
    int a = 3;
    a++;
    for(int i =0; i < M; i++, a++)
    {
        matrix[i] = new int[N];
        a++;
    }
    a++;
    for (int i = 0; i < M*N; i++, a++)
    {
        matrix[i/N][i%N] = i;
        a++;
    }

    vector<int> route;
    int len_route = 0;
    int i = 0, j = 0;
    a = a + 3;zz
    // Goi ham printPaths
    printPaths(matrix, route, len_route, i, j, M, N); // Ban co the thay doi dong nay neu co thay doi tham so cua ham
    
    // In ra so phep gan và so phep so sanh
    // CODE HERE
}

int kthSmallest(int* arr, int n, int k)
{
    //CODE HERE
    return 0;
}

int main()
{
    system("cls");
    // Cau 1
    string filename = "data.txt";
    // 1.1
    LinkedList* list = readAnimals(filename);
    NODE* temp = list->pHead;
    while (temp) {
        cout << "haha.\n";
        cout << temp->data.en << " " << temp->data.ph << " " << temp->data.vn << " " << temp->data.loai << endl;
        temp = temp->pnext; 
    }
    // 1.2
    removeDuplicate(list);
    
    // Cau 2
    CountAssignmentandComparision();

    // Cau 3

    int n = 10;
    int * arr = new int[n]{0, 5, 2, 4, 1, 9, 10, 10, 7, 2};
    int k = 5;

    int res = kthSmallest(arr, n, k);
    return -1;
}
