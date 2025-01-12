#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function using the first element as pivot
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int left = low + 1;
    int right = high;

    while (left <= right) {
        while (left <= right && arr[left] <= pivot) left++;
        while (left <= right && arr[right] > pivot) right--;
        if (left < right) swap(arr[left], arr[right]);
    }

    swap(arr[low], arr[right]);
    return right;
}

// QuickSort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    // Generate random data
    int size = 10000;  // Change this value for larger sizes
    vector<int> data(size);

    // Fill the vector with random numbers
    srand(time(0));
    for (int& num : data) {
        num = rand() % 100000;
    }

    // Measure sorting time
    auto start = chrono::high_resolution_clock::now();
    quickSort(data, 0, data.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Sorted " << size << " elements in " << elapsed.count() << " seconds.\n";

    return 0;
}
