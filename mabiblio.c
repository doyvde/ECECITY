//
// Created by denis on 02/11/2022.
//

#include "mabiblio.h"

/////////////////bfs.c////////////////////////
int* recherchepluscourtchemin(t_bfs* bfs,t_case*** kase)
{
    t_file* file;
    t_case* temp;
    int marque[NB_CASES_LIG][NB_CASES_COL];
    int ligne,colonne,compteur;
    int* longueurs;

    longueurs=malloc(bfs->ordre*sizeof(int));
    for(compteur=0;compteur<bfs->ordre;compteur++)
    {
        longueurs[compteur]=0;
    }

    file=file_creer();
    for(ligne=0;ligne<NB_CASES_LIG;ligne++)
    {
        for(colonne=0;colonne<NB_CASES_COL;colonne++)
        {
            marque[ligne][colonne]=0;
        }
    }

    if(kase[bfs->case_de_referenceY][bfs->case_de_referenceX]->type==CHATEAU)
    {
        for(ligne=bfs->case_de_referenceY;ligne<bfs->case_de_referenceY+CHATEAU_H;ligne++)
        {
            for(colonne=bfs->case_de_referenceX;colonne<bfs->case_de_referenceX+CHATEAU_W;colonne++)
            {
                tester_voisins(kase,ligne,colonne,longueurs,marque,file);

            }
        }
    }

    if(kase[bfs->case_de_referenceY][bfs->case_de_referenceX]->type==CASERNE)
    {
        for(ligne=bfs->case_de_referenceY;ligne<bfs->case_de_referenceY+CASERNE_H;ligne++)
        {
            for(colonne=bfs->case_de_referenceX;colonne<bfs->case_de_referenceX+CASERNE_W;colonne++)
            {
                tester_voisins(kase,ligne,colonne,longueurs,marque,file);

            }
        }
    }

    if(kase[bfs->case_de_referenceY][bfs->case_de_referenceX]->type==CENTRALE)
    {
        for(ligne=bfs->case_de_referenceY;ligne<bfs->case_de_referenceY+CENTRALE_H;ligne++)
        {
            for(colonne=bfs->case_de_referenceX;colonne<bfs->case_de_referenceX+CENTRALE_W;colonne++)
            {
                tester_voisins(kase,ligne,colonne,longueurs,marque,file);

            }
        }
    }
    while(!file_vide(file))
    {
        temp=file_defiler(file);
        ligne=((t_route*)temp->elem)->case_de_referenceY;
        colonne=((t_route*)temp->elem)->case_de_referenceX;
        tester_voisins(kase,ligne,colonne,longueurs,marque,file);
    }
    free(file); // free et non pas file_detruire car il ne faut pas détruire les éléments de la file, qui sont directement
    // des éléments (des cases) de notre terrain !
    return longueurs;
}

void tester_voisins(t_case*** kase,int ligne,int colonne,int* longueurs,int marque[NB_CASES_LIG][NB_CASES_COL],t_file* file)
{
    if(ligne>0)
    {
        if(marque[ligne-1][colonne]==0)
        {
            if(kase[ligne-1][colonne]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne-1][colonne]);
                marque[ligne-1][colonne]=marque[ligne][colonne]+1;
            }
            if(kase[ligne-1][colonne]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne-1][colonne]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne-1][colonne]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne-1][colonne]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
    if(ligne<NB_CASES_LIG-1)
    {
        if(marque[ligne+1][colonne]==0)
        {
            if(kase[ligne+1][colonne]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne+1][colonne]);
                marque[ligne+1][colonne]=marque[ligne][colonne]+1;
            }
            if(kase[ligne+1][colonne]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne+1][colonne]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne+1][colonne]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne+1][colonne]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
    if(colonne<NB_CASES_COL-1)
    {
        if(marque[ligne][colonne+1]==0)
        {
            if(kase[ligne][colonne+1]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne][colonne+1]);
                marque[ligne][colonne+1]=marque[ligne][colonne]+1;
            }
            if(kase[ligne][colonne+1]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne][colonne+1]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne][colonne+1]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne][colonne+1]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
    if(colonne>0)
    {
        if(marque[ligne][colonne-1]==0)
        {
            if(kase[ligne][colonne-1]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne][colonne-1]);
                marque[ligne][colonne-1]=marque[ligne][colonne]+1;
            }
            if(kase[ligne][colonne-1]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne][colonne-1]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne][colonne-1]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne][colonne-1]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
}
/////////////////info.c////////////////////////
t_infos * infos_creer()
{

    t_infos* nouv;
    //allocation mémoire pour cette instance
    nouv=(t_infos*)malloc(1*sizeof(t_infos));
    //On en profite pour remplir directement les champs de l'instance
    //Car ils sont définis en DUR par le developeur
    nouv->x=COORDX1;
    nouv->y=COORDY1;

    nouv->isCatch=0;
    return nouv;
}

void info_afficher(t_editeur* ed)
{
    int x,y;
    x = ed->info->x;
    y = ed->info->y;
    rectfill(page, x, y, x+695, y+45, COUL_FOND);
    rect(page, x, y-20, x+695, y+45, COUL_BORD);
    /***** il faudra aussi rajouter les variables du style: argent, nombre d'habitants etc..*****/
    textprintf_ex(page,font,x+12,y+10,makecol(255,255,255),-1,"Nombre habitants: %d",ed->maville->nb_habitants);
    textprintf_ex(page,font,x+400,y+10,makecol(82,143,118),-1,"Argent: %d ECEFlouz",ed->maville->argent);
    //textprintf_ex(page,font,x+400,y+10,makecol(255,255,255),-1,"Temps de jeu: %d:%d:%.0f",ed->maville->temps_de_jeu->heures,ed->maville->temps_de_jeu->minutes,ed->maville->temps_de_jeu->secondes);
    textprintf_ex(page,font,x+12,y+30,makecol(255,228,54),-1,"Elec dispo:%d/%d",ed->maville->qte_elec.capacite_disponible,ed->maville->qte_elec.capacite_max);
    textprintf_ex(page,font,x+400,y+30,makecol(0,0,255),-1,"Eau dispo:%d/%d",ed->maville->qte_eau.capacite_disponible,ed->maville->qte_eau.capacite_max);
    //if(ed->maville->pause == PAUSE_ACTIVEE) textprintf_ex(page,font,700,40,makecol(0,0,0),-1,"PAUSE ACTIVEE");
}

void info_drag(t_editeur* ed)
{


    if (mouse_x >= ed->info->x && mouse_x <=  ed->info->x + 695 && mouse_y <=  ed->info->y && mouse_y >=  ed->info->y - 20)
    {
        rectfill(page,  ed->info->x,  ed->info->y-20,  ed->info->x+695,  ed->info->y, COUL_BORD);
        if (mouse_b&1) {
            ed->boite_a_outils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
            ed->info->isCatch = 1;
            //printf("%d", boiteaoutils->isCatch);

        }
    }

    if ( ed->info->isCatch==1) {
        ed->info->x = mouse_x-695/2;
        if (mouse_y + 10 >= 20) {
            ed->info->y = mouse_y + 10;
        }
        else {
            ed->info->y = 20;
        }
        //boiteaoutils_afficher(boiteaoutils);
    }

    if (mouse_b&1)
    { ed->info->isCatch = 0;}



}

/////////////////boitaoutil.c////////////////////////
t_boite_a_outils* boiteaoutils_creer()
{
    int i,j,cpt=0;
    //déclaration d'une instance boite à outil
    t_boite_a_outils* nouv;
    //allocation mémoire pour cette instance
    nouv=(t_boite_a_outils*)malloc(1*sizeof(t_boite_a_outils));
    //On en profite pour remplir directement les champs de l'instance
    //Car ils sont définis en DUR par le developeur
    nouv->x=COORDX;
    nouv->y=COORDY;

    nouv->bouton_choisi = -1;
    //On charge les images (outil%d.bmp)
    boiteaoutils_chargerimages(nouv);
    //on rempli la matrice MATACTION qui va définir
    //le comportement de l'utilisateur dans le jeu
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            nouv->matbouton[i][j]=cpt;
            cpt++;
        }
    }
    return nouv;
}

void boiteaoutils_chargerimages(t_boite_a_outils* boiteaoutils)
{
    int i,j,nb=0;
    char img_off[TAILLE_CHAINE];
    char img_on[TAILLE_CHAINE];
    //Pour chaque case de la boite à outil, on va charger l'image correspondante
    //NB:on effectue cette action 1 fois, en début de programme, afin de ne pas toujours charger les images
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            sprintf(img_off,"fichiers/images/boite_a_outils/outil_off%d.bmp",nb);
            sprintf(img_on,"fichiers/images/boite_a_outils/outil_on%d.bmp",nb);
            boiteaoutils->img_bouton_off[i][j]=chargerImage(img_off);
            boiteaoutils->img_bouton_on[i][j]=chargerImage(img_on);
            nb++;
        }
    }
}

void boiteaoutils_drag(t_boite_a_outils* boiteaoutils)
{


    if (mouse_x >= boiteaoutils->x && mouse_x <= boiteaoutils->x + NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+75 && mouse_y <= boiteaoutils->y && mouse_y >= boiteaoutils->y - 20)
    {
        rectfill(page, boiteaoutils->x, boiteaoutils->y-20, boiteaoutils->x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+75, boiteaoutils->y, COUL_BORD);
        if (mouse_b&1) {
            boiteaoutils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
            boiteaoutils->isCatch = 1;
            //printf("%d", boiteaoutils->isCatch);

        }
    }

    if (boiteaoutils->isCatch==1) {
        boiteaoutils->x = mouse_x-(NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS))/2;
        if (mouse_y + 10 >= 20) {
            boiteaoutils->y = mouse_y + 10;
        }
        else {
            boiteaoutils->y = 20;
        }
        //boiteaoutils_afficher(boiteaoutils);
    }

    if (mouse_b&1)
    {boiteaoutils->isCatch = 0;}



}

void boiteaoutils_afficher(t_boite_a_outils* boiteaoutils)
{
    int x,y;
    int i,j,b;
    //boiteaoutils->isCatch=0;


    x = boiteaoutils->x;
    y = boiteaoutils->y;
    //créer le rectangle de la boite à outil
    rectfill(page, x, y-20, x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+75, y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS), COUL_FOND);
    rect(page, x, y-20, x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+75, y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS), COUL_BORD);

    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+26,makecol(0,0,0),-1,"Route");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+78,makecol(0,0,0),-1,"Maison");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+130,makecol(0,0,0),-1,"Chateau");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+182,makecol(0,0,0),-1,"Centrale");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+234,makecol(0,0,0),-1,"Caserne");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+286,makecol(0,0,0),-1,"Vu sol");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+338,makecol(0,0,0),-1,"Vu eau");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+390,makecol(0,0,0),-1,"Vu elec");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+442,makecol(0,0,0),-1,"Pause");
    textprintf_ex(page,font,x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+2,y+489,makecol(0,0,0),-1,"Sauv");

    //la remplir avec les images
    for(i=0;i<NB_BOUTONS_H;i++) {
        for (j = 0; j < NB_BOUTONS_W; j++) {
            if (boiteaoutils->bouton_choisi != boiteaoutils->matbouton[i][j]) {
                draw_sprite(page, boiteaoutils->img_bouton_off[i][j], x, y);
            } else {
                draw_sprite(page, boiteaoutils->img_bouton_on[i][j], x, y);
            }
            for (b = 0; b < TAILLE_BORDS; b++) {
                rect(page, x - b, y - b, x + LARGEUR_CASE + b+75, y + LARGEUR_CASE + b, COUL_BORD);
            }
            x = x + LARGEUR_CASE + TAILLE_BORDS;
        }
        x = boiteaoutils->x;
        y = y + LARGEUR_CASE + TAILLE_BORDS;
    }
}

/////////////////case.c////////////////////////

t_case* case_allouer()
{
    t_case* nouv;
    nouv=malloc(sizeof(t_case));

    nouv->elem=NULL;
    nouv->type=VIDE;

    return nouv;
}

int case_libre(t_case* kase)
{
    int libre=1;

    if(kase->type!=VIDE)
    {
        libre=0;
    }
    return libre;
}

/////////////////caserne.c////////////////////////
t_caserne* caserne_creer()
{
    t_caserne* nouv;
    nouv=malloc(sizeof(t_caserne));

    nouv->temps_de_rechargement=0;
    nouv->occupe=0;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;

    return nouv;
}

int caserne_place_libre(int x,int y,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!caserne_depassement_matrice(x,y))
    {
        for(i=x;i<x+CASERNE_W;i++)
        {
            for(j=y;j<y+CASERNE_H;j++)
            {
                if(kase[j][i]->type!=VIDE)
                {
                    libre=0;
                }
            }
        }
    }
    else libre=0;
    return libre;
}

int caserne_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<NB_CASES_COL-(CASERNE_W-1))&&(ligne>=0)&&(ligne<NB_CASES_LIG-(CASERNE_H-1)))
    {
        depasse=0;
    }
    return depasse;
}

/////////////////centrale.c////////////////////////
t_centrale* centrale_creer()
{
    t_centrale* nouv;
    nouv=malloc(sizeof(t_centrale));

    nouv->capacite.capacite_disponible = CAPACITE_CENTRALE;
    nouv->capacite.capacite_max = CAPACITE_CENTRALE;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->id_centrale.caseX = -1;
    nouv->id_centrale.caseX = -1;
    return nouv;
}

