#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int main(){

    Player UrusNoire = {
		"KENMOE",
		"Vajra",
		100,
		47
	};
	
	Player UrusJaune = {
		"FOMETIO",
		"Equalizer",
		100,
		66
	};

	Player UrusNeon = {
		"MBA",
		"ghost",
		100,
		87
	};

	print_queue();
    enQueue(&UrusJaune);
    enQueue(&UrusNoire);
	enQueue(&UrusNeon);

	printf("Before dequeue :\n");
	print_queue();
	deQueue();
	printf("After dequeue :\n");
	print_queue();
	printf("Queue lentgh: %d \n", queue_length);
	clear_queue();

	List myList = new_list();

	print_list(myList);
	myList = add_first(myList, &UrusNoire);
	myList = add_last(myList, &UrusNeon);
	myList = add_first(myList, &UrusJaune);

	print_list(myList);
	myList = remove_first(myList);
	print_list(myList);
	myList = remove_last(myList);
	print_list(myList);
	clear_list(myList);

	return 0;
}