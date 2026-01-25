#include<stdio.h>
int main (){
	int i, j, c;
	
	printf("Enter any number :");
	scanf("%d", &c);
	
	for(i = 1; i <= c; i++){
		
		for(j = 1; j <= c; j++){
			if(i == 1 || j == c || i == c || j == 1){
				printf("* ");	
			}else{
				printf("  ");
			}
		}
		printf("\n");

	}	
	return 0;
}
