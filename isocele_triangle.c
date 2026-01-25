//Triangle isocele.
#include<stdio.h>
int main (void){
	
	int a, i, j, height;
	
	printf("Enter the height of the triangle :");
	scanf("%d",&height);
	
	if(height < 0){
		height = -1 * height;
	}

	for(i = 1; i <= height; i++){
		a = i;

		while(a <= height - 1){
			printf(" ");		
			a++;
		}

		for(j = 1; j <= height; j++){
			if(j > i){
				printf("");
			}
			else{	
				printf("* ");
			}
		}

		printf("\n");
		}	
	return 0;
}
