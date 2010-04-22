/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.cpp
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */


#include "../h/sommet.h"
#include "../h/matAdj.h"

MatAdj::MatAdj () : m_size(0), m_Matrix(NULL){
    m_summit = new Sommet();
}


MatAdj::MatAdj (int s) : m_size(s) {
    int i = 0;
    m_Matrix = new int*[m_size];
    for (i = 0; i < m_size; i++){
        m_Matrix[i] = new int[m_size];
    }
}

MatAdj::MatAdj (UserData u) {
    map < int, Person >::iterator it_UserData;
    m_summit = new Sommet();
    //On recopie dans la matrice la liste de voisins que l'on obtient a partir du userData
    for (it_UserData=u.get_listPerson().begin(); it_UserData != u.get_listPerson().end(); it_UserData++){
        // TODO : Remplissage de la matrice
    }
    m_summit->setTaille(m_size);
}


MatAdj::~MatAdj () {
    int i = 0;
    for (i = 0; i < m_size; i++){
        delete m_Matrix[i];
    }
    delete[] m_Matrix;
}


void MatAdj::iniMat () { // Renvoie la matrice d'adjacence
    int i, j;
    m_Matrix = new int*[m_size];
    for (i = 0; i < m_size; i++){
        m_Matrix[i] = new int[m_size];
    }
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            m_Matrix[j][i] = 0;
        }
    }
}

void MatAdj::printMat () { // Affiche la matrice adjacente
    int i, j;
    cout << endl;
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            cout << m_Matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void MatAdj::PPG () { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    m_summit->iniEtatSommet();
    for (i = 0; i < m_size; i++) {
        if ( m_summit->getEtat(m_summit->getNum(i)) == -1 ){ // version c de quentin : s[s[i].num].etat == -1)
            PProfG(m_summit->getNum(i), t);
        }
    }
    m_summit->triDecroissant();
}

void MatAdj::PProfG (int i, int* t) { // Parcours en profondeur du graphe (recursif)
    int j;
    m_summit->setEtat(i, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(i, *t);
    for (j = 0; j < m_size; j++) {
        if ((m_Matrix[i][j] > 0) && (m_summit->getEtat(j) == -1)) { // Successeur non atteint
            PProfG(j, t);
        }
    }
    m_summit->setEtat(i, 1); // Etat explore
    (*t)++;
    m_summit->setFin(i, *t);
}

void MatAdj::PPGD () { // Parcours en profondeur du graphe dual (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    m_summit->iniEtatSommet();
    for (i = 0; i < m_size; i++) {
        if (m_summit->getEtat(m_summit->getNum(i)) == -1) {
            PProfGD(m_summit->getNum(i), t);
        }
    }
}

void MatAdj::PProfGD (int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    m_summit->setEtat(i, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(i, *t);
    for (j = 0; j < m_size; j++) {
        if ((m_Matrix[j][i] > 0) && (m_summit->getEtat(j) == -1)) { // Successeur non atteint
            PProfGD(j, t);
        }
    }
    m_summit->setEtat(i, 1); // Etat explore
    (*t)++;
    m_summit->setFin(i,*t);
}

int MatAdj::getTMin (int x, int y) { // Renvoie le temps min pour aller de x à y
    int t;
    int* tmin = &t;
    x = m_summit->getIndice(x);
    y = m_summit->getIndice(y);
    t = - m_summit->getFreq(x);
    m_summit->iniEtatSommet();
    getTMinProf(x, y, tmin, t);
    return *tmin;
}

void MatAdj::getTMinProf (int x, int y, int* t, int temp) { // Parcours en profondeur
    int j;
    m_summit->setEtat(x,0); // Etat atteint
    cout << "s = " << (x + 1) << " (" << m_summit->getId(x) << "), t = " << temp << endl;
    temp += m_summit->getFreq(x);
    if (x == y) {
        *t = temp;
    } else {
        for (j = 0; j < m_size; j++) {
            if ((m_Matrix[x][j] > 0) && (m_summit->getEtat(j) == -1)) { // Successeur non atteint
                getTMinProf(j, y, t, temp);
            }
        }
    }
    m_summit->setEtat(x, 1); // Etat explore
}
