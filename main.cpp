#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge" && hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	//SmartPlayer sp("Lisa");
	//assert(sp.name() == "Lisa" && !sp.isInteractive());
	Scaffold s(3, 2);
	s.makeMove(1, RED);
	s.makeMove(1, BLACK);
	cout << "=========" << endl;
	int n = hp.chooseMove(s, 3, RED);
	cout << "=========" << endl;
	assert(n == 2 || n == 3);
	n = bp.chooseMove(s, 3, RED);
	assert(n == 2 || n == 3);
	//n = sp.chooseMove(s, 3, RED);
	//assert(n == 2 || n == 3);
}

int main()
{
	doPlayerTests();
	cout << "Passed all tests" << endl;
}