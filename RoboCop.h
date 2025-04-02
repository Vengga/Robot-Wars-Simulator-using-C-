/*******
Program:RoboCop.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef ROBOCOP_H
#define ROBOCOP_H

#include "AbstractRobots.h" // Include the abstract robots header
#include "CustomDynamicArray.h" // Include the custom dynamic array header
#include "HealthManager.h" // Include the health manager header
#include <cstdlib> // For standard library functions
#include <iostream> // For input and output
#include <string> // For string manipulation

// RoboCop class inheriting from SeeingRobot, MovingRobot, and ShootingRobot
class RoboCop : public SeeingRobot, public MovingRobot, public ShootingRobot {
public:
    // Constructor for RoboCop
    RoboCop(int x, int y, std::string name, HealthManager& healthManager)
        : Robot(x, y, name, healthManager), SeeingRobot(x, y, name, healthManager), MovingRobot(x, y, name, healthManager), ShootingRobot(x, y, name, healthManager) {}

        // Copy Constructor
    RoboCop(const RoboCop& other)
        : Robot(other.x, other.y, other.name, other.healthManager),
          SeeingRobot(other.x, other.y, other.name, other.healthManager),
          MovingRobot(other.x, other.y, other.name, other.healthManager),
          ShootingRobot(other.x, other.y, other.name, other.healthManager) {}

    // Override the look method from SeeingRobot
    void look(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        std::cout << name << " looks around at (" << x << ", " << y << ")." << std::endl;
        // Iterate over the battlefield to find a target
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (battlefield[i][j] != "" && battlefield[i][j] != name) {
                    targetName = battlefield[i][j]; // Set the target name
                    std::cout << name << " targets " << targetName << " at (" << i << ", " << j << ")." << std::endl;
                    return;
                }
            }
        }
    }

    // Override the move method from MovingRobot
    void move(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        int newX, newY;
        // Randomly choose a direction to move
        do {
            int direction = rand() % 8;
            newX = x + ((direction % 3) - 1);
            newY = y + ((direction / 3) - 1);
        } while ((newX < 0 || newX >= rows || newY < 0 || newY >= cols ||
                 (!upgraded && battlefield[newX][newY] != "") ||
                 (newX == x && newY == y)));

        std::cout << name << " moves to (" << newX << ", " << newY << ")." << std::endl;
        x = newX; // Update x-coordinate
        y = newY; // Update y-coordinate
    }

    // Override the fire method from ShootingRobot
    void fire(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        // Fire three shots
        for (int i = 0; i < 3; ++i) {
            int targetX, targetY;
            // Randomly choose a target within a certain range
            do {
                targetX = x + (rand() % 21 - 10);
                targetY = y + (rand() % 21 - 10);
            } while ((abs(targetX - x) + abs(targetY - y) > 10) || (targetX == x && targetY == y) ||
                     targetX < 0 || targetY < 0 || targetX >= rows || targetY >= cols);

            std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
            // Check if the target is within bounds and not empty
            if (targetX >= 0 && targetX < rows && targetY >= 0 && targetY < cols && battlefield[targetX][targetY] != "") {
                std::cout << name << " has fired at " << battlefield[targetX][targetY] << "." << std::endl;
                healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease health of the target
                if (healthManager.getHealth(battlefield[targetX][targetY]) == 0) { // Check if the target is destroyed
                    healthManager.increaseScore(name, 5); // Increase score by 5 points
                }
                battlefield[targetX][targetY] = ""; // Clear the target position
                incrementKills(); // Increment the kill count
            }
        }
    }

    // Override the performAction method from Robot
    void performAction(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        look(battlefield, rows, cols); // Call the look method
        move(battlefield, rows, cols); // Call the move method
        fire(battlefield, rows, cols); // Call the fire method
        if (kills >= 3 && !upgraded) { // Check if the robot should upgrade
            upgrade(); // Call the upgrade method
        }
    }

    // Override the getType method from Robot
    std::string getType() const override {
        return upgraded ? "TerminatorRoboCop" : "RoboCop"; // Return the type of the robot
    }

private:
    // Override the upgrade method from Robot
    void upgrade() override {
        std::cout << name << " is upgrading to TerminatorRoboCop." << std::endl;
        upgraded = true; // Set the upgraded flag to true
    }
};

#endif // ROBOCOP_H
