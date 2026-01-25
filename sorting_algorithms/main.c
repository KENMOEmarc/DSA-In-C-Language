#include <stdio.h>
#include <stdlib.h>
#include "tris.h"

int main(){

    int arrayLength;
    int *array = NULL;
    int *value = NULL;

    printf("Enter array's length : \n");
    scanf("%d", &arrayLength);

    array = malloc(arrayLength * (sizeof(int)));
    fillArray(array, arrayLength);
    value = (arrayMin(array, arrayLength));
    
    printf(" Min value founded into array : %d", *value);

    free(array);
    return 0;
}
