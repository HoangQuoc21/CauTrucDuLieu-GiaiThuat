#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//1. Selection sort:
//Đưa phần tử nhỏ nhất về đầu, lặp lại n lần
void selectionSortCompare(int a[], int n, unsigned long long& comparisions)
{
    int min_idx;
    for (int i = 0; ++comparisions && i < n - 1; i++) {
        // Tìm phần tử nhỏ nhất trong mảng chưa sắp xếp
        min_idx = i;
        for (int j = i + 1; ++comparisions && j < n; j++) {
            ++comparisions;
            if (a[j] < a[min_idx])
                min_idx = j;
        }
        swap(a[min_idx], a[i]);
    }
}
//2. Insertion sort:
void insertionSortCompare(int a[], int n, unsigned long long& comparisions)
{
    for (int i = 1; ++comparisions && i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (++comparisions && j >= 0 && a[j] > key) {
            ++comparisions;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
//3. Bubble sort:
void bubbleSortCompare(int a[], int n, unsigned long long& comparisions) {
    for (int i = 0; ++comparisions && i < n - 1; i++)
        for (int j = 0; ++comparisions && j < n - i - 1; j++) {
            ++comparisions;
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        }
}

//4. Shaker Sort (Cải tiến của Buble Sort):
void shakerSortCompare(int a[], int n, unsigned long long& comparisions) {
    int Left = 0;
    int Right = n - 1;
    int k = 0;
    while (++comparisions&& Left < Right) {
        for (int i = Left; ++comparisions && i < Right; i++) {
            ++comparisions;
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                k = i;
            }
        }
        Right = k;
        for (int i = Right; ++comparisions && i > Left; i--) {
            ++comparisions;
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
                k = i;
            }
        }
        Left = k;
    }
}

//5. Shell sort:
void shellSortCompare(int a[], int n, unsigned long long& comparisions) {
    for (int interval = n / 2; ++comparisions && interval > 0; interval /= 2) {
        for (int i = interval; ++comparisions && i < n; i++) {
            int j;
            int temp = a[i];
            for (j = i; ++comparisions && j >= interval && a[j - interval] > temp; ++comparisions, j -= interval) {
                a[j] = a[j - interval];
            }
            a[j] = temp;
        }
    }
}

//6. Heap sort:
void heapifyCompare(int a[], int N, int i, unsigned long long& comparisions) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    ++comparisions;
    if (left < N && a[left] > a[largest]) {
        ++comparisions;
        largest = left;
    }

    ++comparisions;
    if (right < N && a[right] > a[largest]) {
        ++comparisions;
        largest = right;
    }

    ++comparisions;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapifyCompare(a, N, largest, comparisions);
    }
}

void builMaxHeapCompare(int a[], int N, unsigned long long& comparisions) {
    for (int i = N / 2 - 1; ++comparisions && i >= 0; i--)
        heapifyCompare(a, N, i, comparisions);
}

void heapSortCompare(int a[], int N, unsigned long long& comparisions)
{
    builMaxHeapCompare(a, N, comparisions);

    for (int i = N - 1; ++comparisions && i >= 0; i--) {
        swap(a[0], a[i]);
        heapifyCompare(a, i, 0, comparisions);
    }
}

