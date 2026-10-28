#include "termite.hpp"

//Constructor definition
Termite::Termite(int id, Coord c, int teamId) : coord{c}, idTermite{id}, team{teamId} {
	dir = Direction::N;
}
//

//Getters Definition
int Termite::getId() const {
	return idTermite;
}

Direction Termite::getDir() const{
	return dir;
}

Coord Termite::getCoord() const{
	return coord;
}

int Termite::getSablier() const{
	return sablier;
}

int Termite::getTeam() const{
	return team;
}

bool Termite::etatBrindille() const {
	return porteBrindille;
}
//

//Setters Definition
void Termite::setPos(Coord c) {
	coord = c;
}

void Termite::setDir(Direction d) {
	dir = d;
}

void Termite::decrementeSablier() {
	sablier -= 1;
}
//

//Helper Definitions
void Termite::tourneAleat() {
	if (rand() % 2 == 0) {
		dir = aDroite(dir);
	} else {
		dir = aGauche(dir);
	}
}

void Termite::chargerBrindille() {
	porteBrindille = true;
	sablier = dureeSablier;
}

void Termite::dechargerBrindille() {
	porteBrindille = false;
	sablier = dureeSablier;
}