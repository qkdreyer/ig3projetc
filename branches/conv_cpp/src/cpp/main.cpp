/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <iostream>
#include <string>
#include <fstream>
//#include "../h/matAdj.h"
//#include "../h/lscAdj.h"
#include "../h/ListeVoisins.h"
#include "../h/generate_mat.h"

int main(int argc, char* argv[]) {

    int i, size_g, m, temp, x = 0, y = 0, **M;
    string nom_in, nom_out, dir_in = "test/", dir_out = "test/",buffer, buffer_lig;
    char typestruct;
    char c1,c2,c3;
    ListeVoisins L, P;
    Sommet S;
    Sommet S2(5);
    ifstream file_in;
    ofstream file_out;

    typestruct = 'm'; // Choix de la structure, m pour matrice, l pour liste

    if (argc > 2) { // s'il y a 2 arguments, on les utilise comme noms de fichiers d'entrée et de sortie
        nom_in = argv[1];
        nom_out = argv[2];
    } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
        nom_in = argv[1];
        nom_out += nom_in;
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

    file_in.open("test/in", ios::in);  // on ouvre le fichier en lecture

    if(file_in)  // si l'ouverture a réussi
    {
        getline(file_in, buffer_lig); // lecture du nombre de sommets du graphe

        i = 0;
        size_g = atoi(buffer_lig.c_str());
        cout << "La taille du graphe est : " << size_g << endl;
        S.setTaille(size_g);

        L.setTaille(size_g);
        P.setTaille(size_g);

        while (i < size_g) { // lecture des id / nom / frequence
            cout << "i : " << i;
            cout << "buffer_lig : " << buffer_lig << endl;
            //fscanf(fichier, "%[^,], %d, %d\n", buffer, &x, &y);
            S.setNom(i, buffer_lig);
            cout << "S.getEtat(i)" << S.getEtat(i) << endl;// = buffer_lig;

            //s[i].num = i;
            //s[i].id = x;
            //s[i].freq = y;
            i++;
        }

        file_in.close();
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    return 0;

}
