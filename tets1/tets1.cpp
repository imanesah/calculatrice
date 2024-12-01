#include "Pile.h"
#include "Expression.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    try {
        // Tester la classe PPile
        PPile<int> pile;
        cout << "Empilement des éléments 10, 20, 30..." << endl;
        pile.empile(10);
        pile.empile(20);
        pile.empile(30);

        cout << "État de la pile : ";
        pile.affiche();

        cout << "Sommet actuel : " << pile.sommet() << endl;
        cout << "Dépiler un élément..." << endl;
        pile.depile();

        cout << "État de la pile après dépilage : ";
        pile.affiche();

        cout << "Vérification si la pile est palindrome : ";
        cout << (pile.isPalindrome() ? "Oui" : "Non") << endl;

        // Tester la classe Expression
        Expression<double> expression;
        string expr;

        cout << "\nEntrez une expression mathématique (par exemple : 3 + 5 * (2 - 8)): ";
        getline(cin, expr);

        if (expression.checkEquation(expr)) {
            double result = expression.solveEquation(expr);
            cout << "Résultat de l'expression '" << expr << "' : " << result << endl;
        }
        else {
            cout << "L'expression '" << expr << "' est invalide." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
    }

    return 0;
}