int centrale_place_libre(int col,int lig,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!centrale_depassement_matrice(col,lig))
    {
        for(i=lig;i<lig+CENTRALE_H;i++)
        {
            for(j=col;j<col+CENTRALE_W;j++)
            {
                if(kase[i][j]->type!=VIDE)
                {
                    libre=0;
                }
            }
        }
    }
    else libre=0;
    return libre;
}

int centrale_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<=NB_CASES_COL-CENTRALE_W)&&(ligne>=0)&&(ligne<=NB_CASES_LIG-CENTRALE_H))
    {
        depasse=0;
    }
    return depasse;
}

/////////////////chateau.c////////////////////////
t_chateau* chateau_creer()
{
    t_chateau* nouv;
    nouv=malloc(sizeof(t_chateau));

    nouv->capacite.capacite_disponible = CAPACITE_CHATEAU;
    nouv->capacite.capacite_max = CAPACITE_CHATEAU;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->id_chateau.caseX = -1;
    nouv->id_chateau.caseY = -1;

    return nouv;
}

int chateau_place_libre(int col,int lig,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!chateau_depassement_matrice(col,lig))
    {
        for(i=col;i<col+CHATEAU_W;i++)
        {
            for(j=lig;j<lig+CHATEAU_H;j++)
            {
                if(kase[j][i]->type!=VIDE)
                {
                    libre=0;
                }
            }
        }
    }
    else libre=0;
    return libre;
}

int chateau_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<=NB_CASES_COL-CHATEAU_W)&&(ligne>=0)&&(ligne<=NB_CASES_LIG-CHATEAU_H))
    {
        depasse=0;
    }
    return depasse;
}

int chateau_distribuer(t_chateau* chateau,t_habitation* habitation)
{
    int eau_distribuee=0,quantitee,i,eau_distrib;
    int index = 0;

    for(i=0;i<FOURNISSEUR_MAX;i++)
    {
        eau_distribuee+=habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
    }

//desert

    if (habitation->case_de_referenceX >= 0/20 && habitation->case_de_referenceX <= 320/20 && habitation->case_de_referenceY >= (585-25)/20 && habitation->case_de_referenceY <=(725-25)/20)
    {
        quantitee=habitation_nbhabitants(habitation)+eau_distribuee+100;
        printf("desert1\n");

    }

    else if (habitation->case_de_referenceX >= 0/20 && habitation->case_de_referenceX <= 120/20 && habitation->case_de_referenceY >= (25-25)/20 && habitation->case_de_referenceY <=(725-25)/20)
    {
        quantitee=habitation_nbhabitants(habitation)+eau_distribuee+100;
        printf("desert2\n");
    }

    else if (habitation->case_de_referenceX >= 0/20 && habitation->case_de_referenceX <= 200/20 && habitation->case_de_referenceY >= (85-25)/20 && habitation->case_de_referenceY <=(725-25)/20)
    {
        quantitee=habitation_nbhabitants(habitation)+eau_distribuee+100;
        printf("desert3\n");
    }

    else if (habitation->case_de_referenceX >= 0/20 && habitation->case_de_referenceX <= 240/20 && habitation->case_de_referenceY >= (285-25)/20 && habitation->case_de_referenceY <=(725-25)/20)
    {
        quantitee=habitation_nbhabitants(habitation)+eau_distribuee+100;
        printf("desert4\n");
    }

    else
    {
        quantitee=habitation_nbhabitants(habitation)-eau_distribuee;
        printf("%d\n",quantitee);
    }


    if(chateau->capacite.capacite_disponible>=quantitee)
    {
        //////////////////////////////////////////////////////////////// on cherche l'indice du 1er chateau fournisseur
        // qui n'a pas encore distribué d'eau
        // (on cherche à savoir s'il reste une place dans
        // le tableau des fournisseurs)
        i=0;
        do
        {
            eau_distrib= habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
            if(eau_distrib == 0) index = i;
            i++;
        }while(eau_distrib != 0 && i<FOURNISSEUR_MAX);
        ///////////////////////////////////////////////////////////////
        if(eau_distrib == 0) // si on a trouvé une place dans le tableau des fournisseurs, on alimente. sinon non.
        {
            habitation->chateaux_fournisseurs[index].qte_eau_distribuee=quantitee;
            habitation->chateaux_fournisseurs[index].id_fournisseur.caseX =chateau->id_chateau.caseX;
            habitation->chateaux_fournisseurs[index].id_fournisseur.caseY =chateau->id_chateau.caseY;
            chateau->capacite.capacite_disponible-=quantitee;
            habitation->eau=1;
        }
        else // on n'a pas trouvé de place, on n'alimente pas, donc la quantité distribuée est nulle
        {
            quantitee=0;
        }
    }
    else if(chateau->capacite.capacite_disponible<quantitee)
    {
        //////////////////////////////////////////////////////////////// on cherche l'indice du 1er chateau fournisseur
        // qui n'a pas encore distribué d'eau
        // (on cherche à savoir s'il reste une place dans
        // le tableau des fournisseurs)
        i=0;
        do
        {
            eau_distrib= habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
            if(eau_distrib == 0)
            {
                index = i;
            }
            i++;
        }while(eau_distrib != 0 && i<FOURNISSEUR_MAX);
        ///////////////////////////////////////////////////////////////
        if(eau_distrib == 0) // si on a trouvé une place dans le tableau des fournisseurs, on alimente. sinon non.
        {
            quantitee =chateau->capacite.capacite_disponible;
            chateau->capacite.capacite_disponible=0;

            habitation->chateaux_fournisseurs[index].qte_eau_distribuee=quantitee;
            habitation->chateaux_fournisseurs[index].id_fournisseur=chateau->id_chateau;
        }
        else // on n'a pas trouvé de place, on n'alimente pas, donc la quantité distribuée est nulle
        {
            quantitee = 0;
        }
    }
    return quantitee;
}

/////////////////collection_casernes.c////////////////////////
t_collection_casernes* collection_casernes_creer()
{
    t_collection_casernes* nouv;
    nouv=malloc(sizeof(t_collection_casernes));
    nouv->taille_actuelle=0;
    nouv->taille_max=TAILLE_INITIALE_COLLECTION;
    nouv->caserne=malloc(nouv->taille_max*sizeof(t_caserne*));
    return nouv;
}

void collection_casernes_ajouter_caserne(t_collection_casernes* collection_casernes,t_caserne* new_caserne)
{
    if(collection_casernes->taille_actuelle==collection_casernes->taille_max)
    {
        collection_casernes->taille_max=3*collection_casernes->taille_max/2;
        collection_casernes->caserne=realloc(collection_casernes->caserne,collection_casernes->taille_max*sizeof(t_caserne*));
    }
    collection_casernes->caserne[collection_casernes->taille_actuelle]=new_caserne;
    collection_casernes->taille_actuelle++;
}

int** collection_casernes_tableau_longueurs(t_collection_casernes* collection_casernes,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation)
{
    int i;
    int** longueurs_casernes_maisons;

    longueurs_casernes_maisons=malloc(collection_casernes->taille_actuelle*sizeof(int*));

    bfs->ordre=collection_habitation->taille_actuelle;
    for(i=0; i<collection_casernes->taille_actuelle; i++)
    {
        bfs->case_de_referenceX=collection_casernes->caserne[i]->case_de_referenceX;
        bfs->case_de_referenceY=collection_casernes->caserne[i]->case_de_referenceY;
        longueurs_casernes_maisons[i]=recherchepluscourtchemin(bfs,kase);
    }
    return longueurs_casernes_maisons;
}

void collection_casernes_proteger(t_collection_casernes* collection_casernes,t_collection_habitation* collection_habitation,int** longueurs)
{
    int i,j;
    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        for(j=0;j<collection_casernes->taille_actuelle;j++)
        {
            if((longueurs[j][i]<RAYON_INFLUENCE_CASERNE)&&(longueurs[j][i]))
            {
                collection_habitation->habitation[i]->protegee=PROTEGEE;
            }
        }
    }
}

/////////////////collection_centrales.c////////////////////////
t_collection_centrale* collection_centrale_creer()
{
    t_collection_centrale* nouv;
    nouv=malloc(sizeof(t_collection_centrale));
    nouv->taille_actuelle=0;
    nouv->taille_max=TAILLE_INITIALE_COLLECTION;
    nouv->centrale=malloc(nouv->taille_max*sizeof(t_centrale*));
    return nouv;
}

void collection_centrale_ajouter_centrale(t_collection_centrale* collection_centrale,t_centrale* new_centrale)
{
    if(collection_centrale->taille_actuelle==collection_centrale->taille_max)
    {
        collection_centrale->taille_max=3*collection_centrale->taille_max/2;
        collection_centrale->centrale=realloc(collection_centrale->centrale,collection_centrale->taille_max*sizeof(t_centrale*));
    }
    collection_centrale->centrale[collection_centrale->taille_actuelle]=new_centrale;
    collection_centrale->taille_actuelle++;
}

void collection_centrale_distribuer(t_collection_centrale* collection_centrale,t_collection_habitation* collection_habitation,int** longueurs)
{
    int i=0,j=0;
    int quantitee;

    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        for(j=0; j<collection_habitation->taille_actuelle; j++)
        {
            if((collection_habitation->habitation[j]->electricite==0)&&(longueurs[i][j]!=0))
            {
                //glace

                if (collection_habitation->habitation[j]->case_de_referenceX >= 600/20 && collection_habitation->habitation[j]->case_de_referenceX <= 900/20 && collection_habitation->habitation[j]->case_de_referenceY >= (25-25)/20 && collection_habitation->habitation[j]->case_de_referenceY <=(165-25)/20)
                {
                    quantitee=habitation_nbhabitants(collection_habitation->habitation[j])+100;
                    printf("glace1\n");
                }

                else if (collection_habitation->habitation[j]->case_de_referenceX >= 800/20 && collection_habitation->habitation[j]->case_de_referenceX <= 900/20 && collection_habitation->habitation[j]->case_de_referenceY >= (25-25)/20 && collection_habitation->habitation[j]->case_de_referenceY <=(345-25)/20)
                {
                    quantitee=habitation_nbhabitants(collection_habitation->habitation[j])+100;
                    printf("glace2\n");
                }

                else if (collection_habitation->habitation[j]->case_de_referenceX >= 660/20 && collection_habitation->habitation[j]->case_de_referenceX <= 900/20 && collection_habitation->habitation[j]->case_de_referenceY >= (25-25)/20 && collection_habitation->habitation[j]->case_de_referenceY <=(205-25)/20)
                {
                    quantitee=habitation_nbhabitants(collection_habitation->habitation[j])+100;
                    printf("glace3\n");
                }

                else if (collection_habitation->habitation[j]->case_de_referenceX >= 860/20 && collection_habitation->habitation[j]->case_de_referenceX <= 900/20 && collection_habitation->habitation[j]->case_de_referenceY >= (25-25)/20 && collection_habitation->habitation[j]->case_de_referenceY <=(385-25)/20)
                {
                    quantitee=habitation_nbhabitants(collection_habitation->habitation[j])+100;
                    printf("glace4\n");
                }

                else if (collection_habitation->habitation[j]->case_de_referenceX >= 760/20 && collection_habitation->habitation[j]->case_de_referenceX <= 900/20 && collection_habitation->habitation[j]->case_de_referenceY >= (245-25)/20 && collection_habitation->habitation[j]->case_de_referenceY <=(285-25)/20)
                {
                    quantitee=habitation_nbhabitants(collection_habitation->habitation[j])+100;
                    printf("glace5\n");

                }
                else
                {
                    quantitee=habitation_nbhabitants(collection_habitation->habitation[j]);
                    printf("%d\n",quantitee);
                }
                //quantitee=habitation_nbhabitants(collection_habitation->habitation[j]); ///retourne le nombre d'habitant en fonction du stade de développement
                if(collection_centrale->centrale[i]->capacite.capacite_disponible>=quantitee)
                {
                    collection_habitation->habitation[j]->id_centrale_fournisseuse.caseX = collection_centrale->centrale[i]->id_centrale.caseX; // on recopie l'ID de la centrale
                    collection_habitation->habitation[j]->id_centrale_fournisseuse.caseY = collection_centrale->centrale[i]->id_centrale.caseY; // on recopie l'ID de la centrale
                    collection_centrale->centrale[i]->capacite.capacite_disponible-=quantitee;
                    collection_habitation->habitation[j]->electricite=1;
                }
            }
        }
    }
}

int collection_centrale_elec_disponible(t_collection_centrale* collection_centrale)
{
    int elec_totale_dispo = 0;
    int i;
    for(i=0;i<collection_centrale->taille_actuelle;i++)
    {
        elec_totale_dispo += collection_centrale->centrale[i]->capacite.capacite_disponible;
    }
    return elec_totale_dispo;
}

int** collection_centrale_tableau_longueurs(t_collection_centrale* collection_centrale,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation)
{
    int i;
    int** longueurs_centrales_maisons;

    longueurs_centrales_maisons=malloc(collection_centrale->taille_actuelle*sizeof(int*));

    bfs->ordre=collection_habitation->taille_actuelle;
    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        bfs->case_de_referenceX=collection_centrale->centrale[i]->case_de_referenceX;
        bfs->case_de_referenceY=collection_centrale->centrale[i]->case_de_referenceY;
        longueurs_centrales_maisons[i]=recherchepluscourtchemin(bfs,kase);
    }
    return longueurs_centrales_maisons;
}

