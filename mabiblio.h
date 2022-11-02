//
// Created by denis on 02/11/2022.
//

#ifndef ECECITY_MABIBLIO_H
#define ECECITY_MABIBLIO_H

#include <stdlib.h>
#include <stdio.h>
#include "allegro.h"
#include <allegro.h>
#include <winalleg.h>
#include <tchar.h>
#include <stdio.h>
#include <commdlg.h>
#include <string.h>
#include <direct.h>
#include <time.h>

/////////////////define.h////////////////////////
/********************************/

typedef struct id
{
    int caseX;
    int caseY;
}t_id;

typedef struct fournisseur
{
    int qte_eau_distribuee;
    t_id id_fournisseur;
}t_fournisseur;

/********************************/

#define GAME_W 901
#define GAME_H 701

#define TAILLE_FENETRE_W 1024
#define TAILLE_FENETRE_H 768

#define TAILLE_POLICE 10

#define GAME_POSX 112
#define GAME_POSY 56

#define NB_CASES_LIG 35
#define NB_CASES_COL 45

#define TAILLE_CASE 20

#define TAILLE_CHAINE 256

#define CAPACITE_CHATEAU 5000
#define CAPACITE_CENTRALE 5000

#define PROBABILITE_INCENDIE 2000
#define DUREE_INCENDIE 250

#define PROTEGEE 1
#define PAS_PROTEGEE 0

#define COUT_ROUTE 10
#define COUT_HABITATION 1000
#define COUT_CENTRALE 100000
#define COUT_CHATEAU 100000
#define COUT_CASERNE 150000

#define PAUSE_DESACTIVEE 0
#define PAUSE_ACTIVEE 1

#define PAS_DU_TIMER 0.1

#define CHARGER -1

#define RAYON_INFLUENCE_CASERNE 20

#define FOURNISSEUR_MAX 5

#define ARGENT_INITIAL 500000

#define IMPOTS_PAR_HABITANT 10

#define MODE_COMMUNISTE 0
#define MODE_CAPITALISTE 1

#define VIDE 0
#define ROUTE 1
#define HABITATION 2
#define CENTRALE 3
#define CHATEAU 4
#define CASERNE 5

#define HABITATION_H 3
#define HABITATION_W 3

#define CHATEAU_H 6
#define CHATEAU_W 4

#define CASERNE_H 4
#define CASERNE_W 6

#define CENTRALE_H 6
#define CENTRALE_W 4

#define INFINI 10000

#define EN_FEU 1
#define PAS_EN_FEU 0

#define DUREE_CYCLE 15

#define TAILLE_INITIALE_COLLECTION 10

#define NB_HABITANTS_RUINE 0
#define NB_HABITANTS_TERRAIN_VAGUE 0
#define NB_HABITANTS_CABANE 10
#define NB_HABITANTS_MAISON 50
#define NB_HABITANTS_IMMEUBLE 100
#define NB_HABITANTS_GRATTECIEL 1000

#define STADE_RUINE 0
#define STADE_TERRAIN_VAGUE 1
#define STADE_CABANE 2
#define STADE_MAISON 3
#define STADE_IMMEUBLE 4
#define STADE_GRATTECIEL 5

#define NB_IMG_ROUTES 11
#define NB_IMG_CABANES 2
#define NB_IMG_MAISONS 2
#define NB_IMG_IMMEUBLES 2
#define NB_IMG_GRATTECIELS 2

#define NIVEAU_SOL 0
#define NIVEAU_EAU 1
#define NIVEAU_ELEC 2

#define NB_NIVEAUX 3

#define BOUTON_AJOUTER_ROUTE 0
#define BOUTON_AJOUTER_HABITATION 1
#define BOUTON_AJOUTER_CHATEAU 2
#define BOUTON_AJOUTER_CENTRALE 3
#define BOUTON_AJOUTER_CASERNE 4
#define BOUTON_NIVEAU_SOL 5
#define BOUTON_NIVEAU_EAU 6
#define BOUTON_NIVEAU_ELEC 7
#define BOUTON_PAUSE 8
#define BOUTON_SAUVEGARDER 9

