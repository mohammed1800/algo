#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to perform the partition around a pivot element
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Choose the pivot as the last element
    int i = low - 1;  // Pointer for the smaller element

    // Rearrange the array so that elements smaller than pivot are on the left
    // and elements greater than pivot are on the right
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);  // Place the pivot in its correct position
    return i + 1;  // Return the pivot index
}

// Function to randomly select a pivot and partition the array
int randomized_partition(int arr[], int low, int high) {
    // Generate a random index and swap it with the high index
    int random_index = low + rand() % (high - low + 1);
    swap(arr[random_index], arr[high]);
    return partition(arr, low, high);
}

// Randomized Select function to find the ith smallest element
int randomized_select(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low];  // Base case: only one element
    }

    int pivot_index = randomized_partition(arr, low, high);  // Partition the array
    int k = pivot_index - low + 1;  // The rank of the pivot element

    if (i == k) {
        return arr[pivot_index];  // The pivot is the ith smallest element
    } else if (i < k) {
        return randomized_select(arr, low, pivot_index - 1, i);  // Search in the left partition
    } else {
        return randomized_select(arr, pivot_index + 1, high, i - k);  // Search in the right partition
    }
}

int main() {
    srand(time(0));  // Seed for random number generation

    // Input array
    int arr[] = {12, 3, 5, 7, 19, 2, 11, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // The index of the element to find (1-based index)
    int i;
    cout << "Enter the value of i (1-based index for the ith smallest element): ";
    cin >> i;

    // Find the ith smallest element
    if (i > 0 && i <= n) {
        int result = randomized_select(arr, 0, n - 1, i);
        cout << "The " << i << "th smallest element is: " << result << endl;
    } else {
        cout << "Invalid input! Please enter an index between 1 and " << n << "." << endl;
    }

    return 0;
}
