/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file RunScareGame.cpp
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Implementation file for RunScareGame class

#include "RunScareGame.h"
#include "TournamentNode.h"

#include <iostream>
#include <fstream>
#include <sstream>

RunScareGame::RunScareGame(std::string& fileName) {
    std::vector<TournamentNode<Monster>*> gameVector; // initialize vector 
    processFile(fileName); // process file to assign vector 
}

RunScareGame::~RunScareGame() {}

void RunScareGame::processFile(std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while(std::getline(ss, token, ',')) { // splitting on commas 
            tokens.push_back(token); // add to token vector 
        }

        gameVector.push_back(new TournamentNode<Monster>(new Monster(tokens[0], std::stoi(tokens[1])))); // create first round of tournament using default TournamentNode constructor 
    }

    file.close();
}

void RunScareGame::runTournament(std::string mode) {
    TournamentTree<Monster>* tree = new TournamentTree<Monster>(gameVector); // instantiate the TournamentTree from the gameVector 
    
    if (mode == "single") {
        tree->singleElimTournament();
    } else if (mode =="double") {
        tree->doubleElimTournament();
    }

    tree->saveTreeAsDot(); 
}