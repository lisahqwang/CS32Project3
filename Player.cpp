// Player.cpp
// name: Lisa Wang
// UID: 105502901 

#include "provided.h"
//#include "support.h"
#include <string>
#include <iostream>
using namespace std;

class HumanPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};


/*
A HumanPlayer chooses its move by prompting a person running the program for a move
(reprompting if necessary until the person enters a valid move), and returning that choice.
You may assume that the user will enter an integer when prompted for a column number,
although it might not be within the range of valid column numbers.

the player were to be playing the indicated color and have to make a move given scaffold s, 
with a goal of getting N in a row, the function returns the column the player would choose. If no move is possible, return 0.
*/
int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int columnchosen;
    bool satisfied = false;

    if (s.numberEmpty() <= 0) { //the scaffold must have at least one empty spot
        return 0; 
    }
    while (!satisfied) {
        cout << "Enter column number:" << endl;
        cin >> columnchosen;
        if (columnchosen <= s.cols() && columnchosen > 0 && (N <= s.cols() || N <= s.levels())) 
        {
            satisfied = true; 
        }
    }
    return columnchosen; //input by the user
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int columnchosen;
    if (N > s.cols() && N > s.levels()) {
        cerr << "inappropriate scaffold initial cols and levels"
    }
    else {
        for (int i = 1; i < s.levels(); i++) {
            for (int j = 1; j < s.cols(); j++) {
                if (s.checkerAt(i, j) == VACANT) {
                    columnchosen = j;
                    //cout << columnchosen; 
                    if (columnchosen != s.cols() && columnchosen > 0 ) {
                        return columnchosen;
                    }
                }
            }
        }
    }
}


/*
//implement now!
int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{

}

*/

    
    
    /*
useful functions from Scaffold 
 int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();

*/










//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code. 

HumanPlayer::HumanPlayer(string nm)
    : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
    : Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
    : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
