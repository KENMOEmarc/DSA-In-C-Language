#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main(){

    BList bookList = new_list_b();
    SList subsList = new_subList();

    Book book1;
    Book book2;
    Book book3;

    printf("First book \n");
    book1.init_book = init;
    book1.init_book(&book1);
    book1.info(&book1);

    printf("Second book \n");
    book2.init_book = init;
    book2.init_book(&book2);
    book2.info(&book2);

    printf("Third book \n");
    book3.init_book = init;
    book3.init_book(&book3);
    book3.info(&book3);
    
    Subscriber subscriber1;
    Subscriber subscriber2;
    Subscriber subscriber3;

    printf("first subscriber \n");
    subscriber1.init = init_subscriber;
    subscriber1.init(&subscriber1);
    subscriber1.introduce_yourself(&subscriber1);

    printf("Second subscriber \n");
    subscriber2.init = init_subscriber;
    subscriber2.init(&subscriber2);
    subscriber2.introduce_yourself(&subscriber2);

    printf("Third subscriber \n");
    subscriber3.init = init_subscriber;
    subscriber3.init(&subscriber3);
    subscriber3.introduce_yourself(&subscriber3);

    printf("Book's availability Before borrow :\n");
    book1.is_available(&book1);
    subscriber2.borrow_book(&subscriber2, &book1);
    printf("Book's availability After borrow :\n");
    book1.is_available(&book1);
    subscriber2.giveback_book(&subscriber2, &book1);
    printf("Book's availability After give-back :\n");
    book1.info(&book1);

    bookList = add_first_b(bookList, &book1);
    bookList = add_first_b(bookList, &book2);
    bookList = add_first_b(bookList, &book3);
    subsList = add_first(subsList, &subscriber1);
    subsList = add_first(subsList, &subscriber2);
    subsList = add_first(subsList, &subscriber3);

    printf("List of subscribers : \n");
    print_list(subsList);
    printf("List of books : \n");
    print_list_b(bookList);

    clear_list(subsList);
    clear_list_b(bookList);

	printf(" \n //UrusNoire|| \n");
    return 0;
}