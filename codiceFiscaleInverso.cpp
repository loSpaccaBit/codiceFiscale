/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  File:   codiceFiscaleInverso.cpp
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  Versione: 1.2
 *  Descrizione:
 * ? Calcolo del codice fiscale inverso
 *================================================================================================**/
#ifdef _WIN32
#include <windows.h>

/*================================ COLORI ==============================*/

#define GREEN 10
#define RED 12
#define WHITE 15
#define WHITE_OFF 7
#define YELLOW 14
#define BLUE 9
#define MAGENTA 13

/*==============*/

#elif __APPLE__
#include <unistd.h>
/*================================ COLORI ==============================*/
#define GREEN "92"
#define RED "91"
#define YELLOW "93"
#define BLUE "94"
#define BLUE_BACKGROUND "44"
#define WHITE "97"
#define MAGENTA "95"
#define BOLD "1"
#endif

/*=======================================================================*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <ctime>
using namespace std;

/*================================ LISTA ERRORI ==============================*/
/**
 * ERROR 001 -> STRINGA VUOTA
 * ERROR 002 -> STRING INCOMPLETA
 * ERROR 003 -> CARATTERE DI CONTROLLO ERRATO
 * ERROR 004 ->  DATA DI NASCITA FEMMINILE INVALIDA
 * CODICE COMUNE NON TROVATO -> MacOS -> segmentation fault error compiler
 * SI PUO CAMBIRARE NOME AL CODICESORGENTE E RICOMPILARLO MA NON L'ESEGUIBILE, NEL CASO AVRA PROBLEMI CON IL RIAVVIO IN CASO ERRATO DI DATA
 */

/*================================ INZIO PROTOTIPI ==============================*/

void upper(string &str); // Converte i caratteri della stringa in maiuscolo
void slp(int s);         // Sleep

/*================================ ESTRAZIONE DATI ==============================*/

void estr_dati(string codice, string &cognome, string &nome, string &luogoNascita, string &annoNascita, string &giornoNascita, string &codCatastale, string &meseNascita, string &char_cntrl); // Estrae i dati interessati dalle stringhe
string estr_sesso(string giornoNascita);                                                                                                                                                       // Dato il giorno di nascita determina il sesso
string estr_mese(string meseNascita);                                                                                                                                                          // Dato il carattere del mese estrae il mese corrispondente

/*================================ CONTROLLI ==============================*/

void cntrl_input(string &input, string out); // Controlla se c'e input
char cntrl_char(string codice);              // Controlla il carattere di controllo
void cntrl_giornoNascita(string &giornoNascita, string &dataNascita, string &meseNascita, string &annoNascita, string sesso);
/*=================================================================*/

string ricerca_comune(string path_file, string codiceCatastale); // Ricerca del comune di nascita
string anno_corrente();
void aggiungi_anno(string &annoNascita, string sesso); // elimina
int carattere_pari(char t);                            // Valori caratteri in posizone pari
int carattere_dispari(char t);                         // Valori caratteri in posizione dispari
string nome_file();                                    // Nome file corrente

/*================== GRAFICA =================*/

void cl(); // Pulisci schermo
#ifdef _WIN32
void set_console_color(int dim); //*Win
void bandiera_italiana();
void size_shell(int h, int w);          //* Ridimensiona la shell
std::ostream &bold_on(std::ostream &os) //! testo in bold per win
{
    return os << "\e[1m";
}

std::ostream &bold_off(std::ostream &os)
{
    return os << "\e[0m";
}
#elif defined __APPLE__ //*MacOs
//! overloading color
void size_shell_MacOS(string h, string w);            //* Ridimensiona shell
string color(string word, string back, string frase); //* Colori x MacOS
string color(string word, string back, char frase);
string color(string word, string back, int num);
string color(string word, string back, float num);
#endif
void card(string codice, string codice2, string cognome, string nome, string sesso, string &dataNascita, string &giornoNascita, string &meseNascita, string &annoNascita, string luogoNascita, string char_cntrl, string char_cntrl2); // Stampa finales
void error_char(string &codice, string char_cntrl, string char_cntrl2, bool &trv);                                                                                                                                                     // Caso di errore del carattere di controllo
void banner();                                                                                                                                                                                                                         // Banner
/*================================ FINE PROTOTIPI ==============================*/