int* collection_centrale_tableau_capacite(t_collection_centrale* collection_centrale)
{
    int* capacite_centrale;
    int i;
    capacite_centrale=malloc(collection_centrale->taille_actuelle*sizeof(int));
    for(i=0;i<collection_centrale->taille_actuelle;i++)
    {
        capacite_centrale[i]=collection_centrale->centrale[i]->capacite.capacite_disponible;
    }
    return capacite_centrale;
}

/////////////////collection_chateau.c////////////////////////
t_collection_chateau* collection_chateau_creer()
{
    t_collection_chateau* nouv;
    nouv=malloc(sizeof(t_collection_chateau));
    nouv->taille_actuelle=0;
    nouv->taille_max=TAILLE_INITIALE_COLLECTION;
    nouv->chateau=malloc(nouv->taille_max*sizeof(t_chateau*));
    return nouv;
}

void collection_chateau_ajouter_chateau(t_collection_chateau* collection_chateau,t_chateau* new_chateau)
{
    if(collection_chateau->taille_actuelle==collection_chateau->taille_max)
    {
        collection_chateau->taille_max=3*collection_chateau->taille_max/2;
        collection_chateau->chateau=realloc(collection_chateau->chateau,collection_chateau->taille_max*sizeof(t_chateau*));
    }
    collection_chateau->chateau[collection_chateau->taille_actuelle]=new_chateau;
    collection_chateau->taille_actuelle++;
}

int** collection_chateau_tableau_longueurs(t_collection_chateau* collection_chateau,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation)
{
    int i;
    int** longueurs_chateaux_maisons;

    longueurs_chateaux_maisons=malloc(collection_chateau->taille_actuelle*sizeof(int*));

    bfs->ordre=collection_habitation->taille_actuelle;
    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        bfs->case_de_referenceX=collection_chateau->chateau[i]->case_de_referenceX;
        bfs->case_de_referenceY=collection_chateau->chateau[i]->case_de_referenceY;
        longueurs_chateaux_maisons[i]=recherchepluscourtchemin(bfs,kase);
    }
    return longueurs_chateaux_maisons;
}

void collection_chateau_distribuer(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs_chateaux_habitations)
{
    int i=0;
    int eau_dispo;
    int taille1,taille2,compteur,j,compteur2,k,l;
    int mini,distributeur=0,receveur;
    if((collection_habitation->taille_actuelle!=0)&&(collection_chateau->taille_actuelle!=0))
    {
        //pour toutes les maisons
        while(i<collection_habitation->taille_actuelle)
        {//on cherche TOUTES les plus grosses
            compteur=i;
            taille1=collection_habitation->habitation[i]->stade;
            taille2=collection_habitation->habitation[i]->stade;
            while(taille1==taille2)
            {
                compteur++;
                if(compteur<collection_habitation->taille_actuelle) taille2=collection_habitation->habitation[compteur]->stade;
                else taille2=INFINI;
            }
            //Pour CHACUNE de ces habitations (il y en a compteur-1)
            for(l=i;l<compteur;l++)
            {
                mini=INFINI;
                receveur=-1;
                for(k=0;k<collection_chateau->taille_actuelle;k++)
                {
                    for(j=i;j<compteur;j++)
                    {
                        if((longueurs_chateaux_habitations[k][j]!=0)&&(longueurs_chateaux_habitations[k][j]<mini)&&(collection_habitation->habitation[j]->electricite==1)&&(collection_habitation->habitation[j]->eau!=1))
                        {
                            mini=longueurs_chateaux_habitations[k][j];
                            receveur=j;
                        }
                    }
                }
                if(receveur!=-1)
                {
                    //on compte l'eau disponible sur le réseau
                    eau_dispo=0;
                    for(compteur2=0;compteur2<collection_chateau->taille_actuelle;compteur2++)
                    {
                        if(longueurs_chateaux_habitations[compteur2][receveur]!=0)
                        {
                            eau_dispo+=collection_chateau->chateau[compteur2]->capacite.capacite_disponible;
                        }
                    }//TANT que l'habitation n'est pas alimenté et que l'eau disponible n'est pas épuisée et qu'on a pas atteint la limite des fournisseur
                    while((collection_habitation->habitation[receveur]->eau!=1)&&(eau_dispo>0)&&(collection_habitation->habitation[receveur]->chateaux_fournisseurs[FOURNISSEUR_MAX-1].qte_eau_distribuee==0))
                    {
                        //On recherche la centrale sur le réseau la plus proche
                        mini=INFINI;
                        for(compteur2=0;compteur2<collection_chateau->taille_actuelle;compteur2++)
                        {
                            if((longueurs_chateaux_habitations[compteur2][receveur]!=0)&&(longueurs_chateaux_habitations[compteur2][receveur]<mini)&&(collection_chateau->chateau[compteur2]->capacite.capacite_disponible!=0))
                            {
                                distributeur=compteur2;
                                mini=longueurs_chateaux_habitations[compteur2][receveur];
                            }
                        }//on alimente l'habitation et on tient à jours la quantitee d'eau dispo
                        eau_dispo-=chateau_distribuer(collection_chateau->chateau[distributeur],collection_habitation->habitation[receveur]);
                    }
                }

            }
            i=compteur;
        }
    }
}

int collection_chateau_eau_disponible(t_collection_chateau* collection_chateau)
{
    int eau_totale_dispo = 0;
    int i;

    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        eau_totale_dispo = eau_totale_dispo + collection_chateau->chateau[i]->capacite.capacite_disponible;;
    }

    return eau_totale_dispo;
}

int* collection_chateau_tableau_capacite(t_collection_chateau* collection_chateau)
{
    int* capacite_chateau;
    int i;
    capacite_chateau=malloc(collection_chateau->taille_actuelle*sizeof(int));
    for(i=0;i<collection_chateau->taille_actuelle;i++)
    {
        capacite_chateau[i]=collection_chateau->chateau[i]->capacite.capacite_disponible;
    }
    return capacite_chateau;
}

/////////////////collection_habitations.c////////////////////////
t_collection_habitation* collection_habitation_creer()
{
    t_collection_habitation* nouv;
    nouv=malloc(sizeof(t_collection_habitation));
    nouv->taille_actuelle=0;
    nouv->taille_max=TAILLE_INITIALE_COLLECTION;
    nouv->habitation=malloc(nouv->taille_max*sizeof(t_habitation*));
    return nouv;
}

void collection_habitation_trier(t_collection_habitation* collection_habitation)
{
    int i;
    qsort(collection_habitation->habitation, collection_habitation->taille_actuelle, sizeof(t_habitation*),habitation_comparer);
    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        collection_habitation->habitation[i]->indice=i;
    }
}

void collection_habitation_ajouter_habitation(t_collection_habitation* collection_habitation,t_habitation* new_habitation)
{
    if(collection_habitation->taille_actuelle==collection_habitation->taille_max)
    {
        collection_habitation->taille_max=3*collection_habitation->taille_max/2;
        collection_habitation->habitation=realloc(collection_habitation->habitation,collection_habitation->taille_max*sizeof(t_habitation*));
    }
    collection_habitation->habitation[collection_habitation->taille_actuelle]=new_habitation;
    collection_habitation->taille_actuelle++;
}

void collection_habitation_evolution(t_collection_habitation* collection_habitation,int mode, int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale)
{
    int i;
    if(collection_habitation->taille_actuelle!=0)
    {
        for(i=0;i<collection_habitation->taille_actuelle;i++)
        {
            habitation_evoluer(collection_habitation->habitation[i],mode,argent,nb_chateaux,nb_centrales,longueurs_chateaux,longueurs_centrales,capacite_chateaux,capacite_centrale);
        }
    }
}

void collection_habitation_debut_tour(t_collection_habitation* collection_habitation, int* nb_habitants)
{
    int i;
    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        int l,alea;
        collection_habitation->habitation[i]->eau =0;
        collection_habitation->habitation[i]->electricite=0;
        collection_habitation->habitation[i]->id_centrale_fournisseuse.caseX = -1;
        collection_habitation->habitation[i]->id_centrale_fournisseuse.caseX = -1;
        ///DECLARATION ALEATOIRE D'UN INCENDIE
        if(collection_habitation->habitation[i]->stade>=STADE_CABANE)
        {
            if(!collection_habitation->habitation[i]->feu)
            {
                alea=rand()%PROBABILITE_INCENDIE+1;
                if(alea==PROBABILITE_INCENDIE)
                {
                    collection_habitation->habitation[i]->feu=EN_FEU;
                }
            }
            else
            {
                collection_habitation->habitation[i]->feu+=1;
            }
        }
        collection_habitation->habitation[i]->protegee=PAS_PROTEGEE;

        for(l=0;l<FOURNISSEUR_MAX;l++)
        {
            collection_habitation->habitation[i]->chateaux_fournisseurs[l].qte_eau_distribuee=0;
            collection_habitation->habitation[i]->chateaux_fournisseurs[l].id_fournisseur.caseX= -1;
            collection_habitation->habitation[i]->chateaux_fournisseurs[l].id_fournisseur.caseY= -1;
        }
    }
    collection_habitation_trier(collection_habitation);
    *nb_habitants = collection_habitation_nombre_habitants(collection_habitation);
}

int collection_habitation_nombre_habitants(t_collection_habitation* collection_habitation)
{
    int nb_hab_total = 0;
    int i;

    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        nb_hab_total = nb_hab_total + habitation_nbhabitants(collection_habitation->habitation[i]);
    }

    return nb_hab_total;
}

/////////////////compalleg.c////////////////////////
BITMAP *page=NULL;
int page_couleur_fond;
char bouton;
char touche;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];
int mouse_depx;
int mouse_depy;

void initialiser_allegro(int w, int h)
{
    if (page) return;

    COLOR_MAP global_trans_table;
    PALETTE pal;

    allegro_init();
    install_keyboard();
    set_keyboard_rate(0,0);
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL); //////////// INDISPENSABLE!!

    create_trans_table(&global_trans_table, pal, 128, 128, 128, NULL);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    changer_nom_fenetre("ECE City");

    if (get_color_depth() == 8)
        color_map = &global_trans_table;
    else
        set_trans_blender(128, 128, 128, 100);

    show_mouse(screen);

    page=create_bitmap(TAILLE_FENETRE_W,TAILLE_FENETRE_H);

    page_couleur_fond = PAGE_COULEUR_INIT;

    effacer_page();

    afficher_page();
}

void fermer_allegro()
{
    if (!page) return;
    destroy_bitmap(page);
    page=NULL;
    allegro_exit();
}

void effacer_page()
{
    if (!page) return;
    clear_to_color(page, page_couleur_fond);
}

void afficher_page()
{
    if (!page) return;
    acquire_screen();
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();
}

void rafraichir_clavier_souris()
{
    static int mouse_prev, mouse_now;
    static int key_prev[KEY_MAX], key_now[KEY_MAX];
    int k;

    mouse_prev = mouse_now;
    mouse_now = mouse_b;
    mouse_click = mouse_now & ~mouse_prev;
    mouse_unclick = ~mouse_now & mouse_prev;

    bouton = '\0';
    if (mouse_click&1)
        bouton = 'g';
    if (mouse_click&2)
        bouton = 'd';
    if (mouse_click&4)
        bouton = 'm';

    for (k=0; k<KEY_MAX; k++)
    {
        key_prev[k] = key_now[k];
        key_now[k] = key[k];
        key_press[k] = key_now[k] && !key_prev[k];
        key_unpress[k] = !key_now[k] && key_prev[k];
    }

    touche = '\0';
    while (keypressed())
        touche = (char)readkey();

    get_mouse_mickeys(&mouse_depx, &mouse_depy);
}

BITMAP *chargerImage(const char* nomFichierImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomFichierImage,NULL);
    if (bmp==NULL)
    {
        allegro_message("pas pu trouver/charger %s",nomFichierImage);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    printf("Image charg\202e : %s\n", nomFichierImage);
    return bmp;
}

void changer_nom_fenetre(const char* ch)
{
    set_window_title(ch);
}

SAMPLE* chargerSon(const char* nomfichier)
{
    SAMPLE* nouv;
    nouv=load_sample(nomfichier);
    if(nouv==NULL)
    {
        allegro_message("pas pu trouver/charger %s",nomfichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return nouv;
}

/////////////////date.c////////////////////////
t_date* date_allouer()
{
    t_date* nouv = NULL;
    nouv = (t_date*)malloc(1*sizeof(t_date));

    nouv->heures = 0;
    nouv->minutes = 0;
    nouv->secondes = 0;

    return nouv;
}

void date_actualiser(t_date* date)
{
    date->secondes = date->secondes + PAS_DU_TIMER;
    if(date->secondes>= 60)
    {
        date->minutes += 1;
        date->secondes = 0.00;
    }
    if(date->minutes>=60)
    {
        date->heures +=1;
        date->minutes = 0;
    }
}

/////////////////editeur.c////////////////////////
t_editeur* editeur_allouer(int mode_de_jeu) // sera envoyé par le menu
{
    t_editeur* nouv = NULL;

    nouv = (t_editeur*)malloc(1*sizeof(t_editeur));

    nouv->maville = ville_allouer_initialiser(mode_de_jeu);
    nouv->boite_a_outils = boiteaoutils_creer();
    nouv->info=infos_creer();

    return nouv;
}

void editeur_gerer(t_editeur* ed)
{
    switch(ed->boite_a_outils->bouton_choisi)
    {
        case BOUTON_PAUSE:
        case BOUTON_SAUVEGARDER:
            ed->boite_a_outils->bouton_choisi = -1;
    }

    if((mouse_x>ed->boite_a_outils->x)&&(mouse_x<ed->boite_a_outils->x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS)+75)&&(mouse_y>ed->boite_a_outils->y)&&(mouse_y<ed->boite_a_outils->y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS)))
    {//On récupère les coordonnées de la souris et on en profite pour changer de référentiel
        int xc = (mouse_x-ed->boite_a_outils->x)/(LARGEUR_CASE+TAILLE_BORDS+75);
        int yc = (mouse_y-ed->boite_a_outils->y)/(LARGEUR_CASE+TAILLE_BORDS);

        //on donne à la boîte à outil la valeur de l'action sur laquelle à cliqué l'utilisateur afin de définir
        //son comportement par rapport au programme
        if ( bouton=='g' && xc>=0 && xc<NB_BOUTONS_W+75 && yc>=0 && yc<NB_BOUTONS_H )
        {
            ed->boite_a_outils->bouton_choisi=ed->boite_a_outils->matbouton[yc][xc];
        }
    }
    if(mouse_b&2)
    {
        ed->boite_a_outils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
    }


    ville_gerer(ed->maville, ed->boite_a_outils->bouton_choisi);

}

