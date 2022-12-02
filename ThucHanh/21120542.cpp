#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;
int p = 31;
long long m = (long long)(pow(10, 9) + 9);
int hashTableSize = 2000;

struct Company
{
	string name;
	string tax_code;
	string address;
};

Company readCompany(string company_info) {
	stringstream ss(company_info);
	vector<string> v;
	Company company;
	string buffer;
	while (getline(ss, buffer, '|')) {
		v.push_back(buffer);
	}
	company.name = v[0];
	company.tax_code = v[1];
	company.address = v[2];

	return company;
}

vector<Company> ReadCompanyList(string file_name) {
	ifstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Can't open " << file_name << " to read.\n";
		exit(1);
	}

	vector <Company> results;
	vector <string> lines;
	string company_info;

	getline(fin, company_info);
	while(getline(fin, company_info)) {
		Company company = readCompany(company_info);
		results.push_back(company);
	}
	cout << "Successfully read " << file_name << endl;
	fin.close();
	return results;

}

long long powMod(int p, int j) {
	long long n = pow(p, j);
	long long k = n;
	long long h = (n + 1);
	if (k % 2 == 0) k /= 2;
	else h /= 2;
	// tinh ket qua cua (k*h)%d
	long long kq = ((k % m) * (h % m)) % m;

	return kq;
}

long long HashString(string company_name) {
	unsigned long long hash = 0;
	unsigned int com_size = company_name.size();
	int j = 0;
	if (com_size >= 20) {
		for (int i = com_size - 1; j <= 19; i--)
			hash = hash + (((long long)(company_name[i] - '0') % m) * powMod(p, j++)) % m;
	}
	else {
		for (int i = com_size - 1; i >= 0; i--)
			hash = hash + (((long long)(company_name[i] - '0') % m) * powMod(p, j++)) % m;
	}
	//(a+b) mod m = (a mod m + b mod m) mod m
	//(a*b) mod m = ( a mod m * b mod m ) mod m

	//(a + b + c) mod m = (a mod m + b mod m + c mod m) mod m
	// a mod m = (s[i] mod m) * (p^i mod m)
	// p^i mod m = p^c mod m + p^b mod m Với b + c = m

	return hash % m ;
}

bool isFull(Company* hash_table) {
	while()
}

void Insert(Company* hash_table, Company company){
	long long i = HashString(company.name) % hashTableSize ;
	while (!hash_table[i%2000].name.empty()) {
		i++;
	}
	hash_table[i] = company;

}

//Company* CreateHashTable(vector<Company> list_company) {
//	Company table[2000]{0};
//	
//}



//Company* Search(Company* hash_table, string company_name) {
//
//}

int main() {
	system("cls");
	string file_name("data.txt");
	vector <Company> Company_list = ReadCompanyList(file_name);
	for (int i = 0; i < 10; i++)
		cout << HashString(Company_list[i].name) << endl;
		
	return 0;
}