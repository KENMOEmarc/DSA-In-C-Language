#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================================
// FONCTIONS POUR LES LIVRES
// ===========================================

void init_book(Book* book) {
    book->set_availability = set_avail;
    book->info = book_info;
    book->is_available = is_available;

    printf("Title (max %d chars): ", MAX_TITLE - 1);
    scanf("%63s", book->title);

    printf("Author (max %d chars): ", MAX_AUTHOR - 1);
    scanf("%31s", book->author);

    printf("ISBN: ");
    scanf("%d", &book->ISBN);

    printf("Publication year: ");
    scanf("%d", &book->pubYear);

    book->availability = True;
}

void book_info(const Book* book) {
    printf("|| Title: %s | Author: %s | ISBN: %d | Year: %d | Status: %s ||\n",
           book->title,
           book->author,
           book->ISBN,
           book->pubYear,
           book->availability ? "Available" : "Unavailable");
}

void set_avail(Boolean boolean, Book* book) {
    book->availability = boolean;
}

Boolean is_available(const Book* book) {
    return book->availability;
}

// ===========================================
// FONCTIONS POUR LES ABONNÉS
// ===========================================

void init_subscriber(Subscriber* subscriber) {
    subscriber->introduce_yourself = introduce;
    subscriber->borrow_book = borrow;
    subscriber->giveback_book = give_back;

    printf("First name (max %d chars): ", MAX_NAME - 1);
    scanf("%31s", subscriber->name);

    printf("Last name (max %d chars): ", MAX_SURNAME - 1);
    scanf("%31s", subscriber->surname);

    printf("ID: ");
    scanf("%d", &subscriber->id);

    subscriber->history = new_stack();
}

void introduce(const Subscriber* subscriber) {
    printf("Name: %s %s | ID: %d\n",
           subscriber->name,
           subscriber->surname,
           subscriber->id);

    printf("History:\n");
    print_stack(subscriber->history);
}

Boolean borrow(Subscriber* subscriber, Book* book) {
    if (!book->availability) {
        printf("Book not available!\n");
        return False;
    }

    book->availability = False;
    subscriber->history = push_stack(subscriber->history, book, Borrow);
    printf("Book borrowed successfully.\n");
    return True;
}

Boolean give_back(Subscriber* subscriber, Book* book) {
    if (book->availability) {
        printf("Book already in library!\n");
        return False;
    }

    book->availability = True;
    subscriber->history = push_stack(subscriber->history, book, Revert);
    printf("Book returned successfully.\n");
    return True;
}

// ===========================================
// FONCTIONS POUR LA PILE
// ===========================================

Stack new_stack(void) {
    return NULL;
}

Boolean is_empty_stack(Stack stack) {
    return stack == NULL ? True : False;
}

Stack push_stack(Stack stack, const Book* book, Transaction transaction) {
    StackElement* element = malloc(sizeof(StackElement));
    if (!element) {
        fprintf(stderr, "Stack allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    element->book = *book;
    element->transaction = transaction;
    element->next = stack;
    return element;
}

Stack pop_stack(Stack stack) {
    if (is_empty_stack(stack)) return NULL;

    Stack next = stack->next;
    free(stack);
    return next;
}

Stack clear_stack(Stack stack) {
    while (stack) {
        stack = pop_stack(stack);
    }
    return NULL;
}

void print_stack(Stack stack) {
    if (is_empty_stack(stack)) {
        printf("No history.\n");
        return;
    }

    while (stack) {
        stack->book.info(&stack->book);
        printf("Transaction: %s\n",
               stack->transaction == Borrow ? "Borrow" : "Return");
        stack = stack->next;
    }
}

Boolean contains(Stack stack, int ISBN) {
    while (stack) {
        if (stack->book.ISBN == ISBN) return True;
        stack = stack->next;
    }
    return False;
}

// ===========================================
// FONCTIONS POUR LA LISTE DE LIVRES
// ===========================================

BList new_list_b(void) { return NULL; }

Boolean is_empty_list_b(BList list) { return list == NULL ? True : False; }

int list_size_b(BList list) {
    int size = 0;
    while (list) {
        size++;
        list = list->next;
    }
    return size;
}

void print_list_b(BList list) {
    if (is_empty_list_b(list)) {
        printf("No books in list.\n");
        return;
    }

    printf("=== Book list (%d) ===\n", list_size_b(list));
    while (list) {
        list->book.info(&list->book);
        list = list->next;
    }
}

Boolean searchBook_b(BList list, int ISBN) {
    while (list) {
        if (list->book.ISBN == ISBN) return True;
        list = list->next;
    }
    return False;
}

BList add_last_b(BList list, const Book* book) {
    if (searchBook_b(list, book->ISBN)) return list;

    BookList* node = malloc(sizeof(BookList));
    if (!node) exit(EXIT_FAILURE);

    node->book = *book;
    node->next = NULL;

    if (!list) return node;

    BList cur = list;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return list;
}

BList add_first_b(BList list, const Book* book) {
    if (searchBook_b(list, book->ISBN)) return list;

    BookList* node = malloc(sizeof(BookList));
    if (!node) exit(EXIT_FAILURE);

    node->book = *book;
    node->next = list;
    return node;
}

BList remove_last_b(BList list) {
    if (!list) return NULL;

    if (!list->next) {
        free(list);
        return NULL;
    }

    BList prev = list;
    BList cur = list->next;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;
    free(cur);
    return list;
}

BList remove_first_b(BList list) {
    if (!list) return NULL;
    BList next = list->next;
    free(list);
    return next;
}

void clear_list_b(BList list) {
    while (list) list = remove_first_b(list);
}

// ===========================================
// FONCTIONS POUR LA LISTE D'ABONNÉS
// ===========================================

SList new_subList(void) { return NULL; }

Boolean is_empty_list(SList list) { return list == NULL ? True : False; }

int list_size(SList list) {
    int size = 0;
    while (list) {
        size++;
        list = list->next;
    }
    return size;
}

void print_list(SList list) {
    if (is_empty_list(list)) {
        printf("No subscribers.\n");
        return;
    }

    printf("=== Subscriber list (%d) ===\n", list_size(list));
    while (list) {
        list->subscriber.introduce_yourself(&list->subscriber);
        list = list->next;
    }
}

Boolean searchSubs(SList list, int id) {
    while (list) {
        if (list->subscriber.id == id) return True;
        list = list->next;
    }
    return False;
}

SList add_last(SList list, const Subscriber* subscriber) {
    if (searchSubs(list, subscriber->id)) return list;

    SubsList* node = malloc(sizeof(SubsList));
    if (!node) exit(EXIT_FAILURE);

    node->subscriber = *subscriber;
    node->next = NULL;

    if (!list) return node;

    SList cur = list;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return list;
}

SList add_first(SList list, const Subscriber* subscriber) {
    if (searchSubs(list, subscriber->id)) return list;

    SubsList* node = malloc(sizeof(SubsList));
    if (!node) exit(EXIT_FAILURE);

    node->subscriber = *subscriber;
    node->next = list;
    return node;
}

SList remove_last(SList list) {
    if (!list) return NULL;

    if (!list->next) {
        free(list);
        return NULL;
    }

    SList prev = list;
    SList cur = list->next;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;
    free(cur);
    return list;
}

SList remove_first(SList list) {
    if (!list) return NULL;
    SList next = list->next;
    free(list);
    return next;
}

void clear_list(SList list) {
    while (list) list = remove_first(list);
}
