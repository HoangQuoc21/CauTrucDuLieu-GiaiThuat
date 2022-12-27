#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
#define m 17

int HashKey(string name) {
	int key = 0;
	for (int i = 0; i < name.size(); i++)
		key += (int)name[i] - 96;
	return key % m;
}

vector<string> ReadName(string file_name) {
	vector<string> names;
	ifstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Can't open " << file_name << " to read.\n";
		exit(1);
	}
	string line;
	while (!fin.eof()) {
		getline(fin, line);
		names.push_back(line);
	}
	fin.close();
	cout << "Successfully read " << file_name << endl;
	return names;
}

//a) ==================================================================

void push_a(string* hash_table, string name) {
	int key = HashKey(name);
	int i = 0;
	while (!hash_table[(int)(key + pow(i, 2)) % m].empty()) {
		cout << name << "[" << key  << "], collocation: " << i + 1 << ", at: " << (int)(key + pow(i, 2)) % m << endl;
		i++;
	}
	hash_table[(int)(key + pow(i, 2)) % m] = name;
	cout << name << "[" << key << "] >> " << (int)(key + pow(i, 2)) % m << endl;
	cout << "-----------------------------------------\n";
}

string* CreateHashTableA(vector<string> names) {
	string* hash_table = new string[m];
	cout << "=========================================\n";
	for (int i = 0; i < names.size(); i++)
		push_a(hash_table, names[i]);
	cout << "=========================================\n";
	return hash_table;
}

void WriteFileA(string* hash_table) {
	ofstream fout("hash_table_a.txt");
	if (!fout.is_open()) {
		cout << "Cant't open hash_table_a.txt ro write.\n";
		exit(1);
	}
	fout << "HASH TABLE A:\n";
	fout << "=========================================\n";
	for (int i = 0; i < m; i++) {
		fout << i << ": " << hash_table[i] << endl;
		fout << "-----------------------------------\n";
	}
	fout << "=========================================\n";
	cout << "Succesfully write hash table a to hash_table_a.txt.\n";
	fout.close();
}

//b) ==========================================================================
int HashKeySecond(string name) {
	int key = 0;
	for (int i = 0; i < name.size(); i++)
		key += (int)name[i] - 96;
	return 1 + key % 7;
}

void push_b(string* hash_table, string name) {
	int key = HashKey(name);
	int i = 0;
	while (!hash_table[key % m].empty()) {
		cout << name << "[" << key << "], collocation: " << i + 1 << ", at: " << key << endl;
		i++;
		key = HashKey(name) + i * HashKeySecond(name);
	}
	hash_table[key % m] = name;
	cout << name << "[" << key << "] >> " << key % m << endl;
	cout << "-----------------------------------------\n";
}

string* CreateHashTableB(vector<string> names) {
	string* hash_table = new string[m];
	for (int i = 0; i < names.size(); i++)
		push_b(hash_table, names[i]);
	return hash_table;
}

void WriteFileB(string* hash_table) {
	ofstream fout("hash_table_b.txt");
	if (!fout.is_open()) {
		cout << "Cant't open hash_table_a.txt ro write.\n";
		exit(1);
	}
	fout << "HASH TABLE B:\n";
	fout << "=========================================\n";
	for (int i = 0; i < m; i++) {
		fout << i << ": " << hash_table[i] << endl;
		fout << "-----------------------------------\n";
	}
	fout << "=========================================\n";
	cout << "Succesfully write hash table b to hash_table_b.txt.\n";
	fout.close();
}


int main() {
	system("cls");
	string file_name = "names.txt";
	vector <string> names = ReadName(file_name);
	string* hash_table_a = CreateHashTableA(names);
	WriteFileA(hash_table_a);
	cout << "*************************************************************************\n";
	string* hash_table_b = CreateHashTableB(names);
	WriteFileB(hash_table_b);
	return 0;
}