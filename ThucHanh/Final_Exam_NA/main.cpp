#include<iostream>
#include<algorithm>
#include<vector>
#include <fstream>
#include <string>
using namespace std;
#define hashTableSize 26

// Cau 1
// 1.a

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void BuildMaxHeap(int arr[], int n) // Ham xay dung min heap
{
	for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}


// 1.b
void HeapSort(int arr[], int n) // Ham sap xep mang bang heap sort
{
	BuildMaxHeap(arr, n);

    for (int i = n - 1; i >= 0; i--) {
        //Hoán đổi max trên đầu max heap với giá trị cuối mảng
        //Sau đó lại điều chỉnh max heap lại
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Cau 2

struct Node {
	int key;
	Node* left;
	Node* right;
};

Node* createNode(int x){
	Node* new_node = new Node;
	new_node->key = x;
	new_node->left = new_node->right = NULL;
	return new_node;
}

void Insert(Node*& pRoot, int x){
	
	if(!pRoot){
		Node* new_node = createNode(x);
		pRoot = new_node;
	}
	if (x == pRoot->key)
		return;	
	else if (x < pRoot->key)
		Insert(pRoot->left,x);
	else if (x > pRoot->key)
		Insert(pRoot->right,x);
}

//2.a
Node* createBST(int arr[], int n)
{
	Node* pRoot = NULL;
	for (int i = 0; i < n; i++)
		Insert(pRoot, arr[i]);
	return pRoot;
}

//2.b 
//Nếu cây có 1 Node thì chiều cao là 0
int calHeight(Node* root)
{
	if (!root)
		return -1;
	return max(calHeight(root->left), calHeight(root->right)) + 1;
}
//2.c
bool isAVL(Node* root)
{
	if (!root)
        return true;

    int lh = calHeight(root->left);
    int rh = calHeight(root->right);

    return (abs(lh - rh) <= 1) && isAVL(root->left) && isAVL(root->right);
}


// Cau 3
bool DelimeterChecker(string expression)
{
	return false;
}

// Cau 4
string ds_loai[6] = { "vat nuoi", "dong vat hoang da", "con trung", "luong cu","dong vat duoi nuoc", "loai chim" };

struct Animal {
	string en;
	string ph;
	string vn;
	int loai;
};

//4.1
vector<Animal> readAnimals(string file_name) {
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
//4.2
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

HNode** saveAnimals(vector<Animal> animal_list) {
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
//4.3
HNode* searchAnimal(HNode** hash_table, string name)
{
	int i = hashKey(name[0]) % hashTableSize;
	HNode* temp = hash_table[i];
	while (temp) {
		if (temp->data.en == name)
			return temp;
		temp = temp->pNext;
	}
	return nullptr; 
}

// Sinh vien khong thay doi doan code duoi day
vector<int> nodes;
void traverse(Node* root)
{
	if (root == NULL) {
		return;
	}
	traverse(root->left);
	nodes.push_back(root->key);
	traverse(root->right);
}

int main()
{
	int arr[11] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	int n = 11;

	int c_r[11] = { 17, 15, 13, 9, 6, 5, 10, 4, 8, 3,1 };
	BuildMaxHeap(arr, n);
	
	bool flag = true;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] != c_r[i])
		{
			flag = false;
			break;
		}
	}
	if (flag == false) {
		cout << "Cau 1.a sai!" << endl;
	}
	else {
		cout << "Cau 1.a dung!" << endl;
	}

	HeapSort(arr, n);
	if (is_sorted(arr, arr + n))
	{
		cout << "Cau 1.b dung!" << endl;
	}
	else {
		cout << "Cau 1.b sai" << endl;
	}

	int arr_2[10] = { 5,2,7,1,4,6,5,3,9,6 };
	n = 10;

	Node* root = createBST(arr_2, n);
	traverse(root);
	int c_r_2[10] = { 1,2,3,4,5,6,7,9,15,16 };
	flag = true;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] != c_r_2[i])
		{
			flag = false;
			break;
		}
	}
	if (flag == true && nodes.size() > 0)
	{
		cout << "Cau 2.a dung" << endl;
	}
	else {
		cout << "Cau 2.a sai" << endl;
	}

	int height = calHeight(root);
	if (height == 3)
	{
		cout << "Cau 2.b dung" << endl;
	}
	else {
		cout << "Cau 2.b sai" << endl;
	}

	bool is_avl = isAVL(root);
	if (is_avl == false)
	{
		cout << "Cau 2.c sai" << endl;
	}
	else {
		cout << "Cau 2.c dung" << endl;
	}

	vector<Animal>animal_list = readAnimals("Animal.txt");
	Print_Animal_List(animal_list);

	cout << "\nCHUC CAC BAN LAM BAI TOT!" << endl;
}