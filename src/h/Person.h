/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Person.cpp
OBJET            : Classe pour les donnees d'une personne
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
  - Creation du fichier : (19/04/2010)
    Lit un fichier et stocke toutes les donnees qu'il contient en donnees reutilisables par une fonction externe
    On stocke
        - Le nom (name)
        - Son id (id_number)
        - Sa frequence de visite (frequency)
        - La liste des personnes a qui il fait confiance (listLink)

  - Modification : (20/04/2010)
    Ajout du stockage des relations duales (inversement des relations)
    => Attribut supplementaire
        - La liste des personnes qui lui font confiance (listDualLink)

  - Modification : (29/04/2010)
    Deplacement des amis dans une autre classe

============================================================================= */

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED


/*=================================
Includes
===================================*/
#include <iostream>
#include <string>
/*=================================*/

using namespace std;


class Person {
  /* Attributs */
  /* Le nom, l'id de la personne, la frequence de ses visites */
  private:
  string name;
  int id_number;
  int frequency;


  public:
  /* Methodes */

    /* Constructeurs et Desctructeurs */
    Person();
    Person(string n, int i, int f);
    ~Person();


    /* Accesseur en ecriture */
    void set_name(string n);
    void set_id(int i);
    void set_freq(int f);


    /* Accesseur en lecture */
    string get_name();
    int get_id();
    int get_freq();

    void print();
      /* Affichage d'une personne */

};

#endif // PERSON_H_INCLUDED
