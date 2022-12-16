#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
#define MAX 100

struct Animal {
	string en;
	string vn;
	string ph;
	int loai;
};

struct AVLNode {
	int key;
	Animal data;
	AVLNode* pLeft;
	AVLNode* pRight;
};

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

int hashKey(string en) {
	int key = 0;
	for (int i = 0; i < en.size(); i++)
		key = key +  (int)en[i];
	return key;
}

AVLNode* createNode(Animal animal_data) {
	AVLNode* new_node = new AVLNode;
	new_node->key = hashKey(animal_data.en);
	new_node->data = animal_data;
	new_node->pLeft = new_node->pRight = NULL;
	return new_node;
}

int height(AVLNode* node) {
	if (node == NULL)
		return 0;
	return max(height(node->pLeft), height(node->pRight)) + 1;
}

void rightRotate(AVLNode*& y) {
	AVLNode* x = y->pLeft;
	AVLNode* T2 = x->pRight;

	//Xoay
	x->pRight = y;
	y->pLeft = T2;

	//Cập nhật con trỏ gốc
	y = x;
}

void leftRotate(AVLNode*& x) {
	AVLNode* y = x->pRight;
	AVLNode* T2 = y->pLeft;

	//Xoay
	y->pLeft = x;
	x->pRight = T2;

	//Cập nhật con trỏ gốc
	x = y;
}

int getBalance(AVLNode* node) {
	if (node == NULL)
		return 0;
	return height(node->pLeft) - height(node->pRight);
}

void Insert(AVLNode*& pRoot, Animal animal_data) {
	if (pRoot == NULL)
		pRoot = createNode(animal_data);

	if (hashKey(animal_data.en) < pRoot->key)
		Insert(pRoot->pLeft, animal_data);
	else if (hashKey(animal_data.en) > pRoot->key)
		Insert(pRoot->pRight, animal_data);
	else
		return;

	// B3: Tìm chỉ số cân bằng để xem cây có bị mất cân bằng không
	int balance = getBalance(pRoot);

	//Nếu mất cân bằng, có 4 trường hợp có thể xảy ra:

	// -TH1: mất cân bằng trái trái (xoay phải cây gốc)
	if (balance > 1 && hashKey(animal_data.en) < pRoot->pLeft->key) {
		cout << pRoot->key << " Mat can bang trai trai.\n";
		rightRotate(pRoot);
		return;
	}

	// -TH2: mất cân bằng phải phải (xoay trái cây gốc)
	if (balance < -1 && hashKey(animal_data.en) > pRoot->pRight->key) {
		cout << pRoot->key << " Mat can bang phai phai.\n";
		leftRotate(pRoot);
		return;
	}

	// -TH3: mất cân bằng trái phải (xoay trái cây con trái - xoay phải cây gốc)
	if (balance > 1 && hashKey(animal_data.en) > pRoot->pLeft->key) {
		cout << pRoot->key << " Mat can bang trai phai.\n";
		leftRotate(pRoot->pLeft);
		rightRotate(pRoot);
		return;
	}

	// -TH4: mất cân bằng phải trái (xoay phải cây con phải - xoay trái cây gốc)
	if (balance < -1 && hashKey(animal_data.en) < pRoot->pRight->key) {
		cout << pRoot->key << " Mat can bang phai trai.\n";
		rightRotate(pRoot->pRight);
		leftRotate(pRoot);
		return;
	}
}

AVLNode* readAnimals(string file_name) {
	vector<Animal> animal_list = createAnimalList(file_name);
	AVLNode* pRoot = NULL;
	for (int i = 0; i < animal_list.size(); i++) {
		//cout << animal_list[i].en << " " << animal_list[i].ph << " " << animal_list[i].vn << " " << animal_list[i].loai << endl;
		Insert(pRoot, animal_list[i]);
	}
	return pRoot;
}

// Duyệt theo mức
void LevelOrder(AVLNode* pRoot) {
	if (!pRoot)
		return;

	queue<AVLNode*> nodeQueue;
	nodeQueue.push(pRoot);
	while (!nodeQueue.empty()) {
		cout << endl;
		AVLNode* currNode = nodeQueue.front();
		cout << currNode->key << ": " << currNode->data.en << ", ";
		nodeQueue.pop();
		if (currNode->pLeft)
			nodeQueue.push(currNode->pLeft);
		if (currNode->pRight)
			nodeQueue.push(currNode->pRight);
	}
}

AVLNode* maxValueNode(AVLNode* node) {
	AVLNode* current = node;
	while (current->pRight != NULL)
		current = current->pRight;

	return current;
}

