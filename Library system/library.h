#if !defined(__LIBRARY_H__)
#define __LIBRARY_H__

/**
 * @file library.h
 * @brief Fichier d'en-tête pour la gestion d'une bibliothèque.
 * 
 * Ce fichier définit les structures et fonctions nécessaires pour gérer des livres,
 * des abonnés, des historiques de transactions via des piles, et des listes de livres
 * et d'abonnés. Il utilise une approche orientée objet en C via des pointeurs de fonctions.
 * 
 * @author [KENMOE KEMGANG Marc Bertrand]
 * @date [20 Janvier 2025]
 * @version 1.1
 */

//---------------------------------------------------------------------------------------------
// Fichier d'en-tête pour une bibliothèque de gestion de bibliothèque (library management system).
// Ce fichier définit des types énumérés, des structures de données pour les livres, abonnés,
// piles pour l'historique des transactions, et listes chaînées pour stocker des livres et abonnés.
// Il inclut également des prototypes de fonctions pour manipuler ces structures.
// 
// Conseils d'analyse :
// - Ce code utilise des typedefs pour simplifier les noms de types.
// - Les structures incluent des pointeurs de fonctions pour simuler un comportement objet-oriented en C.
// - Les listes et piles sont implémentées comme des listes chaînées simples (singly linked lists).
// - Potentiels améliorations : Ajouter des checks pour NULL pointers dans les fonctions pour éviter les crashes.
// - Erreurs potentielles : Pas de gestion de mémoire explicite (e.g., malloc/free), assume que l'utilisateur gère ça.
// - Style : Utilise des noms en snake_case, cohérent mais pourrait être amélioré avec des préfixes pour éviter les conflits.
//---------------------------------------------------------------------------------------------

//---------------------------------------------Bool-Enum---------------------------------------//
/**
 * @enum Boolean
 * @brief Type énuméré représentant les valeurs booléennes.
 * 
 * Utilisé pour des flags comme la disponibilité d'un livre.
 * - False : Valeur fausse (équivalente à 0).
 * - True : Valeur vraie (équivalente à 1).
 * 
 * @note En C standard, on pourrait utiliser <stdbool.h>, mais ceci est une implémentation personnalisée.
 */
typedef enum Boolean {
    False,  /**< Valeur fausse (0). */
    True    /**< Valeur vraie (1). */
} Boolean;

//---------------------------------------------Op-Enum---------------------------------------//
/**
 * @enum Transaction
 * @brief Type énuméré pour les types de transactions sur les livres.
 *
 * - borrow : Emprunt d'un livre par l'abonné.
 * - revert : Retour d'un livre à la bibliothèque retour.
 * 
 * @note Utilisé dans l'historique des abonnés pour tracer les opérations.
 */
typedef enum transaction {
    borrow,  /**< Transaction d'emprunt par l'abonné. */
    revert      /**< Transaction de retour. */
} Transaction;

//-----------------------------------------------BOOK-----------------------------------------//
/**
 * @struct Book
 * @brief Structure représentant un livre dans la bibliothèque.
 * 
 * Contient les informations sur un livre et des pointeurs vers des fonctions (méthodes) pour
 * simuler un comportement objet-oriented.
 * 
 * @var Book::title
 * Titre du livre (chaîne de caractères, max 32 + '\0').
 * 
 * @var Book::autor
 * Nom de l'auteur (max 14 + '\0').
 * 
 * @var Book::ISBN
 * Numéro ISBN unique.
 * 
 * @var Book::pubYear
 * Année de publication.
 * 
 * @var Book::disponibility
 * Disponibilité du livre (True si disponible).
 * 
 * @var Book::init_book
 * Pointeur vers fonction d'initialisation.
 * 
 * @var Book::info
 * Pointeur vers fonction d'affichage des infos.
 * 
 * @var Book::set_disponibility
 * Pointeur vers fonction pour définir la disponibilité.
 * 
 * @var Book::is_available
 * Pointeur vers fonction pour vérifier la disponibilité.
 * 
 * @note Attention aux overflows de chaînes ; utiliser strncpy pour les copies.
 */
