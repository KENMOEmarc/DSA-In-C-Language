#ifndef __TRIS_H_
#define __TRIS_H_

int *binarySearch(int *array, int arrayLength, int value);
int *dichotomicSearch(int *array, int arrayLength, int value);
int *arrayMin(int * array, int arraylength);
int *arrayMax(int * array, int arrayLength);

void swapValue(int *firstNum, int *secondNum);
int pwr(int n,int p);
void divide(int a, int b, int * q, int* r);

void bubbleSort(int *array, int arrayLength);
void selectionSort(int *array, int arrayLength);
void insertionSort(int *array, int arrayLength);

void quickSort(int *array, int arrayLength);
void mergeSort(int *array, int arrayLength);

void printArray(int *array, int arrayLength);
void fillArray(int *array, int arrayLength);

#endif