void removeNode(AVLNode*& pRoot, string en) {
	if (pRoot == NULL)
		return;

	if (hashKey(en) < pRoot->key)
		removeNode(pRoot->pLeft, en);

	else if (hashKey(en) > pRoot->key)
		removeNode(pRoot->pRight, en);

	// x == pRoot->key
	else {
		//Trường hợp node muốn xóa có 1 con hoặc không có con 
		if ((pRoot->pLeft == NULL) || (pRoot->pRight == NULL)) {
			AVLNode* deleteNode = pRoot->pLeft ? pRoot->pLeft : pRoot->pRight;

			//TH không có con 
			if (deleteNode == NULL) {
				deleteNode = pRoot;
				pRoot = NULL;
			}
			//Trường hợp có 1 con
			else
				*pRoot = *deleteNode;

			delete deleteNode;
		}
		else {
			//Tìm phần tử thế mạng
			AVLNode* standingNode = maxValueNode(pRoot->pLeft);

			//Đưa giá trị của phần tử thế mạng lên node xóa
			pRoot->key = standingNode->key;

			//Xóa phần tử thế mạng
			removeNode(pRoot->pLeft, standingNode->data.en);
		}
	}

	//Nếu cây chỉ còn 1 Node thì return 
	if (pRoot == NULL)
		return;

	// B3: Tìm chỉ số cân bằng để xem cây có bị mất cân bằng không
	int balance = getBalance(pRoot);

	//Nếu mất cân bằng, có 4 trường hợp có thể xảy ra:

	// -TH1: mất cân bằng trái trái (xoay phải cây gốc)
	if (balance > 1 && getBalance(pRoot->pLeft) >= 0) {
		cout << pRoot->key << " Mat can bang trai trai.\n";
		rightRotate(pRoot);
		return;
	}

	// -TH2: mất cân bằng phải phải (xoay trái cây gốc)
	if (balance < -1 && getBalance(pRoot->pRight) <= 0) {
		cout << pRoot->key << " Mat can bang phai phai.\n";
		leftRotate(pRoot);
		return;
	}

	// -TH3: mất cân bằng trái phải (xoay trái cây con trái - xoay phải cây gốc)
	if (balance > 1 && getBalance(pRoot->pLeft) < 0) {
		cout << pRoot->key << " Mat can bang trai phai.\n";
		leftRotate(pRoot->pLeft);
		rightRotate(pRoot);
		return;
	}

	// -TH4: mất cân bằng phải trái (xoay phải cây con phải - xoay trái cây gốc)
	if (balance < -1 && getBalance(pRoot->pRight) > 0) {
		cout << pRoot->key << " Mat can bang phai trai.\n";
		rightRotate(pRoot->pRight);
		leftRotate(pRoot);
		return;
	}
}

void SaveAVLTree(AVLNode* pRoot) {
	ofstream fout("avl_tree.txt");
	if (!fout.is_open()) {
		cout << "Can't open avl_tree.txt to write.\n";
		exit(1);
	}
	if (!pRoot)
		return;
	queue<AVLNode*> nodeQueue;
	nodeQueue.push(pRoot);
	while (!nodeQueue.empty()) {
		AVLNode* currNode = nodeQueue.front();
		fout << currNode->key << ": " << currNode->data.en << endl;
		nodeQueue.pop();
		if (currNode->pLeft)
			nodeQueue.push(currNode->pLeft);
		if (currNode->pRight)
			nodeQueue.push(currNode->pRight);
	}
	fout.close();
	cout << "Successfully write data to avl_tree.txt.\n";
}

void SaveKey(AVLNode* pRoot) {
	ofstream fout("key.txt");
	if (!fout.is_open()) {
		cout << "Can't open key.txt to write.\n";
		exit(1);
	}
	if (!pRoot)
		return;
	queue<AVLNode*> nodeQueue;
	nodeQueue.push(pRoot);
	while (!nodeQueue.empty()) {
		AVLNode* currNode = nodeQueue.front();
		fout << currNode->key << ",";
		nodeQueue.pop();
		if (currNode->pLeft)
			nodeQueue.push(currNode->pLeft);
		if (currNode->pRight)
			nodeQueue.push(currNode->pRight);
	}
	fout.close();
	cout << "Successfully write keys to key.txt.\n";
}

//Đồ thị đang xét là đồ thị vô hướng

vector<vector<int>> createEdgeList(int so_luong_canh) {
	int x, y;
	vector<vector<int>> edges;
	for (int i = 0; i < so_luong_canh; i++) {
		cin >> x >> y;
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

int** convertAdjacencyMatrix(vector<vector<int>> edges, int n, int so_luong_canh) {
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

//c. Hàm chuyển đổi danh sách kề thành ma trận kề
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

int main() {
	//===== Cau01: =====
	/*string file_name("data.txt");
	AVLNode* pRoot = readAnimals(file_name);
	SaveKey(pRoot);
	SaveAVLTree(pRoot);
	system("pause");*/
	/*while (1) {
		string delete_en;
		system("cls");
		LevelOrder(pRoot);
		cout << "\n=======================================\n";
		cout << "Nhap ten con vat muon xoa: ";
		cin >> delete_en;
		removeNode(pRoot, delete_en);
		system("pause");
	}*/
	
	//===== Cau02: =====
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
	int** matrix = convertAdjacencyMatrix(edges, n, so_luong_canh);
	PrintMatrix(matrix, n);
	cout << "--------------------------\n";
	vector <int>* list = matrixToList(matrix, n);
	//Tính mảng answer
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
	for (int i = 0; i < n; i++)
		cout << answer[i] << " ";
	return 0;
}