typedef struct Book Book;

/**
 * @typedef INIT_BOOK
 * @brief Type de pointeur vers fonction pour initialiser un livre.
 * @param book Pointeur vers le livre à initialiser.
 */
typedef void (*INIT_BOOK)(Book*);

/**
 * @typedef INFO
 * @brief Type de pointeur vers fonction pour afficher les infos d'un livre.
 * @param book Pointeur vers le livre.
 */
typedef void (*INFO)(Book*);

/**
 * @typedef SETDISP
 * @brief Type de pointeur vers fonction pour définir la disponibilité.
 * @param boolean Nouvelle valeur de disponibilité.
 * @param book Pointeur vers le livre.
 */
typedef void (*SETDISP)(Boolean, Book*);

/**
 * @typedef ISAVAILABLE
 * @brief Type de pointeur vers fonction pour vérifier la disponibilité.
 * @param book Pointeur vers le livre.
 */
typedef void (*ISAVAILABLE)(Book*);

typedef struct Book {
    char title[33];         /**< Titre du livre. */
    char autor[15];         /**< Nom de l'auteur. */
    int ISBN;               /**< Numéro ISBN. */
    int pubYear;            /**< Année de publication. */
    Boolean disponibility;  /**< Disponibilité. */
    INIT_BOOK init_book;    /**< Méthode d'initialisation. */
    INFO info;              /**< Méthode d'affichage. */
    SETDISP set_disponibility;  /**< Méthode pour setter disponibilité. */
    ISAVAILABLE is_available;   /**< Méthode pour checker disponibilité. */
} Book;

/**
 * @brief Initialise un livre et assigne ses méthodes.
 * @param book Pointeur vers le livre à initialiser.
 * 
 * Cette fonction assigne les pointeurs de fonctions et met des valeurs par défaut.
 */
void init(Book *book);

/**
 * @brief Affiche les informations d'un livre.
 * @param book Pointeur vers le livre.
 */
void book_info(Book *book);

/**
 * @brief Définit la disponibilité d'un livre.
 * @param boolean Nouvelle valeur (True/False).
 * @param book Pointeur vers le livre.
 */
void set_disp(Boolean boolean, Book *book);

/**
 * @brief Vérifie et potentiellement affiche la disponibilité d'un livre.
 * @param book Pointeur vers le livre.
 */
void get_available(Book *book);

//-----------------------------------------------Stack----------------------------------------//
/**
 * @struct StackElement
 * @brief Élément d'une pile pour l'historique des transactions.
 * 
 * @var StackElement::book
 * Livre associé.
 * 
 * @var StackElement::transaction
 * Type de transaction.
 * 
 * @var StackElement::next
 * Pointeur vers l'élément suivant.
 * 
 * @note Pile LIFO pour historique.
 */
typedef struct StackElement {
    Book book;                  /**< Livre de la transaction. */
    Transaction transaction;    /**< Type de transaction. */
    struct StackElement *next;  /**< Élément suivant. */
} StackElement, *Stack;

/**
 * @brief Vérifie si la pile est vide.
 * @param stack La pile.
 * @return True si vide, False sinon.
 */
Boolean is_empty_stack(Stack stack);

/**
 * @brief Crée une nouvelle pile vide.
 * @return Pointeur vers la pile vide (NULL).
 */
Stack new_stack(void);

/**
 * @brief Ajoute un élément au sommet de la pile.
 * @param stack Pile actuelle.
 * @param book Livre à ajouter.
 * @param transaction Type de transaction.
 * @return Nouvelle pile avec l'élément ajouté.
 * 
 * @note Alloue de la mémoire ; gérer avec malloc.
 */
Stack push_stack(Stack stack, Book *book, Transaction transaction);

/**
 * @brief Vide la pile et libère la mémoire.
 * @param stack Pile à vider.
 * @return Pile vide (NULL).
 */
