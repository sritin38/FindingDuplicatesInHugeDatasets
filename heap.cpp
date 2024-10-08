#include <vector>
#include <iostream>

using namespace std;

class MaxHeap {
    private:
        vector<int> array;
        int size;
        int capacity;

    public:
        // Constructor
        MaxHeap(int capacity) {
            this->size = 0;
            this->capacity = capacity;
            this->array.resize(capacity);
        }

        // Heapify function, heapify the node at index 'i'
        void heapify(int i) {

            // initialize initial values
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            // Compare root node with left node of subtree
            if (left < size && array[left] > array[largest]) {
                largest = left;
            }
            // Compare root node with right node of subtree
            if (right < size && array[right] > array[largest]) {
                largest = right;
            }
            // If root node is changed then swap the values and call heapify function on subtree
            if (i != largest) {
                swap(array[i], array[largest]);
                heapify(largest);
            }
        }

        // Build heap function
        void buildHeap(const vector<int>& arr) {

            capacity = arr.size();
            size = capacity;
            array = arr;

            for (int i= (size-1)/2; i>=0; i--) {
                heapify(i);
            }
        }

        // Insert new values into the heap
        void insert(int value) {

            // increase array capacity
            if (size == capacity) {
                capacity *= 2;
                array.resize(capacity);
            }

            size++;
            int i = size-1;
            array[i] = value;

            // Adjust the value in the heap
            while (i != 0 && array[(i-1)/2] < array[i]) {

                swap(array[i], array[(i - 1) / 2]);
                i = (i-1)/2;
            }
        }

        // Function to get the root node
        int top() {

            if (size < 0) {
                return -1;
            }
            else {
                return array[0];
            }
        }

        // Remove and return the root-node/max-value of the heap
        int pop() {
            
            // If the heap is empty
            if (size < 0) {
                return -1;
            }

            // If the heap is of size 1
            if (size == 1) {
                size--;
                return array[0];
            }

            // Store the max value and remove it
            // Place the last value in the heap to the root
            int max = array[0];
            array[0] = array[size-1];
            size--;
            
            // Call heapify function to adjust the structure
            heapify(0);
            return max;
        }

        // Delete a specific key from heap
        void deleteKey(int key) {

            int index = -1;
            for (int i=0; i<size; i++) {
                
                if (array[i] == key) {
                    index = i;
                    break;
                }
            }

            if (index == size-1) {

                cout << "Key not found" << endl;
                return;
            }

            if (index == size-1) {
                
                size--;
                return;
            }

            array[index] = array[size-1];
            size--;

            heapify(index);
        }

        // Function to print the heap
        void print() const {
            cout << "Max Heap: ";
            for (int i = 0; i < size; ++i)
                cout << array[i] << " ";
            cout << endl;
        }
};

int main() {
    // Create a MaxHeap with initial capacity of 6
    MaxHeap maxHeap(6);
    vector<int> arr = {2, 3, 4, 5, 10, 15};

    // Build the heap from the array
    maxHeap.buildHeap(arr);

    // Print the max heap
    maxHeap.print();

    // Insert a node into the heap
    maxHeap.insert(9);
    cout << "After inserting 9: " << endl;
    maxHeap.print();

    // Get the maximum value from the max heap
    cout << "Top value: " << maxHeap.top() << endl;

    // Delete the root node of the max heap
    cout << "Popped value: " << maxHeap.pop() << endl;
    cout << "After popping: ";
    maxHeap.print();

    // Delete a specific value from the max heap
    maxHeap.deleteKey(5);
    cout << "After deleting the node 5: ";
    maxHeap.print();

    return 0;
}