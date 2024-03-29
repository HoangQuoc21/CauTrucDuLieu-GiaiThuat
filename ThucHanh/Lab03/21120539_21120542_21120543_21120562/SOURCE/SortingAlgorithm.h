﻿#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//1. Selection sort:
//Đưa phần tử nhỏ nhất về đầu, lặp lại n lần
void selectionSort(int a[], int n) {
    // Di chuyển ranh giới của mảng đã sắp xếp và chưa sắp xếp
    int min_idx;
    for (int i = 0; i < n - 1; i++) {
        // Tìm phần tử nhỏ nhất trong mảng chưa sắp xếp
        min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min_idx])
                min_idx = j;

        // Đổi chỗ phần tử nhỏ nhất với phần tử đầu tiên
        swap(a[min_idx], a[i]);
    }
}

//2. Insertion sort:
//Di chuyển những phần từ nhỏ hơn key về trước key
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

//3. Bubble sort:
//So sánh 2 phần tử liên tiếp từ đầu mảng rồi đổi chỗ chúng (nếu cần), lặp lại cho đến khi được mảng tăng
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

//4. Shaker Sort (Cải tiến của Buble Sort):
//So sánh 2 phần tử liên tiếp từ đầu mảng và 2 phần tử liên tiếp cuối mảng rồi đổi chỗ chúng (nếu cần), lặp lại cho đến khi được mảng tăng
void shakerSort(int a[], int n) {
    int Left = 0;
    int Right = n - 1;
    int k = 0;
    while (Left < Right) {
        for (int i = Left; i < Right; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                k = i;
            }
        }
        Right = k;
        for (int i = Right; i > Left; i--) {
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
                k = i;
            }
        }
        Left = k;
    }
}

//5. Shell sort:
//Dựa trên Insertion sort
//Chia Các phần tử có khoảng cách xa đến gần thành các mảng con. Sắp xếp thứ tự trong các mảng con đó
//Giảm dần khoảng cách ban đầu và lặp lại cho đến khi tìm được mảng tăng dần
void shellSort(int a[], int n) {
    // interval là biến khoảng cách giữa các phần tử
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= interval && a[j - interval] > temp; j -= interval) {
                a[j] = a[j - interval];
            }
            a[j] = temp;
        }
    }
}

//6. Heap sort:
//Dựa trên Ý tưởng cấu trúc Max Heap của Cây Nhị Phân 
//Tìm được max trên đầu thì hoán đổi nó với phần tử ở cuối cây, sau đó lại điều chỉnh max heap
//Lặp lại như thế cho đến khi có được 1 cây nhị phân mà khi viết ra mảng thì được 1 mảng tăng dần
//6.a Hàm điều chỉnh max heap
void heapify(int a[], int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && a[left] > a[largest])
        largest = left;

    if (right < N && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, N, largest);
    }
}

