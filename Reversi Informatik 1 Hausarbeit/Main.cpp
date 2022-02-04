// Informatik 1 Hausarbeit 
// Aufgabenstellung: https://ilias.h-ka.de/ilias.php?ref_id=648147&cmd=view&cmdClass=ilrepositorygui&cmdNode=vj&baseClass=ilrepositorygui
// Helen Reichhard und Niklas Fürst
// 13.01.2022

// Niklas:
// -Log-Datei einbauen.

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
// sein Symbol, seine aktuelle Anzahl an legalen Zügen
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

	while (true) {

		char spielbrett[8][8]; // Array mit Spielbrett.
		int legaleZüge[8][8]; // Array mit den aktuellen legalen Zügen.
		int currentPlayer; // Speichert den Spieler mit aktuellem Legerecht.
		int gesetzteSteine = 0; // Speichert die Anzahl bereits gesetzter Steine.
		int *moveHistory = new int[120]; // Speichert die gespielten Moves im dynamischen Speicher.

		Spieler spieler[2];

		// Auswahl zur Anzeige der Spielregeln.
		cout << "Herzlich Willkommen bei Reversi!" << endl << endl;
		cout << "Moechtest du die Spielregeln wissen oder bist du schon Profi?" << endl;
		cout << "Bitte gib p fuer Profi und a fuer Anfaenger ein." << endl;

		while (true) {
			char auswahl;
			cin >> auswahl;

			if (auswahl == 'p') {
				system("cls");
			}
			else if (auswahl == 'a') {
				system("cls");
				spielregeln(spielbrett);
			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (p oder a)" << endl;
				continue;
			}
			break;
		}

		// Auswahl des Spielmodus.
		cout << "Willst du gegen einen anderen Spieler oder gegen den Computer spielen?" << endl << endl;
		cout << "Bitte geben Sie c (klein) ein, um gegen den Computer zu spielen oder s (klein)," << endl << "um gegen einen anderen Spieler zu spielen: ";

		while (true) {
			char auswahl;
			cin >> auswahl;

			// Bei Spieler vs. Spieler werden beide Spieler auf "Mensch (true)" gesetzt.
			if (auswahl == 's') {
				spieler[0].isHuman = true;
				spieler[1].isHuman = true;
			}
			// Bei Spieler vs. Computer wird der zweite Spieler auf "Computer (false)" gesetzt
			else if (auswahl == 'c') {
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

		// Schluckt ein "ENTER".
		string dummy;
		getline(cin, dummy);

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



		// Gameloop *ANFANG*
		// Wird solange ausgeführt, bis keiner der beiden Spieler mehr einen legalen Zug hat.
		while ((spieler[0].anzahlZüge != 0) || (spieler[1].anzahlZüge != 0)) {

			// Anzahl der legalen Züge des Spielers mit Legerecht werden gezählt.
			spieler[currentPlayer].anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler[1 - currentPlayer].symbol);

			// if-Abfrage ob der Spieler mit Legerecht einen legalen Zug hat.
			if (spieler[currentPlayer].anzahlZüge != 0) {
				cout << spieler[currentPlayer].name << " (" << spieler[currentPlayer].symbol << ") ist am Zug." << endl;
				Move move;

				// Wenn der aktuelle Spieler ein Mensch ist, so kann er nun seinen Zug eingeben.
				if (spieler[currentPlayer].isHuman) {
					move = zugEingabe(legaleZüge);
				}
				// Wenn der aktuelle Spieler der Computer ist, so greift die "zugEingabeAutomatik".
				else {
					move = zugEingabeAutomatik(spielbrett, legaleZüge, spieler[currentPlayer].symbol, spieler[1 - currentPlayer].symbol);
				}

				zugAusfuehren(spielbrett, move.legalX, move.legalY, spieler[currentPlayer].symbol, spieler[1 - currentPlayer].symbol);

				// Koordinaten des gesetzten Steins wird gespeichert.
				gesetzteSteine++;
				moveHistory[gesetzteSteine*2-1] = move.legalY;
				moveHistory[gesetzteSteine*2] = move.legalX;

				system("cls");
				cout << "Zuletzt ausgefuehrter Spielzug: (" << moveHistory[gesetzteSteine] << "|" << moveHistory[gesetzteSteine + 1] << ")" << endl;
				cout << "Aktueller Punktestand von " << spieler[0].name << ": " << ergebnis(spielbrett, spieler[0].symbol) << endl;
				cout << "Aktueller Punktestand von " << spieler[1].name << ": " << ergebnis(spielbrett, spieler[1].symbol) << endl;
				anzeigen(spielbrett);
			}
			// Spieler hat keinen legalen Zug zur Verfügung.
			else {
				cout << "Ich kann keinen Zug machen :(, du bist dran." << endl;
			}

			// Wechsel des Spielers mit Legerecht.
			currentPlayer = 1 - currentPlayer;

			// Kontrolle der Gameloop-Bedingung.
			spieler[0].anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler[0].symbol);
			spieler[1].anzahlZüge = legalMoves(spielbrett, legaleZüge, spieler[1].symbol);
		}
		cout << endl;
		// Gameloop *ENDE*



		cout << "Das Spiel ist vorbei!" << endl << endl;;

		// Steine werden gezählt.
		int ergebnisVon[2];
		for (int i = 0; i < 2; i++) {
			ergebnisVon[i] = ergebnis(spielbrett, spieler[i].symbol);
			cout << spieler[i].name << " hat insgesamt " << ergebnisVon[i] << " Steine auf dem Spielbrett." << endl;
		}
		cout << endl;

		// Ergebnis wird verkündet.
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
		
		// Auswahl zur Anzeige des Spielverlaufs.
		cout << "Moechtest du die Log-Datei angezeigt bekommen?" << endl;
		cout << "j = JA und n = NEIN" << endl;
		getline(cin, dummy);

		while (true) {
			char auswahl;
			cin >> auswahl;

			if (auswahl == 'j') {
				logDateiEingabe(moveHistory, "LogDatei");
				ausgabeMoveHistory(moveHistory);
			}
			else if (auswahl == 'n') {
			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (j oder n)" << endl;
				continue;
			}
			break;
		}
		cout << endl;

		// Abfrage ob nochmal gespielt werden möchte.
		cout << "Wollt ihr nochmal eine Runde spielen :)?" << endl;
		cout << "j = JA und n = NEIN" << endl;

		while (true) {
			char auswahl;
			cin >> auswahl;

			if (auswahl == 'j') {
			}
			else if (auswahl == 'n') {
				cout << "Auf Wiedersehen :)!" << endl;
				return;
			}
			else {
				cout << "Bitte geben Sie ein gueltiges Zeichen ein (j oder n)" << endl;
				continue;
			}
			break;
		}
		cout << endl;

		delete[] moveHistory;
	}

	system("pause");
}