int main()
{
    string codice;
    string cognome, nome, sesso, luogoNascita, annoNascita, giornoNascita, codiceCatastale, meseNascita, char_cntrl, char_cntrl2;

#ifdef _WIN32 // Ridimensionamento console
    size_shell(1000, 600);
#elif __APPLE__
    size_shell_MacOS("107", "31");
#endif

    cl();
    banner();

    //* Inserimento codices
    cout << "Inserisci Codice Fiscale > ";
    fflush(stdin);
    getline(cin, codice);
    cntrl_input(codice, "Inserisci Codice Fiscale > ");
    upper(codice);

    estr_dati(codice, cognome, nome, luogoNascita, annoNascita, giornoNascita, codiceCatastale, meseNascita, char_cntrl); // Estrazione dati

    string comuneNascita, sessoC, dataNascita, codice2;
    comuneNascita = ricerca_comune("./src/DB_comuni_IT.txt", codiceCatastale);
    sessoC = estr_sesso(giornoNascita);
    // cntrl_giornoNascita(giornoNascita, sessoC);
    aggiungi_anno(annoNascita, sessoC);
    codice2 = codice.substr(0, 15);
    char_cntrl2 = cntrl_char(codice2);

    dataNascita = giornoNascita + " " + estr_mese(meseNascita) + " " + annoNascita;

    cl();
    card(codice, codice2, cognome, nome, sessoC, dataNascita, giornoNascita, meseNascita, annoNascita, comuneNascita, char_cntrl, char_cntrl2);

    return 0;
}

/*================================ INZIO FUNZIONI ==============================*/

void upper(string &str)
{
    /**----------------------
     **   upper
     *? Trasforma l'intera stringa in maiuscolo
     *@param &str string
     *@return void
     *------------------------**/

    int tot, j = 0;
    for (int i = 0; i < str.size(); i++, j++)
    {
        tot = str[i] - 32;
        if (tot <= 64)
            str[j] = str[i];
        else
            str[j] = tot;
    }
}

void slp(int s)
{
    /**----------------------------------------------
     **              sleep
     *?  Sleep
     *@param s int
     *@return void
     *---------------------------------------------**/

#ifdef _WIN32
    s *= 2000;
    Sleep(s);
#elif defined __APPLE__
    sleep(s);
#endif
}

void estr_dati(string codice, string &cognome, string &nome, string &luogoNascita, string &annoNascita, string &giornoNascita, string &codCatastale, string &meseNascita, string &char_cntrl)
{
    /**------------------------------------------------------------------------
     **                           estr_dati
     *?  Estrazione dati date le stringhe
     *@param codice, &congome, &nome, &luogoNascita, &giornoNascita, &codCatastale, &meseNascita, &char_cntrl string
     *@return void
     *------------------------------------------------------------------------**/
    string an;
    cognome = codice.substr(0, 3);
    nome = codice.substr(3, 3);
    annoNascita = codice.substr(6, 2);
    meseNascita = codice.substr(8, 1);
    giornoNascita = codice.substr(9, 2);
    codCatastale = codice.substr(11, 4);
    char_cntrl = codice.substr(15, 1);
}

string estr_sesso(string giornoNascita)
{
    /**----------------------
     **   estr_sessp
     *? Dato il giorno di nascita estrae il sesso
     *@param giornoNascita string
     *@return string
     *------------------------**/

    string ret;
    int giorno = stoi(giornoNascita);
    if (giorno >= 41)
        ret = "DONNA";
    else
        ret = "UOMO";
    return ret;
}

