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
#include <bits/stdc++.h>
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

// in the merge arguments add one more for a third array
void merge(int a1[], int s1, int a2[], int s2, int a3[]) {
  int i = 0, j = 0, k = 0;

  // Traverse arr1 and insert its elements into arr3
  while (i < s1) {
      a3[k++] = a1[i++];
  }

  // Traverse arr2 and insert its elements into arr3
  while (j < s2) {
      a3[k++] = a2[j++];
  }

  // Sort the entire arr3
  sort(a3, a3 + s1 + s2);
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
    int section_size = size / 16;
    int* a1 = new int[section_size * 2];
    int* a2 = new int[section_size * 2];
    int* a3 = new int[section_size * 2];
    int* a4 = new int[section_size * 2];
    int* a5 = new int[section_size * 2];
    int* a6 = new int[section_size * 2];
    int* a7 = new int[section_size * 2];
    int* a8 = new int[section_size * 2];

    merge(ptr1, ptr_size, ptr2, ptr_size, a1);
    merge(ptr3, ptr_size, ptr4, ptr_size, a2);
    merge(ptr5, ptr_size, ptr6, ptr_size, a3);
    merge(ptr7, ptr_size, ptr8, ptr_size, a4);
    merge(ptr9, ptr_size, ptr10, ptr_size, a5);
    merge(ptr11, ptr_size, ptr12, ptr_size, a6);
    merge(ptr13, ptr_size, ptr14, ptr_size, a7);
    merge(ptr15, ptr_size, ptr16, ptr_size, a8);

    int* a9 = new int[section_size * 4];
    int* a10 = new int[section_size * 4];
    int* a11 = new int[section_size * 4];
    int* a12 = new int[section_size * 4];

    merge(a1, section_size * 2, a2, section_size * 2, a9);
    merge(a3, section_size * 2, a4, section_size * 2, a10);
    merge(a5, section_size * 2, a6, section_size * 2, a11);
    merge(a7, section_size * 2, a8, section_size * 2, a12);

    int* a13 = new int[section_size * 8];
    int* a14 = new int[section_size * 8];
    merge(a9, section_size * 4, a10, section_size * 4, a13);
    merge(a11, section_size * 4, a12, section_size * 4, a14);

    int* finalArray = new int[size];
    merge(a13, section_size * 8, a14, section_size * 8, finalArray);
    cout << "Total Swaps: " << swapCount << "\n";
    cout << "Ending bubble sort\n";



    for (int i = 0; i < size; i++){
      fout << finalArray[i] << '\n';
    }


    delete[] numbers;
    delete[] a1; delete[] a2; delete[] a3; delete[] a4;
    delete[] a5; delete[] a6; delete[] a7; delete[] a8;
    delete[] a9; delete[] a10; delete[] a11; delete[] a12;
    delete[] a13; delete[] a14; delete[] finalArray;


    fout.close();
    fin.close();
    cout << size << " numbers sorted and transferred from " << argv[1] << " to " << argv[2] << endl;
    return 0;
}