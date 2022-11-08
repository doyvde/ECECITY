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

void boiteaoutils_reinitialiser_boutons_uniques(t_boite_a_outils* boiteaoutils)
{
    switch(boiteaoutils->bouton_choisi)
    {
        case BOUTON_PAUSE:
        case BOUTON_SAUVEGARDER:
            boiteaoutils->bouton_choisi = -1;
    }
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

void boiteaoutils_afficher(t_boite_a_outils* boiteaoutils)
{
    int x,y;
    int i,j,b;

    x = boiteaoutils->x;
    y = boiteaoutils->y;
    //créer le rectangle de la boite à outil
    rectfill(page, x, y, x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS), y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS), COUL_FOND);
    rect(page, x, y, x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS), y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS), COUL_BORD);

    //la remplir avec les images
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            if(boiteaoutils->bouton_choisi!=boiteaoutils->matbouton[i][j])
            {
                draw_sprite(page,boiteaoutils->img_bouton_off[i][j],x,y);
            }
            else
            {
                draw_sprite(page,boiteaoutils->img_bouton_on[i][j],x,y);
            }
            for(b=0;b<TAILLE_BORDS;b++)
            {
                rect(page,x-b,y-b,x+LARGEUR_CASE+b,y+LARGEUR_CASE+b,COUL_BORD);
            }
            x=x+LARGEUR_CASE+TAILLE_BORDS;
        }
        x= boiteaoutils->x;
        y=y+LARGEUR_CASE+TAILLE_BORDS;
    }
}

void boiteaoutils_gerer(t_boite_a_outils* boiteaoutils)
{
    boiteaoutils_reinitialiser_boutons_uniques(boiteaoutils);

    if((mouse_x>boiteaoutils->x)&&(mouse_x<boiteaoutils->x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS))&&(mouse_y>boiteaoutils->y)&&(mouse_y<boiteaoutils->y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS)))
    {//On récupère les coordonnées de la souris et on en profite pour changer de référentiel
        int xc = (mouse_x-boiteaoutils->x)/(LARGEUR_CASE+TAILLE_BORDS);
        int yc = (mouse_y-boiteaoutils->y)/(LARGEUR_CASE+TAILLE_BORDS);

        //on donne à la boîte à outil la valeur de l'action sur laquelle à cliqué l'utilisateur afin de définir
        //son comportement par rapport au programme
        if ( bouton=='g' && xc>=0 && xc<NB_BOUTONS_W && yc>=0 && yc<NB_BOUTONS_H )
        {
            boiteaoutils->bouton_choisi=boiteaoutils->matbouton[yc][xc];
        }
    }
    if(mouse_b&2)
    {
        boiteaoutils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
    }
}

void boiteaoutils_liberer(t_boite_a_outils* boiteaoutils)
{//Libération mémoire de la boite à outil
    int i,j;
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            destroy_bitmap(boiteaoutils->img_bouton_off[i][j]);
            destroy_bitmap(boiteaoutils->img_bouton_on[i][j]);
        }
    }
    free(boiteaoutils);
}

/////////////////case.c////////////////////////
void case_vider(t_case* k)
{
    k->elem=NULL;
    k->type=VIDE;
}

void case_remplir(t_case* k,int type,void* elem)
{
    k->type=type;
    k->elem=elem;
}

t_case* case_allouer()
{
    t_case* nouv;
    nouv=malloc(sizeof(t_case));

    case_vider(nouv);

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

void case_free(t_case* k)
{
    free(k);
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

void caserne_liberer(t_caserne* c)
{
    free(c);
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

void caserne_placer(t_caserne* caserne,int x,int y,t_case*** kase)
{
    int i,j;
    caserne->case_de_referenceX=x;
    caserne->case_de_referenceY=y;
    for(i=x;i<x+CASERNE_W;i++)
    {
        for(j=y;j<y+CASERNE_H;j++)
        {
            case_remplir(kase[j][i],CASERNE,caserne);
        }
    }
}

void caserne_afficher(t_caserne* caserne,int niveau)
{
    if(niveau==NIVEAU_SOL)
    {
        draw_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*caserne->case_de_referenceX,1+TAILLE_CASE*caserne->case_de_referenceY);
    }
    draw_trans_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*caserne->case_de_referenceX,1+TAILLE_CASE*caserne->case_de_referenceY);
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

void centrale_liberer(t_centrale* c)
{
    free(c);
}

void centrale_distribuer(t_centrale* centrale,t_habitation* habitation,int quantitee)
{
    habitation->id_centrale_fournisseuse.caseX = centrale->id_centrale.caseX; // on recopie l'ID de la centrale
    habitation->id_centrale_fournisseuse.caseY = centrale->id_centrale.caseY; // on recopie l'ID de la centrale
    centrale->capacite.capacite_disponible-=quantitee;
    habitation->electricite=1;
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

void centrale_placer(t_centrale* centrale,int col,int lig,t_case*** kase)
{
    int i,j;
    centrale->case_de_referenceX=col;
    centrale->case_de_referenceY=lig;
    centrale->id_centrale.caseX = col;
    centrale->id_centrale.caseY = lig;
    for(i=lig;i<lig+CENTRALE_H;i++)
    {
        for(j=col;j<col+CENTRALE_W;j++)
        {
            case_remplir(kase[i][j],CENTRALE,centrale);
        }
    }
}

void centrale_afficher(t_centrale* centrale,int niveau)
{
    if(niveau==NIVEAU_EAU)
    {
        draw_trans_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*centrale->case_de_referenceX,1+TAILLE_CASE*centrale->case_de_referenceY);
    }
    else
    {
        draw_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*centrale->case_de_referenceX,1+TAILLE_CASE*centrale->case_de_referenceY);
    }
}

void centrale_debut_tour(t_centrale* centrale)
{
    centrale->capacite.capacite_disponible = CAPACITE_CENTRALE;
}

int centrale_elec_disponible(t_centrale* centrale)
{
    return centrale->capacite.capacite_disponible;
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

void chateau_debut_tour(t_chateau* chateau)
{
    chateau->capacite.capacite_disponible=CAPACITE_CHATEAU;
}

void chateau_liberer(t_chateau* c)
{
    free(c);
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

void chateau_placer(t_chateau* chateau,int col,int lig,t_case*** kase)
{
    int i,j;
    chateau->case_de_referenceX=col;
    chateau->case_de_referenceY=lig;
    chateau->id_chateau.caseX = col;
    chateau->id_chateau.caseY = lig;
    for(i=col;i<col+CHATEAU_W;i++)
    {
        for(j=lig;j<lig+CHATEAU_H;j++)
        {
            case_remplir(kase[j][i],CHATEAU,chateau);
        }
    }
}

void chateau_afficher(t_chateau* chateau,int niveau)
{
    if(niveau==NIVEAU_ELEC)
    {
        draw_trans_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*chateau->case_de_referenceX,1+TAILLE_CASE*chateau->case_de_referenceY);
    }
    else
    {
        draw_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*chateau->case_de_referenceX,1+TAILLE_CASE*chateau->case_de_referenceY);
    }
}

int chateau_distribuer(t_chateau* chateau,t_habitation* habitation)
{
    int eau_distribuee=0,quantitee,i,eau_distrib;
    int index = 0;

    for(i=0;i<FOURNISSEUR_MAX;i++)
    {
        eau_distribuee+=habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
    }
    quantitee=habitation_nbhabitants(habitation)-eau_distribuee;
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

int chateau_eau_disponible(t_chateau* chateau)
{
    return chateau->capacite.capacite_disponible;
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
        collection_casernes_reallouer(collection_casernes);
    }
    collection_casernes->caserne[collection_casernes->taille_actuelle]=new_caserne;
    collection_casernes->taille_actuelle++;
}

void collection_casernes_liberer(t_collection_casernes* collection_casernes)
{
    int i;

    for(i=0;i<collection_casernes->taille_actuelle;i++)
    {
        caserne_liberer(collection_casernes->caserne[i]);
    }
    free(collection_casernes->caserne);
    free(collection_casernes);
}

void collection_casernes_reallouer(t_collection_casernes* collection_casernes)
{
    collection_casernes->taille_max=3*collection_casernes->taille_max/2;
    collection_casernes->caserne=realloc(collection_casernes->caserne,collection_casernes->taille_max*sizeof(t_caserne*));
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

void collection_casernes_afficher(t_collection_casernes* collection_casernes,int niveau)
{
    int i;
    for(i=0; i<collection_casernes->taille_actuelle; i++)
    {
        caserne_afficher(collection_casernes->caserne[i],niveau);
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
        collection_centrale_reallouer(collection_centrale);
    }
    collection_centrale->centrale[collection_centrale->taille_actuelle]=new_centrale;
    collection_centrale->taille_actuelle++;
}

void collection_centrale_liberer(t_collection_centrale* collection_centrale)
{
    int i;

    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        centrale_liberer(collection_centrale->centrale[i]);
    }
    free(collection_centrale->centrale);
    free(collection_centrale);
}

void collection_centrale_reallouer(t_collection_centrale* collection_centrale)
{
    collection_centrale->taille_max=3*collection_centrale->taille_max/2;
    collection_centrale->centrale=realloc(collection_centrale->centrale,collection_centrale->taille_max*sizeof(t_centrale*));
}

void collection_centrale_afficher(t_collection_centrale* collection_centrale,int niveau)
{
    int i;
    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        centrale_afficher(collection_centrale->centrale[i],niveau);
    }
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
                quantitee=habitation_nbhabitants(collection_habitation->habitation[j]); ///retourne le nombre d'habitant en fonction du stade de développement
                if(collection_centrale->centrale[i]->capacite.capacite_disponible>=quantitee)
                {
                    centrale_distribuer(collection_centrale->centrale[i],collection_habitation->habitation[j],quantitee);
                }
            }
        }
    }
}

