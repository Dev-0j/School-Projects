// main.cpp
// Author: Jonathan Clayton
// Date: April 3, 2025
// Description: Entry point for the Airgead Banking investment calculator.
//              Handles user input, validation, and drives the display output.

#include <iostream>
#include <limits>
#include "InvestmentCalculator.h"

using namespace std;

int main() {
    InvestmentCalculator calc;

    double initialInvestment = 0.0;
    double monthlyDeposit = 0.0;
    double annualInterest = 0.0;
    int    numYears = 0;
    char   runAgain = 'y';

    while (runAgain == 'y' || runAgain == 'Y') {

        // Display input screen
        cout << "\n**********************************" << endl;
        cout << "********** Data Input ************" << endl;

        // Get and validate initial investment
        cout << "Initial Investment Amount: ";
        while (!(cin >> initialInvestment) || initialInvestment <= 0) {
            cout << "Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Get and validate monthly deposit
        cout << "Monthly Deposit: ";
        while (!(cin >> monthlyDeposit) || monthlyDeposit <= 0) {
            cout << "Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Get and validate annual interest rate
        cout << "Annual Interest: ";
        while (!(cin >> annualInterest) || annualInterest <= 0) {
            cout << "Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Get and validate number of years
        cout << "Number of Years: ";
        while (!(cin >> numYears) || numYears <= 0) {
            cout << "Please enter a positive whole number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Show entered values back to user
        cout << "\n**********************************" << endl;
        cout << "********** Data Input ************" << endl;
        cout << "Initial Investment Amount: $" << initialInvestment << endl;
        cout << "Monthly Deposit: $" << monthlyDeposit << endl;
        cout << "Annual Interest: %" << annualInterest << endl;
        cout << "Number of Years: " << numYears << endl;

        cout << "\nPress any key to continue . . .";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        // Store values and run calculations
        calc.setInitialInvestment(initialInvestment);
        calc.setMonthlyDeposit(monthlyDeposit);
        calc.setAnnualInterest(annualInterest);
        calc.setNumYears(numYears);

        calc.displayWithoutMonthly();
        calc.displayWithMonthly();

        // Ask user if they want to run again
        cout << "\nWould you like to run again? (y/n): ";
        cin >> runAgain;
    }

    cout << "\nThank you for using Airgead Banking. Goodbye!" << endl;

    return 0;
}