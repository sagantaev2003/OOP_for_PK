#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//  Сортировка вставками 
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//  Сортировка выбором 
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

//  Блочная сортировка 
void bucketSort(vector<int>& arr) {
    int n = arr.size();
    int maxValue = *max_element(arr.begin(), arr.end());
    int bucketCount = sqrt(n);

    vector<vector<int>> buckets(bucketCount);

    for (int num : arr) {
        int index = (num * bucketCount) / (maxValue + 1);
        buckets[index].push_back(num);
    }

    int idx = 0;
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        for (int num : bucket) arr[idx++] = num;
    }
}

// Вспомогательная функция для RadixSort (подсчёт) 
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = { 0 };

    for (int num : arr)
        count[(num / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

//  Поразрядная сортировка
void radixSort(vector<int>& arr) {
    int maxValue = getMax(arr);

    for (int exp = 1; maxValue / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

//  Печать массива 
void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// запуск
int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> arr = { 29, 10, 14, 37, 13, 5, 88, 50, 1 };

    cout << "Исходный массив:\n";
    printArray(arr);

    vector<int> a1 = arr;
    insertionSort(a1);
    cout << "\nСортировка вставками:\n";
    printArray(a1);

    vector<int> a2 = arr;
    selectionSort(a2);
    cout << "\nСортировка выбором:\n";
    printArray(a2);

    vector<int> a3 = arr;
    bucketSort(a3);
    cout << "\nБлочная сортировка:\n";
    printArray(a3);

    vector<int> a4 = arr;
    radixSort(a4);
    cout << "\nПоразрядная сортировка:\n";
    printArray(a4);

    return 0;
}