void collection_centrale_debut_tour(t_collection_centrale* collection_centrale)
{
    int i;
    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        centrale_debut_tour(collection_centrale->centrale[i]);
    }
}

int collection_centrale_elec_disponible(t_collection_centrale* collection_centrale)
{
    int elec_totale_dispo = 0;
    int i;
    for(i=0;i<collection_centrale->taille_actuelle;i++)
    {
        elec_totale_dispo += centrale_elec_disponible(collection_centrale->centrale[i]);
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
        collection_chateau_reallouer(collection_chateau);
    }
    collection_chateau->chateau[collection_chateau->taille_actuelle]=new_chateau;
    collection_chateau->taille_actuelle++;
}

void collection_chateau_liberer(t_collection_chateau* collection_chateau)
{
    int i;

    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        chateau_liberer(collection_chateau->chateau[i]);
    }
    free(collection_chateau->chateau);
    free(collection_chateau);
}

void collection_chateau_reallouer(t_collection_chateau* collection_chateau)
{
    collection_chateau->taille_max=3*collection_chateau->taille_max/2;
    collection_chateau->chateau=realloc(collection_chateau->chateau,collection_chateau->taille_max*sizeof(t_chateau*));
}

void collection_chateau_afficher(t_collection_chateau* collection_chateau,int niveau)
{
    int i;
    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        chateau_afficher(collection_chateau->chateau[i],niveau);
    }
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

void collection_chateau_distribuer_proche(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs)
{
    int i=0,j,distributeur,minimum;
    while(i<collection_habitation->taille_actuelle)
    {
        minimum=INFINI;
        distributeur=-1;
        for(j=0; j<collection_chateau->taille_actuelle; j++)
        {
            if((longueurs[j][i]<minimum)&&(collection_chateau->chateau[j]->capacite.capacite_disponible!=0)&&(longueurs[j][i]!=0))
            {
                distributeur=j;
                minimum=longueurs[j][i];
            }
        }
        if(distributeur!=-1)
        {
            chateau_distribuer(collection_chateau->chateau[distributeur],collection_habitation->habitation[i]);
        }
        i++;
    }
}

void collection_chateau_distribuer(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs_chateaux_habitations)
{
    if((collection_habitation->taille_actuelle!=0)&&(collection_chateau->taille_actuelle!=0))
    {
        collection_chateau_distribuer_minimiser(collection_chateau,collection_habitation,longueurs_chateaux_habitations);
    }
}

void collection_chateau_distribuer_minimiser(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueur)
{
    int i=0;
    int eau_dispo;
    int taille1,taille2,compteur,j,compteur2,k,l;
    int mini,distributeur=0,receveur;
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
                    if((longueur[k][j]!=0)&&(longueur[k][j]<mini)&&(collection_habitation->habitation[j]->electricite==1)&&(collection_habitation->habitation[j]->eau!=1))
                    {
                        mini=longueur[k][j];
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
                    if(longueur[compteur2][receveur]!=0)
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
                        if((longueur[compteur2][receveur]!=0)&&(longueur[compteur2][receveur]<mini)&&(collection_chateau->chateau[compteur2]->capacite.capacite_disponible!=0))
                        {
                            distributeur=compteur2;
                            mini=longueur[compteur2][receveur];
                        }
                    }//on alimente l'habitation et on tient à jours la quantitee d'eau dispo
                    eau_dispo-=chateau_distribuer(collection_chateau->chateau[distributeur],collection_habitation->habitation[receveur]);
                }
            }

        }
        i=compteur;
    }
}

int collection_chateau_eau_disponible(t_collection_chateau* collection_chateau)
{
    int eau_totale_dispo = 0;
    int i;

    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        eau_totale_dispo = eau_totale_dispo + chateau_eau_disponible(collection_chateau->chateau[i]);
    }

    return eau_totale_dispo;
}

void collection_chateau_debut_tour(t_collection_chateau* collection_chateau)
{
    int i;
    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        chateau_debut_tour(collection_chateau->chateau[i]);
    }
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
        collection_habitation_reallouer(collection_habitation);
    }
    collection_habitation->habitation[collection_habitation->taille_actuelle]=new_habitation;
    collection_habitation->taille_actuelle++;
}

void collection_habitation_liberer(t_collection_habitation* collection_habitation)
{
    int i;

    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        habitation_liberer(collection_habitation->habitation[i]);
    }
    free(collection_habitation->habitation);
    free(collection_habitation);
}

