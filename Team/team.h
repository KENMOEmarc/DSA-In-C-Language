#ifndef __TEAM_H_
#define __TEAM_H_
	
	typedef enum{
		false,
		true
	}Boolean;

	typedef struct Player {
	
		char name[15];
		char surname[15];
		short years;
		short score; 
	}Player;
	
	typedef struct Team {
		char name[20];
		Player player1;
		Player player2;
	}Team;
	
	void initPlayer(Player *player);

#endif