//6.b Hàm tạo max heap
void builMaxHeap(int a[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(a, N, i);
}

//6.c Hàm Heap Sort:
void heapSort(int a[], int N)
{
    //Đầu tiên tạo max heap
    builMaxHeap(a, N);

    for (int i = N - 1; i >= 0; i--) {
        //Hoán đổi max trên đầu max heap với giá trị cuối mảng
        //Sau đó lại điều chỉnh max heap lại
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

//7. Merge sort:
//Chia nhỏ mảng gốc thành các mảng nhỏ (chia đôi ra nhờ phần tử ở giữa) cho đến khi các mảng con chỉ có 1 phần tử
//Ghép các mảng con đó lại theo thứ tự tăng dần của giá trị phần tử
//Ghép như thế cho đến khi mảng có số lượng phần tử của mảng ban đầu
//7.a Hàm Chia nhỏ và ghép các mảng chia nhỏ đã đó (nhưng đã được sắp xếp tăng dần) lại
void merge(int a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    //Tạo 2 mảng con
    int* L = new int[n1];
    int* R = new int[n2];

    //Sao chép dữ liệu từ mảng gốc sang 2 mảng con
    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    //Ghép 2 mảng con lại rồi sao chép dữ liệu đưa cho mảng gốc
    i = 0; //Vị trí khởi đầu của mảng con L
    j = 0; //Vị trí khởi đầu của mảng con R
    k = l; //Vị trí khởi đầu của mảng gốc (được sao chép dữ liệu đã sắp xếp tăng dần vào)
    while (i < n1 && j < n2) {
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

    //Nếu mảng con L vẫn còn phần tử chưa được sao chép thì sao chép về chúng về mảng gốc
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    //Nếu mảng con R vẫn còn phần tử chưa được sao chép thì sao chép về chúng về mảng gốc
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

//7.b Hàm Merge sort
//l = 0, r = n - 1, m là giá trị ở giữa;
void mergeSort(int a[], int l, int r)
{
    if (l < r) {
        //Tính m thế này giúp tránh tràn số nếu l hoặc r quá lớn
        int m = l + (r - l) / 2;
        //Chia nhỏ các mảng ra rồi ghép tổng thể lại (Theo kiểu đệ quy)
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);

        merge(a, l, m, r);
    }
}


//8. Quick sort:
//Chia để trị (phân hoạch theo 2 con trỏ i và j). Dùng đệ quy
//Sử dụng 1 phần tử để làm mốc so sánh phân hoạch là pivot
//i đi từ đầu mảng về cuối mảng, dừng lại ghi gặp giá trị không bé hơn pivot, nếu gặp thì hoán đổi giá trị với phần tử đó và tăng vị trí bắt đầu của i lên 1 đơn vị (i++)
//j đi từ cuối mảng về đầu mảng, dừng lại ghi gặp giá trị không lớn hơn pivot, nếu gặp thì hoán đổi giá trị với phần tử đó và giảm vị trí bắt đầu của j xuống 1 đơn vị (j--)
//Nếu j vượt qua i thì phân hoạch mảng gốc thành 2 mảng con, mảng con 1 từ phần tử đầu mảng đến phần tử tại vị trí j, mảng con 2 từ phần tử tại vị trí i đến phần tử cuối mảng gốc.

//8.a Hàm tìm phần tử Pivot:
//start = 0; end = n - 1
int partition(int a[], int start, int end) {
    int pivot = a[(start + end) / 2];

    // Sắp xếp mảng bên trái và mảng bên phải của phần tử Pivot
    int i = start, j = end;
    while (i <= j) {
        while (a[i] < pivot) {
            i++;
        }
        while (a[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(a[i++], a[j--]);
        }
    }
    return i;
}

//8.b Hàm Quick sort
void quickSort(int a[], int start, int end) {
    //Điều kiện dừng đệ quy (là khi mảng đã được sắp xếp tăng dần hoàn toàn)
    if (start >= end)
        return;

    // Tao phần tử pivot
    int p = partition(a, start, end);

    // Sắp xếp mảng bên trái
    quickSort(a, start, p - 1);

    // Sắp xếp mảng bên phải
    quickSort(a, p + 1, end);
}

//9. Counting sort:
//LƯU Ý: CHỈ SỬ DỤNG CHO MẢNG CÓ TẤT CẢ PHẦN TỬ KHÔNG ÂM
//Sắp xếp bằng đếm phân phối (số lần xuất hiện)
//Ý tưởng có phần liên quan đến bảng băm
//Cần tạo 1 mảng con có kích thước max - 0 - 1 phần tử, với vị trí từ 0 đến max với max là giá trị lớn nhất trong mảng gốc , mỗi phần tử lưu số lần xuất hiện của giá trị phần tử tương ứng với vị trí của nó
//Giá trị ban đầu của mỗi phần tử trong mảng con là 0
//Đếm số lần xuất hiện của các phần tử trong mảng gốc rồi đưa vào mảng con, sau đó thực hiện sắp xếp dãy dựa trên mảng con

//9.c Hàm tìm giá trị phần tử lớn nhất
int findMaxValue(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

//9.b Counting sort
void countingSort(int a[], int n) {

    //Tạo mảng con đếm số lần xuất hiện của các giá trị
    int maxValue = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > maxValue)
            maxValue = a[i];
    int countArraySize = maxValue + 1;
    int* countArray = new int [countArraySize] {0};

    //Đếm số lần xuất hiện của 1 phần tử trong mảng gốc rồi lưu số lần xuất hiện đó vào mảng con
    for (int i = 0; i < n; i++)
        countArray[a[i]]++;

    //Sắp xếp mảng gốc bằng cách lấy số lần xuất hiện của từng giá trị trong mảng con đếm viết thành dãy rồi sao chép vào mảng gốc
    for (int i = 1; i <= maxValue; i++)
        countArray[i] = countArray[i] + countArray[i - 1];

    int* temp = new int[n];
    for (int i = 0; i < n; i++)
    {
        temp[countArray[a[i]] - 1] = a[i];
        countArray[a[i]]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = temp[i];
    delete[] countArray;
    delete[] temp;
}

//10. Radix sort:
//Sắp xếp theo cơ số
//Dùng thùng chứa, xét từ 0 đến 9, sắp xếp mảng theo chữ số hàng đơn  vị, đến hàng chục, đến hàng trăm, đến ... m với m là số chữ số của số lớn nhất

//10.a Hàm sắp xếp mảng dựa theo cơ số exp truyền vào
// exp = 1
void expSort(int a[], int n, int exp)
{
    //Mảng giữ kết quả sau khi sắp xếp
    int* budget = new int[n];
    //Mảng thùng chứa theo cơ số
    int digit[10] = { 0 };

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        digit[(a[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (int i = 1; i < 10; i++)
        digit[i] += digit[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        budget[digit[(a[i] / exp) % 10] - 1] = a[i];
        digit[(a[i] / exp) % 10]--;
    }

    // Copy the output array to a[], so that a[] now
    // contains sorted numbers according to current digit
    for (int i = 0; i < n; i++)
        a[i] = budget[i];
}

//10.b Hàm Radix sort:
void radixSort(int a[], int n) {
    //Tìm só lượng chữ số của số lớn nhất trong mảng
    int maxValue = findMaxValue(a, n);

    //Sắp xếp mảng theo chữ số hàng đơn vị, chục, trăm, ....
    for (int exp = 1; maxValue / exp > 0; exp *= 10) {
        expSort(a, n, exp);
    }
}

//11. Flash sort:
//Có 3 bước:
//+B1: Phân lớp dữ liệu: Dựa trên 1 giả thuyết dữ liệu phân bố (công thức) nào đó để tìm công thức ước tính vị trị (lớp) của phần tử sau khi sắp xếp
//+B1a: Đếm số lượng phần tử các lớp theo quy luật, phần tử a[i] sẽ thuộc lớp k = int((m - 1) * (a[i]-minVal) / (a[max] - minVal))
//+B1b: Tính vị trí kết thúc của phân lớp thứ j theo công thức L[j] = L[j] + L[j - 1] (j tăng từ 1 đến m - 1)
//+B2: Hoán vị toàn cục: Dời chuyển các phần tử trong mảng về lớp của mình
//+B3: Sắp xếp cục bộ: Sắp xếp lại các phần tử trong phạm vi của từng lớp
void flashSort(int a[], int n)
{
    int minVal = a[0];
    int maxIndex = 0;

    //Chia các lớp:
    // Tính Số lớp chia ra. Thường người ta sẽ chia là 0.45 x số lượng phần tử của mảng
    int nclass = int(0.45 * n);

    //Mảng classes với mỗi phần tử là 1 lớp và dữ liệu của nó là số lượng phần tử nằm trong lớp đó
    int* classes = new int[nclass] {0};

    //Tìm phần tử nhỏ nhất và vị trí phần tử lớn nhất
    for (int i = 1; i < n; i++)
    {
        if (a[i] < minVal)
            minVal = a[i];
        if (a[i] > a[maxIndex])
            maxIndex = i;
    }

    //Nếu mảng chỉ có 1 phần tử hoặc nhiều phần tử nhưng các phần tử đều bằng nhau thì không cần sắp xếp
    if (a[maxIndex] == minVal)
        return;

    //Tính phần tử c1 để xác định lớp mà phần tử a[i] sẽ được thêm vào (công thức được áp dụng đã được chứng minh)
    double c1 = (double)(nclass - 1) / (a[maxIndex] - minVal);
    //Vị trí lớp mà phần tử a[i] được thêm vào là k với k = (a[i] - minVal) * c1
    //Đếm số phần tử trong từng lớp
    for (int i = 0; i < n; i++)
    {
        int k = int(c1 * (a[i] - minVal));
        ++classes[k];
    }
    //Tính index cuối cùng của từng lớp
    for (int i = 1; i < nclass; i++)
        classes[i] += classes[i - 1];

    //Sau khi có số lượng phần tử từng lớp thì tiến hành sắp xếp các phần tử trong lớp đó, rồi ghép các lớp về thành 1 mảng kết qu
    //Sử dụng hoán vị toàn cục cho các phần tử trong các sô, nếu thêm 1 phần tử vào lớp này thì phải đẩy 1 phần tử sang lớp kia
    swap(a[maxIndex], a[0]);
    int nmove = 0;
    int j = 0;
    int k = nclass - 1;
    int t = 0;
    int flash;
    while (nmove < n - 1)
    {
        while (j > classes[k] - 1)
        {
            j++;
            k = int(c1 * (a[j] - minVal));
        }
        flash = a[j];
        if (k < 0) break;
        while (j != classes[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = a[t = --classes[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    //Sau bước này thì tất cả các phần tử ở trong lớp trước sẽ nhỏ hơn tất cả phần tử nằm ở trong lớp sau

    //Cuối cùng gọi insertionSort sắp xếp cục bộ, sắp xếp các phần tử trong 1 lớp, insertionSort lúc này chỉ còn là O(1)
    delete[] classes;
    insertionSort(a, n);
}