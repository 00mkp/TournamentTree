/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file Monster.h
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Header file for Monster class

#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
    public:
        /// @Default constructor for Monster object
        /// @param name std::string representation of the Monster's name
        /// @param screamPowerLevel int representation of Monster's scream power level
        /// NOTE: No unparametrized constructor, as we always know values for Monster's attributes
        Monster(std::string name, int screamPowerLevel);

        /// Default destructor for Monster object 
        ~Monster();

        /// Getter method for Monster's name
        /// @return std::string representation of Monster's name
        std::string getName();

        /// Getter method for Monster's scream power level
        /// @return int representation of Monster's scream power level
        int getScreamPowerLevel();

        /// Operator overload for Monster comparison, where two Monster's scream levels are compared 
        /// @param monster the Monster to be compared with 
        /// @return bool representation of whether Monster is weaker than Monster being compared with 
        /// NOTE: The const keyword is used in conjunection with passing by reference to ensure that the objects are not modified and that copies are not made
        bool operator<(const Monster& monster) const;

        /// Operator overload for Monster comparison, where two Monster's scream levels are compared 
        /// @param monster the Monster to be compared with 
        /// @return bool representation of whether Monster is stronger than Monster being compared with
        /// NOTE: The const keyword is used in conjunection with passing by reference to ensure that the objects are not modified and that copies are not made 
        bool operator>(const Monster& monster) const;
    private:
        /// Private member variable containing std::string representation of Monster's name 
        std::string m_name;

        /// Private member variable containing int representation of Monster's scream power level
        int m_screamPowerLevel;
};

#endif