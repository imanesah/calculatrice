#include "Expression.h"
#include <stack>
#include <sstream>

template <typename T>
bool Expression<T>::checkEquation(const string& expr) {
    PPile<char> s;  // Utilise une pile pour valider les parenthèses et les opérateurs
    bool dernierCaractereOperateur = false;

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (isspace(ch)) {  // Ignore les espaces
            continue;
        }

        // Vérification de l'équilibre des parenthèses
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
        // Vérification des opérateurs mathématiques
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
        // Si un caractère inconnu est trouvé
        else {
            return false;
        }
    }

    // L'expression est valide si la pile est vide et que le dernier caractère n'était pas un opérateur
    return s.estVide() && !dernierCaractereOperateur;
}

template <typename T>
double Expression<T>::solveEquation(const string& expr) {
    std::stack<double> valeurs; // Pile pour les valeurs numériques
    std::stack<char> operateurs; // Pile pour les opérateurs

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
            i--;  // Revenir un caractère en arrière après la boucle

            stringstream ss(nombre);
            ss >> valeur;
            valeurs.push(valeur);
        }

        // Si c'est une parenthèse ouvrante
        else if (ch == '(') {
            operateurs.push(ch);
        }

        // Si c'est une parenthèse fermante
        else if (ch == ')') {
            while (!operateurs.empty() && operateurs.top() != '(') {
                double b = valeurs.top(); valeurs.pop();
                double a = valeurs.top(); valeurs.pop();
                char op = operateurs.top(); operateurs.pop();
                valeurs.push(appliquerOperation(a, b, op));
            }
            operateurs.pop(); // Supprime la parenthèse ouvrante
        }

        // Si c'est un opérateur
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operateurs.empty() && precedence(operateurs.top()) >= precedence(ch)) {
                double b = valeurs.top(); valeurs.pop();
                double a = valeurs.top(); valeurs.pop();
                char op = operateurs.top(); operateurs.pop();
                valeurs.push(appliquerOperation(a, b, op));
            }
            operateurs.push(ch);
        }

        // Caractère non valide
        else {
            throw runtime_error("Caractère invalide dans l'expression");
        }
    }

    // Évaluation des opérations restantes
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
    case '/': if (b == 0) throw runtime_error("Division par zéro."); return a / b;
    default: throw runtime_error("Opérateur inconnu.");
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
