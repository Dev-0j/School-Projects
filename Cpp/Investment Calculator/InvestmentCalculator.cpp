// InvestmentCalculator.cpp
// Author: Jonathan Clayton
// Date: April 3, 2025
// Description: Defines the functions declared in InvestmentCalculator.h.
//              Handles all compound interest calculations and output.

#include "InvestmentCalculator.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Formats a double value as a dollar string ex: $617.55
static string formatDollars(double t_value) {
    ostringstream oss;
    oss << "$" << fixed << setprecision(2) << t_value;
    return oss.str();
}

// Constructor -- sets all values to zero on startup
InvestmentCalculator::InvestmentCalculator() {
    m_initialInvestment = 0.0;
    m_monthlyDeposit = 0.0;
    m_annualInterest = 0.0;
    m_numYears = 0;
}

// Setters
void InvestmentCalculator::setInitialInvestment(double t_amount) {
    m_initialInvestment = t_amount;
}
void InvestmentCalculator::setMonthlyDeposit(double t_amount) {
    m_monthlyDeposit = t_amount;
}
void InvestmentCalculator::setAnnualInterest(double t_rate) {
    m_annualInterest = t_rate;
}
void InvestmentCalculator::setNumYears(int t_years) {
    m_numYears = t_years;
}

// Getters
double InvestmentCalculator::getInitialInvestment() const { return m_initialInvestment; }
double InvestmentCalculator::getMonthlyDeposit()    const { return m_monthlyDeposit; }
double InvestmentCalculator::getAnnualInterest()    const { return m_annualInterest; }
int    InvestmentCalculator::getNumYears()          const { return m_numYears; }

// Calculates and prints balance/interest per year with no monthly deposit
void InvestmentCalculator::displayWithoutMonthly() const {
    cout << "\n================================================================" << endl;
    cout << "   Balance and Interest Without Additional Monthly Deposits" << endl;
    cout << "================================================================" << endl;
    cout << left << setw(8) << "Year"
        << right << setw(20) << "Year End Balance"
        << right << setw(26) << "Year End Earned Interest" << endl;
    cout << "----------------------------------------------------------------" << endl;

    double balance = m_initialInvestment;
    double monthlyRate = (m_annualInterest / 100.0) / 12.0; // convert annual % to monthly decimal

    for (int year = 1; year <= m_numYears; ++year) {
        double interestEarned = 0.0;

        // compound monthly -- no deposit added
        for (int month = 1; month <= 12; ++month) {
            double interest = balance * monthlyRate;
            balance += interest;
            interestEarned += interest;
        }

        cout << left << setw(8) << year
            << right << setw(20) << formatDollars(balance)
            << right << setw(26) << formatDollars(interestEarned) << endl;
    }
    cout << "================================================================" << endl;
}

// Calculates and prints balance/interest per year with monthly deposit included
void InvestmentCalculator::displayWithMonthly() const {
    cout << "\n================================================================" << endl;
    cout << "     Balance and Interest With Additional Monthly Deposits" << endl;
    cout << "================================================================" << endl;
    cout << left << setw(8) << "Year"
        << right << setw(20) << "Year End Balance"
        << right << setw(26) << "Year End Earned Interest" << endl;
    cout << "----------------------------------------------------------------" << endl;

    double balance = m_initialInvestment;
    double monthlyRate = (m_annualInterest / 100.0) / 12.0; // convert annual % to monthly decimal

    for (int year = 1; year <= m_numYears; ++year) {
        double interestEarned = 0.0;

        // deposit is added before interest is applied each month
        for (int month = 1; month <= 12; ++month) {
            double total = balance + m_monthlyDeposit;
            double interest = total * monthlyRate;
            balance = total + interest;
            interestEarned += interest;
        }

        cout << left << setw(8) << year
            << right << setw(20) << formatDollars(balance)
            << right << setw(26) << formatDollars(interestEarned) << endl;
    }
    cout << "================================================================" << endl;
}