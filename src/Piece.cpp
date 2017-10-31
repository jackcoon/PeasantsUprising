#include "./Piece.h"

Piece::Piece(Type Type, int x, int y, bool isHuman) {
	pos = Point(x, y);
	bit = Type;
	this->isHuman = isHuman;
	//Sets the name and symbol of the piece by type of piece
	switch (bit) {
	case king:
		if (isHuman)
			name = "Crown";
		else
			name = "Orc";
		
		symb = 'K';
		break;
	case queen:
		if (isHuman)
			name = "Dragon";
		else
			name = "Giant Troll";
		
		symb = 'Q';
		break;
	case bishop:
		if (isHuman)
			name = "Magician";
		else
			name = "Warlock";

		symb = 'B';
		break;
	case rook:
		if (isHuman)
			name = "Spirit";
		else
			name = "Demon";

		symb = 'R';
		break;
	case knight:
		if (isHuman)
			name = "Archer";
		else
			name = "Archerboi";

		symb = 'N';
		break;
	case pawn:
		if (isHuman)
			name = "Peasant";
		else
			name = "Peon";

		symb = 'P';
		break;
	}
}

void Piece::move(int x, int y) {//Sets position
	pos.x = x;
	pos.y = y;
}

Point Piece::getPos() {
	return pos;
}

Point* Piece::determineMoveSet(Piece **playerPieces) {
	Point * possible;
	//Uses piece type to determine which valid moveset to return
	switch (bit) {
	case king:
		
		return possible;
	case queen:
		
		return possible;
	case bishop:
		
		return possible;
	case rook://Finds the moveset for each branch radiating from the Rook until it hits
			  //a piece or the edge of the board
		possible = new Point[14];
		for (int i = 0; i < 14; i++)
			possible[i] = Point(NULL, NULL);
		int ctr = 0;
		for (int i = pos.x + 1 ; i < 8 ; i++)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, pos.y);
				if (playerPieces[!isHuman][i].getPos().Equals(temp))
					break;
				if (playerPieces[isHuman][i].getPos().Equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		for (int i = pos.x - 1; i >= 0; i--)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, pos.y);
				if (playerPieces[!isHuman][i].getPos().Equals(temp))
					break;
				if (playerPieces[isHuman][i].getPos().Equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		for (int i = pos.y + 1; i < 8; i++)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(pos.x, i);
				if (playerPieces[!isHuman][i].getPos().Equals(temp))
					break;
				if (playerPieces[isHuman][i].getPos().Equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		for (int i = pos.y - 1; i >= 0; i--)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(pos.x, i);
				if (playerPieces[!isHuman][i].getPos().Equals(temp))
					break;
				if (playerPieces[isHuman][i].getPos().Equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
				
		return possible;
	case knight://Finds all possible places that knight can move and then deletes invalid ones
		possible = new Point[8];
		possible[0] = Point(pos.x + 1, pos.y + 2);
		possible[1] = Point(pos.x + 2, pos.y + 1);
		possible[2] = Point(pos.x + 2, pos.y - 1);
		possible[3] = Point(pos.x + 1, pos.y - 2);
		possible[4] = Point(pos.x - 1, pos.y - 2);
		possible[5] = Point(pos.x - 2, pos.y - 1);
		possible[6] = Point(pos.x - 2, pos.y + 1);
		possible[7] = Point(pos.x - 1, pos.y + 2);
		
		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 8; j++) 
				if (playerPieces[!isHuman][i].getPos().Equals(possible[j]) || !possible[j].onBoard())
					possible[j] = Point(NULL, NULL);

		return possible;
	case pawn://Finds all possible places that pawn can move and then deletes invalid ones
		possible = new Point[3];
		possible[0] = Point(pos.x - 1, pos.y + isHuman ? 1 : -1);
		possible[1] = Point(pos.x + 1, pos.y + isHuman ? 1 : -1);
		possible[2] = Point(pos.x, pos.y + isHuman ? 1 : -1);

		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 3; j++) {
				if (playerPieces[!isHuman][i].getPos().Equals(possible[j]) || !possible[j].onBoard())
					possible[j] = Point(NULL, NULL);
				if (playerPieces[isHuman][i].getPos().Equals(possible[j]) && j != 2)
					possible[j] = Point(NULL, NULL);
			}

		return possible;
	}
}

