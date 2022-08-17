#ifndef DDA67E68_37A4_4BD5_8854_D2FD0ED60747
#define DDA67E68_37A4_4BD5_8854_D2FD0ED60747
/**================================================================================================
* *                                           INFO
*  Autore    : Francesco Pio Nocerino 
*  @email    : kekko.dev16@gmail.com 
*  File      : logica.h
*  Versione  : 0.0
*  Data      : 17/08/2022
*  Descr     :
* ? 
*================================================================================================**/

#include <iostream>
#include "grafica.h"
using namespace std;

/*================================ DIVISION ==============================*/

void cntrl_dati(string &input, string out); //Controlo inserimento stringa
void cntrl_nCaratteri(int nMax, string &input, string out);
void cntrl_sesso(char &sesso);               // Controllo inserimento sesso
void cntrl_dataNascita(string &dataNascita); // Controllo inserimento data di nascita
string nome_file(string name_file);
void restart_programm(string name_file);
/*================================ DIVISION ==============================*/

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
        if (input.empty()) //empty e' una funzione della lib string e controlla se la stringa e vuota
        {
#ifdef _WIN32
            set_console_color(RED);
            cout << bold_on << "[ERROR 001] Non e' stato rilevato alcun input!\n"
                 << bold_off;
            set_console_color(WHITE_OFF);
#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
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
        cout << bold_on << "[ERROR 004] Il valore inserito non e' valido inserire alemo " << bold_off;
        set_console_color(GREEN);
        cout << bold_on << nMax << bold_off;
        set_console_color(RED);
        cout << bold_on << " caratteri!!\n"
             << bold_off;
        set_console_color(WHITE_OFF);
#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        cout << color(RED, BOLD, "[ERROR 004] Il valore inserito non e' valido inserire alemo ")
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

#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cout << color(RED, BOLD, "[ERROR 002] Il sesso inserito non e' valido!!\n");
#endif
            cout << "Inserisci Sesso > ";
            cin.get(sesso);
            upper_Char(sesso);
        }
    } while (!t);
}

void cntrl_dataNascita(string &dataNascita)
{

    /**----------------------------------------------
     **              cntrl_dataNascita
     *?  Controllo la data di Nascita in input la sua validita
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
#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cout << color(RED, BOLD, "[ERROR 003] Data di Nascita non valida!!\n");
            cout << color(YELLOW, BOLD, "Suggerimento inserire data nel formato gg-mm-aaaa\n");
#endif
            cout << "Inserisci Data di Nascita > ";
            fflush(stdin);
            getline(cin, dataNascita);
            cntrl_dati(dataNascita, "Inserisci Data di Nascita > ");
        }
    } while (!t1); //Controllo se e' stata inserita la data completa

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
#elif defined __APPLE__ || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
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

string nome_file(string name_file)
{
    /**----------------------
     **   nome_file
     *@param void void
     *@return void
     *? Nome file corrente  
     *------------------------**/
    string name;
    int i;
    for (i = 0; i < name_file.size(); i++)
    {
        if (name_file[i] == '.')
            break;
    }
    name = name_file.substr(0, i);
    return name;
}

void restart_programm(string name_file)
{
#ifdef _WIN32 //* Composizione nome file exe (WIN)
    string nome = nome_file(name_file) + ".exe";
#elif defined __APPLE__ //* Composizione nome file exe (MacOS)
    string nome = "./" + nome_file(name_file);
#endif
    int n = nome.size();
    char *name_exe;
    name_exe = (char *)malloc(n * sizeof(int));
    strcpy(name_exe, nome.c_str());
    system(name_exe);
}

#endif /* DDA67E68_37A4_4BD5_8854_D2FD0ED60747 */
