/*
	COP3503 Final Project, Piece.cpp
	Purpose: Construct Pieces and move them around

	@authors Andrew Helms, Chris Stauffer
	@version 1.7 11/14/2017
*/

#include "./Piece.h"

/*
	Constructor for Pieces

	@param 	type: the enumeration of the piece (pawn, king, etc.)
		x: the initial x position of the piece (horizontal)
		y: the initial y position of the piece (vertical)
		isHuman: white = true
*/
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

Point Piece::getPos() {//Gets position
	return pos;
}

/*
	Determines the moveset of a piece based on enumeration

	@param 	playerPieces: the array of all pieces on the board
	@return an array of points where the piece is allowed to move
*/
Point* Piece::determineMoveSet(Piece ***playerPieces) {
	Point * possible;//the returned array for moveset
	int ctr;//keeps track of where we are in the array when making movesets
	int k;//iterates through bishop and queen movements
	Point temp;
	
	switch (bit) {

	case king://iterates through a grid around the king and validates each point
		possible = new Point[8];
		for (int i = 0; i < 8; i++)//sets possible[] to (-1, -1)
			possible[i] = Point(-1, -1);
		ctr = 0;

		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				for (int m = 0; m < 16; m++)
				{
					temp = Point(pos.x + i, pos.y + j);
					if (!(temp.onBoard() && !playerPieces[!isHuman][m]->getPos().equals(temp) && !danger(playerPieces, temp)))
						goto endKing;
				}
				possible[ctr++] = temp;
				endKing:
				continue;
			}
		break;

	case queen://iterates through 8 branches of possible movements until a piece
		   //or the edge is encountered (anticlockwise from positive horizontal)
		possible = new Point[27];
		for (int i = 0; i < 27; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;

		for (int i = pos.x + 1 ; i < 8 ; i++) {
			temp = Point(i, pos.y);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ0;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) { 	
					possible[ctr++] = temp;
					goto endQ0;
				}
			}
			possible[ctr++] = temp;
		}
		endQ0:

		k = pos.y + 1;	
		for (int i = pos.x + 1; i < 8; i++) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ45;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ45;
				}
			}
			possible[ctr++] = temp;
			if (++k >= 8)
				break;
		}
		endQ45:

		for (int i = pos.y + 1; i < 8; i++) {
			temp = Point(pos.x, i);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ90;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ90;
				}
			}
			possible[ctr++] = temp;
		}
		endQ90:

		k = pos.y + 1;
		for (int i = pos.x - 1; i >= 0; i--) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ135;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ135;
				}
			}
			possible[ctr++] = temp;
			if (++k >= 8)
				break;
		}
		endQ135:

		for (int i = pos.x - 1; i >= 0; i--) {
			temp = Point(i, pos.y);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ180;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ180;
				}
			}
			possible[ctr++] = temp;
		}
		endQ180:

		k = pos.y - 1;
		for (int i = pos.x - 1; i >= 0; i--) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ225;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ225;
				}
			}
			possible[ctr++] = temp;
			if (--k < 0)
				break;
		}
		endQ225:

		for (int i = pos.y - 1; i >= 0; i--) {
			temp = Point(pos.x, i);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ270;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ270;
				}
			}
			possible[ctr++] = temp;
		}
		endQ270:

		k = pos.y - 1;
		for (int i = pos.x + 1; i < 8; i++) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto endQ315;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto endQ315;
				}
			}
			possible[ctr++] = temp;
			if (--k < 0)
				break;
		}
		endQ315:

		break;

	case rook://Finds the moveset for each branch radiating from the Rook until it hits
		  //a piece or the edge of the board (anticlockwise from positive horizontal)
		possible = new Point[14];
		for (int i = 0; i < 14; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;

		for (int i = pos.x + 1 ; i < 8 ; i++) {
			temp = Point(i, pos.y);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end0;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end0;
				}
			}
			possible[ctr++] = temp;
		}
		end0:

		for (int i = pos.y + 1; i < 8; i++) {
			temp = Point(pos.x, i);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end90;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end90;
				}
			}
			possible[ctr++] = temp;	
		}
		end90:

		for (int i = pos.x - 1; i >= 0; i--) {
			temp = Point(i, pos.y);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end180;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end180;
				}
			}
			possible[ctr++] = temp;
		}
		end180:

		for (int i = pos.y - 1; i >= 0; i--) {
			temp = Point(pos.x, i);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end270;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end270;
				}
			}
			possible[ctr++] = temp;
		}
		end270:

		break;

	case bishop://Finds the moveset for each branch radiating from the bishop until it hits
		    //a piece or the edge of the board (anticlockwise from positive / diagonal)
		possible = new Point[13];
		for (int i = 0; i < 13; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;

		k = pos.y + 1;
		for (int i = pos.x + 1; i < 8; i++) {
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end45;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end45;
				}
			}
			possible[ctr++] = temp;
			if (++k >= 8)
				break;
		}
		end45:

		k = pos.y + 1;
		for (int i = pos.x - 1; i >= 0; i--) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end135;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end135;
				}
			}
			possible[ctr++] = temp;
			if (++k >= 8)
				break;
		}
		end135:

		k = pos.y - 1;
		for (int i = pos.x - 1; i >= 0; i--) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end225;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end225;
				}
			}
			possible[ctr++] = temp;
			if (--k < 0)
				break;
		}
		end225:

		k = pos.y - 1;
		for (int i = pos.x + 1; i < 8; i++) {		
			temp = Point(i, k);
			if (discoverCheck(playerPieces, temp))
				continue;
			for (int j = 0; j < 16; j++) {
				if (playerPieces[!isHuman][j]->getPos().equals(temp))
					goto end315;
				if (playerPieces[isHuman][j]->getPos().equals(temp)) {
					possible[ctr++] = temp;
					goto end315;
				}
			}
			possible[ctr++] = temp;
			if (--k < 0)
				break;
		}
		end315:

		break;

	case knight://adds each possible knight movement if it's valid
		possible = new Point[8];
		for (int i = 0; i < 8; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;
		
		temp = Point(pos.x + 1, pos.y + 2);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x + 2, pos.y + 1);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x + 2, pos.y - 1);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x + 1, pos.y - 2);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x - 1, pos.y - 2);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x - 2, pos.y - 1);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x - 2, pos.y + 1);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		temp = Point(pos.x - 1, pos.y + 2);
		if (knightCheck(playerPieces, temp))
			possible[ctr++] = temp;

		break;

	case pawn://adds each pawn movement if it's valid
		possible = new Point[3];
		for (int i = 0; i < 8; i++)
			possible[i] = Point(-1, -1);
		ctr = 0;
		temp = Point(pos.x - 1, pos.y + (isHuman ? 1 : -1));
		for (int j = 0; j < 16; j++)
			if (temp.onBoard() && !playerPieces[isHuman][j]->getPos().equals(temp) && !playerPieces[!isHuman][j]->getPos().equals(temp) && !discoverCheck(playerPieces, temp)) {
				possible[ctr++] = temp;
				break;
			}

		temp = Point(pos.x + 1, pos.y + (isHuman ? 1 : -1));
		for (int j = 0; j < 16; j++)
			if (temp.onBoard() && !playerPieces[isHuman][j]->getPos().equals(temp) && !playerPieces[!isHuman][j]->getPos().equals(temp) && !discoverCheck(playerPieces, temp)) {
				possible[ctr++] = temp;
				break;
			}

		temp = Point(pos.x, pos.y + (isHuman ? 1 : -1));
		for (int j = 0; j < 16; j++)
			if (temp.onBoard() && playerPieces[isHuman][j]->getPos().equals(temp) && !discoverCheck(playerPieces, temp)) {
				possible[ctr++] = temp;
				break;
			}
		break;
	}

	return possible;
}

