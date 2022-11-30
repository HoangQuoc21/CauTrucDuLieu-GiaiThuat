#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "Timing.h"
#include "DataGenerator.h"
#include "ComparingCounting.h"

using namespace std;
using namespace std::chrono;
using namespace std::literals::chrono_literals;

//Hàm in mảng
void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}

void choosingAlgorithm(string algorithm, int b[], int c[], int n) {
	unsigned long long count = 0;
	if (algorithm == "selection") {
		cout << "-Running time: " << selectionSortTime(b, n).count() << endl;
		selectionSortCompare(c, n, count);
	}
	else if (algorithm == "insertion") {
		cout << "-Running time: " << insertionSortTime(b, n).count() << endl;
		insertionSortCompare(c, n, count);
	}
	else if (algorithm == "bubble") {
		cout << "-Running time: " << bubbleSortTime(b, n).count() << endl;
		bubbleSortCompare(c, n, count);
	}
	else if (algorithm == "shaker") {
		cout << "-Running time: " << shakerSortTime(b, n).count() << endl;
		shakerSortCompare(c, n, count);
	}
	else if (algorithm == "shell") {
		cout << "-Running time: " << shellSortTime(b, n).count() << endl;
		shellSortCompare(c, n, count);
	}
	else if (algorithm == "heap") {
		cout << "-Running time: " << heapSortTime(b, n).count() << endl;
		heapSortCompare(c, n, count);
	}
	else if (algorithm == "merge") {
		cout << "-Running time: " << mergeSortTime(b, n).count() << endl;
		mergeSortCompare(c, 0, n - 1, count);
	}
	else if (algorithm == "quick") {
		cout << "-Running time: " << quickSortTime(b, n).count() << endl;
		quickSortCompare(c, 0, n - 1, count);
	}
	else if (algorithm == "counting") {
		cout << "-Running time: " << countingSortTime(b, n).count() << endl;
		countingSortCompare(c, n, count);
	}
	else if (algorithm == "radix") {
		cout << "-Running time: " << radixSortTime(b, n).count() << endl;
		radixSortCompare(c, n, count);
	}
	else if (algorithm == "flash") {
		cout << "-Running time: " << flashSortTime(b, n).count() << endl;
		flashSortCompare(c, n, count);
	}
	cout << "-Comparing counted: " << count << endl;
}

int main() {
	int dataSize[6] = { 10000, 30000, 50000, 100000, 300000, 500000 };
	string dataOrder[4] = { "-rand","-sorted","-rev","-nsorted" };
	string algorithm[11] = { "selection", "insertion", "bubble", "shaker", "shell", "heap", "merge", "quick", "counting", "radix", "flash" };

	//Hiển thị kết quả ra màn hình
	/*for (int i = 0; i < 4; i++) {
		cout << "===== DATA ORDER: " << dataOrder[i] << " =====\n";
		for (int j = 0; j < 6; j++) {
			cout << "----- Data Size: " << dataSize[j] << " -----\n";
			int* a = new int[dataSize[j]];
			GenerateData(a, dataSize[j], i);
			for (int k = 0; k < 11; k++) {

				int* b = new int[dataSize[j]];
				int* c = new int[dataSize[j]];
				for (int l = 0; l < dataSize[j]; l++)
					c[l] = b[l] = a[l];

				cout << k + 1 << ". " << algorithm[k] << ": \n";
				choosingAlgorithm(algorithm[k], b, c, dataSize[j]);
				delete[]b;
				delete[]c;
			}
			delete[]a;
			cout << "------------------------------------------\n\n";
		}
		cout << "==================================\n\n";
	}*/

	//Ghi dữ liệu vào file .csv
	string filename("result.csv");
	ofstream fout(filename);
	//Với 4 kiểu sắp xếp dữ liệu
	for (int i = 0; i < 4; i++) {
		fout << "DATA ORDER: " << dataOrder[i] << endl;

		fout << "Data Size:,";
		for (int j = 0; j < 6; j++)
			fout << dataSize[j] << "," << ",";
		fout << "\n";

		fout << "Resulting Statics ,";
		//Với 6 bộ dữ liệu
		for (int j = 0; j < 6; j++)
			fout << "Running time, Comparisions,";
		fout << '\n';
		//Với 11 thuật tóan
		for (int j = 0; j <= 10; j++) {

			fout << algorithm[j] << ",";

			for (int k = 0; k < 6; k++) {
				int* a = new int[dataSize[k]];
				GenerateData(a, dataSize[k], i);

				int* b = new int[dataSize[k]];
				for (int l = 0; l < dataSize[k]; l++)
					b[l] = a[l];

				unsigned long long count = 0;
				if (algorithm[j] == "selection") {
					fout << selectionSortTime(a, dataSize[k]).count() << ",";
					selectionSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "insertion") {
					fout << insertionSortTime(a, dataSize[k]).count() << ",";
					insertionSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "bubble") {
					fout << bubbleSortTime(a, dataSize[k]).count() << ",";
					bubbleSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "shaker") {
					fout << shakerSortTime(a, dataSize[k]).count() << ",";
					shakerSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "shell") {
					fout << shellSortTime(a, dataSize[k]).count() << ",";
					shellSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "heap") {
					fout << heapSortTime(a, dataSize[k]).count() << ",";
					heapSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "merge") {
					fout << mergeSortTime(a, dataSize[k]).count() << ",";
					mergeSortCompare(b, 0, dataSize[k] - 1, count);
				}
				else if (algorithm[j] == "quick") {
					fout << quickSortTime(a, dataSize[k]).count() << ",";
					quickSortCompare(b, 0, dataSize[k] - 1, count);
				}
				else if (algorithm[j] == "counting") {
					fout << countingSortTime(a, dataSize[k]).count() << ",";
					countingSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "radix") {
					fout << radixSortTime(a, dataSize[k]).count() << ",";
					radixSortCompare(b, dataSize[k], count);
				}
				else if (algorithm[j] == "flash") {
					fout << flashSortTime(a, dataSize[k]).count() << ",";
					flashSortCompare(b, dataSize[k], count);
				}
				fout << count << ",";

				delete[]a;
				delete[]b;
			}
			fout << "\n";
		}
		fout << "\n";
	}
	fout.close();
	cout << "DA GHI DU LIEU XONG!\n";
	return 0;
}
