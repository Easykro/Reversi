#pragma once

struct Move {
	int legalX;
	int legalY;
};


int ergebnis(char spielbrett[8][8], char player);
void anzeigen(char board[8][8]);
Move zugEingabe(int legalMove[8][8]);
void zugAusfuehren(char spielbrett[8][8], int legalCol, int legalRow, char player, char gegner);
int legalMoves(char brett[8][8], int legalMoveArray[8][8], char enemy);
Move zugEingabeAutomatik(char spielbrett[8][8], int legalMove[8][8], char player, char enemy);
