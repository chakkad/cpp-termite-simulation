#include "grille.hpp" //Already includes coord.hpp
#include "termite.hpp"
#include <iostream>
#include <vector>
#include <ctime> //For random
using namespace std;

//Constants
const float probaTourner = 0.1;
const float densiteBrindille = 0.17;

string getTermiteArrow(Direction d) {
    switch (d) {
        case Direction::N:  return "↑";
        case Direction::NE: return "↗";
        case Direction::E:  return "→";
        case Direction::SE: return "↘";
        case Direction::S:  return "↓";
        case Direction::SW: return "↙";
        case Direction::W:  return "←";
        case Direction::NW: return "↖";
        default:            return "T";
    }
}

void afficheSimulation(const Grille& g, const vector<Termite>& termites) {
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            Coord cur(i, j);

            //NESTS
            if (g.isTeamNest(cur, 0)) {
                cout << "\033[1;31m#\033[0m "; // Bold Red Nest
            } else if (g.isTeamNest(cur, 1)) {
                cout << "\033[1;34m#\033[0m "; // Bold Blue Nest
            }

            //TWIGS
            else if (g.contientBrindille(cur)) {
                int m = g.getMark(cur);
                if (m == 0)      cout << "\033[31m*\033[0m "; // Red Twig
                else if (m == 1) cout << "\033[34m*\033[0m "; // Blue Twig
                else             cout << "* ";               // Neutral Twig
            }

            //TERMITES
            else if (!g.estVide(cur)) {
                int id = g.numeroTermite(cur);
                const Termite& t = termites[id];
                
                //cool ass arrows
                string arrow = getTermiteArrow(t.getDir());

                if (t.getTeam() == 0) {
                    if (t.etatBrindille()) 
                        cout << "\033[1;31mC\033[0m "; // Bold 'C' if carrying
                    else 
                        cout << "\033[31m" << arrow << "\033[0m "; // Red Arrow
                } else {
                    if (t.etatBrindille()) 
                        cout << "\033[1;34mC\033[0m "; // Bold 'C' if carrying
                    else 
                        cout << "\033[34m" << arrow << "\033[0m "; // Blue Arrow
                }
            }

            //Empty case
            else {
                cout << ". ";
            }
        }
        cout << endl; //Next row
    }
}
		
void deplaceAleatoire(Grille& g, vector<Termite>& termites) { //Keep for testing purposes
	for (Termite& t : termites) {
		Coord currentPos = t.getCoord();
	
		if (rand() % 10 == 0) {
			t.tourneAleat();
		}

		try {
			Coord front = devantCoord(t.getCoord(), t.getDir());
			if (!g.estVide(front)) {
				t.tourneAleat();
			} else {
				g.enleveTermite(currentPos);
				g.poseTermite(front, t.getId());
				t.setPos(front);
			}
		}
		catch (const exception& e) {
			t.tourneAleat();
		}
	}
}

