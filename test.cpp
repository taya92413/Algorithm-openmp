//
// Created by Mike on 2018/4/19.
//
#include <iostream>
#include <string>
#include <ctime>
#include <omp.h>
#include <fstream>

using namespace std;

string strcp(string a, string b);

void selection_sort(string arr[], int len);

void swap(string *a, string *b);

void printArray(string arr[], int size);

void heapSort(string arr[], int n);

void heapify(string arr[], int n, int i);

void mergeSort(string arr[], int l, int r);

void merge(string arr[], int l, int m, int r);

void iterativemergeSort(string arr[], int n);

int min(int x, int y);

int recursivebinarySearch(string arr[], int l, int r, string x);

int iterativebinarySearch(string arr[], int l, int r, string x);

int main() {
    srand((unsigned) time(NULL));
    clock_t t1, t2;
    string dataset = "abcdefghijklmnopqrstuvwxyz";
    string name("abcdef");
    int ndata[] = {10000, 50000, 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000, 550000,
                   600000};
    int x = 0;
    int t = 10000000;
    string *data;

    //50000, 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000, 550000,600000
    //cout << "\t" << "selectionsort(MP)" << "\t" << "heapsort" << "\t" << "mergesort" << endl;

    for (int j = 0; j < sizeof(ndata) / sizeof(ndata[0]); j++) {
        data = new string[ndata[j]];
        cout << "createdata" << endl;
        for (int i = 0; i < ndata[j]; i++) {

            for (int k = 0; k < 6; k++) {
                name[k] = dataset[rand() % 26];

            }
            data[i] = strcp(data[i], name);
            //cout  << data[i] << "\n";
        }
        cout << "run" << endl;
        //selection_sort(data, ndata[j]);
        //heapSort(data, ndata[j]);
        mergeSort(data, 0, ndata[j] - 1);
        //iterativemergeSort(data, ndata[j]-1);
        //printArray(data, ndata[j]);
        t1 = clock();
        for (int i = 0; i < t; i++) {
            x = rand() % ndata[j];
            //recursivebinarySearch(data, 0, ndata[j] - 1, data[x]);
            iterativebinarySearch(data, 0, ndata[j] - 1, data[x]);
        }
        t2 = clock();
        cout << ndata[j] << " data" << endl;
        cout << t << " searchtimes" << "   " << (t2 - t1) / (double) (CLOCKS_PER_SEC) << "s" << endl;
        //cout << ndata[j] << " times" << "   " << (t2 - t1) / (double) (CLOCKS_PER_SEC) << "s" << endl;
        delete[] data;
    }


    return 0;


}

string strcp(string a, string b) {

    string a1 = a;
    string a2 = b;
    a1 = a2;
    return a1;
}

void swap(string *a, string *b) {
    string temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(string arr[], int len) {


    for (int i = 0; i < len - 1; i++) {

        int min = i;
#pragma omp parallel for
        for (int j = i + 1; j < len; j++)
            if (arr[j] < arr[min])
                min = j;
        swap(&arr[min], &arr[i]);
    }
}

void printArray(string arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << endl;
}

void heapify(string arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(string arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(string arr[], int l, int m, int r) {
    int i = 0, j = 0, k = 0;
    int n1 = m - l + 1;
    int n2 = r - m;
    string *L, *R;
    L = new string[n1];
    R = new string[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

void mergeSort(string arr[], int l, int r) {
    if (l < r) {

        int m = l + (r - l) / 2;//等於(l+r)/2
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int min(int x, int y) { return (x < y) ? x : y; }

void iterativemergeSort(string arr[], int n) {
    int currsize;

    int leftstart;

    for (currsize = 1; currsize < n; currsize = 2 * currsize) {

        for (leftstart = 0; leftstart < n; leftstart += 2 * currsize) {
            if (currsize > n - leftstart)
                break;
            int mid = leftstart + currsize - 1;
            int rightend = min(leftstart + 2 * currsize - 1, n);
            merge(arr, leftstart, mid, rightend);


        }
    }
}

int recursivebinarySearch(string arr[], int l, int r, string x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return recursivebinarySearch(arr, l, mid - 1, x);

        return recursivebinarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

int iterativebinarySearch(string arr[], int l, int r, string x) {
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (arr[m] == x)
            return m;

        if (arr[m] < x)
            l = m + 1;

        else
            r = m - 1;
    }

    return -1;
}