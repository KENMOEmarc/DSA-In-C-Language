    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "library.h"

	//-----------------------------------------------BOOK-----------------------------------------//

	void init(Book *book){
		char title[33];
		char autor[33];
        int ISBN;
        int year;

		printf("Enter book's title : ");
		scanf("%s", title);
		
		printf("Enter book's autor :");
		scanf("%s", autor);
		
		printf("Enter book's ISBN :");
		scanf("%d", &(ISBN));

		printf("Publication year :");
		scanf("%d", &(year));

        strcpy(book -> title, title);
        strcpy(book -> autor, autor);
        book -> ISBN = ISBN;
        book -> pubYear = year;
		book -> disponibility = True;
		
		book -> set_disponibility = set_disp;
		book -> info = book_info;
        book -> is_available = get_available;
	}
	
	void book_info(Book *book){
		printf("|| Title : %s , Autor : %s , ISBN : %d , Pub year : %d , Disponibility :", book -> title, book -> autor, book -> ISBN, book -> pubYear);
        if (book -> disponibility == True){
            printf("Available ! \n");
        }else{
            printf("Unavailable ! \n");  
        }   
	}
	
	void set_disp(Boolean boolean, Book *book){
		book -> disponibility = boolean;
	}

    void get_available(Book *book){
        printf("%s ", (book -> disponibility) ? "Available !\n" : "Unavaible !\n");
    }

    //--------------------------------------------SUBSCRIBER-------------------------------------------//

    void init_subscriber(Subscriber *subscriber){
        char name[33];
		char surname[33];
        int id;

		printf("Enter subscriber's name : ");
		scanf("%s", name);
		
		printf("Enter subscriber's surname :");
		scanf("%s", surname);
		
		printf("Enter subscriber's id :");
		scanf("%d", &id);

        strcpy(subscriber -> name, name);
        strcpy(subscriber -> surname, surname);
        subscriber -> id = id;
        subscriber -> history = new_stack();

		subscriber -> introduce_yourself = introduce;
		subscriber -> borrow_book = borrow;
		subscriber -> giveback_book = give_back;        
        
    }

	void introduce(Subscriber *subscriber){
        printf("Name : %s , Surname : %s , id : %d \n ", subscriber -> name, subscriber -> surname, subscriber -> id);
        printf("History of %s : \n", subscriber -> name);
        print_stack(subscriber -> history);
    }

	void borrow(Subscriber *subscriber, Book *book){
		if (book -> disponibility == True){
			book -> set_disponibility(False, book);
        	subscriber -> history = push_stack(subscriber -> history, book, withdrawal);
		}
		printf("This book is unavailable !\n");
    }

	void give_back(Subscriber *subscriber, Book *book){
		if (book -> disponibility == False){
			book -> set_disponibility(True, book);
        	subscriber -> history = push_stack(subscriber -> history, book, deposit);	
		}
		printf("This book is already present in the library !\n");
    }

    //----------------------------------------------STACK_HISTORY--------------------------------------//

    Stack new_stack(void){
		return NULL;
	}
	
	Boolean is_empty_stack(Stack stack){
		if(stack == NULL)
			return True; 
		return False;
	}
	
	Stack push_stack(Stack stack, Book *book, Transaction transaction){
		StackElement *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique . \n'");
			exit(EXIT_FAILURE);
		}
		
		element -> book = *book;
        element -> transaction = transaction;
		element -> next = stack;
		
		return  element;
	}
	
	Stack pop_stack(Stack stack){
		
		StackElement *element = NULL;
		
		if(is_empty_stack(stack) == True)
			return new_stack();
		
		element = stack -> next;
		free(stack);
		
		return element;  
	}
	
	Stack clear_stack(Stack stack){
		return clear_stack(pop_stack(stack));
	}
	
	void print_stack(Stack stack){
		if(is_empty_stack(stack) == True){
			printf("\n Nothing to print \n");
			return;
		}
		
		while(! (is_empty_stack(stack) == True) ){
			stack -> book.info(&stack -> book);
            printf("%s ", (stack -> transaction) ? "Deposit ||\n" : "Withdraw ||\n");
			stack = stack -> next; 
		}
	}

	Boolean contains( Stack stack, int ISBN){
		if(is_empty_stack(stack) == True){
			printf("\n Empty ! \n");
			return False;
		}
		
		while((is_empty_stack(stack) == False)){
			if (stack -> book.ISBN == ISBN){
				return True;
			}
			stack = stack -> next; 
		}
		return False;
	}

    //--------------------------------------------BOOKSList-------------------------------------------//

    BList new_list_b(){
		return NULL;	
	}

	Boolean is_empty_list_b(BList list){
		if (list == NULL)
			return True;
		return False;
	}

	int list_size_b(BList list){
		int size = 0;
		if(!is_empty_list_b(list)){
			while (list != NULL){
				++size;
				list = list -> next;
			}
		}
		return size;
	}

	void print_list_b(BList list){
		if(is_empty_list_b(list) == True){
			printf("\n Neither book, Empty list ! \n");
			return;
		}
		
    	while (list != NULL) {
			list -> book.info(&list -> book);
			list = list -> next;
    	}
	}

	Boolean searchBook_b(BList list, int ISBN){
		if(is_empty_list_b(list) == True){
			printf("\n Empty list ! \n");
			return False;
		}
		
		while((is_empty_list_b(list) == False)){
			if (list -> book.ISBN == ISBN){
				return True;
			}
			list = list -> next; 
		}
		return False;
	}

	BList add_last_b(BList list, Book *book){ 
		BookList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (searchBook_b(list, book -> ISBN) == True){
			printf("This element already exist in the SList!\n ");
			return list;	
		}
		
		element -> book = *book;
    	element -> next = NULL;
		
		if (is_empty_list_b(list) == True)
			return element;

		BookList *temp = list;
		while (temp -> next != NULL){
			temp  = temp -> next;
		}

		temp -> next = element; 
		return list;
	}

	BList add_first_b(BList list, Book *book){
		BookList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (searchBook_b(list, book -> ISBN) == True){
			printf("This element already exist in the list!\n ");
			return list;	
		}
		
		element -> book = *book;

		if (is_empty_list_b(list) == True)
			element -> next = NULL;
		
		element -> next = list;
		return element;
	}

	BList remove_last_b(BList list){
		if (is_empty_list_b(list) == True)
			return new_list_b();

		if (list -> next == NULL){
			free(list);
			return new_list_b();
		}
		
		BookList *nodes = list;
		BookList *temp = list;
		 
		while (temp -> next != NULL){
			nodes = temp;
			temp = temp -> next;
		}
		nodes -> next = NULL;
		free(temp);

		return list;
	}

	BList remove_first_b(BList list){

		if (is_empty_list_b(list) == True)
			return new_list_b();

		BookList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}
		element = list -> next;
		free(list);
		return element;
	}

	void clear_list_b(BList list){
		while (list != NULL)
			list = remove_first_b(list);
	}

    //--------------------------------------------SUBSList-------------------------------------------//

	SList new_subList(){
		return NULL;	
	}

	Boolean is_empty_list(SList list){
		if (list == NULL)
			return True;
		return False;
	}

	int list_size(SList list){
		int size = 0;
		if(!is_empty_list(list)){
			while (list != NULL){
				++size;
				list = list -> next;
			}
		}
		return size;
	}

	void print_list(SList list){
		if(is_empty_list(list) == True){
			printf("\n There is Nothing to print, Neither subscriber ! \n");
			return;
		}
		
    	while (list != NULL) {
			list -> subscriber.introduce_yourself(&list -> subscriber);
			list = list -> next;
    	}
	}

	Boolean searchSubs(SList list, int id){
		if(is_empty_list(list) == True){
			printf("\n Empty list ! \n");
			return False;
		}
		
		while((is_empty_list(list) == False)){
			if (list -> subscriber.id == id){
				return True;
			}
			list = list -> next; 
		}
		return False;
	}

	SList add_last(SList list, Subscriber *subscriber){ 
		SubsList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (searchSubs(list, subscriber -> id) == True){
			printf("This element already exist in the SList!\n ");
			return list;	
		}
		
		element -> subscriber = *subscriber;
    	element -> next = NULL;
		
		if (is_empty_list(list) == True)
			return element;

		SubsList *temp = list;
		while (temp -> next != NULL){
			temp  = temp -> next;
		}

		temp -> next = element; 
		return list;
	}

	SList add_first(SList list, Subscriber *subscriber){
		SubsList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}

		if (searchSubs(list, subscriber -> id) == True){
			printf("This element already exist in the SList!\n ");
			return list;	
		}
		
		element -> subscriber = *subscriber;

		if (is_empty_list(list) == True)
			element -> next = NULL;
		
		element -> next = list;
		return element;
	}

	SList remove_last(SList list){
		if (is_empty_list(list) == True)
			return new_subList();

		if (list -> next == NULL){
			free(list);
			return new_subList();
		}
		
		SubsList *nodes = list;
		SubsList *temp = list;
		 
		while (temp -> next != NULL){
			nodes = temp;
			temp = temp -> next;
		}
		nodes -> next = NULL;
		free(temp);

		return list;
	}

	SList remove_first(SList list){

		if (is_empty_list(list) == True)
			return new_subList();

		SubsList *element = NULL;
		element = malloc(sizeof(*element));
		
		if(element == NULL){
			fprintf(stderr, "Erreur d'allocation dynamique .\n") ;
			exit(EXIT_FAILURE);
		}
		element = list -> next;
		free(list);
		return element;
	}

	void clear_list(SList list){
		while (list != NULL)
	    list = remove_first(list);
	}

	//--------------------------------------------LinkedSList---------------------------------------//