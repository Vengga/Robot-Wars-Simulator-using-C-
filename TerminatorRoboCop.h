/*******
Program:TerminatorRoboCop.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

#include "AbstractRobots.h" // Include the abstract robots header
#include "CustomDynamicArray.h" // Include the custom dynamic array header
#include "HealthManager.h" // Include the health manager header
#include <iostream> // For input and output

// TerminatorRoboCop class inheriting from SeeingRobot, MovingRobot, and ShootingRobot
class TerminatorRoboCop : public SeeingRobot, public MovingRobot, public ShootingRobot {
public:
    // Constructor for TerminatorRoboCop
    TerminatorRoboCop(int x, int y, std::string name, HealthManager& hm)
        : Robot(x, y, name, hm), SeeingRobot(x, y, name, hm), MovingRobot(x, y, name, hm), ShootingRobot(x, y, name, hm) {}

         // Copy Constructor
    TerminatorRoboCop(const TerminatorRoboCop& other)
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
        // Define possible neighboring positions
        std::pair<int, int> neighbors[8] = {
            {x - 1, y - 1}, {x - 1, y}, {x - 1, y + 1},
            {x, y - 1}, {x, y + 1},
            {x + 1, y - 1}, {x + 1, y}, {x + 1, y + 1}
        };

        std::pair<int, int> target = {x, y}; // Initialize target position
        for (const auto& neighbor : neighbors) { // Iterate through neighboring positions
            int newX = neighbor.first;
            int newY = neighbor.second;
            // Check if the neighbor is within the battlefield and contains an enemy
            if (newX >= 0 && newY >= 0 && newX < rows && newY < cols && battlefield[newX][newY] != "" && !(newX == 0 && newY == 0)) {
                target = neighbor; // Set target to this neighbor
                break;
            }
        }

        int newX = target.first;
        int newY = target.second;
        if (newX != x || newY != y) { // If target position is different from current position
            std::cout << name << " moves to (" << newX << ", " << newY << ")." << std::endl;
            if (battlefield[newX][newY] != "") { // If the target position contains an enemy
                std::cout << name << " has terminated " << battlefield[newX][newY] << "." << std::endl;
                healthManager.decreaseHealth(battlefield[newX][newY]); // Decrease health of the enemy
                if (healthManager.getHealth(battlefield[newX][newY]) == 0) {
                    healthManager.increaseScore(name, 5); // Increase score if the enemy is destroyed
                }
                battlefield[newX][newY] = ""; // Clear the target position
                incrementKills(); // Increment the kill count
            }
            x = newX; // Update x-coordinate
            y = newY; // Update y-coordinate
        }
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
                     targetX < 0 || targetY < 0 || targetX >= rows || targetY >= cols || (targetX == 0 && targetY == 0));

            std::cout << name << " fires at (" << targetX << ", " << targetY << ")." << std::endl;
            if (battlefield[targetX][targetY] != "") { // If the target position contains an enemy
                std::cout << name << " has fired at " << battlefield[targetX][targetY] << "." << std::endl;
                healthManager.decreaseHealth(battlefield[targetX][targetY]); // Decrease health of the enemy
                if (healthManager.getHealth(battlefield[targetX][targetY]) == 0) {
                    healthManager.increaseScore(name, 5); // Increase score if the enemy is destroyed
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
        return upgraded ? "UltimateRobot" : "TerminatorRoboCop"; // Return the type of the robot
    }

private:
    // Override the upgrade method from Robot
    void upgrade() override {
        std::cout << name << " is upgrading to UltimateRobot." << std::endl;
        upgraded = true; // Set the upgraded flag to true
    }
};

#endif // TERMINATORROBOCOP_H

