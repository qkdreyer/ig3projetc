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

MatAdj::MatAdj() : m_size(0), m_Matrix(NULL){

}


MatAdj::MatAdj(int s) : m_size(s) {
    int i = 0;
    m_Matrix = new int*[m_size];
    for (i = 0; i < m_size; i++){
        m_Matrix[i] = new int[m_size];
    }
}


MatAdj::~MatAdj() {
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

void MatAdj::PPG (Sommet* s) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    s->iniEtatSommet();
    for (i = 0; i < m_size; i++) {
        if ( s->getEtat(s->getNum(i)) == -1 ){ // version c de quentin : s[s[i].num].etat == -1)
            PProfG(s, s->getNum(i), t);
        }
    }
    s->triDecroissant();
}

void MatAdj::PProfG (Sommet* s, int i, int* t) { // Parcours en profondeur du graphe (recursif)
    int j;
    s->setEtat(i, 0); // Etat atteint
    (*t)++;
    s->setDeb(i, *t);
    for (j = 0; j < m_size; j++) {
        if ((m_Matrix[i][j] > 0) && (s->getEtat(j) == -1)) { // Successeur non atteint
            PProfG(s, j, t);
        }
    }
    s->setEtat(i, 1); // Etat explore
    (*t)++;
    s->setFin(i, *t);
}

void MatAdj::PPGD (Sommet* s) { // Parcours en profondeur du graphe dual (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    s->iniEtatSommet();
    for (i = 0; i < m_size; i++) {
        if (s->getEtat(s->getNum(i)) == -1) {
            PProfGD(s, s->getNum(i), t);
        }
    }
}

void MatAdj::PProfGD (Sommet* s, int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    s->setEtat(i, 0); // Etat atteint
    (*t)++;
    s->setDeb(i, *t);
    for (j = 0; j < m_size; j++) {
        if ((m_Matrix[j][i] > 0) && (s->getEtat(j) == -1)) { // Successeur non atteint
            PProfGD( s, j, t);
        }
    }
    s->setEtat(i, 1); // Etat explore
    (*t)++;
    s->setFin(i,*t);
}

int MatAdj::getTMin (Sommet* s, int x, int y) { // Renvoie le temps min pour aller de x à y
    int t;
    int* tmin = &t;
    x = s->getIndice(x);
    y = s->getIndice(y);
    t = - s->getFreq(x);
    s->iniEtatSommet();
    getTMinProf(s, x, y, tmin, t);
    return *tmin;
}

void MatAdj::getTMinProf (Sommet* s, int x, int y, int* t, int temp) { // Parcours en profondeur
    int j;
    s->setEtat(x,0); // Etat atteint
    cout << "s = " << (x + 1) << " (" << s->getId(x) << "), t = " << temp << endl;
    temp += s->getFreq(x);
    if (x == y) {
        *t = temp;
    } else {
        for (j = 0; j < m_size; j++) {
            if ((m_Matrix[x][j] > 0) && (s->getEtat(j) == -1)) { // Successeur non atteint
                getTMinProf(s, j, y, t, temp);
            }
        }
    }
    s->setEtat(x, 1); // Etat explore
}
