#ifndef A23BB289_8696_4BEA_92C0_4484B6EB74A1
#define A23BB289_8696_4BEA_92C0_4484B6EB74A1
/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   comuni.h
 *  Versione: 1.0
 *  Descrizione:
 * ? Libreria impegnata per la ricerca dei comuni
 *================================================================================================**/
#include <iostream>
#include <vector>
#include <fstream>
#include "grafica.h"
#include "supporto.h"
#include "controlli.h"
using namespace std;

#define PATH_FILE "../include/DB_comuni_IT.csv" // Percorso file CSV comuni "IT"

vector<string> codiceComune(string &key, bool &f);                    // Codice catastale del luogo di nascita
vector<string> cntrl_luogoNascita(string &luogoNascita, bool &found); // Controlla se il comune inserito e presente nell'elenco

vector<string> codiceComune(string &key, bool &f)
{
    /**------------------------------------------------------------------------
     **                           codiceComune
     *?  Ritorna il codice catastale del comune
     *@param nome_file, &key string
     *@return string
     *------------------------------------------------------------------------**/

    vector<string> record;
    ifstream file;
    file.open(PATH_FILE);
    bool found = false;

    string citta, codice, prv;

    while (getline(file, citta, ',') && !found)
    {
        getline(file, codice, ',');
        getline(file, prv, '\n');
        if (citta == key)
        {
            found = true;
            record.push_back(citta);
            record.push_back(codice);
            record.push_back(prv);
        }
    }
    f = found;
    return record;
}

vector<string> cntrl_luogoNascita(string &luogoNascita, bool &found)
{
    /**----------------------------------------------
     **              cntrl_luogoNascita
     *?  Controlla se il comune inserito e' presente nell'elenco
     *@param path_file, &luogoNascita string
     *@parm &found bool
     *@return void
     *---------------------------------------------**/

    vector<string> record;
    while (!found) // Ne richiede l'inserimento finché il comune non venga trovato nel file
    {
#ifdef _WIN32 // Caso di Errore
        set_console_color(RED);
        cout << bold_on
             << "[ERROR 005] Luogo di Nascita non valida!!\n"
             << bold_off;
        set_console_color(YELLOW);
        cout << bold_on
             << "Suggerimento inserire data nel formato Comune (prv)\n"
             << bold_off;
        set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        cout << color(RED, BOLD, "[ERROR 005] Luogo di Nascita non valida!!\n");
        cout << color(YELLOW, BOLD, "Suggerimento inserire data nel formato Comune (prv)\n");
#endif
        cout << "Inserisci Luogo di Nascita > ";
        fflush(stdin);
        getline(cin, luogoNascita);
        upper(luogoNascita);
        cntrl_dati(luogoNascita, "Inserisci Luogo di Nascita > ");
        if (!luogoNascita_ok(luogoNascita))
        {
            cntrl_str_luogoN(luogoNascita);
            separatore_str(luogoNascita);
        }
        record = codiceComune(luogoNascita, found);
    }
    const int time_slp = 1;
    slp(time_slp);
    return record;
}
#endif /* A23BB289_8696_4BEA_92C0_4484B6EB74A1 */
