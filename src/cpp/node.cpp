/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : node.cpp
OBJET            : noeud de la liste
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "assert.h"

#include "../h/node.h"

//Par défault la valeur d'initialisation d'une cellule de la liste est 0
Node::Node() : m_next(NULL), m_val(0) {

}

Node::~Node(){

}

/*ACCESSEURS*/
Node* Node::getNext(){
    return m_next;
}

void Node::setNext(Node* n){
    m_next = n;
}

int Node::getVal(){
    return m_val;
}

void Node::setVal(int v){
    m_val = v;
}

void Node::print(){
    cout << m_val;
}
