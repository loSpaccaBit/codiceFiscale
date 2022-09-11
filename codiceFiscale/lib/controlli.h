#ifndef B2C77C0D_3B33_439F_8227_CADB853B5FF2
#define B2C77C0D_3B33_439F_8227_CADB853B5FF2
/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   controlli.h
 *  Versione: 1.4
 *  Descrizione:
 * ? Libreria impegnata nei controlli dei dati
 *================================================================================================**/
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "grafica.h"
#include "supporto.h"
using namespace std;

/*================================ LISTA ERRORI! ==============================*/
/**
 * ERROR 001 -> STRINGA VUOTA
 * ERROR 002 -> SESSO NON VALIDO
 * ERROR 003 -> DATA DI NASCITA NON VALIDA
 * ERROR 004 -> LUNGHEZZA MINIMA NON VALIDA
 * ERROR 005 -> LUOGO DI NASCITA NON VALIDO
 */
/*============================================================================*/

void cntrl_dati(string &input, string out); // Controllo inserimento stringa
void cntrl_nCaratteri(int nMax, string &input, string out);
void cntrl_sesso(char &sesso);               // Controllo inserimento sesso
void cntrl_dataNascita(string &dataNascita); // Controllo inserimento data di nascita
bool luogoNascita_ok(string &str);           // Controllo formato di inserimento luogo di nascita
void separatore_str(string &str);            // Separa il comune dalla prv ES.( napoli(na) => napoli (na) )
void cntrl_str_luogoN(string &str);          // Inserisce '()' ES.( napoli na => napoli (na) )

/*==============================================================*/

void cntrl_dati(string &input, string out)
{
    /**========================================================================
     **                           cntrl_dati
     *?  Controlla se e' stato immesso un input
     *@param &input, out string
     *@return void
     *========================================================================**/

    bool trv;
    do
    {
        if (input.empty()) // empty e' una funzione della lib string e controlla se la stringa e vuota
        {
#ifdef _WIN32
            set_console_color(RED);
            cout << bold_on << "[ERROR 001] Non e' stato rilevato alcun input!\n"
                 << bold_off;
            set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cout << color(RED, BOLD, "[ERROR 001] Non e' stato rilevato alcun input!\n");
#endif
            cout << out;
            fflush(stdin);
            getline(cin, input);
            trv = true;
        }
        else
            trv = false;
    } while (trv);
}

void cntrl_nCaratteri(int nMax, string &input, string out)
{
    /**========================================================================
     **                           cntrl_nCaratteri
     *?  Dati il numero minimo di caratteri controlla se una stringa rispetta il numero minimo
     *@param nMax int
     *@param &input, out string
     *@return void
     *========================================================================**/

    int lunghezza = input.size(); // lughezza stringa
    while (lunghezza < nMax)
    {
#ifdef _WIN32
        set_console_color(RED);
        cout << bold_on << "[ERROR 004] Il valore inserito non e' valido inserire almeno " << bold_off;
        set_console_color(GREEN);
        cout << bold_on << nMax << bold_off;
        set_console_color(RED);
        cout << bold_on << " caratteri!!\n"
             << bold_off;
        set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        cout << color(RED, BOLD, "[ERROR 004] Il valore inserito non e' valido inserire almeno ")
             << color(GREEN, BOLD, nMax)
             << color(RED, BOLD, " caratteri!!\n");
#endif
        cout << out;
        fflush(stdin);
        getline(cin, input);
        cntrl_dati(input, out); // controlla se c'e' stato un input
        lunghezza = input.size();
    }
}

void cntrl_sesso(char &sesso)
{
    /**----------------------
     **   cntrl_sesso
     *? Controlla se il sesso inserito sia valido (M/F)
     *@param &sesso char
     *@return void
     *------------------------**/

    bool t = false;
    do
    {
        if (sesso == 'M' || sesso == 'F')
            t = true;
        if (!t)
        {
#ifdef _WIN32
            set_console_color(RED);
            cout << bold_on << "[ERROR 002] Il sesso inserito non e' valido!!\n"
                 << bold_off;
            set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cout << color(RED, BOLD, "[ERROR 002] Il sesso inserito non e' valido!!\n");
#endif
            cout << "Inserisci Sesso > ";
            cin >> sesso;
            upper_Char(sesso);
        }
    } while (!t);
}

