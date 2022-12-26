#include<iostream>
#include<vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//Cau1
struct BabyName
{
	string name;
	string gender;
	int year;
	int count;
};

struct Node
{
	BabyName data;
	Node* pnext;
};

struct LinkedList
{
	Node* pHead;
	Node* pTail;
};

void initList(LinkedList*& list){
    list = new LinkedList;
    list->pHead = list->pTail = NULL;    
}

bool isEmpty(LinkedList* list){
    return (( list->pHead == NULL ) && (list->pTail == NULL)); 
}

Node* createNode(string name, string gender, int year, int count){
    Node* newNode = new Node;
    newNode->data.name = name;
    newNode->data.gender = gender;
    newNode->data.year = year;
    newNode->data.count = count;
    newNode->pnext = NULL;
    return newNode;
}

void insertTail(LinkedList*&list,string name, string gender, int year, int count ){
    Node* newNode = createNode(name, gender, year, count);
    if (isEmpty(list))
        list->pHead = list->pTail = newNode;
    else{
        list->pTail = newNode;
        list->pTail = newNode;
    }
}

LinkedList* readBabyNames(string filename)
{
    //CODE HERE
    LinkedList* list;
    initList(list);

    ifstream fin(filename);
    if (!fin.is_open()){
        cout << "Can't open " << filename << " to read\n";
    }
    else{
        cout << filename << " opened.\n";
        string tittle;
        getline(fin,tittle);
        while (!fin.eof()){
            string line;
            getline(fin,line, '\n');
            stringstream ss(line);
            cout << "\""<< line <<"\"\n";
            string name;
            string gender;
            string year;
            string count;
            getline(ss , name , ' ' );
            getline(ss , gender , ' ' );
            getline(ss , year , ' ' );
            getline(ss , count);
            cout << "\""<< name << "\"\n"; 
            cout << "\""<< gender << "\"\n"; 
            cout << "\""<< year << "\"\n"; 
            cout << "\""<< count << "\"\n"; 
            int i_year = stoi(year);
            int i_count = stoi(count);
            insertTail(list,name,gender, i_year, i_count);
            
        }
        fin.close();
    }
    return list;
}

LinkedList* splitBabyNames(LinkedList* list, int year)
{
    //CODE HERE
    LinkedList* nlist;
    initList(nlist);
    Node* temp = list->pHead;
    while(temp){
        if(temp->data.year == year)
            insertTail(nlist, temp->data.name, temp->data.gender,temp->data.year, temp->data.count);
        temp = temp->pnext;
    }
    return nlist;
}

LinkedList* mergeLinkedList(LinkedList* list1, LinkedList* list2)
{
	//CODE HERE
    LinkedList* mlist;
    initList(mlist);

    return mlist;
}

//Cau2
void printPaths(int** matrix, vector<int> &route, int len_route,  int i, int j, int M, int N, long long &a, long long &c)
{
    // MxN matrix
    ++c; 
    if(M == 0 || N == 0)
    {
        ++c;
        return;
    }

    // if the last cell is reached
    ++c;
    if(i == M-1 && j == N-1)
    {
        ++c;
        // print the route
        a++;
        for (int k = 0; ++c && k < len_route; k++, a++)
        {
            cout << route[k] << " ";
        }
        cout << matrix[i][j] << endl;
        return;
    }

    // add the current cell to route
    route.push_back(matrix[i][j]);
    a++;
    len_route += 1;
    a++;

    // move down
    ++c;
    if (i + 1 < M)
    {
        printPaths(matrix, route, len_route, i+1, j, M, N,a,c);
    }
    
    // move right
    ++c;
    if (j + 1 < N)
    {
        printPaths(matrix, route, len_route, i, j+1, M, N,a,c);
    }

    // move diagonally
    ++c;
    if (i + 1 < M && j + 1 < N)
    {
        c++;
        printPaths(matrix, route, len_route,  i+1, j+1, M, N,a,c);
    }

    // backtrack
    route.pop_back();
}


void CountAssignmentandComparision()
{   
    long long a = 0;
    long long c = 0;
    int M = 3, N=3;
    int** matrix = new int*[M];
    a = 3;
    a++;
    for(int i =0; ++c && i < M; i++, a++)
    {
        matrix[i] = new int[N];
        a++;
    }
    a++;
    for (int i = 0; ++c && i < M*N; i++, a++)
    {
        matrix[i/N][i%N] = i;
        a++;
    }

    vector<int> route;
    int len_route = 0;
    int i = 0, j = 0;
    a = a + 3;
    
    // Goi ham printPaths
    printPaths(matrix, route, len_route, i, j, M, N,a,c); // Ban co the thay doi dong nay neu co thay doi tham so cua ham
    
    // In ra so phep gan và so phep so sanh
    // CODE HERE
    cout << "So phep gan: " << a << endl;
    cout << "So phep so sanh: " << c << endl;
}

//Cau3

void heapify(int a[], int N, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < N && a[left] > a[largest])
        largest = left;
 
    if (right < N && a[right] > a[largest])
        largest = right;
 
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, N, largest);
    }
}

void builMaxHeap(int a[], int N){
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(a, N, i);
}

void heapSort(int a[], int N)
{
    builMaxHeap(a, N);
    for (int i = N - 1; i >= 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

int countPairs(int* arr, int n, int k)
{
    int countPairs = 0;
    //CODE HERE
    heapSort(arr,n);
    for (int i = 0; i < n - 1; i++){
        if (arr[i] != arr[i+1]){
            for (int j = i; j < n; j++)
                if (arr[j] != arr[j+1] && arr[j] - arr[i] == k)
                    countPairs++;
        }
    }
    return countPairs;
}

int main()
{
    system("cls");
    // Cau 1
    string filename = "data.txt";
    // 1.1
    LinkedList* list = readBabyNames(filename);
    // 1.2
    LinkedList* babyNames1880 = splitBabyNames(list, 1880);
    LinkedList* babyNames1881 = splitBabyNames(list, 1881);
    
    // 1.3 
    LinkedList* mergedList = mergeLinkedList(babyNames1880, babyNames1881);
    
    // Cau 2
    CountAssignmentandComparision();

    // Cau 3

    int n = 5;
    int * arr = new int[n]{3, 1, 4, 1, 5};
    int k = 2;

    int res = countPairs(arr, n, k);
    cout << res << endl;
    
    return -1;
}
