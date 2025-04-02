/*******
Program:Terminator.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef TERMINATOR_H
#define TERMINATOR_H

#include "AbstractRobots.h" // Include the abstract robots header
#include "CustomDynamicArray.h" // Include the custom dynamic array header
#include "HealthManager.h" // Include the health manager header
#include <iostream> // For input and output
#include <cstdlib> // For standard library functions

// Terminator class inheriting from SeeingRobot, MovingRobot, and ShootingRobot
class Terminator : public SeeingRobot, public MovingRobot, public ShootingRobot {
public:
    // Constructor for Terminator
    Terminator(int x, int y, std::string name, HealthManager& healthManager)
        : Robot(x, y, name, healthManager), SeeingRobot(x, y, name, healthManager), MovingRobot(x, y, name, healthManager), ShootingRobot(x, y, name, healthManager) {}

         // Copy Constructor
    Terminator(const Terminator& other)
        : Robot(other.x, other.y, other.name, other.healthManager),
          SeeingRobot(other.x, other.y, other.name, other.healthManager),
          MovingRobot(other.x, other.y, other.name, other.healthManager),
          ShootingRobot(other.x, other.y, other.name, other.healthManager) {}

    // Override the look method from SeeingRobot
    void look(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        std::cout << name << " looks around at (" << x << ", " << y << ")." << std::endl;
    }

    // Override the move method from MovingRobot
    void move(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        int newX, newY; // New coordinates for the move
        do {
            int direction = rand() % 8; // Randomly choose a direction to move
            newX = x + ((direction % 3) - 1); // Calculate new x-coordinate
            newY = y + ((direction / 3) - 1); // Calculate new y-coordinate
        } while ((newX < 0 || newX >= rows || newY < 0 || newY >= cols || // Check boundaries
                 (!upgraded && battlefield[newX][newY] != "") || // Check if the position is occupied
                 (newX == x && newY == y))); // Ensure the new position is different

        std::cout << name << " moves to (" << newX << ", " << newY << ")." << std::endl;
        x = newX; // Update x-coordinate
        y = newY; // Update y-coordinate
    }

    // Override the fire method from ShootingRobot
    void fire(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        for (int i = 0; i < 3; ++i) { // Fire three times
            int targetX, targetY; // Target coordinates
            do {
                targetX = x + (rand() % 21 - 10); // Calculate target x-coordinate
                targetY = y + (rand() % 21 - 10); // Calculate target y-coordinate
            } while ((abs(targetX - x) + abs(targetY - y) > 10) || (targetX == x && targetY == y) || // Check distance and ensure different position
                     targetX < 0 || targetY < 0 || targetX >= rows || targetY >= cols); // Check boundaries

            std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
            if (targetX >= 0 && targetX < rows && targetY >= 0 && targetY < cols && battlefield[targetX][targetY] != "") { // Check if target is valid
                std::cout << name << " has fired at " << battlefield[targetX][targetY] << "." << std::endl;
                healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease health of the target
                if (healthManager.getHealth(battlefield[targetX][targetY]) == 0) {
                    healthManager.increaseScore(name, 5); // Increase score if target is destroyed
                }
                battlefield[targetX][targetY] = ""; // Clear the target position
                incrementKills(); // Increment the kill count
            }
        }
    }

    // Override the performAction method from Robot
    void performAction(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        look(battlefield, rows, cols); // Look around
        move(battlefield, rows, cols); // Move to a new position
        fire(battlefield, rows, cols); // Fire at targets
        if (kills >= 3 && !upgraded) { // Check if eligible for upgrade
            upgrade();
        }
    }

    // Override the getType method from Robot
    std::string getType() const override {
        return upgraded ? "UltimateRobot" : "Terminator"; // Return type based on upgrade status
    }

private:
    // Override the upgrade method from Robot
    void upgrade() override {
        std::cout << name << " is upgrading to UltimateRobot." << std::endl;
        upgraded = true; // Set upgrade status to true
    }
};

#endif // TERMINATOR_H