/*================================ CONTROLLI ==============================*/

void cntrl_input(string &input, string out)
{
    /**------------------------------------------------------------------------
     **                           cntrl_input
     *? Controlla se c'e' stato un input dall utente
     *@param &input, out string
     *@return void
     *------------------------------------------------------------------------**/
    while (input.empty())
    {
#ifdef _WIN32
        set_console_color(12);
        cout << bold_on << "[ERROR 001] Non e' stato rilevato alcun input!\n"
             << bold_off;
        set_console_color(7);
#elif defined __APPLE__
        cout << color(RED, BOLD, "[ERROR 001] Non e' stato rilevato alcun input!\n");
#endif
        cout << out;
        fflush(stdin);
        getline(cin, input);
    }

    while (input.size() <= 15) // Controlla la lunghezza della stringa
    {
#ifdef _WIN32
        set_console_color(12);
        if (input.empty()) // Casi di Errori
        {
            cout << bold_on << "[ERROR 001] Non e' stato rilevato alcun input!\n"
                 << bold_off;
        }
        else
        {
            cout << bold_on << "[ERROR 002] Codice Incompleto!\n"
                 << bold_off;
        }
        set_console_color(7);
#elif defined __APPLE__
        if (input.empty()) // Casi di Errori
            cout << color(RED, BOLD, "[ERROR 001] Non e' stato rilevato alcun input!\n");
        else
            cout << color(RED, BOLD, "[ERROR 002] Codice Incompleto!\n");

#endif
        cout << out;
        fflush(stdin);
        getline(cin, input);
    }
}

char cntrl_char(string codice)
{
    /**----------------------------------------------
     **              carattere_cntrl
     *?  Calcolo del carattere di controllo
     *@param codice string
     *@return char
     *---------------------------------------------**/

    int tot = 0, r;
    char l;

    for (int i = 0; i < codice.size(); i += 2)
    {
        tot += carattere_dispari(codice[i]); // Caratteri in posizione dispari
    }

    for (int i = 1; i < codice.size(); i += 2)
    {
        tot += carattere_pari(codice[i]); // Caratteri in posizione pari
    }

    r = tot % 26; // Calcolo del resto

    switch (r)
    {
        // In base al resto calcolato verra restituito il carattere di controllo
    case 0:
        l = 'A';
        break;
    case 1:
        l = 'B';
        break;
    case 2:
        l = 'C';
        break;
    case 3:
        l = 'D';
        break;
    case 4:
        l = 'E';
        break;
    case 5:
        l = 'F';
        break;
    case 6:
        l = 'G';
        break;
    case 7:
        l = 'H';
        break;
    case 8:
        l = 'I';
        break;
    case 9:
        l = 'J';
        break;
    case 10:
        l = 'K';
        break;
    case 11:
        l = 'L';
        break;
    case 12:
        l = 'M';
        break;
    case 13:
        l = 'N';
        break;
    case 14:
        l = 'O';
        break;
    case 15:
        l = 'P';
        break;
    case 16:
        l = 'Q';
        break;
    case 17:
        l = 'R';
        break;
    case 18:
        l = 'S';
        break;
    case 19:
        l = 'T';
        break;
    case 20:
        l = 'U';
        break;
    case 21:
        l = 'V';
        break;
    case 22:
        l = 'W';
        break;
    case 23:
        l = 'X';
        break;
    case 24:
        l = 'Y';
        break;
    case 25:
        l = 'Z';
        break;
    }
    return l;
}

