#include <iostream>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "grille.hpp" //Already includes coord.hpp
#include "doctest.h"

TEST_CASE("Constructors") {
	Coord a = Coord(9, 7);
	CHECK(a.getLig() == 9);
	CHECK(a.getCol() == 7);
	CHECK_FALSE(a.getLig() == 12);
}

TEST_CASE("Similarity") {
	Coord a = Coord(2, 7);
	Coord b = Coord(3, 4);
	Coord c = Coord(3, 4);
	CHECK((c == b));
	CHECK((b == c));
	CHECK_FALSE((a == c));
	CHECK_FALSE((b == a));
}

TEST_CASE("aDroite") {
    CHECK(aDroite(Direction::N) == Direction::NE);
    CHECK(aDroite(Direction::NE) == Direction::E);
    CHECK(aDroite(Direction::E) == Direction::SE);
    CHECK(aDroite(Direction::SE) == Direction::S);
    CHECK(aDroite(Direction::S) == Direction::SW);
    CHECK(aDroite(Direction::SW) == Direction::W);
    CHECK(aDroite(Direction::W) == Direction::NW);
    CHECK(aDroite(Direction::NW) == Direction::N); 

    //Complete tour test
    Direction d = Direction::N;
    for (int i = 0; i < 8; i++) {
        d = aDroite(d);
    }
    CHECK(d == Direction::N);
}


TEST_CASE("aGauche") {
    CHECK(aGauche(Direction::N) == Direction::NW);
    CHECK(aGauche(Direction::NW) == Direction::W);
    CHECK(aGauche(Direction::W) == Direction::SW);
    CHECK(aGauche(Direction::SW) == Direction::S);
    CHECK(aGauche(Direction::S) == Direction::SE);
    CHECK(aGauche(Direction::SE) == Direction::E);
    CHECK(aGauche(Direction::E) == Direction::NE);
    CHECK(aGauche(Direction::NE) == Direction::N);

    //Complete tour test
    Direction d = Direction::S;
    for (int i = 0; i < 8; i++) {
        d = aGauche(d);
    }
    CHECK(d == Direction::S);
}

TEST_CASE("devantCoord") {
    Coord center(10, 10);

    SUBCASE("Regular Movements") {
        CHECK(devantCoord(center, Direction::N).getLig() == 9);
        CHECK(devantCoord(center, Direction::S).getLig() == 11);
        CHECK(devantCoord(center, Direction::E).getCol() == 11);
        CHECK(devantCoord(center, Direction::W).getCol() == 9);
    }

    SUBCASE("Boundaries") {
        Coord topEdge(0, 5);
        CHECK_THROWS_AS(devantCoord(topEdge, Direction::N), std::invalid_argument);
        CHECK_THROWS_AS(devantCoord(topEdge, Direction::NW), std::invalid_argument);

        Coord bottomEdge(19, 5);
        CHECK_THROWS_AS(devantCoord(bottomEdge, Direction::S), std::invalid_argument);

        Coord corner(0, 0);
        CHECK_THROWS_AS(devantCoord(corner, Direction::W), std::invalid_argument);
    }

	SUBCASE("Original Coordinate") {
        Coord start(5, 5);
        Direction dir = Direction::N;
        Coord step1 = devantCoord(start, dir);
        
        for(int i = 0; i < 4; i++) {
            dir = aDroite(dir);
        }
        
        CHECK(dir == Direction::S);
        Coord finalPos = devantCoord(step1, dir);

        //Verification back to starting point
        CHECK(finalPos.getLig() == start.getLig());
        CHECK(finalPos.getCol() == start.getCol());
    }
	
}

TEST_CASE("estVide") {
    Grille g = Grille();
    Coord c(5, 5);
    CHECK(g.estVide(c) == true);
}

TEST_CASE("poseBrindille and contientBrindille") {
    Grille g = Grille();
    Coord c(5, 5);

    g.poseBrindille(c);
    CHECK(g.contientBrindille(c) == true);
    CHECK(g.estVide(c) == false);

    CHECK_THROWS_AS(g.poseBrindille(c), runtime_error);
}

TEST_CASE("enleveBrindille") {
    Grille g = Grille();
    Coord c(5, 5);

    g.poseBrindille(c);
    g.enleveBrindille(c);
    
    CHECK(g.contientBrindille(c) == false);
    CHECK(g.estVide(c) == true);

    CHECK_THROWS_AS(g.enleveBrindille(c), runtime_error);
}

TEST_CASE("poseTermite and numeroTermite") {
    Grille g = Grille();
    Coord c(5, 5);
    int id = 12;

    g.poseTermite(c, id);
    CHECK(g.numeroTermite(c) == id);
    CHECK(g.estVide(c) == false);

    CHECK_THROWS_AS(g.poseTermite(c, 99), runtime_error);
}

TEST_CASE("enleveTermite") {
    Grille g = Grille();
    Coord c(5, 5);

    g.poseTermite(c, 7);
    g.enleveTermite(c);

    CHECK(g.estVide(c) == true);
    CHECK_THROWS_AS(g.numeroTermite(c), std::runtime_error);
    CHECK_THROWS_AS(g.enleveTermite(c), std::runtime_error);
}


int main(int argc, const char **argv) {
    doctest::Context context(argc, argv);
    int test_result = context.run();
    if (context.shouldExit()) return test_result;


	//Direction display test
	cout << "Direction Display" << endl;
	cout << Direction::E << endl;
	cout << Direction::NE << endl;
	cout << Direction::SE << endl;
	cout << "-----------------" << endl;
	//

	
    return 0;
}