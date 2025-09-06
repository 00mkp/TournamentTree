/// Maksim Popov
/// 2417735
/// @author mpopov@chapman.edu
/// @file TournamentNode.h
/// CPSC350 - 01: Data Structures and Algorithms
/// A5 - Scare Games

/// @brief Header and implementation file for TournamentNode class (templated)

#ifndef TOURNAMENT_NODE_H
#define TOURNAMENT_NODE_H

#include <cstdlib> // for usage of NULL 

template <typename T>
class TournamentNode {
    public:
        /// Default constructor for TournamentNode class 
        /// @param winner pointer to winner of that match
        /// NOTE: This is considered a default constructor as the first level of the TournamentTree will contain nodes with only winners and no matches before then. This is used in any instance where 
        /// the node does not have any preceding matches
        TournamentNode(T* winner);

        /// Overloaded constructor for TournamentNode class
        /// @param left pointer to the left previous match 
        /// @param right pointer to the right previous match 
        /// NOTE: This constructor is used for new nodes as the game goes on. It automatically determines a winner based on whichever matches' (left or right) winner is considered greater
        TournamentNode(TournamentNode<T>* left, TournamentNode<T>* right);

        /// Default destructor for TournamentNode class 
        ~TournamentNode();

        /// Getter method for the winner of the current node 
        /// @return type T*, a pointer to the object that won the current match being looked at 
        T* getWinner();

        /// Getter method for the left previous match 
        /// @return type TournamenNode<T>* representing the left previous match 
        TournamentNode<T>* getLeft();

        /// Getter method for the right previous match 
        /// @return type TournamentNode<T>* representing the right previous match 
        TournamentNode<T>* getRight();
    private:
        /// Private member variable containing a pointer to the winner of the match 
        T* m_winner;

        /// Private member variable containing a recursive reference to the left previous match node
        TournamentNode<T>* m_left;

        /// Private member variable containing a recursive reference to the right previous match node
        TournamentNode<T>* m_right;

        /// Private helper function to decide the winner of the current match when creating a new TournamentNode<T>* from its' two previous matches 
        void decideWinner();
};

template <typename T>
TournamentNode<T>::TournamentNode(T* winner) {
    m_left = NULL; // no previous matches
    m_right = NULL;
    m_winner = winner;
}

template <typename T>
TournamentNode<T>::TournamentNode(TournamentNode* left, TournamentNode* right) {
    m_left = left; // previous matches
    m_right = right;
    decideWinner(); // sets m_winner 
}

template <typename T>
TournamentNode<T>::~TournamentNode() {
    m_left = NULL;
    m_right = NULL;
    m_winner = NULL;
}

template <typename T>
void TournamentNode<T>::decideWinner() {
    T* leftWinner = m_left->getWinner();
    T* rightWinner = m_right->getWinner();
    
    if (*leftWinner>*rightWinner) { // have to dereference to utilize overloaded operator in Monster and compare scream power levels instead of pointers
        m_winner = leftWinner;
    } else if (*leftWinner < *rightWinner){ // ""
        m_winner = rightWinner;
    } else { // case where two monsters in a tournament have equal scream power levels
        m_winner = leftWinner;
    }
}

template <typename T>
T* TournamentNode<T>::getWinner() {
    return m_winner;
}

template <typename T> 
TournamentNode<T>* TournamentNode<T>::getLeft() {
    return m_left;
}

template <typename T>
TournamentNode<T>* TournamentNode<T>::getRight() {
    return m_right;
}

#endif