/*******
Program:HealthManager.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef HEALTHMANAGER_H
#define HEALTHMANAGER_H

#include <iostream> // For input and output
#include <fstream> // For file handling
#include <unordered_map> // For using unordered_map to store health and scores
#include <vector> // For using vector to pass robot names
#include <string> // For using string to handle robot names

// HealthManager class to manage the health and scores of robots
class HealthManager {
private:
    // Unordered map to store the health of each robot by their name
    std::unordered_map<std::string, int> health;
    // Unordered map to store the scores of each robot by their name
    std::unordered_map<std::string, int> scores;

public:
    // Constructor that initializes the health and scores of each robot to 3 and 0 respectively
    HealthManager(const std::vector<std::string>& robotNames) {
        for (const auto& name : robotNames) {
            health[name] = 3;  // Initialize each robot with 3 lives
            scores[name] = 0;  // Initialize each robot with 0 points
        }
    }

    // Copy Constructor
    HealthManager(const HealthManager& other)
        : health(other.health), scores(other.scores) {}


    // Function to register a new robot with 3 lives and 0 points
    void registerRobot(const std::string& name) {
        health[name] = 3;
        scores[name] = 0;
    }

    // Function to decrease the health of a robot by 1
    void decreaseHealth(const std::string& name) {
        if (health.find(name) != health.end() && health[name] > 0) {
            health[name]--;
        }
    }

    // Function to increase the score of a robot by a given number of points
    void increaseScore(const std::string& name, int points) {
        if (scores.find(name) != scores.end()) {
            scores[name] += points;
        }
    }

    // Function to get the current health of a robot
    int getHealth(const std::string& name) const {
        auto it = health.find(name);
        return (it != health.end()) ? it->second : 0;
    }

    // Function to get the current score of a robot
    int getScore(const std::string& name) const {
        auto it = scores.find(name);
        return (it != scores.end()) ? it->second : 0;
    }

    // Function to print the health of all robots to the console
    void printHealth() const {
        for (const auto& entry : health) {
            std::cout << entry.first << " : --- (" << entry.second << " lives left)\n";
        }
    }

    // Function to print the scores of all robots to the console
    void printScores() const {
        for (const auto& entry : scores) {
            std::cout << entry.first << ": " << entry.second << " points\n";
        }
    }

    // Function to log the health of all robots to a file
    void logHealth(std::ofstream& logFile) const {
        for (const auto& entry : health) {
            logFile << entry.first << " : --- (" << entry.second << " lives left)\n";
        }
    }

    // Function to log the scores of all robots to a file
    void logScores(std::ofstream& logFile) const {
        for (const auto& entry : scores) {
            logFile << entry.first << ": " << entry.second << " points\n";
        }
    }

    // Function to get the name of the robot with the highest score
    std::string getWinner() const {
        std::string winner;
        int maxScore = 0;
        for (const auto& entry : scores) {
            if (entry.second > maxScore) {
                maxScore = entry.second;
                winner = entry.first;
            }
        }
        return winner;
    }
};

#endif // HEALTHMANAGER_H

