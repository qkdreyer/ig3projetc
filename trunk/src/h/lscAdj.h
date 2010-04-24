/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.h
OBJET            : liste simplement cha�n�e d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef LSCADJ_H_INCLUDED
#define LSCADJ_H_INCLUDED
#include "../h/sommet.h"

typedef struct cell cell;
struct cell {
    int val;
    struct cell* suiv;
};

typedef cell* liste;

liste* iniListe (int n); // Renvoie la liste d'adjacence
liste* ajoutFin (liste* l, int i, int x); // Ajoute � la fin de la liste l[i] la valeur x
void printListeAdj (liste* l, int n); // Affiche la liste adjacente
void DepthFirstSearch (liste* l, sommet* s, int n); // Parcours en profondeur du graphe
void DepthFirstSearchVisit (liste* l, sommet* s, int n, int i, int* t); // Parcours en profondeur du graphe (r�cursif)
void ShortestPath (liste* l, sommet* s, int n, int x); // Algorithme de Dijkstra : calcule les plus courts chemins � partir de x

#endif // LSCADJ_H_INCLUDED