#define TYPE_ROUTE_VERTICALE 0
#define TYPE_ROUTE_HORIZONTALE 1
#define TYPE_ROUTE_BAS_GAUCHE 2
#define TYPE_ROUTE_BAS_DROITE 3
#define TYPE_ROUTE_HAUT_GAUCHE 4
#define TYPE_ROUTE_HAUT_DROITE 5
#define TYPE_ROUTE_DROITE_BAS_HAUT 6
#define TYPE_ROUTE_GAUCHE_BAS_HAUT 7
#define TYPE_ROUTE_GAUCHE_DROITE_HAUT 8
#define TYPE_ROUTE_GAUCHE_DROITE_BAS 9
#define TYPE_ROUTE_INTERSECTION 10

/************************************************/

/////////////////liste_generique_simple_chainage.h////////////////////////
// Ceci est un module de liste générique, à simple chainage et double ancrage.

// Pour l'utiliser correctement, il faut juste appeler les fonctions listées ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements à effectuer sur les éléments
// par exemple pour une liste chainée de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

// Attention, certaines fonctions nécessitent de recevoir une fonction en paramètre
// par exemple: void liste_afficher(t_liste* lst, tpf_afficher afficher);
// Il est logique que pour afficher chaque élément de la liste, il faut avoir une fonction qui se charge d'afficher 1 élément.
// Cette fonction doit être transmise en paramètre.
// L'appel à liste_afficher pour afficher des points par exemple sera:
// liste_afficher(maliste, (tpf_afficher)point_afficher);
// avec point_afficher le nom de la fonction qui affiche 1 point.
// dont le prototype serait par exemple:
// void point_afficher(t_point* p);

/*
Par rapport à une liste simple chainage double ancrage, une liste double chainage double ancrage aurait permis:

- un accès à l'élément précédent efficace.
- une suppression en queue efficace.

*/

/// Définition des structures
typedef struct maillon
{
    void* elem;
    struct maillon* p_suiv;
}t_maillon;

typedef struct liste
{
    int longueur;
    struct maillon* p_tete;
    struct maillon* p_queue;
    struct maillon* p_courant;
}t_liste;

/// Alias pour les pointeurs de fonction
typedef void  (*tpf_detruire) (void*);
typedef void* (*tpf_copier)   (void*);
typedef void  (*tpf_afficher) (void*);
typedef int   (*tpf_trier)    (const void*, const void*);
typedef int   (*tpf_recherche)(void*);

/// Prototypes

// Constructeur
t_liste* liste_creer();

// Destructeur
void liste_detruire(t_liste* lst, tpf_detruire detruire);

// Vider la liste sans la détruire
void liste_vider(t_liste* lst, tpf_detruire detruire);

// Constructeur par copie
t_liste* liste_copier(t_liste* lst, tpf_copier copier);

// Ajout d'élément en tête
void liste_ajout_tete(t_liste* lst, void* elem);

// Ajout d'élément en queue
void liste_ajout_queue(t_liste* lst, void* elem);

// Nombre d'éléments référencés
int liste_taille(t_liste* lst);

// Retourne 1 (Vrai) si la liste est vide
int liste_vide(t_liste* lst);

// Accès élément en tête
void* liste_elem_tete(t_liste* lst);

// Accès élément en queue
void* liste_elem_queue(t_liste* lst);

// Accès élément courant
void* liste_elem_courant(t_liste* lst);

// On retire la tête de la liste, et on retourne la donnée qu'elle pointait.
void* liste_recup_tete(t_liste* lst);

// On retire la queue de la liste, et on retourne la donnée qu'elle pointait.
// PAS EFFICACE ICI CAR SIMPLE CHAINAGE
void* liste_recup_queue(t_liste* lst);

// Supprime l'élément de tête
void liste_supprimer_tete(t_liste* lst, tpf_detruire detruire);

// Initialiser un parcours
void liste_demarrer(t_liste* lst);

// Il reste encore des éléments à parcourir
int liste_encore(t_liste* lst);

// Déplacement du courant au suivant
void liste_suivant(t_liste* lst);

// Affichage bilan allocations/libérations
void liste_bilan();

////////////////////////////////////////////////////////
/* Petites fonctions supplémentaires*/

// Affiche les éléments de la liste, dans l'ordre tete --> queue
void liste_afficher(t_liste* lst, tpf_afficher afficher);

