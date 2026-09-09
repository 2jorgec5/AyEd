#include <iostream>
#include <vector>

using namespace std;

// bubbleSort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
// insertionSort
void insertionSort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// selectionSort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}
// mergeSort
void merge(vector<int>& arr, int left,int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        R[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {arr[k] = L[i]; i++;}
        else {arr[k] = R[j]; j++;}
        k++;
    }
    while (i < n1) {arr[k] = L[i]; i++; k++;}
    while (j < n2) {arr[k] = R[j]; j++; k++;}
}
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// printers
void printArray(int arr[], int n) {for (int i = 0; i < n; ++i) {cout << arr[i] << " ";}}
void printVector(const vector<int>& arr) {for (int num : arr)cout << " " << num;}

