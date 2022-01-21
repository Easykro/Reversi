// Informatik 1 Hausarbeit 
// Aufgabenstellung: https://ilias.h-ka.de/ilias.php?ref_id=648147&cmd=view&cmdClass=ilrepositorygui&cmdNode=vj&baseClass=ilrepositorygui
// Helen Reichhard und Niklas Fürst
// 13.01.2022

#include <iostream>
#include <string>
#include "Funktionen.h"

using namespace std;

void main()
{
	char currentPlayer;

	char ich = 'O';
	char gegner = 'X';

	char spielbrett[8][8]; // Spielbrett
	int legaleZüge[8][8]; // Array mit den aktuellen legalen Zügen.

	// Alle Spielfelder werden auf "blank" gesetzt.
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			spielbrett[row][col] = ' ';

	// Die vorgegebenen Steine werden gesetzt.
	spielbrett[3][3] = { 'X' };
	spielbrett[4][4] = { 'X' };
	spielbrett[3][4] = { 'O' };
	spielbrett[4][3] = { 'O' };
	
	cout << "Anzahl legaler Zuege: " << legalMoves(spielbrett, legaleZüge, gegner) << endl;

	anzeigen(spielbrett);

	// Funktion zur Eingabe
	zugEingabe(legaleZüge);

	// Legaler zug wird in den globalen Variablen legalX und legalY gespeichert.
	spielbrett[gLegalY][gLegalX] = { 'O' };

	zugAusfuehren(spielbrett, gLegalX, gLegalY, ich, gegner);

	// Aktuelles Speilbrett wird ausgegeben.
	anzeigen(spielbrett);

	system("pause");
}