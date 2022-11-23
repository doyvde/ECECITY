#include "mabiblio.h"

///Source Majeure: https://github.com/iNaDeX/ECE-City   2018
///Source: https://github.com/MaximeJUMELINE/ECE_CITY_2O12   2012

t_graphismes* graphs;

int main()
{
    srand(time(NULL));
    initialiser_allegro(1024, 768);

    graphs = graphismes_charger();

    t_graphMenu graphs_menu;
    menu_charger(&graphs_menu);

    menu_afficher(graphs_menu);

    menu_liberer(&graphs_menu);
    graphismes_liberer(graphs);
    fermer_allegro();

    return 0;
}END_OF_MAIN();
