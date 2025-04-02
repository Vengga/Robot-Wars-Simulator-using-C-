/*******
Program:UltimateRobot.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef ULTIMATEROBOT_H
#define ULTIMATEROBOT_H

#include "AbstractRobots.h" // Base classes for different robot capabilities
#include "CustomDynamicArray.h" // Custom dynamic array implementation
#include <cstdlib> // For random number generation
#include <iostream> // For input and output
#include "HealthManager.h" // HealthManager class to manage robot health and scores

// UltimateRobot class inheriting from SeeingRobot, MovingRobot, and ShootingRobot
class UltimateRobot : public SeeingRobot, public MovingRobot, public ShootingRobot {
public:
    // Constructor to initialize the UltimateRobot with position, name, and health manager
    UltimateRobot(int x, int y, const std::string& name, HealthManager& healthManager)
        : Robot(x, y, name, healthManager), SeeingRobot(x, y, name, healthManager), MovingRobot(x, y, name, healthManager), ShootingRobot(x, y, name, healthManager) {}

        // Copy Constructor
    UltimateRobot(const UltimateRobot& other)
        : Robot(other.x, other.y, other.name, other.healthManager),
          SeeingRobot(other.x, other.y, other.name, other.healthManager),
          MovingRobot(other.x, other.y, other.name, other.healthManager),
          ShootingRobot(other.x, other.y, other.name, other.healthManager) {}

    // Look around method overridden from SeeingRobot
    void look(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        std::cout << name << " looks around at (" << x << ", " << y << ")." << std::endl;
    }

    // Move method overridden from MovingRobot
    void move(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        std::pair<int, int> neighbors[8] = {
            {x - 1, y - 1}, {x - 1, y}, {x - 1, y + 1},
            {x, y - 1}, {x, y + 1},
            {x + 1, y - 1}, {x + 1, y}, {x + 1, y + 1}
        };

        std::pair<int, int> target = {x, y}; // Default target is the current position
        for (const auto& neighbor : neighbors) {
            int newX = neighbor.first;
            int newY = neighbor.second;
            if (newX >= 0 && newY >= 0 && newX < rows && newY < cols && !(newX == 0 && newY == 0)) {
                target = neighbor; // Set target to a valid neighbor
                if (!battlefield[newX][newY].empty()) { // Check if the neighbor has a robot
                    std::cout << name << " has stepped on " << battlefield[newX][newY] << "." << std::endl;
                    healthManager.decreaseHealth(battlefield[newX][newY]); // Decrease health of the robot at the neighbor position
                    if (healthManager.getHealth(battlefield[newX][newY]) == 0) {
                        healthManager.increaseScore(name, 5); // Increase score if the robot at the neighbor position is dead
                    }
                    battlefield[newX][newY] = ""; // Clear the position on the battlefield
                    incrementKills(); // Increment kills for the robot
                }
                break; // Stop after finding the first valid neighbor
            }
        }

        int newX = target.first;
        int newY = target.second;
        if (newX != x || newY != y) { // Check if the target position is different from the current position
            std::cout << name << " moves to (" << newX << ", " << newY << ")." << std::endl;
            battlefield[x][y] = "";  // Clear the current position
            x = newX;
            y = newY;
            battlefield[x][y] = name;  // Update the new position
        }
    }

    // Fire method overridden from ShootingRobot
    void fire(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        for (int i = 0; i < 3; ++i) { // Fire three times
            int targetX, targetY;
            do {
                targetX = rand() % rows;
                targetY = rand() % cols;
            } while ((targetX == x && targetY == y) || targetX < 0 || targetY < 0 || targetX >= rows || targetY >= cols || (targetX == 0 && targetY == 0));

            std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
            if (!battlefield[targetX][targetY].empty()) { // Check if the target position has a robot
                std::cout << name << " has fired at " << battlefield[targetX][targetY] << "." << std::endl;
                healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease health of the robot at the target position
                if (healthManager.getHealth(battlefield[targetX][targetY]) == 0) {
                    healthManager.increaseScore(name, 5); // Increase score if the robot at the target position is dead
                }
                battlefield[targetX][targetY] = ""; // Clear the position on the battlefield
                incrementKills(); // Increment kills for the robot
            }
        }
    }

    // Perform action method that calls look, move, and fire in sequence
    void performAction(CustomDynamicArray<CustomDynamicArray<std::string>>& battlefield, int rows, int cols) override {
        look(battlefield, rows, cols);
        move(battlefield, rows, cols);
        fire(battlefield, rows, cols);
    }

    // Get the type of the robot
    std::string getType() const override {
        return "UltimateRobot";
    }
};

#endif // ULTIMATEROBOT_H
