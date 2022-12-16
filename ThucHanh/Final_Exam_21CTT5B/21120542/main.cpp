#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
#define MAX 1000
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
        rightRotate(pRoot);
        return;
    }
        
    if (balance < -1 && x > pRoot->pRight->key){
        leftRotate(pRoot);
        return;
    }
        
    if (balance > 1 && x > pRoot->pLeft->key ){
        leftRotate(pRoot->pLeft);
        rightRotate(pRoot);
        return;
    }

    if (balance < -1 && x < pRoot->pRight->key ){
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

bool isAVL(AVLNode* root){
	if (!root)
        return true;

    int lh = height(root->pLeft);
    int rh = height(root->pRight);

    return (abs(lh - rh) <= 1) && isAVL(root->pLeft) && isAVL(root->pRight);
}

void NLR(AVLNode* pRoot) {
	if (!pRoot)
		return;
	cout << pRoot->key << " ";
	NLR(pRoot->pLeft);
	NLR(pRoot->pRight);
}

vector<Animal> readAnimals(string filename) {
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "Can't open " << filename << " to read.\n";
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
	cout << "Successfully read " << filename << endl;
	fin.close();
	return animal_list;
}

void Print_Animal_List(vector<Animal> animal_list){
    cout << "----------------- ANIMAL LIST --------------\n";
    for (int i = 0; i < animal_list.size(); i++)
        cout << i << ": " << animal_list[i].en << "-" << animal_list[i].ph << "-" << animal_list[i].vn << "-" << animal_list[i].loai << endl;
    cout << "--------------------------------------------\n";
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
    Push(hash_table[i], animal_data);
}

HNode** CreateHashTable(vector<Animal> animal_list) {
	HNode** hash_table = new HNode* [hashTableSize];
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

vector<vector<int>> createEdgeList(int edge_num) {
	int x, y;
	vector<vector<int>> edges;
	for (int i = 0; i < edge_num; i++) {
        cout << "Edge " << i + 1<< ": ";
		cin >> x >> y;
		vector<int> e;
		e.push_back(x);
		e.push_back(y);
		edges.push_back(e);
	}
	return edges;
}

void printEdges(vector<vector<int>> edges, int edge_num) {
  
	for (int i = 0; i < edge_num; i++) {
		cout << edges[i][0] << " " << edges[i][1] << endl;
	}
}

int** edgeListToMatrix(vector<vector<int>> edges, int n, int edge_num) {
	int** matrix = new int* [n]{};
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n]{};

	for (int i = 0; i < edge_num; i++) {
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

void printList(vector<int>* list, int vertices) {
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < list[i].size(); j++)
			cout << list[i][j] << " ";
		cout << endl;
	}
}

void DFS(vector<int>* list, int u, bool visited[MAX], int &vertices_components, int &edge_components) {
	visited[u] = true;
	vertices_components++;
	for (int v : list[u]){
		edge_components++;
		if (!visited[v]){
			DFS(list, v, visited, vertices_components, edge_components);
		}
	}	
}

int minimumEdges(int ** graph, int n, int k){
	int them = 0;
	vector<int>* list = matrixToList(graph, n);
	bool visited[MAX]{};
	for (int i = 0; i < n; i++) {
		int vertices_components = 0;
		int edge_components = 0;
		if (!visited[i]) {
			DFS(list, i, visited, vertices_components, edge_components);
			edge_components /=2;
			int max_edges = (vertices_components * (vertices_components - 1))/2;
			if (k > max_edges){
				return -1;
			};	
		}
		them = them + (edge_components%k);
	}
	return them;
}

int main() {
    system("cls");
	// cout << "Cau01:\n";
	// int na;
	// cout << "Number of AVLNode: ";
	// cin >> na;
	// int* arr = new int [na];
	// for (int i = 0; i < na; i++){
	// 	cout << "Node " << i+1 << ": ";
	// 	cin >> arr[i];
	// }
	// AVLNode* pRoot = createAVL(arr, na);
	// cout << "--------------------------\n";
	// cout << "Created AVLTree with NLR traversal:\n";
    // NLR(pRoot);
	// cout << endl;
	// if (isAVL(pRoot))
	// 	cout << "This is an AVL tree.\n";
	// else
	// 	cout << "This is not an AVL tree.\n";
    // cout << "===========================================================\n";

	// cout << "Cau02:\n";
    // string file_name("data.txt");
	// vector<Animal> animal_list = readAnimals(file_name);
	// Print_Animal_List(animal_list);
    // HNode** hash_table = CreateHashTable(animal_list);
	// writeFile(hash_table, "hash_table.txt");
	// cout << "===========================================================\n";
  
	cout << "Cau03:\n";
	vector<vector<int>> edges;
	int vertices,edge_num, k ;
	cout << "Number of vertices: ";
	cin >> vertices;
	cout << "Number of edges: ";
	cin >> edge_num;
	edges = createEdgeList(edge_num);
	cout << "--------------------------\n";
	printEdges(edges, edge_num);
	cout << "--------------------------\n";
	int** matrix = edgeListToMatrix(edges, vertices, edge_num);
	PrintMatrix(matrix, vertices);
	cout << "--------------------------\n";
	bool visited[MAX]{};
	int connected_components;
	vector<int>* list = matrixToList(matrix,vertices);
	printList(list, vertices);
	cout << "--------------------------\n";
	cout << "Enter k: ";
	cin >> k;
	cout << "So canh can them vao de thoa de bai: "<< minimumEdges(matrix, vertices, k);
	
	return 0;
}