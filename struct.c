#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

//-------------------------------------------------PLayer---------------------------------------//

void attack(Player *player){
		
	if(player->hp <= 0)
		printf("Game over %s lose!",player->name);
	player->hp -= 10;	
}

void updateName(Player *player,char newName[15]){
	strcpy(player -> name, newName);
}

//-------------------------------------------------Stack-----------------------------------------//

Stack new_stack(void){
		return NULL;
	}
	
	Boolean is_empty_stack(Stack stack){
		if(stack == NULL)
			return true; 
		return false;
	}
	
	Stack push_stack(Stack stack, Player new_player){
		StackElement *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique . \n'");
			exit(EXIT_FAILURE);
		}
		
		element -> player = new_player;
		element -> next = stack;
		
		return  element;
	}
	
	Stack pop_stack(Stack stack){
		
		Stack *element = NULL;
		
		if(is_empty_stack(stack) == true)
			return new_stack();
		
		element = stack -> next;
		free(stack);
		
		return element;  
	}
	
	Stack clear_stack(Stack stack){
		return clear_stack(pop_stack(stack));
	}
	
	void print_stack(Stack stack){
		if(is_empty_stack(stack) == true){
			printf("\n Nothing to print \n");
			return;
		}
		
		while(! (is_empty_stack(stack) == true) ){
			if (stack -> player.pseudo != NULL){
				break;
			}
			
			printf("\n|%d|\n", stack -> player.id);
			printf("|%s|\n", stack -> player.name);
			printf("|%s|\n", stack -> player.pseudo);
			printf("|%d|\n", stack -> player.hp);
			stack = stack -> next; 
		}
	}

	Boolean contains(Stack stack, char pseudo[]){
		if(is_empty_stack(stack) == true){
			printf("\n Empty stack ! \n");
			return false;
		}
		
		while((is_empty_stack(stack) == false)){
			if (stack -> player.pseudo == pseudo){
				return true;
			}
			stack = stack -> next; 
		}
		return false;
	}

    //--------------------------------------------Queue--------------------------------------------//

    static int queue_length;
	
	Boolean is_empty_queue(){
		if (last == NULL && first == NULL)
			return true;
		return false;
	}
	
	void enQueue(Player *new_player){
		QueueElement *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}
		
		element -> player.id = new_player -> id;
		element -> player.hp = new_player -> hp;
		strcpy(element -> player.name, new_player -> name);
		strcpy(element -> player.pseudo, new_player -> pseudo);
		//element->player = *new_player;
    	element -> next = NULL;

		if (is_empty_queue() == true){
			first = element;
		}else{
			last -> next = element;
		}

		last = element;
		queue_length++;
	}  
	
	void deQueue(){
		
		if(is_empty_queue() == true){
			printf("Queue is already empty ! \n ");
			return ;
		}
		
		if (first == last){
			first = NULL;
			last = NULL;
			return;
		}

		QueueElement *temp = first;
		
		first = first -> next;
		free(temp);
		queue_length--;
	}
	
	void clear_queue(){
        while (!(is_empty_queue() == true) )
          deQueue();      
	}
	
	void print_queue(){
		if(is_empty_queue() == true){
			printf("\n There is Nothing to print ! \n");
			return;
		}
		
		QueueElement* current = first;
    	while (current != NULL) {
			printf("Player ID: %d, Name: %s, Pseudo: %s, HP: %d |\n", current -> player.id, current -> player.name, current -> player.pseudo, current -> player.hp);
			current = current -> next;
    	}
	}

	Boolean find_player(char pseudo[]){
		if(is_empty_queue() == true){
			printf("\n Empty queue ! \n");
			return false;
		}
		
		while((is_empty_queue() == false)){
			if (first -> player.pseudo == pseudo){
				return true;
			}
			first = first -> next; 
		}
		return false;
	}

	//------------------------------------------------List----------------------------------------//
	
	List new_list(){
		return NULL;	
	}

	Boolean is_empty_list(List list){
		if (list == NULL)
			return true;
		return false;
	}

	int list_size(List list){
		int size = 0;
		if(!is_empty_list(list)){
			while (list != NULL){
				++size;
				list = list -> next;
			}
		}
		return size;
	}

	void print_list(List list){
		if(is_empty_list(list) == true){
			printf("\n There is Nothing to print ! \n");
			return;
		}
		
    	while (list != NULL) {
			printf("Player ID: %d, Name: %s, Pseudo: %s, HP: %d |\n", list -> player.id, list -> player.name, list -> player.pseudo, list -> player.hp);
			list = list -> next;
    	}
	}

	Boolean searchPlayer(List list, char pseudo[]){
		if(is_empty_list(list) == true){
			printf("\n Empty list ! \n");
			return false;
		}
		
		while((is_empty_list(list) == false)){
			if (list -> player.pseudo == pseudo){
				return true;
			}
			list = list -> next; 
		}
		return false;
	}

	List add_last(List list, Player *new_player){ 
		PlayerList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (searchPlayer(list, new_player -> pseudo) == true){
			printf("This element already exist in the List!\n ");
			return list;	
		}
		
		element -> player.id = new_player -> id;
		element -> player.hp = new_player -> hp;
		strcpy(element -> player.name, new_player -> name);
		strcpy(element -> player.pseudo, new_player -> pseudo);
		//element->player = *new_player;
    	element -> next = NULL;
		
		if (is_empty_list(list) == true)
			return element;

		PlayerList *temp = list;
		while (temp -> next != NULL){
			temp  = temp -> next;
		}

		temp -> next = element; 
		return list;
	}

	List add_first(List list, Player *new_player){
		PlayerList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (searchPlayer(list, new_player -> pseudo) == true){
			printf("This element already exist in the List!\n ");
			return list;	
		}
		
		element -> player.id = new_player -> id;
		element -> player.hp = new_player -> hp;
		strcpy(element -> player.name, new_player -> name);
		strcpy(element -> player.pseudo, new_player -> pseudo);
		//element->player = *new_player;
		
		if (is_empty_list(list) == true)
			element -> next = NULL;
		
		element -> next = list;
		return element;
	}

	List remove_last(List list){
		if (is_empty_list(list) == true)
			return new_list();

		if (list -> next == NULL){
			free(list);
			return new_list();
		}
		
		PlayerList *nodes = list;
		PlayerList *temp = list;
		 
		while (temp -> next != NULL){
			nodes = temp;
			temp = temp -> next;
		}
		nodes -> next = NULL;
		free(temp);

		return list;
	}

	List remove_first(List list){

		if (is_empty_list(list) == true)
			return new_list;

		PlayerList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}
		element = list -> next;
		free(list);
		return element;
	}

	void clear_list(List list){
		while (list != NULL)
			list = remove_first(list);
	}

	//--------------------------------------------LinkedList---------------------------------------//

	Boolean is_empty_linkedList(LinkedList linkedList){
		if (linkedList == NULL)
			return true;
		return false;
	}

	LinkedList new_linkedList(){
		return NULL;
	}

	int linkedList_size(LinkedList linkedList){
		if (is_empty_linkedList(linkedList) == true)
			return 0;
		return linkedList -> length;
		
	}

	void printLinkedList(LinkedList linkedList){
		if (is_empty_linkedList(linkedList)){
			printf("Nothing to print the list is empty ! \n");
			return new_linkedList();
		}

		NodeList *node = linkedList -> first;

		while (node != NULL){
			printf("Player ID: %d, Name: %s, Pseudo: %s, HP: %d |\n", node -> player.id, node -> player.name, node -> player.pseudo, node -> player.hp);
			node= node -> next;
		}	
		printf("\n");
	}

	Player getFirst(LinkedList linkedList){
		if (is_empty_linkedList(linkedList) == true)
			exit(1);

		return linkedList -> first -> player;
	}

	Player getFLast(LinkedList linkedList){
		if (is_empty_linkedList(linkedList) == true)
			exit(1);

		return linkedList -> last -> player;
	}

	Boolean containsPlayer(LinkedList linkedList, char pseudo[]){
		if (is_empty_linkedList(linkedList)){
			printf("The list is empty ! \n");
			return false;
		}

		NodeList *node = linkedList -> first;

		while (node != NULL){
			if (node -> player.pseudo == pseudo){
				return true;
			}
			
			node= node -> next;
		}	
		return false;
	}

	LinkedList addLast(LinkedList linkedList, Player *new_player){
		NodeList *node = NULL;
		node = malloc(sizeof(*node));
		
		if(node == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (containsPlayer(linkedList, new_player -> pseudo) == true){
			printf("This element already exist in the linkedList!\n ");
			return linkedList;	
		}
		
		node -> player.id = new_player -> id;
		node -> player.hp = new_player -> hp;
		strcpy(node -> player.name, new_player -> name);
		strcpy(node -> player.pseudo, new_player -> pseudo);
		//element->player = *new_player;

		node -> next = NULL;
		node -> previous = NULL;

		if (is_empty_linkedList(linkedList) == true){
			linkedList = malloc(sizeof(*linkedList));

			if (linkedList == NULL){
				fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			    exit(EXIT_FAILURE);
			}
			
			linkedList -> first = node;
			linkedList -> length = 0;
		}else{
			linkedList -> last -> next = node;
			node -> previous = linkedList -> last;
		}

		linkedList -> last = node;
		linkedList -> length++;
	}

	LinkedList addFirst(LinkedList linkedList, Player *new_player){
		NodeList *node = NULL;
		node = malloc(sizeof(*node));
		
		if(node == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (containsPlayer(linkedList, new_player -> pseudo) == true){
			printf("This element already exist in the linkedList!\n ");
			return linkedList;	
		}
		
		node -> player.id = new_player -> id;
		node -> player.hp = new_player -> hp;
		strcpy(node -> player.name, new_player -> name);
		strcpy(node -> player.pseudo, new_player -> pseudo);
		//element->player = *new_player;

		node -> next = NULL;
		node -> previous = NULL;

		if (is_empty_linkedList(linkedList) == true){
			linkedList = malloc(sizeof(*linkedList));

			if (linkedList == NULL){
				fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			    exit(EXIT_FAILURE);
			}
			
			linkedList -> first = node;
			linkedList -> length = 0;
		}else{

			linkedList -> first -> previous = node;
			node -> next = linkedList -> first;
			linkedList -> first = node;
		}
		
		linkedList -> last = node;
		linkedList -> length++;
	}

	LinkedList removeLast(LinkedList linkedList){
		if (is_empty_linkedList(linkedList)){
			printf("Nothing to remove the list is already empty ! \n");
			return new_linkedList();
		}
			
		if (linkedList -> first == linkedList -> last){
			free(linkedList);
			return new_linkedList();
		}
			
		NodeList *temp = linkedList -> last;

		linkedList -> last = linkedList -> last -> previous;
		linkedList -> last -> next = NULL;
		temp -> previous = NULL;
		temp -> next = NULL;
		free(temp);
		linkedList -> length--;

		return linkedList;
	}

	LinkedList removeFirst(LinkedList linkedList){
		if (is_empty_linkedList(linkedList)){
			printf("Nothing to remove the list is already empty ! \n");
			return new_linkedList();
		}
			
		if (linkedList -> first == linkedList -> last){
			free(linkedList);
			return new_linkedList();
		}
			 
		NodeList *temp = linkedList -> first;

		linkedList -> first = linkedList -> first -> next;
		linkedList -> first -> previous = NULL;
		temp -> previous = NULL;
		temp -> next = NULL;
		free(temp);
		linkedList -> length--;

		return linkedList; 
	}

	void clear_linkedList(LinkedList linkedList){
		 while (linkedList != NULL)
		 	removeFirst(linkedList);
	}