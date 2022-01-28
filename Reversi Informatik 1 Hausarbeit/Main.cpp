// Informatik 1 Hausarbeit 
// Aufgabenstellung: https://ilias.h-ka.de/ilias.php?ref_id=648147&cmd=view&cmdClass=ilrepositorygui&cmdNode=vj&baseClass=ilrepositorygui
// Helen Reichhard und Niklas Fürst
// 13.01.2022

// Niklas:
// -Log-Datei einbauen.
// -Buchstaben bei Anzeigefunktion X-Achse.


// Helen:
// -Test Modus.
// -Sie zu Du.
// -Computer verbessern.
// -Referenzen.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Funktionen.h"

using namespace std;

// Durch den Struct kann man jedem Spieler seinen Namen,
// sein Symbol und seine aktuelle Anzahl an legalen Zügen
// und seine Menschlichkeit zuweisen.
struct Spieler
{
	string name;
	char symbol;
	int anzahlZüge = -1; // -1 heißt unbekannt an durchführbaren Zügen
	bool isHuman;
};

void main()
{
	srand(time(0));
	bool spielen = true;

	while (spielen) {

		char spielbrett[8][8]; // Array mit Spielbrett.
		int legaleZüge[8][8]; // Array mit den aktuellen legalen Zügen.
		int currentPlayer; // Speichert den spieler mit aktuellem Legerecht.
		int gesetzteSteine = 0;
		int *moveHistory = new int[124];
		bool spielen = true;

		// 2 Spieler werden erzeugt.
		Spieler spieler[2];

		cout << "Herzlich Willkommen bei Reversi!" << endl << endl;
		cout << "Moechtest du die Spielregeln wissen oder bist du schon Profi?" << endl;
		cout << "Bitte gib p fuer Profi und a fuer Anfaenger ein." << endl;

		while (true) {
			char Auswahl;
			string input;
			getline(cin, input);
			Auswahl = input.at(0);

			if (Auswahl == 'p') {
				system("cls");
			}
			else if (Auswahl == 'a') {
				spielregeln(spielbrett);
			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (p oder a)" << endl;
				continue;
			}
			break;
		}

		cout << "Wollen Sie gegen einen anderen Spieler oder gegen den Computer spielen?" << endl << endl
		   	 << "Bitte geben Sie c (klein) ein, um gegen den Computer zu spielen oder s (klein)," << endl << "um gegen einen anderen Spieler zu spielen: ";

		char modusAuswahl;
		while (true) {
			string input;
			getline(cin, input);
			modusAuswahl = input.at(0);

			if (modusAuswahl == 's') {

				spieler[0].isHuman = true;
				spieler[1].isHuman = true;


			}
			else if (modusAuswahl == 'c') {

				spieler[0].isHuman = true;
				spieler[1].isHuman = false;


			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (c oder s)" << endl;
				continue;
			}

			break;
		}

		cout << endl;

		// Eingabe der 2 Namen (oder eines Namens, wenn man gegen den Computer spielt)
		for (int i = 0; i < 2; i++) {

			if (spieler[i].isHuman) {
				cout << "Spieler " << i + 1 << ", gib deinen Namen ein:" << endl;
				getline(cin, spieler[i].name);
			}
			else {
				spieler[i].name = "Fieser Computer";
			}
		}


		spieler[0].symbol = 'O';
		spieler[1].symbol = 'X';

		// Der beginnende Spieler wird ausgelost.
		currentPlayer = rand() % 2;
		cout << endl << "Die Wuerfel sind gefallen! ";

		cout << spieler[currentPlayer].name << " beginnt mit dem ersten Zug!" << endl
			<< "Du hast die Spielsteine '" << spieler[currentPlayer].symbol << "'." << endl;


		// Das Spielbrett wird auf "blank" gesetzt.
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				spielbrett[row][col] = ' ';
			}
		}

		// Die 4 festen Steine werden gesetzt und das Spielfeld erstmals angezeigt.
		spielbrett[3][3] = { 'X' };
		spielbrett[4][4] = { 'X' };
		spielbrett[3][4] = { 'O' };
		spielbrett[4][3] = { 'O' };
		anzeigen(spielbrett);

		// Gameloop
		// Wird solange ausgeführt, bis keiner der beiden Spieler mehr einen legalen Zug hat.
		while ((spieler[0].anzahlZüge != 0) || (spieler[1].anzahlZüge != 0)) {

			spieler[currentPlayer].anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler[1 - currentPlayer].symbol);
			if (spieler[currentPlayer].anzahlZüge != 0) {
				cout << spieler[currentPlayer].name << " (" << spieler[currentPlayer].symbol << ") ist am Zug." << endl;
				Move move;
				if (spieler[currentPlayer].isHuman) {
					move = zugEingabe(legaleZüge);
				}
				else {
					move = zugEingabeAutomatik(spielbrett, legaleZüge, spieler[currentPlayer].symbol, spieler[1 - currentPlayer].symbol);
				}
				zugAusfuehren(spielbrett, move.legalX, move.legalY, spieler[currentPlayer].symbol, spieler[1 - currentPlayer].symbol);
				// Gesetzter Stein wird gespeichert
				gesetzteSteine++;
				moveHistory[gesetzteSteine] = move.legalY;
				moveHistory[gesetzteSteine + 1] = move.legalX;
				system("cls");
				cout << "Zuletzt ausgefuehrter Spielzug: (" << moveHistory[gesetzteSteine] << "|" << moveHistory[gesetzteSteine + 1] << ")" << endl;
				cout << "Aktueller Punktestand von " << spieler[0].name << ": " << ergebnis(spielbrett, spieler[0].symbol) << endl;
				cout << "Aktueller Punktestand von " << spieler[1].name << ": " << ergebnis(spielbrett, spieler[1].symbol) << endl;
				anzeigen(spielbrett);
			}
			else {
				cout << "Ich kann keinen Zug machen :(, du bist dran." << endl;
			}
			currentPlayer = 1 - currentPlayer;

			spieler[0].anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler[0].symbol);
			spieler[1].anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler[1].symbol);
		}

		cout << endl;
		cout << "Das Spiel ist vorbei!" << endl;
		cout << endl;


		// Steine werden gezählt und das Ergebnis verkündet.
		int ergebnisVon[2];
		for (int i = 0; i < 2; i++) {
			ergebnisVon[i] = ergebnis(spielbrett, spieler[i].symbol);
			cout << spieler[i].name << " hat insgesamt " << ergebnisVon[i] << " Steine auf dem Spielbrett." << endl;
		}
		cout << endl;


		if (ergebnisVon[0] > ergebnisVon[1]) {
			cout << spieler[0].name << " hat gewonnen, herzlichen Glueckwunsch!" << endl;
		}
		else if (ergebnisVon[0] == ergebnisVon[1]) {
			cout << "Das Spiel ging unentschieden aus!" << endl;
		}
		else {
			cout << spieler[1].name << " hat gewonnen, herzlichen Glueckwunsch!" << endl;
		}
		cout << endl;

		cout << "Moechtest du die Log-Datei angezeigt bekommen?" << endl;
		cout << "j = JA und n = NEIN" << endl;
		cout << endl;

		// Auswahl zur Anzeige der Log-Datei.
		while (true) {
			char Auswahl;
			string input;
			getline(cin, input);
			Auswahl = input.at(0);

			if (Auswahl == 'j') {
				logDatei(moveHistory, "LogDatei");
			}
			else if (Auswahl == 'n') {
				cout << "Alles klar!" << endl;
			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (j oder n)" << endl;
				continue;
			}
			break;
		}

		cout << "Wollt ihr nochmal eine Runde spielen :)?" << endl;
		cout << "j = JA und n = NEIN" << endl;
		cout << endl;

		while (true) {
			char Auswahl;
			string input;
			getline(cin, input);
			Auswahl = input.at(0);

			if (Auswahl == 'j') {
				spielen = true;
			}
			else if (Auswahl == 'n') {
				cout << "Auf Wiedersehen :)!" << endl;
				spielen = false;
			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (j oder n)" << endl;
				continue;
			}
			break;
		}

		delete[] moveHistory;
	}

	system("pause");
}