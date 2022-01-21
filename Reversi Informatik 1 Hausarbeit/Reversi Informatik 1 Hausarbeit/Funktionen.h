#pragma once

extern int gLegalX;
extern int gLegalY;
extern int gErgebnisS1;
extern int gErgebnisS2;

void ergebnis(char spielbrett[8][8]);
void anzeigen(char board[8][8]);
void zugEingabe(int legalMove[8][8]);
void zugAusfuehren(char spielbrett[8][8], int legalCol, int legalRow, char player, char gegner);
int legalMoves(char brett[8][8], int legalMoveArray[8][8], char enemy);
