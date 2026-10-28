#include "grille.hpp"

//Case Constructors
Case::Case() : brindille{false}, termite{-1}, mark{-1}, nestId{-1} {}
//

//Grille Constructors
Grille::Grille() {
	for (int i = 0; i < tailleGrille; i++) {
		vector<Case> ligne;
		for (int j = 0; j < tailleGrille; j++) {
			Case c = Case(); //Produces empty case
			ligne.push_back(c);
		}
		tableau.push_back(ligne);
	}
}
//		

//Methods
void Grille::poseBrindille(Coord c){
	int line = c.getLig();
	int col = c.getCol();
	if (tableau[line][col].brindille == true || tableau[line][col].termite != -1) {
		throw runtime_error("Case Occupied");
	} else {
		tableau[line][col].brindille = true;
	}
}

void Grille::enleveBrindille(Coord c) {
	int line = c.getLig();
	int col = c.getCol();
	if (tableau[line][col].brindille == false) {
		throw runtime_error("No Twig in Case");
	}
	tableau[line][col].brindille = false;
	tableau[line][col].mark = -1; //Turn back to neutral
}

bool Grille::contientBrindille(Coord c) const {
	int line = c.getLig();
	int col = c.getCol();
	if (tableau[line][col].brindille == false) {
		return false;
	}
	return true;
}

void Grille::poseTermite(Coord c, int idT) {
	int line = c.getLig();
	int col = c.getCol();
	if (tableau[line][col].brindille == false && tableau[line][col].termite == -1) {
		tableau[line][col].termite = idT;
	} else { 
		throw runtime_error("Placement Not Possible");
	}
}

void Grille::enleveTermite(Coord c) {
	int line = c.getLig();
	int col = c.getCol();
	if (tableau[line][col].brindille == false && tableau[line][col].termite != -1) {
		tableau[line][col].termite = -1;
	} else {
		throw runtime_error("Displacement Not Possible");
	}
}

int Grille::numeroTermite(Coord c) const {
    int line = c.getLig();
    int col = c.getCol();
    if (tableau[line][col].termite == -1) {
        throw std::runtime_error("No Termite At Coordinate");
    }

    return tableau[line][col].termite;
}

bool Grille::estVide(Coord c) const {
	int line = c.getLig();
    int col = c.getCol();
	if (tableau[line][col].brindille == false && tableau[line][col].termite == -1 && tableau[line][col].nestId == -1){
		return true;
	}
	return false;
}

bool Grille::isTeamNest(Coord c, int teamId) const {
	int lig = c.getLig();
	int col = c.getCol();
	if (tableau[lig][col].nestId == teamId) {
		return true;
	}
	return false;
}

bool Grille::isNest(Coord c) const {
	if (tableau[c.getLig()][c.getCol()].nestId != -1) { //Its a nest
		return true;
	}
	return false;
}
// 

//Operators
ostream& operator<<(ostream& out, Grille g){
	for(int i = 0; i < tailleGrille; i++) { //Rows
		for (int j = 0; j < tailleGrille; j++) { //Columns
			Coord cur = Coord(i,j);
			if (g.estVide(cur)) {
				out << ".";
			} 
			else if (g.contientBrindille(cur)) {
				out << "*";
			} else {
				out << "T";
			}
		}
		out << endl;
	}
	return out;
}
//

//Getters and Setters
int Grille::getMark(Coord c) const {
	int lig = c.getLig();
	int col = c.getCol();
	return tableau[lig][col].mark;
}

void Grille::setNest(Coord c, int teamId) {
	int lig = c.getLig();
	int col = c.getCol();
	tableau[lig][col].nestId = teamId;
}

void Grille::setMark(Coord c, int teamId) {
	int lig = c.getLig();
	int col = c.getCol();
	tableau[lig][col].mark = teamId;
}
	
		