void cntrl_dataNascita(string &dataNascita)
{

    /**----------------------------------------------
     **              cntrl_dataNascita
     *?  Controllo la data di Nascita in input la sua validità
     *@param &dataNascita string
     *@return void
     *---------------------------------------------**/

    bool t1 = false;
    do
    {
        if (dataNascita.size() == 10)
            t1 = true;
        if (!t1)
        {
#ifdef _WIN32
            set_console_color(RED);
            cout << bold_on
                 << "[ERROR 003] Data di Nascita non valida!!\n"
                 << bold_off;
            set_console_color(YELLOW);
            cout << bold_on
                 << "Suggerimento inserire data nel formato gg-mm-aaaa\n"
                 << bold_off;
            set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cout << color(RED, BOLD, "[ERROR 003] Data di Nascita non valida!!\n");
            cout << color(YELLOW, BOLD, "Suggerimento inserire data nel formato gg-mm-aaaa\n");
#endif
            cout << "Inserisci Data di Nascita > ";
            fflush(stdin);
            getline(cin, dataNascita);
            cntrl_dati(dataNascita, "Inserisci Data di Nascita > ");
        }
    } while (!t1); // Controllo se e' stata inserita la data completa

    int annoCor = annoCorrente(); //* Anno Corrente
    /*======= ESTRAZIONE DATA =======*/

    string annoIns = dataNascita.substr(6, 4);
    string meseIns = dataNascita.substr(3, 2);
    string giornoIns = dataNascita.substr(0, 2);

    /*======= CONVERSIONE IN INT =======*/

    int annoI = stoi(annoIns);     // Anno
    int meseI = stoi(meseIns);     // Mese
    int giornoI = stoi(giornoIns); // Giorno

    const int min = 1900; // Anno minimo
    bool t = false;
    do
    {
        if (annoI <= annoCor && annoI > 0 && meseI > 0 && meseI <= 12 && giornoI > 0 && giornoI <= 31)
            t = true;
        if (annoI < min)
            t = false;
        if (!t)
        {
#ifdef _WIN32
            set_console_color(RED);
            cout << bold_on << "[ERROR 003] Data di Nascita non valida\n"
                 << bold_off;
            set_console_color(YELLOW);
            cout << bold_on
                 << "Suggerimento inserire data nel formato gg-mm-aaaa\n"
                 << bold_off;
            set_console_color(WHITE_OFF);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cout << color(RED, BOLD, "[ERROR 003] Data di nascita non valida\n");
            cout << color(YELLOW, BOLD, "Suggerimento inserire data nel formato gg-mm-aaaa\n");

#endif
            cout << "Inserisci Data di Nascita > ";
            fflush(stdin);
            getline(cin, dataNascita);
            cntrl_dati(dataNascita, "Inserisci Data di Nascita > ");
            annoIns = dataNascita.substr(6, 4);
            meseIns = dataNascita.substr(3, 2);
            giornoIns = dataNascita.substr(0, 2);

            annoI = stoi(annoIns);
            meseI = stoi(meseIns);
            giornoI = stoi(giornoIns);
        }
    } while (!t);
}

bool luogoNascita_ok(string &str)
{
    /**----------------------------------------------
     **              luogoNascita_ok
     *?  Controllo formato di inserimento luogo di nascita
     *@param &str string
     *@return void
     *---------------------------------------------**/
    int dimensione_str = str.size();
    int i = 0;
    bool trv = false;
    while (i < dimensione_str && !trv)
    {
        if (str[i] == 32 && str[i + 1] == '(')
            trv = true;
        i++;
    }
    return trv;
}

void separatore_str(string &str)
{
    /**----------------------------------------------
     **              separatore_str
     *? Separa il comune dalla prv ES.( napoli(na) => napoli (na) )
     *@param &str string
     *@return void
     *---------------------------------------------**/
    int dimensione_str = str.size();
    int i = 0;
    bool trv = false;
    string s1, s2;
    while (i < dimensione_str && !trv)
    {
        if (str[i] == '(')
        {
            trv = true;
            s1 = str.substr(0, i);
            s2 = str.substr(i, dimensione_str);
        }
        i++;
    }
    if (trv)
    {
        str.clear();
        str = s1 + " " + s2;
    }
}

void cntrl_str_luogoN(string &str)
{
    /**----------------------------------------------
    **              cntrl_str_luogoN
    *? Inserisce '()' ES.( napoli na => napoli (na) )
    *@param &str string
    *@return void
    *---------------------------------------------**/
    int dimensione_str = str.size();
    int i = 0;
    bool trv = false;
    while (i < dimensione_str && !trv)
    {
        if (str[i] == ' ')
        {
            trv = true;
            str[i] = '(';
        }
        i++;
    }
    if (trv)
    {
        char fine = ')';
        str += fine;
    }
}

#endif /* B2C77C0D_3B33_439F_8227_CADB853B5FF2 */
