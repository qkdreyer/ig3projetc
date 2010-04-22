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

ListeVoisins::ListeVoisins () : m_tailleGraph(0){
    m_summit = new Sommet();
}

ListeVoisins::ListeVoisins (UserData u){
    map < int, Person >::iterator it_UserData;
    m_summit = new Sommet();
    //On recopie dans le map (m_graph) la liste de voisins que l'on obtient a partir du userData
    for (it_UserData=u.get_listPerson().begin(); it_UserData != u.get_listPerson().end(); it_UserData++){
        m_graph[it_UserData->first] = it_UserData->second.get_listLink() ;
        m_tailleGraph++;
    }
    m_summit->setTaille(m_tailleGraph);
}

//ListeVoisins::ListeVoisins(int taille) : m_tailleGraph(taille){
    //int i = 0;
    //m_graph = new vector <int>[m_tailleGraph];
//}


ListeVoisins::~ListeVoisins(){
    delete m_summit;
}

ListeVoisins ListeVoisins::toDual(){

 return *(this);
}

void ListeVoisins::iniData(UserData u){
    map < int, Person >::iterator it_UserData;
    //On recopie dans le map (m_graph) la liste de voisins que l'on obtient a partir du userData
    for (it_UserData=u.get_listPerson().begin(); it_UserData != u.get_listPerson().end(); it_UserData++){
        m_graph[it_UserData->first] = it_UserData->second.get_listLink() ;
        m_tailleGraph++;
    }
    m_summit->setTaille(m_tailleGraph);
}


void ListeVoisins::addSummit(int i, int x){
    m_graph[i].push_back(x); // On rajoute le sommet x dans les voisins de i
    m_graphDual[x].push_back(i); // On fait l'inverse pour obtenir le graphe dual
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


void ListeVoisins::printListeAdjD () {
    int i;
    vector <int>::iterator it;
    for (i = 0; i < m_tailleGraph; i++) {
        printf("%d ", i+1);
        for(it = m_graphDual[i].begin(); it < m_graphDual[i].end(); it++){
            cout << "-> " << ( (*it) + 1 );
        }
        cout << endl;
    }
    printf("\n");
}

void ListeVoisins::printSummits () {
    m_summit->print();
}

void ListeVoisins::PPG () { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    m_summit->iniEtatSommet();
    for (i = 0; i < m_tailleGraph; i++) {
        if (m_summit->getEtat(m_summit->getNum(i)) == -1) { // ancienne version : s->getStructSommet(s->getStructSommet(i).num).etat
            PProfG(m_summit->getNum(i), t);
        }
    }
    m_summit->triDecroissant();
}


void ListeVoisins::PProfG (int i, int* t) { // Parcours en profondeur du graphe (recursif)
    vector <int>::iterator it;
    m_summit->setEtat(i, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(i, *t);
    for ( it = m_graph[i].begin(); it < m_graph[i].end(); it++){
        if (m_summit->getEtat(*it) == -1) {
            PProfG(*it, t);
        }
    }
    m_summit->setEtat(i,1); // Etat explore
    (*t)++;
    m_summit->setFin(i,*t);
}


void ListeVoisins::PPGD () { // Parcours en profondeur du graphe dual (appel sur PProfGD)
    int i;
    int temps = 0;
    int* t = &temps;
    m_summit->iniEtatSommet();
    for (i = 0; i < m_tailleGraph; i++) {
        if (m_summit->getEtat(m_summit->getNum(i)) == -1) {
            PProfGD(m_summit->getNum(i), t);
        }
    }
}
void ListeVoisins::PProfGD (int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    vector <int>::iterator it;
    m_summit->setEtat(i, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(i ,*t);
    for ( it = m_graphDual[i].begin(); it < m_graphDual[i].end(); it++){
        if (m_summit->getEtat(*it) == -1) {
            PProfGD(*it, t);
        }
    }
    m_summit->setEtat(i, 1); // Etat explore
    (*t)++;
    m_summit->setFin(i, *t);
}


int ListeVoisins::getTaille(){
    return m_tailleGraph;
}


void ListeVoisins::setTaille(int t){
    m_tailleGraph = t;
    setSummitSize(t);
    //delete[] m_graph;
  //  m_graph = new vector <int> [t];
}

void ListeVoisins::setSummitEtat (int i, int e) {
    m_summit->setEtat(i, e);
}

void ListeVoisins::setSummitNom (int i, string s) {
    m_summit->setNom(i, s);
}

void ListeVoisins::setSummitNum (int i, int n) {
    m_summit->setNum(i, n);
}

void ListeVoisins::setSummitId (int i, int id) {
    m_summit->setId(i, id);
}

void ListeVoisins::setSummitFreq (int i, int f) {
    m_summit->setFreq(i, f);
}

void ListeVoisins::setSummitSize (int t) {
    m_summit->setTaille(t);
}

int ListeVoisins::getSummitSize () {
    return m_summit->getTaille();
}

int ListeVoisins::getIndice (int x) {
    return m_summit->getIndice(x);
}

int ListeVoisins::getNbCFC(){
    return m_summit->getNbCFC();
}

string ListeVoisins::getCFC(){
    return m_summit->getCFC();
}
