//support.cpp

int numberEmpty() const
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

int checkerAt(int column, int level) const
{
    if (scaffold[levels() - level][column - 1] == 'R') {
        return RED;
    }
    if (scaffold[levels() - level][column - 1] == 'B') {
        return BLACK;
    }
    return VACANT;
}


void display() const
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


bool makeMove(int column, int color)
{
    if (column <= cols() && scaffold[0][column - 1] == ' ') {
        for (int i = levels() - 1; i >= 0; i--) {
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
