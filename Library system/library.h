#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===================== CONSTANTES ===================== */

#define MAX_TITLE   64
#define MAX_AUTHOR  32
#define MAX_NAME    32
#define MAX_SURNAME 32

/* ===================== TYPES ===================== */

typedef enum {
    False = 0,
    True  = 1
} Boolean;

typedef enum {
    Borrow = 0,
    Revert = 1
} Transaction;

/* ===================== DECLARATIONS ANTICIPEES ===================== */

typedef struct StackElement StackElement;
typedef StackElement* Stack;

/* ===================== STRUCTURES ===================== */

/* -------- Livre -------- */

typedef struct Book {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int  ISBN;
    int  pubYear;
    Boolean availability;

    void (*init_book)(struct Book*);
    void (*set_availability)(Boolean, struct Book*);
    void (*info)(const struct Book*);
    Boolean (*is_available)(const struct Book*);
} Book;

/* -------- Abonné -------- */

typedef struct Subscriber {
    char name[MAX_NAME];
    char surname[MAX_SURNAME];
    int  id;
    Stack history;

    void (*introduce_yourself)(const struct Subscriber*);
    Boolean (*borrow_book)(struct Subscriber*, Book*);
    Boolean (*giveback_book)(struct Subscriber*, Book*);
} Subscriber;

/* -------- Pile -------- */

struct StackElement {
    Book book;
    Transaction transaction;
    StackElement* next;
};

/* -------- Liste de livres -------- */

typedef struct BookList {
    Book book;
    struct BookList* next;
} BookList, *BList;

/* -------- Liste d’abonnés -------- */

typedef struct SubsList {
    Subscriber subscriber;
    struct SubsList* next;
} SubsList, *SList;

/* ===================== PROTOTYPES ===================== */

/* ---- Livres ---- */

void     init_book(Book* book);
void     book_info(const Book* book);
void     set_avail(Boolean boolean, Book* book);
Boolean is_available(const Book* book);

/* ---- Abonnés ---- */

void     init_subscriber(Subscriber* subscriber);
void     introduce(const Subscriber* subscriber);
Boolean borrow(Subscriber* subscriber, Book* book);
Boolean give_back(Subscriber* subscriber, Book* book);

/* ---- Pile ---- */

Stack   new_stack(void);
Boolean is_empty_stack(Stack stack);
Stack   push_stack(Stack stack, const Book* book, Transaction transaction);
Stack   pop_stack(Stack stack);
Stack   clear_stack(Stack stack);
void    print_stack(Stack stack);
Boolean contains(Stack stack, int ISBN);

/* ---- Liste des livres ---- */

BList   new_list_b(void);
Boolean is_empty_list_b(BList list);
int     list_size_b(BList list);
void    print_list_b(BList list);
Boolean searchBook_b(BList list, int ISBN);
BList   add_last_b(BList list, const Book* book);
BList   add_first_b(BList list, const Book* book);
BList   remove_last_b(BList list);
BList   remove_first_b(BList list);
void    clear_list_b(BList list);

/* ---- Liste des abonnés ---- */

SList   new_subList(void);
Boolean is_empty_list(SList list);
int     list_size(SList list);
void    print_list(SList list);
Boolean searchSubs(SList list, int id);
SList   add_last(SList list, const Subscriber* subscriber);
SList   add_first(SList list, const Subscriber* subscriber);
SList   remove_last(SList list);
SList   remove_first(SList list);
void    clear_list(SList list);

#endif /* LIBRARY_H */