int editeur_afficher(t_editeur* ed, int* quitquestion)
{
    int quit ;
    int x,y;
    // on vide le buffer page
    clear_bitmap(page);

    rectfill(page, 0, 0, TAILLE_FENETRE_W, TAILLE_FENETRE_H, COUL_FOND1);
    rectfill(page, 0, 0, 1024, 20, COUL_FOND);

    // on construit notre affichage sur le buffer page
    ville_afficher(ed->maville,ed->boite_a_outils->bouton_choisi);

    rectfill(page, 10/2, 10/2, 20/2, 20/2, makecol(255,0,0));
    rectfill(page, 20/2, 10/2, 30/2, 20/2, makecol(0,255,0));
    rectfill(page, 10/2, 20/2, 20/2, 30/2, makecol(0,0,255));
    rectfill(page, 20/2, 20/2, 30/2, 30/2, makecol(255,228,54));
    rect(page, 0, 0, 1024, 20, COUL_BORD);
    textprintf_ex(page,font,20,7,makecol(0,0,0),-1,"Windows");
    if (mouse_x >= 950 && mouse_x <= 1024 && mouse_y <= 20 && mouse_y >=0)
    {
        rectfill(page, 950, 0, 1024, 20, makecol(255,0,0));
        textprintf_ex(page,font,960,7,makecol(0,0,0),-1,"Quitter");

    }
    if (mouse_b&1 && mouse_x >= 950 && mouse_x <= 1024 && mouse_y <= 20 && mouse_y >=0) {
        ed->boite_a_outils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
        *quitquestion = 1;
    }

    if (*quitquestion !=0)
    {
        rectfill(page, 325, 265, 600, 365, COUL_FOND);
        rect(page, 324, 264, 601, 366, COUL_BORD);

        textprintf_ex(page,font,350,290,makecol(0,0,0),-1,"Voulez vous vraiment quitter ?");
        if (mouse_x >= 390 && mouse_x <= 430 && mouse_y <= 355 && mouse_y >=320)
        {
            rectfill(page, 390, 320, 430, 335, makecol(255,0,0));
        }
        rect(page, 390, 320, 430, 335, COUL_BORD);
        textprintf_ex(page,font,400,325,makecol(0,0,0),-1,"OUI");

        if (mouse_x >= 490 && mouse_x <= 530 && mouse_y <= 355 && mouse_y >=320)
        {
            rectfill(page, 490, 320, 530, 335, makecol(255,0,0));
        }
        rect(page, 490, 320, 530, 335, COUL_BORD);
        textprintf_ex(page,font,500,325,makecol(0,0,0),-1,"NON");

        if (mouse_b&1 && mouse_x >= 390 && mouse_x <= 430 && mouse_y <= 355 && mouse_y >=320) {
            ed->boite_a_outils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
            *quitquestion = 0;
            quit = 1;
            //printf("%d", quit);

        }
        if (mouse_b&1 && mouse_x >= 490 && mouse_x <= 530 && mouse_y <= 355 && mouse_y >=320) {
            ed->boite_a_outils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
            *quitquestion = 0;

            //printf("%d", quit);

        }
    }
    textprintf_ex(page,font,960,7,makecol(0,0,0),-1,"Quitter");
    rect(page, 950, 0, 1024, 20, COUL_BORD);
    rect(page, 951, 1, 1023, 19, COUL_BORD);
    rect(page, 952, 2, 1022, 18, COUL_BORD);

   /* //desert

    if (mouse_x >= 0 && mouse_x <= 325 && mouse_y >= 585 && mouse_y <=725)
    {
        rectfill(page, 0, 586, 326, 724, COUL_BORD);
    }

    if (mouse_x >= 0 && mouse_x <= 125 && mouse_y >= 25 && mouse_y <=725)
    {
        rectfill(page, 0, 26, 126, 724, COUL_BORD);
    }

    if (mouse_x >= 0 && mouse_x <= 205 && mouse_y >= 85 && mouse_y <=725)
    {
        rectfill(page, 0, 86, 206, 724, COUL_BORD);
    }

    if (mouse_x >= 0 && mouse_x <= 245 && mouse_y >= 285 && mouse_y <=725)
    {
        rectfill(page, 0, 286, 246, 724, COUL_BORD);
    }

//glace

    if (mouse_x >= 607 && mouse_x <= 905 && mouse_y >= 25 && mouse_y <=165)
    {
        rectfill(page, 607, 25, 905, 165, COUL_BORD);
    }

    if (mouse_x >= 806 && mouse_x <= 905 && mouse_y >= 25 && mouse_y <=345)
    {
        rectfill(page, 806, 25, 905, 346, COUL_BORD);
    }

    if (mouse_x >= 665 && mouse_x <= 905 && mouse_y >= 25 && mouse_y <=205)
    {
        rectfill(page, 665, 25, 905, 205, COUL_BORD);
    }

    if (mouse_x >= 865 && mouse_x <= 905 && mouse_y >= 25 && mouse_y <=385)
    {
        rectfill(page, 865, 25, 905, 385, COUL_BORD);
    }

    if (mouse_x >= 765 && mouse_x <= 905 && mouse_y >= 245 && mouse_y <=285)
    {
        rectfill(page, 765, 245, 905, 285, COUL_BORD);
    }*/


    boiteaoutils_afficher(ed->boite_a_outils);

    boiteaoutils_drag(ed->boite_a_outils);

    info_afficher(ed);

    info_drag(ed);
    /***** il faudra aussi rajouter les variables du style: argent, nombre d'habitants etc..*****/
    /*textprintf_ex(page,font,112,20,makecol(255,255,255),-1,"Nombre habitants: %d",ed->maville->nb_habitants);
    textprintf_ex(page,font,300,20,makecol(255,255,255),-1,"Argent: %d ECEFlouz",ed->maville->argent);
    textprintf_ex(page,font,500,20,makecol(255,255,255),-1,"Temps de jeu: %d:%d:%.0f",ed->maville->temps_de_jeu->heures,ed->maville->temps_de_jeu->minutes,ed->maville->temps_de_jeu->secondes);
    textprintf_ex(page,font,112,40,makecol(255,255,255),-1,"Elec dispo:%d/%d",ed->maville->qte_elec.capacite_disponible,ed->maville->qte_elec.capacite_max);
    textprintf_ex(page,font,500,40,makecol(255,255,255),-1,"Eau dispo:%d/%d",ed->maville->qte_eau.capacite_disponible,ed->maville->qte_eau.capacite_max);
    if(ed->maville->pause == PAUSE_ACTIVEE) textprintf_ex(page,font,700,40,makecol(255,255,255),-1,"PAUSE ACTIVEE");
*/
    textprintf_ex(page,font,915,640,makecol(255,255,255),-1,"x:%d , y:%d",mouse_x,mouse_y);

    rectfill(page, 910, 650, 1024, 768, COUL_FOND);
    textprintf_ex(page,font,915,660,makecol(255,255,255),-1,"Temps de jeu:");
    textprintf_ex(page,font,920,680,makecol(255,255,255),-1,"%d:%d:%.0f",ed->maville->temps_de_jeu->heures,ed->maville->temps_de_jeu->minutes,ed->maville->temps_de_jeu->secondes);
    if(ed->maville->pause == PAUSE_ACTIVEE) textprintf_ex(page,font,915,700,makecol(255,255,255),-1,"PAUSE ACTIVEE");
    textprintf_ex(page,font,915,720,makecol(255,255,255),-1,"Cliquez sur S");
    textprintf_ex(page,font,915,735,makecol(255,255,255),-1,"pour couper ");
    textprintf_ex(page,font,915,750,makecol(255,255,255),-1,"le son");
    // on affiche le buffer page sur l'écran
    //blit(page,screen,0,0,0,0, SCREEN_W, SCREEN_H);
    stretch_blit(page, screen, 0, 0, TAILLE_FENETRE_W, TAILLE_FENETRE_H, 0, 0, SCREEN_W, SCREEN_H);// permet de gérer les ordis
    // incapables d'ouvrir un mode graphique 1024*768
    //rest(150);
    return quit;
}

void editeur_liberer(t_editeur* ed)
{
    //Libération mémoire de la boite à outil
    int l,k;
    for(l=0;l<NB_BOUTONS_H;l++)
    {
        for(k=0;k<NB_BOUTONS_W;k++)
        {
            destroy_bitmap(ed->boite_a_outils->img_bouton_off[l][k]);
            destroy_bitmap(ed->boite_a_outils->img_bouton_on[l][k]);
        }
    }
    free(ed->boite_a_outils);

    int lig,col;
    int lig1,col1;
    for(lig=0; lig<NB_CASES_LIG; lig++)
    {
        for(col=0; col<NB_CASES_COL; col++)
        {
            if(ed->maville->terrain[lig][col]->type == ROUTE)
            {
                free(ed->maville->terrain[lig][col]->elem);
            }
        }
    }
    for(lig1=0;lig1<NB_CASES_LIG;lig1++)
    {
        for(col1=0;col1<NB_CASES_COL;col1++)
        {
            free(ed->maville->terrain[lig1][col1]);
        }
    }

    for(lig1=0;lig1<NB_CASES_LIG;lig1++)
    {
        free(ed->maville->terrain[lig1]);
    }

    free(ed->maville->terrain);

    int i;

    for(i=0;i<ed->maville->collec_habitations->taille_actuelle;i++)
    {
        free(ed->maville->collec_habitations->habitation[i]->chateaux_fournisseurs);
        free(ed->maville->collec_habitations->habitation[i]);
    }
    free(ed->maville->collec_habitations->habitation);
    free(ed->maville->collec_habitations);

    int i0;

    for(i0=0;i0<ed->maville->collec_casernes->taille_actuelle;i0++)
    {
        free(ed->maville->collec_casernes->caserne[i0]);
    }
    free(ed->maville->collec_casernes->caserne);
    free(ed->maville->collec_casernes);

    int i1;

    for(i1=0; i1<ed->maville->collec_chateaux->taille_actuelle; i1++)
    {
        free(ed->maville->collec_chateaux->chateau[i1]);
    }
    free(ed->maville->collec_chateaux->chateau);
    free(ed->maville->collec_chateaux);

    int i2;

    for(i2=0; i2<ed->maville->collec_centrales->taille_actuelle; i2++)
    {
        free(ed->maville->collec_centrales->centrale[i2]);
    }
    free(ed->maville->collec_centrales->centrale);
    free(ed->maville->collec_centrales);

    free(ed->maville->temps_de_jeu);

    free(ed->maville);

    free(ed);
}

/////////////////file.c////////////////////////
// Alloue une file
t_file* file_creer()
{
    return liste_creer();
}

// Enfile ( = ajoute ) un élément à la file
void file_enfiler(t_file* file, void* elem)
{
    liste_ajout_queue(file,elem);
}

// Défile ( = retire ) un élément à la file
void* file_defiler(t_file* file)
{
    return liste_recup_tete(file);
}

// Retourne 1 si la file est vide, 0 sinon
int file_vide(t_file* file)
{
    return liste_vide(file);
}

/////////////////file_explorer.c////////////////////////
int obtenir_chemin_sauvegarde(char* chemin)
{
    int res;

    TCHAR Buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, Buffer);

    OPENFILENAME ofn;
    TCHAR tmp[TAILLE_BUFFER] ;
    tmp[0]= '\0' ;
    ZeroMemory ( &ofn , sizeof ( OPENFILENAMEW ) );
    ofn.lStructSize = sizeof ( OPENFILENAMEW );
    ofn.lpstrFile = tmp;
    ofn.nMaxFile = TAILLE_BUFFER;
    ofn.lpstrTitle = _T("Le titre");
    ofn.lpstrFilter = _T("Tous (*.*)\0*.*\0Textes (*.txt)\0*.TXT\0");
    ofn.lpstrInitialDir = _T(Buffer);
    ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER | OFN_OVERWRITEPROMPT;
    res = GetSaveFileName(&ofn);
    if (res==1)
    {
        // si choix du fichier réussi
        strncpy(chemin,ofn.lpstrFile,TAILLE_CHAINE);
        supprimer_contenu_chaine_apres_point(chemin); // obtient un nom de fichier sans extension déjà incluse
        strncat(chemin,".txt",TAILLE_CHAINE); // on rajoute proprement nous même l'extension
    }
    else printf("Choix du fichier annule\n");

    return res;
}

void supprimer_contenu_chaine_apres_point(char* chemin)
{
    unsigned int i;
    for(i=0;i<strlen(chemin);i++)
    {
        if (chemin[i] == '.')
        {
            chemin[i] = '\0';
            break;
        }
    }
}

