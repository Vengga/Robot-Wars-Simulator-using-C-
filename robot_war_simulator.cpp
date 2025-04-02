/*******
Program:robot_war_simulator.cpp
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#include <iostream> // For input and output
#include <fstream> // For file handling
#include <sstream> // For string stream operations
#include <ctime> // For time functions
#include "AbstractRobots.h" // Including the header file for abstract robots
#include "RoboCop.h" // Including the header file for RoboCop
#include "BlueThunder.h" // Including the header file for BlueThunder
#include "Madbot.h" // Including the header file for Madbot
#include "RoboTank.h" // Including the header file for RoboTank
#include "Terminator.h" // Including the header file for Terminator
#include "TerminatorRoboCop.h" // Including the header file for TerminatorRoboCop
#include "UltimateRobot.h" // Including the header file for UltimateRobot
#include "Utility.h" // Including the header file for utility functions
#include "CustomDynamicArray.h" // Including the header file for custom dynamic array
#include "HealthManager.h" // Including the header file for health manager

using namespace std; // Using the standard namespace

// Function to load initial conditions from a file
void loadInitialConditions(const string& filename, CustomDynamicArray<CustomDynamicArray<string>>& battlefield, CustomDynamicArray<Robot*>& robots, int& numTurns, vector<string>& robotNames, HealthManager& healthManager) {
    ifstream inputFile(filename); // Open the file for reading
    if (!inputFile) { // Check if the file opened successfully
        throw runtime_error("Error opening input file!"); // Throw an error if the file couldn't be opened
    }

    string line; // Variable to store each line read from the file
    int numRows, numCols, numRobots; // Variables to store number of rows, columns, and robots

    getline(inputFile, line); // Read the first line from the file
    istringstream ss(line); // Create a string stream from the line
    ss >> numRows >> numCols; // Extract number of rows and columns

    if (numRows > 30 || numCols > 30) { // Check if the battlefield size exceeds the maximum allowed size
        throw runtime_error("Error: Battlefield size exceeds 30x30 grid!"); // Throw an error if it does
    }

    battlefield.setSize(numRows); // Set the size of the battlefield
    for (int i = 0; i < numRows; ++i) {
        battlefield[i].setSize(numCols); // Set the size of each row in the battlefield
    }

    getline(inputFile, line); // Read the second line from the file
    ss.clear(); // Clear the string stream
    ss.str(line); // Set the string stream to the new line
    ss >> numTurns; // Extract number of turns

    getline(inputFile, line); // Read the third line from the file
    ss.clear(); // Clear the string stream
    ss.str(line); // Set the string stream to the new line
    ss >> numRobots; // Extract number of robots

    for (int i = 0; i < numRobots; ++i) { // Loop to read details of each robot
        getline(inputFile, line); // Read the next line from the file
        ss.clear(); // Clear the string stream
        ss.str(line); // Set the string stream to the new line
        string type, name; // Variables to store robot type and name
        int x, y; // Variables to store robot's coordinates
        ss >> type >> name >> x >> y; // Extract robot's type, name, and coordinates

        if (name == "random") { // If the name is "random"
            x = rand() % numRows; // Generate a random x coordinate
            y = rand() % numCols; // Generate a random y coordinate
        }

        name[0] = toupper(name[0]); // Capitalize the first letter of the name
        for (size_t j = 1; j < name.size(); ++j) {
            name[j] = tolower(name[j]); // Convert the rest of the name to lowercase
        }

        Robot* robot = nullptr; // Pointer to store the new robot

        // Create a new robot based on its type
        if (type == "RoboCop") {
            robot = new RoboCop(x, y, name, healthManager);
        } else if (type == "BlueThunder") {
            robot = new BlueThunder(x, y, name, healthManager);
        } else if (type == "Madbot") {
            robot = new Madbot(x, y, name, healthManager);
        } else if (type == "RoboTank") {
            robot = new RoboTank(x, y, name, healthManager);
        } else if (type == "Terminator") {
            robot = new Terminator(x, y, name, healthManager);
        } else if (type == "UltimateRobot") {
            robot = new UltimateRobot(x, y, name, healthManager);
        }

        if (robot != nullptr) { // If a robot was created successfully
            robots.push_back(robot); // Add the robot to the list of robots
            battlefield[x][y] = name; // Place the robot on the battlefield
            robotNames.push_back(name); // Add the robot's name to the list of names
            healthManager.registerRobot(name); // Register the robot with the health manager
        }
    }
}

// Function to validate and correct coordinates if they are out of bounds
void validateCoordinates(int& x, int& y, int maxX, int maxY) {
    if (x < 0) x = 0; // If x is less than 0, set it to 0
    if (x >= maxX) x = maxX - 1; // If x is greater than or equal to maxX, set it to maxX - 1
    if (y < 0) y = 0; // If y is less than 0, set it to 0
    if (y >= maxY) y = maxY - 1; // If y is greater than or equal to maxY, set it to maxY - 1
}

// Function to update the lives of robots based on their health
void updateRobotLives(CustomDynamicArray<Robot*>& robots, HealthManager& healthManager) {
    for (size_t i = 0; i < robots.getSize(); ++i) { // Loop through each robot
        if (healthManager.getHealth(robots[i]->name) <= 0) { // If the robot's health is zero or less
            robots[i]->decrementLives(); // Decrease the robot's lives by one
        }
    }
}

// Function to remove dead robots from the battlefield
void removeDeadRobots(CustomDynamicArray<Robot*>& robots, CustomDynamicArray<CustomDynamicArray<string>>& battlefield, HealthManager& healthManager, ofstream& logFile) {
    for (size_t i = 0; i < robots.getSize(); ) { // Loop through each robot
        Robot* robot = robots[i]; // Get the current robot
        if (robot->lives <= 0) { // If the robot has no lives left
            cout << robot->name << " died and is removed from the battlefield.\n";
            logFile << robot->name << " died and is removed from the battlefield.\n"; // Log the robot's removal
            battlefield[robot->x][robot->y] = ""; // Clear the robot's position on the battlefield
            robots.remove_at(i); // Remove the robot from the list of robots
            delete robot; // Delete the robot object
        } else {
            ++i; // Move to the next robot
        }
    }
}

// Function to perform the action of a robot
void performRobotAction(Robot* robot, CustomDynamicArray<CustomDynamicArray<string>>& battlefield, int rows, int cols, HealthManager& healthManager) {
    if (battlefield.getSize() > 0 && battlefield[robot->x].getSize() > 0 && battlefield[robot->x][robot->y] == robot->name) {
        battlefield[robot->x][robot->y] = ""; // Clear the robot's old position
    }
    robot->performAction(battlefield, rows, cols); // Perform the robot's action
    validateCoordinates(robot->x, robot->y, rows, cols); // Validate the robot's new coordinates
    battlefield[robot->x][robot->y] = robot->name; // Update the robot's new position on the battlefield

    if (!robot->targetName.empty()) { // If the robot has a target
        healthManager.decreaseHealth(robot->targetName); // Decrease the target's health
        healthManager.increaseScore(robot->name, 5); // Increase the robot's score by 5 points
        robot->targetName = ""; // Clear the target name
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    CustomDynamicArray<CustomDynamicArray<string>> battlefield; // Create the battlefield
    CustomDynamicArray<Robot*> robots; // Create the list of robots
    int numTurns; // Variable to store the number of turns
    vector<string> robotNames; // List to store the names of robots

    ofstream logFile("simulation_log.txt"); // Open the log file for writing
    if (!logFile) { // Check if the file opened successfully
        cerr << "Error opening output file!" << endl; // Print an error message if the file couldn't be opened
        return 1; // Return 1 to indicate failure
    }

    HealthManager healthManager(robotNames); // Create a health manager with the list of robot names

    try {
        loadInitialConditions("initial_conditions.txt", battlefield, robots, numTurns, robotNames, healthManager); // Load the initial conditions from the file
    } catch (const runtime_error& e) {
        cerr << e.what() << endl; // Print an error message if there was an error loading the initial conditions
        return 1; // Return 1 to indicate failure
    }

    cout << "Initial Battlefield: \n"; // Print the initial battlefield
    logFile << "Initial Battlefield: \n"; // Log the initial battlefield
    printBattlefield(battlefield); // Print the battlefield to the console
    logBattlefield(logFile, battlefield); // Log the battlefield to the log file

    cout << "\nHEALTHBAR:\n"; // Print the health bar
    logFile << "\nHEALTHBAR:\n"; // Log the health bar
    healthManager.printHealth(); // Print the health bar to the console
    healthManager.logHealth(logFile); // Log the health bar to the log file

    cout << "\nSCOREBOARD:\n"; // Print the scoreboard
    logFile << "\nSCOREBOARD:\n"; // Log the scoreboard
    healthManager.printScores(); // Print the scores to the console
    healthManager.logScores(logFile); // Log the scores to the log file

    for (int turn = 1; turn <= numTurns; ++turn) { // Loop through each turn
        cout << "\nTurn " << turn << "\n"; // Print the turn number
        logFile << "\nTurn " << turn << "\n"; // Log the turn number

        for (size_t i = 0; i < robots.getSize(); ++i) { // Loop through each robot
            performRobotAction(robots[i], battlefield, battlefield.getSize(), battlefield[0].getSize(), healthManager); // Perform the robot's action
        }

        updateRobotLives(robots, healthManager); // Update the lives of the robots
        removeDeadRobots(robots, battlefield, healthManager, logFile); // Remove dead robots

        cout << "\nBattlefield:\n"; // Print the battlefield
        printBattlefield(battlefield); // Print the battlefield to the console
        logBattlefield(logFile, battlefield); // Log the battlefield to the log file

        cout << "\nHEALTHBAR:\n"; // Print the health bar
        logFile << "\nHEALTHBAR:\n"; // Log the health bar
        healthManager.printHealth(); // Print the health bar to the console
        healthManager.logHealth(logFile); // Log the health bar to the log file

        cout << "\nSCOREBOARD:\n"; // Print the scoreboard
        logFile << "\nSCOREBOARD:\n"; // Log the scoreboard
        healthManager.printScores(); // Print the scores to the console
        healthManager.logScores(logFile); // Log the scores to the log file

        if (turn == numTurns) { // If this is the last turn
            string winner = healthManager.getWinner(); // Get the winner
            if (!winner.empty()) {
                cout << "\nThe winner is: " << winner << " with " << healthManager.getScore(winner) << " points!\n"; // Print the winner
                logFile << "\nThe winner is: " << winner << " with " << healthManager.getScore(winner) << " points!\n"; // Log the winner
            }
        }
    }

    for (size_t i = 0; i < robots.getSize(); ++i) { // Loop through each robot
        delete robots[i]; // Delete the robot object
    }

    logFile.close(); // Close the log file
    return 0; // Return 0 to indicate success
}
