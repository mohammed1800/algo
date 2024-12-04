#include <iostream> 
#include <cstdlib> 
#include <ctime> 

using namespace std; 

int randomizedQuickSort(int arr[], int low, int high, int& comparisons); 

 

int partition(int arr[], int low, int high, int& comparisons); 

 

int randomPivot(int arr[], int low, int high); 

 

void printArray(int arr[], int size); 

 

int main() { 

    

    srand(time(0)); 

 

    int arr[] = {10, 7, 8, 9, 1, 5}; 

    int size = sizeof(arr) / sizeof(arr[0]); 

    int comparisons = 0; 

 

    cout << "Original array: "; 

    printArray(arr, size); 

 

    

    randomizedQuickSort(arr, 0, size - 1, comparisons); 

 

    cout << "Sorted array: "; 

    printArray(arr, size); 

     

    cout << "Number of comparisons: " << comparisons << endl; 

 

    return 0; 

} 

 

int randomizedQuickSort(int arr[], int low, int high, int& comparisons) { 

    if (low < high) { 

        int pivotIndex = partition(arr, low, high, comparisons); 

        randomizedQuickSort(arr, low, pivotIndex - 1, comparisons); 

        randomizedQuickSort(arr, pivotIndex + 1, high, comparisons); 

    } 

    return comparisons; 

} 

int partition(int arr[], int low, int high, int& comparisons) { 

    int pivotIndex = randomPivot(arr, low, high); 

    int pivot = arr[pivotIndex]; 

    swap(arr[pivotIndex], arr[high]); 

 

    int i = low - 1; 

    for (int j = low; j < high; j++) { 

        comparisons++; 

        if (arr[j] <= pivot) { 

            i++; 

            swap(arr[i], arr[j]); 

        } 

    } 

    swap(arr[i + 1], arr[high]); 

    return i + 1; 

} 

int randomPivot(int arr[], int low, int high) { 

    int pivotIndex = low + rand() % (high - low + 1); 

    return pivotIndex; 

} 

void printArray(int arr[], int size) { 

    for (int i = 0; i < size; i++) { 

        cout << arr[i] << " "; 

    } 

    cout << endl; 