int remplit_chemin_sauvegarde(char* chemin)
{
    int choix_fini;
    choix_fini = obtenir_chemin_sauvegarde(chemin);
    if(choix_fini)
    {
        // on est certain qu'un fichier a bien été choisi (et qu'il ne dispose pas d'une double extension)
        printf("Chemin: %s\n",chemin);
        return 1;
    }
    else return 0;
}

/////////////////graphismes.c////////////////////////

t_graphismes* graphismes_charger()
{
    int i,j;
    int barres_deja_affichees=0;
    char nom_fichier[TAILLE_CHAINE];
    t_graphismes* nouv = NULL;
    nouv = (t_graphismes*)malloc(1*sizeof(t_graphismes));



    ///////////////////////////////////////////

    nouv->buffer_ville = create_bitmap(GAME_W,GAME_H);

    clear_bitmap(nouv->buffer_ville);

    nouv->fond_herbe = chargerImage("fichiers/images/jeu/fond_herbe.bmp");

    nouv->grille = chargerImage("fichiers/images/jeu/grille.bmp");


    for(j=0; j<NB_NIVEAUX; j++)
    {
            sprintf(nom_fichier,"fichiers/images/jeu/route%d.bmp",j);
            nouv->route[j]= chargerImage(nom_fichier);

    }

    nouv->terrain_vague = chargerImage("fichiers/images/jeu/terrain_vague.bmp");

    nouv->ruine = chargerImage("fichiers/images/jeu/ruine.bmp");

    nouv->pompier = chargerImage("fichiers/images/jeu/pompier.bmp");

    for(i=0; i<NB_IMG_CABANES; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/cabane%d.bmp",i);
        nouv->cabane[i] = chargerImage(nom_fichier);

    }

    for(i=0; i<NB_IMG_MAISONS; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/maison%d.bmp",i);
        nouv->maison[i] = chargerImage(nom_fichier);

    }

    for(i=0; i<NB_IMG_IMMEUBLES; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/immeuble%d.bmp",i);
        nouv->immeuble[i] = chargerImage(nom_fichier);

    }

    for(i=0; i<NB_IMG_GRATTECIELS; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/gratte_ciel%d.bmp",i);
        nouv->gratte_ciel[i] = chargerImage(nom_fichier);

    }

    nouv->chateau = chargerImage("fichiers/images/jeu/chateau.bmp");

    nouv->centrale = chargerImage("fichiers/images/jeu/centrale.bmp");

    nouv->caserne = chargerImage("fichiers/images/jeu/caserne.bmp");




    return nouv;
}

void graphismes_liberer(t_graphismes* graph)
{
    int i,j;

    destroy_bitmap(graph->buffer_ville);

    destroy_bitmap(graph->fond_herbe);

    destroy_bitmap(graph->grille);

    for(j=0; j<NB_NIVEAUX; j++)
    {

            destroy_bitmap(graph->route[j]);

    }

    destroy_bitmap(graph->terrain_vague);
    destroy_bitmap(graph->ruine);
    destroy_bitmap(graph->pompier);

    for(i=0; i<NB_IMG_CABANES; i++)
    {
        destroy_bitmap(graph->cabane[i]);
    }

    for(i=0; i<NB_IMG_MAISONS; i++)
    {
        destroy_bitmap(graph->maison[i]);
    }

    for(i=0; i<NB_IMG_IMMEUBLES; i++)
    {
        destroy_bitmap(graph->immeuble[i]);
    }

    for(i=0; i<NB_IMG_GRATTECIELS; i++)
    {
        destroy_bitmap(graph->gratte_ciel[i]);
    }

    destroy_bitmap(graph->chateau);
    destroy_bitmap(graph->centrale);
    destroy_bitmap(graph->caserne);

    free(graph);
}

/////////////////habitation.c////////////////////////
t_habitation* habitation_creer()
{
    int i;
    t_habitation* nouv;

    nouv=malloc(sizeof(t_habitation));
    nouv->chateaux_fournisseurs=malloc(FOURNISSEUR_MAX*sizeof(t_fournisseur));
    for(i=0; i<FOURNISSEUR_MAX; i++)
    {
        nouv->chateaux_fournisseurs[i].id_fournisseur.caseX = -1;
        nouv->chateaux_fournisseurs[i].id_fournisseur.caseY = -1;
        nouv->chateaux_fournisseurs[i].qte_eau_distribuee = 0;
    }

    nouv->chrono = 0.00;
    nouv->feu= PAS_EN_FEU;
    nouv->stade= STADE_TERRAIN_VAGUE;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->electricite = 0;
    nouv->eau = 0;
    nouv->indice = 0;
    nouv->id_centrale_fournisseuse.caseX = -1;
    nouv->id_centrale_fournisseuse.caseY = -1;
    return nouv;
}

int habitation_place_libre(int col,int lig,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!habitation_depassement_matrice(col,lig))
    {
        for(i=lig; i<lig+HABITATION_H; i++)
        {
            for(j=col; j<col+HABITATION_W; j++)
            {
                ///PEUT MIEUX FAIRE (RETURN LIBRE IF LIBRE ==0)
                if(kase[i][j]->type!=VIDE)
                {
                    libre=0;
                }
            }
        }
    }
    else libre=0;
    return libre;
}

int habitation_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<=NB_CASES_COL-HABITATION_W)&&(ligne>=0)&&(ligne<=NB_CASES_LIG-HABITATION_H))
    {
        depasse=0;
    }
    return depasse;
}

void habitation_placer(t_habitation* h,int col,int lig,t_case*** kase)
{
    int i,j;
    h->case_de_referenceX=col;
    h->case_de_referenceY=lig;
    for(i=lig; i<lig+HABITATION_H; i++)
    {
        for(j=col; j<col+HABITATION_W; j++)
        {
            kase[i][j]->type=HABITATION;
            kase[i][j]->elem=h;
        }
    }
}

int habitation_nbhabitants(t_habitation* habitation)
{
    int habitants = NB_HABITANTS_RUINE;

    switch(habitation->stade)
    {
        case STADE_RUINE :
            habitants=NB_HABITANTS_RUINE; // ruine
            break;

        case STADE_TERRAIN_VAGUE :
            habitants=NB_HABITANTS_TERRAIN_VAGUE; // terrain vague
            break;

        case STADE_CABANE :
            habitants=NB_HABITANTS_CABANE; // cabane
            break;

        case STADE_MAISON :
            habitants=NB_HABITANTS_MAISON; // maison
            break;

        case STADE_IMMEUBLE :
            habitants=NB_HABITANTS_IMMEUBLE; // immeuble
            break;

        case STADE_GRATTECIEL:
            habitants=NB_HABITANTS_GRATTECIEL; // gratte-ciel
    }
    return habitants;
}

int habitation_comparer(const void* a, const void* b)
{
    const t_habitation* const* h1 = a; // en théorie ici il manque un degré de "const", comment savoir que c'était un pointeur constant sur pointeur (non constant) d'habitation constante qu'on voulait??
    const t_habitation* const* h2 = b;
    if((*h1)->stade < (*h2)->stade)
    {
        return 1;
    }
    else if((*h1)->stade > (*h2)->stade)
    {
        return -1;
    }
    else
        return 0;
}

void habitation_evoluer(t_habitation* habitation,int mode,int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateau,int* capacite_centrale)
{
    if(habitation->feu)
    {
        if(habitation->feu==DUREE_INCENDIE)
        {
            habitation->feu=PAS_EN_FEU;
            if(!habitation->protegee)
            {
                habitation->stade=STADE_RUINE;
            }
        }
        if( habitation->chrono >= DUREE_CYCLE)
        {
            habitation->chrono = 0;
        }
    }
    else if( habitation->chrono >= DUREE_CYCLE) // si 15 secondes se sont écoulées
    {
        habitation->chrono = 0; // on remet à 0 la durée
        *argent = *argent + habitation_recolter_impots(habitation);

        switch(mode)
        {
            case MODE_CAPITALISTE : habitation_evolution_capitaliste(habitation,nb_chateaux,nb_centrales,longueurs_chateaux,longueurs_centrales);

                break;

            case MODE_COMMUNISTE : habitation_evolution_communiste(habitation,nb_chateaux,nb_centrales,longueurs_chateaux,longueurs_centrales,capacite_chateau,capacite_centrale);
                break;
        }
    }
}

void habitation_progression(t_habitation* habitation)
{
    if((habitation->stade<STADE_GRATTECIEL)&&(habitation->stade!=STADE_RUINE))
    {
        habitation->stade+=1;
    }
}

void habitation_regression(t_habitation* habitation)
{
    if(habitation->stade==STADE_CABANE)
    {
        habitation->stade=STADE_RUINE;
    }
    if(habitation->stade>STADE_TERRAIN_VAGUE)
    {
        habitation->stade-=1;
    }
}

void habitation_evolution_communiste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale)
{
    int i,eau_dispo=0,elec_dispo=0,quantitee_future;
    for(i=0;i<nb_chateaux;i++)
    {///ON REGARDE L'EAU DISPO SUR LE RESEAU
        if(longueurs_chateaux[i][habitation->indice])
        {
            eau_dispo+=capacite_chateaux[i];
        }
    }
    for(i=0;i<nb_centrales;i++)
    {///ON REGARDE L'ELEC DISPO SUR LE RESEAU
        if(longueurs_centrales[i][habitation->indice])
        {
            elec_dispo+=capacite_centrale[i];
        }
    }
    if((habitation->eau==0)||(habitation->electricite==0)) ///SI L'HABITATION N'EST PAS ALIM, ELLE REGRESSE
    {
        habitation_regression(habitation);
    }
    else
    {///ON REGARDE LA QUANTITEE DONT ELLE AURA BESOIN SI ELLE EVOLUE
        quantitee_future=habitation->stade+1;
        switch(quantitee_future)
        {
            case STADE_CABANE : quantitee_future = NB_HABITANTS_CABANE;
                break;

            case STADE_MAISON : quantitee_future = NB_HABITANTS_MAISON;
                break;

            case STADE_IMMEUBLE : quantitee_future = NB_HABITANTS_IMMEUBLE;
                break;

            case STADE_GRATTECIEL : quantitee_future = NB_HABITANTS_GRATTECIEL;
                break;
        }

        //desert

        if (habitation->case_de_referenceX >= 0 && habitation->case_de_referenceX <= 325 && habitation->case_de_referenceY >= 585 && habitation->case_de_referenceX <=725)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 0 && habitation->case_de_referenceX <= 125 && habitation->case_de_referenceY >= 25 && habitation->case_de_referenceY <=725)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 0 && habitation->case_de_referenceX <= 205 && habitation->case_de_referenceY >= 85 && habitation->case_de_referenceY <=725)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 0 && habitation->case_de_referenceX <= 245 && habitation->case_de_referenceY >= 285 && habitation->case_de_referenceY <=725)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

//glace

        if (habitation->case_de_referenceX >= 607 && habitation->case_de_referenceX <= 905 && habitation->case_de_referenceY >= 25 && habitation->case_de_referenceY <=165)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 806 && habitation->case_de_referenceX <= 905 && habitation->case_de_referenceY >= 25 && habitation->case_de_referenceY <=345)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 665 && habitation->case_de_referenceX <= 905 && habitation->case_de_referenceY >= 25 && habitation->case_de_referenceY <=205)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 865 && habitation->case_de_referenceX <= 905 && habitation->case_de_referenceY >= 25 && habitation->case_de_referenceY <=385)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        if (habitation->case_de_referenceX >= 765 && habitation->case_de_referenceX <= 905 && habitation->case_de_referenceY >= 245 && habitation->case_de_referenceY <=285)
        {
            quantitee_future+=habitation_nbhabitants(habitation);
        }

        else
        {
            quantitee_future-=habitation_nbhabitants(habitation);
        }



        if((eau_dispo>=quantitee_future)&&(elec_dispo>=quantitee_future)) ///SI LA QUANTITEE DISPONIBLE EST SUPERIEURE A LA
        {                                                               ///QUANTITEE FUTURE, ON AUGMENTE LE BATIMENT
            habitation_progression(habitation);
        }
    }
}

void habitation_evolution_capitaliste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales)
{
    int connect_elec=0,connect_eau=0,i;
    for(i=0;i<nb_chateaux;i++)
    {
        if(longueurs_chateaux[i][habitation->indice])
        {
            connect_eau=1;
        }
    }
    for(i=0;i<nb_centrales;i++)
    {
        if(longueurs_centrales[i][habitation->indice])
        {
            connect_elec=1;
        }
    }
    if((habitation->stade==STADE_TERRAIN_VAGUE)&&(connect_eau)&&(connect_elec))
    {
        habitation_progression(habitation);
    }
    else
    {
        if((habitation->eau==0)||(habitation->electricite==0))
        {
            if(habitation->stade>STADE_TERRAIN_VAGUE)
                habitation_regression(habitation);
        }
        else
        {
            if(habitation->stade<STADE_GRATTECIEL)
                habitation_progression(habitation);
        }
    }
}

int habitation_recolter_impots(t_habitation* hab)
{
    return IMPOTS_PAR_HABITANT*habitation_nbhabitants(hab);
}

/////////////////liste_generique_simple_chainage.c////////////////////////
/// Variables globales pour tracer le bilan des allocations/libérations des maillons

// Total des maillons alloués
int nb_maillons_alloues = 0;

// Total des maillons libérés
int nb_maillons_liberes = 0;

/// Implémentation des sous-programmes du module