// Ajoute lst2 à la suite (en queue) de lst1 (copie les éléments de lst2, et les rajoute à lst1.
// Lst2 garde ses élements (Lst2 reste inchangée)
void liste_fusionner(t_liste* lste1, t_liste* lste2, tpf_copier copier);

// Supprime l'élément de queue de la liste (PAS EFFICACE CAR SIMPLE CHAINAGE ICI)
void liste_supprimer_queue(t_liste* lst, tpf_detruire detruire);

// Trie les élements d'une liste, en fonction du résultat retourné par la fonction de comparaison des élements
// on évitera de trier tout le temps, on préférera l'ajout trié.
void liste_trier(t_liste* lst, tpf_trier trier);

// ajout trié dans la liste ( = ajout à la bonne position selon une fonction de comparaison)
void liste_ajout_trie(t_liste* lst, void* elem, tpf_trier trier);

// Recherche dans la liste tous les maillons contenant les données demandées
// (via une fonction element_rechercher, qui analyse un maillon et dit si ce maillon est intéressant)
// Afin de gérer le cas où plusieurs élements contiendraient les mêmes données
// -> on retourne une liste chainée de pointeurs sur éléments trouvés :)
// ATTENTION, la liste retournée est une liste de REFERENCES vers des éléments existant dans lst.
// les éléments de la liste retournée sont CEUX de lst.
// ce ne sont PAS des copies.
t_liste* liste_rechercher(t_liste* lst, tpf_recherche recherche);

// On recoit un élément forcément dans la liste, qu'on veut supprimer
// puis on parcourt la liste jusqu'à tomber dessus, et on le supprime, peu importe sa position (tete,milieu,queue)
void liste_supprimer_precis(t_liste* lst, void* elem, tpf_detruire detruire);

// On recoit la liste dont il faut supprimer certains éléments, et une liste référençant tous les éléments à supprimer.
// On va chercher les éléments de lst_elem_a_supprimer DANS lst, et quand on tombe dessus on les supprime.
void liste_supprimer_partie(t_liste* lst, t_liste* lst_elem_a_supprimer, tpf_detruire detruire);

// Supprime le maillon de tête de liste, sans détruire la donnée pointée
void liste_dereferencer_tete(t_liste* lst);

// Supprime tous les maillons de la liste, sans détruire les données pointées
void liste_dereferencer(t_liste* lst);

// Ajoute dans la liste l'élement à insérer juste avant l'élément de référence
void liste_ajout_avant(t_liste* lst, void* elem_a_inserer, void* elem_ref);

/*
Tester tous les scénarios

Résoudre problème qsort liste_trier
Ameliorer la fonction liste_rechercher : paramètre facultatif à rajouter
Coder liste_traiter_chaque
*/

/////////////////file.h////////////////////////
//#include "memcheck.h"

// Ceci est un module de file générique.

// Pour l'utiliser correctement, il faut juste appeler les fonctions listées ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements à effectuer sur les éléments
// par exemple pour une file de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

/*// Attention, certaines fonctions nécessitent de recevoir une fonction en paramètre
// par exemple: t_file* file_copier(t_file* file, tpf_copier copier);
// Il est logique que pour copier chaque élément de la file
// il faut avoir une fonction qui se charge de copier 1 élément.
// Cette fonction doit être transmise en paramètre.
// L'appel à file_copier sera donc par exemple:
// file_copier(mafile, (tpf_copier)point_copier);
// avec point_copier le nom de la fonction qui copie 1 point.
// dont le prototype serait par exemple:
// t_point* point_copier(t_point* p);
*/
// On crée un alias du type t_liste, c'est à dire qu'on le renomme en t_file pour une cohérence logique
// Ainsi l'utilisateur du module n'utilisera pas le type t_liste ni le mot "liste" dans son code.
typedef t_liste t_file;

// Alloue une file
t_file* file_creer();

// Détruit une file
void file_detruire(t_file* file, tpf_detruire detruire);

// Vide une file
void file_vider(t_file* file, tpf_detruire detruire);

// Enfile ( = ajoute ) un élément à la file
void file_enfiler(t_file* file, void* elem);

// Défile ( = retire ) un élément à la file
void* file_defiler(t_file* file);

// Retourne l'élément du sommet de la file, sans le retirer de la file
void* file_elem_sommet(t_file* file);

