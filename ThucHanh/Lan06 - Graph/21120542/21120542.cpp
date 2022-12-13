#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
#define MAX 100

//I. CÁC HÀM ĐỌC/ IN/ CHUYỂN ĐỔI: 
//1. CÁC HÀM VỚI MA TRẬN KỀ:
//a. Hàm đọc ma trận kề từ 1 file:
int** readMatrix(string file_name, int& vertices) {
	vertices = 0;
	fstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Cann't open " << file_name << " to read matrix.\n";
		exit(1);
	}
	else {
		//Lay so dinh va tao mang dong 2 chieu kich thuoc dinh+1 x dinh+1 (ko su dung cot/ hang 0)
		string line;
		getline(fin, line, '\n');
		vertices = stoi(line);
		int** matrix = new int* [vertices];
		for (int i = 0; i < vertices; i++)
			matrix[i] = new int[vertices];

		vector<int> buffer;
		while (getline(fin, line)) {
			stringstream ss(line);
			string adj;
			while (getline(ss, adj, ' '))
				buffer.push_back(stoi(adj));
		}

		int index = 0;
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++)
				matrix[i][j] = buffer[index++];
		}
		cout << "Successfully read " << file_name << endl;
		fin.close();
		return &*matrix;
	}
}

//b. Hàm in ma trận kề:
void printMatrix(int** matrix, int vertices) {
	cout << "    ";
	for (int i = 0; i < vertices; i++)
		cout << "[" << i << "]";
	cout << endl;
	for (int i = 0; i < vertices; i++) {
		cout << "[" << i << "]: ";
		for (int j = 0; j < vertices; j++)
			cout << matrix[i][j] << "  ";
		cout << endl;
	}
}

//c. Hàm chuyển đổi danh sách kề thành ma trận kề:
int** listToMatrix(vector <int>* list, int vertices) {
	int** matrix = new int* [vertices];
	for (int i = 0; i < vertices; i++)
		matrix[i] = new int[vertices] {};

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < list[i].size(); j++)
			matrix[i][list[i][j]] = 1;

	return matrix;
}

//2. CÁC HÀM VỚI DANH SÁCH KỀ:
//a. Hàm đọc danh sách kề từ file:
vector<int>* readList(string file_name, int vertices) {
	fstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Cann't open " << file_name << " to read.\n";
		exit(1);
	}
	else {
		vector <int>* list = new vector<int>[vertices];
		string line;
		getline(fin, line);
		int index = 0;
		
		while (getline(fin, line)) {
			stringstream ss(line);
			string adj;
			vector <int> buffer;
			while (getline(ss, adj, ' '))
				buffer.push_back(stoi(adj));
			int buffer_size = (int)buffer.size();
			for (int i = 0; i < buffer_size; i++)
				list[index].push_back(buffer[i]);
			index++;
		}
		cout << "Successfully read " << file_name << endl;
		fin.close();
		return list;
	}
}

