/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : ListeVoisins.cpp
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef LISTEVOISINS_H_INCLUDED
#define LISTEVOISINS_H_INCLUDED

// Include
#include <iostream>
#include <string>
#include <vector>
#include "sommet.h"

using namespace std;

class ListeVoisins{

    private :

    vector <int>* m_graph;
    int m_tailleGraph;

    public:

    ListeVoisins();
    ListeVoisins(int taille);
    ~ListeVoisins();

    void addSummit(int i, int x);//Ajoute l'element x dans la liste graph[i]
    void lscAdjCFC (char* a, int n); // Renvoie les composantes fortement connexes du graphe
    void printListeAdj (); // Affiche la liste adjacente
    void PPG (Sommet* s); // Parcours en profondeur du graphe (appel sur PProfG)
    void PProfG (Sommet* s, int i, int* t); // Parcours en profondeur du graphe (recursif)
    void PPGD (Sommet* s); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    void PProfGD (Sommet* s, int i, int* t); // Parcours en profondeur du graphe dual (recursif)

    int getTaille();
    void setTaille(int t);


};

#endif
