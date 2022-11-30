#pragma once
#include <iostream>
#include <time.h>
#include "SortingAlgorithm.h"
#include "DataGenerator.h"
#include <chrono>
using namespace std::chrono;
using namespace std::literals::chrono_literals;

//1. selectionSort(a,n);
duration<double, std::milli> selectionSortTime(int a[], int n) {
    auto start = steady_clock::now();
    selectionSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//2. insertionSort(a,n);
duration<double, std::milli> insertionSortTime(int a[], int n) {
    auto start = steady_clock::now();
    insertionSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//3. bubbleSort(a,n);
duration<double, std::milli> bubbleSortTime(int a[], int n) {
    auto start = steady_clock::now();
    bubbleSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//4. shakerSort(a,n);
duration<double, std::milli> shakerSortTime(int a[], int n) {
    auto start = steady_clock::now();
    shakerSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//5. shellSort(a,n)
duration<double, std::milli> shellSortTime(int a[], int n) {
    auto start = steady_clock::now();
    shellSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//6. heapSort(a,n);
duration<double, std::milli> heapSortTime(int a[], int n) {
    auto start = steady_clock::now();
    heapSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//7. mergeSort(a,n)
duration<double, std::milli> mergeSortTime(int a[], int n) {
    auto start = steady_clock::now();
    mergeSort(a, 0, n - 1);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//8. quickSort(a,n)
duration<double, std::milli> quickSortTime(int a[], int n) {
    auto start = steady_clock::now();
    quickSort(a, 0, n - 1);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//9. countingSort(a,n);
duration<double, std::milli> countingSortTime(int a[], int n) {
    auto start = steady_clock::now();
    countingSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//10. radixSort(a,n)
duration<double, std::milli> radixSortTime(int a[], int n) {
    auto start = steady_clock::now();
    radixSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}

//11. flashSort
duration<double, std::milli> flashSortTime(int a[], int n) {
    auto start = steady_clock::now();
    flashSort(a, n);
    auto end = steady_clock::now();
    return duration<double, std::milli>(end - start);
}