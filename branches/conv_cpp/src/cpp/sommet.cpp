/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : sommet.cpp
OBJET            : liste simplement cha�n�e d'adjacence
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

void Sommet::triDecroissant () { // Renvoie l'ordre de parcours de la matrice duale (tri� par ordre d�croissant des temps d'acc�s finaux)
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

int Sommet::getIndiceMinDeb () { // Renvoie l'indice du plus petit d(x)
    int i, imin, min = INT_MAX;
    for (i = 0; i < m_tailleGraph; i++) {
        if ((m_tabSommet[i].deb < min) && (m_tabSommet[i].etat == -1)) {
            min = m_tabSommet[i].deb;
            imin = i;
        }
    }
    if (imin != INT_MAX)
        return imin;
    else
        return 0;
}

s_sommet Sommet::getStructSommet (int x){
    if ((x >= 0) && (x < m_tailleGraph)){
        return m_tabSommet[x];
    }
    else
        cerr << "Erreur : x n'appartient pas a l'intervalle defini par m_tailleGraph" << endl;
        exit (0);
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
    std::ostringstream oss;
    int d = m_tabSommet[0].deb, f = m_tabSommet[0].fin, i;
    string buffer = "";
    string cfc = "";
    oss << m_tabSommet[0].id;
    buffer = oss.str();
    cfc = buffer;
    for (i = 0; i < m_tailleGraph - 1; i++) {
        if ((d < (m_tabSommet[i+1].deb)) && (f > (m_tabSommet[i+1].fin))) {
            oss.str("");
            oss << m_tabSommet[i+1].id;
            buffer = oss.str();
            cfc += ", ";
            cfc += buffer;
        } else {
            d = m_tabSommet[i+1].deb;
            f = m_tabSommet[i+1].fin;
            if (i+1 < m_tailleGraph) {
                oss.str("");
                oss <<m_tabSommet[i+1].id;
                buffer = oss.str();
                cfc += "\n";
                cfc += buffer;
            }
        }
    }
    return cfc;
}

bool Sommet::nonExplore () { // Renvoie vrai s'il reste un sommet non explor�
    int i;
    for (i = 0; i < m_tailleGraph; i++) {
        if ((m_tabSommet[i].etat == -1) && (m_tabSommet[i].deb != INT_MAX))
            return true;
    }
    return false;
}

char* Sommet::getCheminMin (int y) {
    int i, j, k, p, l, m;
    char temp;
    char* buffer = (char*) malloc(5*m_tailleGraph*sizeof(char));
    char* chemin = (char*) malloc(5*m_tailleGraph*sizeof(char));
    sprintf(chemin, "%d : ", m_tabSommet[y].deb);
    strcpy(buffer, chemin);
    m = strlen(buffer);
    while (y != -1) {
        sprintf(chemin, "%d, ", m_tabSommet[y].id);
        strcat(buffer, chemin);
        y = m_tabSommet[y].fin;
    }
    p = strlen(buffer);
    strcpy(chemin, buffer);
    i = m;
    while (i < p) { // inversion de l'ordre (fonction super bordelique!)
        l = 0;
        while (buffer[i] != ' ') {
            i++;
            l++;
        }
        i = i-l;
        l++;
        k = 0;
        j = p-l-i;
        while (k < l) {
            //printf("Var : (l=%d p=%d i=%d), chemin[%d] = %c\n", l, p, i, j+m, buffer[i]);
            chemin[j+m] = buffer[i];
            i++;
            k++;
            j++;
        }
    }
    chemin[p-2] = '\0'; // on el�ve la derni�re virgule et le dernier espace
    strcat(chemin, "\n");
    free(buffer);
    return chemin;
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


