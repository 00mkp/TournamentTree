/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file RunScareGame.h
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Header file for RunScareGame class 

#ifndef RUN_SCARE_GAME_H
#define RUN_SCARE_GAME_H

#include "TournamentTree.h"
#include "Monster.h"

#include <string>

class RunScareGame{
    public:
        /// Default constructor for RunScareGame object 
        /// @param fileName std::string representation of input file 
        RunScareGame(std::string& fileName);

        /// Default destrcutor for RunScareGame object 
        ~RunScareGame();

        /// Method to run the tournament 
        /// @param mode std::string representation of the mode to run the tournament in (single or double elimination)
        void runTournament(std::string mode);
    private:
        /// Private member variable containing a vector of pointers to TournamentNode<Monster> representing the contestants of the tournament 
        std::vector<TournamentNode<Monster>*> gameVector;

        /// Private helper function to process the the file input and populate the vector of contestants (gameVector)
        /// @param fileName std::string representation of the input file 
        void processFile(std::string& fileName);
};

#endif 