// Constructeur
t_liste* liste_creer()
{
    t_liste* nouv;
    nouv = (t_liste*) malloc(1*sizeof(t_liste));

    nouv->longueur = 0;
    nouv->p_tete = NULL;
    nouv->p_queue = NULL;
    nouv->p_courant = NULL;

    return nouv;
}

// Ajout d'élément en queue
void liste_ajout_queue(t_liste* lst, void* elem)
{
    t_maillon* nouv;
    nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
    nouv->elem = elem; // on accroche la donnée reçue en paramètre
    nouv->p_suiv = NULL;

    nb_maillons_alloues++; // on augmente le compteur de bilan mémoire

    if(liste_vide(lst)) // si la liste était vide
    {
        lst->p_queue = nouv; // on accroche le nouveau maillon sur la queue
        lst->p_tete = nouv; // on met à jour la tete aussi
    }
    else
    {
        lst->p_queue->p_suiv = nouv; // on accroche le nouveau maillon sur la queue actuelle
        lst->p_queue = nouv; // on met à jour la queue
    }
    lst->longueur = lst->longueur + 1;
}

// Retourne 1 (Vrai) si la liste est vide
int liste_vide(t_liste* lst)
{
    return (lst->longueur ==0) ? 1 : 0;
}

void* liste_recup_tete(t_liste* lst)
{
    t_maillon* tmp = NULL;
    void* elem_tete = NULL;

    if(!liste_vide(lst))
    {
        tmp = lst->p_tete->p_suiv;
        elem_tete = lst->p_tete->elem;
        free(lst->p_tete); // on détruit le maillon, mais pas les données.
        lst->p_tete = tmp; // on fait pointer la tête sur le successeur du maillon détruit
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }
    else
    {
        printf("erreur, impossible supprimer tete, la liste est vide\n");
    }

    return elem_tete;
}

/////////////////menu.c////////////////////////
void menu(BITMAP* menu1, t_graphMenu* graph)
{
    int son=1;
    graph->music = chargerSon("fichiers/sound.wav");//initialisation du son
    play_sample(graph->music, 255, 127, 1000, 1); //jouer la musique
    while(!key[KEY_ESC])
    {
        if(key_press[KEY_S] && son==0)//remet la musique en marche
        {
            son= 1;
            play_sample(graph->music, 255, 127, 1000, 1); //on joue la musique
        }
        else if(key_press[KEY_S] && son==1)//arrete la musique
        {
            son= 0;
            stop_sample(graph->music);
        }
        blit(menu1, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//on affiche le menu de choix des langues
        if((mouse_b&1) && (mouse_x >= 120) && (mouse_x <= 350) && (mouse_y >= 300) && (mouse_y <= 550))//si l'utilisateur a cliqué sur le drapeau du RU
        {
            //chargement des bitmap anglaises
        }
        else if((mouse_b&1) && (mouse_x >= 480) && (mouse_x <= 850) && (mouse_y >= 380) && (mouse_y <= 820))//le clic se situe sur le drapeau français
        {
            BITMAP* menuFR=chargerImage("fichiers/images/menu1/menuFR/menu2FR.bmp");//chargement des bitmap françaises
            menuBisFR(menu1, menuFR,  graph);//on lance le jeu en français
            destroy_bitmap(menuFR);
        }
    }
}

int menuModeFR(BITMAP* menufr, BITMAP* menuModefr, t_graphMenu* graph)//menu choix du mode
{
    int mode, quitter;
    mode=-1;
    quitter=-1;
    blit(menuModefr, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//on affiche le menu de choix du mode communiste/capitaliste
    while(quitter == -1)
    {
        if ((mouse_b & 1) && (mouse_x >= 0) && (mouse_x <= 470) && (mouse_y >= 300) && (mouse_y <= 500))//si l'utilisateur a cliqué sur les règles
        {
            printf("mode communiste\n");
            mode=MODE_COMMUNISTE;//jeu en mode communiste
            quitter=1;
        }
        else if ((mouse_b & 1) && (mouse_x >= 550) && (mouse_x <= 1024) && (mouse_y >= 300) && (mouse_y <= 500))//si l'utilisateur a cliqué sur les règles
        {
            printf("mode capitaliste\n");
            mode=MODE_CAPITALISTE;//jeu en mode capitaliste
            quitter=1;
        }
        rest(20);
    }
    return mode;//on retourne la valeur du mode
}

void menuBisFR(BITMAP* menu1, BITMAP* menuFR, t_graphMenu* graph)
{
    int choix;
    BITMAP* menufr=chargerImage("fichiers/images/menu1/menuFR/menu2FR.bmp");//chargement des bitmap anglaises
    BITMAP* menuModefr=chargerImage("fichiers/images/menu1/menuFR/menuModeFR.bmp");
    BITMAP* menuReglesfr=chargerImage("fichiers/images/menu1/menuFR/menuReglesFR.bmp");
    blit(menufr, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//on affiche le menu en français
    while(!key[KEY_ESC])
    {
        if((mouse_b&1) && (mouse_x >= 10) && (mouse_x <= 60) && (mouse_y >= 10) && (mouse_y <= 60))//si l'utilisateur a cliqué sur la croix rouge
        {
            printf("quitter\n");
            destroy_bitmap(menufr);
            destroy_bitmap(menuModefr);
            destroy_bitmap(menuReglesfr);//on détruit les bitmap
            allegro_exit();
            exit(EXIT_FAILURE);//on quitte le jeu
        }
        else if((mouse_b&1) && (mouse_x >= 100) && (mouse_x <= 950) && (mouse_y >= 165) && (mouse_y <= 265))//si l'utilisateur a cliqué sur "nouvelle partie"
        {
            printf("jouer\n");
            choix=menuModeFR(menufr, menuModefr, graph);//le joueur choisi le mode de la partie
            destroy_bitmap(menufr);
            destroy_bitmap(menuModefr);
            destroy_bitmap(menuReglesfr);//on détruit les bitmap
            menu_boucle_jeu(choix,NULL,*graph);//on lance la boucle de jeu
        }
        else if((mouse_b&1) && (mouse_x >= 100) && (mouse_x <= 950) && (mouse_y >= 350) && (mouse_y <= 450))//si l'utilisateur a cliqué sur "charger partie"
        {
            printf("quitter\n");
            destroy_bitmap(menufr);
            destroy_bitmap(menuModefr);
            destroy_bitmap(menuReglesfr);//on détruit les bitmap
            allegro_exit();
            exit(EXIT_FAILURE);//on quitte le jeu
        }
        else if((mouse_b&1) && (mouse_x >= 100) && (mouse_x <= 950) && (mouse_y >= 560) && (mouse_y <= 660))//si l'utilisateur a cliqué sur "règles du jeu"
        {
            printf("regles\n");
            menuReglesFR(menufr, menuReglesfr, menu1, graph);//on affiche les règles du jeu
        }
    }
}

void menuReglesFR(BITMAP* menufr, BITMAP* menuReglesfr, BITMAP* menu1, t_graphMenu* graph)//affichage des règles du jeu
{
    blit(menuReglesfr, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//on affiche le menu en français
    while(!key[KEY_ESC])
    {
        if((mouse_b&1) && (mouse_x >= 0) && (mouse_x <= 100) && (mouse_y >= 650) && (mouse_y <= 768))//si l'utilisateur a cliqué sur la flèche de retour
        {
            menuBisFR(menu1, menufr, graph);//on retourne au menu
        }
    }
}

void menu_boucle_jeu(int mode,const char* nom_fichier,t_graphMenu graph)
{
    int quitte,son;
    quitte=0;
    son=0;
    t_editeur* ed = NULL;
    switch(mode)
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
    while((!key[KEY_ESC])&&(quitte != 1))
    {
        if(key_press[KEY_S] && son==0)//joue la musique
        {
            son=1;//on met le son à 1
            play_sample(graph.music, 255, 127, 1000, 1);//on joue la musique
        }
        else if(key_press[KEY_S] && son==1)//arrête la musique
        {
            son=0;//on met le son à 0
            stop_sample(graph.music);//on arrete la musique
        }
        rafraichir_clavier_souris();
        editeur_gerer(ed);
        quitte=editeur_afficher(ed);
        rest(0.1);
    }
    editeur_liberer(ed);
}
/////////////////route.c////////////////////////
t_route* route_creer()
{
    t_route* nouv;
    nouv=malloc(sizeof(t_route));

    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->type = TYPE_ROUTE_HORIZONTALE;

    return nouv;
}

/*void route_actualiser(t_route* route,t_case*** kase)
{
    int colonne,ligne;
    colonne=route->case_de_referenceX;
    ligne=route->case_de_referenceY;
    route->type=TYPE_ROUTE_HORIZONTALE;
    if(ligne>0)
    {
        if(kase[ligne-1][colonne]->type==ROUTE) route->type=TYPE_ROUTE_VERTICALE;
    }
    if(ligne<NB_CASES_LIG-1)
    {
        if(kase[ligne+1][colonne]->type==ROUTE) route->type=TYPE_ROUTE_VERTICALE;
    }
    if(colonne>0)
    {
        if(kase[ligne][colonne-1]->type==ROUTE) route->type=TYPE_ROUTE_HORIZONTALE;
    }
    if(colonne<NB_CASES_COL-1)
    {
        if(kase[ligne][colonne+1]->type==ROUTE) route->type=TYPE_ROUTE_HORIZONTALE;
    }
    if((colonne>0)&&(ligne>0))
    {
        if((kase[ligne][colonne-1]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_HAUT_GAUCHE;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_BAS_DROITE;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_HAUT_DROITE;
    }
    if((colonne>0)&&(ligne<NB_CASES_LIG-1))
    {
        if((kase[ligne][colonne-1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_BAS_GAUCHE;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1)&&(colonne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne][colonne-1]->type==ROUTE)) route->type=TYPE_ROUTE_GAUCHE_DROITE_BAS;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne>0)&&(colonne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)&&(kase[ligne][colonne-1]->type==ROUTE)) route->type=TYPE_ROUTE_GAUCHE_DROITE_HAUT;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1)&&(ligne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_DROITE_BAS_HAUT;
    }
    if((colonne>0)&&(ligne<NB_CASES_LIG-1)&&(ligne>0))
    {
        if((kase[ligne][colonne-1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_GAUCHE_BAS_HAUT;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1)&&(ligne>0)&&(colonne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)&&(kase[ligne][colonne-1]->type==ROUTE)) route->type=TYPE_ROUTE_INTERSECTION;
    }
}*/

/*void route_actualiser_voisins(t_route* route,t_case*** kase)
{
    int ligne,colonne;

    ligne=route->case_de_referenceY;
    colonne=route->case_de_referenceX;

    if(colonne>0)
    {
        if(kase[ligne][colonne-1]->type==ROUTE)
        {
            route_actualiser(kase[ligne][colonne-1]->elem,kase);
        }
    }
    if(colonne<NB_CASES_COL-1)
    {
        if(kase[ligne][colonne+1]->type==ROUTE)
        {
            route_actualiser(kase[ligne][colonne+1]->elem,kase);
        }
    }
    if(ligne<NB_CASES_LIG-1)
    {
        if(kase[ligne+1][colonne]->type==ROUTE)
        {
            route_actualiser(kase[ligne+1][colonne]->elem,kase);
        }
    }
    if(ligne>0)
    {
        if(kase[ligne-1][colonne]->type==ROUTE)
        {
            route_actualiser(kase[ligne-1][colonne]->elem,kase);
        }
    }
}*/

int route_place_libre(int colonne,int ligne,t_case*** kase)
{
    int libre=1;
    if(!route_depassement_matrice(colonne,ligne))
    {
        libre=case_libre(kase[ligne][colonne]);
    }
    else libre=0;
    return libre;
}

int route_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<NB_CASES_COL)&&(ligne>=0)&&(ligne<NB_CASES_LIG))
    {
        depasse=0;
    }
    return depasse;
}

void route_placer(t_route* route,int colonne,int ligne,t_case*** kase)
{
    route->case_de_referenceX=colonne;
    route->case_de_referenceY=ligne;

    //route_actualiser(route,kase);

    kase[ligne][colonne]->type=ROUTE;
    kase[ligne][colonne]->elem=route;
    //route_actualiser_voisins(route,kase);
}

void route_afficher(t_route* route,int niveau)
{
    draw_sprite(graphs->buffer_ville,graphs->route[niveau],1+TAILLE_CASE*route->case_de_referenceX,1+TAILLE_CASE*route->case_de_referenceY);
}

/////////////////terrain.c////////////////////////
t_case*** terrain_allouer()
{
    int lig,col;
    t_case*** nouv;

    nouv = (t_case***)malloc(NB_CASES_LIG*sizeof(t_case**));
    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        nouv[lig] = (t_case**)malloc(NB_CASES_COL*sizeof(t_case*));
    }

    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        for(col=0;col<NB_CASES_COL;col++)
        {
            nouv[lig][col] = case_allouer();
        }
    }

    return nouv;
}

/// A APPELER APRES AVOIR LIBERE LES COLLECTIONS DE STRUCTURES (habitations, casernes, chateaux, centrales etc...)
/// SINON, fuite mémoire