Stack clear_stack(Stack stack);

/**
 * @brief Retire l'élément du sommet.
 * @param stack Pile actuelle.
 * @return Pile sans le sommet.
 * 
 * @note Libère la mémoire de l'élément retiré.
 */
Stack pop_stack(Stack stack);

/**
 * @brief Affiche le contenu de la pile.
 * @param stack La pile.
 */
void print_stack(Stack stack);

/**
 * @brief Vérifie si un ISBN est présent dans la pile.
 * @param stack La pile.
 * @param ISBN ISBN à chercher.
 * @return True si trouvé, False sinon.
 */
Boolean contains(Stack stack, int ISBN);

//---------------------------------------------SUSCRIBERS-------------------------------------//
/**
 * @struct Subscriber
 * @brief Structure représentant un abonné.
 * 
 * @var Subscriber::name
 * Prénom.
 * 
 * @var Subscriber::surname
 * Nom de famille.
 * 
 * @var Subscriber::id
 * ID unique.
 * 
 * @var Subscriber::history
 * Historique des transactions (pile).
 * 
 * @var Subscriber::init
 * Méthode d'initialisation.
 * 
 * @var Subscriber::introduce_yourself
 * Méthode de présentation.
 * 
 * @var Subscriber::borrow_book
 * Méthode d'emprunt.
 * 
 * @var Subscriber::giveback_book
 * Méthode de retour.
 */
typedef struct Subscriber Subscriber;

/**
 * @typedef INIT
 * @brief Pointeur vers fonction d'initialisation d'abonné.
 * @param subscriber Pointeur vers l'abonné.
 */
typedef void (*INIT)(Subscriber*);

/**
 * @typedef INTRODUCE
 * @brief Pointeur vers fonction de présentation.
 * @param subscriber Pointeur vers l'abonné.
 */
typedef void (*INTRODUCE)(Subscriber*);

/**
 * @typedef BORROW
 * @brief Pointeur vers fonction d'emprunt.
 * @param subscriber Abonné.
 * @param book Livre.
 */
typedef void (*BORROW)(Subscriber*, Book*);

/**
 * @typedef GIVEBACK
 * @brief Pointeur vers fonction de retour.
 * @param subscriber Abonné.
 * @param book Livre.
 */
typedef void (*GIVEBACK)(Subscriber*, Book*);

typedef struct Subscriber {
    char name[15];          /**< Prénom. */
    char surname[15];       /**< Nom de famille. */
    int id;                 /**< ID unique. */
    Stack history;          /**< Historique. */
    INIT init;              /**< Initialisation. */
    INTRODUCE introduce_yourself;  /**< Présentation. */
    BORROW borrow_book;     /**< Emprunt. */
    GIVEBACK giveback_book; /**< Retour. */
} Subscriber;

/**
 * @brief Initialise un abonné.
 * @param subscriber Pointeur vers l'abonné.
 */
void init_subscriber(Subscriber *subscriber);

/**
 * @brief Présente l'abonné.
 * @param subscriber Pointeur vers l'abonné.
 */
void introduce(Subscriber *subscriber);

/**
 * @brief Gère l'emprunt d'un livre.
 * @param subscribe Abonné (note : typo dans le param, devrait être subscriber).
 * @param book Livre.
 * 
 * @note Met à jour l'historique et la disponibilité.
 */
void borrow(Subscriber *subscribe, Book *book);

/**
 * @brief Gère le retour d'un livre.
 * @param subscribe Abonné (typo similaire).
 * @param book Livre.
 */
void give_back(Subscriber *subscribe, Book *book);

//---------------------------------------------BOOK_List----------------------------------------//
/**
 * @struct BookList
 * @brief Élément d'une liste chaînée de livres.
 * 
 * @var BookList::book
 * Livre stocké.
 * 
 * @var BookList::next
 * Élément suivant.
 */
