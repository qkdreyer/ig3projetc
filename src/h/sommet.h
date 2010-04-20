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

#include <iostream>
#include <string>
using namespace std;

//J'ai gard� la structure qui permet de definir l'ensemble des variables, alors que la classe
//definit le tableau de sommet ainsi que l'ensemble de m�thodes associ�es.
typedef struct struct_sommet s_sommet;
struct struct_sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Explor�
    int deb;
    int fin;
    int num;
    string nom;
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
    void triDecroissant (); // Renvoie l'ordre de parcours de la matrice duale (tri� par ordre d�croissant des temps d'acc�s finaux)
    int getIndice (int x); // Renvoie l'indice du tableau correspondant a l'id x
    s_sommet getStructSommet (int x); // Renvoie la struct_sommet(s_sommet) qui est a l'indice x du tableau m_tabSommet
    int getNbCFC (); // Renvoie le nombre de composantes fortement connexes
    string getCFC (); // Renvoie les CFC

    //Accesseurs
    int getTaille ();
    void setTaille (int t);
    s_sommet getTabSommet ();
    void setTabSommet (s_sommet* t);

    void setEtat(int i, int e);
    int getEtat(int i);
    void setDeb(int i, int d);
    int getDeb(int i);
    void setFin(int i, int f);
    int getFin(int i);
    void setNum(int i, int n);
    int getNum(int i);
    void setNom(int i, string n);
    string getNom(int i);
    void setId(int i, int id);
    int getId(int i);
    void setFreq(int i, int f);
    int getFreq(int i);

};


#endif // SOMMET_H_INCLUDED
