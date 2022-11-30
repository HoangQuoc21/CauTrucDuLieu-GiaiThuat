#pragma once
#include <fstream>
#include <chrono>
#include <string.h>
#include <iomanip>
#include "DataGenerator.h"
#include "ComparingCounting.h"
#include "SortingAlgorithm.h"
#include "Timing.h"
using namespace std;


void command1(char Algorithm[], char inputFile[], char outPara[]) {
    cout << "============\n";
    cout << "| Command1 |\n";
    cout << "============\n";
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << Algorithm << endl;
    cout << "Input file: " << inputFile << endl;

    // Doc file dau vao
    ifstream fin;
    fin.open(inputFile);
    if (!fin.is_open()) {
        cout << "Can't open file to read.\n";
        return;
    }
        
    int n = 0;
    fin >> n;
    cout << "Input size: " << n << endl;
    cout << "---------------------------------\n";

    // Khoi tao hai mang n phan tu
    int* arr = new int[n];
    int* arr2 = new int[n];

    //Doc tu file vao hai mang
    for (int i = 0; i < n; i++)
    {
        fin >> arr[i];
        arr2[i] = arr[i];
    }
    // Dong file
    fin.close();

    // Sap xep bang cac thuat toan sap xep
    unsigned long long countcomp = 0;
    duration<double, std::milli> counttime;
    //double counttime = 0;
    // Sap xep bang cac thuat toan sap xep
    if (strcmp(Algorithm, "selection-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        selectionSortCompare(arr, n, countcomp);
        counttime = selectionSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "insertion-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        insertionSortCompare(arr, n, countcomp);
        counttime = insertionSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "bubble-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        bubbleSortCompare(arr, n, countcomp);
        counttime = bubbleSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "shaker-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        shakerSortCompare(arr, n, countcomp);
        counttime = shakerSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "shell-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        shellSortCompare(arr, n, countcomp);
        counttime = shellSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "heap-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        heapSortCompare(arr, n, countcomp);
        counttime = heapSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "merge-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        mergeSortCompare(arr, 0, n - 1, countcomp);
        counttime = mergeSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "quick-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        quickSortCompare(arr, 0, n - 1, countcomp);
        counttime = mergeSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "counting-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        countingSortCompare(arr, n, countcomp);
        counttime = countingSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "radix-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        radixSortCompare(arr, n, countcomp);
        counttime = radixSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "flash-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        flashSortCompare(arr, n, countcomp);
        counttime = flashSortTime(arr2, n);
    }
    else
        cout << "Algorithm is not found!\n";

    // Ghi mang da sap xep vao file output.txt
    fstream fout;
    fout.open("output.txt", ios::out);
    if (!fout.is_open()) {
        cout << "Can't open file to write.\n";
        return;
    }

    fout << n << endl;
    for (int i = 0; i < n; i++)
    {
        fout << arr[i] << " ";
    }
    // Dong file
    fout.close();

    //In Output parameter
    if (strcmp(outPara, "-time") == 0) {
        cout << "Running time: " << counttime.count() << " ms\n";
    }
    else if (strcmp(outPara, "-comp") == 0) {
        cout << "Comparisions: " << countcomp << endl;
    }
    else if (strcmp(outPara, "-both") == 0) {
        cout << "Running time: " << counttime.count() << " ms\n";
        cout << "Comparisions: " << countcomp << endl;
    }
    else
        cout << "Output parameter is not found!\n";

}

void command2(char Algorithm[], char inputSize[], char inputOrder[], char outPara[]){
    cout << "============\n";
    cout << "| Command2 |\n";
    cout << "============\n";
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << Algorithm << endl;
    int n = atoi(inputSize);
    cout << "Input size: " << n << endl;
    cout << "Input order: " << inputOrder << endl;
    cout << "---------------------------------\n";

    // Khoi tao mang n phan tu
    int* arr = new int[n];
    int* arr2 = new int[n];

    // Yeu cau tao mang 
    int dataType = 0;

    if (strcmp(inputOrder, "-rand") == 0) {
        dataType = 0;
    }
    else if (strcmp(inputOrder, "-sorted") == 0) {
        dataType = 1;
    }
    else if (strcmp(inputOrder, "-rev") == 0) {
        dataType = 2;
    }
    else if (strcmp(inputOrder, "-nsorted") == 0) {
        dataType = 3;
    }
    else
        cout << "Input order is not found!\n";

    //~~~~Tao mang bang ham cua thay~~~~
    GenerateData(arr, n, dataType);

    //Ghi mang vua tao vao file input.txt
    ofstream fin;
    fin.open("input.txt");
    if (!fin.is_open())
        cout << "Can't open file to write.\n";

    fin << n << endl;
    for (int i = 0; i < n; i++)
    {
        fin << arr[i] << " ";
    }
    // Dong file
    fin.close();

    //Sao chép mảng 1 qua mảng 2
    for (int i = 0; i < n; i++)
        arr2[i] = arr[i];

    // Khai báo hai biến đếm phép so sánh và thời gian
    unsigned long long countcomp = 0;
    duration<double, std::milli> counttime;
    //double counttime = 0;
    // Sap xep bang cac thuat toan sap xep
    if (strcmp(Algorithm, "selection-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        selectionSortCompare(arr, n, countcomp);
        counttime = selectionSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "insertion-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        insertionSortCompare(arr, n, countcomp);
        counttime = insertionSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "bubble-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        bubbleSortCompare(arr, n, countcomp);
        counttime = bubbleSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "shaker-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        shakerSortCompare(arr, n, countcomp);
        counttime = shakerSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "shell-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        shellSortCompare(arr, n, countcomp);
        counttime = shellSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "heap-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        heapSortCompare(arr, n, countcomp);
        counttime = heapSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "merge-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        mergeSortCompare(arr, 0, n - 1, countcomp);
        counttime = mergeSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "quick-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        quickSortCompare(arr, 0 , n - 1, countcomp);
        counttime = mergeSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "counting-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        countingSortCompare(arr, n, countcomp);
        counttime = countingSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "radix-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        radixSortCompare(arr, n, countcomp);
        counttime = radixSortTime(arr2, n);
    }
    else if (strcmp(Algorithm, "flash-sort") == 0) {
        //Bo Ham Sap Xep Vao Day
        flashSortCompare(arr, n, countcomp);
        counttime = flashSortTime(arr2, n);
    }
    else
        cout << "Algorithm is not found!\n";

    //Ghi mang da sap xep vao file output.txt
    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open())
        cout << "Khong mo duoc file de ghi!\n";

    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << " ";
    // Dong file
    fout.close();

    //In Output parameter
    if (strcmp(outPara, "-time") == 0) {
        cout << "Running time: " << counttime.count() << " ms\n";
    }
    else if (strcmp(outPara, "-comp") == 0) {
        cout << "Comparisions: " << countcomp << endl;
    }
    else if (strcmp(outPara, "-both") == 0) {
        cout << "Running time: " << counttime.count() << " ms\n";
        cout << "Comparisions: " << countcomp << endl;
    }
    else
        cout << "Output parameter is not found!\n";
}

void command3(char Algorithm[], char inputSize[], char outPara[]){
    cout << "============\n";
    cout << "| Command3 |\n";
    cout << "============\n";
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << Algorithm << endl;
    int n = atoi(inputSize);
    cout << "Input size: " << n << endl << endl;

    // Khoi tao mang n phan tu
    int* a1 = new int[n];
    int* a2 = new int[n];
    int* a3 = new int[n];
    int* a4 = new int[n];

    //~~~~Tao mang bang ham cua thay~~~~
    GenerateData(a1, n, 0);//random
    GenerateData(a2, n, 3);//nearly sorted
    GenerateData(a3, n, 1);//sorted
    GenerateData(a4, n, 2);//reversed 

    //Ghi mang a1 vua tao vao file input_1.txt
    fstream fin;
    fin.open("input_1.txt", ios::out);
    if (!fin.is_open())
    {
        cout << "Khong mo duoc file de ghi!\n";
    }

    fin << n << endl;
    for (int i = 0; i < n; i++)
    {
        fin << a1[i] << " ";
    }
    // Dong file
    fin.close();

    //Ghi mang a2 vua tao vao file input_2.txt
    fin.open("input_2.txt", ios::out);
    if (!fin.is_open())
    {
        cout << "Khong mo duoc file de ghi!\n";
    }

    fin << n << endl;
    for (int i = 0; i < n; i++)
    {
        fin << a2[i] << " ";
    }
    // Dong file
    fin.close();

    //Ghi mang a3 vua tao vao file input_3.txt
    fin.open("input_3.txt", ios::out);
    if (!fin.is_open())
    {
        cout << "Khong mo duoc file de ghi!\n";
    }

    fin << n << endl;
    for (int i = 0; i < n; i++)
    {
        fin << a3[i] << " ";
    }
    // Dong file
    fin.close();

    //Ghi mang a4 vua tao vao file input_4.txt
    fin.open("input_4.txt", ios::out);
    if (!fin.is_open())
    {
        cout << "Khong mo duoc file de ghi!\n";
    }

    fin << n << endl;
    for (int i = 0; i < n; i++)
    {
        fin << a4[i] << " ";
    }
    // Dong file
    fin.close();

    int* b1 = new int[n];
    int* b2 = new int[n];
    int* b3 = new int[n];
    int* b4 = new int[n];

    for (int i = 0; i < n; i++) {
        b1[i] = a1[i];
        b2[i] = a2[i];
        b3[i] = a3[i];
        b4[i] = a4[i];
    }

    unsigned long long comp1 = 0, comp2 = 0, comp3 = 0, comp4 = 0;
    duration<double, std::milli> time1, time2, time3, time4;

    if (strcmp(Algorithm, "selection-sort") == 0) {
        selectionSortCompare(a1, n, comp1);
        time1 = selectionSortTime(b1, n);

        selectionSortCompare(a2, n, comp2);
        time2 = selectionSortTime(b2, n);

        selectionSortCompare(a3, n, comp3);
        time3 = selectionSortTime(b3, n);

        selectionSortCompare(a4, n, comp4);
        time4 = selectionSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "insertion-sort") == 0) {
        insertionSortCompare(a1, n, comp1);
        time1 = insertionSortTime(b1, n);

        insertionSortCompare(a2, n, comp2);
        time2 = insertionSortTime(b2, n);

        insertionSortCompare(a3, n, comp3);
        time3 = insertionSortTime(b3, n);

        insertionSortCompare(a4, n, comp4);
        time4 = insertionSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "bubble-sort") == 0) {
        bubbleSortCompare(a1, n, comp1);
        time1 = bubbleSortTime(b1, n);

        bubbleSortCompare(a2, n, comp2);
        time2 = bubbleSortTime(b2, n);

        bubbleSortCompare(a3, n, comp3);
        time3 = bubbleSortTime(b3, n);

        bubbleSortCompare(a4, n, comp4);
        time4 = bubbleSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "shaker-sort") == 0) {
        shakerSortCompare(a1, n, comp1);
        time1 = shakerSortTime(b1, n);

        shakerSortCompare(a2, n, comp2);
        time2 = shakerSortTime(b2, n);

        shakerSortCompare(a3, n, comp3);
        time3 = shakerSortTime(b3, n);

        shakerSortCompare(a4, n, comp4);
        time4 = shakerSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "shell-sort") == 0) {
        shellSortCompare(a1, n, comp1);
        time1 = shellSortTime(b1, n);

        shellSortCompare(a2, n, comp2);
        time2 = shellSortTime(b2, n);

        shellSortCompare(a3, n, comp3);
        time3 = shellSortTime(b3, n);

        shellSortCompare(a4, n, comp4);
        time4 = shellSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "heap-sort") == 0) {
        heapSortCompare(a1, n, comp1);
        time1 = heapSortTime(b1, n);

        heapSortCompare(a2, n, comp2);
        time2 = heapSortTime(b2, n);

        heapSortCompare(a3, n, comp3);
        time3 = heapSortTime(b3, n);

        heapSortCompare(a4, n, comp4);
        time4 = heapSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "merge-sort") == 0) {
        mergeSortCompare(a1,0, n-1, comp1);
        time1 = mergeSortTime(b1, n);

        mergeSortCompare(a2, 0, n - 1, comp2);
        time2 = mergeSortTime(b2, n);

        mergeSortCompare(a3, 0, n - 1, comp3);
        time3 = mergeSortTime(b3, n);

        mergeSortCompare(a4, 0, n - 1, comp4);
        time4 = mergeSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "quick-sort") == 0) {
        quickSortCompare(a1, 0, n - 1, comp1);
        time1 = quickSortTime(b1, n);

        quickSortCompare(a2, 0, n - 1, comp2);
        time2 = quickSortTime(b2, n);

        quickSortCompare(a3, 0, n - 1, comp3);
        time3 = quickSortTime(b3, n);

        quickSortCompare(a4, 0, n - 1, comp4);
        time4 = quickSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "counting-sort") == 0) {
        countingSortCompare(a1, n, comp1);
        time1 = countingSortTime(b1, n);

        countingSortCompare(a2, n, comp2);
        time2 = countingSortTime(b2, n);

        countingSortCompare(a3, n, comp3);
        time3 = countingSortTime(b3, n);

        countingSortCompare(a4, n, comp4);
        time4 = countingSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "radix-sort") == 0) {
        radixSortCompare(a1, n, comp1);
        time1 = radixSortTime(b1, n);

        radixSortCompare(a2, n, comp2);
        time2 = radixSortTime(b2, n);

        radixSortCompare(a3, n, comp3);
        time3 = radixSortTime(b3, n);

        radixSortCompare(a4, n, comp4);
        time4 = radixSortTime(b4, n);
    }
    else if (strcmp(Algorithm, "flash-sort") == 0) {
        flashSortCompare(a1, n, comp1);
        time1 = flashSortTime(b1, n);

        flashSortCompare(a2, n, comp2);
        time2 = flashSortTime(b2, n);

        flashSortCompare(a3, n, comp3);
        time3 = flashSortTime(b3, n);

        flashSortCompare(a4, n, comp4);
        time4 = flashSortTime(b4, n);
    }
    else
        cout << "Algorithm is not found!\n";
    //In Output parameter

    if (strcmp(outPara, "-time") == 0) {
        cout << "Input order: Randomize" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time1.count() << " ms\n";
        cout << endl;

        cout << "Input order: Nearly Sorted" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time2.count() << " ms\n";
        cout << endl;

        cout << "Input order: Sorted" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time3.count() << " ms\n";
        cout << endl;

        cout << "Input order: Reversed" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time4.count() << " ms\n";
        cout << endl;
    }
    else if (strcmp(outPara, "-comp") == 0) {
        cout << "Input order: Randomize" << endl;
        cout << "---------------------------------\n";
        cout << "Comparisions: " << comp1 << endl;
        cout << endl;

        cout << "Input order: Nearly Sorted" << endl;
        cout << "---------------------------------\n";
        cout << "Comparisions: " << comp2 << endl;
        cout << endl;

        cout << "Input order: Sorted" << endl;
        cout << "---------------------------------\n";
        cout << "Comparisions: " << comp3 << endl;
        cout << endl;

        cout << "Input order: Reversed" << endl;
        cout << "---------------------------------\n";
        cout << "Comparisions: " << comp4 << endl;
        cout << endl;
    }
    else if (strcmp(outPara, "-both") == 0) {
        cout << "Input order: Randomize" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time1.count() << " ms\n";
        cout << "Comparisions: " << comp1 << endl;
        cout << endl;

        cout << "Input order: Nearly Sorted" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time2.count() << " ms\n";
        cout << "Comparisions: " << comp2 << endl;
        cout << endl;

        cout << "Input order: Sorted" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time3.count() << " ms\n";
        cout << "Comparisions: " << comp3 << endl;
        cout << endl;

        cout << "Input order: Reversed" << endl;
        cout << "---------------------------------\n";
        cout << "Running time: " << time4.count() << " ms\n";
        cout << "Comparisions: " << comp4 << endl;
        cout << endl;
    }
    else
        cout << "Output parameter is not found!\n";
}