/////////////////ville.c////////////////////////
t_ville* ville_allouer_initialiser(int mode_de_jeu)
{
    t_ville* nouv = NULL;
    nouv = (t_ville*)malloc(1*sizeof(t_ville));

    nouv->argent = ARGENT_INITIAL;
    nouv->nb_habitants = 0;
    nouv->qte_eau.capacite_disponible = 0;
    nouv->qte_eau.capacite_max = 0;
    nouv->qte_elec.capacite_disponible = 0;
    nouv->qte_elec.capacite_max = 0;
    nouv->timer = clock();
    nouv->pause = PAUSE_DESACTIVEE;
    nouv->niveau_visualisation = NIVEAU_SOL;
    nouv->mode = mode_de_jeu;
    nouv->temps_de_jeu = date_allouer();

    nouv->terrain = terrain_allouer();

    nouv->collec_habitations = collection_habitation_creer();
    nouv->collec_centrales = collection_centrale_creer();
    nouv->collec_casernes = collection_casernes_creer();
    nouv->collec_chateaux = collection_chateau_creer();

    nouv->data_bfs.case_de_referenceX =0;
    nouv->data_bfs.case_de_referenceY =0;
    nouv->data_bfs.ordre =0;

    return nouv;
}

void ville_sauvegarder(const char* nom_fichier,t_ville* v)
{
    int i,j;
    FILE* fp;

    fp=fopen(nom_fichier,"w");
    if(fp==NULL)
    {
        printf("ERREUR FICHIER DE SAUVEGARDE");
        exit(1);
    }
    ///ON ECRIT LE MODE DE JEU
    fprintf(fp,"%d %d\n",v->mode,v->argent);
    fprintf(fp,"%d %d %lf\n",v->temps_de_jeu->heures,v->temps_de_jeu->minutes,v->temps_de_jeu->secondes);
    ///ON ECRIT LA MATRICE DU TERRAIN (pour pouvoir charger les routes)
    for(i=0; i<NB_CASES_LIG; i++)
    {
        for(j=0; j<NB_CASES_COL; j++)
        {
            fprintf(fp,"%d ",v->terrain[i][j]->type);
        }
        fprintf(fp,"\n");
    }
    ///ON ECRIT LES INFORMATIONS DE LA COLLECTION D'HABITATION
    fprintf(fp,"%d\n",v->collec_habitations->taille_actuelle);
    for(i=0; i<v->collec_habitations->taille_actuelle; i++)
    {
        fprintf(fp,"%d %d %d %f %d\n",v->collec_habitations->habitation[i]->case_de_referenceX, v->collec_habitations->habitation[i]->case_de_referenceY,v->collec_habitations->habitation[i]->stade, v->collec_habitations->habitation[i]->chrono, v->collec_habitations->habitation[i]->feu);
    }
    fprintf(fp,"\n\n");
    ///ON ECRIT LES INFORMATIONS DE LA COLLECTION DE CHATEAUX
    fprintf(fp,"%d\n",v->collec_chateaux->taille_actuelle);
    for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
    {
        fprintf(fp,"%d %d\n",v->collec_chateaux->chateau[i]->case_de_referenceX,v->collec_chateaux->chateau[i]->case_de_referenceY);
    }
    fprintf(fp,"\n\n");
    ///ON ECRIT LES INFORMATIONS DE LA COLLECTION DE CENTRALE
    fprintf(fp,"%d\n",v->collec_centrales->taille_actuelle);
    for(i=0; i<v->collec_centrales->taille_actuelle; i++)
    {
        fprintf(fp,"%d %d\n",v->collec_centrales->centrale[i]->case_de_referenceX,v->collec_centrales->centrale[i]->case_de_referenceY);
    }
    fprintf(fp,"\n\n");
    ///ON ECRIT LES INFORMATIONS DE LA COLLECTION DE CASERNE
    fprintf(fp,"%d\n",v->collec_casernes->taille_actuelle);
    for(i=0; i<v->collec_casernes->taille_actuelle; i++)
    {
        fprintf(fp,"%d %d\n",v->collec_casernes->caserne[i]->case_de_referenceX,v->collec_casernes->caserne[i]->case_de_referenceY);
    }
    fclose(fp);
}

