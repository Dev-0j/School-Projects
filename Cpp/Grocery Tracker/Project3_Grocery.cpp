/*
Name: Jon C
Course: CS210
Assignment: Project Three - Grocery Tracking Program
Date: 04/18/2026

Description:
This program reads grocery items from a file, counts how often each item appears,
and allows the user to search, display all items, or view a histogram.
It also creates a frequency.dat file to store the results.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

class GroceryTracker {
private:
    map<string, int> groceryMap;

public:
    void LoadFile() {
        ifstream inFS("CS210_Project_Three_Input_File.txt");
        string item;

        while (inFS >> item) {
            groceryMap[item]++;
        }
    }

    void SearchItem() {
        string item;
        cout << "\nEnter item: ";
        cin >> item;

        cout << item << " appears " << groceryMap[item] << " times.\n";
    }

    void PrintAll() {
        cout << "\n--- ITEM FREQUENCY LIST ---\n";
        for (auto pair : groceryMap) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }

    void PrintHistogram() {
        cout << "\n--- HISTOGRAM ---\n";

        // find longest item name
        int maxLength = 0;
        for (auto pair : groceryMap) {
            if (pair.first.length() > maxLength) {
                maxLength = pair.first.length();
            }
        }

        // print aligned histogram
        for (auto pair : groceryMap) {
            cout << pair.first;

            // spacing
            for (int i = pair.first.length(); i < maxLength + 2; i++) {
                cout << " ";
            }

            // stars
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }

    void SaveToFile() {
        ofstream outFS("frequency.dat");

        for (auto pair : groceryMap) {
            outFS << pair.first << " " << pair.second << endl;
        }
    }
};

int main() {
    GroceryTracker tracker;
    tracker.LoadFile();
    tracker.SaveToFile();

    int choice = 0;

    while (choice != 4) {

        cout << "\n============================\n";
        cout << "   Grocery Tracking Menu\n";
        cout << "============================\n";

        cout << "1. Search item\n";
        cout << "2. Print all\n";
        cout << "3. Histogram\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        // input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number 1-4.\n";
            continue;
        }

        if (choice < 1 || choice > 4) {
            cout << "Please enter a valid option (1-4).\n";
            continue;
        }

        if (choice == 1) {
            tracker.SearchItem();
        }
        else if (choice == 2) {
            tracker.PrintAll();
        }
        else if (choice == 3) {
            tracker.PrintHistogram();
        }
    }

    cout << "\nExiting program.\n";
    return 0;
}