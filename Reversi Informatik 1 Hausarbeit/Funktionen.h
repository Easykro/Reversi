#pragma once

struct Move {
	int legalX;
	int legalY;
};

//using Board = std::array < std::array<char, 8>, 8>;
using Board = char[8][8];

bool logDateiEingabe(int moveHistory[124], std::string fileName);
void spielregeln(Board &brett);
void anzeigen(Board &board);
void zugAusfuehren(Board &spielbrett, int legalCol, int legalRow, char player, char gegner);
void ausgabeMoveHistory(int moveHistory[120]);
int legalMoves(Board &brett, int legalMoveArray[8][8], char enemy);
int ergebnis(Board &spielbrett, char player);
Move zugEingabeAutomatik(Board &spielbrett, int legalMove[8][8], char player, char enemy);
Move zugEingabe(int legalMove[8][8]);
void spielbrettBefuellen(Board &spielbrett);
void spielbrettBefuellenTestversion(Board &spielbrett);

