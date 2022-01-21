#include <iostream>
#include "Funktionen.h"
using namespace std;

// Globale Variablen.
int gLegalX = 0;
int gLegalY = 0;

int gErgebnisS1 = 0;
int gErgebnisS2 = 0;

/*
   Die Funktion zugEingabe l�sst den Spieler seinen n�chsten Spielzug 
   eingeben. Nicht legale Spielz�ge werden abgefangen und es muss ein 
   neuer legaler Zug eingegeben werden. Sie bekommt als argument den  
   Array mit den legalen Z�gen.                                       
*/

void zugEingabe(int legalMove[8][8])
{
	int reihe, spalte;
    int counter = 0;
	bool eingabe = true;

	cout << "Bitte geben Sie ihren Zug ein:" << endl;
	cout << "(1. Y - Koordinate (enter), 2. X - Koordinate (enter))" << endl;

	// Funktion isalpha() f�r die Buchstaben

	// Die while-Schleife wird so lange ausgef�hrt, bis ein legaler
	// Zug eingegeben wurde.
	while (eingabe) {
		cin >> reihe;
		cin >> spalte;

		for (int z = 0; z < 8; z++) {
			for (int s = 0; s < 8; s++) {
				if (legalMove[reihe][spalte] == 1) {
					counter++;
				}
			}
		}

		if (counter > 0) {
			eingabe = false;
			gLegalY = reihe;
			gLegalX = spalte;
		}
		else {
			cout << "Sie haben einen nicht legalen Zug eingegeben!" << endl;
			cout << "Bitte geben Sie neue Koordinaten ein:" << endl;
		}
	}
}

/*
   Die Funktion anzeige() zeigt das Spielfeld in seinem Status quo an. 
   Die Funktion wird mit dem 2D-Array "spielbrett" mit den aktuellen   
   Spielsteinpositionen aufgerufen.									   
*/

void anzeigen(char brett[8][8]) 
{
	const int SIZE = 8;
	int reihe = 0;
	int spalte = 0;
	int yKoor = 0;

	cout << endl;

	// Beschriftung der X-Achse.
	for (int i = 0; i < SIZE; i++) {
		if (i == 0) {
			cout << "      0";
		}
		if (i == 7) {
			continue;
		}
		cout << "   " << i + 1;
	}

	cout << endl;

	// In dieser for-Schleife wird das ganze Spielfeld (au�er die unterste Reihe)
	// ausgegeben. Au�erdem wird die Beschriftung der Y-Achse ausgegeben.
	for (reihe = 0; reihe < SIZE; reihe++) {

		// Oberste Reihe wird ausgegeben.
		cout << "    +";
		for (spalte = 0; spalte < SIZE; spalte++) {
			cout << "---+";

		}

		// Y-Achse bekommt ihre Beschriftung.
		cout << endl;
		cout << "  " << yKoor << " |";
		yKoor += 1;

		// Reihe die die Spielsteine enth�lt wird ausgegeben.
		for (spalte = 0; spalte < SIZE; spalte++) {
			cout << " " << brett[reihe][spalte] << " |";
		}

		cout << endl;
	}

	// Letzte Reihe des Spielfelds wird ausgegeben.
	cout << "    +";
	for (int i = 0; i < SIZE; i++) {
		cout << "---+";
	}

	cout << endl << endl;
}

/*
   Diese Funktion speichert am Ende jeden aktuellen legalen Spielzug eines Spielers, 
   in abh�ngigkeit des aktuellen Spielbrettzustandes.								  
*/