void cntrl_giornoNascita(string &giornoNascita, string &dataNascita, string &meseNascita, string &annoNascita, string sesso)
{
#ifdef _WIN32 //* Composizione nome file exe (WIN)
    string nome = nome_file() + ".exe";
#elif defined __APPLE__ //* Composizione nome file exe (MacOS)
    string nome = "./" + nome_file();
#endif
    int n = nome.size();
    char name_exe[n + 1];
    strcpy(name_exe, nome.c_str());

    int giorno = stoi(giornoNascita);
    const int time = 2;
    if (sesso == "DONNA")
    {
        if (giorno <= 71)
        {
            giorno -= 40;
            giornoNascita = to_string(giorno);
            dataNascita = giornoNascita + " " + estr_mese(meseNascita) + " " + annoNascita;
        }
        else
        {
#ifdef _WIN32
            set_console_color(12);
            cout << "[ERROR 004] GIORNO DI NASCITA NON VALIDO\n";
            set_console_color(7);
#elif defined __APPLE__
            cout << color(RED, BOLD, "[ERROR 004] GIORNO DI NASCITA NON VALIDO\n");
#endif
            cout.flush();
            cout << "Il programma verra' riavviato in " << time << " s\n";
            slp(time);
#ifdef _WIN32
            system(name_exe);
#elif defined __APPLE__
            system(name_exe); //! Riavvia il programma
#endif
        }
    }
    else
    {
        if (giorno >= 31 && giorno <= 40)
        {
#ifdef _WIN32
            set_console_color(12);
            cout << "[ERROR 004] GIORNO DI NASCITA NON VALIDO\n";
            set_console_color(7);
#elif defined __APPLE__
            cout << color(RED, BOLD, "[ERROR 004] GIORNO DI NASCITA NON VALIDO\n");
#endif
            cout.flush();
            cout << "Il programma verra' riavviato in " << time << " s\n";
            slp(time);
#ifdef _WIN32
            system(name_exe);
#elif defined __APPLE__
            system(name_exe); //! Riavvia il programma
#endif
        }
    }
}

string estr_mese(string meseNascita)
{
    /**------------------------------------------------------------------------
     **                           estr_mese
     *?  Data la lettere del mese ritorna il mese corrispondente
     *@param meseNascita string
     *@return string
     *------------------------------------------------------------------------**/

    string ret;
    switch (meseNascita[0])
    {
    case 'A':
        ret += "Gennaio";
        break;
    case 'B':
        ret += "Febbraio";
        break;
    case 'C':
        ret += "Marzo";
        break;
    case 'D':
        ret += "Aprile";
        break;
    case 'E':
        ret += "Maggio";
        break;
    case 'H':
        ret += "Giugno";
        break;
    case 'L':
        ret += "Luglio";
        break;
    case 'M':
        ret += "Agosto";
        break;
    case 'P':
        ret += "Settembre";
        break;
    case 'R':
        ret += "Ottobre";
        break;
    case 'S':
        ret += "Novembre";
        break;
    case 'T':
        ret += "Dicembre";
        break;
    }
    return ret;
}

/*=================================================================*/

string ricerca_comune(string path_file, string codiceCatastale)
{
    /**========================================================================
     **                           ricerca_comune
     *?  Dato il codice catastale restituisce il comunue di nascita
     *@param path_file, codiceCatastale string
     *@return string
     *========================================================================**/
    vector<string> record;
    ifstream file;
    file.open(path_file);
    bool found = false;

    string citta, cod, prv;
    while (getline(file, citta, ',') && !found)
    {
        getline(file, cod, ',');
        getline(file, prv, '\n');
        if (cod == codiceCatastale)
        {
            record.push_back(citta);
            record.push_back(cod);
            record.push_back(prv);
        }
    }
    return record[0];
}

string anno_corrente()
{
    /**----------------------------------------------
     **              anno_corrente
     *?  Restituisce l'anno corrente in cui siamo
     *@param void
     *@return string
     *---------------------------------------------**/

    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int r = 1900 + local_time->tm_year;
    string ret = to_string(r);
    ret = ret.substr(2, 2);
    return ret;
}

