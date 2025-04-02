/*******
Program:AbstractRobots.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef ABSTRACTROBOTS_H
#define ABSTRACTROBOTS_H

#include <iostream> // For standard input and output
#include <string> // For standard string operations
#include "CustomDynamicArray.h" // Include custom dynamic array header
#include "HealthManager.h" // Include the full definition of HealthManager

using namespace std;

// Base class for all robots
class Robot {
public:
    int x, y; // Coordinates of the robot
    int kills; // Number of kills the robot has made
    int lives; // Number of lives the robot has left
    int respawns; // Number of respawns the robot has left
    string name; // Name of the robot
    string targetName; // Name of the target robot
    bool upgraded; // Whether the robot is upgraded
    HealthManager& healthManager; // Reference to the health manager

    // Constructor to initialize the robot
    Robot(int x, int y, string name, HealthManager& hm)
        : x(x), y(y), kills(0), lives(3), respawns(3), name(name), targetName(""), upgraded(false), healthManager(hm) {
        healthManager.registerRobot(name); // Register the robot with the health manager
    }

    // Pure virtual function to perform the robot's action
    virtual void performAction(CustomDynamicArray<CustomDynamicArray<string>>& battlefield, int rows, int cols) = 0;
    // Pure virtual function to get the type of the robot
    virtual string getType() const = 0;

    // Method to increment the number of kills and upgrade if necessary
    void incrementKills() {
        kills++;
        if (kills == 3) {
            upgrade();
        }
    }

    // Method to decrement the number of lives and handle respawns
    void decrementLives() {
        if (lives > 0) {
            lives--;
            if (lives == 0 && respawns > 0) {
                respawns--;
                lives = 3; // Reset lives for respawn
            }
        }
    }

    // Virtual method to upgrade the robot, to be overridden by subclasses
    virtual void upgrade() {}

    // Virtual destructor
    virtual ~Robot() = default;
};

// Class for robots that can move
class MovingRobot : virtual public Robot {
public:
    // Constructor to initialize the moving robot
    MovingRobot(int x, int y, string name, HealthManager& hm) : Robot(x, y, name, hm) {}

    // Pure virtual function to move the robot
    virtual void move(CustomDynamicArray<CustomDynamicArray<string>>& battlefield, int rows, int cols) = 0;
};

// Class for robots that can shoot
class ShootingRobot : virtual public Robot {
public:
    // Constructor to initialize the shooting robot
    ShootingRobot(int x, int y, string name, HealthManager& hm) : Robot(x, y, name, hm) {}

    // Pure virtual function to fire at a target
    virtual void fire(CustomDynamicArray<CustomDynamicArray<string>>& battlefield, int rows, int cols) = 0;
};

// Class for robots that can see
class SeeingRobot : virtual public Robot {
public:
    // Constructor to initialize the seeing robot
    SeeingRobot(int x, int y, string name, HealthManager& hm) : Robot(x, y, name, hm) {}

    // Pure virtual function to look around
    virtual void look(CustomDynamicArray<CustomDynamicArray<string>>& battlefield, int rows, int cols) = 0;
};

// Class for robots that can step on targets
class SteppingRobot : virtual public Robot {
public:
    // Constructor to initialize the stepping robot
    SteppingRobot(int x, int y, string name, HealthManager& hm) : Robot(x, y, name, hm) {}

    // Pure virtual function to step on a target
    virtual void step(CustomDynamicArray<CustomDynamicArray<string>>& battlefield, int rows, int cols) = 0;
};

#endif // ABSTRACTROBOTS_H
