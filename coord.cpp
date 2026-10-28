//Dependecies
#include "coord.hpp"

//Constructors
Coord::Coord(int l, int g) : lig{l}, col{g} {
	if (l > tailleGrille - 1 || l < 0 || g > tailleGrille - 1 || g < 0) {
		throw invalid_argument("Invalid size");
	}
}

//Getters
int Coord::getLig() {
	return lig;
}

int Coord::getCol() {
	return col;
}
//

//Coord Operators
ostream& operator<<(ostream& out, Coord& c) {
	out << "(" << c.getLig();
	out << "," << c.getCol();
	out << ")" << endl;
	return out;
}

bool operator==(Coord& a, Coord& b) {
    return a.getLig() == b.getLig() && a.getCol() == b.getCol();
}
//

//Direction Operators
ostream& operator<<(ostream& out, Direction d) {
    switch (d) {
        case Direction::N:  out << "N";  break;
        case Direction::NE: out << "NE"; break;
        case Direction::E:  out << "E";  break;
        case Direction::SE: out << "SE"; break;
        case Direction::S:  out << "S";  break;
        case Direction::SW: out << "SW"; break;
        case Direction::W:  out << "W";  break;
        case Direction::NW: out << "NW"; break;
    }
    return out;
}

Direction aDroite(Direction d) {
    switch (d) {
        case Direction::N:  return Direction::NE; break;
        case Direction::NE: return Direction::E; break;
        case Direction::E:  return Direction::SE; break;
        case Direction::SE: return Direction::S; break;
        case Direction::S:  return Direction::SW; break;
        case Direction::SW: return Direction::W; break;
        case Direction::W:  return Direction::NW; break;
        case Direction::NW: return Direction::N; break;
		default : throw invalid_argument("Direction incorrect");
    }
}

Direction aGauche(Direction d) {
    switch (d) {
        case Direction::N:  return Direction::NW; break;
        case Direction::NW: return Direction::W; break;
        case Direction::W:  return Direction::SW; break;
        case Direction::SW: return Direction::S; break;
        case Direction::S:  return Direction::SE; break;
        case Direction::SE: return Direction::E; break;
        case Direction::E:  return Direction::NE; break;
        case Direction::NE: return Direction::N; break;
		default : throw invalid_argument("Direction incorrect");
    }
}
//

//Functions
Coord devantCoord(Coord c, Direction d) {
    int l = c.getLig();
    int cl = c.getCol();

    switch (d) {
        case Direction::N:
            l = l - 1; // Up 1 line
            break;
        case Direction::NE:
            l = l - 1; cl = cl + 1; //Up 1 line, Right 1 Column
            break;
        case Direction::E:
            cl = cl + 1; // Right 1 Column
            break;
        case Direction::SE:
            l = l + 1; cl = cl + 1; // Down 1 Line, Right 1 Column
            break;
        case Direction::S:
            l = l + 1; // Down 1 Line
            break;
        case Direction::SW:
            l = l + 1; cl = cl - 1; // Down 1 Line, Left 1 Column
            break;
        case Direction::W:
            cl = cl - 1; // Left 1 Column
            break;
        case Direction::NW:
            l = l - 1; cl = cl - 1; // Up 1 Line, Left 1 Column
            break;
    }

	//Constructor will determine to throw an exception or not
    return Coord(l, cl);
}



