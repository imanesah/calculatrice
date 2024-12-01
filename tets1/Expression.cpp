#include "Expression.h"
#include <stack>
#include <sstream>

template <typename T>
bool Expression<T>::checkEquation(const string& expr) {
    PPile<char> s;  // Utilise une pile pour valider les parenth�ses et les op�rateurs
    bool dernierCaractereOperateur = false;

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (isspace(ch)) {  // Ignore les espaces
            continue;
        }

        // V�rification de l'�quilibre des parenth�ses
        if (ch == '(' || ch == '[') {
            s.empile(ch);
            dernierCaractereOperateur = false;
        }
        else if (ch == ')' || ch == ']') {
            if (s.estVide()) {
                return false;
            }
            char top = s.sommet();
            if ((ch == ')' && top == '(') || (ch == ']' && top == '[')) {
                s.depile();
            }
            else {
                return false;
            }
            dernierCaractereOperateur = false;
        }
        // V�rification des op�rateurs math�matiques
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (dernierCaractereOperateur || (i == 0) || (expr[i - 1] == '(') || (expr[i - 1] == '[')) {
                return false;
            }
            dernierCaractereOperateur = true;
        }
        // Validation des chiffres
        else if (isdigit(ch)) {
            dernierCaractereOperateur = false;
        }
        // Si un caract�re inconnu est trouv�
        else {
            return false;
        }
    }

    // L'expression est valide si la pile est vide et que le dernier caract�re n'�tait pas un op�rateur
    return s.estVide() && !dernierCaractereOperateur;
}

template <typename T>
double Expression<T>::solveEquation(const string& expr) {
    std::stack<double> valeurs; // Pile pour les valeurs num�riques
    std::stack<char> operateurs; // Pile pour les op�rateurs

    for (size_t i = 0; i < expr.size(); ++i) {
        char ch = expr[i];

        if (isspace(ch)) {  // Ignore les espaces
            continue;
        }

        // Si c'est un chiffre ou un nombre
        else if (isdigit(ch) || ch == '.') {
            double valeur = 0;
            string nombre;

            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                nombre += expr[i];
                i++;
            }
            i--;  // Revenir un caract�re en arri�re apr�s la boucle

            stringstream ss(nombre);
            ss >> valeur;
            valeurs.push(valeur);
        }

        // Si c'est une parenth�se ouvrante
        else if (ch == '(') {
            operateurs.push(ch);
        }

        // Si c'est une parenth�se fermante
        else if (ch == ')') {
            while (!operateurs.empty() && operateurs.top() != '(') {
                double b = valeurs.top(); valeurs.pop();
                double a = valeurs.top(); valeurs.pop();
                char op = operateurs.top(); operateurs.pop();
                valeurs.push(appliquerOperation(a, b, op));
            }
            operateurs.pop(); // Supprime la parenth�se ouvrante
        }

        // Si c'est un op�rateur
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operateurs.empty() && precedence(operateurs.top()) >= precedence(ch)) {
                double b = valeurs.top(); valeurs.pop();
                double a = valeurs.top(); valeurs.pop();
                char op = operateurs.top(); operateurs.pop();
                valeurs.push(appliquerOperation(a, b, op));
            }
            operateurs.push(ch);
        }

        // Caract�re non valide
        else {
            throw runtime_error("Caract�re invalide dans l'expression");
        }
    }

    // �valuation des op�rations restantes
    while (!operateurs.empty()) {
        double b = valeurs.top(); valeurs.pop();
        double a = valeurs.top(); valeurs.pop();
        char op = operateurs.top(); operateurs.pop();
        valeurs.push(appliquerOperation(a, b, op));
    }

    if (valeurs.size() != 1) {
        throw runtime_error("Expression invalide");
    }

    return valeurs.top();
}

template <typename T>
double Expression<T>::appliquerOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': if (b == 0) throw runtime_error("Division par z�ro."); return a / b;
    default: throw runtime_error("Op�rateur inconnu.");
    }
}

template <typename T>
int Expression<T>::precedence(char op) const {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Explicit instantiation
template class Expression<int>;
template class Expression<double>;
