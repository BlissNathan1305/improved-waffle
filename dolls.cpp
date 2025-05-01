#include <iostream>
using namespace std;

int main() {
    double naira, dollars;
    const double rate = 1700.0; // Naira per Dollar

    cout << "Enter amount in Naira: ";
    cin >> naira;

    dollars = naira / rate;

    cout << "Equivalent in Dollars: $" << dollars << endl;

    return 0;
}
