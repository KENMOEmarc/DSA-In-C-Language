#if !defined(__STRUCT_H_)
#define __STRUCT_H_

	//---------------------------------------------Bool-Enum---------------------------------------//

    typedef enum{
		false,
		true
	}Boolean;

	//-----------------------------------------------PLayer---------------------------------------//
	
	typedef struct Player {
		char name[15];
		char pseudo[15];
		int hp;
		int id; 
	}Player;
		
	void updateName(Player *player,char newName[15]);
	void attack(Player *player);
	
	//-----------------------------------------------Stack----------------------------------------//

	typedef struct StackElement{
		Player player;
		struct StackElement *next;
	}StackElement, *Stack;

	Boolean is_empty_stack(Stack stack);
	Stack new_stack(void);
	Stack push_stack(Stack stack, Player new_player);
	Stack clear_stack(Stack stack);
	Stack pop_stack(Stack stack);
	void peek_stack(Stack stack);
	void print_stack(Stack stack);
	Boolean contains( Stack stack, char pseudo[]);
	
     //---------------------------------------------Queue------------------------------------------//

	typedef struct QueueElement{
        Player player;
		struct QueueElement *next;
    }QueueElement, *Queue;

	Boolean is_empty_queue();
	void enQueue(Player *new_player);
	void clear_queue();
	void deQueue();
	void print_queue();
	Boolean find_player(char pseudo[]);

	static QueueElement* first = NULL;
	static QueueElement* last = NULL;
    static int queue_length;

	//-----------------------------------------------List------------------------------------------//

	typedef struct PlayerList{
        Player player;
		struct PlayerList *next;
    }PlayerList, *List;

	Boolean is_empty_list(List list);
	List new_list();
	int list_size(List list);
	void print_list(List list);
	Boolean searchPlayer(List list, char pseudo[]);

	List add_last(List list, Player *player);
	List add_first(List list, Player *player);
	List remove_last(List list);
	List remove_first(List list);
	void clear_list(List list);

	//-------------------------------------------LinkedList---------------------------------------//

	typedef struct NodeList{
        Player player;
		struct PlayerList *previous;
		struct PlayerList *next;
    }NodeList;

	typedef struct LinkedList{
        int length;
		struct NodeList *first;
		struct NodeList *last;
    }*LinkedList;

	Boolean is_empty_linkedList(LinkedList linkedList);
	LinkedList new_linkedList();
	int linkedList_size(LinkedList linkedList);
	void printLinkedList(LinkedList linkedList);
	Player getFirst(LinkedList linkedList);
	Player getFLast(LinkedList linkedList);
	Boolean containsPlayer(LinkedList linkedList, char pseudo[]);
	Player get(LinkedList linkedList, char pseudo[]);

	LinkedList addLast(LinkedList linkedList, Player *player);
	LinkedList addFirst(LinkedList linkedList, Player *player);
	LinkedList removeLast(LinkedList linkedList);
	LinkedList removeFirst(LinkedList linkedList);
	void clear_linkedList(LinkedList linkedList);

#endif 