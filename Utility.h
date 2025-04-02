/*******
Program:Utility.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream> // For standard input and output
#include "CustomDynamicArray.h" // Include custom dynamic array header

// Function to print the battlefield to the console
void printBattlefield(const CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield) {
    int numRows = battlefield.getSize(); // Get the number of rows in the battlefield
    if (numRows == 0) return; // If there are no rows, exit the function
    int numCols = battlefield[0].getSize(); // Get the number of columns in the first row

    // Print the column headers
    std::cout << "   ";
    for (int j = 0; j < numCols; ++j) {
        std::cout << (j % 10) << " "; // Print column numbers modulo 10
    }
    std::cout << std::endl;

    // Print the top border of the battlefield
    std::cout << "  ";
    for (int j = 0; j < numCols; ++j) {
        std::cout << "--";
    }
    std::cout << "-" << std::endl;

    // Print each row of the battlefield
    for (int i = 0; i < numRows; ++i) {
        std::cout << (i % 10) << " |"; // Print row numbers modulo 10
        for (int j = 0; j < numCols; ++j) {
            if (!battlefield[i][j].empty()) {
                std::cout << battlefield[i][j][0] << " "; // Print the first character of the robot's name if the cell is not empty
            } else {
                std::cout << ". "; // Print a dot if the cell is empty
            }
        }
        std::cout << "|" << std::endl; // End of row
    }

    // Print the bottom border of the battlefield
    std::cout << "  ";
    for (int j = 0; j < numCols; ++j) {
        std::cout << "--";
    }
    std::cout << "-" << std::endl;
}

// Function to log the battlefield to a file
void logBattlefield(std::ofstream& logFile, const CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield) {
    int numRows = battlefield.getSize(); // Get the number of rows in the battlefield
    if (numRows == 0) return; // If there are no rows, exit the function
    int numCols = battlefield[0].getSize(); // Get the number of columns in the first row

    // Log the column headers
    logFile << "   ";
    for (int j = 0; j < numCols; ++j) {
        logFile << (j % 10) << " "; // Log column numbers modulo 10
    }
    logFile << std::endl;

    // Log the top border of the battlefield
    logFile << "  ";
    for (int j = 0; j < numCols; ++j) {
        logFile << "--";
    }
    logFile << "-" << std::endl;

    // Log each row of the battlefield
    for (int i = 0; i < numRows; ++i) {
        logFile << (i % 10) << " |"; // Log row numbers modulo 10
        for (int j = 0; j < numCols; ++j) {
            if (!battlefield[i][j].empty()) {
                logFile << battlefield[i][j][0] << " "; // Log the first character of the robot's name if the cell is not empty
            } else {
                logFile << ". "; // Log a dot if the cell is empty
            }
        }
        logFile << "|" << std::endl; // End of row
    }

    // Log the bottom border of the battlefield
    logFile << "  ";
    for (int j = 0; j < numCols; ++j) {
        logFile << "--";
    }
    logFile << "-" << std::endl;
}

#endif // UTILITY_H