// Retourne 1 si la file est vide, 0 sinon
int file_vide(t_file* file);

// Retourne une copie (profonde) de la file reçue en paramètre
t_file* file_copier(t_file* file,tpf_copier copier);

// Retourne le nombre d'éléments de la file
int file_taille(t_file* file);

// Affichage bilan allocations/libérations
void file_bilan(t_file* file);

/////////////////file_explorer.h////////////////////////
#define TAILLE_BUFFER 1024

/// penser à linker libComdlg32.a dans le projet

/// Module permettant le choix d'un fichier à charger ou à sauvegarder via un explorateur de fichiers Windows.
/// Le contenu des fonctions qui obtiennent le chemin du fichier est majoritairement tiré d'un tutoriel de "fvirtman"
/// voir: http://fvirtman.free.fr/recueil/04_01_02_getopenfilename.c.php
/// Mon travail sur ces fonctions a permis de blinder la réussite de l'obtention du chemin.
/// Les fonctions qui blindent l'extension du fichier ont été entièrement codées par moi même.

// met le chemin du fichier choisi dans la chaine de caractères envoyée en paramètre
// s'assure qu'il n'y a pas une double extension dans le nom du fichier
// retourne un booléen correspondant à la réussite ou à l'échec du choix du fichier (pour savoir si l'utilisateur a annulé)
// informe l'utilisateur via un printf si le choix du fichier a été annulé
int obtenir_chemin_sauvegarde(char* chemin);

// met le chemin du fichier choisi dans la chaine de caractères envoyée en paramètre
// retourne un booléen correspondant à la réussite ou à l'échec du choix du fichier (pour savoir si l'utilisateur a annulé)
// informe l'utilisateur via un printf si le choix du fichier a été annulé
int obtenir_chemin_chargement(char* chemin);

// reçoit le chemin d'un fichier en parametre
// informe l'utilisateur via un printf de la validité de l'extension du fichier choisi, et retourne un booléen correspondant.
int verif_type_fichier(const char* chemin);

// retourne une chaine de caractères, allouée dynamiquement, contenant l'extension du fichier dont le chemin est passé en paramètre
char* return_extension_blindee(const char* chemin);

// sert à supprimer le point et ce qu'il y a après le point dans une chaine de caractère
// permet plusieurs choses:
// - d'écraser un fichier (car on choisit un fichier portant déjà l'extension .txt, mais dans le code on rajoute nous meme un .txt
// - de récupérer un nom de fichier convenable si jamais l'utilisateur tapait comme nom de fichier à créer: "dessin.txt", alors qu'il devrait plutot logiquement taper "dessin"
void supprimer_contenu_chaine_apres_point(char* chemin);

// remplit le chemin, retourne 0 si il y a eu un problème
int remplit_chemin_sauvegarde(char* chemin);

// remplit le chemin, retourne 0 si il y a eu un problème
int remplit_chemin_chargement(char* chemin);

// à partir d'un chemin, récupère le nom du fichier choisi
void recup_nom_fichier(const char* chemin, char* nom);

/////////////////case.h////////////////////////
typedef struct kase
{
    int type;
    void* elem;
}t_case;

void case_vider(t_case*);

int case_libre(t_case*);

t_case* case_allouer();

void case_free(t_case*);

void case_remplir(t_case*, int, void*);

/////////////////boitaoutil.h////////////////////////
//géométrie de la boite

#define COORDX 10
#define COORDY 56
#define LARGEUR_CASE 50
#define TAILLE_BORDS 2
#define NB_BOUTONS_H 10
#define NB_BOUTONS_W 1
//#define NB_BOUTONS 5
#define COUL_BORD makecol(140,140,140)
#define COUL_FOND makecol(180,180,180)

typedef struct boiteaoutils
{
    int x; //coordonnées d'affichage de la boite à outils
    int y; //coordonnées d'affichage de la boite à outils
    int bouton_choisi;
    int matbouton[NB_BOUTONS_H][NB_BOUTONS_W];
    BITMAP *img_bouton_off[NB_BOUTONS_H][NB_BOUTONS_W];
    BITMAP *img_bouton_on[NB_BOUTONS_H][NB_BOUTONS_W];
}t_boite_a_outils;

