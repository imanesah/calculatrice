#include "Pile.h"
// Destructeur
template <typename T>
PPile<T>::~PPile() {
    while (sommetNoeud != nullptr) {
        depile();
    }
}

template <typename T>
bool PPile<T>::estVide() const {
    return sommetNoeud == nullptr;
}

template <typename T>
void PPile<T>::empile(T val) {
    Noeud<T>* nouveau = new Noeud<T>(val);
    nouveau->suivant = sommetNoeud;// Le nouveau nœud pointe vers l'ancien sommet
    sommetNoeud = nouveau;
}

template <typename T>
void PPile<T>::depile() {
    if (estVide()) {
      cout << "La pile est vide, impossible de dépiler." ;
    }
    Noeud<T>* temp = sommetNoeud;
    sommetNoeud = sommetNoeud->suivant; // Le nouveau nœud pointe vers l'ancien sommet
    delete temp; 
}

template <typename T>
T PPile<T>::sommet() const {
    if (estVide()) {
        cout << "La pile est vide, aucun sommet disponible.";
    }
    return sommetNoeud->val;
}

template <typename T>
void PPile<T>::affiche() const {
    Noeud<T>* courant = sommetNoeud;
    while (courant != nullptr) {
        cout << courant->val << " ";
        courant = courant->suivant;
    }
    cout << endl;
}

template <typename T>
void PPile<T>::invertStack() {
    Noeud<T>* prev = nullptr;
    Noeud<T>* current = sommetNoeud;
    Noeud<T>* next = nullptr;

    while (current != nullptr) {
        next = current->suivant;
        current->suivant = prev;
        prev = current;
        current = next;
    }

    sommetNoeud = prev;
}

template <typename T>
bool PPile<T>::isPalindrome() {
    vector<T> elements;
    Noeud<T>* courant = sommetNoeud;

    while (courant != nullptr) {
        elements.push_back(courant->val); // Empile les valeurs dans un vecteur
        courant = courant->suivant;
    }

    vector<T> reversed = elements; // Copie de l'ordre des éléments
    reverse(reversed.begin(), reversed.end()); // Inverse l'ordre du vecteur

    return elements == reversed;
}



template class PPile<char>;
template class PPile<int>;
template class PPile<float>;
template class PPile<double>;