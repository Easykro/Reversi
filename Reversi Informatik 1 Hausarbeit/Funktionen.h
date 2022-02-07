#pragma once

struct Move {
	int legalX;
	int legalY;
};

struct History
{
	int volleHistory[121];
	int testHistory[21];
};

using Board = char[8][8];

bool logDateiEingabe(History moveHistory, std::string fileName, bool spielmodus);
void spielregeln(Board &brett);
void anzeigen(Board &board);
void zugAusfuehren(Board &spielbrett, int legalCol, int legalRow, char player, char gegner);
void ausgabeMoveHistory(History moveHistory, bool spielmodus);
int legalMoves(Board &brett, int legalMoveArray[8][8], char enemy);
int ergebnis(Board &spielbrett, char player);
Move zugEingabeAutomatik(Board &spielbrett, int legalMove[8][8], char player, char enemy);
Move zugEingabe(int legalMove[8][8]);
void spielbrettBefuellen(Board &spielbrett);
void spielbrettBefuellenTestversion(Board &spielbrett);

