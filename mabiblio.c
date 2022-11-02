//
// Created by denis on 02/11/2022.
//

#include "mabiblio.h"

void menu_liberer(t_graphMenu* graph)
{
    int i;
    destroy_bitmap(graph->fond);
    destroy_bitmap(graph->cursor);
    destroy_bitmap(graph->contenu_credits);

    for(i=0; i<NB_BOUTONS; i++)
    {
        destroy_bitmap(graph->img_boutons_off[i]);
        destroy_bitmap(graph->img_boutons_on[i]);
    }

    destroy_sample(graph->music);

    sous_menu_liberer(&graph->graphsdusousmenu);
}

void sous_menu_liberer(t_graphsousMenu* g)
{
    int i;
    destroy_bitmap(g->fond);
    for(i=0;i<NB_BOUTONS_SOUS_MENU;i++)
    {
        destroy_bitmap(g->img_boutons_off[i]);
        destroy_bitmap(g->img_boutons_on[i]);
    }
    for(i=0;i<NB_IMG_OISEAU;i++)
    {
        destroy_bitmap(g->oiseau[i]);
    }
}

void sous_menu_charger(t_graphsousMenu* g)
{
    int i;
    char tmp[TAILLE_CHAINE];
    FILE *fpx,*fpy;
    fpx=fopen("fichiers/sous_menu_boutons_x.txt","r");
    fpy=fopen("fichiers/sous_menu_boutons_y.txt","r");
    if ((fpx == NULL)|| (fpy==NULL))
    {
        allegro_message("prb ouverture fichiers boutons");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    g->fond = chargerImage("fichiers/images/menu/sousmenu/fond.bmp");

    g->img_boutons_off[SOUS_MENU_COMMUNISTE] = chargerImage("fichiers/images/menu/sousmenu/communiste0.bmp");
    g->img_boutons_on[SOUS_MENU_COMMUNISTE]  = chargerImage("fichiers/images/menu/sousmenu/communiste1.bmp");
    g->img_boutons_off[SOUS_MENU_CAPITALISTE] = chargerImage("fichiers/images/menu/sousmenu/capitaliste0.bmp");
    g->img_boutons_on[SOUS_MENU_CAPITALISTE]  = chargerImage("fichiers/images/menu/sousmenu/capitaliste1.bmp");

    for(i=0;i<NB_IMG_OISEAU;i++)
    {
        sprintf(tmp,"fichiers/images/menu/sousmenu/oiseau%d.bmp",i);
        g->oiseau[i] = chargerImage(tmp);
    }

    for(i=0; i<NB_BOUTONS_SOUS_MENU; i++)
    {
        fscanf(fpx,"%d",&g->boutons_x[i]);
        fscanf(fpy,"%d",&g->boutons_y[i]);
    }
    fclose(fpx);
    fclose(fpy);
}


void menu_charger(t_graphMenu* graph)
{
    int i;
    FILE *fpx,*fpy;
    fpx=fopen("fichiers/boutons_x.txt","r");
    fpy=fopen("fichiers/boutons_y.txt","r");
    if ((fpx == NULL)|| (fpy==NULL))
    {
        allegro_message("prb ouverture fichiers boutons");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    sous_menu_charger(&graph->graphsdusousmenu);

    graph->fond=chargerImage("fichiers/images/menu/fond.bmp");
    graph->cursor=chargerImage("fichiers/images/menu/cursor.bmp");
    graph->contenu_credits=chargerImage("fichiers/images/menu/contenu_credits.bmp");

    graph->img_boutons_off[MENU_BOUTON_NOUVEAU]=chargerImage("fichiers/images/menu/nouveau0.bmp");
    graph->img_boutons_off[MENU_BOUTON_CHARGER]=chargerImage("fichiers/images/menu/charger0.bmp");
    graph->img_boutons_off[MENU_BOUTON_CREDITS]=chargerImage("fichiers/images/menu/credits0.bmp");
    graph->img_boutons_off[MENU_BOUTON_QUITTER]=chargerImage("fichiers/images/menu/quitter0.bmp");
    graph->img_boutons_off[MENU_BOUTON_RETOUR]=chargerImage("fichiers/images/menu/boutonRetour0.bmp");

    graph->img_boutons_on[MENU_BOUTON_NOUVEAU]=chargerImage("fichiers/images/menu/nouveau1.bmp");
    graph->img_boutons_on[MENU_BOUTON_CHARGER]=chargerImage("fichiers/images/menu/charger1.bmp");
    graph->img_boutons_on[MENU_BOUTON_CREDITS]=chargerImage("fichiers/images/menu/credits1.bmp");
    graph->img_boutons_on[MENU_BOUTON_QUITTER]=chargerImage("fichiers/images/menu/quitter1.bmp");
    graph->img_boutons_on[MENU_BOUTON_RETOUR]=chargerImage("fichiers/images/menu/boutonRetour1.bmp");

    graph->music = chargerSon("fichiers/sound.wav");

    for(i=0; i<NB_BOUTONS; i++)
    {
        fscanf(fpx,"%d",&graph->boutons_x[i]);
        fscanf(fpy,"%d",&graph->boutons_y[i]);
    }
    fclose(fpx);
    fclose(fpy);
}

void menu_afficher(t_graphMenu graph)
{
    int mx, my, i;
    int quitter = 0;
    int choix;
    char nom_fichier[TAILLE_CHAINE];
    int son=1;

    play_sample(graph.music, 255, 127, 1000, 1); // play the music

    while (!quitter)
    {
        if(key_press[KEY_S] && son==0)
        {
            son= 1;
            play_sample(graph.music, 255, 127, 1000, 1); // play the music
        }
        else if(key_press[KEY_S] && son==1)
        {
            son= 0;
            stop_sample(graph.music);
        }

        show_mouse(NULL);
        // Mettre à jour les variables touche (clavier) et bouton (souris)
        rafraichir_clavier_souris();

        mx=mouse_x;
        my=mouse_y;

        // Effacer complètement le buffer (tout disparaît)
        effacer_page();

        //AFFICHAGE
        draw_sprite(page, graph.fond, 0,0);

        for (i=0; i<NB_BOUTONS-1; i++)
        {
            if (mx>=graph.boutons_x[i] && mx<=(graph.boutons_x[i]+graph.img_boutons_off[i]->w) && my>=graph.boutons_y[i] && my<=(graph.boutons_y[i]+graph.img_boutons_off[i]->h))
                draw_sprite(page, graph.img_boutons_on[i], graph.boutons_x[i], graph.boutons_y[i]);
            else
                draw_sprite(page, graph.img_boutons_off[i], graph.boutons_x[i], graph.boutons_y[i]);
        }

        draw_sprite(page, graph.cursor, mx, my);
        afficher_page();

        //GESTION DU CLIC
        if (bouton=='g')
        {
            if (mx>=graph.boutons_x[MENU_BOUTON_NOUVEAU] && mx<=(graph.boutons_x[MENU_BOUTON_NOUVEAU]+graph.img_boutons_off[MENU_BOUTON_NOUVEAU]->w) && my>=graph.boutons_y[MENU_BOUTON_NOUVEAU] && my<=(graph.boutons_y[MENU_BOUTON_NOUVEAU]+graph.img_boutons_off[MENU_BOUTON_NOUVEAU]->h))
            {
                //NOUVEAU
                printf("nouveau\n");
                choix = menu_selection_mode(graph);
                if (choix != -1)
                {
                    show_mouse(screen);
                    menu_boucle_jeu(choix,NULL);
                }
            }
            if (mx>=graph.boutons_x[MENU_BOUTON_CHARGER] && mx<=(graph.boutons_x[MENU_BOUTON_CHARGER]+graph.img_boutons_off[MENU_BOUTON_CHARGER]->w) && my>=graph.boutons_y[MENU_BOUTON_CHARGER] && my<=(graph.boutons_y[MENU_BOUTON_CHARGER]+graph.img_boutons_off[MENU_BOUTON_CHARGER]->h))
            {
                //NOUVEAU
                printf("charger\n");
                if(remplit_chemin_chargement(nom_fichier))
                {
                    show_mouse(screen);
                    menu_boucle_jeu(CHARGER,nom_fichier);
                }
            }
            if (mx>=graph.boutons_x[MENU_BOUTON_CREDITS] && mx<=(graph.boutons_x[MENU_BOUTON_CREDITS]+graph.img_boutons_off[MENU_BOUTON_CREDITS]->w) && my>=graph.boutons_y[MENU_BOUTON_CREDITS] && my<=(graph.boutons_y[MENU_BOUTON_CREDITS]+graph.img_boutons_off[MENU_BOUTON_CREDITS]->h))
            {
                //CREDITS
                printf("credits\n");
                menu_afficher_credits(graph);
            }
            if (mx>=graph.boutons_x[MENU_BOUTON_QUITTER] && mx<=(graph.boutons_x[MENU_BOUTON_QUITTER]+graph.img_boutons_off[MENU_BOUTON_QUITTER]->w) && my>=graph.boutons_y[MENU_BOUTON_QUITTER] && my<=(graph.boutons_y[MENU_BOUTON_QUITTER]+graph.img_boutons_off[MENU_BOUTON_QUITTER]->h))
            {
                //QUITTER
                printf("Quitter\n");
                quitter = 1;
            }
        }
        rest(20);
    }
}

void menu_afficher_credits(t_graphMenu graph)
{
    int mx;
    int my;
    int quitter = 0;

    while(!quitter)
    {
        mx = mouse_x;
        my = mouse_y;

        //AFFICHAGE
        effacer_page();
        draw_sprite(page, graph.contenu_credits, 0, 0);
        if (mx>=graph.boutons_x[MENU_BOUTON_RETOUR] && mx<=graph.boutons_x[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->w && my>=graph.boutons_y[MENU_BOUTON_RETOUR] && my<=graph.boutons_y[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->h)
            draw_sprite(page, graph.img_boutons_on[MENU_BOUTON_RETOUR], graph.boutons_x[MENU_BOUTON_RETOUR],graph.boutons_y[MENU_BOUTON_RETOUR]);
        else
            draw_sprite(page, graph.img_boutons_off[MENU_BOUTON_RETOUR], graph.boutons_x[MENU_BOUTON_RETOUR],graph.boutons_y[MENU_BOUTON_RETOUR]);

        //CLIC
        if (mx>=graph.boutons_x[MENU_BOUTON_RETOUR] && mx<=graph.boutons_x[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->w && my>=graph.boutons_y[MENU_BOUTON_RETOUR] && my<=graph.boutons_y[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->h && mouse_b==1)
            quitter = 1;

        draw_sprite(page, graph.cursor, mx, my);
        afficher_page();
        rest(20);
    }
}

int menu_selection_mode(t_graphMenu graph)
{
    int mx, my, i;
    int quitter = 0;
    int mode = -1;

    int index = 0;
    int posx = 0;
    int cpt = 0;

    while (!quitter)
    {
        cpt++;
        // Mettre à jour les variables touche (clavier) et bouton (souris)
        rafraichir_clavier_souris();

        mx=mouse_x;
        my=mouse_y;

        // Effacer complètement le buffer (tout disparaît)
        effacer_page();

        //AFFICHAGE
        draw_sprite(page, graph.graphsdusousmenu.fond, 0,0);

        for (i=0; i<NB_BOUTONS_SOUS_MENU; i++)
        {
            if (mx>=graph.graphsdusousmenu.boutons_x[i] && mx<=(graph.graphsdusousmenu.boutons_x[i]+graph.graphsdusousmenu.img_boutons_off[i]->w) && my>=graph.graphsdusousmenu.boutons_y[i] && my<=(graph.graphsdusousmenu.boutons_y[i]+graph.graphsdusousmenu.img_boutons_off[i]->h))
                draw_sprite(page, graph.graphsdusousmenu.img_boutons_on[i], graph.graphsdusousmenu.boutons_x[i], graph.graphsdusousmenu.boutons_y[i]);
            else
                draw_sprite(page, graph.graphsdusousmenu.img_boutons_off[i], graph.graphsdusousmenu.boutons_x[i], graph.graphsdusousmenu.boutons_y[i]);
        }

        if (mx>=graph.boutons_x[MENU_BOUTON_RETOUR] && mx<=graph.boutons_x[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->w && my>=graph.boutons_y[MENU_BOUTON_RETOUR] && my<=graph.boutons_y[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->h)
            draw_sprite(page, graph.img_boutons_on[MENU_BOUTON_RETOUR], graph.boutons_x[MENU_BOUTON_RETOUR],graph.boutons_y[MENU_BOUTON_RETOUR]);
        else
            draw_sprite(page, graph.img_boutons_off[MENU_BOUTON_RETOUR], graph.boutons_x[MENU_BOUTON_RETOUR],graph.boutons_y[MENU_BOUTON_RETOUR]);

        draw_sprite(page,graph.graphsdusousmenu.oiseau[index],posx,120);
        posx+=5;
        if(cpt% 4== 0)
            index++;
        if(index>=NB_IMG_OISEAU)
            index=0;

        draw_sprite(page, graph.cursor, mx, my);
        afficher_page();

        //GESTION DU CLIC
        if (bouton=='g')
        {
            if (mx>=graph.graphsdusousmenu.boutons_x[SOUS_MENU_COMMUNISTE] && mx<=(graph.graphsdusousmenu.boutons_x[SOUS_MENU_COMMUNISTE]+graph.graphsdusousmenu.img_boutons_off[SOUS_MENU_COMMUNISTE]->w) && my>=graph.graphsdusousmenu.boutons_y[SOUS_MENU_COMMUNISTE] && my<=(graph.graphsdusousmenu.boutons_y[SOUS_MENU_COMMUNISTE]+graph.graphsdusousmenu.img_boutons_off[SOUS_MENU_COMMUNISTE]->h))
            {
                quitter = 1;
                mode = MODE_COMMUNISTE;
            }
            if (mx>=graph.graphsdusousmenu.boutons_x[SOUS_MENU_CAPITALISTE] && mx<=(graph.graphsdusousmenu.boutons_x[SOUS_MENU_CAPITALISTE]+graph.graphsdusousmenu.img_boutons_off[SOUS_MENU_CAPITALISTE]->w) && my>=graph.graphsdusousmenu.boutons_y[SOUS_MENU_CAPITALISTE] && my<=(graph.graphsdusousmenu.boutons_y[SOUS_MENU_CAPITALISTE]+graph.graphsdusousmenu.img_boutons_off[SOUS_MENU_CAPITALISTE]->h))
            {
                quitter = 1;
                mode = MODE_CAPITALISTE;
            }
            if (mx>=graph.boutons_x[MENU_BOUTON_RETOUR] && mx<=graph.boutons_x[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->w && my>=graph.boutons_y[MENU_BOUTON_RETOUR] && my<=graph.boutons_y[MENU_BOUTON_RETOUR]+graph.img_boutons_off[MENU_BOUTON_RETOUR]->h && mouse_b==1)
            {
                quitter = 1;
            }
        }
        rest(20);
    }
    return mode;
}

void menu_boucle_jeu(int mode_choisi,const char* nom_fichier)
{
    t_editeur* ed = NULL;

    switch(mode_choisi)
    {
        case MODE_CAPITALISTE:
            ed = editeur_allouer(MODE_CAPITALISTE);
            break;
        case MODE_COMMUNISTE:
            ed = editeur_allouer(MODE_COMMUNISTE);
            break;
        case CHARGER:
            ed = editeur_allouer(MODE_CAPITALISTE); // osef on va le changer en chargeant la ville
            ville_charger(nom_fichier,ed->maville);
            break;
    }

    while(!key[KEY_ESC])
    {
        rafraichir_clavier_souris();
        editeur_gerer(ed);
        editeur_afficher(ed);
        rest(20);
    }

    editeur_liberer(ed);
}