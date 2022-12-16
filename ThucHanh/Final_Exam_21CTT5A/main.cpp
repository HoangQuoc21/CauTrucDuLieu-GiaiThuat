#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
#define MAX 100
#define hashTableSize 26

struct Animal {
	string en;
	string vn;
	string ph;
	int loai;
};

struct AVLNode {
	int key;
	AVLNode* pLeft;
	AVLNode* pRight;
    int height;
};

AVLNode* createNode(int data) {
    AVLNode* newNode = new AVLNode;
    newNode->height = 1;
    newNode->pLeft = newNode->pRight = NULL;
    newNode->key = data;
    return newNode;
}

int height(AVLNode* Node){
    if (Node == NULL)
        return 0;
    return Node->height;
}

void rightRotate(AVLNode* &y){
    AVLNode* x = y->pLeft;
    AVLNode* T2 = x->pRight;

    x->pRight = y;
    y->pLeft = T2;

    y->height = max(height(y->pLeft), height(y->pRight)) + 1;
    x->height = max(height(x->pLeft), height(x->pRight)) + 1;

    y = x;
}

void leftRotate(AVLNode*& x){
    AVLNode* y = x->pRight;
    AVLNode* T2 = y->pLeft;

    y->pLeft = x;
    x->pRight = T2;

    x->height = max(height(x->pLeft), height(x->pRight)) + 1;
    y->height = max(height(y->pLeft), height(y->pRight)) + 1;

    x = y;
}

int getBalance(AVLNode* Node){
    if (Node == NULL)
        return 0;
    return height(Node->pLeft) - height(Node->pRight);
}

void InsertNode(AVLNode* &pRoot, int x){
    if (pRoot == NULL)
        pRoot = createNode(x);

    if (x < pRoot->key)
        InsertNode(pRoot->pLeft, x);
    else if (x > pRoot->key)
        InsertNode(pRoot->pRight, x);
    else
        return;

    pRoot->height = max(height(pRoot->pLeft),height(pRoot->pRight)) + 1;

    int balance = getBalance(pRoot);

    if (balance > 1 && x < pRoot->pLeft->key){
        cout << pRoot->key << " Mat can bang trai trai.\n";
        rightRotate(pRoot);
        return;
    }
        
    if (balance < -1 && x > pRoot->pRight->key){
        cout << pRoot->key << " Mat can bang phai phai.\n";
        leftRotate(pRoot);
        return;
    }
        
    if (balance > 1 && x > pRoot->pLeft->key ){
        cout << pRoot->key << " Mat can bang trai phai.\n";
        leftRotate(pRoot->pLeft);
        rightRotate(pRoot);
        return;
    }

    if (balance < -1 && x < pRoot->pRight->key ){
        cout << pRoot->key << " Mat can bang phai trai.\n";
        rightRotate(pRoot->pRight);
        leftRotate(pRoot);
        return;
    }
}

AVLNode* maxValueNode(AVLNode* node){
    AVLNode* current = node;
    while (current->pRight != NULL)
        current = current->pRight;

    return current;
}

void deleteElement(AVLNode* &pRoot, int x){
    if (pRoot == NULL)
        return;

    if (x < pRoot->key)
        deleteElement(pRoot->pLeft, x);

    else if (x > pRoot->key)
        deleteElement(pRoot->pRight, x);

    else{
        if ((pRoot->pLeft == NULL) || (pRoot->pRight == NULL)){
            AVLNode* deleteNode = pRoot->pLeft ? pRoot->pLeft : pRoot->pRight;

            if (deleteNode == NULL){
                deleteNode = pRoot;
                pRoot = NULL;
            }
            else  
                *pRoot = *deleteNode;  
            
            delete deleteNode;
        }
        else{
            AVLNode* standingNode = maxValueNode(pRoot->pLeft);
            pRoot->key = standingNode->key;
            deleteElement(pRoot->pLeft, standingNode->key);
        }
    }
    if (pRoot == NULL)
        return;

    pRoot->height = max(height(pRoot->pLeft),height(pRoot->pRight)) + 1;

    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->pLeft) >= 0 ){
        cout << pRoot->key << " Mat can bang trai trai.\n";
        rightRotate(pRoot);
        return;
    }
        
    if (balance < -1 && getBalance(pRoot->pRight) <= 0 ){
        cout << pRoot->key << " Mat can bang phai phai.\n";
        leftRotate(pRoot);
        return;
    }
        
    if (balance > 1 && getBalance(pRoot->pLeft) < 0 ){
        cout << pRoot->key << " Mat can bang trai phai.\n";
        leftRotate(pRoot->pLeft);
        rightRotate(pRoot);
        return;
    }

    if (balance < -1 && getBalance(pRoot->pRight) > 0){
        cout << pRoot->key << " Mat can bang phai trai.\n";
        rightRotate(pRoot->pRight);
        leftRotate(pRoot);
        return;
    }
}