void aggiungi_anno(string &annoNascita, string sesso)
{
    /**----------------------------------------------
     **              aggiungi_anno
     *?  Aggiunge la cifra davanti all' anno di nascita
     *@param &annoNascita, sesso string
     *@return void
     *---------------------------------------------**/

    int anno = stoi(annoNascita);
    string ac = anno_corrente();
    int annCorrente = stoi(ac);

    if (anno <= annCorrente)
    {
        annoNascita = "20" + annoNascita;
    }

    else
        annoNascita = "19" + annoNascita;
}

int carattere_pari(char t)
{
    /**----------------------------------------------
     **              carattere_pari
     *?  Valori caratteri in posizione pari
     *@param t char
     *@return int
     *---------------------------------------------**/

    int conta = 0;
    switch (t)
    {
        // 48-57 numeri (0-9)
    case 48:
        conta += 0;
        break;
    case 'A':
        conta += 0;
        break;
    case 49:
        conta += 1;
        break;
    case 'B':
        conta += 1;
        break;
    case 50:
        conta += 2;
        break;
    case 'C':
        conta += 2;
        break;
    case 51:
        conta += 3;
        break;
    case 'D':
        conta += 3;
        break;
    case 52:
        conta += 4;
        break;
    case 'E':
        conta += 4;
        break;
    case 53:
        conta += 5;
        break;
    case 'F':
        conta += 5;
        break;
    case 54:
        conta += 6;
        break;
    case 'G':
        conta += 6;
        break;
    case 55:
        conta += 7;
        break;
    case 'H':
        conta += 7;
        break;
    case 56:
        conta += 8;
        break;
    case 'I':
        conta += 8;
        break;
    case 57:
        conta += 9;
        break;
    case 'J':
        conta += 9;
        break;
    case 'K':
        conta += 10;
        break;
    case 'L':
        conta += 11;
        break;
    case 'M':
        conta += 12;
        break;
    case 'N':
        conta += 13;
        break;
    case 'O':
        conta += 14;
        break;
    case 'P':
        conta += 15;
        break;
    case 'Q':
        conta += 16;
        break;
    case 'R':
        conta += 17;
        break;
    case 'S':
        conta += 18;
        break;
    case 'T':
        conta += 19;
        break;
    case 'U':
        conta += 20;
        break;
    case 'V':
        conta += 21;
        break;
    case 'W':
        conta += 22;
        break;
    case 'X':
        conta += 23;
        break;
    case 'Y':
        conta += 24;
        break;
    case 'Z':
        conta += 25;
        break;
    }
    return conta;
}

int carattere_dispari(char t)
{
    /**----------------------------------------------
     **              carattere_dispari
     *?  Valori caratteri in posizione dispari
     *@param t char
     *@return int
     *---------------------------------------------**/

    int conta = 0;
    switch (t)
    {
    case 48:
        conta += 1;
        break;
    case 'A':
        conta += 1;
        break;
    case 49:
        conta += 0;
        break;
    case 'B':
        conta += 0;
        break;
    case 50:
        conta += 5;
        break;
    case 'C':
        conta += 5;
        break;
    case 51:
        conta += 7;
        break;
    case 'D':
        conta += 7;
        break;
    case 52:
        conta += 9;
        break;
    case 'E':
        conta += 9;
        break;
    case 53:
        conta += 13;
        break;
    case 'F':
        conta += 13;
        break;
    case 54:
        conta += 15;
        break;
    case 'G':
        conta += 15;
        break;
    case 55:
        conta += 17;
        break;
    case 'H':
        conta += 17;
        break;
    case 56:
        conta += 19;
        break;
    case 'I':
        conta += 19;
        break;
    case 57:
        conta += 21;
        break;
    case 'J':
        conta += 21;
        break;
    case 'K':
        conta += 2;
        break;
    case 'L':
        conta += 4;
        break;
    case 'M':
        conta += 18;
        break;
    case 'N':
        conta += 20;
        break;
    case 'O':
        conta += 11;
        break;
    case 'P':
        conta += 3;
        break;
    case 'Q':
        conta += 6;
        break;
    case 'R':
        conta += 8;
        break;
    case 'S':
        conta += 12;
        break;
    case 'T':
        conta += 14;
        break;
    case 'U':
        conta += 16;
        break;
    case 'V':
        conta += 10;
        break;
    case 'W':
        conta += 22;
        break;
    case 'X':
        conta += 25;
        break;
    case 'Y':
        conta += 24;
        break;
    case 'Z':
        conta += 23;
        break;
    }
    return conta;
}

