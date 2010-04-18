/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

typedef struct struct_sommet s_sommet;
struct struct_sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int deb;
    int fin;
    int num;
    char nom[32];
    int id;
    int freq;
};

class Sommet{

    private :

    int m_tailleGraph;
    s_sommet* m_tabSommet;

    public :

    //Methodes
    Sommet();
    Sommet(int taille);
    ~Sommet();

    void print (); // Affiche les informations des sommets
    void printCFC (); // Affiche les CFC
    void iniEtatSommet (); // Initialise les etats des sommets
    void triDecroissant (); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
    int getIndice (int x); // Renvoie l'indice du tableau correspondant a l'id x
    int getNbCFC (); // Renvoie le nombre de composantes fortement connexes
    string getCFC (); // Renvoie les CFC

    //Accesseurs
    int getTaille ();
    void setTaille (int t);
    s_sommet getTabSommet ();
    void setTabSommet (s_sommet* t);
};


#endif // SOMMET_H_INCLUDED