//b. Hàm in danh sách kề:
void printList(vector<int>* list, int vertices) {
	for (int i = 0; i < vertices; i++) {
		cout << "[" << i << "]: ";
		for (int j = 0; j < list[i].size(); j++)
			cout << list[i][j] << " ";
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

//II. CÁC HÀM VỚI ĐỒ THỊ CÓ HƯỚNG VÀ ĐỒ THỊ VÔ HƯỚNG 
//1. Hàm kiểm tra đồ thị có hướng (true -> đồ thị có hướng, false -> đồ thị vô hướng)
bool isDirected(int** matrix, int vertices) {
	for (int i = 0; i < vertices; i++)
		for (int j = i; j < vertices; j++)
			if (matrix[i][j] != matrix[j][i])
				return true;
	return false;
}

//2. Hàm đếm cạnh của đồ thị:
int countEdges(int** matrix, vector<int>* list, int vertices) {
	int edges = 0;
	//Với đồ thị có hướng:
	if (isDirected(matrix, vertices)) {
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < list[i].size(); j++)
				edges++;
	}
	//Với đồ thị vô hướng:
	else {
		for (int i = 0; i < vertices; i++)
			for (int j = i; j < vertices; j++)
				edges = edges + matrix[i][j];
	}
	return edges;
}

//3. Hàm trả về bậc của các đỉnh:
//a. Với đồ thị có hướng:
//-Hàm trả về vector chứa bậc ngoài và bậc trong của từng đỉnh:
//Sử dụng vector pair với first là bậc ngoài, second là bậc trong
vector<pair<int, int>> degreeDirectedGraph(int** matrix, int vertices) {
	vector<pair<int, int>> degrees;
	for (int i = 0; i < vertices; i++) {
		int out_degree = 0;
		int in_degree = 0;
		for (int j = 0; j < vertices; j++) {
			if (matrix[i][j] == 1)
				out_degree++;
			if (matrix[j][i] == 1)
				in_degree++;
		}
		degrees.push_back({ out_degree,in_degree });
	}
	return degrees;
}

//Hàm in bậc ngoài và bậc trong của các đỉnh của đồ thị có hướng:
void printDegreesDirectedGraph(vector<pair<int, int>> degrees) {
	cout << "               Out|In\n";
	for (int i = 0; i < degrees.size(); i++)
		cout << "Degrees of [" << i << "]:  " << degrees[i].first << " " << degrees[i].second << endl;
}

//b. Với đồ thị vô hướng
///-Hàm trả về vector chứa bậc của từng đỉnh:
vector<int> degreeUndirectedGraph(int** matrix, int vertices) {
	vector <int> degrees;
	for (int i = 0; i < vertices; i++) {
		int current_vertice = 0;
		for (int j = 0; j < vertices; j++)
			if (matrix[i][j] == 1)
				current_vertice++;
		degrees.push_back(current_vertice);
	}
	return degrees;
}

//Hàm in bậc của các đỉnh của đồ thị vô hướng:
void printDegreesUndirectedGraph(vector <int> degrees) {
	for (int i = 0; i < degrees.size(); i++)
		cout << "Degrees of [" << i << "]: " << degrees[i] << endl;
}

//4. Hàm trả về các đỉnh cô lập:
vector<int> isolatedVertices(int** matrix, vector<int>* list, int vertices) {
	vector <int> isolated_vertices;
	//Với đồ thị có hướng
	if (isDirected(matrix, vertices)) {
		vector<pair<int, int>> degrees = degreeDirectedGraph(matrix, vertices);
		for (int i = 0; i < vertices; i++)
			if (degrees[i].first + degrees[i].second == 0)
				isolated_vertices.push_back(i);
	}
	//Với đồ thị vô hướng
	else {
		vector<int> degrees = degreeUndirectedGraph(matrix, vertices);
		for (int i = 0; i < degrees.size(); i++)
			if (degrees[i] == 0)
				isolated_vertices.push_back(i);
	}
	return isolated_vertices;
}

//5. Hàm trả về các đỉnh lá
vector<int> leafVertices(int** matrix, vector<int>* list, int vertices) {
	vector <int> leaf_vertices;
	//Với đồ thị có hướng
	if (isDirected(matrix, vertices)) {
		vector<pair<int, int>> degrees = degreeDirectedGraph(matrix, vertices);
		for (int i = 0; i < vertices; i++)
			if (degrees[i].first + degrees[i].second == 1)
				leaf_vertices.push_back(i);
	}
	//Với đồ thị vô hướng
	else {
		vector<int> degrees = degreeUndirectedGraph(matrix, vertices);
		for (int i = 0; i < degrees.size(); i++)
			if (degrees[i] == 1)
				leaf_vertices.push_back(i);
	}
	return leaf_vertices;
}

//6. Hàm kiểm tra đồ thị có phải đồ thị đầy đủ hay không
//Đồ thị đầy đủ là đồ thị đơn vô hướng
bool isCompleteGraph(int**matrix, int vertices, int edges) {
	if (!isDirected(matrix, vertices) && edges == (vertices * (vertices - 1) / 2)) {
		vector<int> degrees = degreeUndirectedGraph(matrix, vertices);
		for (int x : degrees) {
			if (x != vertices - 1)
				return false;
		}
		return true;
	}
	return false;
}

//7. Hàm kiểm tra đồ thị có phải đồ thị vòng hay không
bool isCircularGraph(int** matrix, int vertices, int edges) {
	if (vertices <= 2 || vertices != edges)
		return false;
	if (isDirected(matrix, vertices)) {
		//Với đồ thị có hướng
		vector<pair<int, int>> degrees = degreeDirectedGraph(matrix, vertices);
		for (auto x : degrees)
			if (x.first != 1 || x.second != 1)
				return false;
	}
	else {
		//Với đồ thị vô hướng
		vector<int> degrees = degreeUndirectedGraph(matrix, vertices);
		for (auto x : degrees)
			if (x != 2)
				return false;
	}
	return true;
}

//III. CÁC THUẬT TOÁN CÓ SỬ DỤNG DFS/BFS:
//Đồ thị đang xét là đơn đồ thị, nghĩa là không có khuyên hay cạnh song song

//1. Hàm DFS và BFS cơ bản (duyệt qua rồi in thứ tự đỉnh duyệt):
//LƯU Ý, 2 HÀM NÀY CHỈ DUYỆT QUA 1 THÀNH PHẦN LIÊN THÔNG
//a. DFS (duyệt theo chiều sâu - đệ quy):
void DFS1(vector<int>* list, int u, bool visited[MAX]) {
	cout << u << " ";
	visited[u] = true;
	for (int v : list[u]) {
		if (!visited[v])
			DFS1(list, v, visited);
	}
}

//b. BFS (duyệt theo chiều ngang - hàng đợi):
void BFS1(vector<int>* list, int u, bool visited[MAX]) {
	queue<int> dinh;
	dinh.push(u);
	visited[u] = true;
	while (!dinh.empty()) {
		int v = dinh.front();
		dinh.pop();
		cout << v << " ";
		for (int x : list[v])
			if (!visited[x]) {
				dinh.push(x);
				visited[x] = true;
			}
	}
}

//2. Hàm DFS và BFS duyệt qua tất cả thành phần liên thông:
//a. DFS:
void DFS2(vector<int>* list, int vertices, bool visited[MAX]) {
	for (int i = 0; i < vertices; i++)
		if (!visited[i]) {
			//Liệt kê các đỉnh của 1 thành phần liên thông
			DFS1(list, i, visited);
			cout << endl;
		}
}

//b.BFS:
void BFS2(vector<int>* list, int vertices, bool visited[MAX]) {
	for (int i = 0; i < vertices; i++)
		if (!visited[i]) {
			//Liệt kê các đỉnh của 1 thành phần liên thông
			BFS1(list, i, visited);
			cout << endl;
		}
}

//3. Hàm đếm thành phần liên thông:
//a. Đếm thành phần liên thông thường:
//DFS3 chỉ duyệt, ko in ra các đỉnh của thành phần liên thông đang xét
void DFS3(vector<int>* list, int u, bool visited[MAX]) {
	visited[u] = true;
	for (int v : list[u])
		if (!visited[v])
			DFS3(list, v, visited);
}

int countConnectedComponent(vector<int>* list, int vertices, bool visited[MAX]) {
	int count = 0;
	for (int i = 0; i < vertices; i++) {
		if (!visited[i]) {
			count++;
			DFS3(list, i, visited);
			//BFS
		}
	}
	return count;
}

//b. Đếm thành phần liên thông là cây:
//DFS4 vừa duyệt chiều sâu, vừa kiểm tra thành phần liên thông đang duyệt có tồn tại chu trình hay không 
bool DFS4(vector<int>* list, int par, int u, bool visited[MAX]) {
	bool isCycle = true;
	visited[u] = true;
	for (int v : list[u]) {
		if (!visited[v]) {
			if (DFS4(list, u, v, visited))
				isCycle = true;
			else
				isCycle = false;
		}
		else if (u != par) {
			//cout << u << endl;
			isCycle = false;
		}	
	}
	return isCycle;
}

int countTreeConnectedComponent(vector<int>* list, int vertices,bool visited[MAX]) {
	int count = 0;
	for (int i = 0; i < vertices; i++) {
		if (!visited[i]) {
			//Nếu duyệt qua DFS (lấy dc 1 thành phần liên thông) mà thành phần liên thông đó không có chu trình thì thành phần liên thông đó là thành phần liên thông cây
			if (!DFS4(list, i, 0, visited)) {
				//cout << "Thanh phan lien thong cay: " << i << endl;
				count++;
			}
			//BFS
		}
	}
	return count;
}

//4. Hàm kiểm tra đồ thị có phải đồ thị hai phía hay không 
//Thường check = tô màu, 1 phía là 1 màu, nếu đồ thị chỉ có 2 màu thì là đồ thị 2 phía
//-Hàm BFS để tô màu 1 thành phần liên thông:
// Quy định mảng màu: 0 -> noncolor; 1 -> Red; 2 -> Blue
bool BFS3(vector<int>* list, int u, int color[MAX]) {
	queue<int> q;
	q.push(u);
	color[u] = 1; //Red
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int x : list[v]) {
			if (color[x] == 0) {
				//Tô màu các đỉnh kề với đỉnh đang xét (khác màu)
				if (color[v] == 1)
					color[x] = 2; //Blue
				else if (color[v] == 2)
					color[x] = 1; //Red
				q.push(x);
			}
			//Nếu gặp 1 đỉnh kề giống màu với đỉnh đang xét thì return false
			else if (color[x] == color[v])
				return false;
		}
	}
	//Duyệt qua hết mà ko bị sai thì return true
	return true;
}