string nome_file()
{
    /**----------------------
     **   nome_file
     *@param void void
     *@return void
     *? Nome file corrente  
     *------------------------**/
    string name_file = __FILE__;
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

/*================== GRAFICA =================*/

void cl()
{
    /**----------------------
     **   cl
     *@param void void
     *@return void
     *? Pulisce la console x tutti i SO
     *------------------------**/

#ifdef _WIN32
    system("cls");
#elif defined(__APPLE__)
    system("clear");
#endif
}

#ifdef _WIN32

void set_console_color(int cl)
{
    /**----------------------
    ** set_console_color
    *? Colori x shell Win
    *@param cl int
    *@return void
    *------------------------**/

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cl);
}

void bandiera_italiana()
{
    /**----------------------
    ** bandiera_italiana
    *? Stampa banidiera italiana
    *@param void
    *@return void
    *------------------------**/

    char x = 219;
    string C = string(1, x);
    set_console_color(GREEN);
    cout << C;
    cout << C;
    cout << C;
    set_console_color(WHITE);
    cout << C;
    cout << C;
    cout << C;
    set_console_color(RED);
    cout << C;
    cout << C;
    cout << C;
    set_console_color(WHITE_OFF);
}

void size_shell(int h, int w) //! Ridimensiona shell data altezza e larghezza
{
    /**----------------------
    **   size_shell
    *? Ridimensionamento terminale Win
    *@param cl int
    *@return void
    *------------------------**/

    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, h, w, TRUE);
}
/*=============================================*/
#elif __APPLE__

void size_shell_MacOS(string h, string w) //! Ridimensiona shell data altezza e largehzza su UNIX
{
    /**----------------------
    **  size_shell_MacOS
    *? Ridimensionamento terminale MacOS
    *@param h e w string
    *@return void
    *------------------------**/

    cout.flush();
    cout << "\e[8;" + w + ";" + h + "t";
}
/**----------------------
 **   color
 *? Colori x shell MacOS
 *@param word, back e frase string or number
 *@return string
 *------------------------**/
string color(string word, string back, string frase)
{
    string tot = "\033[" + back + ";" + word + "m" + frase + "\033[0m";
    return tot;
}
string color(string word, string back, char frase)
{
    string frase2(1, frase);
    string tot = "\033[" + back + ";" + word + "m" + frase2 + "\033[0m";
    return tot;
}
string color(string word, string back, int num)
{
    string n = to_string(num);
    string tot = "\033[" + back + ";" + word + "m" + n + "\033[0m";
    return tot;
}
string color(string word, string back, float num)
{
    string n = to_string(num);
    string tot = "\033[" + back + ";" + word + "m" + n + "\033[0m";
    return tot;
}
#endif