t_boite_a_outils* boiteaoutils_creer();

void boiteaoutils_reinitialiser_boutons_uniques(t_boite_a_outils* boiteaoutils);

void boiteaoutils_chargerimages(t_boite_a_outils* boiteaoutils);

void boiteaoutils_afficher(t_boite_a_outils* boiteaoutils);

void boiteaoutils_gerer(t_boite_a_outils* boiteaoutils);

void boiteaoutils_liberer(t_boite_a_outils* boiteaoutils);

/////////////////caserne.h////////////////////////
typedef struct caserne
{
    int case_de_referenceX;
    int case_de_referenceY;
    int temps_de_rechargement; // permettra de savoir si les pompiers sont disponibles
    int occupe; // permettra de savoir si les pompiers sont disponibles
} t_caserne;


t_caserne* caserne_creer();

void caserne_afficher(t_caserne* caserne,int niveau);

void caserne_liberer(t_caserne*);

int caserne_depassement_matrice(int colonne,int ligne);

int caserne_place_libre(int x,int y,t_case*** kase);

void caserne_placer(t_caserne* caserne,int x,int y,t_case*** kase);

/////////////////habitation.h////////////////////////
typedef struct habitation
{
    int stade;
    int case_de_referenceX;
    int case_de_referenceY;
    float chrono;
    int feu;
    int electricite;
    int protegee;
    int indice;
    int eau;
    t_id id_centrale_fournisseuse;
    t_fournisseur* chateaux_fournisseurs;
}t_habitation;

typedef struct capacite
{
    int capacite_max;
    int capacite_disponible;
}t_capacite;

void habitation_progression(t_habitation* habitation);

void habitation_regression(t_habitation* habitation);

t_habitation* habitation_creer();

int habitation_place_libre(int,int,t_case***);

void habitation_placer(t_habitation*,int,int,t_case***);

void habitation_actualiser_timer(t_habitation* habitation);

int habitation_depassement_matrice(int colonne,int ligne);

int habitation_nbhabitants(t_habitation* habitation);

void habitation_liberer(t_habitation*);

int habitation_comparer(const void* a, const void* b);

void habitation_afficher(t_habitation* hab,int niveau);

int habitation_recolter_impots(t_habitation* hab);

void habitation_evoluer(t_habitation* habitation,int mode,int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateau,int* capacite_centrale);

void habitation_evolution_communiste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale);

void habitation_evolution_capitaliste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales);

void habitation_debut_tour(t_habitation* hab);

void habitation_sauvegarder(t_habitation* hab, FILE* fp);

void habitation_charger(t_habitation* hab, FILE* fp);

/////////////////centrale.h////////////////////////
typedef struct centrale
{
    t_capacite capacite;
    int case_de_referenceX;
    int case_de_referenceY;
    t_id id_centrale;
}t_centrale;

t_centrale* centrale_creer();

void centrale_liberer(t_centrale*);

int centrale_depassement_matrice(int colonne,int ligne);

void centrale_distribuer(t_centrale* centrale,t_habitation* habitation,int quantitee);

int centrale_place_libre(int x,int y,t_case*** kase);

void centrale_placer(t_centrale* centrale,int x,int y,t_case*** kase);

void centrale_afficher(t_centrale* centrale,int niveau);

void centrale_debut_tour(t_centrale* centrale);

int centrale_elec_disponible(t_centrale* centrale);

/////////////////chateau.h////////////////////////
typedef struct chateau
{
    t_capacite capacite;
    int case_de_referenceX;
    int case_de_referenceY;
    t_id id_chateau;
}t_chateau;

t_chateau* chateau_creer();

void chateau_liberer(t_chateau*);

int chateau_depassement_matrice(int colonne,int ligne);

int chateau_place_libre(int x,int y,t_case*** kase);

void chateau_placer(t_chateau* chateau,int x,int y,t_case*** kase);

void chateau_afficher(t_chateau* chateau,int niveau);

int chateau_distribuer(t_chateau* chateau,t_habitation* habitation);

void chateau_debut_tour(t_chateau* chateau);

int chateau_eau_disponible(t_chateau* chateau);

/////////////////collection_habitations.h////////////////////////
typedef struct collection_habitation
{
    t_habitation** habitation;
    int taille_actuelle;
    int taille_max;
}t_collection_habitation;

