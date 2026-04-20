// InvestmentCalculator.h
// Author: Jonathan Clayton
// Date: April 3, 2025
// Description: Header file for the InvestmentCalculator class.
//              Declares member variables and functions used to
//              calculate compound interest for Airgead Banking.

#ifndef AIRGEAD_INVESTMENTCALCULATOR_H_
#define AIRGEAD_INVESTMENTCALCULATOR_H_

class InvestmentCalculator {
public:
    InvestmentCalculator();

    // Setters
    void setInitialInvestment(double t_amount);
    void setMonthlyDeposit(double t_amount);
    void setAnnualInterest(double t_rate);
    void setNumYears(int t_years);

    // Getters
    double getInitialInvestment() const;
    double getMonthlyDeposit() const;
    double getAnnualInterest() const;
    int getNumYears() const;

    // Display functions
    void displayWithoutMonthly() const;
    void displayWithMonthly() const;

private:
    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterest;
    int    m_numYears;
};

#endif