AVLNode* createAVL(int *arr, int n){
    AVLNode *pRoot = createNode(arr[0]);
    for (int i = 1; i < n ;i++)
        InsertNode(pRoot, arr[i]);
    return pRoot;
}

void LevelOrder(AVLNode* pRoot) {
	if (!pRoot)
		return;

	queue<AVLNode*> nodeQueue;
	nodeQueue.push(pRoot);
	while (!nodeQueue.empty()) {
		AVLNode* currNode = nodeQueue.front();
		cout << currNode->key << " ";
		nodeQueue.pop();
		if (currNode->pLeft)
			nodeQueue.push(currNode->pLeft);
		if (currNode->pRight)
			nodeQueue.push(currNode->pRight);
	}
}

//============================================================================
vector<Animal> createAnimalList(string file_name) {
	ifstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Can't open " << file_name << " to read.\n";
		exit(1);
	}
	vector<Animal> animal_list;
	Animal buffer;
	string line1;
	string line2;
	string line3;
	string line4;
	while (!fin.eof()) {
		getline(fin, line1);
		getline(fin, line2);
		getline(fin, line3);
		getline(fin, line4);
		buffer.en = line1; 
		buffer.ph = line2;
		buffer.vn = line3;
		buffer.loai = stoi(line4);
		animal_list.push_back(buffer);
	}
	cout << "Successfully read " << file_name << endl;
	fin.close();
	return animal_list;
}

void Print_Animal_List(vector<Animal> animal_list){
    cout << "================= ANIMAL LIST ==============\n";
    for (int i = 0; i < animal_list.size(); i++)
        cout << i << ": " << animal_list[i].en << "-" << animal_list[i].ph << "-" << animal_list[i].vn << "-" << animal_list[i].loai << endl;
    cout << "============================================\n";
}

int hashKey(char letter) {
	return (int)(letter) - 65;
}

struct HNode{
    Animal data;
    HNode* pNext = NULL;
};

HNode* createHNode(Animal animal_data){
    HNode* new_node = new HNode;
    new_node->data = animal_data;
    return new_node;
}

void Push(HNode* &pHead, Animal animal_data){
    if (pHead->data.en.empty()) {
		pHead->data = animal_data;
	}
	else {
		//Thêm Node cho các node sau i
		HNode* new_node = createHNode(animal_data);
		HNode* temp = pHead;

		while (temp->pNext)
			temp = temp->pNext;

		temp->pNext = new_node;
	}
}

void InsertHNode(HNode** hash_table, Animal animal_data){
    int i = hashKey(animal_data.en[0]) % hashTableSize;
    //cout << i << endl;
    Push(hash_table[i], animal_data);
}

HNode** CreateHashTable(vector<Animal> animal_list) {
	//Tạo mảng động các con trỏ
	HNode** hash_table = new HNode* [hashTableSize];
	//Cấp phát vùng nhớ cho con trỏ đầu tiên (các con trỏ đầu tiên này khác NULL)
	for (int i = 0; i < hashTableSize; i++) {
		hash_table[i] = new HNode;
	}
		

	for (int i = 0; i < animal_list.size(); i++)
		InsertHNode(hash_table, animal_list[i]);
	cout << "Hash Table created.\n";
	return *&hash_table;
}

void writeFile(HNode** hash_table, string outputFile) {
	ofstream fout(outputFile);

	if (!fout.is_open()){
		cout << "Can't open file " << outputFile << " to write.\n";
		return;
	}
	int dem = 0;
	HNode* temp = NULL;
	for (int i = 0; i < hashTableSize; i++) {
		fout << "INDEX: " << i << ":\n";
		temp = hash_table[i];
		while(temp && !temp->data.en.empty()){
			fout << temp->data.en << "|" << temp->data.ph << "|" << temp->data.vn << "|" << temp->data.loai << endl;
			dem++;
			temp = temp->pNext;
		}
		fout << "---------------------------------------------------\n";
	}
	fout << "=========================================================\n";
	delete temp;
	fout << "Total numbers of animals: " << dem << endl;
	fout.close();
	cout << "Successfully write created hash table to " << outputFile << endl;
}

