#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

unsigned int p = 31;
unsigned long long m = (pow(10, 9) + 9);
unsigned int hashTableSize = 2000;


struct Company {
	string name;
	string tax_code;
	string address;
};

Company readCompany(string company_info) {
	stringstream ss(company_info);
	vector<string> info;
	Company company;
	string buffer;
	while (getline(ss, buffer, '|')) {
		info.push_back(buffer);
	}
	company.name = info[0];
	company.tax_code = info[1];
	company.address = info[2];

	return company;
}

vector<Company> ReadCompanyList(string file_name) {
	ifstream fin(file_name);
	if (!fin.is_open()) {
		cout << "Can't open " << file_name << " to read.\n";
		exit(1);
	}

	vector <Company> results;
	string company_info;

	getline(fin, company_info);
	while (getline(fin, company_info)) {
		Company company = readCompany(company_info);
		results.push_back(company);
	}
	cout << "Successfully read " << file_name << endl;
	fin.close();

	return results;
}

unsigned long long sqr(unsigned long long  x) {
	return x * x;
}

unsigned long long powMod(unsigned int a, unsigned int b, unsigned long long MOD) {
	if (b == 0) 
		return 1 % MOD;
	else
		if (b % 2 == 0)
			return sqr(powMod(a, b / 2, MOD)) % MOD;
		else
			return a * (sqr(powMod(a, b / 2,MOD)) % MOD) % MOD;
}

unsigned long long HashString(string company_name) {
	unsigned long long hash = 0;
	unsigned int com_size = company_name.size();

	string subString;
	if (com_size <= 20)
		subString = company_name;
	else {
		subString = company_name.substr(com_size - 20, 20);
	}

	for (int i = 0; i < subString.size(); i++) {
		hash = hash + (((long long)subString[i] % m) * powMod(p, i, m)) % m;
	}
		
	//(a+b) mod m = (a mod m + b mod m) mod m
	//(a*b) mod m = ( a mod m * b mod m ) mod m

	//(a + b + c) mod m = (a mod m + b mod m + c mod m) mod m
	// a mod m = (s[i] mod m) * (p^i mod m)
	// p^i mod m = p^c mod m + p^b mod m Với b + c = m

	return hash % m;
}

bool isFull(Company* hash_table) {
	for (int i = 0; i < hashTableSize; i++)
		if (hash_table[i].name.empty())
			return false;
	return true;
}

//* Linear probing (Use for array only):
//index = index % hashTableSize
//index = (index + 1) % hashTableSize
//index = (index + 2) % hashTableSize
//index = (index + 3) % hashTableSize
void Insert(Company* hash_table, Company company) {
	int i = HashString(company.name) % hashTableSize;
	while (!hash_table[i % hashTableSize].name.empty() && isFull(hash_table) == false)
		i++;

	hash_table[i] = company;
}

Company* CreateHashTable(vector<Company> list_company) {
	Company* hash_table = new Company[hashTableSize];
	for (int i = 0; i < list_company.size(); i++)
		Insert(hash_table, list_company[i]);

	cout << "Hash Table created.\n";

	return &hash_table[0];
}



Company* Search(Company* hash_table, string company_name) {
	int i = HashString(company_name) % hashTableSize;
	int count = 0;
	while (hash_table[i % hashTableSize].name != company_name && count < hashTableSize){
		i++;
		count++;
	}
	if (count == hashTableSize) 
		return nullptr;
	else
		return &hash_table[i];
}

void writeFile(Company* hash_table, string outputFile) {
	ofstream fout(outputFile);

	if (!fout.is_open()) {
		cout << "Can't open file " << outputFile << " to write.\n";
		return;
	}

	int dem = 0;
	for (int i = 0; i < hashTableSize; i++) {
		fout << "INDEX: " << i << "|" << hash_table[i].name << "|" << hash_table[i].tax_code << "|" << hash_table[i].address << endl;
		
		if (!hash_table[i].name.empty())
			dem++;
	}
	fout << "---------------------------------------------------\n";
	fout << "Total numbers of companies: " << dem << endl;
	fout.close();
	cout << "Successfully write created hash table to " << outputFile << endl;
}

int main() {
	system("cls");

	cout << "*******************************************************\n";
	cout << "*               HOME WORK 4: HASH TABLE               *\n";
	cout << "*******************************************************\n";
	string file_name("MST.txt");
	vector <Company> Company_list = ReadCompanyList(file_name);
	Company* hash_table = CreateHashTable(Company_list);

	string outputFile("hash_table.txt");
	writeFile(hash_table, outputFile);

	cout << "------------------------------------------------------\n";
	system("pause");

	string company_name;
	Company* searching = new Company;
	while (1){
		system("cls");
		cout << "*******************************************************\n";
		cout << "*               HOME WORK 4: HASH TABLE               *\n";
		cout << "*******************************************************\n";
		cout << "Created hash table saved as " << outputFile << endl;
		cout << "=======================================================\n";
		cout << "Enter the finding company's name (Enter \"E\" to exit program):\n";
		cout << "> ";
		getline(cin, company_name);
		if (company_name == "E")
			exit(0);

		searching = Search(hash_table, company_name);
		cout << "-------------------------------------------------------\n";
		if (searching != nullptr) {
			cout << "The company's information: \n";
			cout << "-Name: " << searching->name << endl;
			cout << "-Tax Code: " << searching->tax_code << endl;
			cout << "-Address: " << searching->address << endl;
			
		}
		else
			cout << "There is no company has the name: " << company_name << endl;
		cout << "-------------------------------------------------------\n";
		
		system("pause");
	}

	delete[]hash_table;
	delete searching;
	
	return 0;
}