t_collection_habitation* collection_habitation_creer();

void collection_habitation_trier(t_collection_habitation* collection_habitation);

void collection_habitation_actualiser_timer(t_collection_habitation* collection_habitation);

void collection_habitation_ajouter_habitation(t_collection_habitation* collection_habitation,t_habitation* habitation);

void collection_habitation_reallouer(t_collection_habitation* collection_habitation);

void collection_habitation_afficher(t_collection_habitation* collection_habitation,int niveau);

void collection_habitation_liberer(t_collection_habitation* collection_habitation);

void collection_habitation_debut_tour(t_collection_habitation* collection_habitation, int* nb_habitants);

void collection_habitation_evolution(t_collection_habitation* collection_habitation,int mode, int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale);

int collection_habitation_nombre_habitants(t_collection_habitation* collection_habitation);

/////////////////BFS.h////////////////////////
typedef struct bfs
{
    int ordre;
    int case_de_referenceX;
    int case_de_referenceY;

}t_bfs;

int* recherchepluscourtchemin(t_bfs* bfs,t_case*** kase);

void tester_voisins(t_case*** kase,int ligne,int colonne,int* longueurs,int marque[NB_CASES_LIG][NB_CASES_COL],t_file* file);

/////////////////collection_casernes.h////////////////////////
typedef struct collection_casernes
{
    t_caserne** caserne;
    int taille_actuelle;
    int taille_max;
}t_collection_casernes;


t_collection_casernes* collection_casernes_creer();

void collection_casernes_ajouter_caserne(t_collection_casernes* collection_casernes,t_caserne* caserne);

void collection_casernes_reallouer(t_collection_casernes* collection_casernes);

void collection_casernes_afficher(t_collection_casernes* collection_casernes,int niveau);

void collection_casernes_liberer(t_collection_casernes* collection_casernes);

void collection_casernes_proteger(t_collection_casernes* collection_casernes,t_collection_habitation* collection_habitation,int** longueurs);

int** collection_casernes_tableau_longueurs(t_collection_casernes* collection_casernes,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation);

/////////////////collection_centrales.h////////////////////////
typedef struct collection_centrale
{
    t_centrale** centrale;
    int taille_actuelle;
    int taille_max;
}t_collection_centrale;

t_collection_centrale* collection_centrale_creer();

void collection_centrale_ajouter_centrale(t_collection_centrale* collection_centrale,t_centrale* centrale);

void collection_centrale_reallouer(t_collection_centrale* collection_centrale);

void collection_centrale_afficher(t_collection_centrale* collection_centrale,int niveau_de_visualisation);

void collection_centrale_liberer(t_collection_centrale* collection_centrale);

void collection_centrale_distribuer(t_collection_centrale* collection_centrale,t_collection_habitation* collection_habitation,int** longueurs);

int** collection_centrale_tableau_longueurs(t_collection_centrale* collection_centrale,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation);

void collection_centrale_debut_tour(t_collection_centrale* collection_centrale);

int collection_centrale_elec_disponible(t_collection_centrale* collection_centrale);

int* collection_centrale_tableau_capacite(t_collection_centrale* collection_centrale);

/////////////////collection_chateau.h////////////////////////
typedef struct collection_chateau
{
    t_chateau** chateau;
    int taille_actuelle;
    int taille_max;
}t_collection_chateau;

t_collection_chateau* collection_chateau_creer();


void collection_chateau_distribuer_proche(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs);

void collection_chateau_distribuer(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs_chateaux_habitations);

void collection_chateau_distribuer_minimiser(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueur);

void collection_chateau_debut_tour(t_collection_chateau* collection_chateau);

int collection_chateau_eau_disponible(t_collection_chateau* collection_chateau);

/////////////////compalleg.h////////////////////////
/// Constantes

// Couleur initiale :
// 255,255,255 pour du blanc    0,0,0 pour du noir...
#define PAGE_COULEUR_INIT makecol(0,0,0)


/// Variables globales : visibles partout où compalleg.h est inclus

// Le buffer sur lequel tout est dessiné
extern BITMAP *page;

// Couleur de fond du buffer page, modifiable à tout moment
// Exemple   page_couleur_fond = makecol( 0, 255, 0); // fond vert !
extern int page_couleur_fond;

