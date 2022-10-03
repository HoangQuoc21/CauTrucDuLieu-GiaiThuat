#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
//I. POINTERS
//1. With 2 interger;
void swap(int*a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* sum(int* a, int* b){
    int *sum = new int;
    *sum = *a + *b;
    return sum;
}

//2. With 1 1D Arrays
void inputArray(int* &a, int &n){
    for (int i=0; i<n; i++){
        cout << "a[" << i << "] = ";
        cin >> a[i];
    }
}

void printArray(int *a, int n){
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int* findMax(int* arr, int n){
    int *max  = new int;
    *max = arr[0];
    for (int i = 1; i < n; i++){
        for (int j = i +1; j < n; j++){
            if (arr[j] > *max)
                *max = arr[j];
        }
    }
    return max;
}

int* findLongestAscendingSubarray(int* a, int n, int& length){
    //Tìm length và lưu vị trí bắt đầu của dãy con lớn nhất (j)
    length = 1;
    int* indexOfSubArray = &a[0];
    for (int i = 0; i < n; i++){
        int currentLength = 1;
        int* currentIndex = &a[i];
        for (int j = i; j < n-1; j++){
            if(a[j] < a[j+1])
                currentLength++;
            else
                break;
        }
        if (currentLength > length){
            length = currentLength;
            indexOfSubArray = currentIndex;
        }
    }
    return indexOfSubArray;
}

//3. With 2 1D Arrays

void swapArrays(int* &a, int* &b, int &na, int &nb){
    int temp = na;
    na = nb;
    nb = temp;
    int* tempPointer = &a[0];
    a = &b[0];
    b = tempPointer;
}

int* concatenate2Arrays(int* a, int*b, int na, int nb, int &nc){
    nc = na+nb;
    int* c = new int[nc];
    for (int i = 0; i < na; i++){
        c[i] = a[i];
        c[i+na] = b[i];
    }
    return c;
}

int* merge2Arrays(int*a , int*b, int na, int nb, int &nc){
    int* c = concatenate2Arrays(a,b,na,nb,nc);
    for (int i = 0; i < nc; i++){
        for (int j = i; j < nc; j++){
            if (c[j] < c[i]){
                swap(c[j], c[i]);
            }
        }
    }
    return c;
}

//4. With 1 Matrix

void printMatrix(int** a, int length, int width){
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
}

void generateMatrix1(int** &a, int &length, int &width){
    a = new int*[length];
    for (int i = 0; i < length; i++)
        a[i] = new int[width];
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
}

int** generateMatrix2(int* a, int* b, int na, int nb, int &crow, int &ccol){
    crow = na;
    ccol = nb;
    int** c = new int*[crow];
    for (int i = 0; i < crow; i++)
        c[i] = new int [ccol];
    for (int i = 0; i < crow; i++){
        for (int j = 0; j < ccol; j++)
            c[i][j] = a[i]*b[j];
    }
    return c;
}

void swapRows(int** a, int length, int width, int ir1, int ir2){
    swapArrays(a[ir1], a[ir2], width, width);
}

void swapColumns(int** a, int length, int width, int ic1, int ic2){
    for (int i = 0; i < length; i++)
        swap(a[i][ic1], a[i][ic2]);
}

int** transposeMatrix(int** a, int length, int width){
    int** t = new int*[width];
    for (int i = 0; i < width; i++)
        t[i] = new int [length];
    for (int i = 0; i < width; i++)
        for (int j = 0; j < length; j++)
            t[i][j] = a[j][i];
    return t;
}
//Theo chiều ngang
int** concatenate2MatricesH(int** a, int** b, int length, int width, int &lres, int &wres){
    lres = length;
    wres = width*2;
    int** newMa = new int*[lres];
    for (int i = 0; i < lres; i++)
        newMa[i] = new int [wres];
    for (int i = 0; i < lres; i++){
        for (int j = 0; j < width; j++){
            newMa[i][j] = a[i][j];
            newMa[i][j+width] = b[i][j];
        }
    }
    return newMa;
}

//Theo chiều dọc
int** concatenate2MatricesV(int** a, int** b, int length, int width, int &lres, int &wres){
    lres = length*2;
    wres = width;
    int** newMa = new int*[lres];
    for (int i = 0; i < lres; i++)
        newMa[i] = new int [wres];
    for (int i = 0; i < length; i++){
        for (int j = 0; j < wres; j++){
            newMa[i][j] = a[i][j];
            newMa[i+length][j] = b[i][j];
        }
    }
    return newMa;
}

bool multiple2Matrices(int**& res, int** a, int **b, int& lengthr, int& widthr, int lengtha, int widtha, int lengthb, int widthb){
    if (widtha != lengthb)
        return false;
    else{
        lengthr = lengtha;
        widthr = widthb;
        res = new int* [lengthr];
        for (int i=0; i<lengthr; i++)
            res[i] = new int [widthr];
        for (int i = 0; i < lengthr; i++)
            for (int j = 0; j < widthr; j++){
                int result = 0;
                for (int k = 0; k < widtha; k++)
                    result = result+ a[i][k]*b[k][j];
                res[i][j] = result;
            }
        return true;
    }
}

int** findSubmatrix(int** a, int length, int width, int &lres, int &wres){
    //Giả sử đã kiểm tra tính hợp lệ của lres và wres
    int** subMa = new int* [lres];
    for (int i = 0; i < lres; i++)
        subMa[i] = new int [wres];
    int max = 0;
    int rIndex, cIndex;
    for (int i = 0; i < length - lres + 1 ; i++){
        for (int j = 0; j < width - wres + 1; j++){
            int sum = 0;
            for (int k = 0; k < lres; k++)
                for (int t = 0; t < wres; t++){
                    sum =sum + a[i+k][j+t];
                }
            if (sum > max){
                max = sum;
                rIndex = i;
                cIndex = j;
            }
        }
    }
    for (int i = 0; i < lres; i++)
        for (int j = 0; j < wres; j++)
            subMa[i][j] = a[rIndex+i][cIndex+j];
    return subMa;
}

int LinearSearch(int* a, int n, int key){
    int i = 0;
    while (i <  n && a[i] != key)
        i++;
    if (i == n)
        return -1;
    else
        return i;
}

int SentinelLinearSearch(int* a, int n, int key){
    int i = 0;
    a[n] = key;
    while (a[i] != key)
        i++;
    if (i == n)
        return -1;
    else
        return i;
}

int BinarySearch(int* a, int n, int key){
    int left = 0, right = n - 1;
    int mid;
    while(left <= right){
        mid = (left + right)/2;
        if (a[mid] == key)
            return mid;
        else if (key < a[mid])
            right = mid-1;
        else
            left = mid+1;
    }
    return -1;
}

int RecursiveBinarySearch(int* a, int left, int right, int key){
    int mid = (left + right)/2;
    if (a[mid] == key)
        return mid;
    else if (mid == right)
        return -1;
    else if (key < a[mid])
        return RecursiveBinarySearch(a, left, mid - 1 , key);
    else if (key > a[mid])
        return RecursiveBinarySearch(a, mid + 1, right, key);
}

//II. RECURSION
//1. With 1 little interger
int sumRecursive(int n){
    if (n==0)
        return 0;
    return (n + sumRecursive(n-1));
}

int factorial(int n){
    if (n==1)
        return 1;
    return (n*factorial(n-1));
}

int exponentiation(int x, int n){
    if (n==0)
        return 1;
    return (x*exponentiation(x,n-1));
}

//2. With 1 big interger
int countNumberOfDigits(int n){
    if (n < 10)
        return 1;
    return(1+countNumberOfDigits(n/10));
}

bool isAllDigitsEven(int n){
    if (n < 10 && n >= 0)
        return (n%2==0);
    return (isAllDigitsEven(n%10)&&isAllDigitsEven(n/10));
}

int reverseValue(int number){
    static int reverseNumber = 0;
    if (number == 0)
        return reverseNumber;
    else{
        reverseNumber = 10*reverseNumber + number%10;
        return reverseValue(number/10);
    }
}

//3. With 2 interger
int greatestCommonDivisor(int number1, int number2){
    if(number2 == 0)
        return number1;
    return greatestCommonDivisor(number2, number1 % number2);
}

int leastCommonMultiple(int number1, int number2){
    return ((number1 * number2)/greatestCommonDivisor(number1, number2));
}

int countNumberOfCommonDivisor(int number1, int number2){
    //Biến i dùng để tìm ước chung của 2 số bằng cách sử dụng vòng lặp chia 
    static int i = 1; 
    if (i == greatestCommonDivisor(number1,number2))
        return 1;
    i++;
    return (((number1 % i == 0)&&(number2 % i == 0)) + countNumberOfCommonDivisor(number1,number2)); 
}

//4. Fibonacci 


int fibonacciNumber(int n){
    if (n == 0 || n == 1)
        return 1;
    return (fibonacciNumber(n-1) + fibonacciNumber(n-2));
}

//5. With 4 characters

//Hàm in kết quả của những hoán vị tìm được
void printResult(int n, char result[]){
    for (int i = 0; i < n; i++)
        cout << result[i];
    cout << ", ";
}

//Hàm này dùng đệ quy quay lui
void allPossiblePermutation(int i ,int n, char charArray[], char result[], char used[]){
    for (int j = 0; j < n;j++){
        if(used[j] == 0){
            result[i] = charArray[j];
            used[j] = 1;
            if (i == (n - 1))
                printResult(n,result);
            else
                allPossiblePermutation(i+1,n,charArray,result,used);
            used[j] = 0;
        }
    }
}

//III. My Functions
//==================MENU FUNCTIONS===================

void op1a(){
    while(1){
        system("cls");
        string choice;
        cout << "1. Work with 2 numbers.\n";
        cout << "2. Go back to POINTER MENU.\n";
        cout << "---------------------------------\n";
        cout << "Your choice: ";
        cin >> choice;
        if (choice == "1"){
            int number1, number2; 
            cout << "Please enter Number1's value: ";
            cin >> number1;
            cout << "Please enter Number2's value: ";
            cin >> number2;
            cout << "Number1= " << number1 << ", Number2= " << number2 << endl;
            int *a = &number1;
            int *b = &number2;
            int *Sum = sum(a,b);
            cout << number1 << " + " << number2 << "= " << *Sum << endl;
            swap(a,b);
            cout << "After swapping. Number1 =  " << number1 << ", Number2 = " << number2 << endl;  
        }
        else if (choice == "2")
            break;
        else 
            cout << "Invalid choice.\n";
        system("pause");
    }
}

void op1b(){
    int size;
    cout << "Please enter Array's size: ";
    cin >> size;
    int* array = new int[size];
    inputArray(array,size);
    while(1){
        system("cls");
        cout << "Inputed Array: ";
        printArray(array,size);
        cout << "=======================================\n";
        int* max = findMax(array,size);
        cout << "1. The max element of the Array: " << *max << endl;
        int subArraySize;
        cout << "2. The longest ascending subArray: ";
        int* subArray = findLongestAscendingSubarray(array,size,subArraySize);
        printArray(subArray,subArraySize);
        cout << "---------------------------------------\n";
        string choice;
        cout << "3.Enter \"F\" if you want to find a value in the Array. \"E\" if you want to go back to POINTER MENU.\n" << endl;
        cout << "Your choice: ";
        cin >> choice;
        if (choice == "F"){
            int value;
            cout << "Enter the value you want to find: ";
            cin >> value;
            cout << "-LinearSearch: a[" << LinearSearch(array,size,value) << "].\n";
            cout << "-SentinelLinearSearch: a[" << SentinelLinearSearch(array,size,value) << "].\n";
            cout << "-BinarySearch: a[" << BinarySearch(array,size,value) << "].\n";
            cout << "-RecursiveBinarySearch: a[" << RecursiveBinarySearch(array,0,size,value) << "].\n";
        }  
        else if (choice == "E")
            break;
        else 
            cout << "Invalid choice.\n";
        system("pause");
    }
}

void op1c(){
    while(1){
        system("cls");
        string choice;
        cout << "1. Works with 2 Arrays.\n";
        cout << "2. Go back to POINTER MENU.\n";
        cout << "-------------------------------\n";
        cout << "Your choice: ";
        cin >> choice;
        if (choice == "1"){
            int size1, size2;
            cout << "Please enter size of Array1 & Array2: ";
            cin >> size1 >> size2;
            int* array1 = new int[size1];
            int* array2 = new int[size2];
            cout << "Please inpur Array1: ";
            inputArray(array1, size1);
            cout << "Please inpur Array2: ";
            inputArray(array2, size2);
            cout << "-------------------------------\n";
            cout << "Array1: ";
            printArray(array1, size1);
            cout << "Array2: ";
            printArray(array2, size2);
            swapArrays(array1, array2,size1,size2);
            cout << "a. After swap: \n";
            cout << "Array1: ";
            printArray(array1, size1);
            cout << "Array2: ";
            printArray(array2, size2);
            int nC;
            int* cArray = concatenate2Arrays(array1, array2,size1, size2, nC);
            cout << "b. Concatenated array: ";
            printArray(cArray, nC);
            int nM;
            cout << "c. Merged array: ";
            int *mArray = merge2Arrays(array1,array2,size1,size2,nM);
            printArray(mArray, nM);
            int mrow, mcol;
            int** matrix = generateMatrix2(array1,array2,size1, size2, mrow, mcol);
            cout << "d. Generated Matrix from Array1 & Array2: \n";
            printMatrix(matrix,mrow,mcol);
        }
        else if (choice == "2")
            break;
        else
            cout << "Invalid choice.\n";
        system("pause");
    }   
}

void op1d(){
    int length1, width1;
    cout << "Enter the length and width of the matrix1 and matrix2: ";
    cin >> length1 >> width1;
    int **matrix1;
    int ** Tmaxtrix1;
    cout << "Enter matrix1: \n";
    generateMatrix1(matrix1,length1, width1);
    system("cls");
    int **matrix2;
    cout << "Enter matrix2: \n";
    generateMatrix1(matrix2, length1, width1);
    while(1){
        system("cls");
        string choice;
        int lres1, wres1, lres2, wres2,lres3,wres3;
        cout << "Inputed matrix1: \n";
        printMatrix(matrix1,length1, width1);
        cout << "Inputed matrix2: \n";
        printMatrix(matrix2,length1, width1);
        cout << "---------------------------------------\n";
        Tmaxtrix1 = transposeMatrix(matrix1,length1,width1);
        cout << "Transpose maxtrix: \n";
        printMatrix(Tmaxtrix1,width1,length1);
        cout << "---------------------------------------\n";
        cout << "Concatenated2MatricedsH: \n";
        int **Hmatrix = concatenate2MatricesH (matrix1, matrix2,length1, width1,lres1,wres1);
        printMatrix(Hmatrix, lres1, wres1);
        cout << "---------------------------------------\n";
        cout << "Concatenated2MatricedsV: \n";
        int **Vmatrix = concatenate2MatricesV(matrix1, matrix2,length1, width1, lres2, wres2);
        printMatrix(Vmatrix, lres2, wres2);
        cout << "---------------------------------------\n";
        cout << "Multiple matrix1 and matrix2: \n";
        int** mulMatrix;
        int mlength, mwidth;
        if(multiple2Matrices(mulMatrix,matrix1, matrix2,mlength, mwidth, length1, width1, length1, width1))
            printMatrix(mulMatrix,mlength,mwidth);
        else
            cout << "Can not multiple 2 matrices.\n";
        cout << "---------------------------------------\n";
        cout << "The submatrix of the muilpled matrix above: \n";
        cout << "Enter the number of column and row of the submatrix: ";
        cin >> lres3 >> wres3;
        int** subMatrix = findSubmatrix(mulMatrix,mlength, mwidth, lres3, wres3);
        printMatrix(subMatrix,lres3, wres3);
        cout << "=======================================\n";
        cout << "1. Swap 2 columns of matrix1.\n";
        cout << "2. Swap 2 rows of matrix1.\n";
        cout << "3. Go back to POINTER MENU.\n";
        cout << "---------------------------------------\n";
        cout << "Your choice: ";
        cin >> choice;
        if (choice == "1"){
            int col1, col2;
            cout << "Enter the two columns that you want to swap: ";
            cin >> col1 >> col2;
            swapColumns(matrix1, length1, width1, col1, col2);
        }
        else if (choice == "2"){
            int row1, row2;
            cout << "Enter the two columns that you want to swap: ";
            cin >> row1 >> row2;
            swapRows(matrix1, length1, width1, row1, row2);
        }
        else if (choice == "3")
            break;
        else
            cout << "Invalid choice.\n";
        system("pause");
    }
}

void op2a(){
    int number1,number2 , x;
    cout << "Enter the first little integer that you want to work with: ";
    cin >> number1;
    cout << "Enter the second little integer that you want to work with: ";
    cin >> number2;
    system ("cls");
    cout << "Number1 = " << number1 << ", Number2 = " << number2 << endl;
    cout << "---------------------------------------\n";
    cout << "a. S = 1 + 2 + 3 + ... + number1 = " << sumRecursive(number1) << endl;
    cout << "b. number1! = 1*2*3*...*number1 = " << factorial(number1) << endl;
    cout << "Enter x: ";
    cin >> x;
    cout << "c. x^(number1) = " << exponentiation(x,number1) << endl;
    cout << "d. The Greatest Common Divisor of number1 & number2 is: " << greatestCommonDivisor(number1, number2) << endl;
    cout << "e. The Least Common Multiple of number1 & number2 is: " << leastCommonMultiple(number1,number2) << endl;
    cout << "f. The number of common divisors of number1 & number2 is: " << countNumberOfCommonDivisor(number1, number2) << endl;
}

void op2b(){
    int number;
    cout << "Enter the big integer that you want to work with: ";
    cin >> number;
    system("cls");
    cout << "Entered number: " << number << endl;
    cout << "---------------------------------------\n";
    cout << "a. The number if digits of it: " << countNumberOfDigits(number) << endl;
    if (isAllDigitsEven(number))
        cout << "b. Every digits of it are even.\n";
    else
        cout << "c. Every digit of it are not even.\n";
    cout << "d. The reserved value of it is: " << reverseValue(number) << endl;
}

void op2c(){
    int i;
    cout << "Enter the ith number of Fibonacci that you want to find: ";
    cin >> i;
    cout << "---------------------------------------\n";
    cout << "The " << i << " number of Fibonacci is: " << fibonacciNumber(i) << endl;
}

void op2d(){
    char charArray[4];
    for (int i = 0; i < 4; i++){
        cout << "Enter the letter: " << i + 1 <<": ";
        cin >> charArray[i];
    }
    char result[100] = {0};
    char used[100] = {0};
    cout << "---------------------------------------\n";
    cout << "All possible permutation can happen with 4 letters above are : \n";
    allPossiblePermutation(0,4,charArray,result,used);
}


int main(){
    
    while(1){
        system("cls");
        string choice1;
        cout << "****************************************************************\n";
        cout << "*                              WEEK1                           *\n";
        cout << "****************************************************************\n";
        cout << "============================== MENU ============================\n";
        cout << "1. POINTER MENU.\n";
        cout << "2. RECURSION MENU.\n";
        cout << "3. EXIT PROGRAM.\n";
        cout << "============================== END ============================\n";
        cout << "Your choice: ";
        cin >> choice1;
        if (choice1 == "1"){
            string choice2;
            while(1){
                system("cls");
                cout << "========================== POINTERS MENU =======================\n";
                cout << "a. Works with 2 pointers.\n";
                cout << "b. Works with 1 arrays.\n";
                cout << "c. Works with 2 arrays.\n";
                cout << "d. Works with matrix.\n";
                cout << "0. Go back to Main Menu.\n";
                cout << "============================== END ============================\n";
                cout << "Your choice: ";
                cin >> choice2;
                if (choice2 == "a")
                    op1a();
                else if (choice2 == "b")
                    op1b();
                else if (choice2 == "c")
                    op1c();
                else if (choice2 == "d")
                    op1d();
                else if (choice2 == "0")
                    break;
                else
                    cout << "Invalid choice.\n";
                system("pause");
            }
        }
        else if (choice1 == "2"){
            string choice2;
            while(1){
                system("cls");
                cout << "=========================== RECURSION =========================\n";
                cout << "a. Works with 2 little integer.\n";
                cout << "b. Works with 1 big integer.\n";
                cout << "c. Find ith number of Fibonacci.\n";
                cout << "d. Find all possible permutation can happen with 4 letters.\n";
                cout << "0. Go back to Main Menu.\n";
                cout << "============================== END ============================\n";
                cout << "Your choice: ";
                cin >> choice2;
                if (choice2 == "a")
                    op2a();
                else if (choice2 == "b")
                    op2b();
                else if (choice2 == "c")
                    op2c();
                else if (choice2 == "d")
                    op2d();
                else if (choice2 == "0")
                    break;
                else
                    cout << "Invalid choice.\n";
                system("pause");

            }
        }
        else if (choice1 == "3")
            exit(0);
        else
            cout << "Invalid choice.\n";
        system("pause");
    }
    return 0;
}