#include <iostream>
#include <fstream>
#include "Funktionen.h"
#include <algorithm> 
#include <iterator> 
#include <iomanip>
using namespace std;

/*
   Die Funktion zugEingabe lässt den Spieler seinen nächsten Spielzug
   eingeben. Nicht legale Spielzüge werden abgefangen und es muss ein
   neuer legaler Zug eingegeben werden. Sie bekommt als argument den
   Array mit den legalen Zügen.
*/

Move zugEingabe(int legalMove[8][8])
{
	int reihe, spalte;
	int counter = 0;

	cout << "Bitte gib deinen Zug ein:" << endl;
	cout << "(1. Y - Koordinate (enter), 2. X - Koordinate (enter))" << endl;

	// Die while-Schleife wird so lange ausgeführt, bis ein legaler
	// Zug eingegeben wurde.
	while (true) {
		cin >> reihe;
		cin >> spalte;

		if (0 <= reihe && reihe <= 7 && 0 <= spalte && spalte <= 7 && legalMove[reihe][spalte] == 1) {
			Move move;
			move.legalY = reihe;
			move.legalX = spalte;

			return move;
		}
		else {
			cout << "Du hast einen nicht legalen Zug eingegeben!" << endl;
			cout << "Bitte gib neue Koordinaten ein:" << endl;
			cin.clear();
			cin.ignore(10000, '\n'); // siehe https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
			//das falsch eingegebene Zeichen, das nicht in die Variablen reihe und spalte abgespeichert werden kann, wird jetzt ignoriert		
		}
	}
}

/*
   Die Funktion anzeige() zeigt das Spielfeld in seinem Status quo an.
   Die Funktion wird mit dem 2D-Array "spielbrett" mit den aktuellen
   Spielsteinpositionen aufgerufen.
*/

void anzeigen(Board &brett)
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

	// In dieser for-Schleife wird das ganze Spielfeld (außer die unterste Reihe)
	// ausgegeben. Außerdem wird die Beschriftung der Y-Achse ausgegeben.
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

		// Reihe die die Spielsteine enthält wird ausgegeben.
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
   in abhängigkeit des aktuellen Spielbrettzustandes.
*/

