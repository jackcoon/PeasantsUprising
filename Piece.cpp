#include "./Piece.h"

Piece::Piece(Type type, int x, int y, bool isHuman) {
	pos = Point(x, y);
	bit = type;
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
	int ctr;//Variable to keep track of where we are in the array when making
		//rook, bishop, and queen movesets
	int k;//Iterates through bishop and queen movements	
	switch (bit) {
	case king:
		possible = new Point[8];
		ctr = 0;
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				for (int m = 0; m < 16; m++)
				{
					Point temp = Point(pos.x + i, pos.y + j);
					if (playerPieces[!isHuman][m].getPos().equals(temp) || !temp.onBoard() || danger(playerPieces, temp))
						break;
					possible[ctr++] = temp;
				}
		
		break;
	case queen:
		possible = new Point[27];
		for (int i = 0; i< 27; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;
		k = pos.y + 1;
		for (int i = pos.x + 1; i < 8; i++)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (++k >= 8)
				break;
		}
		for (int i = pos.x + 1 ; i < 8 ; i++)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, pos.y);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		k = pos.y - 1;
		for (int i = pos.x + 1; i < 8; i++)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (--k < 0)
				break;
		}
		for (int i = pos.y - 1; i >= 0; i--)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(pos.x, i);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		k = pos.y - 1;
		for (int i = pos.x - 1; i > 0; i--)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (--k < 0)
				break;
		}
		for (int i = pos.x - 1; i >= 0; i--)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, pos.y);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		k = pos.y + 1;
		for (int i = pos.x - 1; i < 8; i--)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (++k < 0)
				break;
		}
		for (int i = pos.y + 1; i < 8; i++)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(pos.x, i);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		break;
	case bishop:
		possible = new Point[13];
		for (int i = 0; i < 13; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;
		k = pos.y + 1;
		for (int i = pos.x + 1; i < 8; i++)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (++k >= 8)
				break;
		}
		k = pos.y - 1;
		for (int i = pos.x + 1; i < 8; i++)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (--k < 0)
				break;
		}
		k = pos.y - 1;
		for (int i = pos.x - 1; i > 0; i--)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (--k < 0)
				break;
		}
		k = pos.y + 1;
		for (int i = pos.x - 1; i < 8; i--)
		{		
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, k);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
			if (++k < 0)
				break;
		}
		break;
	case rook://Finds the moveset for each branch radiating from the Rook until it hits
			  //a piece or the edge of the board
		possible = new Point[14];
		for (int i = 0; i < 14; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;
		for (int i = pos.x + 1 ; i < 8 ; i++)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, pos.y);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		for (int i = pos.y - 1; i >= 0; i--)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(pos.x, i);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}	
		for (int i = pos.x - 1; i >= 0; i--)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(i, pos.y);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		for (int i = pos.y + 1; i < 8; i++)
			for (int j = 0; j < 16; j++) {
				Point temp = Point(pos.x, i);
				if (playerPieces[!isHuman][j].getPos().equals(temp))
					break;
				if (playerPieces[isHuman][j].getPos().equals(temp)) {
					possible[ctr] = temp;
					break;
				}
				possible[ctr++] = temp;
			}
		break;
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
				if (playerPieces[!isHuman][i].getPos().equals(possible[j]) || !possible[j].onBoard())
					possible[j] = Point(-1, -1);

		break;
	case pawn://Finds all possible places that pawn can move and then deletes invalid ones
		possible = new Point[3];
		possible[0] = Point(pos.x - 1, pos.y + isHuman ? 1 : -1);
		possible[1] = Point(pos.x + 1, pos.y + isHuman ? 1 : -1);
		possible[2] = Point(pos.x, pos.y + isHuman ? 1 : -1);

		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 3; j++) {
				if (playerPieces[!isHuman][i].getPos().equals(possible[j]) || !possible[j].onBoard())
					possible[j] = Point(-1, -1);
				if (playerPieces[isHuman][i].getPos().equals(possible[j]) && j != 2)
					possible[j] = Point(-1, -1);
			}
		break;
	}
	return possible;
}
bool Piece::danger(Piece **playerPieces, Point tip) {//checks if a point is capturable
	Point *moveSet;
	Piece fakeRook = Piece(rook, tip.x, tip.y, isHuman);
	moveSet = fakeRook.determineMoveSet(playerPieces);	
	for (int i = 0; i < 14; i++)
		for (int j = 2; j < 4; j++)		
			if (playerPieces[isHuman][j].getPos().equals(moveSet[i]) && moveSet[i].onBoard())
				return true;
	
	Piece fakeBishop = Piece(bishop, tip.x, tip.y, isHuman);
	moveSet = fakeBishop.determineMoveSet(playerPieces);	
	for (int i = 0; i < 13; i++)
		for (int j = 4; j < 6; j++)		
			if (playerPieces[isHuman][j].getPos().equals(moveSet[i]) && moveSet[i].onBoard())
				return true;

	Piece fakeKnight = Piece(knight, tip.x, tip.y, isHuman);
	moveSet = fakeKnight.determineMoveSet(playerPieces);	
	for (int i = 0; i < 8; i++)
		for (int j = 6; j < 8; j++)		
			if (playerPieces[isHuman][j].getPos().equals(moveSet[i]) && moveSet[i].onBoard())
				return true;

	Piece fakeQueen = Piece(queen, tip.x, tip.y, isHuman);
	moveSet = fakeQueen.determineMoveSet(playerPieces);	
	for (int i = 0; i < 27; i++)		
		if (playerPieces[isHuman][1].getPos().equals(moveSet[i]) && moveSet[i].onBoard())
			return true;

	for (int i = 8; i < 16; i++)
		if (playerPieces[isHuman][i].getPos().equals(Point(tip.x, tip.y + isHuman ? 1 : -1)))
			return true;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (playerPieces[isHuman][0].getPos().equals(Point(tip.x + i, tip.y + j)))
				return true;

	return false;			
}
















