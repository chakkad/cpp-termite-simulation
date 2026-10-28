#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>
using namespace std;

const int tailleGrille = 20;

class Coord {
	private :
		int lig;
		int col;
	public :
		//Constructors
		Coord(int l, int g);
		//

		//Getters
		int getLig();
		int getCol();
		//
};

enum class Direction { 
	N, NW, W, SW, S, SE, E, NE
};

//Coord Operators
ostream& operator<<(ostream& out, Coord& c);
bool operator==(Coord& a, Coord& b);
//

//Direction Operators
ostream& operator<<(ostream& out, Direction d);
Direction aDroite(Direction d);
Direction aGauche(Direction d);
//

//Functions
Coord devantCoord(Coord c, Direction d);
//

#endif