#ifndef TERMITE_HPP
#define TERMITE_HPP

#include <iostream>
using namespace std;
//Dependencies (Coord and Dir)
#include "coord.hpp"
//Constants
const int dureeSablier = 6;

class Termite {
	private :
		Coord coord;
		Direction dir;
		int idTermite;
		bool porteBrindille;
		int sablier;
		int team;
	public :
		//Constructors
		Termite(int id, Coord c, int teamId);
		//
		
		//Getters
		int getId() const;
		Direction getDir() const;
		Coord getCoord() const;
		int getSablier() const;
		bool etatBrindille() const;
		int getTeam() const;
		//
		
		//Setters
		void setPos(Coord c);
		void setDir(Direction d);
		void decrementeSablier();
		//

		//Helpers
		void tourneAleat();
		void chargerBrindille();
		void dechargerBrindille();
		//
};

#endif		