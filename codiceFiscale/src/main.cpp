/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   codiceFiscale.cpp
 *  Versione: 1.5
 *  Descrizione:
 * ? Calcolo del CodiceFiscale inserendo le proprie generalità l'algoritmo calcolerà' il codice
 *================================================================================================**/
#include <iostream>
#include "../lib/supporto.h"
#include "../lib/controlli.h"
#include "../lib/estr_dati.h"
#include "../lib/comuni.h"
#include "../lib/grafica.h"
using namespace std;

#define NCHAR_MIN 3 //? Numero di caratteri minimo richiesto

/*================================++==============================*/
void dati(string &dato, string out); // Inserimento dati
/*================================++==============================*/

int main()
{

#ifdef _WIN32 // Ridimensionamento console
	size_shell(1000, 600);
#elif defined(__APPLE__)
	size_shell_MacOS("107", "28");
#endif

	string nome, cognome, dataNascita, luogoNascita;
	char sesso, c;

	cl();
	banner();

	/*================================ INSERIMENTO DATI ==============================*/

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
	cin >> sesso;
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
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	cout << color(YELLOW, BOLD, "Suggerimento inserire data di nascita nel formato gg-mm-aaaa\n");
#endif
	dati(dataNascita, "Inserisci Data di Nascita > ");
	cntrl_dati(dataNascita, "Inserisci Data di Nascita > ");
	cntrl_dataNascita(dataNascita); //? Controllo validità data
	cout << "----------------------------------\n";

//* Luogo Nascita
#ifdef _WIN32
	set_console_color(YELLOW);
	cout
		<< bold_on
		<< "Suggerimento inserire luogo nascita nel formato Comune (prv)\n"
		<< bold_off;
	set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	cout << color(YELLOW, BOLD, "Suggerimento inserire luogo nascita nel formato Comune (prv)\n");
#endif
	dati(luogoNascita, "Inserisci Luogo di Nascita > ");
	cntrl_dati(luogoNascita, "Inserisci Luogo di Nascita > ");
	cntrl_nCaratteri(NCHAR_MIN, luogoNascita, "Inserisci Luogo Nascita > ");
	upper(luogoNascita);
	cout << "----------------------------------\n";

	/*================================ FINE INSERIMENTO DATI ==============================*/

	//* Controlli formattazione su luogoNascita
	if (!luogoNascita_ok(luogoNascita))
	{
		cntrl_str_luogoN(luogoNascita);
		separatore_str(luogoNascita);
	}

	vector<string> codice;
	bool codTrv;
	codice = codiceComune(luogoNascita, codTrv);		   // Estrapola il codice catastale del comune
	if (!codTrv)										   // Se il codice non e' stato trv il comune e' sbagliato!
		codice = cntrl_luogoNascita(luogoNascita, codTrv); // Richiesta di reinserimento comune

	/*=====================================*/

	string giorno, anno;
	estr_data(dataNascita, sesso, giorno, anno);

	string codice_calcolato;
	// Calcolo de codice

	codice_calcolato = estr_cognome(cognome) + estr_nome(nome) + anno + lettera_mese(dataNascita) + giorno + codice[1];
	codice_calcolato += carattere_cntrl(codice_calcolato);

	slp(1);
	loading();

	card(codice_calcolato, nome, cognome, luogoNascita, dataNascita, sesso);

	return 0;
}

/*================================ INIZO FUNZIONI ==============================*/

void dati(string &dato, string out)
{
	/**------------------------------------------------------------------------
	 **                           dati
	 *?  Inserimento dati per la generazione del codice
	 *@param &dato, out string
	 *@return void
	 *------------------------------------------------------------------------**/

	cout << out;
	fflush(stdin);
	getline(cin, dato);
}

/*================================ FINE PROGRAMMA ==============================*/
