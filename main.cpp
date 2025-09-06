/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file main.cpp
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Implementation file for all logic 

#include "RunScareGame.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Invalid number of arguments, 3 needed (executable, input, mode)" << std::endl; // make sure we have required arguments

        return -1;
    }
    
    std::string inFile = argv[1]; // set input file
    std::string mode = argv[2]; // set mode 

    RunScareGame* runGame = new RunScareGame(inFile); // create RunScareGame and populate contestant vector 

    runGame->runTournament(mode); // runTournament with passed mode from command line 

    return 0;
}