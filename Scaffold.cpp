// Scaffold.cpp

//UID: 105502901
//name: Lisa Wang 

#include "provided.h"
#include <iostream>
using namespace std;

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();

private: 
    int m_columns; 
    int m_levels;
    vector<int> temp_col; 
    vector<int> temp_level; 
    vector<vector<char>> scaffold; 
};


ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels): m_columns(nColumns), m_levels(nLevels)
{
    if (cols() <= 0 || levels() <= 0) { //if not appropriate, then exit
        cerr << "the scaffold range out of bound" << endl;
        exit(0);
    }

    scaffold.resize(levels()); //make a vector named scaffold with levels and cols
    for (int i = 0; i < levels(); i++) {
        scaffold[i].resize(cols());
    }

    for (int i = 0; i < levels(); i++)
        for (int j = 0; j < cols(); j++)
            scaffold[i][j] = ' '; //made all chars empty 
}

int ScaffoldImpl::cols() const
{
    return m_columns;   
}

int ScaffoldImpl::levels() const
{
    return m_levels;  
}


//Return the number of positions in the scaffold not occupied by a checker.
int ScaffoldImpl::numberEmpty() const
{
    int counter = 0; 
    for (int i = 0; i < levels(); i++) {
        for (int j = 0; j < cols(); j++) {
            if (scaffold[i][j] != 'R' && scaffold[i][j] != 'B') { 
                counter++; 
            }
        }
    }
    return counter; 
}

//If there is a red checker at the indicated column and level, return RED; if there's a black checker there, return BLACK; otherwise, return VACANT
int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (scaffold[levels()-level][column-1] == 'R') {
        return RED; 
    }
    if (scaffold[levels()-level][column-1] == 'B') {
        return BLACK; 
    }
    return VACANT; 
}

//need revision
void ScaffoldImpl::display() const
{			// prints out the gameboard
    for (int j = 0; j < levels(); j++)
    {
        for (int i = 0; i < cols(); i++)
        {
            cout << "|" << scaffold[j][i];
        }
        cout << "|" << endl;
    }
    cout << "+";
    for (int i = cols(); i != 0; i--) {
        cout << "-+";
    }
    cout << endl;
}

//If the first parameter is a valid column number with at least one vacant position in that column, 
//and if color is RED or BLACK, drop a checker of the appropriate color into that column and return true. 
//Otherwise, do nothing and return false

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column <= cols() && scaffold[0][column - 1] == ' ') {
        for (int i = levels()-1; i >= 0; i--) {
            if (scaffold[i][column - 1] == ' ' && color == RED) {
                scaffold[i][column - 1] = 'R';
                temp_col.push_back(column - 1);
                temp_level.push_back(i);
                return true;
            }
            if (scaffold[i][column - 1] == ' ' && color == BLACK) {
                scaffold[i][column - 1] = 'B';
                temp_col.push_back(column - 1);
                temp_level.push_back(i);
                return true;
            }
        }
    }
    return false;
}
        //Undo the most recently made move that has not already been undone (i.e., remove the checker in the scaffold that was most recently added)
        // and return the number of the column from which that checker was removed. If there are no checkers in the scaffold, do nothing and return 0.

        //I created two vectors that keep track of the last moves taken


        //More specifically one vector to keep track of the most recent column added toand one for the most recent Level added to

        //Then I set it so that when undoMove is called, the scaffold position corresponding to the last member of the two vectors is set back to - 1, then I popped the two vectors back
int ScaffoldImpl::undoMove()
{
    int holder; 
    if (numberEmpty() == (cols() * levels())) {
        return 0;
    }
    scaffold[temp_level.back()][temp_col.back()] = VACANT;
    temp_level.pop_back();
    holder = temp_col.back(); 
    temp_col.pop_back(); 
    return holder; 
}

        //******************** Scaffold functions *******************************

        //  These functions simply delegate to ScaffoldImpl's functions.
        //  You probably don't want to change any of this code. 

        Scaffold::Scaffold(int nColumns, int nLevels)
        {
            m_impl = new ScaffoldImpl(nColumns, nLevels);
        }

        Scaffold::~Scaffold()
        {
            delete m_impl;
        }

        Scaffold::Scaffold(const Scaffold & other)
        {
            m_impl = new ScaffoldImpl(*other.m_impl);
        }

        Scaffold& Scaffold::operator=(const Scaffold & rhs)
        {
            if (this != &rhs)
            {
                Scaffold temp(rhs);
                swap(m_impl, temp.m_impl);
            }
            return *this;
        }

        int Scaffold::cols() const
        {
            return m_impl->cols();
        }

        int Scaffold::levels() const
        {
            return m_impl->levels();
        }

        int Scaffold::numberEmpty() const
        {
            return m_impl->numberEmpty();
        }

        int Scaffold::checkerAt(int column, int level) const
        {
            return m_impl->checkerAt(column, level);
        }

        void Scaffold::display() const
        {
            m_impl->display();
        }

        bool Scaffold::makeMove(int column, int color)
        {
            return m_impl->makeMove(column, color);
        }

        int Scaffold::undoMove()
        {
            return m_impl->undoMove();
        }
   