//============================================================================
//Đồ thị đang xét là đồ thị vô hướng

vector<vector<int>> createEdgeList(int so_luong_canh) {
	int x, y;
	vector<pair<int, int>> test_case;
	test_case.push_back({0,1});
	test_case.push_back({0,2});
	test_case.push_back({2,3});
	test_case.push_back({2,4});
	test_case.push_back({2,5});

	vector<vector<int>> edges;
	for (int i = 0; i < so_luong_canh; i++) {
        // cout << "Nhap canh " << i + 1<< ": ";
		// cin >> x >> y;
		x = test_case[i].first;
		y = test_case[i].second;
		vector<int> e;
		e.push_back(x);
		e.push_back(y);
		edges.push_back(e);
	}
	return edges;
}

void printEdges(vector<vector<int>> edges, int so_luong_canh) {
  
	for (int i = 0; i < so_luong_canh; i++) {
		cout << edges[i][0] << " " << edges[i][1] << endl;
	}
    
}

int** edgeListToMatrix(vector<vector<int>> edges, int n, int so_luong_canh) {
	int** matrix = new int* [n]{};
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n]{};

	for (int i = 0; i < so_luong_canh; i++) {
		matrix[edges[i][0]][edges[i][1]] = 1;
		matrix[edges[i][1]][edges[i][0]] = 1;
	}
	return *&matrix;
}

void PrintMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

vector<int>* matrixToList(int** matrix, int vertices) {
	vector <int>* list = new vector<int>[vertices];
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++) {
			if (matrix[i][j] == 1)
				list[i].push_back(j);
		}

	return list;
}

//BFS đi từ đỉnh s đến các đỉnh còn lại
//Tính khoảng cách từ s đến từng đỉnh i và lưu lại vào mảng distance
void BFS1(vector<int>* list, int s, bool visited[MAX], int* distance) {
	queue<int> dinh;
	dinh.push(s);
	visited[s] = true;
	distance[s] = 0;
	while (!dinh.empty()) {
		int u = dinh.front();
		dinh.pop();
		//cout << v << " ";
		for (int v : list[u])
			if (!visited[v]) {
				distance[v] = distance[u] + 1;
				visited[v] = true;
				dinh.push(v);
			}
	}
}

int *CalAnswer(vector<int>* list, int n){
    int* answer = new int[n - 1];
	int ia = 0;
	for (int i = 0; i < n; i++) {
		bool visited[MAX]{ false };
		int sum = 0;
		int* distance = new int[n - 1];
		BFS1(list, i, visited, distance);
		for (int i = 0; i < n; i++)
			sum+= distance[i];

		answer[ia++] = sum;
	}
    return answer;
}



int main() {
    
	//===== Cau01: =====
    system("cls");
	int arr[10] = { 5,2,7,1,4,6,5,3,9,6 };
	int na = 10;
	AVLNode* pRoot = createAVL(arr, na);
    LevelOrder(pRoot);
    cout << endl;
    system("pause");
	
    //===== Cau02: =====
    system("cls");
    string read_file("data.txt");
	vector<Animal> animal_list = createAnimalList(read_file);
	Print_Animal_List(animal_list);

    HNode** hash_table = CreateHashTable(animal_list);
    string write_file("hash_table.txt");
    writeFile(hash_table, write_file);
    system("pause");

	//===== Cau03: =====
    system("cls");
	vector<vector<int>> edges;
	int n = 6;
	int so_luong_canh = 5;
	//0 1
	//0 2
	//2 3
	//2 4
	//2 5
	edges = createEdgeList(so_luong_canh);
	cout << "--------------------------\n";
	printEdges(edges, so_luong_canh);
	cout << "--------------------------\n";
	int** matrix = edgeListToMatrix(edges, n, so_luong_canh);
	PrintMatrix(matrix, n);
	cout << "--------------------------\n";
	
	vector <int>* list = matrixToList(matrix, n);
	//Tính mảng answer
	int *answer = CalAnswer(list, n);
	for (int i = 0; i < n; i++)
		cout << answer[i] << " ";
    cout << endl;
    system("pause");
	return 0;
}