int legalMoves(char brett[8][8], int legalMoveArray[8][8], char enemy)
{
	int spalte = 0;
	int reihe = 0;
	int rowSearch = 0;
	int colSearch = 0;
	int legalMoveCounter = 0;

	// Array mit den bisherigen legalen Spielz�gen wird auf seinen
	// Default-Zustand zur�ckgesetzt, also jedes Feld auf 0.
	for (reihe = 0; reihe < 8; reihe++) {
		for (spalte = 0; spalte < 8; spalte++) {
			legalMoveArray[reihe][spalte] = { 0 };
		}
	}

	// Nun schaut man sich jedes Spielfeld an
	for (reihe = 0; reihe < 8; reihe++) {
		for (spalte = 0; spalte < 8; spalte++) {
			// Wir suchen nach gegnerischen Steinen. Ansonsten
			// gehen wir zum n�chsten Feld
			if (brett[reihe][spalte] != enemy) {
				continue;
			}

			// Wenn wir einen gegnerischen Stein gefunden haben, so schauen wir
			// jeweils die Felder eins daneben an.
			for (rowSearch = -1; rowSearch < 2; rowSearch++) {
				for (colSearch = -1; colSearch < 2; colSearch++) {
					// Wenn wir au�erhalb des Spielfeldes sind, dann
					// gehen wir weiter.
					if (reihe + rowSearch < 0 || reihe + rowSearch > 7 ||
						spalte + colSearch < 0 || spalte + colSearch > 7 || (colSearch == 0 && rowSearch == 0)) {
						continue;
					}

					// Wenn das Feld daneben belegt ist, dann gehen wir auch weiter.
					if (brett[reihe + rowSearch][spalte + colSearch] != ' ') {
						continue;
					}

					// Hier haben wir ein legales Feld �brig. Dieses wird
					// mit einer 1 markiert, wenn es nicht bereits markiert wurde.
					if (legalMoveArray[reihe + rowSearch][spalte + colSearch] == 1) {
						continue;
					}
					else {
     					legalMoveArray[reihe + rowSearch][spalte + colSearch] = 1;
	     				legalMoveCounter++;
				    }
				}
			}
		}
	}
	return legalMoveCounter;
}

/*
   Diese Funktion ist f�hr die Ausf�hrung des Spielzuges zust�ndig. Hier wird also
   der Stein gesetzt und die gegnerischen Steine wenn notwendig umgedreht.
*/

void zugAusfuehren(char spielbrett[8][8], int legalCol, int legalRow, char player, char gegner)
{
	int rowSearch = 0;
	int colSearch = 0;
	int x = 0;
	int y = 0;

	// Wir setzen den Spielstein
	spielbrett[legalRow][legalCol] = player;

	// Nun schauen wir einmal jedes Feld um den Spielstein herum an
	for (rowSearch = -1; rowSearch < 2; rowSearch++) {
		for (colSearch = -1; colSearch < 2; colSearch++) {
			// Wenn wir au�erhalb des Spielfelds sind, dann gehen wir zum n�chsten Feld weiter
			if (legalRow + rowSearch < 0 || legalRow + rowSearch > 7 ||
				legalCol + colSearch < 0 || legalCol + colSearch > 7 || (colSearch == 0 && rowSearch == 0)) {
				continue;
			}
			// Wenn wir den Gegner um den gesetzen Stein gefunden haben,
			// dann gehen wir in diese Richtung weiter, um die n�chsten
			// Steine anzuschauen.
			if (spielbrett[legalRow + rowSearch][legalCol + colSearch] == gegner)
			{
				// Wir h�pfen auf den gefundenen benachbarten Stein.
				y = legalRow + rowSearch;
				x = legalCol + colSearch;

				// Diese Schleife wird ausgef�hrt, solange man einen weiteren gegnerischen Stein angrenzend findet
				// oder bis man einen eigenen Stein findet.
				while (true) {
					// colSearch und rowSearch geben wie Vektoren die Suchrichtung an.
					x += colSearch;
					y += rowSearch;

					// Wenn wir au�erhalb des Boards sind, dann h�ren wir die Suche auf.
					if (x < 0 || x > 7 || y < 0 || y > 7) {
						break;
					}

					// Wenn wir ein leeres Feld finden, dann h�ren wir die Suche auf.
					if (spielbrett[y][x] == ' ') {
						break;
					}

					// Wenn wir unseren eigenen Stein finden, dann gehen wir alle Felder zur�ck
					// und drehen dabei alle gegnerischen Steine um.
					if (spielbrett[y][x] == player) {
						while (spielbrett[y -= rowSearch][x -= colSearch] == gegner) {
							spielbrett[y][x] = player;
						}
						break;
					}
				}
			}
		}
	}
}

void ergebnis(char spielbrett[8][8])
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (spielbrett[i][j] == 'O') {
				gErgebnisS1++;
			}
			if (spielbrett[i][j] == 'X') {
				gErgebnisS2++;
			}
		}
	}
}