void rassemblerBrindille(Grille& g, vector<Termite>& termites) {
	for (Termite& t : termites) {
		if (t.getSablier() > 0) {
			t.decrementeSablier();
		}

		Coord currentPos = t.getCoord();

		if (rand() % 100 < probaTourner * 100) { //1 in 10 chance
			t.tourneAleat();
		}

		try {
			Coord front = devantCoord(t.getCoord(), t.getDir());

			//Case 1 : Branch and Termite not holding anything
			if (g.contientBrindille(front) && t.etatBrindille() == false) {
				if (t.getSablier() == 0 && g.getMark(front) != t.getTeam()) { //Dont take ally's twigs
					t.chargerBrindille();
					g.enleveBrindille(front);
				} else {
					t.tourneAleat();
				}
			//Case 2 : Branch and Termite has branch
			} else if ((g.contientBrindille(front) || g.isTeamNest(front, t.getTeam())) && t.etatBrindille() == true) {
				bool teamNest = g.isTeamNest(front, t.getTeam());
				Coord savedFront = front;
				//Sablier is 0 : found a pile, and is on the same team or neutral
				if (t.getSablier() == 0) {
					bool dropSpotFound = false;
                    for (int i = 0; i < 8 && !dropSpotFound; i++) {
                        t.tourneAleat();
                        try {
                            front = devantCoord(t.getCoord(), t.getDir());
                            if (g.estVide(front)) {
								int fspots = 0;
								//Counting empty neighbor cases
								for (int d = 0; d < 8; d++) {
									try {
										Coord neighbor = devantCoord(t.getCoord(), static_cast<Direction>(d));
				                        if (g.estVide(neighbor)) {
											fspots++;
										}
									} catch (const exception& a) {} //Ignoring, we just want to increment fspots
								}
							if (fspots >= 2) {
								g.poseBrindille(front);
								if (teamNest || g.getMark(savedFront) == t.getTeam()){
									g.setMark(front, t.getTeam());
								}
								t.dechargerBrindille();
								dropSpotFound = true;
								}
							}
                        } catch (const exception& e) { 
							t.tourneAleat();
						}
                    }
				} //Finish of Condition 1
					
				//Sablier not 0 yet
				else {
					t.tourneAleat();
				}
			//Case 3 : There is a Termite
			} else if (!g.estVide(front)) {
				t.tourneAleat();
			//Case 4 : Empty Case
			} else {
				g.enleveTermite(currentPos);
				g.poseTermite(front, t.getId());
				t.setPos(front);
			}
		} catch (const exception& e) {
			t.tourneAleat();
		}
	}
}
	
int main() {
	cout << "Starting" << endl;
	srand(time(NULL)); //Random numbers
	Grille g = Grille();
	cout << "Grid Created" << endl;
	vector<Termite> termites;

	//Nest Placing
	Coord nestA(2,2);
	Coord nestB(10,18);
	g.setNest(nestA, 1);
	g.setNest(nestB, 0);
	//

	//Placing random twigs
	cout << "Placing Twigs" << endl;
	for (int i = 0; i < tailleGrille; i++) {
		for (int j = 0; j < tailleGrille; j++) {
			Coord cur = Coord(i,j);
			if(g.isNest(cur)) {
				continue;
			}
			if (rand() % 100 < densiteBrindille * 100){ //5 in 100 chance
				g.poseBrindille(Coord(i,j));
				g.setMark(cur, -1);
			}
		}
	}
	
	//Placing random termites (20)
	cout << "Placing Termites" << endl;
	int index = 0;
	while (index < 20) {
		Coord randomCoord = Coord(rand() % tailleGrille, rand() % tailleGrille);

		if (g.estVide(randomCoord) && !g.isNest(randomCoord)) {
			//Assigning team
			int teamId;
			if (index < 10) {
				teamId = 0;
			} else {
				teamId = 1;
			}
			
			Termite t = Termite(index, randomCoord, teamId);
			termites.push_back(t);
			g.poseTermite(randomCoord, index);
			index += 1;
		}
	}
	
	char cmd = ' ';
	int nbPasse = 100;
	while (cmd != '.') {
		for (int i = 0; i < nbPasse; i++) {
			rassemblerBrindille(g, termites);
		}

		//DISPLAY
		system("clear"); //To see animation
		afficheSimulation(g, termites);
		cout << "[Enter] to continue || [*] to double speed || [/] to halve" << endl;
		cout << "Speed : " << nbPasse << endl;

		//INPUT
		string input;
		getline(cin, input);

		if (input.empty()) {
			cmd = ' '; //Basically enter
		} else {
			cmd = input[0]; //Read only first char
		}

		if (cmd == '*') {
			nbPasse = nbPasse * 2;
		} else if (cmd == '/') {
			if (nbPasse > 1) {
				nbPasse = nbPasse / 2;
			}
		}
	}
    return 0;
}