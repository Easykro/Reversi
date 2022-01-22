// Informatik 1 Hausarbeit 
// Aufgabenstellung: https://ilias.h-ka.de/ilias.php?ref_id=648147&cmd=view&cmdClass=ilrepositorygui&cmdNode=vj&baseClass=ilrepositorygui
// Helen Reichhard und Niklas Fürst
// 13.01.2022

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Funktionen.h"

using namespace std;

// Durch den Struct kann man jedem Spieler seinen Namen,
// sein Symbol und seine aktuelle Anzahl an legalen Zügen
// zuweisen.
struct Spieler
{
	string name;
	char symbol;
	int anzahlZüge;
};

void main()
{
	srand(time(0));

	char spielbrett[8][8]; // Array mit Spielbrett.
	int legaleZüge[8][8]; // Array mit den aktuellen legalen Zügen.
	int currentPlayer; // Speichert den spieler mit aktuellem Legerecht.

	// 2 Spieler werden erzeugt.
	Spieler spieler1;
	Spieler spieler2;

	// Eingabe der 2 Namen
	cout << "Bitte geben sie den Namen von Spieler 1 ein:" << endl;
	getline(cin, spieler1.name);
	spieler1.symbol = 'O';

	cout << "Bitte geben sie den Namen von Spieler 2 ein:" << endl;
	getline(cin, spieler2.name);
	spieler2.symbol = 'X';

	// Der beginnende Spieler wird ausgelost.
	int random;
	random = rand() % 2;

	cout << endl;

	cout << "Die Wuerfel sind gefallen! ";

	if (random == 0) {
		currentPlayer = 0;
		cout << spieler1.name << " beginnt mit dem ersten Zug!" << endl;
		cout << "Du hast die Spielsteine 'O'" << endl;
	}
	if (random == 1) {
		currentPlayer = 1;
		cout << spieler2.name << " beginnt mit dem ersten Zug!" << endl;
		cout << "Du hast die Spielsteine 'X'" << endl;
	}

	// Das Spielbrett wird auf "blank" gesetzt.
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			spielbrett[row][col] = ' ';
		}
	}

	// Die 4 festen Steine werden gesetzt.
	spielbrett[3][3] = { 'X' };
	spielbrett[4][4] = { 'X' };
	spielbrett[3][4] = { 'O' };
	spielbrett[4][3] = { 'O' };

	anzeigen(spielbrett);

	// Gameloop
	// Wird solange ausgeführt, bis keiner der beiden Spieler mehr einen legalen Zug hat.
	while ((spieler1.anzahlZüge != 0) || (spieler2.anzahlZüge != 0)) {
		if (currentPlayer == 0) {
			spieler1.anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler2.symbol);
			if (spieler1.anzahlZüge != 0) {
				cout << spieler1.name << " (O) ist am Zug." << endl;
				zugEingabe(legaleZüge);
				zugAusfuehren(spielbrett, gLegalX, gLegalY, spieler1.symbol, spieler2.symbol);
				system("cls");
				anzeigen(spielbrett);
				currentPlayer = 1;
			}
			else {
				cout << "Ich kann keinen Zug machen :(, du bist dran." << endl;
				currentPlayer = 1;
			}
		}
		else {
			spieler2.anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler1.symbol);
			if (spieler2.anzahlZüge != 0) {
				cout << spieler2.name << " (X) ist am Zug." << endl;
				//zugEingabe(legaleZüge);
				zugEingabeAutomatik(spielbrett, legaleZüge, spieler2.symbol, spieler1.symbol);
				zugAusfuehren(spielbrett, gLegalX, gLegalY, spieler2.symbol, spieler1.symbol);
				system("cls");
				anzeigen(spielbrett);
				currentPlayer = 0;
			}
			else {
				cout << "Ich kann keinen Zug machen :(, du bist dran." << endl;
				currentPlayer = 0;
			}
		}
		spieler1.anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler2.symbol);
		spieler2.anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler1.symbol);
	}

	cout << endl;
	cout << "Das Spiel ist vorbei!" << endl;
	cout << endl;


	// Steine werden gezählt und das Ergebnis verkündet.

	int ergebnisS1 = ergebnis(spielbrett, spieler1.symbol);
	int ergebnisS2 = ergebnis(spielbrett, spieler2.symbol);


	cout << spieler1.name << " hat insgesamt " << ergebnisS1 << " Steine auf dem Spielbrett." << endl;
	cout << spieler2.name << " hat insgesamt " << ergebnisS2 << " Steine auf dem Spielbrett." << endl;
	cout << endl;

	if (ergebnisS1 > ergebnisS2) {
		cout << spieler1.name << " hat gewonnen, herzlichen Glueckwunsch!" << endl;
	}
	else if (ergebnisS1 == ergebnisS2) {
		cout << "Das Spiel ging unentschieden aus!" << endl;
	}
	else {
		cout << spieler2.name << " hat gewonnen, herzlichen Glueckwunsch!" << endl;
	}
	cout << endl;

	system("pause");
}