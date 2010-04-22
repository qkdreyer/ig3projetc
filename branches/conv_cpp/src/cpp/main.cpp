/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "../h/matAdj.h"
#include "../h/ListeVoisins.h"
#include "../h/generate_mat.h"

int main(int argc, char* argv[]) {

    int i, n, m, temp = 0, x = 0, y = 0;
    char *nom_in, *nom_out, dir_in[6] = "test/", dir_out[6] = "test/", *buffer, typestruct;
    string string_CFC, string_nom;
    ListeVoisins L, P;
    MatAdj M;
    //sommet* s, *d;
    FILE* fic_in, *fic_out;

    typestruct = 'l'; // Choix de la structure, m pour matrice, l pour liste
    nom_in = (char*) malloc(16*sizeof(char));
    nom_out = (char*) malloc(16*sizeof(char));

    if (argc > 2) { // s'il y a 2 arguments, on les utilise comme noms de fichiers d'entrée et de sortie
        nom_in = argv[1];
        nom_out = argv[2];
    } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
        nom_in = argv[1];
        strcpy(nom_out, nom_in);
        strcat(nom_out, ".res");
    } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entrée et de sortie
        printf("Entrez le nom du graphe.\n");
        scanf("%s", nom_in);
        printf("Entrez le nom du fichier resultat.\n");
        scanf("%s", nom_out);
        printf("\n");
    }

    strcat(dir_in, nom_in); // concaténation du repertoire test avec le nom du fichier d'entrée
    strcat(dir_out, nom_out); // concaténation du repertoire test avec le nom du fichier de sortie

    fic_in = fopen(dir_in, "r");
    if (fic_in != NULL) { // lecture du graphe

        fscanf(fic_in, "%d\n", &n); // lecture du nombre de sommets du graphe
        i = 0;
        L.setTaille(n);
        //s = iniSommet(n);
        //d = iniSommet(n);
        //M = iniMat(n);
        //L = iniListe(n);
        //P = iniListe(n);
        buffer = (char*) malloc(1000*sizeof(char));
        while (i < n) { // lecture des id / nom / frequence
            fscanf(fic_in, "%[^,], %d, %d\n", buffer, &x, &y);
            cout << "buffer : " << buffer << endl;
            cout << "m_tailleGraph : " << L.getSummitSize() << endl;
            L.setSummitNom(i, buffer);
            L.setSummitId(i, x);
            L.setSummitFreq(i, y);
            L.setSummitNum(i, i);

            //strcpy(s[i].nom, buffer);
            //s[i].num = i;
            //s[i].id = x;
            //s[i].freq = y;
            //d[i].id = x;
            //d[i].freq = y;
            i++;
        }
        L.printSummits();

        fscanf(fic_in, "%d\n", &m); // lecture du nombre de sommets du graphe
        i = 0;
        while (i < m) { // lecture les relations entre les sommets
            fscanf(fic_in, "%d, %d\n", &x, &y);
            x = L.getIndice(x);
            y = L.getIndice(y);
            if (typestruct == 'm') {
                //M[x][y] = 1; // remplissage de la matrice d'adjacence M
            } else if (typestruct == 'l') {
                L.addSummit(x, y);
                //P.addSummit(y, x);
                //ajoutFin(L, x, y); // creation de la liste d'adjacence L
                //ajoutFin(P, y, x); // creation de la liste duale d'adjacence P
            }
            i++;
        }
        cout << "CHECK : " << endl;
        L.printListeAdj();
        L.printListeAdjD();

        if (typestruct == 'm') { // Matrice

            M.PPG();
            M.PPGD();

        } else if (typestruct == 'l') { // Liste

            L.PPG();
            L.PPGD();
            //PPGD(P, s, n);

        }
        cout << "CHECK : " << endl;
        L.printSummits();
        cout << endl << endl;

        fic_out = fopen(dir_out, "w+"); // traiement du fichier resultat
        temp = L.getNbCFC(); // recuperation du nombre de cfc
        fprintf(fic_out, "%d\n", temp);
        string_CFC = L.getCFC(); // recuperation des cfc
        fprintf(fic_out, "%s\n", string_CFC.c_str());

        fscanf(fic_in, "%d\n", &m); // lecture du nombre de sommets du graphe
        i = 0;
        while (i < m) { // lecture des questions
            fscanf(fic_in, "%d -> %d\n", &x, &y);
            if (x != temp) {
                temp = x;
                if (typestruct == 'm') {
                    //algoDijkstra(M, d, n, x);
                } else if (typestruct == 'l') {
                    //algoDijkstra(L, d, n, x);
                }
            }
            //y = getIndice(s, n, y);
            //buffer = getCheminMin(d, n, y);
            //fprintf(fic_out, "%s", buffer);
            i++;
        }

        fclose(fic_in);
        fclose(fic_out);

    } else {
        printf("Lecture du fichier impossible\n");
    }
    system("PAUSE");
    return 0;

}
