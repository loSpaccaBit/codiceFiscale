/**================================================================================================
* *                                           INFO
*  Autore    : Francesco Pio Nocerino
*  @email    : kekko.dev16@gmail.com
*  File      : main.cpp
*  Versione  : 1.0
*  Data      : 17/08/2022
*  Descr     :
* ?	Calcolo del Codice Fiscale
*================================================================================================**/
#include <iostream>
#include "../lib/dati.h"
#include "../lib/logica.h"
#include "../lib/grafica.h"
using namespace std;

#define NCHAR_MIN 3 // Numero di caratteri minimo

int main()
{

#ifdef _WIN32 // Ridimensionamento console
	size_shell(1000, 600);
#elif __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	size_shell_MacOS("107", "28");
#endif
	string nome, cognome, dataNascita, luogoNascita;
	char sesso, c;
	cl();
	banner();

	//* Cognome
	dati(cognome, "Inserisci Cognome > ");
	cntrl_dati(cognome, "Inserisci Cognome > ");
	cntrl_nCaratteri(NCHAR_MIN, cognome, "Inserisci Cognome > ");
	upper(cognome);
	cout << "----------------------------------\n";

	//* Nome
	dati(nome, "Inserisci Nome > ");
	cntrl_dati(nome, "Inserisci Nome > ");
	cntrl_nCaratteri(NCHAR_MIN, nome, "Inserisci Nome > ");
	upper(nome);
	cout << "----------------------------------\n";

	//* Sesso
	cout << "Inserisci Sesso > ";
	cin.get(sesso);
	upper_Char(sesso);
	cntrl_sesso(sesso);

	cout << "----------------------------------\n";

//* Data di Nascita
#ifdef _WIN32
	set_console_color(YELLOW);
	cout
		<< bold_on
		<< "Suggerimento inserire data di nascita nel formato gg-mm-aaaa\n"
		<< bold_off;
	set_console_color(WHITE_OFF);
#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	cout << color(YELLOW, BOLD, "Suggerimento inserire data di nascita nel formato gg-mm-aaaa\n");
#endif
	dati(dataNascita, "Inserisci Data di Nascita > ");
	cntrl_dati(dataNascita, "Inserisci Data di Nascita > ");
	cntrl_dataNascita(dataNascita); //? Controllo validita data
	cout << "----------------------------------\n";

//* Luogo Nascita
#ifdef _WIN32
	set_console_color(YELLOW);
	cout
		<< bold_on
		<< "Suggerimento inserire luogo nascita nel formato Comune (prv)\n"
		<< bold_off;
	set_console_color(WHITE_OFF);
#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	cout << color(YELLOW, BOLD, "Suggerimento inserire luogo nascita nel formato Comune (prv)\n");
#endif
	dati(luogoNascita, "Inserisci Luogo di Nascita > ");
	cntrl_dati(luogoNascita, "Inserisci Luogo di Nascita > ");
	cntrl_nCaratteri(NCHAR_MIN, luogoNascita, "Inserisci Luogo Nascita > ");
	upper(luogoNascita);
	cout << "----------------------------------\n";

	string giorno, anno;
	estr_data(dataNascita, sesso, giorno, anno);

	string codice_calcolato;
	// Calcolo de codice
	codice_calcolato = estr_cognome(cognome) + estr_nome(nome) + anno + lettera_mese(dataNascita) + giorno + codiceComune("../include/DB_comuni_IT.txt", luogoNascita);
	codice_calcolato += carattere_cntrl(codice_calcolato);

	loading();

	card(codice_calcolato, nome, cognome, luogoNascita, dataNascita, sesso);

	char s;
#ifdef _WIN32
	set_console_color(12);
	cout << "\n[ R ] -> Calcola un nuovo Codice\n";
	set_console_color(10);
	cout << "[ Enter ] -> Termina Programma\n";
	set_console_color(7);
#elif __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	cout << color(RED, BOLD, "\n[ R ] -> Calcola un nuovo Codice\n");
	cout << color(GREEN, BOLD, "[ Enter ] -> Termina Programma\n");
#endif
	cin.get(s);
	upper_Char(s);
	switch (s)
	{
	case 'R':
		restart_programm(__FILE__);
		slp(2);
		break;

	default:
		break;
	}

	return 0;
}