void command4(char Algorithm1[], char Algorithm2[], char inputFile[])
{
    // Open file
    cout << "============\n";
    cout << "| Command4 |\n";
    cout << "============\n";
    ifstream fin(inputFile);
    if (!fin.is_open())
    {
        cout << "Can't open file to read";
        return;
    }
    // Print to console
    cout << "COMPARE MODE" << endl;
    cout << "Algorithms: " << setw(14) << Algorithm1 << " | " << setw(14) << Algorithm2 << endl;

    // Read data
    cout << "Input file: " << inputFile << endl;
    int n;
    fin >> n;
    cout << "Input size: " << n << endl;
    cout << "------------------------" << endl;
    int* a = new int[n] {0};
    int* b = new int[n] {0};
    int* c = new int[n] {0};
    int* d = new int[n] {0};

    for (int i = 0; i < n; i++)
        fin >> a[i];
    fin.close();

    for (int i = 0; i < n; i++) {
        b[i] = a[i];
        c[i] = a[i];
        d[i] = a[i];
    }

    
    duration<double, std::milli> time1, time2;
    if (!strcmp(Algorithm1, "selection-sort"))
        time1 = selectionSortTime(a, n);
    else if (!strcmp(Algorithm1, "insertion-sort"))
        time1 = insertionSortTime(a, n);
    else if (!strcmp(Algorithm1, "bubble-sort"))
        time1 = bubbleSortTime(a, n);
    else if (!strcmp(Algorithm1, "shaker-sort"))
        time1 = shakerSortTime(a, n);
    else if (!strcmp(Algorithm1, "shell-sort"))
        time1 = shellSortTime(a, n);
    else if (!strcmp(Algorithm1, "heap-sort"))
        time1 = heapSortTime(a, n);
    else if (!strcmp(Algorithm1, "merge-sort"))
        time1 = mergeSortTime(a, n);
    else if (!strcmp(Algorithm1, "quick-sort"))
        time1 = quickSortTime(a, n);
    else if (!strcmp(Algorithm1, "counting-sort"))
        time1 = countingSortTime(a, n);
    else if (!strcmp(Algorithm1, "radix-sort"))
        time1 = radixSortTime(a, n);
    else if (!strcmp(Algorithm1, "flash-sort"))
        time1 = flashSortTime(a, n);
    delete[]a;

    if (!strcmp(Algorithm2, "selection-sort"))
        time2 = selectionSortTime(b, n);
    else if (!strcmp(Algorithm2, "insertion-sort"))
        time2 = insertionSortTime(b, n);
    else if (!strcmp(Algorithm2, "bubble-sort"))
        time2 = bubbleSortTime(b, n);
    else if (!strcmp(Algorithm2, "shaker-sort"))
        time2 = shakerSortTime(b, n);
    else if (!strcmp(Algorithm2, "shell-sort"))
        time2 = shellSortTime(b, n);
    else if (!strcmp(Algorithm2, "heap-sort"))
        time2 = heapSortTime(b, n);
    else if (!strcmp(Algorithm2, "merge-sort"))
        time2 = mergeSortTime(b, n);
    else if (!strcmp(Algorithm2, "quick-sort"))
        time2 = quickSortTime(b, n);
    else if (!strcmp(Algorithm2, "counting-sort"))
        time2 = countingSortTime(b, n);
    else if (!strcmp(Algorithm2, "radix-sort"))
        time2 = radixSortTime(b, n);
    else if (!strcmp(Algorithm2, "flash-sort"))
        time2 = flashSortTime(b, n);
    delete[]b;

    cout << "Running time: " << setw(9) << fixed << setprecision(2) << time1.count() << " ms | " << setw(9) << fixed << setprecision(2) << time2.count() << " ms\n";

    unsigned long long count1 = 0, count2 = 0;
    if (!strcmp(Algorithm1, "selection-sort"))
        selectionSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "insertion-sort"))
        insertionSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "bubble-sort"))
        bubbleSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "shaker-sort"))
        shakerSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "shell-sort"))
        shellSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "heap-sort"))
        heapSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "merge-sort"))
        mergeSortCompare(c, 0, n - 1, count1);
    else if (!strcmp(Algorithm1, "quick-sort"))
        quickSortCompare(c, 0, n - 1, count1);
    else if (!strcmp(Algorithm1, "counting-sort"))
        countingSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "radix-sort"))
        radixSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "flash-sort"))
        flashSortCompare(c, n, count1);
    delete[]c;

    if (!strcmp(Algorithm2, "selection-sort"))
        selectionSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "insertion-sort"))
        insertionSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "bubble-sort"))
        bubbleSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "shaker-sort"))
        shakerSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "shell-sort"))
        shellSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "heap-sort"))
        heapSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "merge-sort"))
        mergeSortCompare(d, 0, n - 1, count2);
    else if (!strcmp(Algorithm2, "quick-sort"))
        quickSortCompare(d, 0, n - 1, count2);
    else if (!strcmp(Algorithm2, "counting-sort"))
        countingSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "radix-sort"))
        radixSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "flash-sort"))
        flashSortCompare(d, n, count2);
    delete[]d;

    cout << "Comparisions: " << setw(12) << count1 << " | " << setw(12) << count2 << endl;
}

