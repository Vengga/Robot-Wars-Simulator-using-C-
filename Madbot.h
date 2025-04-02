/*******
Program:Madbot.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef MADBOT_H
#define MADBOT_H

#include "AbstractRobots.h" // Include the abstract robots header
#include "CustomDynamicArray.h" // Include the custom dynamic array header
#include "HealthManager.h" // Include the health manager header
#include <iostream> // For input and output
#include <cstdlib> // For standard library functions

// Madbot class inheriting from Robot
class Madbot : public Robot {
public:
    // Constructor for Madbot
    Madbot(int x, int y, std::string name, HealthManager& healthManager)
        : Robot(x, y, name, healthManager) {}

         // Copy Constructor
    Madbot(const Madbot& other)
        : Robot(other.x, other.y, other.name, other.healthManager) {}

    // Override the performAction method from Robot
    void performAction(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        fire(battlefield, rows, cols); // Call the fire method
    }

    // Fire method specific to Madbot
    void fire(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) {
        // Possible directions to fire
        std::pair<int, int> directions[] = {
            {x-1, y-1}, {x-1, y}, {x-1, y+1},
            {x, y-1}, {x, y+1},
            {x+1, y-1}, {x+1, y}, {x+1, y+1}
        };

        int idx = rand() % 8; // Randomly choose a direction
        int targetX = directions[idx].first; // Target x-coordinate
        int targetY = directions[idx].second; // Target y-coordinate

        // Check if the target position is within bounds and not empty
        if (targetX >= 0 && targetX < rows && targetY >= 0 && targetY < cols && !battlefield[targetX][targetY].empty()) {
            std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
            healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease health of the target
            if (healthManager.getHealth(battlefield[targetX][targetY]) == 0) { // Check if the target is destroyed
                healthManager.increaseScore(name, 5); // Increase score by 5 points
            }
            battlefield[targetX][targetY] = ""; // Clear the target position (fire at target)
            incrementKills(); // Increment the kill count
        }

        // Check if kills are enough to upgrade
        if (kills >= 3) {
            upgrade(); // Upgrade to a different robot
        }
    }

    // Override the upgrade method from Robot
    void upgrade() override {
        std::cout << name << " is upgrading to RoboTank." << std::endl;
    }

    // Override the getType method from Robot
    std::string getType() const override {
        return "Madbot"; // Return the type of the robot
    }
};

#endif // MADBOT_H

