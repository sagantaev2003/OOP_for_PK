#include <iostream>
#include <vector>
using namespace std;

//  Пузырьковая сортировка 
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

//  Быстрая сортировка 
int partitionQS(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Сортировка слиянием 
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Пирамидальная сортировка 
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Вспомогательная функция печати
void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// запуск
int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> arr = { 9, 5, 1, 4, 3, 8, 7, 2, 6 };

    cout << "Исходный массив:\n";
    printArray(arr);

    // Пузырьковая сортировка
    vector<int> arr1 = arr;
    bubbleSort(arr1);
    cout << "\nПузырьковая сортировка:\n";
    printArray(arr1);

    // Быстрая сортировка
    vector<int> arr2 = arr;
    quickSort(arr2, 0, arr2.size() - 1);
    cout << "\nБыстрая сортировка:\n";
    printArray(arr2);

    // Сортировка слиянием
    vector<int> arr3 = arr;
    mergeSort(arr3, 0, arr3.size() - 1);
    cout << "\nСортировка слиянием:\n";
    printArray(arr3);

    // Пирамидальная сортировка
    vector<int> arr4 = arr;
    heapSort(arr4);
    cout << "\nПирамидальная сортировка:\n";
    printArray(arr4);

    return 0;
}
