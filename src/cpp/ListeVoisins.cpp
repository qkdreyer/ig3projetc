/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : liste_voisins.cpp
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../h/ListeVoisins.h"

ListeVoisins::ListeVoisins() : m_graph(0), m_tailleGraph(0){

}

ListeVoisins::ListeVoisins(int taille) : m_tailleGraph(taille){
    //int i = 0;
    m_graph = new vector <int>[m_tailleGraph];
}


ListeVoisins::~ListeVoisins(){
    //TODO
    delete[] m_graph;
}


void ListeVoisins::addSummit(int i, int x){
    m_graph[i].push_back(x);
}


void ListeVoisins::printListeAdj () {
    int i;
    vector <int>::iterator it;
    for (i = 0; i < m_tailleGraph; i++) {
        printf("%d ", i+1);
        for(it = m_graph[i].begin(); it < m_graph[i].end(); it++){
            cout << "-> " << ( (*it) + 1 );
        }
        cout << endl;
    }
    printf("\n");
}


void ListeVoisins::PPG (Sommet* s) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    s->iniEtatSommet();
    for (i = 0; i < m_tailleGraph; i++) {
        if (s->getEtat(s->getNum(i)) == -1) { // ancienne version : s->getStructSommet(s->getStructSommet(i).num).etat
            PProfG(s, s->getNum(i), t);
        }
    }
    s->triDecroissant();
}


void ListeVoisins::PProfG (Sommet* s, int i, int* t) { // Parcours en profondeur du graphe (recursif)
    vector <int>::iterator it;
    s->getStructSommet(i).etat = 0; // Etat atteint
    (*t)++;
    s->getStructSommet(i).deb = *t;
    for ( it = m_graph[i].begin(); it < m_graph[i].end(); it++){
        if (s->getStructSommet(*it).etat == -1) {
            PProfG(s, *it, t);
        }
    }
    s->getStructSommet(i).etat = 1; // Etat explore
    (*t)++;
    s->getStructSommet(i).fin = *t;
}


void ListeVoisins::PPGD (Sommet* s) { // Parcours en profondeur du graphe dual (appel sur PProfGD)
    int i;
    int temps = 0;
    int* t = &temps;
    s->iniEtatSommet();
    for (i = 0; i < m_tailleGraph; i++) {
        if (s->getStructSommet(s->getStructSommet(i).num).etat == -1) {
            PProfGD(s, s->getStructSommet(i).num, t);
        }
    }
}
void ListeVoisins::PProfGD (Sommet* s, int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    vector <int>::iterator it;
    s->getStructSommet(i).etat = 0; // Etat atteint
    (*t)++;
    s->getStructSommet(i).deb = *t;
    for ( it = m_graph[i].begin(); it < m_graph[i].end(); it++){
        if (s->getStructSommet(*it).etat == -1) {
            PProfG(s, *it, t);
        }
    }
    s->getStructSommet(i).etat = 1; // Etat explore
    (*t)++;
    s->getStructSommet(i).fin = *t;
}


int ListeVoisins::getTaille(){
    return m_tailleGraph;
}


void ListeVoisins::setTaille(int t){
    m_tailleGraph = t;
    delete[] m_graph;
    m_graph = new vector <int> [t];
}