void collection_habitation_actualiser_timer(t_collection_habitation* collection_habitation)
{
    int i;

    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        habitation_actualiser_timer(collection_habitation->habitation[i]);
    }
}

void collection_habitation_reallouer(t_collection_habitation* collection_habitation)
{
    collection_habitation->taille_max=3*collection_habitation->taille_max/2;
    collection_habitation->habitation=realloc(collection_habitation->habitation,collection_habitation->taille_max*sizeof(t_habitation*));
}

void collection_habitation_afficher(t_collection_habitation* collection_habitation,int niveau)
{
    int i;
    for(i=0;i<collection_habitation->taille_actuelle;i++)
    {
        habitation_afficher(collection_habitation->habitation[i],niveau);
    }
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
        habitation_debut_tour(collection_habitation->habitation[i]);
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

char touche;
char bouton;
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

void line_epaisse(BITMAP *bmp, int x1, int y1, int x2, int y2, int coul)
{
    line(bmp, x1, y1, x2, y2, coul);
    line(bmp, x1+1, y1, x2+1, y2, coul);
    line(bmp, x1-1, y1, x2-1, y2, coul);
    line(bmp, x1, y1+1, x2, y2+1, coul);
    line(bmp, x1, y1-1, x2, y2-1, coul);
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

void date_liberer(t_date* d)
{
    free(d);
}

/////////////////editeur.c////////////////////////
t_editeur* editeur_allouer(int mode_de_jeu) // sera envoyé par le menu
{
    t_editeur* nouv = NULL;

    nouv = (t_editeur*)malloc(1*sizeof(t_editeur));

    nouv->maville = ville_allouer_initialiser(mode_de_jeu);
    nouv->boite_a_outils = boiteaoutils_creer();

    return nouv;
}

void editeur_gerer(t_editeur* ed)
{
    boiteaoutils_gerer(ed->boite_a_outils);
    ville_gerer(ed->maville, ed->boite_a_outils->bouton_choisi);
}

void editeur_afficher(t_editeur* ed)
{
    // on vide le buffer page
    clear_bitmap(page);

    rectfill(page, 0, 0, TAILLE_FENETRE_W, TAILLE_FENETRE_H, COUL_FOND1);
    // on construit notre affichage sur le buffer page
    ville_afficher(ed->maville,ed->boite_a_outils->bouton_choisi);
    boiteaoutils_afficher(ed->boite_a_outils);
    /***** il faudra aussi rajouter les variables du style: argent, nombre d'habitants etc..*****/
    textprintf_ex(page,font,112,20,makecol(255,255,255),-1,"Nombre habitants: %d",ed->maville->nb_habitants);
    textprintf_ex(page,font,300,20,makecol(255,255,255),-1,"Argent: %d",ed->maville->argent);
    textprintf_ex(page,font,500,20,makecol(255,255,255),-1,"Temps de jeu: %d:%d:%.0f",ed->maville->temps_de_jeu->heures,ed->maville->temps_de_jeu->minutes,ed->maville->temps_de_jeu->secondes);
    textprintf_ex(page,font,112,40,makecol(255,255,255),-1,"Elec dispo:%d/%d",ed->maville->qte_elec.capacite_disponible,ed->maville->qte_elec.capacite_max);
    textprintf_ex(page,font,500,40,makecol(255,255,255),-1,"Eau dispo:%d/%d",ed->maville->qte_eau.capacite_disponible,ed->maville->qte_eau.capacite_max);
    if(ed->maville->pause == PAUSE_ACTIVEE) textprintf_ex(page,font,700,40,makecol(255,255,255),-1,"PAUSE ACTIVEE");

    // on affiche le buffer page sur l'écran
    //blit(page,screen,0,0,0,0, SCREEN_W, SCREEN_H);
    stretch_blit(page, screen, 0, 0, TAILLE_FENETRE_W, TAILLE_FENETRE_H, 0, 0, SCREEN_W, SCREEN_H);// permet de gérer les ordis
    // incapables d'ouvrir un mode graphique 1024*768
}

void editeur_liberer(t_editeur* ed)
{
    boiteaoutils_liberer(ed->boite_a_outils);
    ville_liberer(ed->maville);

    free(ed);
}

/////////////////file.c////////////////////////
// Alloue une file
t_file* file_creer()
{
    return liste_creer();
}

// Détruit une file
void file_detruire(t_file* file, tpf_detruire detruire)
{
    liste_detruire(file,detruire);
}

// Vide une file
void file_vider(t_file* file, tpf_detruire detruire)
{
    liste_vider(file,detruire);
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

// Retourne l'élément du sommet de la file, sans le retirer de la file
void* file_elem_sommet(t_file* file)
{
    return liste_elem_tete(file);
}

// Retourne 1 si la file est vide, 0 sinon
int file_vide(t_file* file)
{
    return liste_vide(file);
}

// Retourne une copie (profonde) de la file reçue en paramètre
t_file* file_copier(t_file* file,tpf_copier copier)
{
    return liste_copier(file,copier);
}

// Retourne le nombre d'éléments de la file
int file_taille(t_file* file)
{
    return liste_taille(file);
}

// Affichage bilan allocations/libérations
void file_bilan(t_file* file)
{
    liste_bilan(file);
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

int obtenir_chemin_chargement(char* chemin)
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
    ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER;
    res = GetOpenFileName(&ofn);
    if (res==1)
    {
        // si choix du fichier réussi
        strncpy(chemin,ofn.lpstrFile,TAILLE_CHAINE);
    }
    else printf("Choix du fichier annule\n");

    return res;
}

int verif_type_fichier(const char* chemin)
{
    int ok;
    char* ext;

    ext = return_extension_blindee(chemin);
    if (strncmp(ext,"txt",3) == 0)
    {
        ok=1;
        printf("Extension OK\n");
    }
    else
    {
        ok=0;
        printf("Fichier non accepte (extension non reconnue)\n");
    }

    free(ext);

    return ok;
}

char* return_extension_blindee(const char* chemin)
{
    int i=0;
    int j=0;
    char* ext = NULL;
    ext= (char*) malloc(50*sizeof(char));
    while(chemin[i]!= '.' && chemin[i]!='\0')
    {
        i++;
    }
    i++;
    while(chemin[i]!='\0')
    {
        ext[j]=chemin[i];
        i++;
        j++;
    }
    ext[j]='\0';

    return ext;
}

int remplit_chemin_chargement(char* chemin)
{
    int choix_fini;
    int type_fichier_ok;

    choix_fini = obtenir_chemin_chargement(chemin);
    if(choix_fini)
    {
        type_fichier_ok = verif_type_fichier(chemin);
    }
    if(choix_fini && type_fichier_ok)
    {
        // on est certain qu'un fichier a bien été choisi, et qu'il est bien de type txt
        printf("Chemin: %s\n",chemin);
        return 1;
    }
    else return 0;
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

void recup_nom_fichier(const char* chemin, char* nom)
{
    char temp[TAILLE_BUFFER];
    int i= strlen(chemin)-1; // on va parcourir la chaine chemin en partant de la derniere case, d'indice i
    int j= 0;

    while(chemin[i] != '\\') // tant que l'on ne tombe pas sur un "\"
    {
        temp[j] = chemin[i]; // on met dans tmp le caractère analysé
        j++;
        i--;
    }
    temp[j]='\0';
    // on obtient une chaine inversée
    // printf("temp: %s\n",temp);

    j=0;
    for(i=strlen(temp)-1;i>=0;i--) // on réinverse la chaine
    {
        nom[j]=temp[i];
        j++;
    }
    nom[j]='\0';
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
        for(i=0; i<NB_IMG_ROUTES; i++)
        {
            sprintf(nom_fichier,"fichiers/images/jeu/route%d-%d.bmp",j,i);
            nouv->route[j][i] = chargerImage(nom_fichier);

        }
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
        for(i=0; i<NB_IMG_ROUTES; i++)
        {
            destroy_bitmap(graph->route[j][i]);
        }
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

void habitation_liberer(t_habitation* h)
{
    free(h->chateaux_fournisseurs);
    free(h);
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
            case_remplir(kase[i][j],HABITATION,h);
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

int habitation_comparer(const void* a, const void* b) // il manque un degré de const, pourquoi?
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

void habitation_charger(t_habitation* hab, FILE* fp)
{
    fscanf(fp,"%d %d %d %f %d",&hab->case_de_referenceX,&hab->case_de_referenceY,&hab->stade,&hab->chrono,&hab->feu);
}

void habitation_sauvegarder(t_habitation* hab, FILE* fp)
{
    fprintf(fp,"%d %d %d %f %d\n",hab->case_de_referenceX, hab->case_de_referenceY,hab->stade, hab->chrono, hab->feu);
}

void habitation_afficher(t_habitation* hab,int niveau)
{
    int img_utilisee;

    if(hab->feu >= EN_FEU)
    {
        img_utilisee=0;
    }
    else
    {
        img_utilisee=1;
    }


    switch(hab->stade)
    {
        case 0:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
            {
                draw_lit_sprite(graphs->buffer_ville,graphs->ruine,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
            }
            else draw_sprite(graphs->buffer_ville,graphs->ruine,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
            break;
        case 1:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
            {
                draw_lit_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
            }
            else draw_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
            break;
        case 2:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
            {
                draw_lit_sprite(graphs->buffer_ville,graphs->cabane[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
            }
            else draw_sprite(graphs->buffer_ville,graphs->cabane[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
            break;
        case 3:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
            {
                draw_lit_sprite(graphs->buffer_ville,graphs->maison[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
            }
            else draw_sprite(graphs->buffer_ville,graphs->maison[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
            break;
        case 4:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
            {
                draw_lit_sprite(graphs->buffer_ville,graphs->immeuble[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
            }
            else draw_sprite(graphs->buffer_ville,graphs->immeuble[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
            break;
        case 5:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
            {
                draw_lit_sprite(graphs->buffer_ville,graphs->gratte_ciel[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
            }
            else draw_sprite(graphs->buffer_ville,graphs->gratte_ciel[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
            break;
    }
    if((hab->feu)&&(hab->protegee))
    {
        draw_sprite(graphs->buffer_ville,graphs->pompier,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
    }
}

void habitation_actualiser_timer(t_habitation* habitation)
{
    habitation->chrono = habitation->chrono + PAS_DU_TIMER;
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
        quantitee_future-=habitation_nbhabitants(habitation);
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

void habitation_debut_tour(t_habitation* hab)
{
    int i,alea;
    hab->eau =0;
    hab->electricite=0;
    hab->id_centrale_fournisseuse.caseX = -1;
    hab->id_centrale_fournisseuse.caseX = -1;
    ///DECLARATION ALEATOIRE D'UN INCENDIE
    if(hab->stade>=STADE_CABANE)
    {
        if(!hab->feu)
        {
            alea=rand()%PROBABILITE_INCENDIE+1;
            if(alea==PROBABILITE_INCENDIE)
            {
                hab->feu=EN_FEU;
            }
        }
        else
        {
            hab->feu+=1;
        }
    }
    hab->protegee=PAS_PROTEGEE;

    for(i=0;i<FOURNISSEUR_MAX;i++)
    {
        hab->chateaux_fournisseurs[i].qte_eau_distribuee=0;
        hab->chateaux_fournisseurs[i].id_fournisseur.caseX= -1;
        hab->chateaux_fournisseurs[i].id_fournisseur.caseY= -1;
    }
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

// Destructeur
void liste_detruire(t_liste* lst, tpf_detruire detruire)
{
    // pour détruire la liste, on va commencer par la vider.
    // En effet, il faut détruire (free) chaque maillon un par un.
    // on garde en tête que pour chaque "malloc" il faut un "free"
    // -> on a fait un malloc par nouveau maillon --> un free par maillon sera nécessaire

    liste_vider(lst,detruire);

    // on a détruit tous les maillons
    // on peut donc détruire l'instance "liste" (la structure qui contient : la longueur de la liste et le pointeur sur la tête
    // -> on a fait un malloc pour créer la liste --> un free pour libérer la liste

    free(lst);
}

// Vider la liste sans la détruire
void liste_vider(t_liste* lst, tpf_detruire detruire)
{
    while(!liste_vide(lst))
    {
        liste_supprimer_tete(lst,detruire);
    }
}

// Constructeur par copie
t_liste* liste_copier(t_liste* lst, tpf_copier copier)
{
    t_liste* listecopie;
    void* elem;
    listecopie = liste_creer();

    for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
    {
        elem = copier(liste_elem_courant(lst));
        liste_ajout_queue(listecopie,elem);
    }

    return listecopie;
}

// Ajout d'élément en tête
void liste_ajout_tete(t_liste* lst, void* elem)
{
    t_maillon* nouv;
    nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
    nouv->elem = elem; // on accroche la donnée reçue en paramètre
    nouv->p_suiv = NULL;

    nb_maillons_alloues++; // on augmente le compteur de bilan mémoire

    if(liste_vide(lst)) // si la liste était vide
    {
        nouv->p_suiv = lst->p_tete; // on fait pointer le nouveau maillon sur la tête actuelle
        lst->p_tete = nouv; // on met à jour la tete
        lst->p_queue = nouv; // on met à jour la queue aussi
    }
    else
    {
        nouv->p_suiv = lst->p_tete; // on fait pointer le nouveau maillon sur la tête actuelle
        lst->p_tete = nouv; // on met à jour la tete
    }
    lst->longueur = lst->longueur + 1;
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

// Nombre d'éléments référencés
int liste_taille(t_liste* lst)
{
    return lst->longueur;
}

// Retourne 1 (Vrai) si la liste est vide
int liste_vide(t_liste* lst)
{
    return (lst->longueur ==0) ? 1 : 0;
}

// Accès élément en tête
void* liste_elem_tete(t_liste* lst)
{
    return lst->p_tete->elem;
}

// Accès élément en queue
void* liste_elem_queue(t_liste* lst)
{
    return lst->p_queue->elem;
}

// Accès élément courant
void* liste_elem_courant(t_liste* lst)
{
    return lst->p_courant->elem;
}

void liste_supprimer_tete(t_liste* lst, tpf_detruire detruire)
{
    // NOUVELLE VERSION
    detruire(liste_recup_tete(lst));

    // ANCIENNE VERSION, Code répétitif, on aurait pu utiliser liste_recup_tete() puis free les données de la tête.
    /*t_maillon* tmp;

    if(!liste_vide(lst))
    {
        tmp = lst->p_tete->p_suiv;
        detruire(lst->p_tete->elem); // on détruit les données du maillon
        free(lst->p_tete); // on détruit le maillon
        lst->p_tete = tmp; // on fait pointer la tête sur le successeur du maillon détruit
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }
    else
    {
        printf("erreur, impossible supprimer tete, la liste est vide\n");
    }*/
}

// Initialiser un parcours
void liste_demarrer(t_liste* lst)
{
    lst->p_courant = lst->p_tete;
}

// Retourne 1 (Vrai) s'il reste encore des éléments à parcourir
int liste_encore(t_liste* lst)
{
    // attention ne pas faire lst->p_courant->psuiv sinon on réagit un niveau trop tôt
    return (lst->p_courant != NULL) ? 1 : 0;

}

// Déplacement du courant au suivant
void liste_suivant(t_liste* lst)
{
    lst->p_courant = lst->p_courant->p_suiv;
}

// Affichage bilan allocations/libérations
void liste_bilan()
{
    printf("\n\n");
    printf("///////////////////////////////////////\n");
    printf("Nombre de maillons alloues: %d\n",nb_maillons_alloues);
    printf("Nombre de maillons liberes: %d\n",nb_maillons_liberes);
    printf("Nombre de maillons encore reserves: %d\n",nb_maillons_alloues-nb_maillons_liberes);
    printf("\n");
    printf("Attention cette fonction ne verifie pas si le CONTENU des maillons a ete libere proprement.\n");
    printf("Cette fonction sert juste a verifier qu'on a pas perdu des maillons.\n");
    printf("///////////////////////////////////////\n\n");
}

void liste_afficher(t_liste* lst, tpf_afficher afficher)
{
    for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
    {
        afficher(liste_elem_courant(lst));
    }
}

void liste_fusionner(t_liste* lste1, t_liste* lste2, tpf_copier copier)
{
void* elem;
// on parcourt la liste2, et une ajoute une COPIE de chacun de ses éléments à la liste1
for(liste_demarrer(lste2); liste_encore(lste2); liste_suivant(lste2))
{
elem = copier(liste_elem_courant(lste2));
liste_ajout_queue(lste1,elem);
}
}

void liste_supprimer_queue(t_liste* lst, tpf_detruire detruire)
{
    // NOUVELLE VERSION
    detruire(liste_recup_queue(lst));

    // ANCIENNE VERSION, Code répétitif, on aurait pu utiliser liste_recup_queue() puis free les données de la queue.
    /*t_maillon* tmp;

    if (liste_vide(lst)) // cas de la liste vide
    {
        printf("liste vide, rien à supprimer\n");
    }

    else if (liste_taille(lst) == 1) // cas de la liste à un élément
    {
        detruire(lst->p_tete->elem);
        free(lst->p_tete);
        lst->p_tete = NULL;
        lst->p_queue = NULL;
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }

    else // cas de la liste à plus d'un élément
    {
        tmp = lst->p_tete;
        while(tmp->p_suiv->p_suiv != NULL) // autorisé car on sait qu'il y a au moins 2 élements dans la liste
        {
            tmp = tmp->p_suiv;
        }
        detruire(tmp->p_suiv->elem); // on détruit les données du maillon de queue
        free(tmp->p_suiv); // on détruit le maillon de queue
        tmp->p_suiv = NULL; // on indique que l'avant dernier maillon devient le dernier
        lst->p_queue = tmp; // on met à jour la queue
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }*/
}

void liste_dereferencer_tete(t_liste* lst)
{
    t_maillon* tmp;

    if(!liste_vide(lst))
    {
        tmp = lst->p_tete->p_suiv;
        free(lst->p_tete); // on détruit le maillon, mais on n'a pas détruit les données du maillon, pointées par elem
        lst->p_tete = tmp; // on fait pointer la tête sur le successeur du maillon détruit
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }
    else
    {
        printf("erreur, impossible supprimer tete, la liste est vide\n");
    }
}

void liste_dereferencer(t_liste* lst)
{
    while(!liste_vide(lst))
    {
        liste_dereferencer_tete(lst);
    }
}

void liste_trier(t_liste* lst, tpf_trier trier)
{
    int i;
    int taille_liste;
    void** tab_elem = NULL;

    taille_liste = liste_taille(lst);

    // on ne trie que les listes de plus d'un élément ..
    if (taille_liste > 1)
    {
        tab_elem = (void**) malloc(taille_liste*sizeof(void*)); // on alloue un tableau de pointeurs sur elements

        // on parcourt la liste,on référence chaque élément dans le tableau temporaire
        i=0;
        for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
        {
            tab_elem[i] = liste_elem_courant(lst);
            i++;
        }

        // on ne détruit pas la liste, on va la réutiliser
        // on ne vide pas la liste, car les éléments listés sont aussi référencés dans le tableau
        // -> on ne veut pas détruire les éléments listés
        // --> on veut juste déréférencer tous les maillons de notre liste
        // ( = obtenir une liste vide, sans avoir détruit les éléments, ils sont encore en mémoire quelque part)
        liste_dereferencer(lst);

        qsort(tab_elem,taille_liste,sizeof(void*),trier); // on trie le tableau

        // on recopie le tableau trié dans la liste qui ne comporte actuellement plus aucun élément
        for(i=0; i<taille_liste; i++)
        {
            liste_ajout_queue(lst,tab_elem[i]);
        }

        // on free le tableau temporaire, mais pas ses éléments, car on les a ajoutés à la liste !
        free(tab_elem);
    }
    else
    {
        printf("tri inutile, on traite une liste de moins de 2 elements\n");
    }

}

void liste_ajout_trie(t_liste* lst, void* elem, tpf_trier trier)
{
    // On va gérer 4 cas séparément:
    // _ l'ajout dans une liste vide
    // _ l'ajout en tete
    // _ l'ajout en queue
    // _ l'ajout au milieu

    t_maillon* pprec = NULL;

    // cas de l'ajout dans une liste vide
    if(liste_taille(lst) == 0)
    {
        liste_ajout_tete(lst,elem);
    }

        // cas de l'ajout en tête ( = si l'élément à ajouter est censé être placé avant la tete )
    else if(  (trier(elem,liste_elem_tete(lst)))  <   0   )
    {
        liste_ajout_tete(lst,elem);
    }
        // cas de l'ajout en queue ( = si l'élément à ajouter est censé être placé après la queue )
    else if( (trier(elem,liste_elem_queue(lst)))  >  0 )
    {
        liste_ajout_queue(lst,elem);
    }
        // cas de l'ajout au milieu
    else
    {
        t_maillon* nouv;
        nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
        nouv->elem = elem; // on accroche la donnée reçue en paramètre
        nouv->p_suiv = NULL;
        nb_maillons_alloues++; // on augmente le compteur de bilan mémoire
        lst->longueur = lst->longueur + 1;

        // on parcourt toute la liste, et on regarde si l'élément doit être placé avant l'élément actuel
        // le 1er tour de la boucle for traite le cas de l'ajout en tête, ce qui bugguerait vu les actions faites
        // mais le cas de l'ajout en tête est impossible ici, car il a déjà été traité avant
        pprec = lst->p_tete;
        for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
        {
            if(trier(elem,liste_elem_courant(lst)) < 0 )
            {
                nouv->p_suiv = lst->p_courant;
                pprec->p_suiv = nouv;
                break; // on arrete de parcourir la liste, c'est bon, on a placé notre élément
            }
            pprec = lst->p_courant;
        }
    }
}

// ATTENTION, lst_elem_a_supprimer est une liste de REFERENCES vers des éléments existant dans lst.
// les éléments de lst_elem_a_supprimer sont CEUX de lst.
// ce ne sont PAS des copies
void liste_supprimer_partie(t_liste* lst, t_liste* lst_elem_a_supprimer, tpf_detruire detruire)
{
    // on parcourt la liste référençant les éléments à supprimer
    for(liste_demarrer(lst_elem_a_supprimer); liste_encore(lst_elem_a_supprimer); liste_suivant(lst_elem_a_supprimer))
    {
        // on supprime dans lst l'élément actuel de lst_elem_a_supprimer
        liste_supprimer_precis(lst,liste_elem_courant(lst_elem_a_supprimer),detruire);
    }

    // on enlève tous les maillons de la liste, sans détruire les éléments pointés car on vient de le faire avant!
    liste_dereferencer(lst_elem_a_supprimer);
}

void liste_supprimer_precis(t_liste* lst, void* elem, tpf_detruire detruire)
{
    /*
    Le  cas de la liste à un élément (l'élément cherché est pointé par la tete ET la queue) est géré par le elseif
    -> on ne fera pas les deux cas ;)
    */

    int trouve = 0; // variable de debug
    t_maillon* tmp = NULL;
    t_maillon* tmp2 = NULL;

    if(liste_taille(lst) == 0)
    {
        printf("GROS BUG: L'element qu'on cherche ne pourra pas etre trouve car la liste est vide\n");
    }
    else if(liste_elem_tete(lst) == elem) // on compare les adresses pour savoir si on est sur le bon maillon
    {
        trouve = 1;
        liste_supprimer_tete(lst,detruire);
    }
    else if(liste_elem_queue(lst) == elem) // // on compare les adresses pour savoir si on est sur le bon maillon
    {
        trouve = 1;
        liste_supprimer_queue(lst,detruire);
    }
    else // le maillon cherché n'est ni en tête ni en queue
    {
        tmp = lst->p_tete;
        // tant qu'on est pas sur le maillon précédant celui à supprimer
        // et tant qu'on n'est pas à la fin de la liste (impossible normalement car on doit trouver l'élément cherché)
        while(tmp->p_suiv->elem != elem && tmp->p_suiv != NULL )
        {
            tmp = tmp->p_suiv;
        }
        // on vérifie qu'on a bien trouvé le maillon qu'on veut supprimer
        if (tmp->p_suiv->elem == elem)
        {
            trouve = 1;

            tmp2 = tmp->p_suiv->p_suiv; // autorisé car on sait que tmp n'est pas la queue de la liste (cas traité avant)
            detruire(tmp->p_suiv->elem); // on détruit les données du maillon
            free(tmp->p_suiv); // on détruit le maillon
            tmp->p_suiv = tmp2; // on reforme les liens autour du maillon supprimé

            lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
            nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
        }
    }

    if (trouve == 0) // DEBUG
    {
        printf("GROS BUG, on a parcouru toute la liste sans tomber sur l'element qu'on cherchait a supprimer\n");
    }
}

t_liste* liste_rechercher(t_liste* lst, tpf_recherche recherche)
{
    // On devrait recevoir en paramètre un paramètre facultatif
    // qui peut être parfois nécessaire dans la fonction de recherche
    // si l'on reçoit NULL, ça veut dire que l'utilisateur ne veut pas l'utiliser dans sa fonction de recherche

    t_liste* liste_trouvee = NULL;
    liste_trouvee = liste_creer();

    // on parcourt toute la liste
    for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
    {
        // si l'élément courant est interessant
        if(recherche(liste_elem_courant(lst)) == 1)
        {
            // on ajoute l'élément à la liste des éléments trouvés
            liste_ajout_queue(liste_trouvee,liste_elem_courant(lst));
        }
    }

    return liste_trouvee;
}

void liste_ajout_avant(t_liste* lst, void* elem_a_inserer, void* elem_ref)
{
    // On va gérer 4 cas séparément:
    // _ l'ajout dans une liste vide (impossible dans la logique de la fonction)
    // _ l'ajout en tete
    // _ l'ajout au milieu

    t_maillon* pprec = NULL;

    // cas de l'ajout dans une liste vide ou d'un élément de référence à NULL
    if((liste_taille(lst) == 0) || (elem_ref == NULL))
    {
        printf("GROS BUG, on ne peut pas ajouter avant l'element demande car il n'est pas dans la liste: la liste est vide\n");
        printf("Ou bien tu as envoye NULL comme element de reference.\n");
    }

        // cas de l'ajout en tête ( = si l'élément à ajouter est censé être placé avant la tete )
    else if(liste_elem_tete(lst) == elem_ref)
    {
        liste_ajout_tete(lst,elem_a_inserer);
    }
        // cas de l'ajout au milieu
    else
    {
        t_maillon* nouv;
        nouv = (t_maillon*) malloc(1*sizeof(t_maillon));
        nouv->elem = elem_a_inserer; // on accroche la donnée reçue en paramètre
        nouv->p_suiv = NULL;
        nb_maillons_alloues++; // on augmente le compteur de bilan mémoire
        lst->longueur = lst->longueur + 1;

        // on parcourt toute la liste, et on regarde si l'élément doit être placé avant l'élément actuel
        // le 1er tour de la boucle for traite le cas de l'ajout en tête, ce qui bugguerait vu les actions faites
        // mais le cas de l'ajout en tête est impossible ici, car il a déjà été traité avant
        pprec = lst->p_tete;
        for(liste_demarrer(lst); liste_encore(lst); liste_suivant(lst))
        {
            if(liste_elem_courant(lst) == elem_ref)
            {
                nouv->p_suiv = lst->p_courant;
                pprec->p_suiv = nouv;
                break; // on arrete de parcourir la liste, c'est bon, on a placé notre élément
            }
            pprec = lst->p_courant;
        }
    }
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

void* liste_recup_queue(t_liste* lst)
{
    t_maillon* tmp = NULL;
    void* elem_queue = NULL;

    if (liste_vide(lst)) // cas de la liste vide
    {
        printf("liste vide, rien à supprimer\n");
    }

    else if (liste_taille(lst) == 1) // cas de la liste à un élément
    {
        elem_queue = lst->p_tete->elem;
        free(lst->p_tete); // on détruit le maillon mais pas les données
        lst->p_tete = NULL;
        lst->p_queue = NULL;
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }

    else // cas de la liste à plus d'un élément
    {
        tmp = lst->p_tete;
        while(tmp->p_suiv->p_suiv != NULL) // autorisé car on sait qu'il y a au moins 2 élements dans la liste
        {
            tmp = tmp->p_suiv;
        }
        elem_queue = tmp->p_suiv->elem;
        free(tmp->p_suiv); // on détruit le maillon de queue, mais pas les données
        tmp->p_suiv = NULL; // on indique que l'avant dernier maillon devient le dernier
        lst->p_queue = tmp; // on met à jour la queue
        lst->longueur = lst->longueur -1; // on diminue la longueur de la liste
        nb_maillons_liberes++;  // on augmente le compteur de bilan mémoire
    }

    return elem_queue;
}

/////////////////menu.c////////////////////////
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
    /*for(i=0;i<NB_IMG_OISEAU;i++)
    {
        destroy_bitmap(g->oiseau[i]);
    }*/
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

    /*for(i=0;i<NB_IMG_OISEAU;i++)
    {
        sprintf(tmp,"fichiers/images/menu/sousmenu/oiseau%d.bmp",i);
        g->oiseau[i] = chargerImage(tmp);
    }*/

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

        /*draw_sprite(page,graph.graphsdusousmenu.oiseau[index],posx,120);
        posx+=5;
        if(cpt% 4== 0)
            index++;
        if(index>=NB_IMG_OISEAU)
            index=0;*/

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

void route_liberer(t_route* route)
{
    free(route);
}

void route_actualiser(t_route* route,t_case*** kase)
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
}

void route_actualiser_voisins(t_route* route,t_case*** kase)
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
}

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

    route_actualiser(route,kase);

    case_remplir(kase[ligne][colonne],ROUTE,route);
    route_actualiser_voisins(route,kase);
}

void route_afficher(t_route* route,int niveau)
{
    draw_sprite(graphs->buffer_ville,graphs->route[niveau][route->type],1+TAILLE_CASE*route->case_de_referenceX,1+TAILLE_CASE*route->case_de_referenceY);
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
void terrain_liberer(t_case*** mat)
{
    int lig,col;

    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        for(col=0;col<NB_CASES_COL;col++)
        {
            case_free(mat[lig][col]);
        }
    }

    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        free(mat[lig]);
    }

    free(mat);
}

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

void ville_actualiser_timer(t_ville* v)
{
    clock_t temps_actuel = clock();

    if(      (((double)(temps_actuel- v->timer))/CLOCKS_PER_SEC)    >=    PAS_DU_TIMER   )
    {
        v->timer = temps_actuel;
        if(v->pause == PAUSE_DESACTIVEE)
        {
            date_actualiser(v->temps_de_jeu);
            collection_habitation_actualiser_timer(v->collec_habitations);
        }
    }
}

void ville_afficher_niveau_sol(t_ville* v, int bouton_boite_a_outil)
{
    int l,c;

    int mx,my; // CHANGEMENT DE REFERENTIEL POUR CONNAITRE LES COORDONNEES DE LA SOURIS DANS LA SUB-BITMAP DE JEU
    // (voir les premiers "define" de "define.h" -> "GAME"

    int lig,col; // permet de savoir dans quelle case la souris est actuellement

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
    collection_habitation_afficher(v->collec_habitations,v->niveau_visualisation);
    collection_centrale_afficher(v->collec_centrales,v->niveau_visualisation);
    collection_chateau_afficher(v->collec_chateaux,v->niveau_visualisation);
    collection_casernes_afficher(v->collec_casernes,v->niveau_visualisation);

    // AFFICHAGE DE L'IMAGE TEMPORAIRE QUI SUIT LA SOURIS:
    if(bouton_boite_a_outil == BOUTON_AJOUTER_ROUTE)
    {
        if((mx>0)&&(mx<GAME_W)&&(my>0)&&(my<GAME_H))
        {
            if(route_place_libre(col,lig,v->terrain))
            {
                //draw_lit_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*col,1+TAILLE_CASE*lig,makecol(0,250,0));
                draw_sprite(graphs->buffer_ville,graphs->route[NIVEAU_SOL][TYPE_ROUTE_HORIZONTALE],1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
            }
            else
            {
                draw_trans_sprite(graphs->buffer_ville,graphs->route[NIVEAU_SOL][TYPE_ROUTE_HORIZONTALE],1+TAILLE_CASE*col,1+TAILLE_CASE*lig);
            }
        }
    }
    else if(bouton_boite_a_outil == BOUTON_AJOUTER_HABITATION)
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
    else if(bouton_boite_a_outil == BOUTON_AJOUTER_CHATEAU)
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
    else if(bouton_boite_a_outil == BOUTON_AJOUTER_CENTRALE)
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
    else if(bouton_boite_a_outil == BOUTON_AJOUTER_CASERNE)
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
}

void ville_afficher_niveau_eau(t_ville* v)
{
    int l,c,compteur,eau_distribue=0;
    int mx,my; // CHANGEMENT DE REFERENTIEL POUR CONNAITRE LES COORDONNEES DE LA SOURIS DANS LA SUB-BITMAP DE JEU
    // (voir les premiers "define" de "define.h" -> "GAME"

    int lig,col; // permet de savoir dans quelle case la souris est actuellement
    t_habitation* tmp;
    t_chateau* cha;

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

    collection_habitation_afficher(v->collec_habitations,v->niveau_visualisation);
    collection_centrale_afficher(v->collec_centrales,v->niveau_visualisation);
    collection_chateau_afficher(v->collec_chateaux,v->niveau_visualisation);
    collection_casernes_afficher(v->collec_casernes,v->niveau_visualisation);

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
}

void ville_afficher_niveau_elec(t_ville* v)
{
    int l,c,compteur,elec_distribue=0;
    int mx,my; // CHANGEMENT DE REFERENTIEL POUR CONNAITRE LES COORDONNEES DE LA SOURIS DANS LA SUB-BITMAP DE JEU
    // (voir les premiers "define" de "define.h" -> "GAME"

    int lig,col; // permet de savoir dans quelle case la souris est actuellement
    t_habitation* tmp;
    t_centrale* cent;

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

    collection_habitation_afficher(v->collec_habitations,v->niveau_visualisation);
    collection_centrale_afficher(v->collec_centrales,v->niveau_visualisation);
    collection_chateau_afficher(v->collec_chateaux,v->niveau_visualisation);
    collection_casernes_afficher(v->collec_casernes,v->niveau_visualisation);

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
        habitation_sauvegarder(v->collec_habitations->habitation[i],fp);
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

// sera appelé comme ceci: ville_charger("test.txt",ed->maville);
void ville_charger(const char* nom_fichier,t_ville* v)
{
    FILE* fp;
    int temp,i,j,x,y;

    fp=fopen(nom_fichier,"r");
    if(fp==NULL)
    {
        printf("ERREUR FICHIER DE SAUVEGARDE");
        exit(1);
    }

    fscanf(fp,"%d",&v->mode);
    fscanf(fp,"%d",&v->argent);
    fscanf(fp,"%d %d %lf",&v->temps_de_jeu->heures,&v->temps_de_jeu->minutes,&v->temps_de_jeu->secondes);
    printf("h:%d,m:%d,s:%lf\n",v->temps_de_jeu->heures,v->temps_de_jeu->minutes,v->temps_de_jeu->secondes);
    ///ON CHARGE LES ROUTES ET ON LES PLACES
    for(i=0; i<NB_CASES_LIG; i++)
    {
        for(j=0; j<NB_CASES_COL; j++)
        {
            fscanf(fp,"%d",&temp);
            if(temp==1)
            {
                route_placer(route_creer(),j,i,v->terrain);
            }
        }
    }

    ///ON CHARGE LA COLLECTION D'HABITATION
    fscanf(fp,"%d",&temp);
    for(i=0; i<temp; i++)
    {
        collection_habitation_ajouter_habitation(v->collec_habitations,habitation_creer());
        habitation_charger(v->collec_habitations->habitation[i],fp);
        habitation_placer(v->collec_habitations->habitation[i],v->collec_habitations->habitation[i]->case_de_referenceX,v->collec_habitations->habitation[i]->case_de_referenceY,v->terrain);
    }

    ///ON CHARGE LA COLLECTION DE CHATEAUX
    fscanf(fp,"%d",&temp);
    for(i=0; i<temp; i++)
    {
        fscanf(fp,"%d %d",&x,&y);
        collection_chateau_ajouter_chateau(v->collec_chateaux,chateau_creer());
        v->collec_chateaux->chateau[i]->case_de_referenceX=x;
        v->collec_chateaux->chateau[i]->case_de_referenceY=y;
        chateau_placer(v->collec_chateaux->chateau[i],x,y,v->terrain);
    }

    ///ON CHARGE LA COLLECTION DE CENTRALES
    fscanf(fp,"%d",&temp);
    for(i=0; i<temp; i++)
    {
        fscanf(fp,"%d %d",&x,&y);
        collection_centrale_ajouter_centrale(v->collec_centrales,centrale_creer());
        v->collec_centrales->centrale[i]->case_de_referenceX=x;
        v->collec_centrales->centrale[i]->case_de_referenceY=y;
        centrale_placer(v->collec_centrales->centrale[i],x,y,v->terrain);
    }

    ///ON CHARGE LA COLLECTION DE CASERNES
    fscanf(fp,"%d",&temp);
    for(i=0; i<temp; i++)
    {
        fscanf(fp,"%d %d",&x,&y);
        collection_casernes_ajouter_caserne(v->collec_casernes,caserne_creer());
        v->collec_casernes->caserne[i]->case_de_referenceX=x;
        v->collec_casernes->caserne[i]->case_de_referenceY=y;
        caserne_placer(v->collec_casernes->caserne[i],x,y,v->terrain);
    }
    fclose(fp);
}

void ville_afficher(t_ville* v, int bouton_boite_a_outils)
{
    switch(v->niveau_visualisation)
    {
        case NIVEAU_SOL:
            ville_afficher_niveau_sol(v,bouton_boite_a_outils);
            break;
        case NIVEAU_EAU:
            ville_afficher_niveau_eau(v);
            break;
        case NIVEAU_ELEC:
            ville_afficher_niveau_elec(v);
            break;
    }
}

void ville_liberer(t_ville* v)
{
    int lig,col;
    for(lig=0; lig<NB_CASES_LIG; lig++)
    {
        for(col=0; col<NB_CASES_COL; col++)
        {
            if(v->terrain[lig][col]->type == ROUTE)
            {
                route_liberer(v->terrain[lig][col]->elem);
            }
        }
    }
    terrain_liberer(v->terrain);
    collection_habitation_liberer(v->collec_habitations);
    collection_casernes_liberer(v->collec_casernes);
    collection_chateau_liberer(v->collec_chateaux);
    collection_centrale_liberer(v->collec_centrales);
    date_liberer(v->temps_de_jeu);

    free(v);
}

void afficher_utilisations(t_ville* v)
{
    int i,j;
    if(key_press[KEY_R])
    {
        printf("\n\n\n");
        for(i=0; i<v->collec_chateaux->taille_actuelle; i++)
        {
            printf("Chateau (%d;%d): %d/%d\n",v->collec_chateaux->chateau[i]->case_de_referenceX,v->collec_chateaux->chateau[i]->case_de_referenceY,v->collec_chateaux->chateau[i]->capacite.capacite_disponible,v->collec_chateaux->chateau[i]->capacite.capacite_max);
        }
        for(i=0; i<v->collec_centrales->taille_actuelle; i++)
        {
            printf("Centrale (%d;%d): %d/%d\n",v->collec_centrales->centrale[i]->case_de_referenceX,v->collec_centrales->centrale[i]->case_de_referenceY,v->collec_centrales->centrale[i]->capacite.capacite_disponible,v->collec_centrales->centrale[i]->capacite.capacite_max);
        }
        for(i=0; i<v->collec_habitations->taille_actuelle; i++)
        {
            printf("Habitation (%d;%d): Stade: %d, Timer:%.2f, Eau: %d, Elec: %d\n",v->collec_habitations->habitation[i]->case_de_referenceX,v->collec_habitations->habitation[i]->case_de_referenceY,v->collec_habitations->habitation[i]->stade, v->collec_habitations->habitation[i]->chrono, v->collec_habitations->habitation[i]->eau,v->collec_habitations->habitation[i]->electricite);
            printf("Centrale fournisseuse: (%d;%d)\n",v->collec_habitations->habitation[i]->id_centrale_fournisseuse.caseX,v->collec_habitations->habitation[i]->id_centrale_fournisseuse.caseY);
            for(j=0; j<FOURNISSEUR_MAX; j++)
            {
                printf("Chateau fournisseur: (%d;%d): fourni %d eau\n",v->collec_habitations->habitation[i]->chateaux_fournisseurs[j].id_fournisseur.caseX,v->collec_habitations->habitation[i]->chateaux_fournisseurs[j].id_fournisseur.caseY,v->collec_habitations->habitation[i]->chateaux_fournisseurs[j].qte_eau_distribuee);
            }
        }
        printf("\n\n\n");
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

    if(v->pause == PAUSE_DESACTIVEE)
    {
        // Actions à effectuer à chaque tour de boucle
        ville_actualiser_timer(v);
        collection_habitation_debut_tour(v->collec_habitations,&(v->nb_habitants));
        collection_centrale_debut_tour(v->collec_centrales);
        collection_chateau_debut_tour(v->collec_chateaux);

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
    ville_gerer_actions_utilisateur(v,bouton_boite_a_outil);
}

void ville_gerer_actions_utilisateur(t_ville* v, int bouton_boite_a_outil)
{
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
                chateau_placer(chateau,col,lig,v->terrain);
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
                centrale_placer(centrale,col,lig,v->terrain);
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
                caserne_placer(caserne,col,lig,v->terrain);
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