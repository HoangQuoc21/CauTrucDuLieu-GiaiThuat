#include <iostream>
using namespace std;
#define MAX 100

bool SoChan(int n){
    return (n % 2 == 0);
}

void InterchangeSortEven(int a[], int n){
    //Đưa hết mấy số chẵn về cuối
    for (int i = 0; i < n; i++){
        if (SoChan(a[i]) )
           for (int j = n - 1; j >= i; j--)
                if (!SoChan(a[j]))
                    swap(a[i], a[j]);
    }

    //Lưu vị trí xuất hiện của số chẵn đầu tiên
    int k = 0;
    for (int i = 0; i < n; i++)
        if (SoChan(a[i])){
            k = i;
            break;
        }

    //Sắp xếp mảng con toàn số chẵn ở cuối
    for (int i = n - 1; i >= k + 1; i--)
        for (int j = i - 1; j >= k; j--)
            if (a[i] > a[j])
                swap(a[i], a[j]);
}

int main(){
    int n = 11;
    int a[11] = {0,1,2,3,4,5,6,7,8,9,10};
    system("cls");
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n---------------------------------------\n";
    InterchangeSortEven(a,n);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}