void ville_afficher(t_ville* v, int bouton_boite_a_outils)
{
    int i;
    int img_utilisee;
    int elec_distribue=0;
    int l,c,compteur,eau_distribue=0;
    int mx,my; // CHANGEMENT DE REFERENTIEL POUR CONNAITRE LES COORDONNEES DE LA SOURIS DANS LA SUB-BITMAP DE JEU
    // (voir les premiers "define" de "define.h" -> "GAME"

    int lig,col; // permet de savoir dans quelle case la souris est actuellement
    t_habitation* tmp;
    t_chateau* cha;
    //t_habitation* tmp;
    t_centrale* cent;
    switch(v->niveau_visualisation)
    {
        case NIVEAU_SOL:


            mx = mouse_x - GAME_POSX;
            my = mouse_y - GAME_POSY;

            lig = my / TAILLE_CASE;
            col = mx / TAILLE_CASE;

            draw_sprite(graphs->buffer_ville,graphs->fond_herbe,0,0);
            draw_sprite(graphs->buffer_ville,graphs->grille,0,0);

            // Affichage des routes. On est obligés de parcourir la matrice car on ne dispose pas de collection de routes
            // Pour optimiser:
            // - soit on fait une collection de routes
            // - soit on parcourt la matrice pour tout afficher (préférable pour l'éventuelle 3D iso)
            for(l=0; l<NB_CASES_LIG; l++)
            {
                for(c=0; c<NB_CASES_COL; c++)
                {
                    if(v->terrain[l][c]->type == ROUTE)
                    {
                        route_afficher(v->terrain[l][c]->elem,v->niveau_visualisation);
                    }
                }
            }


            for(i=0;i<v->collec_habitations->taille_actuelle;i++) {


                if (v->collec_habitations->habitation[i]->feu >= EN_FEU) {
                    img_utilisee = 0;
                } else {
                    img_utilisee = 1;
                }


                switch (v->collec_habitations->habitation[i]->stade) {
                    case 0:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->ruine,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->ruine,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 1:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->terrain_vague,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->terrain_vague,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 2:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->cabane[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->cabane[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 3:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->maison[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->maison[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 4:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->immeuble[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->immeuble[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 5:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->gratte_ciel[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->gratte_ciel[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                }
                if ((v->collec_habitations->habitation[i]->feu) && (v->collec_habitations->habitation[i]->protegee)) {
                    draw_sprite(graphs->buffer_ville, graphs->pompier,
                                1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_centrales->taille_actuelle; i++)
            {
                if(v->niveau_visualisation==NIVEAU_EAU)
                {
                    draw_trans_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceY);
                }
                else
                {
                    draw_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
            {

                if(v->niveau_visualisation==NIVEAU_ELEC)
                {
                    draw_trans_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceY);
                }
                else
                {
                    draw_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_casernes->taille_actuelle; i++)
            {
                if(v->niveau_visualisation==NIVEAU_SOL)
                {
                    draw_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceY);
                }
                draw_trans_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceY);
            }

            // AFFICHAGE DE L'IMAGE TEMPORAIRE QUI SUIT LA SOURIS:
            if(bouton_boite_a_outils == BOUTON_AJOUTER_ROUTE)
            {
                if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
                {
                    if(route_place_libre(col,lig,v->terrain))
                    {
                        //draw_lit_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*col,1+TAILLE_CASE*lig,makecol(0,250,0));
                        draw_sprite(graphs->buffer_ville,graphs->route[NIVEAU_SOL],1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                    else
                    {
                        draw_trans_sprite(graphs->buffer_ville,graphs->route[NIVEAU_SOL],1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                }
            }
            else if(bouton_boite_a_outils == BOUTON_AJOUTER_HABITATION)
            {
                if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
                {
                    if(habitation_place_libre(col,lig,v->terrain))
                    {
                        draw_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                    else
                    {
                        draw_trans_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                }
            }
            else if(bouton_boite_a_outils == BOUTON_AJOUTER_CHATEAU)
            {
                if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
                {
                    if(chateau_place_libre(col,lig,v->terrain))
                    {
                        draw_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                    else
                    {
                        draw_trans_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                }
            }
            else if(bouton_boite_a_outils == BOUTON_AJOUTER_CENTRALE)
            {
                if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
                {
                    if(centrale_place_libre(col,lig,v->terrain))
                    {
                        draw_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                    else
                    {
                        draw_trans_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                }
            }
            else if(bouton_boite_a_outils == BOUTON_AJOUTER_CASERNE)
            {
                if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
                {
                    if(caserne_place_libre(col,lig,v->terrain))
                    {
                        draw_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                    else
                    {
                        draw_trans_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
                    }
                }
            }
            // FIN DE L'AFFICHAGE TEMPORAIRE QUI SUIT LA SOURIS

            blit(graphs->buffer_ville,page, 0,0, GAME_POSX,GAME_POSY, GAME_W,GAME_H);
            break;
        case NIVEAU_EAU:


            mx = mouse_x - GAME_POSX;
            my = mouse_y - GAME_POSY;

            lig = my / TAILLE_CASE;
            col = mx / TAILLE_CASE;

            draw_sprite(graphs->buffer_ville,graphs->fond_herbe,0,0);
            draw_sprite(graphs->buffer_ville,graphs->grille,0,0);

            for(l=0; l<NB_CASES_LIG; l++)
            {
                for(c=0; c<NB_CASES_COL; c++)
                {
                    if(v->terrain[l][c]->type == ROUTE)
                    {
                        route_afficher(v->terrain[l][c]->elem,v->niveau_visualisation);
                    }
                }
            }


            for(i=0;i<v->collec_habitations->taille_actuelle;i++) {


                if (v->collec_habitations->habitation[i]->feu >= EN_FEU) {
                    img_utilisee = 0;
                } else {
                    img_utilisee = 1;
                }


                switch (v->collec_habitations->habitation[i]->stade) {
                    case 0:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->ruine,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->ruine,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 1:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->terrain_vague,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->terrain_vague,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 2:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->cabane[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->cabane[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 3:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->maison[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->maison[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 4:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->immeuble[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->immeuble[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 5:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->gratte_ciel[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->gratte_ciel[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                }
                if ((v->collec_habitations->habitation[i]->feu) && (v->collec_habitations->habitation[i]->protegee)) {
                    draw_sprite(graphs->buffer_ville, graphs->pompier,
                                1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_centrales->taille_actuelle; i++)
            {
                if(v->niveau_visualisation==NIVEAU_EAU)
                {
                    draw_trans_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceY);
                }
                else
                {
                    draw_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
            {

                if(v->niveau_visualisation==NIVEAU_ELEC)
                {
                    draw_trans_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceY);
                }
                else
                {
                    draw_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_casernes->taille_actuelle; i++)
            {
                if(v->niveau_visualisation==NIVEAU_SOL)
                {
                    draw_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceY);
                }
                draw_trans_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceY);
            }

            for(compteur=0; compteur<v->collec_chateaux->taille_actuelle; compteur++)
            {
                cha=v->collec_chateaux->chateau[compteur];
                textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*cha->case_de_referenceX,1+TAILLE_CASE*cha->case_de_referenceY+(CHATEAU_H*TAILLE_CASE/2),makecol(0,0,0),-1,"Chateau %d-%d :",cha->id_chateau.caseX,cha->id_chateau.caseY);
                textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*cha->case_de_referenceX,1+TAILLE_CASE*cha->case_de_referenceY+(CHATEAU_H*TAILLE_CASE/2)+TAILLE_POLICE,makecol(0,0,0),-1,"%d/%d",cha->capacite.capacite_disponible,cha->capacite.capacite_max);
            }

            if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
            {
                if((v->terrain[lig][col]->type==HABITATION))
                {
                    tmp=((t_habitation*) v->terrain[lig][col]->elem);
                    for(compteur=0; compteur<FOURNISSEUR_MAX; compteur++)
                    {
                        eau_distribue+=tmp->chateaux_fournisseurs[compteur].qte_eau_distribuee;
                    }
                    textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*tmp->case_de_referenceX,1+TAILLE_CASE*tmp->case_de_referenceY,makecol(0,100,255),-1,"%d/%d",eau_distribue,habitation_nbhabitants(tmp));
                    compteur=0;
                    while((tmp->chateaux_fournisseurs[compteur].qte_eau_distribuee != 0) && (compteur<FOURNISSEUR_MAX))
                    {
                        textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*tmp->case_de_referenceX,1+TAILLE_CASE*tmp->case_de_referenceY+(compteur+1)*TAILLE_POLICE,makecol(255,255,255),-1,"Chateau %d-%d : %d",tmp->chateaux_fournisseurs[compteur].id_fournisseur.caseX,tmp->chateaux_fournisseurs[compteur].id_fournisseur.caseY,tmp->chateaux_fournisseurs[compteur].qte_eau_distribuee);
                        compteur++;
                    }
                }
            }

            blit(graphs->buffer_ville,page, 0,0, GAME_POSX,GAME_POSY, GAME_W,GAME_H);
            break;
        case NIVEAU_ELEC:

            /*int mx,my; // CHANGEMENT DE REFERENTIEL POUR CONNAITRE LES COORDONNEES DE LA SOURIS DANS LA SUB-BITMAP DE JEU
            // (voir les premiers "define" de "define.h" -> "GAME"

            int lig,col; // permet de savoir dans quelle case la souris est actuellement
            */

            mx = mouse_x - GAME_POSX;
            my = mouse_y - GAME_POSY;

            lig = my / TAILLE_CASE;
            col = mx / TAILLE_CASE;

            draw_sprite(graphs->buffer_ville,graphs->fond_herbe,0,0);
            draw_sprite(graphs->buffer_ville,graphs->grille,0,0);

            for(l=0; l<NB_CASES_LIG; l++)
            {
                for(c=0; c<NB_CASES_COL; c++)
                {
                    if(v->terrain[l][c]->type == ROUTE)
                    {
                        route_afficher(v->terrain[l][c]->elem,v->niveau_visualisation);
                    }
                }
            }

            int i;
            int img_utilisee;
            for(i=0;i<v->collec_habitations->taille_actuelle;i++) {


                if (v->collec_habitations->habitation[i]->feu >= EN_FEU) {
                    img_utilisee = 0;
                } else {
                    img_utilisee = 1;
                }


                switch (v->collec_habitations->habitation[i]->stade) {
                    case 0:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->ruine,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->ruine,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 1:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->terrain_vague,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->terrain_vague,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 2:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->cabane[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->cabane[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 3:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->maison[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->maison[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 4:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->immeuble[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->immeuble[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                    case 5:
                        if (((v->niveau_visualisation == NIVEAU_EAU) && (!v->collec_habitations->habitation[i]->eau)) ||
                            ((v->niveau_visualisation == NIVEAU_ELEC) &&
                             (!v->collec_habitations->habitation[i]->electricite))) {
                            draw_lit_sprite(graphs->buffer_ville, graphs->gratte_ciel[img_utilisee],
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                            1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY,
                                            makecol(255, 0, 0));
                        } else
                            draw_sprite(graphs->buffer_ville, graphs->gratte_ciel[img_utilisee],
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                        1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                        break;
                }
                if ((v->collec_habitations->habitation[i]->feu) && (v->collec_habitations->habitation[i]->protegee)) {
                    draw_sprite(graphs->buffer_ville, graphs->pompier,
                                1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceX,
                                1 + TAILLE_CASE * v->collec_habitations->habitation[i]->case_de_referenceY);
                }
            }
            for(i=0; i<v->collec_centrales->taille_actuelle; i++)
            {
                if(v->niveau_visualisation==NIVEAU_EAU)
                {
                    draw_trans_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceY);
                }
                else
                {
                    draw_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_centrales->centrale[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
            {

                if(v->niveau_visualisation==NIVEAU_ELEC)
                {
                    draw_trans_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceY);
                }
                else
                {
                    draw_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_chateaux->chateau[i]->case_de_referenceY);
                }
            }

            for(i=0; i<v->collec_casernes->taille_actuelle; i++)
            {
                if(v->niveau_visualisation==NIVEAU_SOL)
                {
                    draw_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceY);
                }
                draw_trans_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceX,1+TAILLE_CASE*v->collec_casernes->caserne[i]->case_de_referenceY);
            }

            for(compteur=0; compteur<v->collec_centrales->taille_actuelle; compteur++)
            {
                cent=v->collec_centrales->centrale[compteur];
                textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*cent->case_de_referenceX,1+TAILLE_CASE*cent->case_de_referenceY+(CENTRALE_H*TAILLE_CASE/2),makecol(0,0,0),-1,"Centrale %d-%d :",cent->id_centrale.caseX,cent->id_centrale.caseY);
                textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*cent->case_de_referenceX,1+TAILLE_CASE*cent->case_de_referenceY+(CENTRALE_H*TAILLE_CASE/2)+TAILLE_POLICE,makecol(0,0,0),-1,"%d/%d",cent->capacite.capacite_disponible,cent->capacite.capacite_max);
            }

            if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
            {
                if((v->terrain[lig][col]->type==HABITATION))
                {
                    tmp=((t_habitation*) v->terrain[lig][col]->elem);
                    if(tmp->electricite)
                    {
                        elec_distribue=habitation_nbhabitants(tmp);
                    }
                    else elec_distribue=0;
                    textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*tmp->case_de_referenceX,1+TAILLE_CASE*tmp->case_de_referenceY,makecol(255,255,255),-1,"%d/%d",elec_distribue,habitation_nbhabitants(tmp));
                    textprintf_ex(graphs->buffer_ville,font,1+TAILLE_CASE*tmp->case_de_referenceX,1+TAILLE_CASE*tmp->case_de_referenceY+TAILLE_POLICE,makecol(255,255,255),-1,"Centrale %d-%d : %d",tmp->id_centrale_fournisseuse.caseX,tmp->id_centrale_fournisseuse.caseY,elec_distribue);
                }
            }

            blit(graphs->buffer_ville,page, 0,0, GAME_POSX,GAME_POSY, GAME_W,GAME_H);
            break;
    }
}

void ville_gerer(t_ville* v, int bouton_boite_a_outil)
{
    int** longueurs_casernes;
    int** longueurs_chateaux;
    int** longueurs_centrales;
    int* capacite_centrale;
    int* capacite_chateaux;
    int i;
    int j;

    if(v->pause == PAUSE_DESACTIVEE)
    {
        // Actions à effectuer à chaque tour de boucle
        clock_t temps_actuel = clock();

        if(      (((double)(temps_actuel- v->timer))/CLOCKS_PER_SEC)    >=    PAS_DU_TIMER   )
        {
            v->timer = temps_actuel;
            if(v->pause == PAUSE_DESACTIVEE)
            {
                date_actualiser(v->temps_de_jeu);


                for(j=0;j<v->collec_habitations->taille_actuelle;j++)
                {
                    v->collec_habitations->habitation[j]->chrono = v->collec_habitations->habitation[j]->chrono + PAS_DU_TIMER;
                }
            }
        }

        collection_habitation_debut_tour(v->collec_habitations,&(v->nb_habitants));

        for(i=0; i<v->collec_centrales->taille_actuelle; i++)
        {
            v->collec_centrales->centrale[i]->capacite.capacite_disponible = CAPACITE_CENTRALE;
        }

        for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
        {
            v->collec_chateaux->chateau[i]->capacite.capacite_disponible=CAPACITE_CHATEAU;
        }

        ///Calcul des longueurs entre les habitations et les différents batiments
        longueurs_chateaux=collection_chateau_tableau_longueurs(v->collec_chateaux,v->terrain,&(v->data_bfs),v->collec_habitations);
        longueurs_centrales=collection_centrale_tableau_longueurs(v->collec_centrales,v->terrain,&(v->data_bfs),v->collec_habitations);
        longueurs_casernes=collection_casernes_tableau_longueurs(v->collec_casernes,v->terrain,&(v->data_bfs),v->collec_habitations);

        ///distribution de l'eau et de l'électicité et protection des incendies
        collection_centrale_distribuer(v->collec_centrales,v->collec_habitations,longueurs_centrales);
        collection_chateau_distribuer(v->collec_chateaux,v->collec_habitations,longueurs_chateaux);
        collection_casernes_proteger(v->collec_casernes,v->collec_habitations,longueurs_casernes);

        /** On tient à jour la qté d'eau et d'elec disponible **/
        v->qte_eau.capacite_disponible = collection_chateau_eau_disponible(v->collec_chateaux);
        v->qte_eau.capacite_max = CAPACITE_CHATEAU * v->collec_chateaux->taille_actuelle;

        v->qte_elec.capacite_disponible = collection_centrale_elec_disponible(v->collec_centrales);
        v->qte_elec.capacite_max = CAPACITE_CENTRALE * v->collec_centrales->taille_actuelle;

        capacite_chateaux=collection_chateau_tableau_capacite(v->collec_chateaux);
        capacite_centrale=collection_centrale_tableau_capacite(v->collec_centrales);

        collection_habitation_evolution(v->collec_habitations,v->mode,&(v->argent),v->collec_chateaux->taille_actuelle,v->collec_centrales->taille_actuelle,longueurs_chateaux,longueurs_centrales,capacite_chateaux,capacite_centrale);

        ///LIBERATION MEMOIRE DES TABLEAUX DYNAMIQUES ALLOUES
        for(i=0; i<v->collec_centrales->taille_actuelle; i++)
        {
            free(longueurs_centrales[i]);
        }
        free(longueurs_centrales);
        free(capacite_centrale);

        for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
        {
            free(longueurs_chateaux[i]);
        }
        free(longueurs_chateaux);
        free(capacite_chateaux);

        for(i=0; i<v->collec_casernes->taille_actuelle; i++)
        {
            free(longueurs_casernes[i]);
        }
        free(longueurs_casernes);

    }


    // Actions utilisateur
    int mx,my; // CHANGEMENT DE REFERENTIEL POUR CONNAITRE LES COORDONNEES DE LA SOURIS DANS LA SUB-BITMAP DE JEU
    // (voir les premiers "define" de "define.h" -> "GAME"

    int lig,col; // permet de savoir dans quelle case la souris est actuellement

    char chemin[TAILLE_CHAINE];

    t_habitation* habitation;
    t_chateau* chateau;
    t_centrale* centrale;
    t_caserne* caserne;

    mx = mouse_x - GAME_POSX;
    my = mouse_y - GAME_POSY;

    lig = my / TAILLE_CASE;
    col = mx / TAILLE_CASE;

    if((bouton_boite_a_outil == BOUTON_AJOUTER_ROUTE) && (v->pause != PAUSE_ACTIVEE) && (v->niveau_visualisation == NIVEAU_SOL))
    {
        if(mouse_b&1 && v->argent >= COUT_ROUTE)
        {
            if(route_place_libre(col,lig,v->terrain))
            {
                route_placer(route_creer(),col,lig,v->terrain);
                v->argent-= COUT_ROUTE;
            }
        }
    }
    else if((bouton_boite_a_outil == BOUTON_AJOUTER_HABITATION) && (v->pause != PAUSE_ACTIVEE) && (v->niveau_visualisation == NIVEAU_SOL))
    {
        if(bouton == 'g' && v->argent >= COUT_HABITATION)
        {
            if(habitation_place_libre(col,lig,v->terrain))
            {
                habitation=habitation_creer();
                habitation_placer(habitation,col,lig,v->terrain);
                collection_habitation_ajouter_habitation(v->collec_habitations,habitation);
                v->argent -= COUT_HABITATION;
            }
        }
    }
    else if((bouton_boite_a_outil == BOUTON_AJOUTER_CHATEAU) && (v->pause != PAUSE_ACTIVEE) && (v->niveau_visualisation == NIVEAU_SOL))
    {
        if(bouton == 'g' && v->argent >= COUT_CHATEAU)
        {
            if(chateau_place_libre(col,lig,v->terrain))
            {
                chateau=chateau_creer();
                int i,j;
                chateau->case_de_referenceX=col;
                chateau->case_de_referenceY=lig;
                chateau->id_chateau.caseX = col;
                chateau->id_chateau.caseY = lig;
                for(i=col;i<col+CHATEAU_W;i++)
                {
                    for(j=lig;j<lig+CHATEAU_H;j++)
                    {
                        v->terrain[j][i]->type=CHATEAU;
                        v->terrain[j][i]->elem=chateau;
                    }
                }
                collection_chateau_ajouter_chateau(v->collec_chateaux,chateau);
                v->argent -= COUT_CHATEAU;
            }
        }
    }
    else if((bouton_boite_a_outil == BOUTON_AJOUTER_CENTRALE) && (v->pause != PAUSE_ACTIVEE) && (v->niveau_visualisation == NIVEAU_SOL))
    {
        if(bouton == 'g' && v->argent >= COUT_CENTRALE)
        {
            if(centrale_place_libre(col,lig,v->terrain))
            {
                centrale=centrale_creer();
                int o,p;
                centrale->case_de_referenceX=col;
                centrale->case_de_referenceY=lig;
                centrale->id_centrale.caseX = col;
                centrale->id_centrale.caseY = lig;
                for(o=lig;o<lig+CENTRALE_H;o++)
                {
                    for(p=col;p<col+CENTRALE_W;p++)
                    {
                        v->terrain[o][p]->type=CENTRALE;
                        v->terrain[o][p]->elem=centrale;
                    }
                }
                collection_centrale_ajouter_centrale(v->collec_centrales,centrale);
                v->argent -= COUT_CENTRALE;
            }
        }
    }
    else if((bouton_boite_a_outil == BOUTON_AJOUTER_CASERNE) && (v->pause != PAUSE_ACTIVEE) && (v->niveau_visualisation == NIVEAU_SOL))
    {
        if(bouton == 'g' && v->argent >= COUT_CASERNE)
        {
            if(caserne_place_libre(col,lig,v->terrain))
            {
                caserne=caserne_creer();

                int i,j;
                caserne->case_de_referenceX=col;
                caserne->case_de_referenceY=lig;
                for(i=col;i<col+CASERNE_W;i++)
                {
                    for(j=lig;j<lig+CASERNE_H;j++)
                    {
                        v->terrain[j][i]->type=CASERNE;
                        v->terrain[j][i]->elem=caserne;
                    }
                }
                collection_casernes_ajouter_caserne(v->collec_casernes,caserne);
                v->argent -= COUT_CENTRALE;
            }
        }
    }
    else if(bouton_boite_a_outil == BOUTON_PAUSE) // || (touche == 'p') ne fonctionne pas toujours, souci compalleg
    {
        v->pause = !(v->pause);
    }
    else if(bouton_boite_a_outil == BOUTON_SAUVEGARDER)
    {
        if(remplit_chemin_sauvegarde(chemin))
            ville_sauvegarder(chemin, v);
    }
    else if(bouton_boite_a_outil == BOUTON_NIVEAU_SOL)
    {
        v->pause = PAUSE_DESACTIVEE;
        v->niveau_visualisation = NIVEAU_SOL;
    }
    else if(bouton_boite_a_outil == BOUTON_NIVEAU_EAU)
    {
        v->pause = PAUSE_ACTIVEE;
        v->niveau_visualisation = NIVEAU_EAU;
    }
    else if(bouton_boite_a_outil == BOUTON_NIVEAU_ELEC)
    {
        v->pause = PAUSE_ACTIVEE;
        v->niveau_visualisation = NIVEAU_ELEC;
    }
}
