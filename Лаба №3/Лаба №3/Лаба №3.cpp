#include <iostream>
#include <conio.h>
using namespace std;
const int nmax = 15;

void insertionSort(double* data,int& size) {
    int j = 0;
    double curr = 0;
    for (int i=0; i < size; i++) {
        j = i - 1;
        curr = data[i];
        while (data[j]>curr and j>=0){
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = curr;
    }

}


void selectionSort(double* data, int& size) {
    double MaxD = 0;
    int temp = 0;
    double tempV = 0;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size - i; j++) {
            if (MaxD < data[j]) {
                MaxD = data[j];
                temp = j;
            }
        }

        tempV = data[size - i-1];
        data[size - i-1] = MaxD;
        data[temp] = tempV;
        MaxD = 0;
        temp = 0;

    }

}


void bubbleSort(double* data, int& size){
    double temp = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) { temp = data[j]; data[j] = data[j + 1]; data[j + 1] = temp; }
        }
    }


}


//void merge(int begin, int end, double* data) {
//    int
//        i = begin,
//        mid = (begin + end) / 2,
//        j = mid + 1,
//        k = 0;
//    double
//        d[100];
//
//    while (i <= mid and j <= end) {
//        if (data[i] <= data[j]) {
//            d[k] = data[i]; i++;
//        }
//        else {
//            d[k] = data[j]; j++;
//        }
//        k++;
//    }
//
//    while (i <= mid) {
//        d[k] = data[i];
//        i++; k++;
//    }
//
//    while (j <= end) {
//        d[k] = data[j];
//        j++; k++;
//    }
//
//    for (int m = 0; m < k; m++) {
//        data[begin + m] = d[m];
//    }
//
//
//}
//
//
//void mergeSort(int left, int right, double* data) {
//
//    int temp = 0;
//    if (left < right) {
//        if (right - left == 1) {
//            if (data[left] > data[right]) {
//                temp = data[left];
//                data[left] = data[right];
//                data[right] = temp;
//            }
//        }
//        else {
//            mergeSort(left, (left + right) / 2, data);
//            mergeSort((left + right) / 2, right, data);
//            merge(left, right, data);
//
//        }
//    }
//
//}


void merge(double* arr, int low, int high, int mid)
{
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        }
        else {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        arr[i] = c[i];
    }
}


void mergeSort(double* arr, int low, int high)
{
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
}


void Shell(double* data, int n){

    int i, j,d, count;
    d = n;
    d = d / 2;
    while (d > 0)
    {
        for (i = 0; i < n - d; i++)
        {
            j = i;
            while (j >= 0 && data[j] > data[j + d])
            {
                count = data[j];
                data[j] = data[j + d];
                data[j + d] = count;
                j--;
            }
        }
        d = d / 2;
    }
   
}


void Qsort(double* mas, int size) {

    int i = 0;
    int j = size - 1;
    int mid = mas[size / 2];

    do {
      
        while (mas[i] < mid) {
            i++;
        }
       
        while (mas[j] > mid) {
            j--;
        }

        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    if (j > 0) {
        Qsort(mas, j + 1);
    }
    
    if (i < size) {
        Qsort(&mas[i], size - i);
    }

}


int main()
{
    double data[11] = { 16,2,8,7,3,32,1,2,5,6,7 };
    int size = (sizeof(data) / sizeof(*data));

    /*insertionSort(data,size);
    for (int i = 0; i < 11; i++) {
        cout << data[i] << ' ';
    }*/


    /*selectionSort(data, size);
    for (int i = 0; i < 11; i++) {
        cout << data[i] << ' ';
    }*/


    /* bubbleSort(data, size);
    for (int i = 0; i < 11; i++) {
        cout << data[i] << ' ';
    }*/


    /*mergeSort(data,0, size-1);
    for (int i = 0; i < 11; i++) {
        cout << data[i] << ' ';
    }*/


    /*Shell(data, size);
    for (int i = 0; i < 11; i++) {
        cout << data[i] << ' ';
    }*/


    /*Qsort(data, size);
    for (int i = 0; i < 11; i++) {
        cout << data[i] << ' ';
    }*/

}
