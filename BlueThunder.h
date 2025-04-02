/*******
Program:BlueThunder.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef BLUETHUNDER_H
#define BLUETHUNDER_H

#include "AbstractRobots.h" // Including the header file for abstract robots
#include "CustomDynamicArray.h" // Including the header file for custom dynamic array
#include "HealthManager.h" // Including the header file for health manager
#include <iostream> // For input and output
#include <cstdlib> // For standard library functions

// BlueThunder class inheriting from the Robot class
class BlueThunder : public Robot {
public:
    // Constructor for BlueThunder
    BlueThunder(int x, int y, std::string name, HealthManager& healthManager)
        : Robot(x, y, name, healthManager) {}

        // Copy Constructor
    BlueThunder(const BlueThunder& other)
        : Robot(other.x, other.y, other.name, other.healthManager) {}


    // Override the performAction method from the Robot class
    void performAction(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        fire(battlefield, rows, cols); // BlueThunder only fires in its action
    }

    // Method to fire at a target
    void fire(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) {
        // Define possible directions to fire
        std::pair<int, int> directions[] = {
            {x-1, y}, {x-1, y+1}, {x, y+1},
            {x+1, y+1}, {x+1, y}, {x+1, y-1},
            {x, y-1}, {x-1, y-1}
        };

        int idx = rand() % 8; // Randomly choose a direction to fire
        int targetX = directions[idx].first; // Get the x-coordinate of the target
        int targetY = directions[idx].second; // Get the y-coordinate of the target

        // Check if the target coordinates are within the battlefield and not empty
        if (targetX >= 0 && targetX < rows && targetY >= 0 && targetY < cols && !battlefield[targetX][targetY].empty()) {
            std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
            healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease the health of the target
            if (healthManager.getHealth(battlefield[targetX][targetY]) == 0) {
                healthManager.increaseScore(name, 5); // Increase the score if the target is destroyed
            }
            battlefield[targetX][targetY] = ""; // Clear the target position on the battlefield
            incrementKills(); // Increment the kill count
            std::cout << name << " has attacked a robot!" << std::endl;
        }

        // Upgrade the robot if it has 3 or more kills
        if (kills >= 3) {
            upgrade();
        }
    }

    // Method to upgrade the robot
    void upgrade() override {
        std::cout << name << " is upgrading to RoboTank." << std::endl;
        // Implement the logic to replace this BlueThunder with a RoboTank
        // This part might involve interaction with the main simulation logic
    }

    // Method to get the type of the robot
    std::string getType() const override {
        return "BlueThunder";
    }
};

#endif // BLUETHUNDER_H
