#include <stdio.h>
#include <string.h>
#include "team.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	Player UrusNoire = {
		"KENMOE",
		"Marc",
		100,
		47
	};
		
	printf("Before updating \n");
	
	printf("%s  ", UrusNoire.name);
	printf("%s  ", UrusNoire.surname);
	
	initPlayer(&UrusNoire);
	
	printf("After Udating \n");
	
	printf("%s  ", UrusNoire.name);
	printf("%s  ", UrusNoire.surname);
	
	return 0;
}