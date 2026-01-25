#include <stdio.h>
#include <stdlib.h>
#include "tris.h"

    int *binarySearch(int *array, int arrayLength, int value){
        int *index = &value;
        int i = 0;

        for(i = 0; i < arrayLength; i++){
            if (*(array + i) == *index){
                printf("Value found at @%p \n",index);
                return index;
            } 
        }
        printf("We have not found this value into array \n");
        return array;
    }

    int *dichotomicSearch(int *array, int arrayLength, int value){
        int midle = ( arrayLength / 2);
        int *rightPart = NULL;

        if(*(array + midle) == value){
            return (array + midle);
        }else if(value < *(array + midle)){
            return dichotomicSearch(array, (midle - 1), value);
        }else if (value < *(array + midle)){
            rightPart = (array + midle + 1);
            return dichotomicSearch(rightPart, (arrayLength - midle) ,value); 
        }else{
            printf("Value not found !");
            return NULL;
        }
    }   

    int *arrayMin(int *array, int arrayLength){
        int i = 0;
        int *min = array;
        
        for ( i = 0; i < arrayLength; i++){
            if (*(array + i) < *min){
                min = (array + i);
            } 
        }
        return min;
    }

    int *arrayMax(int *array, int arrayLength){
        int i = 0;
        int *max = array;
        
        for ( i = 0; i < arrayLength; i++){
            if (*(array + i) > *max){
                max = (array + i);
            } 
        }
        return max;
    }
    
    void swapValue(int *firstNum, int *secondNum){
        int temp = *firstNum;

        *firstNum = *secondNum;
        *secondNum = temp;
    }

    int pwr(int n,int p){
        int i;

        if(p < 0){
            return-1;
        }else if (p == 0){
            return 1;
        }

        return n * pwr(n, p - 1);
    }

    void divide(int a, int b, int * q, int* r){
        *r = a % b;
        *q = a/b;
    }

    void bubbleSort(int *array, int arrayLength){
        int i = 0;
        int j = 0;
        for(i = 0; i < arrayLength; i++){
            for(j = 0; j < arrayLength - i; j++){
                if( *(array + j) > *(array + j + 1)){
                  swapValue((array + j), (array + j + 1));  
                }  
           }
            
        }
        printf("After sorting \n");
    }

    void selectionSort(int *array, int arrayLength){
    int i = 0;
    int *min = NULL;

        for(i = 0; i < arrayLength; i++){           
            *min = arrayMin((array + i), (arrayLength - i));
            printf(" \n min : %d", *min);
            swapValue(min, (array + i));         
        }
        printf("\n After sorting \n");        
    }

    void insertionSort(int *array, int arrayLength){
    int i = 0;
    int j = 0;
    
        for(i = 1; i < arrayLength; i++){
            j = i; 
                     
            while ( j > 0 && *(array + j) < *(array + j - 1) ){
                swapValue((array + j), (array + j - 1)); 
                j--;
            }        
        }
        printf("\n After sorting \n");        
    }

    void fillArray(int *array, int arrayLength){
        int i = 0;
        for ( i = 0; i < arrayLength; i++){
            printf("\nEnter the value at index %d : ", i);
            scanf("%d", (array + i));
        }
       printArray(array, arrayLength);
    }

    void printArray(int *array, int arrayLength){
        int i = 0;
        for (i = 0; i < arrayLength; i++){
            printf("Value at index %d :  %d\n", i,  *(array + i));
        }  
    }