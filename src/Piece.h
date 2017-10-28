#ifndef PIECE_H
#define PIECE_H

#include "Point.h"
#include <string>

using namespace std;

class Piece {
private:
	Point pos;
public:
	enum Type { king, queen, bishop, rook, knight, pawn};

	const char symb;
	string name;
	Type bit;
	
	Piece(Type , int x, int y);
	void move(int x, int y);
	Point* determineMoveSet(Piece *player1, Piece *player2);
	Point getPos();
};

#endif