void card(string codice, string codice2, string cognome, string nome, string sesso, string &dataNascita, string &giornoNascita, string &meseNascita, string &annoNascita, string luogoNascita, string char_cntrl, string char_cntrl2)
{
    /**========================================================================
     **                           card
     *?  Grafica x stampa finale
     *@param codice, nome, cognome, luogoNascita, dataNascita string
     *@param sesso char
     *@return void
     *========================================================================**/

    bool trv;
    error_char(codice2, char_cntrl, char_cntrl2, trv);

#ifdef _WIN32 // Windows code
    set_console_color(YELLOW);
    cout << bold_on << "NB: E' POSSIBBILE CHE DUE PERSONE ABBIANO LO STESSO CODICE FISCALE IN QUESTO CASO L'AGENZIA DELLE ENTRATE PROVVEDE A SOSTITUIRE ALCUNI CARATTERI\n"
         << bold_off;
    set_console_color(WHITE_OFF);
    cout << "-====================================================================-\n";
    cout << "====- ____          _ _            _____ _               _       -====\n";
    cout << "===- / ___|___   __| (_) ___ ___  |  ___(_)___  ___ __ _| | ___   ====\n";
    cout << "===-| |   / _ \\ / _` | |/ __/ _ \\ | |_  | / __|/ __/ _` | |/ _ \\  ";
    bandiera_italiana();
    cout << endl
         << "";
    cout << "===-| |__| (_) | (_| | | (_|  __/ |  _| | \\__ \\ (_| (_| | |  __/  ";
    bandiera_italiana();
    cout << endl;
    cout << "==== \\____\\___/ \\__,_|_|\\___\\___| |_|   |_|___/\\___\\__,_|_|\\___| ====\n ";
    cout << " ==================================================================== \n";
    cout << "|                                                                    |\n";
    cntrl_giornoNascita(giornoNascita, dataNascita, meseNascita, annoNascita, sesso);
    if (trv)
    {
        set_console_color(12);
        cout << "| \t"
             << "[ERROR 003] Il carattere di controllo e' errato!!" << setw(15) << "|" << endl;
        cout << "|\t\t" << bold_on << "CODICE ERRATO > " << bold_off;
        set_console_color(14);
        cout << codice << setw(22) << "|" << endl;
        cout << "|--------------------------------------------------------------------|\n";
        cout << "| \t\t" << bold_on << "CODICE CORRETTO > " << bold_off;
        set_console_color(11);
        cout << codice2 << setw(20) << "|" << endl;
        set_console_color(7);
        cout << "Preme un tasto per terminare...\n";
        cin.get();
    }
    else
    {
        set_console_color(10);
        cout << "| \t\t\t" << bold_on << codice << bold_off << setw(30) << "|" << endl;
    }
    set_console_color(7);
    cout << "| ------------------------------------------------------------------ |\n";
    set_console_color(15);
    cout << ".                                                                    .\n";
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| COGNOME: " << bold_on << cognome << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| NOME: " << bold_on << nome << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| SESSO: " << bold_on << sesso << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| LUOGO DI NASCITA: " << bold_on << luogoNascita << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| DATA DI NASCITA: " << bold_on << dataNascita << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| \n";
    cout << ".                                                                    .\n";
    cout << " =====================================================================\n";
#elif defined __APPLE__ // MacOs code

    cout << color(RED, BOLD, "NB: E' POSSIBBILE CHE DUE PERSONE ABBIANO LO STESSO CODICE FISCALE IN QUESTO CASO L'AGENZIA DELLE ENTRATE PROVVEDE A SOSTITUIRE ALCUNI CARATTERI\n");
    cout << "-====================================================================-\n";
    cout << "====- ____          _ _            _____ _               _       -====\n";
    cout << "===- / ___|___   __| (_) ___ ___  |  ___(_)___  ___ __ _| | ___   ====\n";
    cout << "===-| |   / _ \\ / _` | |/ __/ _ \\ | |_  | / __|/ __/ _` | |/ _ \\  ";
    cout << color(GREEN, "", "███") << color(WHITE, "", "███") << color(RED, "", "███\n");
    cout << "===-| |__| (_) | (_| | | (_|  __/ |  _| | \\__ \\ (_| (_| | |  __/  ";
    cout << color(GREEN, "", "███") << color(WHITE, "", "███") << color(RED, "", "███\n");
    cout << "==== \\____\\___/ \\__,_|_|\\___\\___| |_|   |_|___/\\___\\__,_|_|\\___|  ";
    cout << color(GREEN, "", "███") << color(WHITE, "", "███") << color(RED, "", "███\n");
    cout << " ==================================================================== \n";
    cout << "|                                                                    |\n";
    cntrl_giornoNascita(giornoNascita, dataNascita, meseNascita, annoNascita, sesso);
    if (trv)
    {
        cout << "| \t" << color(RED, BOLD, "[ERROR 003] Il carattere di controllo e' errato!!") << setw(15) << "|" << endl;
        cout << "|\t\t" << color(RED, BOLD, "CODICE ERRATO > ") << color(YELLOW, "", codice) << setw(22) << "|" << endl;
        cout << "|--------------------------------------------------------------------|\n";
        cout << "| \t\t" << color(GREEN, BOLD, "CODICE CORRETTO > ") << color(BLUE, "", codice2) << setw(20) << "|" << endl;
    }
    else
        cout << "| \t\t\t" << color(GREEN, BOLD, codice) << setw(30) << "|" << endl;
    cout << "| ------------------------------------------------------------------ |\n";
    cout << ".                                                                    .\n";
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| COGNOME: " << color(WHITE, BOLD, cognome) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| NOME: " << color(WHITE, BOLD, nome) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| SESSO: " << color(WHITE, BOLD, sesso) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| LUOGO DI NASCITA: " << color(WHITE, BOLD, luogoNascita) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| DATA DI NASCITA: " << color(WHITE, BOLD, dataNascita) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| \n";
    cout << ".                                                                    .\n";
    cout << " =====================================================================\n";
#endif
}

