#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// Variables globales pour stocker les listes
BList bibliotheque = NULL;
SList abonnes = NULL;

void afficher_menu_principal();
void gerer_livres();
void gerer_abonnes();
void gerer_emprunts();
void ajouter_livre();
void afficher_livres();
void rechercher_livre();
void supprimer_livre();
void ajouter_abonne();
void afficher_abonnes();
void rechercher_abonne();
void supprimer_abonne();
void emprunter_livre();
void retourner_livre();
void afficher_historique_abonne();
void tester_pile();
void vider_buffer();

int main() {
    printf("=========================================\n");
    printf("   SYSTEME DE GESTION DE BIBLIOTHEQUE\n");
    printf("=========================================\n");
    
    // Initialisation des listes
    bibliotheque = new_list_b();
    abonnes = new_subList();
    
    afficher_menu_principal();
    
    // Nettoyage avant de quitter
    clear_list_b(bibliotheque);
    clear_list(abonnes);
    
    return 0;
}

void afficher_menu_principal() {
    int choix;
    
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1.  Gérer les livres\n");
        printf("2.  Gérer les abonnés\n");
        printf("3.  Emprunter un livre\n");
        printf("4.  Retourner un livre\n");
        printf("5.  Afficher l'historique d'un abonné\n");
        printf("6.  Tester les fonctions de pile\n");
        printf("7.  Afficher tous les livres\n");
        printf("8.  Afficher tous les abonnés\n");
        printf("9.  Vider les listes (reset)\n");
        printf("0.  Quitter\n");
        printf("===================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        vider_buffer();
        
        switch(choix) {
            case 1: gerer_livres(); break;
            case 2: gerer_abonnes(); break;
            case 3: emprunter_livre(); break;
            case 4: retourner_livre(); break;
            case 5: afficher_historique_abonne(); break;
            case 6: tester_pile(); break;
            case 7: afficher_livres(); break;
            case 8: afficher_abonnes(); break;
            case 9:
                clear_list_b(bibliotheque);
                clear_list(abonnes);
                bibliotheque = new_list_b();
                abonnes = new_subList();
                printf("✓ Listes vidées avec succès !\n");
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while(choix != 0);
}

void gerer_livres() {
    int choix;
    
    do {
        printf("\n--------- GESTION DES LIVRES ---------\n");
        printf("1. Ajouter un nouveau livre\n");
        printf("2. Afficher tous les livres\n");
        printf("3. Rechercher un livre par ISBN\n");
        printf("4. Supprimer un livre\n");
        printf("5. Nombre de livres dans la bibliothèque\n");
        printf("0. Retour au menu principal\n");
        printf("-------------------------------------\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        vider_buffer();
        
        switch(choix) {
            case 1: ajouter_livre(); break;
            case 2: afficher_livres(); break;
            case 3: rechercher_livre(); break;
            case 4: supprimer_livre(); break;
            case 5:
                printf("Nombre de livres : %d\n", list_size_b(bibliotheque));
                break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }
    } while(choix != 0);
}

void gerer_abonnes() {
    int choix;
    
    do {
        printf("\n-------- GESTION DES ABONNES --------\n");
        printf("1. Ajouter un nouvel abonné\n");
        printf("2. Afficher tous les abonnés\n");
        printf("3. Rechercher un abonné par ID\n");
        printf("4. Supprimer un abonné\n");
        printf("5. Nombre d'abonnés\n");
        printf("0. Retour au menu principal\n");
        printf("-------------------------------------\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        vider_buffer();
        
        switch(choix) {
            case 1: ajouter_abonne(); break;
            case 2: afficher_abonnes(); break;
            case 3: rechercher_abonne(); break;
            case 4: supprimer_abonne(); break;
            case 5:
                printf("Nombre d'abonnés : %d\n", list_size(abonnes));
                break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }
    } while(choix != 0);
}

void ajouter_livre() {
    printf("\n--- AJOUT D'UN NOUVEAU LIVRE ---\n");
    
    // Création dynamique d'un livre
    Book *nouveauLivre = malloc(sizeof(Book));
    if (nouveauLivre == NULL) {
        printf("Erreur d'allocation mémoire !\n");
        return;
    }
    
    // Initialisation via la fonction init
    nouveauLivre->init_book(nouveauLivre);
    
    // Demander où ajouter
    printf("\nOù voulez-vous ajouter le livre ?\n");
    printf("1. Au début de la liste\n");
    printf("2. À la fin de la liste\n");
    printf("Votre choix : ");
    int position;
    scanf("%d", &position);
    vider_buffer();
    
    if (position == 1) {
        bibliotheque = add_first_b(bibliotheque, nouveauLivre);
        printf("✓ Livre ajouté au début de la liste.\n");
    } else if (position == 2) {
        bibliotheque = add_last_b(bibliotheque, nouveauLivre);
        printf("✓ Livre ajouté à la fin de la liste.\n");
    } else {
        printf("Position invalide. Livre non ajouté.\n");
    }
    
    // Ne pas free le livre car il est référencé dans la liste
}

void afficher_livres() {
    printf("\n--- LISTE DES LIVRES ---\n");
    if (is_empty_list_b(bibliotheque)) {
        printf("Aucun livre dans la bibliothèque.\n");
    } else {
        print_list_b(bibliotheque);
    }
}

void rechercher_livre() {
    printf("\n--- RECHERCHE D'UN LIVRE ---\n");
    if (is_empty_list_b(bibliotheque)) {
        printf("La bibliothèque est vide.\n");
        return;
    }
    
    int isbn;
    printf("Entrez l'ISBN du livre à rechercher : ");
    scanf("%d", &isbn);
    vider_buffer();
    
    if (searchBook_b(bibliotheque, isbn)) {
        printf("✓ Le livre avec ISBN %d est présent dans la bibliothèque.\n", isbn);
    } else {
        printf("✗ Aucun livre trouvé avec l'ISBN %d.\n", isbn);
    }
}

void supprimer_livre() {
    printf("\n--- SUPPRESSION D'UN LIVRE ---\n");
    if (is_empty_list_b(bibliotheque)) {
        printf("La bibliothèque est vide.\n");
        return;
    }
    
    printf("Comment voulez-vous supprimer ?\n");
    printf("1. Supprimer le premier livre\n");
    printf("2. Supprimer le dernier livre\n");
    printf("Votre choix : ");
    int choix;
    scanf("%d", &choix);
    vider_buffer();
    
    if (choix == 1) {
        bibliotheque = remove_first_b(bibliotheque);
        printf("✓ Premier livre supprimé.\n");
    } else if (choix == 2) {
        bibliotheque = remove_last_b(bibliotheque);
        printf("✓ Dernier livre supprimé.\n");
    } else {
        printf("Choix invalide.\n");
    }
}

void ajouter_abonne() {
    printf("\n--- AJOUT D'UN NOUVEL ABONNE ---\n");
    
    // Création dynamique d'un abonné
    Subscriber *nouvelAbonne = malloc(sizeof(Subscriber));
    if (nouvelAbonne == NULL) {
        printf("Erreur d'allocation mémoire !\n");
        return;
    }
    
    // Initialisation via la fonction init_subscriber
    init_subscriber(nouvelAbonne);
    
    // Demander où ajouter
    printf("\nOù voulez-vous ajouter l'abonné ?\n");
    printf("1. Au début de la liste\n");
    printf("2. À la fin de la liste\n");
    printf("Votre choix : ");
    int position;
    scanf("%d", &position);
    vider_buffer();
    
    if (position == 1) {
        abonnes = add_first(abonnes, nouvelAbonne);
        printf("✓ Abonné ajouté au début de la liste.\n");
    } else if (position == 2) {
        abonnes = add_last(abonnes, nouvelAbonne);
        printf("✓ Abonné ajouté à la fin de la liste.\n");
    } else {
        printf("Position invalide. Abonné non ajouté.\n");
    }
}

void afficher_abonnes() {
    printf("\n--- LISTE DES ABONNES ---\n");
    if (is_empty_list(abonnes)) {
        printf("Aucun abonné enregistré.\n");
    } else {
        print_list(abonnes);
    }
}

void rechercher_abonne() {
    printf("\n--- RECHERCHE D'UN ABONNE ---\n");
    if (is_empty_list(abonnes)) {
        printf("Aucun abonné enregistré.\n");
        return;
    }
    
    int id;
    printf("Entrez l'ID de l'abonné à rechercher : ");
    scanf("%d", &id);
    vider_buffer();
    
    if (searchSubs(abonnes, id)) {
        printf("✓ L'abonné avec ID %d est présent.\n", id);
    } else {
        printf("✗ Aucun abonné trouvé avec l'ID %d.\n", id);
    }
}

void supprimer_abonne() {
    printf("\n--- SUPPRESSION D'UN ABONNE ---\n");
    if (is_empty_list(abonnes)) {
        printf("Aucun abonné enregistré.\n");
        return;
    }
    
    printf("Comment voulez-vous supprimer ?\n");
    printf("1. Supprimer le premier abonné\n");
    printf("2. Supprimer le dernier abonné\n");
    printf("Votre choix : ");
    int choix;
    scanf("%d", &choix);
    vider_buffer();
    
    if (choix == 1) {
        abonnes = remove_first(abonnes);
        printf("✓ Premier abonné supprimé.\n");
    } else if (choix == 2) {
        abonnes = remove_last(abonnes);
        printf("✓ Dernier abonné supprimé.\n");
    } else {
        printf("Choix invalide.\n");
    }
}

void emprunter_livre() {
    printf("\n--- EMPRUNT D'UN LIVRE ---\n");
    
    if (is_empty_list_b(bibliotheque)) {
        printf("Aucun livre disponible dans la bibliothèque.\n");
        return;
    }
    
    if (is_empty_list(abonnes)) {
        printf("Aucun abonné enregistré.\n");
        return;
    }
    
    // Afficher les livres disponibles
    printf("Livres disponibles :\n");
    BList temp = bibliotheque;
    int i = 1;
    while (temp != NULL) {
        if (temp->book.disponibility == True) {
            printf("%d. ", i);
            temp->book.info(&temp->book);
        }
        temp = temp->next;
        i++;
    }
    
    // Afficher les abonnés
    printf("\nAbonnés disponibles :\n");
    SList tempA = abonnes;
    i = 1;
    while (tempA != NULL) {
        printf("%d. ", i);
        tempA->subscriber.introduce_yourself(&tempA->subscriber);
        tempA = tempA->next;
        i++;
    }
    
    int choixLivre, choixAbonne;
    printf("\nNuméro du livre à emprunter : ");
    scanf("%d", &choixLivre);
    printf("Numéro de l'abonné : ");
    scanf("%d", &choixAbonne);
    vider_buffer();
    
    // Trouver le livre sélectionné
    BList livreSelect = bibliotheque;
    int compteur = 1;
    while (livreSelect != NULL && compteur < choixLivre) {
        livreSelect = livreSelect->next;
        compteur++;
    }
    
    // Trouver l'abonné sélectionné
    SList abonneSelect = abonnes;
    compteur = 1;
    while (abonneSelect != NULL && compteur < choixAbonne) {
        abonneSelect = abonneSelect->next;
        compteur++;
    }
    
    if (livreSelect != NULL && abonneSelect != NULL) {
        abonneSelect->subscriber.borrow_book(&abonneSelect->subscriber, &livreSelect->book);
        printf("✓ Opération d'emprunt effectuée.\n");
    } else {
        printf("✗ Sélection invalide.\n");
    }
}

void retourner_livre() {
    printf("\n--- RETOUR D'UN LIVRE ---\n");
    
    if (is_empty_list_b(bibliotheque)) {
        printf("Aucun livre dans la bibliothèque.\n");
        return;
    }
    
    if (is_empty_list(abonnes)) {
        printf("Aucun abonné enregistré.\n");
        return;
    }
    
    // Afficher les livres non disponibles
    printf("Livres actuellement empruntés :\n");
    BList temp = bibliotheque;
    int i = 1;
    while (temp != NULL) {
        if (temp->book.disponibility == False) {
            printf("%d. ", i);
            temp->book.info(&temp->book);
        }
        temp = temp->next;
        i++;
    }
    
    // Afficher les abonnés
    printf("\nAbonnés :\n");
    SList tempA = abonnes;
    i = 1;
    while (tempA != NULL) {
        printf("%d. ", i);
        tempA->subscriber.introduce_yourself(&tempA->subscriber);
        tempA = tempA->next;
        i++;
    }
    
    int choixLivre, choixAbonne;
    printf("\nNuméro du livre à retourner : ");
    scanf("%d", &choixLivre);
    printf("Numéro de l'abonné : ");
    scanf("%d", &choixAbonne);
    vider_buffer();
    
    // Trouver le livre sélectionné
    BList livreSelect = bibliotheque;
    int compteur = 1;
    while (livreSelect != NULL && compteur < choixLivre) {
        if (livreSelect->book.disponibility == False) {
            compteur++;
        }
        if (compteur < choixLivre) {
            livreSelect = livreSelect->next;
        }
    }
    
    // Trouver l'abonné sélectionné
    SList abonneSelect = abonnes;
    compteur = 1;
    while (abonneSelect != NULL && compteur < choixAbonne) {
        abonneSelect = abonneSelect->next;
        compteur++;
    }
    
    if (livreSelect != NULL && abonneSelect != NULL) {
        abonneSelect->subscriber.giveback_book(&abonneSelect->subscriber, &livreSelect->book);
        printf("✓ Opération de retour effectuée.\n");
    } else {
        printf("✗ Sélection invalide.\n");
    }
}

void afficher_historique_abonne() {
    printf("\n--- HISTORIQUE D'UN ABONNE ---\n");
    
    if (is_empty_list(abonnes)) {
        printf("Aucun abonné enregistré.\n");
        return;
    }
    
    // Afficher les abonnés
    printf("Abonnés disponibles :\n");
    SList temp = abonnes;
    int i = 1;
    while (temp != NULL) {
        printf("%d. ", i);
        temp->subscriber.introduce_yourself(&temp->subscriber);
        temp = temp->next;
        i++;
    }
    
    int choix;
    printf("\nNuméro de l'abonné : ");
    scanf("%d", &choix);
    vider_buffer();
    
    // Trouver l'abonné sélectionné
    SList abonneSelect = abonnes;
    int compteur = 1;
    while (abonneSelect != NULL && compteur < choix) {
        abonneSelect = abonneSelect->next;
        compteur++;
    }
    
    if (abonneSelect != NULL) {
        printf("\nHistorique de %s %s :\n", 
               abonneSelect->subscriber.name, 
               abonneSelect->subscriber.surname);
        print_stack(abonneSelect->subscriber.history);
    } else {
        printf("✗ Abonné non trouvé.\n");
    }
}

void tester_pile() {
    printf("\n--- TEST DES FONCTIONS DE PILE ---\n");
    
    Stack pileTest = new_stack();
    int choix;
    
    do {
        printf("\nMenu Pile :\n");
        printf("1. Créer une nouvelle pile\n");
        printf("2. Vérifier si la pile est vide\n");
        printf("3. Empiler un élément\n");
        printf("4. Dépiler un élément\n");
        printf("5. Afficher la pile\n");
        printf("6. Vider la pile\n");
        printf("7. Rechercher un ISBN dans la pile\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        vider_buffer();
        
        switch(choix) {
            case 1:
                pileTest = new_stack();
                printf("✓ Nouvelle pile créée.\n");
                break;
                
            case 2:
                if (is_empty_stack(pileTest)) {
                    printf("La pile est vide.\n");
                } else {
                    printf("La pile n'est pas vide.\n");
                }
                break;
                
            case 3: {
                // Créer un livre pour la pile
                Book livrePile;
                printf("Titre du livre : ");
                char titre[33];
                scanf("%32s", titre);
                strcpy(livrePile.title, titre);
                
                printf("Auteur : ");
                char auteur[15];
                scanf("%14s", auteur);
                strcpy(livrePile.autor, auteur);
                
                printf("ISBN : ");
                scanf("%d", &livrePile.ISBN);
                vider_buffer();
                
                printf("Année : ");
                scanf("%d", &livrePile.pubYear);
                vider_buffer();
                
                livrePile.disponibility = True;
                livrePile.init_book = init;
                livrePile.set_disponibility = set_disp;
                livrePile.info = book_info;
                livrePile.is_available = get_available;
                
                printf("Type de transaction (1: Emprunt, 2: Retour) : ");
                int type;
                scanf("%d", &type);
                vider_buffer();
                
                Transaction trans = (type == 1) ? borrow : revert;
                pileTest = push_stack(pileTest, &livrePile, trans);
                printf("✓ Élément empilé.\n");
                break;
            }
                
            case 4:
                if (is_empty_stack(pileTest)) {
                    printf("La pile est vide, impossible de dépiler.\n");
                } else {
                    pileTest = pop_stack(pileTest);
                    printf("✓ Élément dépilé.\n");
                }
                break;
                
            case 5:
                printf("Contenu de la pile :\n");
                print_stack(pileTest);
                break;
                
            case 6:
                while (!is_empty_stack(pileTest)) {
                    pileTest = pop_stack(pileTest);
                }
                printf("✓ Pile vidée.\n");
                break;
                
            case 7: {
                if (is_empty_stack(pileTest)) {
                    printf("La pile est vide.\n");
                } else {
                    int isbn;
                    printf("ISBN à rechercher : ");
                    scanf("%d", &isbn);
                    vider_buffer();
                    
                    if (contains(pileTest, isbn)) {
                        printf("✓ ISBN %d trouvé dans la pile.\n", isbn);
                    } else {
                        printf("✗ ISBN %d non trouvé.\n", isbn);
                    }
                }
                break;
            }
                
            case 0:
                // Libérer la pile avant de quitter
                while (!is_empty_stack(pileTest)) {
                    pileTest = pop_stack(pileTest);
                }
                break;
                
            default:
                printf("Choix invalide.\n");
        }
    } while(choix != 0);
}

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
