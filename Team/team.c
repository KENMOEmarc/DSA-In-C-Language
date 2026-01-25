#include <stdio.h>
#include <string.h>
#include "team.h"

	void initPlayer(Player *player){
		
		char tname[20];
		char tsurname[20];
		short tyears;
		short tscore;
		
		printf("Enter the player's name :\n");
		scanf("%s", tname);
		
		strcpy(player->name, tname);
		
		printf("Enter the player's surname :\n");
		scanf("%s", tsurname);
		
		strcpy(player->surname, tsurname);
		
		printf("How many years old ? :\n");
		scanf("%d",&tyears);
		
		player->years = tyears;

		do{
			printf("Enter his score :\n");
			scanf("%d", &tscore);
		}while((tscore <= 0 || tscore > 100));
	
		player->score = tscore;
	}