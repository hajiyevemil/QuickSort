#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition using the first element as pivot
int partitionFirst(vector<int>& arr, int low, int high) {
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

// Partition using the middle element as pivot
int partitionMiddle(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(arr[low], arr[mid]);
    return partitionFirst(arr, low, high);
}

// Partition using a random element as pivot
int partitionRandom(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[randomIndex]);
    return partitionFirst(arr, low, high);
}

// Partition using the median of first, middle, and last as pivot
int partitionMedian(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int a = arr[low], b = arr[mid], c = arr[high];
    int medianIndex = (a < b ? (b < c ? mid : (a < c ? high : low)) : (a < c ? low : (b < c ? high : mid)));
    swap(arr[low], arr[medianIndex]);
    return partitionFirst(arr, low, high);
}

// QuickSort function
void quickSort(vector<int>& arr, int low, int high, int pivotType) {
    if (low < high) {
        int pivotIndex;
        if (pivotType == 1) pivotIndex = partitionFirst(arr, low, high);
        else if (pivotType == 2) pivotIndex = partitionMiddle(arr, low, high);
        else if (pivotType == 3) pivotIndex = partitionRandom(arr, low, high);
        else pivotIndex = partitionMedian(arr, low, high);

        quickSort(arr, low, pivotIndex - 1, pivotType);
        quickSort(arr, pivotIndex + 1, high, pivotType);
    }
}

// Generate data for testing
void generateData(vector<int>& data, int size, int type) {
    data.clear();
    if (type == 0) { // Random data
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, size);
        for (int i = 0; i < size; i++) data.push_back(dis(gen));
    }
    else if (type == 1) { // Sorted data
        for (int i = 1; i <= size; i++) data.push_back(i);
    }
    else { // Reverse sorted data
        for (int i = size; i > 0; i--) data.push_back(i);
    }
}

int main() {
    vector<int> data;
    int sizes[] = { 10000, 20000, 30000, 40000, 50000 };
    string dataTypes[] = { "Random", "Sorted", "Reverse Sorted" };
    int pivotTypes[] = { 1, 2, 3, 4 };
    string pivotTypeNames[] = {
        "First element as pivot",
        "Middle element as pivot",
        "Random element as pivot",
        "Median of first, middle, and last as pivot"
    };

    for (int pivotType : pivotTypes) {
        cout << "\n--- " << pivotTypeNames[pivotType - 1] << " ---\n";
        for (int dataType = 0; dataType < 3; ++dataType) {
            cout << dataTypes[dataType] << " Data:\n";
            for (int size : sizes) {
                generateData(data, size, dataType);

                auto start = chrono::high_resolution_clock::now();
                quickSort(data, 0, data.size() - 1, pivotType);
                auto end = chrono::high_resolution_clock::now();

                chrono::duration<double> elapsed = end - start;
                cout << "Size: " << size << ", Time: " << elapsed.count() << " seconds\n";
            }
        }
    }

    return 0;
}
