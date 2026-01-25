#if !defined(__LIBRARY_H__)
#define __LIBRARY_H__
                              
	//---------------------------------------------Bool-Enum---------------------------------------//

    typedef enum Boolean {
        False,
        True
    }Boolean;
    
    //---------------------------------------------Op-Enum---------------------------------------//
    
    typedef enum transaction {
        withdrawal,
        deposit
    }Transaction;

	//-----------------------------------------------BOOK-----------------------------------------//
	typedef struct  Book Book;
    
	typedef void (*INIT_BOOK)(Book*);
	typedef void (*INFO)(Book*);
	typedef void (*SETDISP)(Boolean, Book*);
	typedef void (*ISAVAILABLE)(Book*);
	
	typedef struct Book {
		char title[33];
		char autor[15];
		int ISBN;
		int pubYear;
		Boolean disponibility; 
		
		INIT_BOOK init_book;
		INFO info; 
		SETDISP set_disponibility;
        ISAVAILABLE is_available;
	}Book;
	
	void init(Book *book);
	void book_info(Book *book);
	void set_disp(Boolean boolean, Book *book);
	void get_available(Book *book);
    	
	//-----------------------------------------------Stack----------------------------------------//

	typedef struct StackElement{
		Book book;
		Transaction transaction;
 		struct StackElement *next;
	}StackElement, *Stack;

	Boolean is_empty_stack(Stack stack);
	Stack new_stack(void);
	Stack push_stack(Stack stack, Book *book, Transaction transaction);
	Stack clear_stack(Stack stack);
	Stack pop_stack(Stack stack);
	void print_stack(Stack stack);
	Boolean contains( Stack stack, int ISBN);

	//---------------------------------------------SUSCRIBERS-------------------------------------//
	
    typedef struct Subscriber Subscriber;
    
	typedef void (*INIT)(Subscriber*);
	typedef void (*INTRODUCE)(Subscriber*); 
	typedef void (*BORROW)(Subscriber*, Book*);
	typedef void (*GIVEBACK)(Subscriber*, Book*);
	
	typedef struct Subscriber {
		char name[15];
		char surname[15];
		int id;
		Stack history;
		
		INIT init;
		INTRODUCE introduce_yourself;
		BORROW borrow_book;
		GIVEBACK giveback_book;
	}Subscriber;
	
	void init_subscriber(Subscriber *subscriber);
	void introduce(Subscriber *subscriber); 
	void borrow(Subscriber *subscribe, Book *book);
	void give_back(Subscriber *subscribe, Book *book);
     
    //---------------------------------------------BOOK_List----------------------------------------//

	typedef struct BookList{
        Book book;
		struct BookList *next;
    }BookList, *BList;

    BList new_list_b();
	Boolean is_empty_list_b(BList list);
	int list_size_b(BList list);
	void print_list_b(BList list);
	Boolean searchBook_b(BList list, int ISBN);

	BList add_last_b(BList list, Book *book);
	BList add_first_b(BList list, Book *book);
	BList remove_last_b(BList list);
	BList remove_first_b(BList list);
	void clear_list_b(BList list);
	
    //-----------------------------------------SUBSLIST-----------------------------------------//

	typedef struct SubsList{
        Subscriber subscriber;
		struct SubsList *next;
    }SubsList, *SList;

	Boolean is_empty_list(SList list);
	SList new_subList();
	int list_size(SList list);
	void print_list(SList list);
	Boolean searchSubs(SList list, int id);

	SList add_last(SList list, Subscriber *subscriber);
	SList add_first(SList list, Subscriber *subscriber);
	SList remove_last(SList list);
	SList remove_first(SList list);
	void clear_list(SList list);
	
#endif // __LIBRARY_H__
