#include<stdio.h>
#include<stdlib.h>

int main(){
	int i, j, edge;
		
	printf("Enter any number :");
	scanf("%d",&edge);
	
	for (i=0; i<edge; i++){
		
		for (j=0; j<edge; j++){
			
			printf("* ");
			
		}
		
		printf("\n");
		
	}
		
	return 0;
}