bool isBiGraph(vector<int>* list,int vertices, int color[MAX]) {
	for (int i = 0; i < vertices; i++) {
		//Nếu đỉnh i chưa được tô màu
		if (color[i] == 0) {
			//Nếu 1 thành phần liên thông không phải 2 phía thì là sai
			if (!BFS3(list, i, color))
				return false;
		}
	}
	return true;
}

//5. Hàm kiểm tra đồ thị có phải đồ thị hai phía đầy đủ hay không 
//Đồ thị 2 phía sẽ có 2 tập có lần lượt m đỉnh và n đỉnh  (m+n = số đỉnh ban đầu của đồ thị)
//Đồ thị 2 phía đầy đủ có số cạnh = m*n
bool isCompleteBiGraph(int **matrix, vector<int>* list, int vertices, int edges, int color[MAX]) {
	if (isBiGraph(list, vertices, color)) {
		int reds = 0;
		int blues = 0;
		for (int i = 0; i < vertices; i++)
			if (color[i] == 1)
				reds++;
			else if (color[i] == 2)
				blues++;
		return (edges == reds * blues);
	}
	return false;
}

//6. Hàm đếm đỉnh trụ (khớp) và cạnh cầu:
//Loại bỏ đỉnh trụ hoặc cạnh cầu thì sẽ làm tăng thành phần liên thông lên
//a. Hàm đếm đỉnh trụ(khớp):
int countCutVertices(vector<int>* list, int vertices, bool visited[MAX]) {
	//Lấy số thành phần liên thông ban đầu
	int base_connected_components = countConnectedComponent(list, vertices, visited);
	int count_cut_vertices = 0;
	//Tiến hành loại bỏ từng đỉnh (Cho giá trị của đỉnh đó trong visited = true) rồi đếm lại thành phần liên thông, nếu lớn hơn ban đầu thì đỉnh đó là đỉnh trụ
	for (int i = 0; i < vertices; i++) {
		memset(visited, false, MAX);
		visited[i] = true;
		int current_connected_components = countConnectedComponent(list, vertices, visited);
		if (current_connected_components > base_connected_components) {
			//cout << i << " ";
			count_cut_vertices++;
		}
	}
	return count_cut_vertices;
}

