#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

#define MAX 100
using namespace std;

//#2: CÓ 3 CÁCH ĐỂ LƯU ĐỒ THỊ TRONG LẬP TRÌNH
//1. Dùng ma trận kề
void nhapMaTranKe(int maTranKe[][MAX], int soCanh) {
	for (int i = 1; i <= soCanh; i++) {
		//Nhập vào cặp cạnh kề nhau
		cout << "Canh " << i << ": ";
		int x, y;
		cin >> x >> y;
		maTranKe[x][y] = maTranKe[y][x] = 1;
	}
}

void inMaTranKe(int a[][MAX], int soDinh) {
	for (int i = 1; i <= soDinh; i++) {
		for (int j = 1; j <= soDinh; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

//2.Dùng danh sách kề (các đỉnh kề với 1 đỉnh)
void nhapDanhSachKe(vector<int> DSKe[MAX], int soCanh) {
	for (int i = 1; i <= soCanh; i++){
		cout << "Canh " << i << ": ";
		int x, y;
		cin >> x >> y;
		DSKe[x].push_back(y);
		DSKe[y].push_back(x);
	}
}

void inDanhSachKe(vector<int> DSKe[MAX], int soDinh) {
	for (int i = 1; i <= soDinh; i++) {
		cout << i << ": ";
		for (int x : DSKe[i])
			cout << x << " ";
		cout << endl;
	}
}

//3. Cho ma trận kề, chuyển sang danh sách các cạnh tương ứng
void docMaTranKeRaDSCanh(int maTranKe[][MAX], vector<pair<int, int>> &DSCanh, int soDinh) {
	for (int i = 1; i <= soDinh; i++) {
		for (int j = 1; j <= soDinh; j++) {
			if (maTranKe[i][j] && i < j)
				DSCanh.push_back({ i,j });
		}
	}
}

void inDanhSachCanh(vector<pair<int, int>> DSCanh) {
	for (auto x : DSCanh)
		cout << x.first << " " << x.second << endl;
}

//Đồ thị test: 
// 5 
// 9
//1 2
//1 3
//1 4
//2 3
//2 4
//2 5
//3 4
//3 5
//4 5

void docMaTranKe(int maTranKe[][MAX], int &soDinh, int&soCanh, string file_name) {
	ifstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Khong mo duoc " << file_name << " de doc.\n";
		exit(1);
	}

	//Lấy số đỉnh
	string line;
	getline(fin, line);
	soDinh = stoi(line);

	//Lưu các giá trị có hoặc ko kề của đỉnh vào vector
	vector<int> coKe;
	while (getline(fin, line)) {
		stringstream ss(line);
		string ke;
		while (getline(ss, ke, ' '))
			coKe.push_back(stoi(ke));
			
	}
	
	//Nhập các giá trị có hoặc ko kề của đỉnh vào ma trận
	int temp = 0;
	for (int i = 1; i <= soDinh; i++) {
		for (int j = 1; j <= soDinh; j++) {
			maTranKe[i][j] = coKe[temp++];
			if ((maTranKe[i][j] == 1) && (i < j))
				soCanh++;
		}
			
	}
	fin.close();
}

//#3: DFS: Tìm kiếm chiều sâu
//9 
//9
//1 2
//1 3
//1 5
//2 4
//3 6
//3 7
//9 3
//5 8
//8 9


void DFS(vector<int> DSKe[MAX], int u, bool daTham[MAX]) {
	cout << u << " ";
	daTham[u] = true;
	for (int v : DSKe[u])
		if (!daTham[v])
			DFS(DSKe, v, daTham);
}

//#4: BFS: Tìm kiếm chiều rộng
//10 
//11 
//1 2
//1 3
//1 5
//1 10
//2 4
//3 6
//3 7
//3 9
//5 8
//6 7
//8 9

void BFS(vector<int> DSKe[MAX], int u, bool daTham[MAX]){
	queue<int> dinh;
	dinh.push(u);
	daTham[u] = 1;
	while (!dinh.empty()) {
		int v = dinh.front();
		dinh.pop();
		//cout << v << " ";

		for (int x : DSKe[v]) {
			if (!daTham[x]) {
				dinh.push(x);
				daTham[x] = 1;
			}
		}
	}
}

//#5: Đếm thành phần liên thông hoặc kiểm tra đồ thị có liên thông hay không
//10
//8
//1 2
//2 3
//2 4
//3 6
//3 7
//6 7
//5 8
//8 9
int demLienThong(vector<int> DSKe[MAX], int soDinh, int u, bool daTham[MAX]) {
	int dem = 0;
	for (int i = 1; i <= soDinh; i++) {
		if (!daTham[i]) {
			dem++;
			DFS(DSKe, i, daTham); 
			//BFS(DSKe, i, daTham);
		}
	}
	return dem;
}



//#6: Tìm đường đi giữa 2 đỉnh trên đồ thị
//7
//7
//1 2
//2 3 
//2 5 
//3 4 
//4 5
//4 7 
//5 6
void DFSPath(vector<int> DSKe[MAX], int u, bool daTham[MAX], int chaMe[MAX]) {
	daTham[u] = 1;
	for (int v : DSKe[u]) {
		if (!daTham[v]) {
			chaMe[v] = u;
			DFSPath(DSKe, v, daTham, chaMe);
		}
	}
}

void duongDi(int dau, int cuoi, vector<int> DSKe[MAX], int chaMe[MAX], bool daTham[MAX]) {
	//DFS nhưng có thêm 1 bước là đưa đỉnh đang xét thành cha mẹ của đỉnh sắp xét
	DFSPath(DSKe, dau, daTham, chaMe);
	if (!daTham[cuoi])
		cout << "khong co duong di";
	else {
		vector <int> duongDi;
		while (cuoi != dau) {
			duongDi.push_back(cuoi);
			cuoi = chaMe[cuoi];
		}
		duongDi.push_back(dau);
		reverse(duongDi.begin(),duongDi.end());
		for (int x : duongDi)
			cout << x << " ";
	}
}

//#7: Áp dụng BFS & DFS trên lưới ô vuông

//#8: Tìm đường đi ngắn nhất giữa 2 điểm trên lưới ô vuông

//#9: Thuật toán sắp xếp Topo trên đồ thị

//#10: Kiểm tra chu trình trên đồ thị dùng DFS
//6
//6
//1 2
//2 3
//2 4
//3 6
//3 7
//6 7
bool chuTrinhDFS(int u, int par, vector<int> DSKe[MAX], bool daTham[MAX]){
	daTham[u] = 1;
	for (int v : DSKe[u]) {
		if (!daTham[v]) {
			if (chuTrinhDFS(v, u, DSKe, daTham))
				return true;
		}
		else if (v != par)
			return true;
	}
	return false;
}

//#12 + #13: Thuật toán Kosaraju: Liệt kê các thành phần liên thông mạnh

//#14: Cấu trúc dữ liệu các tập hợp rời nhau

//#15 + #16: Thuật toán Kruskal tìm cây khung nhỏ nhất
//6
//9
//1 2 12
//1 3 4
//2 3 1
//2 4 5
//2 5 3
//3 5 2
//4 5 3
//4 6 10
//5 6 8

struct Canh {
	int dau;
	int cuoi;
	int trongSo;
};

void make_set(int chaMe[MAX], int size[MAX], int soDinh) {
	for (int i = 1; i <= soDinh; i++){
		chaMe[i] = i;
		size[i] = 1;
	}
}

int find(int dinh, int chaMe[MAX]) {
	if (dinh == chaMe[dinh])
		return dinh;
	return chaMe[dinh] = find(chaMe[dinh], chaMe);
}

//hàm này để kiểm tra thêm cạnh này vào MST mà không tạo thành chu trình
bool Union(int canh1, int canh2, int chaMe[MAX], int size[MAX]) {
	canh1 = find(canh1, chaMe);
	canh2 = find(canh2, chaMe);
	if (canh1 == canh2)
		return false; //Không gộp dc canh1 và canh2
	if (size[canh1] < size[canh2])
		swap(canh1, canh2);
	chaMe[canh2] = canh1;
	size[canh1] += size[canh2];
	return true;
}

bool cmp(Canh a, Canh b) {
	return a.trongSo < b.trongSo;
}

void kruskal(vector <Canh> cacCanh,int soDinh, int soCanh, int chaMe[MAX], int size[MAX]) {
	vector<Canh> mst;
	int tongTrongSo = 0;
	//Sắp xếp các cạnh tăng dần theo trọng số
	sort(cacCanh.begin(), cacCanh.end(), cmp);
	
	//Lặp qua các cạnh
	for (int i = 0; i < soCanh; i++) {
		if (mst.size() == soDinh - 1)
			break;
		//Chọn cạnh có trọng số nhỏ nhất 
		Canh e = cacCanh[i];
		if (Union(e.dau, e.cuoi, chaMe, size)) {
			mst.push_back(e);
			tongTrongSo += e.trongSo;
		}
	}
	//Hiện kết quả
	if (mst.size() != soDinh - 1)
		cout << "Do thi khong lien thong. Khong ton tai MST.\n";
	else {
		cout << "Trong So MST:" << tongTrongSo << endl;
		cout << "Cac canh trong MST la: \n";
		for (int i = 0; i < mst.size(); i++) {
			cout << mst[i].dau << " " << mst[i].cuoi << ": " << mst[i].trongSo << endl;
		}
	}
}

void nhapDSCanh(vector <Canh> &cacCanh, int soCanh) {
	int dau(0), cuoi(0), trongSo(0);
	for (int i = 0; i < soCanh; i++) {
		cin >> dau >> cuoi >> trongSo;
		Canh canh;
		canh.dau = dau;
		canh.cuoi = cuoi;
		canh.trongSo = trongSo;
		cacCanh.push_back(canh);
	}
}

//#17 + #18: Thuật toán Prim tìm cây khung ngắn nhất

void nhapDSCanhKe(vector<pair<int, int>> DSCanhKe[MAX], int soCanh) {
	for (int i = 0; i < soCanh; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		DSCanhKe[x].push_back({ y,w });
		DSCanhKe[y].push_back({ x,w });
	}
}
void prim(vector<pair<int, int>> DSCanhKe[MAX],int soDinh, int soCanh,int dinh, bool daTham[MAX]) {
	vector <Canh> mst;
	int tongTrongSo = 0;
	daTham[dinh] = 1;
	while (mst.size() < soDinh - 1) {
		int min_w = INT_MAX;
		int X(0), Y(0);
		for (int i = 1; i <= soDinh; i++) {
			if (daTham[i]) {
				for (pair<int, int> it : DSCanhKe[i]) {
					int j = it.first, trongSo = it.second;
					if (!daTham[j] && trongSo < min_w) {
						min_w = trongSo;
						X = j; Y = i;
					}
				}
			}
		}
		mst.push_back({ X,Y,min_w });
		tongTrongSo += min_w;
		daTham[X] = 1;
	}
	if (mst.size() != soDinh - 1)
		cout << "Do thi khong lien thong. Khong ton tai MST.\n";
	else {
		cout << "Trong So MST:" << tongTrongSo << endl;
		cout << "Cac canh trong MST la: \n";
		for (int i = 0; i < mst.size(); i++) {
			cout << mst[i].dau << " " << mst[i].cuoi << ": " << mst[i].trongSo << endl;
		}
	}
}

//#19: Thuật toán kiểm tra đồ thị 2 phía

//#20: Kiểm Tra Đỉnh Khớp và Cạnh Cầu

//#21: Thuật toán tìm đường đi ngắn nhất (Dijkstra) 
//6
//8
//1 2 7
//1 3 4
//2 3 2
//2 4 9
//3 5 3
//5 4 4 
//4 6 1
//5 6 5

void dijkstra(vector<pair<int, int>> DSCanhKe[MAX], int soDinh, int s) {
	vector <int> d(soDinh + 1, INT_MAX);
	d[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	// {Khoảng cách, đỉnh}
	Q.push({ 0,s });
	while (!Q.empty()) {
		pair<int, int> top = Q.top();
		Q.pop();
		int u = top.second;
		int kc = top.first;
		if (kc > d[u])
			continue;
		//Cập nhật khoảng cách từ s cho tới mọi đỉnh kề với u
		for (auto it : DSCanhKe[u]) {
			int v = it.first;
			int w = it.second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				Q.push({ d[v], v });
			}
		}
	}
	for (int i = 1; i <= soDinh; i++)
		cout << d[i] << " ";
}

//#22: Chu Trình Euler & Đường Đi Euler
int main() {
	int soDinh(0), soCanh(0);
	cout << "So dinh: ";
	cin >> soDinh;
	cout << "So canh: ";
	cin >> soCanh;

	//1.== THAO TÁC VỚI MA TRẬN KỀ ==
	//int maTranKe[MAX][MAX]{0};
	/*nhapMaTranKe(maTranKe, soCanh);
	inMaTranKe(maTranKe, soDinh);*/

	/*string file_name = "input.txt";
	docMaTranKe(maTranKe, soDinh, soCanh, file_name);
	cout << soDinh << " " << soCanh << endl;
	inMaTranKe(maTranKe, soDinh);*/

	//2.== THAO TÁC VỚI DANH SÁCH KỀ ==
	//vector<int> DSKe[MAX];
	//nhapDanhSachKe(DSKe, soCanh);
	//inDanhSachKe(DSKe, soDinh);

	bool daTham[MAX]{ 0 };
	//DFS(DSKe, 1, daTham);
	//1,2,4,3,6,7,9,8,5

	//BFS(DSKe, 1, daTham);
	//1,2,3,5,10,4,6,7,9,8

	//cout << demLienThong(DSKe, soDinh, 1, daTham) << endl;
	//3

	//int chaMe[MAX]{ 0 };
	//duongDi(1, 7, DSKe, chaMe, daTham);
	//1 2 3 4 7

	//Xét trường hợp có nhiều thành phần liên thông
	/*bool lienThong = 0;
	for (int i = 1; i <= soDinh; i++)
		if (!daTham[i])
			if (chuTrinhDFS(i, 0, DSKe, daTham)){
				lienThong = 1;
				break;
			}
	if (lienThong)
		cout << "Do thi co chu trinh.\n";
	else
		cout << "Do thi khong co chu trinh.\n";*/


	//3. == CÁC THAO TÁC VỚI ĐỒ THỊ CÓ TRỌNG SỐ
	//Cây khung nhỏ nhất:

	//Kruskal
	// int size[MAX]{ 0 };
	//vector<Canh> cacCanh;
	//nhapDSCanh(cacCanh, soCanh);
	//make_set(chaMe, size, soDinh);
	//kruskal(cacCanh, soDinh, soCanh, chaMe, size);

	//Prim
	vector<pair<int, int>> DSCanhKe[MAX];
	nhapDSCanhKe(DSCanhKe, soCanh);
	//prim(DSCanhKe, soDinh, soCanh, 1, daTham);

	//Dijktra:
	dijkstra(DSCanhKe, soDinh, 1);

	return 0;
}