typedef struct BookList {
    Book book;                  /**< Livre. */
    struct BookList *next;      /**< Suivant. */
} BookList, *BList;

/**
 * @brief Crée une nouvelle liste de livres vide.
 * @return Liste vide (NULL).
 */
BList new_list_b();

/**
 * @brief Vérifie si la liste est vide.
 * @param list La liste.
 * @return True si vide.
 */
Boolean is_empty_list_b(BList list);

/**
 * @brief Retourne la taille de la liste.
 * @param list La liste.
 * @return Nombre d'éléments.
 */
int list_size_b(BList list);

/**
 * @brief Affiche la liste de livres.
 * @param list La liste.
 */
void print_list_b(BList list);

/**
 * @brief Cherche un livre par ISBN.
 * @param list La liste.
 * @param ISBN ISBN à chercher.
 * @return True si trouvé.
 */
Boolean searchBook_b(BList list, int ISBN);

/**
 * @brief Ajoute un livre à la fin.
 * @param list Liste actuelle.
 * @param book Livre à ajouter.
 * @return Nouvelle liste.
 */
BList add_last_b(BList list, Book *book);

/**
 * @brief Ajoute un livre au début.
 * @param list Liste actuelle.
 * @param book Livre à ajouter.
 * @return Nouvelle liste.
 */
BList add_first_b(BList list, Book *book);

/**
 * @brief Retire le dernier élément.
 * @param list Liste actuelle.
 * @return Liste mise à jour.
 */
BList remove_last_b(BList list);

/**
 * @brief Retire le premier élément.
 * @param list Liste actuelle.
 * @return Liste mise à jour.
 */
BList remove_first_b(BList list);

/**
 * @brief Vide la liste et libère la mémoire.
 * @param list Liste à vider.
 */
void clear_list_b(BList list);

//-----------------------------------------SUBSLIST-----------------------------------------//
/**
 * @struct SubsList
 * @brief Élément d'une liste chaînée d'abonnés.
 * 
 * @var SubsList::subscriber
 * Abonné stocké.
 * 
 * @var SubsList::next
 * Élément suivant.
 */
typedef struct SubsList {
    Subscriber subscriber;          /**< Abonné. */
    struct SubsList *next;          /**< Suivant. */
} SubsList, *SList;

/**
 * @brief Vérifie si la liste est vide.
 * @param list La liste.
 * @return True si vide.
 */
Boolean is_empty_list(SList list);

/**
 * @brief Crée une nouvelle liste d'abonnés vide.
 * @return Liste vide (NULL).
 */
SList new_subList();

/**
 * @brief Retourne la taille de la liste.
 * @param list La liste.
 * @return Nombre d'éléments.
 */
int list_size(SList list);

/**
 * @brief Affiche la liste d'abonnés.
 * @param list La liste.
 */
void print_list(SList list);

/**
 * @brief Cherche un abonné par ID.
 * @param list La liste.
 * @param id ID à chercher.
 * @return True si trouvé.
 */
Boolean searchSubs(SList list, int id);

/**
 * @brief Ajoute un abonné à la fin.
 * @param list Liste actuelle.
 * @param subscriber Abonné à ajouter.
 * @return Nouvelle liste.
 */
SList add_last(SList list, Subscriber *subscriber);

/**
 * @brief Ajoute un abonné au début.
 * @param list Liste actuelle.
 * @param subscriber Abonné à ajouter.
 * @return Nouvelle liste.
 */
SList add_first(SList list, Subscriber *subscriber);

/**
 * @brief Retire le dernier élément.
 * @param list Liste actuelle.
 * @return Liste mise à jour.
 */
SList remove_last(SList list);

/**
 * @brief Retire le premier élément.
 * @param list Liste actuelle.
 * @return Liste mise à jour.
 */
SList remove_first(SList list);

/**
 * @brief Vide la liste et libère la mémoire.
 * @param list Liste à vider.
 */
void clear_list(SList list);

#endif // __LIBRARY_H__
