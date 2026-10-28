#ifndef GRILLE_HPP
#define GRILLE_HPP

using namespace std;
#include <iostream>
#include <vector>
#include <random>
//Dependecies
#include "coord.hpp" //For tailleGrille

struct Case {
	bool brindille;
	int termite;
	int mark; //-1 for neutral
	int nestId;//-1 for neutral

	//Constructors
	Case();
};

class Grille {
	private :
		vector<vector<Case>> tableau;
	public :
		//Constructors
		Grille(); //Default Constructor makes a tailleGrille x tailleGrille grid
		// 

		//Methods
		void poseBrindille(Coord c);
		void enleveBrindille(Coord c);
		bool contientBrindille(Coord c) const;
		void poseTermite(Coord c, int idT);
		void enleveTermite(Coord c);
		int numeroTermite(Coord c) const;
		bool estVide(Coord c) const;
		bool isTeamNest(Coord c, int teamId) const;
		bool isNest(Coord c) const;
		//

		//Getters and Setters
		int getMark(Coord c) const;
		void setMark(Coord c, int teamId);
		void setNest(Coord c, int teamId);
		//
};

//Grille Operators
ostream& operator<<(ostream& out, Grille g);
//
			
#endif