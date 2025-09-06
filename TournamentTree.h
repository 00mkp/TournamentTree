/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file TournamentTree.h
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Header and implementation file for TournamentTree class (templated)

#ifndef TOURNAMENT_TREE_H
#define TOURNAMENT_TREE_H

#include "TournamentNode.h"

#include <vector>
#include <iostream>
#include <fstream>

template <typename T>
class TournamentTree {
    public:
        /// Default constructor for TournamentTree class 
        /// @param vec vector of pointers to TournamentNodes<T> representing what group of contestants to build the tree from
        /// NOTE: The const keyword is used in conjunection with passing by reference to ensure that the vector is not modified and that copies are not made
        TournamentTree(const std::vector<TournamentNode<T>*>& vec);

        /// Default destructor for TournamentTree class 
        ~TournamentTree();

        /// Method to run a Single Elimination tournament with given contestants
        void singleElimTournament();

        /// Method to run a Double Elimination Tournament 
        void doubleElimTournament();

        /// Method that saves the constructed tree as a .dot file 
        void saveTreeAsDot();
    private:
        /// Private member variable containing a pointer to the root node of the tournament, or the winner of the whole tournament
        TournamentNode<T>* m_root;

        /// Private member variable containing the vector of contestants
        std::vector<TournamentNode<T>*> m_vec;

        /// Private member variable containing the vector of losers from the first round (only used in double elimination tournaments)
        std::vector<TournamentNode<T>*> vecLosers;

        /// Recursive private helper method to build a TournamentTree from the given vector 
        /// @param vec vector from which to build the TournamentTree
        /// @return a pointer to a TournamenNode representing the winner of the tournament 
        /// NOTE: The const keyword is used in conjunection with passing by reference to ensure that the vector is not modified and that copies are not made
        TournamentNode<T>* buildTree(const std::vector<TournamentNode<T>*>& vec);

        /// Recursive helper method for saveTreeAsDot
        /// @param node pointer for which node to start building the .dot file from
        /// @param file file object to write ouput to 
        /// @param nodeID int representation of the starter nodes' ID 
        void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID);
};

template <typename T>
TournamentTree<T>::TournamentTree(const std::vector<TournamentNode<T>*>& vec) {
    m_root = NULL; // no root until tree built
    m_vec = vec; // set to passed vector 
    std::vector<TournamentNode<T>*> vecLosers; // initialize but leave empty as populated later 
}

template <typename T>
TournamentTree<T>::~TournamentTree() {
    if (m_root != NULL) {
        delete m_root; // deallocate memory 
    }

    delete vecLosers; // deallocate memory 
    delete m_vec; // deallocate memory 
}

template <typename T>
void TournamentTree<T>::saveTreeAsDot() {
    std::ofstream file("tree.dot"); // hardcoded file 
    if (!file.is_open()) {
        std::cerr << "Failed to open file for DOT output: tree.dot";
        return;
    }

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(m_root, file, nodeID);
    file << "}\n";
    file.close();
}

template <typename T>
void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) {
    if (node == NULL) return;

    int currentID = nodeID++;
    file << "    node" << currentID << " [label=\"" << node->getWinner()->getName()
         << " (Power: " << node->getWinner()->getScreamPowerLevel() << ")\"];\n";

    if (node->getLeft()) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->getLeft(), file, nodeID);
        file << "    node" << currentID << " -> node" << leftID << ";\n";
    }

    if (node->getRight()) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->getRight(), file, nodeID);
        file << "    node" << currentID << " -> node" << rightID << ";\n";
    }
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::buildTree(const std::vector<TournamentNode<T>*>& vec) {
    if (vec.size() == 1) { // a winner has been found 
        return vec[0];
    }

    std::vector<TournamentNode<T>*> vecInternal; // initialize a vector to hold the next round of contestants
    TournamentNode<T>* nextNode; // initialize next node to be added 

    for (int i = 0; i < vec.size(); i += 2) {
        if ((i + 1) == vec.size()) { // if odd number of contestants dont fight anyone, just add node to next level, will always be last node in next round 
            vecInternal.push_back(new TournamentNode<T>(vec[i]->getWinner()));

            break;
        }
        
        nextNode = new TournamentNode<T>(vec[i], vec[i + 1]); // create a new node and automatically decide the winner 
        vecInternal.push_back(nextNode); // add that node to the next level or round 

        if (nextNode->getWinner()->getName() == vec[i]->getWinner()->getName()) { // add whichever contestant didn't win to the loser vector (vecLosers)
            vecLosers.push_back(new TournamentNode<T>(vec[i + 1]->getWinner()));
        } else {
            vecLosers.push_back(new TournamentNode<T>(vec[i]->getWinner()));
        }
    }

    return buildTree(vecInternal); // recrusive call to build the next level above the one we just made 
}

template <typename T>
void TournamentTree<T>::singleElimTournament() {
    m_root = buildTree(m_vec); // single elimination only has one sided tree, losers not taken into account 
}

template <typename T>
void TournamentTree<T>::doubleElimTournament() {
    TournamentNode<T>* winnersWinner = buildTree(m_vec); // find the winner of the winners' bracket 

    std::vector<TournamentNode<T>*> clonedLosers; // clone losers to ensure that we don't take new losers from the losers of the loser tree
    for (int i = 0; i < vecLosers.size(); ++i) { // adding TournamentNodes to clone vector 
        clonedLosers.push_back(new TournamentNode<T>(vecLosers[i]->getWinner()));
    }

    TournamentNode<T>* losersWinner = buildTree(clonedLosers); // find losers' winner 

    m_root = new TournamentNode<T>(winnersWinner, losersWinner); // determine who actually wins between the winner of the losers' and winners' brackets 
}

#endif