/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.h
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED
#include "../h/sommet.h"

int** iniMat (int n); // Renvoie la matrice d'adjacence
void printMat (int** M, int n); // Affiche la matrice adjacente
void PPG (int** M, sommet* s, int n); // Parcours en profondeur du graphe (appel sur PProfG)
void PProfG (int** M, sommet* s, int n, int i, int* t); // Parcours en profondeur du graphe (recursif)
void PPGD (int** M, sommet* s, int n); // Parcours en profondeur du graphe dual (appel sur PProfGD)
void PProfGD (int** M, sommet* s, int n, int i, int* t); // Parcours en profondeur du graphe dual (recursif)
void algoDijkstra (int** M, sommet* d, int n, int x); // Calcule les plus courts chemins � partir de x
void findCutVertex (int** M, sommet* s, int n);
void findCutVertexRec (int** M, sommet* s, int n, int i, int* t);

#endif // MATADJ_H_INCLUDED
