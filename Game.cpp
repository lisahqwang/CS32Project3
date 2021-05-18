// Game.cpp
//name: Lisa Wang
//UID: 105502901
#include "provided.h"
#include "support.h"
#include <iostream>
#include <vector>
using namespace std; 

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
  //  ~GameImpl(); 
    bool completed(int& winner) const;
    bool takeTurn();
    void play(); //display 
    int check_win(int a, int b, int N, char player) const ; //helper function for completed 
    int checkerAt(int c, int r) const;
    int numEmpty() const; 
    vector<vector<char>> getS() const; 
private:
    //vector<vector<char>> scaffold1;
    Scaffold s; 
    int m_cols; 
    int m_levels; 
    int goalN; 
    Player* m_red;
    Player* m_black; 
    int winner; //variable
    int lastMove; //the column last choosen 
    int whose_turn; //red or black's turn

    bool red_turn; 
    bool black_turn; 
};


/*
Construct a Game to be played with the indicated players
on a scaffold of the indicated size. The red player always moves first. 
The goal of the game is for a player to get N of their checkers in a row.
*/

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black): m_cols(nColumns), m_levels(nLevels), goalN(N), m_red(red), m_black(black)
{  
    //if (m_cols <= 0 || m_levels <= 0) { //if not appropriate, then exit
    //    cerr << "the scaffold range out of bound" << endl;
    //    exit(0);
    //}

    //scaffold1.resize(m_levels); //make a vector named scaffold with levels and cols
    //for (int i = 0; i < m_levels; i++) {
    //    scaffold1[i].resize(m_cols);
    //}

    //for (int i = 0; i < m_levels; i++)
    //    for (int j = 0; j < m_cols; j++)
    //        scaffold1[i][j] = ' '; //made all chars empty 
    
}

//vector<vector<char>> GameImpl::getS() const {
//}

/*
If the game isn't over (i.e., more moves are possible), 
return false and do not change winner. Otherwise, 
set winner to RED, BLACK, or TIE_GAME, 
reflecting the outcome of the game, and return true.
*/
bool GameImpl::completed(int& winner) const
{
    /*
    int lastcols; 
    int lastlevels; 
    lastcols = scaffold1->temp_col.back();
    lastlevels = scaffold1->temp_level.back();
    bool winnerIs = check(*scaffold1, lastcols, lastlevels, goalN); 
    winner = scaffold1[temp_col.back()][temp_level.back()]; 
    */
 
    int i = check_win( m_cols, m_levels, goalN, 'B'); 
    if (i == 1) {
        return true;
    }
    else if (i == 0) {
        return false;
    }
    //count how many times each has moved, if N > countedtimes, then false 
//store the last move made in GameImpl class as a member and examine only every row/column/diagonal that goes through wherever the last move is 

    if (numEmpty() == 0) {
        return true; 
    }
    //not finished, what is outcome?
    return false; 
}


int GameImpl::check_win(int m_l, int m_c, int N, char player) const { //int check_win(Scaffold& s, int a, int b, int N, char player)
    int is_win = 0;
    for (int l = 0; l < m_l; l++) {

        for (int k = 0; k < m_c; k++) {

            if (l + N - 1 <= m_l) {
                int is_line = 0;
                for (int t = 0; t < N; t++) {
                    if (s[l][k+t] == player) {
                        is_line++;
                    }

                }
                if (is_line == N) {
                    is_win = 1;
                    return is_win;
                }


            }
            if (k + N - 1 <= m_c) {
                int is_column = 0;
                for (int t = 0; t < N; t++) {
                    if (s[l][k + t] == player) {
                        is_column++;
                    }
                }
                if (is_column == N) {
                    is_win = 1;
                    return is_win;

                }
            }


            if (l + N - 1 <= m_l && k + N - 1 <= m_c) {
                int is_h = 0;
                for (int t = 0; t < N; t++)
                    if (s[l + t][k + t] == player) {
                        is_h++;

                    }
                if (is_h == N) {
                    is_win = 1;
                    return is_win;

                }
            }




            if (l - N + 1 <= m_l && k - N + 1 <= m_c) {
                int is_v = 0;
                for (int t = 0; t < N; t++) {
                    //if(m_v[l-t][k] == player && m_v[l-1][k-1] == player && m_v[l-2][k-2] == player ){
                    if (s[l - t][k - t] == player) {
                        is_v++;
                    }
                    if (is_v == N)
                    {
                        is_win = 1;
                        return is_win;
                    }
                }//end for
            }


        } //end for m_c

    }//end for m_l
    return is_win;
}




