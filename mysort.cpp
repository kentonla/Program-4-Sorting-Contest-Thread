// Name: Kenton La
// CECS 325-01
// Prog 3 - Sorting Contest
// Oct 14, 2024

// I certify that this program is my own original work. I did not copy any part of this program from any other source.
// I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
using namespace std;

void bubble(int A[], int size)
{
  for (int i = 1; i < size; i++) {
    for (int j = 0; j < size-1; j++) {
      if (A[j] > A[j+1]) {
        int temp = A[j];
        A[j] = A[j+1];
        A[j+1] = temp;
      }
    }
  }
}

int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Please enter 2 parameters:\n";
        cout << "   Parameter 1: input file\n";
        cout << "   Parameter 2: output file\n";
        cout << "Example: ./mysort numbers.dat mysort.out\n";
        exit(EXIT_SUCCESS);
    }
    ifstream fin;
    int n;
    int count = 0;
    fin.open(argv[1]);
    ofstream fout(argv[2]);
    int numbers[1000000];
    int size = 0;
    string num;
    while (getline(fin, num, '\n')){
      if (size < 1000000){
        numbers[size++] = stoi(num);
      }
    }
    
    cout << "Starting Array buble sort with 1000000 items\n";
    bubble(numbers, size);
    cout << "Ending bubble sort\n";

    for (int i = 0; i < size; i++){
      fout << numbers[i] << '\n';
    }

    fout.close();
    fin.close();

    cout << size << " numbers sorted and transferred from " << argv[1] << " to " << argv[2] << endl;
    return 0;
}