/*
	Checks if a knight can move somewhere

	@param 	playerPieces: the array of all pieces on the board
		tip: the point being evaluated
	@return a boolean: true = allowed to move there
*/
bool Piece::knightCheck(Piece ***playerPieces, Point tip) {
	for (int j = 0; j < 16; j++)
		if (!(tip.onBoard() && !playerPieces[!isHuman][j]->getPos().equals(tip) && !discoverCheck(playerPieces, tip)))
			return false;
	return true;
}

/*
	Checks if a point is capturable by making a fake piece at that position
		and then checking if an enemy of that piece type is within its 
		moveset

	@param 	playerPieces: the array of all pieces on the board
		tip: the point being evaluated
	@return a boolean: true = capturable
*/
bool Piece::danger(Piece ***playerPieces, Point tip) {
	if (!tip.onBoard())
		return false;	

	Point were = pos;//saves current position
	move(-1,-1);
	Point *moveSet;
	
	Piece fakeRook = Piece(rook, tip.x, tip.y, isHuman);//rook check
	moveSet = fakeRook.determineMoveSet(playerPieces);	
	for (int i = 0; i < 14; i++)
		for (int j = 2; j < 4; j++)		
			if (playerPieces[isHuman][j]->getPos().equals(moveSet[i]) && moveSet[i].onBoard()) {
				move(were.x, were.y);
				return true;
			}
	
	Piece fakeBishop = Piece(bishop, tip.x, tip.y, isHuman);//bishop check
	moveSet = fakeBishop.determineMoveSet(playerPieces);	
	for (int i = 0; i < 13; i++)
		for (int j = 4; j < 6; j++)		
			if (playerPieces[isHuman][j]->getPos().equals(moveSet[i]) && moveSet[i].onBoard()) {
				move(were.x, were.y);
				return true;
			}

	Piece fakeKnight = Piece(knight, tip.x, tip.y, isHuman);//knight check
	moveSet = fakeKnight.determineMoveSet(playerPieces);	
	for (int i = 0; i < 8; i++)
		for (int j = 6; j < 8; j++)		
			if (playerPieces[isHuman][j]->getPos().equals(moveSet[i]) && moveSet[i].onBoard()) {
				move(were.x, were.y);
				return true;
			}

	Piece fakeQueen = Piece(queen, tip.x, tip.y, isHuman);//queen check
	moveSet = fakeQueen.determineMoveSet(playerPieces);	
	for (int i = 0; i < 27; i++)		
		if (playerPieces[isHuman][1]->getPos().equals(moveSet[i]) && moveSet[i].onBoard()) {
				move(were.x, were.y);
				return true;
			}

	for (int i = 8; i < 16; i++)//pawns check
		if (playerPieces[isHuman][i]->getPos().equals(Point(tip.x, tip.y + (isHuman ? 1 : -1)))) {
				move(were.x, were.y);
				return true;
			}

	for (int i = -1; i <= 1; i++)//king check
		for (int j = -1; j <= 1; j++)
			if (playerPieces[isHuman][0]->getPos().equals(Point(tip.x + i, tip.y + j))) {
				move(were.x, were.y);
				return true;
			}
	move(were.x, were.y);
	return false;			
}

/*
	Checks if your king can be captured given a potential move

	@param 	playerPieces: the array of all pieces on the board
		tryMove: the movement being evaluated
	@return a boolean: true = king is endangered by that move
*/
bool Piece::discoverCheck(Piece ***playerPieces, Point tryMove) {
	Point were = pos;//Keeps the pieces current place
	this->move(tryMove.x, tryMove.y);
	int j;

	for (j = 0; j < 16; j++) {
		if (playerPieces[isHuman][j]->getPos().equals(tryMove)) {
			playerPieces[isHuman][j]->move(-1, -1);//temporarily captures piece occupying tryMove
			break;
		}
	}

	bool inDanger = playerPieces[!isHuman][0]->danger(playerPieces, playerPieces[!isHuman][0]->getPos());
	move(were.x, were.y);
	if (j != 16)//Moves the enemy piece back if it was moved
		playerPieces[isHuman][j]->move(tryMove.x, tryMove.y);
	return inDanger;
}