int GameImpl::numEmpty() const {
    int counter = 0; 
    for (int i = 0; i < m_levels; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (s[i][j] == VACANT) {
                counter++; 
            }
        }
   }
    return counter; 
}



/*
bool GameImpl::check(const Scaffold& s, int a, int b, int N) {
    int vertical = 1;//(|)
    int horizontal = 1;//(-)
    int diagonal1 = 1;//(\)
    int diagonal2 = 1;//(/)
    
    char player = s[a][b];

    int i;//vertical
    int ii;//horizontal
    //check for vertical(|)
    for (i = a + 1; s[i][b] == player && i <= m_cols; i++, vertical++);//Check down
    for (i = a - 1; s[i][b] == player && i >= 0; i--, vertical++);//Check up
    if (vertical >= N)return true;
    //check for horizontal(-)
    for (ii = b - 1; s[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
    for (ii = b + 1; s[a][ii] == player && ii <= m_levels; ii++, horizontal++);//Check right
    if (horizontal >= N) return true;
    //check for diagonal 1 (\)
    for (i = a - 1, ii = b - 1; s[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
    for (i = a + 1, ii = b + 1; s[i][ii] == player && i <= m_cols && ii <= m_levels; diagonal1++, i++, ii++);//down and right
    if (diagonal1 >= N) return true;
    //check for diagonal 2(/)
    for (i = a - 1, ii = b + 1; s[i][ii] == player && i >= 0 && ii <= m_levels; diagonal2++, i--, ii++);//up and right
    for (i = a + 1, ii = b - 1; s[i][ii] == player && i <= m_cols && ii >= 0; diagonal2++, i++, ii--);//up and left
    if (diagonal2 >= N) return true;
    return false;
}
*/


/*
// draft for check 
bool check(Scaffold& s, char player, int N)
{
    int flag = 0;
    for (int i = 0; i < m_levels; i++) {
        if (i + N > m_cols) return false;
        for (int j = 0; j < m_cols; j++) {
            if (j + N > m_levels) return false;
            if (s[i][j] == player) {
                if (flag != 1) {
                    for (int m = 1; m < N; m++) {
                        if (s[i][j + m]) != player) {
        flag = 0;
        break;
    }
    if (flag != 1) {
           
             }
                    }

                }
                
                if(flag == 1)
                return true;

            }

        }
    }
}
*/

/*
Otherwise, make a move for the player whose turn it is
(so that it becomes the other player's turn) and return true.
*/

bool GameImpl::takeTurn()
{
    if (completed(winner)) { //If the game is over, return false.
        return false;
    }


    if (whose_turn % 2 == 0) {
        makeMove(m_red->chooseMove(s, goalN, RED), RED ); 
        red_turn = true;
        black_turn = false; 
    }
    else {
        makeMove(m_black->chooseMove(s, goalN, BLACK), BLACK);
        black_turn = true; 
        red_turn = false;
    }
    //if not red, then black's turn 
    //if not black, then red's turn 

    return true;
}

/*
Play the game. Display the progress of the game in a manner of your choosing, 
provided that someone looking at the screen can follow what's happening. 
If neither player is interactive, then to keep the display from quickly scrolling through the whole game, 
it would be reasonable periodically to prompt the viewer to press 
ENTER to continue and not proceed until ENTER is pressed. 
(The ignore member function for input streams is useful here.) Announce the winner at the end of the game.
*/

void GameImpl::play()
{
    display(); 
    cout << "press Enter to continue" << endl; 
    cin.ignore(100000, '\n');
   // if (!completed(winner)) {
   //     if (takeTurn()) {
   //         m_red->makeMove(m_red->chooseMove()); 
   //     }
   //     if (takeTurn()) {
   //         m_black->makeMove(m_red->chooseMove()); 
   //     }
   // 
    if (completed(winner)) {
        cerr << "the winner is: " << winner << endl;
    }
}


/*
In the Game's scaffold, if there is a red checker at the indicated column and level,
return RED; if there's a black checker there, return BLACK; otherwise, return VACANT. 
This function exists so that we and you can more easily test your program;
a real client would never use it.
*/


int GameImpl::checkerAt(int c, int r) const
{
    if (s[c][r] == 'R') {
        return RED;
    }
    if (s[c][r] == 'B') {
        return BLACK;
    }
    return VACANT;
}


//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code. 

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
