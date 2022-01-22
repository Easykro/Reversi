#pragma once

extern int gLegalX;
extern int gLegalY;


int ergebnis(char spielbrett[8][8], char player);
void anzeigen(char board[8][8]);
void zugEingabe(int legalMove[8][8]);
void zugAusfuehren(char spielbrett[8][8], int legalCol, int legalRow, char player, char gegner);
int legalMoves(char brett[8][8], int legalMoveArray[8][8], char enemy);
void zugEingabeAutomatik(char spielbrett[8][8], int legalMove[8][8], char player, char enemy);
