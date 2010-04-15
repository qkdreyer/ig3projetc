/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement cha�n�e d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

typedef struct sommet sommet;
struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Explor�
    int num;
    int deb;
    int fin;
};

void printCFC (sommet* s, int n); // Affiche les CFC
void iniSommet (sommet* s, int n); // Initialise les valeurs de la structure sommet
void triDecroissant (sommet* s, int n); // Renvoie l'ordre de parcours de la matrice duale (tri� par ordre d�croissant des temps d'acc�s finaux)

#endif // SOMMET_H_INCLUDED