//b. Hàm đếm cạnh cầu:
//*Sử dụng danh sách cạnh để lưu các cạnh dưới dạng (đỉnh đầu-đỉnh cuối)
//-Hàm tạo 1 danh sách cạnh từ 1 danh sách kề:
vector<pair<int, int>> edgeList(vector<int>*list, int vertices) {
	vector<pair<int, int>> edge_list;
	for (int x = 0; x < vertices; x++) {
		for (int y : list[x]) {
			if (list[x].size() > 0)
				edge_list.push_back({ x,y });
		}
	}
	return edge_list;
}

//-Hàm in danh sách cạnh
void printEdgeList(vector<pair<int, int>> edgeList) {
	for (auto it : edgeList)
		cout << it.first << " " << it.second << endl;
}

//-Hàm DFS duyệt bỏ qua cạnh (x-y):
void DFS5(vector<int>* list, int u,int x,int y, bool visited[MAX]) {
	visited[u] = true;
	for (int v : list[u]) {
		if (u == x && v == y || v == x && u == y)
			//Bỏ qua cạnh (x-y)
			continue;
		if (!visited[v])
			DFS5(list, v, x, y, visited);
	}
}
int countBridgeEdges(vector<int>* list, vector<pair<int, int>> edge_list,  int vertices, bool visited[MAX]) {
	//Lấy số thành phần liên thông ban đầu
	int base_connected_components = countConnectedComponent(list, vertices, visited);
	int count_briged_edges = 0;
	for (auto it : edge_list) {
		int x = it.first;
		int y = it.second;
		memset(visited, false, MAX);
		int current_connected_components = 0;
		for (int i = 0; i < vertices; i++) {
			if (!visited[i]) {
				current_connected_components++;
				DFS5(list, i, x, y, visited);
			}
		}
		if (current_connected_components > base_connected_components) {
			count_briged_edges++;
			//cout << x << " " << y << endl;
		}
	}
	return count_briged_edges;
}