void error_char(string &codice, string char_cntrl, string char_cntrl2, bool &trv)
{
    /**========================================================================
     **                           error_char
     *?  Controlla se il carattere controllo nell codice inserito e' errato
     *@param &codice, char_cntrl, char_cntrl2 string
     *@param &trv bool
     *@return void
     *========================================================================**/

    if (char_cntrl != char_cntrl2)
    {
        codice += char_cntrl2;
        trv = true;
    }
    else
        trv = false;
}

void banner()
{
    /**------------------------------------------------------------------------
     **                           banner
     *?  Banner intestazione nome programma
     *@param void
     *@return void
     *------------------------------------------------------------------------**/

#ifdef _WIN32 //*Windows code
    set_console_color(10);
    cout << "   ____          _ _          _____ _               _\n";
    cout << "  / ___|___   __| (_) ___ ___|  ___(_)___  ___ __ _| | ___\n";
    set_console_color(15);
    cout << " | |   / _ \\ / _` | |/ __/ _ \\ |_  | / __|/ __/ _` | |/ _ \\ \n";
    cout << " | |__| (_) | (_| | | (_|  __/  _| | \\__ \\ (_| (_| | |  __/ \n";
    set_console_color(12);
    cout << "  \\____\\___/ \\__,_|_|\\___\\___|_|   |_|___/\\___\\__,_|_|\\___| \n";
    set_console_color(14);
    cout << endl;
    cout << "\t\t\tBy: Francesco Pio Nocerino\n\n";
    set_console_color(7);

#elif defined __APPLE__ //*MacOs code
    cout << color(GREEN, "", "  ____          _ _          _____ _               _\n");
    cout << color(GREEN, "", " / ___|___   __| (_) ___ ___|  ___(_)___  ___ __ _| | ___\n");
    cout << color(WHITE, "", "| |   / _ \\ / _` | |/ __/ _ \\ |_  | / __|/ __/ _` | |/ _ \\ \n");
    cout << color(WHITE, "", "| |__| (_) | (_| | | (_|  __/  _| | \\__ \\ (_| (_| | |  __/ \n");
    cout << color(RED, "", " \\____\\___/ \\__,_|_|\\___\\___|_|   |_|___/\\___\\__,_|_|\\___| \n");
    cout << endl;
    cout << color(YELLOW, BOLD, "\t\t\tBy:Francesco Pio Nocerino\n\n");
#endif
}
