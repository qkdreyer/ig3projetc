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
    char *buffer, typestruct;
    string string_CFC, string_nom, nom_in, nom_out, dir_in, dir_out;
    dir_in = "test/";dir_out = "test/";
    ListeVoisins L, P;
    MatAdj M;
    FILE* fic_in, *fic_out;

    typestruct = 'l'; // Choix de la structure, m pour matrice, l pour liste

    if (argc > 2) { // s'il y a 2 arguments, on les utilise comme noms de fichiers d'entrée et de sortie
        nom_in = argv[1];
        nom_out = argv[2];
    } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
        nom_in = argv[1];
        nom_out = nom_in;
        nom_out += ".res";
    } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entrée et de sortie
        cout << "Entrez le nom du graphe." << endl;
        cin >> nom_in;
        cout << "Entrez le nom du fichier resultat." << endl;
        cin >> nom_out;
        cout << endl;
    }

    dir_in += nom_in; // concaténation du repertoire test avec le nom du fichier d'entrée
    dir_out += nom_out; // concaténation du repertoire test avec le nom du fichier de sortie

    fic_in = fopen(dir_in.c_str(), "r");
    if (fic_in != NULL) { // lecture du graphe

        fscanf(fic_in, "%d\n", &n); // lecture du nombre de sommets du graphe
        i = 0;
        if (typestruct = 'l') {
            L.setTaille(n);
        } else if (typestruct = 'm'){
            M.setSize(n);
        }
        //d = iniSommet(n);
        buffer = (char*) malloc(1000*sizeof(char));
        while (i < n) { // lecture des id / nom / frequence
            fscanf(fic_in, "%[^,], %d, %d\n", buffer, &x, &y);
            if (typestruct = 'l') {
                L.setSummitNom(i, buffer);
                L.setSummitId(i, x);
                L.setSummitFreq(i, y);
                L.setSummitNum(i, i);
            } else if (typestruct = 'm') {
                M.setSummitNom(i, buffer);
                M.setSummitId(i, x);
                M.setSummitFreq(i, y);
                M.setSummitNum(i, i);
            }
            //d[i].id = x;
            //d[i].freq = y;
            i++;
        }

        fscanf(fic_in, "%d\n", &m); // lecture du nombre de sommets du graphe
        i = 0;
        while (i < m) { // lecture les relations entre les sommets
            fscanf(fic_in, "%d, %d\n", &x, &y);
            if (typestruct == 'm') {
                x = M.getIndice(x);
                y = M.getIndice(y);
                M.addSummit(x, y); // remplissage de la matrice d'adjacence M
            } else if (typestruct == 'l') {
                x = L.getIndice(x);
                y = L.getIndice(y);
                L.addSummit(x, y);
            }
            i++;
        }

        if (typestruct == 'm') { // Matrice

            M.PPG();
            M.PPGD();

        } else if (typestruct == 'l') { // Liste

            L.PPG();
            L.PPGD();

        }

        fic_out = fopen(dir_out.c_str(), "w+"); // traiement du fichier resultat
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
                    //TODO
                    //algoDijkstra(M, d, n, x);
                } else if (typestruct == 'l') {
                    //TODO
                    L.algoDijkstra(x);
                }
            }
            //TODO
            y = L.getIndice(y);
            buffer = L.getCheminMin(y);
            fprintf(fic_out, "%s", buffer);
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
