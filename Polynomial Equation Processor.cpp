#include <iostream>
#include <fstream>

using namespace std;

struct Polynomial {
    int* coefficients;
    int degree;
    int equal_value;
};

bool readPolynomial(ifstream& file, Polynomial& poly) {
    if (!(file >> poly.degree >> poly.equal_value)) {
        cerr << "Error: Cannot read degree or equal value.\n";
        return false;
    }

    if (poly.degree < 0) {
        cerr << "Error: Degree must be non-negative.\n";
        return false;
    }

    poly.coefficients = new int[poly.degree + 1];
    for (int i = 0; i <= poly.degree; ++i) {
        if (!(file >> poly.coefficients[i])) {
            cerr << "Error: Cannot read coefficient " << i << ".\n";
            delete[] poly.coefficients;
            return false;
        }
    }

    if (poly.degree == 0 && poly.coefficients[0] != poly.equal_value) {
        cerr << "Error: For degree 0, coefficient must equal the right-hand value ("
             << poly.coefficients[0] << " != " << poly.equal_value << ").\n";
        delete[] poly.coefficients;
        return false;
    }

    return true;
}

void displayPolynomial(const Polynomial& poly, const string& name) {
    cout << name << ": ";

    if (poly.degree == 0) {
        cout << poly.coefficients[0] << " = " << poly.equal_value;
        return;
    }

    bool firstTerm = true;
    for (int i = poly.degree; i >= 0; --i) {
        int coeff = poly.coefficients[i];
        if (coeff == 0) continue;

        if (!firstTerm) {
            cout << (coeff > 0 ? " + " : " - ");
        } else if (coeff < 0) {
            cout << "-";
        }

        if (abs(coeff) != 1 || i == 0) cout << abs(coeff);
        if (i > 0) cout << "x";
        if (i > 1) cout << "^" << i;

        firstTerm = false;
    }

    cout << " = " << poly.equal_value;
}

void processPair(ifstream& file, int pairNum) {
    Polynomial p1, p2;
    bool validPair = true;

    cout << "\n--- Processing Pair " << pairNum << " ---\n";

   
    if (!readPolynomial(file, p1)) {
        validPair = false;
    }
    else {
        displayPolynomial(p1, "First polynomial");
        cout << endl;
    }

    
    if (validPair) {
        if (!readPolynomial(file, p2)) {
            validPair = false;
            delete[] p1.coefficients;
        }
        else {
            displayPolynomial(p2, "Second polynomial");
            cout << endl;
        }
    }

    
    if (!validPair) {
        
        file.clear();
        while (file.get() != '\n' && !file.eof());

      
        if (file.peek() != '\n' && !file.eof()) {
            while (file.get() != '\n' && !file.eof());
        }
        return;
    }

   
    Polynomial sum;
    sum.degree = max(p1.degree, p2.degree);
    sum.equal_value = p1.equal_value + p2.equal_value;
    sum.coefficients = new int[sum.degree + 1]();
    for (int i = 0; i <= p1.degree; ++i) sum.coefficients[i] += p1.coefficients[i];
    for (int i = 0; i <= p2.degree; ++i) sum.coefficients[i] += p2.coefficients[i];
    displayPolynomial(sum, "Sum");
    cout << endl;
    delete[] sum.coefficients;

    Polynomial diff;
    diff.degree = max(p1.degree, p2.degree);
    diff.equal_value = p1.equal_value - p2.equal_value;
    diff.coefficients = new int[diff.degree + 1]();
    for (int i = 0; i <= p1.degree; ++i) diff.coefficients[i] += p1.coefficients[i];
    for (int i = 0; i <= p2.degree; ++i) diff.coefficients[i] -= p2.coefficients[i];
    displayPolynomial(diff, "Difference");
    cout << endl;
    delete[] diff.coefficients;

    delete[] p1.coefficients;
    delete[] p2.coefficients;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error: Cannot open input file.\n";
        return 1;
    }

    int pairCount = 1;
    while (!file.eof()) {
        processPair(file, pairCount++);

        
        while (isspace(file.peek()) && file.peek() != '\n' && !file.eof()) file.get();
    }

    file.close();
    return 0;
}












