/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file Monster.cpp
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Implementation file for Monster class

#include "Monster.h"

Monster::Monster(std::string name, int screamPowerLevel) {
    m_name = name;
    m_screamPowerLevel = screamPowerLevel;
}

Monster::~Monster() {}

std::string Monster::getName() {
    return m_name;
}

int Monster::getScreamPowerLevel() {
    return m_screamPowerLevel;
}

bool Monster::operator<(const Monster& monster) const { // comparing scream power levels
    return this->m_screamPowerLevel < monster.m_screamPowerLevel;
}

bool Monster::operator>(const Monster& monster) const { // comparing scream power levels
    return this->m_screamPowerLevel > monster.m_screamPowerLevel;
}