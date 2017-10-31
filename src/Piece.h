#ifndef PIECE_H
#define PIECE_H

#include "Point.h"
#include "Player.h"
#include <string>

using namespace std;

class Piece {
	friend class Player;

private:
	Point pos;
public:
	enum Type { king, queen, bishop, rook, knight, pawn};

	char symb;
	string name;
	Type bit;
	bool isHuman;
	
	Piece(Type , int x, int y, bool isHuman);
	void move(int x, int y);
	Point* determineMoveSet(Piece **playerPieces);
	Point getPos();
};

#endif