/// Les globales suivantes nécessitent un appel à rafraichir_clavier_souris
/// en début de boucle d'interaction pour être mises à jour à chaque tour de boucle

// La touche appuyée depuis le dernier tour de boucle
// '\0' si aucun bouton appuyé au dernier tour de boucle
extern char touche;

// Le bouton souris appuyé depuis le dernier tour de boucle
// 'g' pour gauche, 'd' pour droit, 'm' pour milieu, '\0' pour aucun
extern char bouton;

// Le clic souris depuis le dernier tour de boucle
// s'utilise comme mouse_b mais contrairement à mouse_b
// n'est valable que pendant un tour de boucle (pas de répétition)
// mouse_click&1 pour clic gauche, mouse_click&2 pour clic droit
extern int mouse_click;

// Le relâchement du clic souris depuis le dernier tour de boucle
// détecte le passage de l'état enfoncé à l'état relâché
// n'est valable que pendant un tour de boucle (pas de répétition)
// mouse_unclick&1 pour clic gauche, mouse_unclick&2 pour clic droit
extern int mouse_unclick;

// Même principe que key mais détecte les transitions (pressé<->non pressé)
// valable pendant un seul tour de boucle (pas de répétition)
// exemple : if (key_unpress[KEY_RIGHT]) printf("touche droite relachee !\n");
extern int key_press[KEY_MAX];
extern int key_unpress[KEY_MAX];

// Déplacement relatif de la souris depuis le dernier tour de boucle
extern int mouse_depx;
extern int mouse_depy;

/// Lancement et fermeture services Allegro

// A appeler une fois et une seule en début de main (après les déclarations)
void initialiser_allegro(int w, int h);

// Pour libérer le buffer et fermer tous les services
// pas indispensable : la fin du programme ferme et libère tout automatiquement
void fermer_allegro();


/// Buffer et sorties graphiques

// Efface le buffer (utilise page_couleur_fond)
// A appeler une fois dans la boucle d'interaction
// avant de redessiner le dessin (et éventuellement
// autre chose après)
void effacer_page();

// Affiche la page effectivement à l'écran
// A appeler une fois dans la boucle d'interaction
// A LA FIN JUSTE AVANT rest(10);
void afficher_page();

// Même procédure que line pour allegro, 3 pixels de large
void line_epaisse(BITMAP *bmp, int x1, int y1, int x2, int y2, int coul);

BITMAP *chargerImage(const char* nomFichierImage);

void changer_nom_fenetre(const char* ch);

SAMPLE* chargerSon(const char* nomfichier);

/// Entrées clavier/souris

// un appel à rafraichir_clavier_souris doit être fait
// en début de boucle d'interaction pour mettre à jour les globales
void rafraichir_clavier_souris();

/////////////////date.h////////////////////////
typedef struct date
{
    double secondes;
    int minutes;
    int heures;
} t_date;

t_date* date_allouer();

void date_actualiser(t_date* date);

void date_liberer(t_date* date);

/////////////////ville.h////////////////////////
typedef struct ville
{
    t_case*** terrain;

    t_collection_habitation* collec_habitations;
    t_collection_chateau* collec_chateaux;
    t_collection_centrale* collec_centrales;
    t_collection_casernes* collec_casernes;

    t_date* temps_de_jeu;
    int argent;
    int nb_habitants;
    t_capacite qte_eau;
    t_capacite qte_elec;
    clock_t timer;
    int pause;
    int niveau_visualisation;
    int mode;

    t_bfs data_bfs;
} t_ville;

void afficher_utilisations(t_ville* v);

void ville_afficher(t_ville* v, int bouton_boite_a_outil);

void ville_gerer(t_ville* v, int bouton_boite_a_outil);

t_ville* ville_allouer_initialiser(int mode_de_jeu);

void ville_charger(const char* nom_fichier,t_ville* v);

void ville_actualiser_timer(t_ville* v);

void ville_liberer(t_ville* v);

void ville_gerer_actions_utilisateur(t_ville* v, int bouton_boite_a_outils);

/////////////////editeur.h////////////////////////
typedef struct editeur
{
    t_ville* maville;
    t_boite_a_outils* boite_a_outils;
} t_editeur;

