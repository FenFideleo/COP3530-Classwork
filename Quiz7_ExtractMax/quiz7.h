/*  COP3530
    Student: Erik Meurrens

    Quiz 7: Heaps (Extract Max)

*/
/*
    Quiz 7: Extract Max

    Write C++ code for a function, extractMax() that takes as input 
    a max heap, arr represented as an integer array and the size of 
    the array, size. The function deletes the maximum element in the 
    max heap and returns the new max heap array after deletion.

    Sample Input:
        3
	    9 8 7
    
    Sample Output:
        8 7
		
	Explanation:

	Input:  Line 1 denotes the number of elements, size in the 
            heap. Line 2 denotes the contents of the max heap 
            that is passed into extractMax() function.
	
	Output: Output is the max heap after deletion.
*/

#include <iostream>

int* extractMax(int arr[], int size)
{
    // root = i
    // left = i * 2 + 1
    // right = i * 2 + 2

    // replace root element with last element and decrement size
    arr[0] = arr[--size];
    
    // heapify root node 
    int i = 0;
    bool heapCorrect = false;

    while (!heapCorrect && (i * 2 + 1) < size) {
        int& root = arr[i];
        int& left = arr[i * 2 + 1];
        int& right = arr[i * 2 + 2];

        // If root is less than left and left is accessible, heapify
        if (root < left && (i * 2 + 1) < size) {
            int temp = root;
            // Check to see if right is greater than left, if so swap with right
            if (right > left) {
                root = right;
                right = temp;
                i = i * 2 + 2;
            }
            // Else swap with left
            else {
                root = left;
                left = temp;
                i = i * 2 + 1;
            }
        }
        // Else if root is less than right and right is accessible, swap with right
        else if (root < right && (i * 2 + 2) < size) {
            int temp = root;
            root = right;
            right = temp;
            i = i * 2 + 2;
        }
        // Else root is lesser than both children, or both children inaccessible, heap is correct
        else {
            heapCorrect = true;
        }
    }

	return arr; 
}