void command5(char Algorithm1[], char Algorithm2[], char inputSize[], char inputOrder[]) {
    cout << "============\n";
    cout << "| Command5 |\n";
    cout << "============\n";
    cout << "COMPARE MODE\n";
    cout << "Algorithms: " << setw(14) << Algorithm1 << " | " << setw(14) << Algorithm2 << endl;
    int n = atoi(inputSize);
    cout << "Input Size: " << n << endl;
    cout << "Input Order: " << inputOrder << endl;
    cout << "---------------------------------------\n";

    int* a = new int[n] {0}, * b = new int[n] {0}, * c = new int[n] {0}, * d = new int[n] {0};
    if (!strcmp(inputOrder, "-rand"))
        GenerateData(a, n, 0);
    else if (!strcmp(inputOrder, "-nsorted"))
        GenerateData(a, n, 3);
    else if (!strcmp(inputOrder, "-sorted"))
        GenerateData(a, n, 1);
    else if (!strcmp(inputOrder, "-rev"))
        GenerateData(a, n, 2);

    for (int i = 0; i < n; i++) {
        b[i] = a[i];
        c[i] = a[i];
        d[i] = a[i];
    }

    string outputFile = "input.txt";
    ofstream fout;
    fout.open(outputFile);
    if (!fout.is_open()){
        cout << "Can't open file to write.\n";
        return;
    }
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << a[i] << " ";
    fout.close();


    duration<double, std::milli> time1, time2;
    if (!strcmp(Algorithm1, "selection-sort"))
        time1 = selectionSortTime(a, n);
    else if (!strcmp(Algorithm1, "insertion-sort"))
        time1 = insertionSortTime(a, n);
    else if (!strcmp(Algorithm1, "bubble-sort"))
        time1 = bubbleSortTime(a, n);
    else if (!strcmp(Algorithm1, "shaker-sort"))
        time1 = shakerSortTime(a, n);
    else if (!strcmp(Algorithm1, "shell-sort"))
        time1 = shellSortTime(a, n);
    else if (!strcmp(Algorithm1, "heap-sort"))
        time1 = heapSortTime(a, n);
    else if (!strcmp(Algorithm1, "merge-sort"))
        time1 = mergeSortTime(a, n);
    else if (!strcmp(Algorithm1, "quick-sort"))
        time1 = quickSortTime(a, n);
    else if (!strcmp(Algorithm1, "counting-sort"))
        time1 = countingSortTime(a, n);
    else if (!strcmp(Algorithm1, "radix-sort"))
        time1 = radixSortTime(a, n);
    else if (!strcmp(Algorithm1, "flash-sort"))
        time1 = flashSortTime(a, n);
    else{
        cout << "Invalid sort algorithm.\n";
        return;
    }
    delete[]a;

    if (!strcmp(Algorithm2, "selection-sort"))
        time2 = selectionSortTime(b, n);
    else if (!strcmp(Algorithm2, "insertion-sort"))
        time2 = insertionSortTime(b, n);
    else if (!strcmp(Algorithm2, "bubble-sort"))
        time2 = bubbleSortTime(b, n);
    else if (!strcmp(Algorithm2, "shaker-sort"))
        time2 = shakerSortTime(b, n);
    else if (!strcmp(Algorithm2, "shell-sort"))
        time2 = shellSortTime(b, n);
    else if (!strcmp(Algorithm2, "heap-sort"))
        time2 = heapSortTime(b, n);
    else if (!strcmp(Algorithm2, "merge-sort"))
        time2 = mergeSortTime(b, n);
    else if (!strcmp(Algorithm2, "quick-sort"))
        time2 = quickSortTime(b, n);
    else if (!strcmp(Algorithm2, "counting-sort"))
        time2 = countingSortTime(b, n);
    else if (!strcmp(Algorithm2, "radix-sort"))
        time2 = radixSortTime(b, n);
    else if (!strcmp(Algorithm2, "flash-sort"))
        time2 = flashSortTime(b, n);
    else{
        cout << "Invalid sort algorithm.\n";
        return;
    }
    delete[]b;

    cout << "Running time: " << setw(9) << fixed << setprecision(2) << time1.count() << " ms | " << setw(9) << fixed << setprecision(2) << time2.count() << " ms\n";

    unsigned long long count1 = 0, count2 = 0;
    if (!strcmp(Algorithm1, "selection-sort"))
        selectionSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "insertion-sort"))
        insertionSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "bubble-sort"))
        bubbleSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "shaker-sort"))
        shakerSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "shell-sort"))
        shellSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "heap-sort"))
        heapSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "merge-sort"))
        mergeSortCompare(c, 0, n - 1, count1);
    else if (!strcmp(Algorithm1, "quick-sort"))
        quickSortCompare(c, 0, n - 1, count1);
    else if (!strcmp(Algorithm1, "counting-sort"))
        countingSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "radix-sort"))
        radixSortCompare(c, n, count1);
    else if (!strcmp(Algorithm1, "flash-sort"))
        flashSortCompare(c, n, count1);
    else{
        cout << "Invalid sort algorithm.\n";
        return;
    }
    delete[]c;

    if (!strcmp(Algorithm2, "selection-sort"))
        selectionSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "insertion-sort"))
        insertionSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "bubble-sort"))
        bubbleSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "shaker-sort"))
        shakerSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "shell-sort"))
        shellSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "heap-sort"))
        heapSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "merge-sort"))
        mergeSortCompare(d, 0, n - 1, count2);
    else if (!strcmp(Algorithm2, "quick-sort"))
        quickSortCompare(d, 0, n - 1, count2);
    else if (!strcmp(Algorithm2, "counting-sort"))
        countingSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "radix-sort"))
        radixSortCompare(d, n, count2);
    else if (!strcmp(Algorithm2, "flash-sort"))
        flashSortCompare(d, n, count2);
    else{
        cout << "Invalid sort algorithm.\n";
        return;
    }
    delete[]d;

    cout << "Comparisions: " << setw(12) << count1 << " | " << setw(12) << count2 << endl;
}
