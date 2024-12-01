#ifndef PILE_H
#define PILE_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Noeud {
public:
    T val;
    Noeud<T>* suivant; // Pointeur brut

    Noeud(T value) : val(value), suivant(nullptr) {}
};

template <typename T>
class PPile {
private:
    Noeud<T>* sommetNoeud; // Pointeur brut pour le sommet
public:
    PPile() : sommetNoeud(nullptr) {}
    ~PPile(); // Destructeur pour libérer la mémoire

    bool estVide() const;
    void empile(T val);
    void depile();
    T sommet() const;
    void affiche() const;
    void invertStack();
    bool isPalindrome();
    
};
#endif // PILE_H