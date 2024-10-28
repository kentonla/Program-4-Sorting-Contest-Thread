// Name: Kenton La
// CECS 325-01
// Prog 4 - Sorting Contest (thread)
// Oct 30, 2024

// I certify that this program is my own original work. I did not copy any part of this program from any other source.
// I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <thread>
#include <mutex> 
#include <fstream>
using namespace std;
mutex mtx;
long long swapCount = 0;  //global variable keeps track of all the swaps

void bubble(int A[], int size, int threadNum)
{
  mtx.lock();
  int localSwapCount = 0;
  for (int i = 1; i < size; i++) {
    for (int j = 0; j < size-1; j++) {
      if (A[j] > A[j+1]) {
        int temp = A[j];
        A[j] = A[j+1];
        A[j+1] = temp;
        localSwapCount++;
      }
    }
  }
  cout << "Process " << threadNum << " swap count: " << localSwapCount << "\n";
  swapCount += localSwapCount;
  mtx.unlock();
}

void merge(int a1[], int s1, int a2[], int s2) {
    // Create a temporary array to hold the merged result
    int temp[s1 + s2];

    int i = 0; // Index for the first array
    int j = 0; // Index for the second array
    int k = 0; // Index for the temporary array

    // Loop to merge both arrays
    while (i < s1 && j < s2) {
        if (a1[i] <= a2[j]) {
            temp[k++] = a1[i++]; // Copy from a1 if it's smaller or equal
        } else {
            temp[k++] = a2[j++]; // Copy from a2 if it's smaller
        }
    }

    // Copy remaining elements from a1, if any
    while (i < s1) {
        temp[k++] = a1[i++];
    }

    // Copy remaining elements from a2, if any
    while (j < s2) {
        temp[k++] = a2[j++];
    }

    // Copy all merged elements back to nums (or can also return temp if needed)
    for (int index = 0; index < s1 + s2; index++) {
        if (index < s1) {
            a1[index] = temp[index]; // If a1 size is sufficient
        } else {
            a2[index - s1] = temp[index]; // Place remaining elements in a2
        }
    }
}

int main(int argc, char* argv[]){
    if (argc != 3 && argc != 4){
        cout << "Please enter 2 or 3 parameters:\n";
        cout << "   Parameter 1: input file\n";
        cout << "   Parameter 2: output file\n";
        cout << "   Parameter 3 (optional): -test\n";
        cout << "Example: ./mysort numbers.dat mysort.out -test\n";
        exit(EXIT_SUCCESS);
    }


    ifstream fin;
    int count = 0;
    fin.open(argv[1]);
    ofstream fout(argv[2]);
    int size = 0;
    int array_size = 1000000;
    if (argc == 4){array_size = 10000;}
    const int threadCount = 16;
    string num;



    //creates and populates numbers array
    int* numbers = new int[array_size];
    while (getline(fin, num, '\n')){
      if (size < array_size){
        numbers[size++] = stoi(num);
      }
    }
    int* sections[threadCount];
    for (int i = 0; i < threadCount; i++){
      sections[i] = &numbers[i * (array_size/threadCount)];
    }


    //creating pointers
    int *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11, *ptr12, *ptr13, *ptr14, *ptr15, *ptr16;
    ptr1 = numbers;
    ptr2 = &numbers[size / 16];
    ptr3 = &numbers[(size / 16) * 2];
    ptr4 = &numbers[(size / 16) * 3]; 
    ptr5 = &numbers[(size / 16) * 4];
    ptr6 = &numbers[(size / 16) * 5];
    ptr7 = &numbers[(size / 16) * 6]; 
    ptr8 = &numbers[(size / 16) * 7]; 
    ptr9 = &numbers[(size / 16) * 8]; 
    ptr10 = &numbers[(size / 16) * 9];
    ptr11 = &numbers[(size / 16) * 10];
    ptr12 = &numbers[(size / 16) * 11];
    ptr13 = &numbers[(size / 16) * 12];
    ptr14 = &numbers[(size / 16) * 13];
    ptr15 = &numbers[(size / 16) * 14];
    ptr16 = &numbers[(size / 16) * 15];
    int ptr_size = size / 16;



    if (argc == 3){
      cout << "Starting Array bubble sort with 1000000 items\n";
    }
    else{
      cout << "Starting Array bubble sort with 10000 items\n";
    }

    // Creating threads and running bubble sort
    thread threads[threadCount];
    threads[0] = thread(bubble, ptr1, ptr_size, 1);
    threads[1] = thread(bubble, ptr2, ptr_size, 2);
    threads[2] = thread(bubble, ptr3, ptr_size, 3);
    threads[3] = thread(bubble, ptr4, ptr_size, 4);
    threads[4] = thread(bubble, ptr5, ptr_size, 5);
    threads[5] = thread(bubble, ptr6, ptr_size, 6);
    threads[6] = thread(bubble, ptr7, ptr_size, 7);
    threads[7] = thread(bubble, ptr8, ptr_size, 8);
    threads[8] = thread(bubble, ptr9, ptr_size, 9);
    threads[9] = thread(bubble, ptr10, ptr_size, 10);
    threads[10] = thread(bubble, ptr11, ptr_size, 11);
    threads[11] = thread(bubble, ptr12, ptr_size, 12);
    threads[12] = thread(bubble, ptr13, ptr_size, 13);
    threads[13] = thread(bubble, ptr14, ptr_size, 14);
    threads[14] = thread(bubble, ptr15, ptr_size, 15);
    threads[15] = thread(bubble, ptr16, ptr_size, 16);
    //Joining threads
    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }
    // merge(ptr1, ptr_size, ptr2, ptr_size);
    // merge(ptr3, ptr_size, ptr4, ptr_size);
    // merge(ptr5, ptr_size, ptr6, ptr_size);
    // merge(ptr7, ptr_size, ptr8, ptr_size);
    // merge(ptr1, ptr_size * 2, ptr3, ptr_size * 2);
    // merge(ptr5, ptr_size * 2, ptr7, ptr_size * 2);
    // merge(ptr1, ptr_size * 4, ptr5, ptr_size * 4);
    cout << "Total Swaps: " << swapCount << "\n";
    cout << "Ending bubble sort\n";



    for (int i = 0; i < size; i++){
      fout << numbers[i] << '\n';
    }
    fout.close();
    fin.close();
    cout << size << " numbers sorted and transferred from " << argv[1] << " to " << argv[2] << endl;
    return 0;
}