t_editeur* editeur_allouer(int mode_de_jeu);

void editeur_gerer(t_editeur* ed);

void editeur_afficher(t_editeur* ed);

void editeur_liberer(t_editeur* ed);



/////////////////graphisme.h////////////////////////
/// ne contient que les images du jeu, PAS du menu NI de la boite à outils
typedef struct graphismes
{
    BITMAP* buffer_ville;
    BITMAP* fond_herbe;
    BITMAP* grille;

    BITMAP* route[NB_NIVEAUX][NB_IMG_ROUTES];

    BITMAP* terrain_vague;
    BITMAP* ruine;
    BITMAP* pompier;

    BITMAP* cabane[NB_IMG_CABANES];
    BITMAP* maison[NB_IMG_MAISONS];
    BITMAP* immeuble[NB_IMG_IMMEUBLES];
    BITMAP* gratte_ciel[NB_IMG_GRATTECIELS];

    BITMAP* chateau;
    BITMAP* centrale;
    BITMAP* caserne;
}t_graphismes;

extern t_graphismes* graphs;

t_graphismes* graphismes_charger();

void graphismes_liberer(t_graphismes* graph);





/////////////////menu.h////////////////////////
#define NB_BOUTONS 5

#define MENU_BOUTON_NOUVEAU 0
#define MENU_BOUTON_CHARGER 1
#define MENU_BOUTON_CREDITS 2
#define MENU_BOUTON_QUITTER 3
#define MENU_BOUTON_RETOUR 4

#define NB_BOUTONS_SOUS_MENU 2
#define NB_IMG_OISEAU 15
#define SOUS_MENU_COMMUNISTE 0
#define SOUS_MENU_CAPITALISTE 1

typedef struct graphsousMenu
{
    BITMAP* img_boutons_on[NB_BOUTONS_SOUS_MENU];
    BITMAP* img_boutons_off[NB_BOUTONS_SOUS_MENU];
    BITMAP* fond;
    BITMAP* oiseau[NB_IMG_OISEAU];
    int boutons_x[NB_BOUTONS_SOUS_MENU];
    int boutons_y[NB_BOUTONS_SOUS_MENU];
}t_graphsousMenu;

typedef struct graphMenu // on déclarera une instance de t_graphMenu dans le main
{
    BITMAP* cursor;
    BITMAP* fond;
    BITMAP* contenu_credits;

    BITMAP* img_boutons_on[NB_BOUTONS];
    BITMAP* img_boutons_off[NB_BOUTONS];

    SAMPLE* music;

    t_graphsousMenu graphsdusousmenu;

    int boutons_x[NB_BOUTONS];
    int boutons_y[NB_BOUTONS];

}t_graphMenu;

// libère les bitmaps du menu, à la fin du programme.
void menu_liberer(t_graphMenu* graph);

// charge les informations du menu
void menu_charger(t_graphMenu* graph);

// affiche le menu
void menu_afficher(t_graphMenu graph);

// affichage du sous-menu a propos
void menu_afficher_credits(t_graphMenu graph);

void menu_boucle_jeu(int mode_choisi,const char* nom_fichier);

int menu_selection_mode(t_graphMenu graph);

void sous_menu_liberer(t_graphsousMenu* g);

void sous_menu_charger(t_graphsousMenu* g);

/////////////////route.h////////////////////////
typedef struct route
{
    int type;
    int case_de_referenceX;
    int case_de_referenceY;
}t_route;

t_route* route_creer();

void route_liberer(t_route* route);

int route_place_libre(int colonne,int ligne,t_case*** kase);

void route_placer(t_route* route,int colonne,int ligne,t_case*** kase);

int route_depassement_matrice(int colonne,int ligne);

void route_actualiser(t_route* route,t_case*** kase);

void route_actualiser_voisins(t_route* route,t_case*** kase);

void route_afficher(t_route* route,int niveau);

/////////////////terrain.h////////////////////////
t_case*** terrain_allouer();

/// A APPELER APRES AVOIR LIBERE LES COLLECTIONS DE STRUCTURES (habitations, casernes, chateaux, centrales etc...)
/// SINON, fuite mémoire
void terrain_liberer(t_case*** mat);



#endif //ECECITY_MABIBLIO_H
