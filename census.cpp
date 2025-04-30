#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Initial population input
    long long population;
    cout << "Enter current population: ";
    cin >> population;

    // Rate inputs (per 1000 people)
    double birthRate, deathRate;
    int immigrants, years;

    cout << "Enter annual birth rate (per 1000): ";
    cin >> birthRate;
    
    cout << "Enter annual death rate (per 1000): ";
    cin >> deathRate;
    
    cout << "Enter annual immigrants: ";
    cin >> immigrants;
    
    cout << "Enter years to project: ";
    cin >> years;

    cout << "\nYearly Population Projection:\n";
    cout << fixed << setprecision(0);

    for (int year = 1; year <= years; ++year) {
        // Calculate annual changes
        long long births = static_cast<long long>(population * birthRate / 1000);
        long long deaths = static_cast<long long>(population * deathRate / 1000);
        
        // Update population
        population += births - deaths + immigrants;
        
        // Output projection
        cout << "Year " << year << ": " << population << endl;
    }

    return 0;
}
