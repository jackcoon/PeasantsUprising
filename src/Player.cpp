#include "Player.h"

Player::Player() {
	*playerPieces[0][0] = Piece(rook, 0, 0, true);
	*playerPieces[0][1] = Piece(knight, 1, 0, true);
	*playerPieces[0][2] = Piece(bishop, 2, 0, true);
	*playerPieces[0][3] = Piece(queen, 3, 0, true);
	*playerPieces[0][4] = Piece(king, 4, 0, true);
	*playerPieces[0][5] = Piece(bishop, 5, 0, true); 
	*playerPieces[0][6] = Piece(knight, 6, 0, true);
	*playerPieces[0][7] = Piece(rook, 7, 0, true);
	*playerPieces[0][8] = Piece(pawn, 0, 1, true);
	*playerPieces[0][9] = Piece(pawn, 1, 1, true);
	*playerPieces[0][10] = Piece(pawn, 2, 1, true);
	*playerPieces[0][11] = Piece(pawn, 3, 1, true);
	*playerPieces[0][12] = Piece(pawn, 4, 1, true);
	*playerPieces[0][13] = Piece(pawn, 5, 1, true); 
	*playerPieces[0][14] = Piece(pawn, 6, 1, true);
	*playerPieces[0][15] = Piece(pawn, 7, 1, true);

	*playerPieces[1][0] = Piece(rook, 0, 7, false);
	*playerPieces[1][1] = Piece(knight, 1, 7, false);
	*playerPieces[1][2] = Piece(bishop, 2, 7, false);
	*playerPieces[1][3] = Piece(queen, 3, 7, false);
	*playerPieces[1][4] = Piece(king, 4, 7, false);
	*playerPieces[1][5] = Piece(bishop, 5, 7, false); 
	*playerPieces[1][6] = Piece(knight, 6, 7, false);
	*playerPieces[1][7] = Piece(rook, 7, 7, false);
	*playerPieces[1][8] = Piece(pawn, 0, 6, false);
	*playerPieces[1][9] = Piece(pawn, 1, 6, false);
	*playerPieces[1][10] = Piece(pawn, 2, 6, false);
	*playerPieces[1][11] = Piece(pawn, 3, 6, false);
	*playerPieces[1][12] = Piece(pawn, 4, 6, false);
	*playerPieces[1][13] = Piece(pawn, 5, 6, false); 
	*playerPieces[1][14] = Piece(pawn, 6, 6, false);
	*playerPieces[1][15] = Piece(pawn, 7, 6, false);
}

