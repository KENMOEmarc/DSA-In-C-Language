#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// Variables globales
BList library = NULL;
SList subscribers = NULL;

// Prototypes
void display_menu(void);
void add_book(void);
void display_books(void);
void add_subscriber(void);
void display_subscribers(void);
void borrow_book(void);
void return_book(void);
void clear_buffer(void);
void search_book_by_isbn(void);
void search_subscriber_by_id(void);
void display_subscriber_history(void);

int main(void) {
    printf("=============================\n");
    printf("   LIBRARY MANAGEMENT SYSTEM\n");
    printf("=============================\n");

    // Initialisation des listes
    library = new_list_b();
    subscribers = new_subList();

    display_menu();

    // Nettoyage
    clear_list_b(library);
    clear_list(subscribers);

    return 0;
}

void display_menu(void) {
    int choice;

    do {
        printf("\n========= MAIN MENU =========\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Add a subscriber\n");
        printf("4. Display all subscribers\n");
        printf("5. Borrow a book\n");
        printf("6. Return a book\n");
        printf("7. Search for a book by ISBN\n");
        printf("8. Search for a subscriber by ID\n");
        printf("9. Display subscriber history\n");
        printf("0. Exit\n");
        printf("=============================\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clear_buffer();
            continue;
        }
        clear_buffer();

        switch(choice) {
            case 1: add_book(); break;
            case 2: display_books(); break;
            case 3: add_subscriber(); break;
            case 4: display_subscribers(); break;
            case 5: borrow_book(); break;
            case 6: return_book(); break;
            case 7: search_book_by_isbn(); break;
            case 8: search_subscriber_by_id(); break;
            case 9: display_subscriber_history(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);
}

void add_book(void) {
    printf("\n--- ADD A NEW BOOK ---\n");

    // Création d'un livre
    Book new_book;

    // Initialisation
    init_book(&new_book);

    // Ajout à la liste
    library = add_last_b(library, &new_book);
    printf("Book added successfully!\n");
}

void display_books(void) {
    printf("\n--- ALL BOOKS ---\n");
    if (is_empty_list_b(library)) {
        printf("No books in the library.\n");
    } else {
        print_list_b(library);
    }
}

void add_subscriber(void) {
    printf("\n--- ADD A NEW SUBSCRIBER ---\n");

    // Création d'un abonné
    Subscriber new_subscriber;

    // Initialisation
    init_subscriber(&new_subscriber);

    // Ajout à la liste
    subscribers = add_last(subscribers, &new_subscriber);
    printf("Subscriber added successfully!\n");
}

void display_subscribers(void) {
    printf("\n--- ALL SUBSCRIBERS ---\n");
    if (is_empty_list(subscribers)) {
        printf("No subscribers registered.\n");
    } else {
        print_list(subscribers);
    }
}

void borrow_book(void) {
    printf("\n--- BORROW A BOOK ---\n");

    if (is_empty_list_b(library)) {
        printf("No books available.\n");
        return;
    }

    if (is_empty_list(subscribers)) {
        printf("No subscribers available.\n");
        return;
    }

    // Afficher les livres disponibles
    printf("Available books:\n");
    BList temp_book = library;
    int book_count = 0;
    int available_book[100]; // Tableau pour stocker les indices des livres disponibles
    int book_index = 0;

    while (temp_book != NULL) {
        if (temp_book->book.availability == True) {
            printf("%d. ", ++book_count);
            temp_book->book.info(&temp_book->book);
            available_book[book_index++] = book_count;
        }
        temp_book = temp_book->next;
    }

    if (book_count == 0) {
        printf("No books available for borrowing.\n");
        return;
    }

    // Afficher les abonnés
    printf("\nAvailable subscribers:\n");
    SList temp_sub = subscribers;
    int sub_count = 0;
    while (temp_sub != NULL) {
        printf("%d. %s %s (ID: %d)\n", ++sub_count,
               temp_sub->subscriber.name,
               temp_sub->subscriber.surname,
               temp_sub->subscriber.id);
        temp_sub = temp_sub->next;
    }

    int book_choice, sub_choice;
    printf("\nSelect book number: ");
    if (scanf("%d", &book_choice) != 1) {
        printf("Invalid input!\n");
        clear_buffer();
        return;
    }

    printf("Select subscriber number: ");
    if (scanf("%d", &sub_choice) != 1) {
        printf("Invalid input!\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    // Vérifier si le choix du livre est valide
    if (book_choice < 1 || book_choice > book_count) {
        printf("Invalid book selection!\n");
        return;
    }

    // Vérifier si le choix de l'abonné est valide
    if (sub_choice < 1 || sub_choice > sub_count) {
        printf("Invalid subscriber selection!\n");
        return;
    }

    // Trouver le livre sélectionné
    BList selected_book = library;
    int current_book = 0;
    while (selected_book != NULL) {
        if (selected_book->book.availability == True) {
            current_book++;
            if (current_book == book_choice) break;
        }
        selected_book = selected_book->next;
    }

    // Trouver l'abonné sélectionné
    SList selected_sub = subscribers;
    int current_sub = 0;
    while (selected_sub != NULL) {
        current_sub++;
        if (current_sub == sub_choice) break;
        selected_sub = selected_sub->next;
    }

    if (selected_book != NULL && selected_sub != NULL) {
        selected_sub->subscriber.borrow_book(&selected_sub->subscriber, &selected_book->book);
    } else {
        printf("Selection error!\n");
    }
}

void return_book(void) {
    printf("\n--- RETURN A BOOK ---\n");

    if (is_empty_list_b(library)) {
        printf("No books in library.\n");
        return;
    }

    if (is_empty_list(subscribers)) {
        printf("No subscribers available.\n");
        return;
    }

    // Afficher les livres empruntés
    printf("Borrowed books:\n");
    BList temp_book = library;
    int book_count = 0;

    while (temp_book != NULL) {
        if (temp_book->book.availability == False) {
            printf("%d. ", ++book_count);
            temp_book->book.info(&temp_book->book);
        }
        temp_book = temp_book->next;
    }

    if (book_count == 0) {
        printf("No books currently borrowed.\n");
        return;
    }

    // Afficher les abonnés
    printf("\nAvailable subscribers:\n");
    SList temp_sub = subscribers;
    int sub_count = 0;
    while (temp_sub != NULL) {
        printf("%d. %s %s (ID: %d)\n", ++sub_count,
               temp_sub->subscriber.name,
               temp_sub->subscriber.surname,
               temp_sub->subscriber.id);
        temp_sub = temp_sub->next;
    }

    int book_choice, sub_choice;
    printf("\nSelect book number to return: ");
    if (scanf("%d", &book_choice) != 1) {
        printf("Invalid input!\n");
        clear_buffer();
        return;
    }

    printf("Select subscriber number: ");
    if (scanf("%d", &sub_choice) != 1) {
        printf("Invalid input!\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    // Vérifier si le choix du livre est valide
    if (book_choice < 1 || book_choice > book_count) {
        printf("Invalid book selection!\n");
        return;
    }

    // Vérifier si le choix de l'abonné est valide
    if (sub_choice < 1 || sub_choice > sub_count) {
        printf("Invalid subscriber selection!\n");
        return;
    }

    // Trouver le livre sélectionné
    BList selected_book = library;
    int current_book = 0;
    while (selected_book != NULL) {
        if (selected_book->book.availability == False) {
            current_book++;
            if (current_book == book_choice) break;
        }
        selected_book = selected_book->next;
    }

    // Trouver l'abonné sélectionné
    SList selected_sub = subscribers;
    int current_sub = 0;
    while (selected_sub != NULL) {
        current_sub++;
        if (current_sub == sub_choice) break;
        selected_sub = selected_sub->next;
    }

    if (selected_book != NULL && selected_sub != NULL) {
        selected_sub->subscriber.giveback_book(&selected_sub->subscriber, &selected_book->book);
    } else {
        printf("Selection error!\n");
    }
}

void search_book_by_isbn(void) {
    printf("\n--- SEARCH BOOK BY ISBN ---\n");

    if (is_empty_list_b(library)) {
        printf("No books in the library.\n");
        return;
    }

    int isbn;
    printf("Enter ISBN: ");
    if (scanf("%d", &isbn) != 1) {
        printf("Invalid ISBN!\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    if (searchBook_b(library, isbn)) {
        printf("Book with ISBN %d is in the library.\n", isbn);
    } else {
        printf("Book with ISBN %d is not found.\n", isbn);
    }
}

void search_subscriber_by_id(void) {
    printf("\n--- SEARCH SUBSCRIBER BY ID ---\n");

    if (is_empty_list(subscribers)) {
        printf("No subscribers registered.\n");
        return;
    }

    int id;
    printf("Enter subscriber ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    if (searchSubs(subscribers, id)) {
        printf("Subscriber with ID %d is registered.\n", id);
    } else {
        printf("Subscriber with ID %d is not found.\n", id);
    }
}

void display_subscriber_history(void) {
    printf("\n--- DISPLAY SUBSCRIBER HISTORY ---\n");

    if (is_empty_list(subscribers)) {
        printf("No subscribers registered.\n");
        return;
    }

    // Afficher les abonnés
    printf("Subscribers:\n");
    SList temp_sub = subscribers;
    int sub_count = 0;
    while (temp_sub != NULL) {
        printf("%d. %s %s (ID: %d)\n", ++sub_count,
               temp_sub->subscriber.name,
               temp_sub->subscriber.surname,
               temp_sub->subscriber.id);
        temp_sub = temp_sub->next;
    }

    int sub_choice;
    printf("\nSelect subscriber number: ");
    if (scanf("%d", &sub_choice) != 1) {
        printf("Invalid input!\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    // Vérifier si le choix est valide
    if (sub_choice < 1 || sub_choice > sub_count) {
        printf("Invalid subscriber selection!\n");
        return;
    }

    // Trouver l'abonné sélectionné
    SList selected_sub = subscribers;
    int current_sub = 0;
    while (selected_sub != NULL) {
        current_sub++;
        if (current_sub == sub_choice) break;
        selected_sub = selected_sub->next;
    }

    if (selected_sub != NULL) {
        printf("\nHistory of %s %s:\n",
               selected_sub->subscriber.name,
               selected_sub->subscriber.surname);
        print_stack((Stack)selected_sub->subscriber.history);
    } else {
        printf("Subscriber not found!\n");
    }
}

void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
