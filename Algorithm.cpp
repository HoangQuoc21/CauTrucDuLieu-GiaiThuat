#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define max 100
//I. CÁC THUẬT TOÁN TÌM KIẾM NỘI:

//1. TÌM KIẾM TUYẾN TÍNH: O(n)
int LinearSearch1(int a[], int n, int x){
    int i = 0;
    while (i < n && a[i] != x)
        i++;
    if (i == n)
        return -1;
    else
        return i;
}

//* TÌM KIẾM TUYẾN TÍNH CÓ LÍNH CANH ( GIÚP GIẢM BỚT 1 PHÉP SO SÁNH TRONG MỖI VÒNG LẶP): O(n-1)
int LinearSearch2 (int a[], int n, int x){
    int i = 0;
    a[n] = x;
    while (a[i] != x)
        i++;
    if (i == n)
        return -1;
    else
        return i;
}

//2. TÌM KIẾM NHỊ PHÂN (DÙNG CHO MẢNG ĐÃ ĐƯỢC SẮP XẾP): O(log2n)
int BinarySearch(int a[], int n, int x){
    int left = 0, right = n - 1;
    int mid;
    while (left < right){
        mid = (left + right)/2;
        if (a[mid] == x)
            return mid;
        else{
            if (x < a[mid])
                right = mid - 1;
            else
                left = right + 1;
        }
    }
    return -1;
}

//II. CÁC THUẬT TOÁN SẮP XẾP NỘI (TỪ NHỎ TỚI LỚN):

//1. SẮP XẾP CHỌN TRỰC TIẾP: O(n^2)
void SelectionSort (int a[], int n){
    int min;
    for (int i = 0; i < n; i++){
        min = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[min])
                min = j;
            swap(a[min], a[i]);
        }
    }
}

//2. SẮP XẾP CHÈN TRỰC TIẾP: O(n^2)
void InsertionSort (int a[], int n){
    int pos, i;
    int x;
    for (int i = 0; i < n; i++){
        x = a[i];
        pos = i - 1;
        while ((pos >= 0) && (a[pos] > x)){
            a[pos+1] = a[pos];
            pos--;
        }
        a[pos+1] = x;
    }
}

//* SẮP XẾP CHÈN NHỊ PHÂN: O(n^2)
void BinsertionSort(int a[], int n){
    int l,r,m,i;
    int x;
    for (int i = 1; i < n; i++){
        x = a[i];
        l = 1;
        r = i-1;
        while (l <= r){
            m = (l+r)/2;
            if (x < a[m])
                r = m - 1;
            else
                l = m + 1;
        }
        for (int j = i - 1; j >= l; j--)
            a[j+1] = a[j];
        a[l] = x;
    }
}

//3. SẮP XẾP ĐỔI CHỖ TRỰC TIẾP (HAY ĐƯỢC DÙNG NHẤT): O(n^2)
void InterchangeSort (int a[], int n){
    for (int i=0; i<n; i++){
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[i])
                swap(a[j], a[i]);
        }
    }
}

//4. SẮP XẾP PHƯƠNG PHÁP NỔI BỌT: O(n^2)
void BubbleSort (int a[], int n){
    int i,j;
    for (i = 0; i < n; i++){
        for (j = n-1; j > i; j--){
            if (a[j] < a[j-1])
                swap(a[j], a[j-1]);
        }
    }
}

//* SẮP XẾP CẢI TIỂN CỦA BUBBLE_SORT: SHAKER_SORT: O(n^2)
void ShakerSort(int a[], int n){
    int left = 0;
    int right = n - 1;
    int k = 0;
    while (left < right){
        for (int i = left; i < right; i++){
            if (a[i] > a[i + 1]){
                swap(a[i], a[i+1]);
                k = i;
            }
        }
        right = k;
        for (int i = right; i > left; i--){
            if (a[i] < a[i - 1]){
                swap(a[i], a[i-1]);
                k = i;
            }
        }
        left = k;
    }
}

//5. SẮP XẾP HEAP_SORT: O(n^x) với 1<x<2
//Tiêu chỉnh 1 dãy thành heap: 
void Shift (int a[], int l, int r){
    int x,i,j;
    i = l;
    j = 2*i;
    x = a[i];
    while (j <= r){
        if (j < r)
            if (a[j] < a[j + 1])
                j = j + 1;
            if (a[j] < x)
                exit(1);
            else{
                a[i] = a[j];
                i = j;
                j = 2*i;
                a[i] = x;
            }
    }
}