//7. Merge sort:
void mergeCompare(int a[], int l, int m, int r, unsigned long long& comparisions) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1] {0};
    int* R = new int[n2] {0};

    for (i = 0; ++comparisions && i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; ++comparisions && j < n2; j++)
        R[j] = a[m + 1 + j];

    i = 0; j = 0; k = l;

    while (++comparisions && i < n1 && j < n2) {
        ++comparisions;
        ++comparisions;
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (++comparisions && i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (++comparisions && j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

//l = 0, r = n - 1
void mergeSortCompare(int a[], int l, int r, unsigned long long& comparisions)
{
    ++comparisions;
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortCompare(a, l, m, comparisions);
        mergeSortCompare(a, m + 1, r, comparisions);
        mergeCompare(a, l, m, r, comparisions);
    }
}

//8. Quick sort:
//start = 0; end = n - 1
int partitionCompare(int a[], int start, int end, unsigned long long& comparisions) {
    int pivot = a[(start + end) / 2];

    // Sắp xếp mảng bên trái và mảng bên phải của phần tử Pivot
    int i = start, j = end;
    while (++comparisions && i <= j) {
        while (++comparisions && a[i] < pivot) {
            i++;
        }
        while (++comparisions && a[j] > pivot) {
            j--;
        }
        ++comparisions;
        if (i <= j) {
            swap(a[i++], a[j--]);
        }
    }
    return i;
}

void quickSortCompare(int a[], int start, int end, unsigned long long& comparisions) {
    ++comparisions;
    if (start >= end)
        return;

    int p = partitionCompare(a, start, end, comparisions);

    quickSortCompare(a, start, p - 1, comparisions);

    quickSortCompare(a, p + 1, end, comparisions);
}

//9. Counting sort:
//9.a Hàm tìm giá trị phần tử lớn nhất trong mảng
int findMaxValueCompare(int a[], int n, unsigned long long& comparisions) {
    int max = a[0];
    for (int i = 1; ++comparisions && i < n; i++) {
        ++comparisions;
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

void countingSortCompare(int a[], int n, unsigned long long& comparisions) {
    int maxValue = findMaxValueCompare(a, n, comparisions);
    int countArraySize = maxValue + 1;
    int* countArray = new int [countArraySize] {0};

    for (int i = 0; ++comparisions && i < n; i++)
        countArray[a[i]]++;

    for (int i = 1; ++comparisions && i <= maxValue; i++)
        countArray[i] = countArray[i] + countArray[i - 1];

    int* temp = new int[n] {0};
    for (int i = 0; ++comparisions && i < n; i++)
    {
        temp[countArray[a[i]] - 1] = a[i];
        countArray[a[i]]--;
    }

    for (int i = 0; ++comparisions && i < n; i++)
        a[i] = temp[i];

    delete[] countArray;
    delete[] temp;
}
//10. Radix sort:
void expSortCompare(int a[], int n, int exp, unsigned long long& comparisions)
{
    int* budget = new int[n];
    int i, digit[10] = { 0 };

    for (i = 0; ++comparisions && i < n; i++)
        digit[(a[i] / exp) % 10]++;

    for (i = 1; ++comparisions && i < 10; i++)
        digit[i] += digit[i - 1];

    for (i = n - 1; ++comparisions && i >= 0; i--) {
        budget[digit[(a[i] / exp) % 10] - 1] = a[i];
        digit[(a[i] / exp) % 10]--;
    }

    for (i = 0; ++comparisions && i < n; i++)
        a[i] = budget[i];
    delete[]budget;
}

void radixSortCompare(int a[], int n, unsigned long long& comparisions) {
    int maxValue = findMaxValueCompare(a, n, comparisions);

    for (int exp = 1; ++comparisions && maxValue / exp > 0; exp *= 10) {
        expSortCompare(a, n, exp, comparisions);
    }
}

//11. Flash sort:

void flashSortCompare(int a[], int n, unsigned long long& comparisions)
{
    int minVal = a[0];
    int maxIndex = 0;

    int nclass = int(0.45 * n);

    int* classes = new int[nclass] {0};

    for (int i = 1; ++comparisions && i < n; i++)
    {
        ++comparisions;
        if (a[i] < minVal)
            minVal = a[i];
        ++comparisions;
        if (a[i] > a[maxIndex])
            maxIndex = i;
    }

    ++comparisions;
    if (a[maxIndex] == minVal)
        return;

    double c1 = (double)(nclass - 1) / (a[maxIndex] - minVal);

    for (int i = 0; ++comparisions && i < n; i++)
    {
        int k = int(c1 * (a[i] - minVal));
        ++classes[k];
    }

    for (int i = 1; ++comparisions && i < nclass; i++)
        classes[i] += classes[i - 1];

    swap(a[maxIndex], a[0]);
    int nmove = 0;
    int j = 0;
    int k = nclass - 1;
    int t = 0;
    int flash;
    while (++comparisions && nmove < n - 1)
    {
        while (++comparisions && j > classes[k] - 1)
        {
            j++;
            k = int(c1 * (a[j] - minVal));
        }
        flash = a[j];
        ++comparisions;
        if (k < 0) break;
        while (++comparisions && j != classes[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = a[t = --classes[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }

    delete[] classes;
    insertionSortCompare(a, n, comparisions);
}