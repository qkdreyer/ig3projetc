/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : sommet.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../h/sommet.h"

Sommet::Sommet () : m_tailleGraph(0), m_tabSommet(NULL){

}

Sommet::Sommet (int taille) : m_tailleGraph(taille) {
    m_tabSommet = new s_sommet[m_tailleGraph];
    int i;
    for (i = 0; i < m_tailleGraph; i++) {
        m_tabSommet[i].etat = -1; // Etat non atteint
        m_tabSommet[i].deb = 0;
        m_tabSommet[i].fin = 0;
    }
}

Sommet::~Sommet (){
    delete[] m_tabSommet;
}

void Sommet::print () {
    int i;
    for (i = 0; i < m_tailleGraph; i++) {
        cout << "sommet " << m_tabSommet[i].id << " :\n  nom = " << m_tabSommet[i].nom
        << ", freq = " << m_tabSommet[i].freq << ", d(" << m_tabSommet[i].deb << "), f(" << m_tabSommet[i].fin << ")" << endl;
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

s_sommet Sommet::getStructSommet (int x){
    if ((x >= 0) && (x < m_tailleGraph)){
        return m_tabSommet[x];
    }
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
    delete[] m_tabSommet;
    m_tabSommet = new s_sommet[m_tailleGraph];
}

void Sommet::setEtat(int i, int e){
    m_tabSommet[i].etat = e;
}

int Sommet::getEtat(int i){
    return m_tabSommet[i].etat;
}

void Sommet::setNom(int i, string n){
    cout << "Nouveau nom : " << n;
    m_tabSommet[i].nom = n;
}

string Sommet::getNom(int i){
    return m_tabSommet[i].nom;
}

void Sommet::setDeb(int i, int d){
    m_tabSommet[i].deb = d;
}


int Sommet::getDeb(int i){
    return m_tabSommet[i].deb;
}


void Sommet::setFin(int i, int f){
    m_tabSommet[i].fin = f;
}


int Sommet::getFin(int i){
    return m_tabSommet[i].fin;
}


void Sommet::setNum(int i, int n){
    m_tabSommet[i].num = n;
}


int Sommet::getNum(int i){
    return m_tabSommet[i].num;
}


void Sommet::setId(int i, int id){
    cout << "iter : " << i << endl;
    m_tabSommet[i].id = id;
}


int Sommet::getId(int i){
    return m_tabSommet[i].id;
}


void Sommet::setFreq(int i, int f){
    m_tabSommet[i].freq = f;
}

int Sommet::getFreq(int i){
    return m_tabSommet[i].freq;
}



