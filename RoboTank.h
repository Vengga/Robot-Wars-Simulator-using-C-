/*******
Program:RoboTank.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef ROBOTANK_H
#define ROBOTANK_H

#include "AbstractRobots.h" // Include the abstract robots header
#include "CustomDynamicArray.h" // Include the custom dynamic array header
#include "HealthManager.h" // Include the health manager header
#include <cstdlib> // For standard library functions
#include <iostream> // For input and output

// RoboTank class inheriting from ShootingRobot
class RoboTank : public ShootingRobot {
public:
    // Constructor for RoboTank
    RoboTank(int x, int y, std::string name, HealthManager& healthManager)
        : Robot(x, y, name, healthManager), ShootingRobot(x, y, name, healthManager) {}

         // Copy Constructor
    RoboTank(const RoboTank& other)
        : Robot(other.x, other.y, other.name, other.healthManager), ShootingRobot(other.x, other.y, other.name, other.healthManager) {}

    // Override the performAction method from Robot
    void performAction(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        fire(battlefield, rows, cols); // Call the fire method
    }

    // Override the getType method from Robot
    std::string getType() const override {
        return "RoboTank"; // Return the type of the robot
    }

    // Override the fire method from ShootingRobot
    void fire(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        int targetX = rand() % rows; // Randomly choose a target x-coordinate
        int targetY = rand() % cols; // Randomly choose a target y-coordinate

        if (battlefield[targetX][targetY] != "") { // Check if the target position is not empty
            std::cout << name << " has fired at " << battlefield[targetX][targetY] << "." << std::endl;
            battlefield[targetX][targetY] = ""; // Clear the target position (fire at target)
            incrementKills(); // Increment the kill count
            healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease health of the target
            healthManager.increaseScore(name, 5); // Increase score by 5 points
        }

        std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
    }
};

#endif // ROBOTANK_H