int legalMoves(Board &brett, int legalMoveArray[8][8], char enemy)
{
	int spalte = 0;
	int reihe = 0;
	int rowSearch = 0;
	int colSearch = 0;
	int legalMoveCounter = 0;


	// Array mit den bisherigen legalen Spielzügen wird auf seinen
	// Default-Zustand zurückgesetzt, also jedes Feld auf 0.
	for (reihe = 0; reihe < 8; reihe++) {
		for (spalte = 0; spalte < 8; spalte++) {
			legalMoveArray[reihe][spalte] = 0;
		}
	}

	// Nun schaut man sich jedes Spielfeld an
	for (reihe = 0; reihe < 8; reihe++) {
		for (spalte = 0; spalte < 8; spalte++) {
			// Wir suchen nach gegnerischen Steinen. Ansonsten
			// gehen wir zum nächsten Feld
			if (brett[reihe][spalte] != enemy) {
				continue;
			}

			// Wenn wir einen gegnerischen Stein gefunden haben, so schauen wir
			// jeweils die Felder eins daneben an.
			for (rowSearch = -1; rowSearch < 2; rowSearch++) {
				for (colSearch = -1; colSearch < 2; colSearch++) {
					// Wenn wir außerhalb des Spielfeldes sind, dann
					// gehen wir weiter.
					if (reihe + rowSearch < 0 || reihe + rowSearch > 7 ||
						spalte + colSearch < 0 || spalte + colSearch > 7) {
						continue;
					}

					// Wenn das Feld daneben belegt ist, dann gehen wir auch weiter.
					if (brett[reihe + rowSearch][spalte + colSearch] != ' ') {
						continue;
					}

					// Hier haben wir ein legales Feld übrig. Dieses wird
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
   Diese Funktion ist für die Ausführung des Spielzuges zuständig. Hier wird also
   der Stein gesetzt und die gegnerischen Steine wenn notwendig umgedreht.
*/

void zugAusfuehren(Board &spielbrett, int legalCol, int legalRow, char player, char gegner)
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
			// Wenn wir außerhalb des Spielfelds sind, dann gehen wir zum nächsten Feld weiter
			if (legalRow + rowSearch < 0 || legalRow + rowSearch > 7 ||
				legalCol + colSearch < 0 || legalCol + colSearch > 7 || (colSearch == 0 && rowSearch == 0)) {
				continue;
			}
			// Wenn wir den Gegner um den gesetzen Stein gefunden haben,
			// dann gehen wir in diese Richtung weiter, um die nächsten
			// Steine anzuschauen.
			if (spielbrett[legalRow + rowSearch][legalCol + colSearch] == gegner)
			{
				// Wir hüpfen auf den gefundenen benachbarten Stein.
				y = legalRow + rowSearch;
				x = legalCol + colSearch;

				// Diese Schleife wird ausgeführt, solange man einen weiteren gegnerischen Stein angrenzend findet
				// oder bis man einen eigenen Stein findet.
				while (true) {
					// colSearch und rowSearch geben wie Vektoren die Suchrichtung an.
					x += colSearch;
					y += rowSearch;

					// Wenn wir außerhalb des Boards sind, dann hören wir die Suche auf.
					if (x < 0 || x > 7 || y < 0 || y > 7) {
						break;
					}

					// Wenn wir ein leeres Feld finden, dann hören wir die Suche auf.
					if (spielbrett[y][x] == ' ') {
						break;
					}

					// Wenn wir unseren eigenen Stein finden, dann gehen wir alle Felder zurück
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

int ergebnis(Board &spielbrett, char player)
{
	int eigeneSteine = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (spielbrett[i][j] == player) {
				eigeneSteine++;
			}

		}
	}
	return eigeneSteine;
}

int bewertung(Board &spielbrett, char player)
{
	int punkte = ergebnis(spielbrett, player);
	int ecken = 0;
	const int eckenKoordinaten[4][2] = { {0,0},{0,7},{7,0},{7,7} };
	for (int i = 0; i < 4; i++) {
		int x = eckenKoordinaten[i][0];
		int y = eckenKoordinaten[i][1];
		if (spielbrett[x][y] == player) {
			ecken++;
		}
	}
	return punkte + ecken * 10;
}

void spielbrettKopieren(Board &spielbrett, Board &spielbrettKopie) {
	for (int reihe = 0; reihe < 8; reihe++) {
		for (int spalte = 0; spalte < 8; spalte++) {
			spielbrettKopie[reihe][spalte] = spielbrett[reihe][spalte];
		}
	}
}

Move zugEingabeAutomatik(Board &spielbrett, int legalMove[8][8], char player, char enemy, int thinkAhead) {
	Board spielbrettKopie;
	int bestesErgebnis = INT_MIN; // damit es schlechter ist als jedes mögliche echte Ergebnis
	int besterZugSpalte;
	int besterZugReihe;

	// probiert aus, welche Punktzahlen alle erlaubte Züge erzielen würden. Wenn es mehrere beste Züge (= Züge, die die höchste Punktzahl erzielen) gibt,
	// wird der erste (=linkest obere) dieser Züge als bester Zug abgespeichert
	for (int reihe = 0; reihe < 8; reihe++) {
		for (int spalte = 0; spalte < 8; spalte++) {
			if (legalMove[reihe][spalte] == 1) {
				spielbrettKopieren(spielbrett, spielbrettKopie);
				zugAusfuehren(spielbrettKopie, spalte, reihe, player, enemy);
				if (thinkAhead > 0) {
					int legaleZuegeGegner[8][8];
					int anzahlZuegeGegner = legalMoves(spielbrettKopie, legaleZuegeGegner, player);
					if (anzahlZuegeGegner == 0) {
						// Gegner wird übersprungen. Rechne nochmal für mich.
						int legaleZuegeIch = legalMoves(spielbrettKopie, legaleZuegeGegner, enemy);
						if (legaleZuegeIch > 0) {
							Move meineReaktion = zugEingabeAutomatik(spielbrettKopie, legaleZuegeGegner, player, enemy, thinkAhead - 1);
							zugAusfuehren(spielbrettKopie, meineReaktion.legalX, meineReaktion.legalY, player, enemy);
						}
						else {
							// Spiel vorbei.
						}
						
					}
					else {
						Move gegnerReaktion = zugEingabeAutomatik(spielbrettKopie, legaleZuegeGegner, enemy, player, thinkAhead - 1);
						zugAusfuehren(spielbrettKopie, gegnerReaktion.legalX, gegnerReaktion.legalY, enemy, player);
					}
								
				}
				
				int hypothetischesErgebnis = bewertung(spielbrettKopie, player) - bewertung(spielbrettKopie, enemy); // Punkte vom Gegner verhingern, auch wenn mein Punktestand gleich bleibt
				if (hypothetischesErgebnis > bestesErgebnis) {
					bestesErgebnis = hypothetischesErgebnis;
					besterZugSpalte = spalte;
					besterZugReihe = reihe;
				}
			}
		}
	}

	Move move;
	move.legalX = besterZugSpalte;
	move.legalY = besterZugReihe;

	return move;
}

Move zugEingabeAutomatik(Board &spielbrett, int legalMove[8][8], char player, char enemy)
{
	return zugEingabeAutomatik(spielbrett, legalMove, player, enemy, 4);
}

bool logDateiEingabe(int moveHistory[124], string fileName)
{
	ofstream fileOut;
	fileOut.open(fileName);

	if (!fileOut) {
		cout << "Fehler beim Oeffnen der LogDatei" << endl;
		return false;
	}

	fileOut << "LogDatei des Spiels:" << endl << endl;

	for (int i = 1; i < 61; i++) {
		fileOut << "(" << moveHistory[i*2-1] << "|" << moveHistory[i*2] << ")" << endl;
	}

	fileOut.close();

	return true;
}

void ausgabeMoveHistory(int moveHistory[120])
{
	cout << "LogDatei des Spiels:" << endl << endl;
	for (int i = 1; i < 61; i++) {
		cout << "(" << moveHistory[i * 2 - 1] << "|" << moveHistory[i * 2] << ")" << endl;
	}
	cout << endl;
}

void spielregeln(Board &brett)
{
	cout << "Spielregeln von Reversi:" << endl;
	cout << "Zu Beginn des Spiels befinden sich vier Steine in der Mitte des Bretts, " << endl;
	cout << "zwei Steine mit dem Symbol 'X' und zwei Steine mit dem Symbol 'O'." << endl;
	cout << "Nun setzt man abwechselnd seine Steine auf das Brett. Dabei muss man beachten," << endl;
	cout << "dass man seinen Stein nur auf ein Feld legen darf, dass horizontal, vertikal oder diagonal" << endl;
	cout << "an einem gegnerischen Stein liegt." << endl;
	cout << "Beispiel:" << endl << endl;

	// Das Spielbrett wird auf "blank" gesetzt.
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			brett[row][col] = ' ';
		}
	}

	brett[3][3] = { 'X' };
	brett[3][4] = { 'O' };
	brett[4][4] = { 'X' };
	brett[4][3] = { 'O' };

	brett[2][2] = { '!' };
	brett[2][3] = { '!' };
	brett[2][4] = { '!' };
	brett[3][2] = { '!' };
	brett[3][5] = { '!' };
	brett[5][5] = { '!' };
	brett[5][3] = { '!' };
	brett[5][4] = { '!' };
	brett[4][2] = { '!' };
	brett[4][5] = { '!' };

	anzeigen(brett);
	
	cout << endl;
	cout << "In diesem Fall kann der Spieler 'O' seinen naechsten Stein auf alle Felder legen, die mit einem ! markiert sind." << endl << endl;
	cout << "Gegnerische Steine kann man zu seinen eigenen Steinen umdrehen, indem man gegnerische Steine" << endl;
	cout << "mit seinem neu gesetzten Stein und einem anderen eigenen bereits liegenden Stein 'einschliesst'." << endl;
	cout << "Beispiel:" << endl << endl;

	brett[2][2] = { ' ' };
	brett[2][3] = { ' ' };
	brett[2][4] = { ' ' };
	brett[3][2] = { ' ' };
	brett[3][5] = { ' ' };
	brett[5][5] = { ' ' };
	brett[5][3] = { ' ' };
	brett[5][4] = { ' ' };
	brett[4][2] = { ' ' };
	brett[4][5] = { ' ' };

	brett[3][5] = { 'O' };
	brett[3][6] = { 'X' };
	brett[4][4] = { ' ' };
	brett[4][3] = { ' ' };

	anzeigen(brett);

	cout << endl;
	cout << "Da Spieler 'X' mit seinem neu gesetzten Stein auf (3|3) die zwei gegnerischen Steine eingeschlossen hat," << endl;
	cout << "werden diese nun zu 'X'en umgedreht. Hat ein Spieler keinen legalen Zug zur Verfuegung, so ist der gegnerische Spieler wieder am Zug." << endl;
	cout << "Ziel des Spiels ist es, am Ende am meisten eigene Steine auf dem Spielbrett zu haben." << endl;
	cout << endl;
	cout << "Viel Spass beim Spielen!";
	cout << endl << endl;

	system("pause");
	system("cls");
}

//Befüllt das Spielfeld vor Spielbeginn  mit den 4 Anfangssteinen
void spielbrettBefuellen(Board &spielbrett) {
// Das Spielbrett wird auf "blank" gesetzt.
for (int row = 0; row < 8; row++) {
	for (int col = 0; col < 8; col++) {
		spielbrett[row][col] = ' ';
	}
}

// Die 4 festen Steine werden gesetzt
spielbrett[3][3] = { 'X' };
spielbrett[4][4] = { 'X' };
spielbrett[3][4] = { 'O' };
spielbrett[4][3] = { 'O' };
}

//Befüllt das Spielfeld so, dass noch 10 Felder frei sind
void spielbrettBefuellenTestversion(Board &spielbrett) {
	const char inhalt[] = "XXOXXOOXOOXXXXXXOOOOXOXXOOXOXXXXOOXOOOOOO XXXOOO   OXX O   OXX  ";
	for (int i = 0; i < 64; i++) {
		((char*) spielbrett)[i] = inhalt[i];
	}
	//Der String stellt das hier unten abgebildete Spielfeld dar
	/*std::array < std::array<char, 8>, 8> test = array{
		array{'X','X','O','X','X','O','O','X'},
		array{'O','O','X','X','X','X','X','X'},
		array{'O','O','O','O','X','O','X','X'},
		array{'O','O','X','O','X','X','X','X'},
		array{'O','O','X','O','O','O','O','O'},
		array{'O',' ','X','X','X','O','O','O'},
		array{' ',' ',' ','O','X','X',' ','O'},
		array{' ',' ',' ','O','X','X',' ',' '},
	};
	*/

}