int main() {
	string matrix_file, list_file;
	int vertices, edges;
	cout << "*******************************************************\n";
	cout << "*                  HOME WORK 3: GRAPH                 *\n";
	cout << "*******************************************************\n";
	cout << "Iput the file containing adjacency matrix: ";
	cin >> matrix_file;
	cout << "Iput the file containing adjacency list: ";
	cin >> list_file;
	
	int** matrix = readMatrix(matrix_file, vertices);
	vector<int>* list = readList(list_file, vertices);
	vector<pair<int, int>> edge_list = edgeList(list, vertices);
	edges = countEdges(matrix, list, vertices);
	cout << "=======================================================\n";
	if (isDirected(matrix, vertices))
		cout << "-This is a Directed Graph.\n";
	else
		cout << "-This is an Undirected Graph.\n";
	cout << "-Number of Vertices: " << vertices << endl;
	cout << "-Number of Edges: " << edges << endl;
	
	cout << "=======================================================\n";
	
	cout << "-- Graph's Adjacency Matrix: --\n";
	printMatrix(listToMatrix(list, vertices), vertices);

	cout << "-- Graph's Adjacency List: --\n";
	printList(matrixToList(matrix, vertices), vertices);

	cout << "-- Graph's Edges List: --\n";
	printEdgeList(edge_list);

	cout << "=======================================================\n";

	cout << "-- Vertices Degree: --\n";
	if (isDirected(matrix, vertices)) {
		vector<pair<int, int>> degrees = degreeDirectedGraph(matrix, vertices);
		printDegreesDirectedGraph(degrees);
	}
	else {
		vector<int> degrees = degreeUndirectedGraph(matrix, vertices);
		printDegreesUndirectedGraph(degrees);
	}
	

	cout << "-- Isolated Vertices: --\n";
	vector<int> isolated_vertices = isolatedVertices(matrix, list, vertices);
	for (int i = 0; i < isolated_vertices.size(); i++)
		cout << isolated_vertices[i] << " ";
	cout << endl;

	cout << "-- Leaf Vertices: --\n";
	vector<int> leaf_vertices = leafVertices(matrix, list, vertices);
	for (int i = 0; i < leaf_vertices.size(); i++)
		cout << leaf_vertices[i] << " ";
	cout << endl;

	cout << "=======================================================\n";
	bool visited[MAX]{};
	
	cout << "-- Graph Browsing In DFS: --\n";
	DFS2(list,vertices, visited);
	
	cout << "-- Graph Browsing In BFS: --\n";
	//Đưa các giá trị trong mảng visited về false đế tiếp tục dùng mảng này cho những thao tác có duyệt DFS hoặc BFS tiếp theo 
	memset(visited, false, MAX);
	BFS2(list, vertices, visited);
	
	memset(visited, false, MAX);
	int component = countConnectedComponent(list, vertices,visited);
	cout << "-Number of connected components: " << component << endl;
	
	memset(visited, false, MAX);
	int treeComponent = countTreeConnectedComponent(list,vertices, visited);
	cout << "-Number of tree connected components: " << treeComponent << endl
		;
	cout << "=======================================================\n";
	if (isCompleteGraph(matrix, vertices, edges))
		cout << "-This is a complete graph.\n";
	else
		cout << "-This is not a complete graph.\n";

	if (isCircularGraph(matrix, vertices, edges))
		cout << "-This is a circular graph.\n";
	else
		cout << "-This is not a circular graph.\n";
	
	int color[MAX]{};
	if (isBiGraph(list, vertices, color))
		cout << "-This is a bigraph.\n";
	else
		cout << "-This is not a bigraph.\n";
	
	memset(color, 0, MAX);
	if(isCompleteBiGraph(matrix, list, vertices, edges, color))
		cout << "-This is a complete bigraph.\n"; 
	else
		cout << "-This is not a complete bigraph.\n";
	cout << "=======================================================\n";
	
	memset(visited, false, MAX);
	cout << "-Number of cut vertices: " << countCutVertices(list, vertices, visited) << endl;
	
	memset(visited, false, MAX);
	cout << "-Number of bridge edges: " << countBridgeEdges(list, edge_list, vertices, visited) << endl;
	
	cout << "=======================================================\n";

	return 0;
}