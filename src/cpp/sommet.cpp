/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : sommet.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <iostream>
#include <string>
#include "../h/sommet.h"

Sommet::Sommet () : m_tailleGraph(0), m_tabSommet(NULL){

}

Sommet::Sommet (int taille) : m_tailleGraph(taille) {
    m_tabSommet = (s_sommet*) malloc( m_tailleGraph * sizeof(s_sommet));

}

Sommet::~Sommet (){

}

void Sommet::print () {
    int i;
    for (i = 0; i < m_tailleGraph; i++) {
        cout << "sommet " << m_tabSommet[i].id << " :\n  nom = " << m_tabSommet[i].nom << ", freq = " << m_tabSommet[i].freq << ", d(" << m_tabSommet[i].deb << "), f(" << m_tabSommet[i].fin << ")" << endl;
    }
}

void Sommet::printCFC () {
    int d = m_tabSommet[0].deb, f = m_tabSommet[0].fin, i;
    cout << "Les composantes fortement connexes du graphe sont :\n{" << m_tabSommet[0].id;
    for (i = 0; i < m_tailleGraph - 1; i++) {
        if ((d < (m_tabSommet[i+1].deb)) && (f > (m_tabSommet[i+1].fin))) {
            cout << ", " << m_tabSommet[i+1].id;
        } else {
            d = m_tabSommet[i+1].deb;
            f = m_tabSommet[i+1].fin;
            if (i+1 < m_tailleGraph)
                cout << "}, {%d" << m_tabSommet[i+1].id;
        }
    }
    cout << "}.\n";
}

void Sommet::iniEtatSommet () { // Initialise les etats des sommets
    int i;
    for (i = 0; i < m_tailleGraph; i++) {
        m_tabSommet[i].etat = -1; // Etat non atteint
        m_tabSommet[i].deb = 0;
        m_tabSommet[i].fin = 0;
    }
}

void Sommet::triDecroissant () { // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
    int i, tmp = 0, continuer = 1;
    while (continuer) {
        continuer--;
        for (i = 0; i < m_tailleGraph - 1; i++) {
            if (m_tabSommet[i].fin < m_tabSommet[i+1].fin) {
                tmp = m_tabSommet[i+1].fin;
                m_tabSommet[i+1].fin = m_tabSommet[i].fin;
                m_tabSommet[i].fin = tmp;

                tmp = m_tabSommet[i+1].deb;
                m_tabSommet[i+1].deb = m_tabSommet[i].deb;
                m_tabSommet[i].deb = tmp;

                tmp = m_tabSommet[i+1].num;
                m_tabSommet[i+1].num = m_tabSommet[i].num;
                m_tabSommet[i].num = tmp;
                continuer++;
            }
        }
    }
}

int Sommet::getIndice (int x) { // Renvoie l'indice du tableau correspondant a l'id x
    int i;
    for (i = 0; i < m_tailleGraph; i++) {
        if (m_tabSommet[i].id == x) {
            return i;
        }
    }
    //Peut etre -1 non pour signaler qu'il y a une erreur ?? Supposition de PJambet
    return 0;
}

int Sommet::getNbCFC () { // Renvoie le nombre de composantes fortement connexes
    int d = m_tabSommet[0].deb, f = m_tabSommet[0].fin, i, r = 1;
    for (i = 0; i < m_tailleGraph - 1; i++) {
        if (!((d < (m_tabSommet[i+1].deb)) && (f > (m_tabSommet[i+1].fin)))) {
            r++;
            d = m_tabSommet[i+1].deb;
            f = m_tabSommet[i+1].fin;
        }
    }
    return r;
}

string Sommet::getCFC () { // Renvoie les CFC
    int d = m_tabSommet[0].deb, f = m_tabSommet[0].fin, i;
    string buffer;
    string cfc;
    cfc += m_tabSommet[0].id;
    for (i = 0; i < m_tailleGraph - 1; i++) {
        if ((d < (m_tabSommet[i+1].deb)) && (f > (m_tabSommet[i+1].fin))) {
            buffer += m_tabSommet[i+1].id;
            cfc += ", ";
            cfc += buffer;
        } else {
            d = m_tabSommet[i+1].deb;
            f = m_tabSommet[i+1].fin;
            if (i+1 < m_tailleGraph) {
                buffer += m_tabSommet[i+1].id;
                cfc += "\n";
                cfc += buffer;
            }
        }
    }
    return cfc;
}

int Sommet::getTaille (){
    return m_tailleGraph;
}

void Sommet::setTaille (int t){
    m_tailleGraph = t;
}