void CreateHeap(int a[], int n){
    int l = n/2;
    while (l > 0){
        Shift(a,l,n);
        l--;
    }
}

void HeapSort(int a[], int n){
    int r;
    CreateHeap(a,n);
    r = n - 1;
    while (r > 0){
        swap(a[0],a[r]);
        r = r - 1;
        Shift(a,0,r);
    }
}

//6. SẮP XẾP SHELL_SORT: O(n^x) với 1<x<2
void ShellSort(int a[], int n, int h[], int k){
    int step,i,j;
    int x,len;
    for (step = 0; step < n; step++){
        len = h[step];
        for (i = len; i < n; i++){
            x = a[i];
            j = i - len;
            while ((x < a[j]) && (j >= 0)){
                a[j+len] = a[j];
                j = j - len;
            }
            a[j + len] = x;
        }
    }
}

//7. SẮP XẾP QHICK_SORT: SẮP XẾP DỰA TRÊN QUY HOẠCH (ĐỆ QUY): O(n*log2n) 
//ĐƯỢC ĐÁNH GIÁ LÀ THUẬT TOÁN SẮP XẾP NHANH NHẤT TRONG SỐ CÁC THUẬT TOÁN
//DỰA TRÊN VIỆC SO SÁNH GIÁ TRỊ CỦA CÁC PHẦN TỬ
void QuickSort (int a[], int l, int r){
    int i,j;
    int x = a[(l+r)/2];
    i = l;
    j = r;
    do {
        while (a[i] < x)    
            i++;
        while (a[j] > x)
            j--;
        if (i <= j){
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }while(i < j);
    if (l < r)
        QuickSort(a,l,j);
    if (i < r)
        QuickSort(a,i,r);
}

//8. SẮP XẾP MERGE_SORT: TRỘN TRỰC TIẾP: O(n*log2n) 
//2 MẢNG PHỤ
int b[max], c[max];

//HÀM MERGE
void Merge(int a[], int nb, int nc, int k){
    int p,pb,pc,ib,ic,kb,kc;
    p = pb = pc = 0;
    ib = ic = 0;
    while ((0 < nb) && (0 < nc) ){
        kb = min(k,nb);
        kc = min(k,nc);
        if (b[pb+ib] <= c[pc+ic]){
            a[p++] = b[pb+ib];
            ib++;
            if (ib == kb){
                for (;ic < kc; ic++)
                    a[p++] = c[pc + ic];
                pb+=kb;
                pc+=kc;
                ib = ic = 0;
                nb-=kb;
                nc-=kc;
            }
        }
        else{
            a[p++] = c[pc+ic];
            ic++;
            if (ic == kc){
                for (;ib < kb; ib++)
                    a[p++] = b[pb+ib];
                pb+=kb;
                pc+=kc;
                ib = ic = 0;
                nb-=kb;
                nc-=kc;
            }
        }
    }
}

void MergeSort(int a[], int n){
    int p, pb, pc;
    int i, k = 1;
    do{
        p = pb = pc;
        while (p < n){
            for ( i = 0; (p < n) && (i < k); i++)
                b[pb++] = a[p++];
            for ( i = 0; (p < n) && (i < k); i++)
                c[pb++] = a[p++];
        }
        Merge(a,pb,pc,k);
        k *= 2;
    }while(k < n);
}

//9. SẮP XẾP THEO PHƯƠNG PHÁP CƠ SỐ RADIX_SORT (POSTMAN'S SORT): O(n)
void RadixSort(int a[], int n)
{
	int i, bucket[max], m = a[0], exp = 1;
	for (i = 0; i < n; i++)
	{
		if (a[i] > m)
			m = a[i];
	}
	while (m / exp > 0)
	{
		int bucket[10] ={  0 };
		for (i = 0; i < n; i++)
			bucket[a[i] / exp % 10]++;
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (i = n - 1; i >= 0; i--)
			b[--bucket[a[i] / exp % 10]] = a[i];
		for (i = 0; i < n; i++)
			a[i] = b[i];
		exp *= 10;
	}
}


int main(){
    system("cls");
    int a[] = {-99,1,0,5,6,7,8,9,10,2,-100,5};
    int n = 12;
}