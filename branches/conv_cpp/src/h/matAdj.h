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

#include <iostream>
#include <string>
#include "../h/sommet.h"

class MatAdj{

    private:

    int m_size;
    int** m_Matrix;

    public:

    MatAdj();
    MatAdj(int s);
    ~MatAdj();

    void iniMat (); // Renvoie la matrice d'adjacence
    void printMat (); // Affiche la matrice adjacente
    void PPG (Sommet* s); // Parcours en profondeur du graphe (appel sur PProfG)
    void PProfG (Sommet*, int i, int* t); // Parcours en profondeur du graphe (recursif)
    void PPGD (Sommet* s); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    void PProfGD (Sommet* s, int i, int* t); // Parcours en profondeur du graphe dual (recursif)
    int getTMin (Sommet* s, int x, int y); // Renvoie le temps min pour aller de x à y
    void getTMinProf (Sommet* s, int x, int y, int* t, int temp); // Parcours en profondeur

    int getSize();
    void setSize();

};


#endif // MATADJ_H_INCLUDED
