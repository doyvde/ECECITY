#include "mabiblio.h"

t_graphismes* graphs;

int main()
{
    srand(time(NULL));
    initialiser_allegro(1024, 768);//initialisation d'Allegro
    BITMAP* menu1=chargerImage("fichiers/images/menu1/menuChoixLangues.bmp");//chargement du menu de choix de la langue
    graphs = graphismes_charger();//chargement des graphismes
    t_graphMenu graphs_menu;//structure menu pour le son
    menu(menu1, &graphs_menu);//menu et jeu
    printf("liberer delivrer\n");
    graphismes_liberer(graphs);//libération des graphismes
    fermer_allegro();

    return 0;
}END_OF_MAIN();

///Source Majeure: https://github.com/iNaDeX/ECE-City   2018
///Source: https://github.com/MaximeJUMELINE/ECE_CITY_2O12   2012
