#pragma once

struct Move {
	int legalX;
	int legalY;
};

bool logDateiEingabe(int moveHistory[124], std::string fileName);
void spielregeln(char brett[8][8]);
void anzeigen(char board[8][8]);
void zugAusfuehren(char spielbrett[8][8], int legalCol, int legalRow, char player, char gegner);
int legalMoves(char brett[8][8], int legalMoveArray[8][8], char enemy);
int ergebnis(char spielbrett[8][8], char player);
Move zugEingabeAutomatik(char spielbrett[8][8], int legalMove[8][8], char player, char enemy);
Move zugEingabe(int legalMove[8][8]);