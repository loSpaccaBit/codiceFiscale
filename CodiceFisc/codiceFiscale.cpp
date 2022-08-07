/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   codiceFiscale.cpp
 *  Versine: 1.3
 *  Descrizione:
 * ? Calcolo del CodiceFiscale inserendo le proprie generalita l'algoritmo calcolera' il codice
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
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
using namespace std;

/*================================ LISTA ERRORI ==============================*/
/**
 * ERROR 001 -> STRINGA VUOTA
 * ERROR 002 -> SESSO NON VALIDO
 * ERROR 003 -> DATA DI NASCITA NON VALIDA
 * CODICE COMUNE NON TROVATO -> MacOS -> segmentation fault error compiler
 */

/*================================ INZIO PROTOTIPI ==============================*/

void dati(string &dato, string out); // Inserimento dati

/*================== DIVISION =================*/

int annoCorrente(); // Restituisce l'anno corrente
void slp(int d);
void upper(string &str);                            // Trasforma in Maiuscolo la stringa
void upper_Char(char &c);                           // Trasforma in Maiuscolo il carattere
string codiceComune(string nome_file, string &key); //Codice catastale del luogo di nascita
char lettera_mese(string data);                     //Dato il mese di nascita viene restituita la lettere corrispondente al mese
char carattere_cntrl(string codice);                //Carattere di controllo
int carattere_pari(char t);
int carattere_dispari(char t);

/*================== CONTROLLI INPUT =================*/

void cntrl_dati(string &input, string out);  //Controlo inserimento stringa
void cntrl_sesso(char &sesso);               // Controllo inserimento sesso
void cntrl_dataNascita(string &dataNascita); // Controllo inserimento data di nascita

/*================== ESTRAZIONE DATI =================*/

string consonanti(string str, int &ind);                               // Archivio consonanti
string vocali(string str);                                             // Archivio vocali
string estr_nome(string nome);                                         // Estrazione lettere dal nome
string estr_cognome(string congnome);                                  // Estrazione lettere dal congome
void estr_data(string data, char sesso, string &giorno, string &anno); // Estrazione data giorno-anno

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
void card(string codice, string nome, string cognome, string lugoNascita, string dataNascita, char sesso); //* Grafica x stampa finale
void banner();                                                                                             //* Banner intestazione nome programma
void loading();                                                                                            //* Schermata di caricamento

/*================================ FINE PROTOTIPI ==============================*/

int main()
{

#ifdef _WIN32 // Ridimensionamento console
    size_shell(800, 600);
#elif __APPLE__
    size_shell_MacOS("107", "28");
#endif
    string nome, cognome, dataNascita, luogoNascita;
    char sesso, c;
    cl();
    banner();

    //* Cognome
    dati(cognome, "Inserisci Cognome > ");
    cntrl_dati(cognome, "Inserisci Cognome > ");
    upper(cognome);
    cout << "----------------------------------\n";

    //* Nome
    dati(nome, "Inserisci Nome > ");
    cntrl_dati(nome, "Inserisci Nome > ");
    upper(nome);
    cout << "----------------------------------\n";

    //* Sesso
    cout << "Inserisci Sesso > ";
    cin >> sesso;
    cntrl_sesso(sesso);
    upper_Char(sesso);
    cout << "----------------------------------\n";

    //* Data di Nascita
    dati(dataNascita, "Inserisci Data di Nascita > ");
    cntrl_dati(dataNascita, "Inserisci Data di Nascita > ");
    cntrl_dataNascita(dataNascita); //? Controllo validita data
    cout << "----------------------------------\n";

    //* Luogo Nascita
    dati(luogoNascita, "Inserisci Luogo di Nascita > ");
    cntrl_dati(luogoNascita, "Inserisci Luogo di Nascita > ");
    upper(luogoNascita);
    cout << "----------------------------------\n";

    string giorno, anno;
    estr_data(dataNascita, sesso, giorno, anno);

    string codice_calcolato;
    // Calcolo de codice
    codice_calcolato = estr_cognome(cognome) + estr_nome(nome) + anno + lettera_mese(dataNascita) + giorno + codiceComune("./src/DB_comuni_IT.txt", luogoNascita);
    codice_calcolato += carattere_cntrl(codice_calcolato);

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
/*================== DIVISION =================*/

int annoCorrente()
{
    /**----------------------
     **   annoCorrente
     *? Restituisce l'anno attuale
     *@param void
     *@return void
     *------------------------**/

    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);

    int anno = 1900 + local_time->tm_year;
    return anno;
}

void slp(int d)
{
    /**----------------------
     **   slp
     *? Funzione sleep
     *@param d int  
     *@return void
     *------------------------**/
#ifdef _WIN32
    Sleep(d);
#elif defined __APPLE__
    sleep(d);
#endif
}

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

void upper_Char(char &c)
{
    /**----------------------
     **   upper_Char
     *? Trasforma un carattere in maiuscolo
     *@param void
     *@return void
     *------------------------**/
    if (c >= 65 && c <= 90)
        c = c;
    else
        c -= 32;
}

string codiceComune(string nome_file, string &key)
{
    /**------------------------------------------------------------------------
     **                           codiceComune
     *?  Ritorna il codice catastale del comune
     *@param nome_file, &key string
     *@return string
     *------------------------------------------------------------------------**/
    vector<string> record;
    ifstream file;
    file.open(nome_file);
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

    return record[1];
}

char lettera_mese(string data)
{
    /**----------------------------------------------
     **              lettere_mese
     *?  Ogni mese corrisponde ad un carattere, verra restiruito il carattere in base al mese dato
     *@param data string
     *@return char
     *---------------------------------------------**/
    string mesi = "ABCDEHLMPRST", m;
    m += data.substr(3, 2);
    int ms = stoi(m);
    ms--;
    return mesi[ms];
}

char carattere_cntrl(string codice)
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
        //48-57 numeri (0-9)
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

/*================== CONTROLLI =================*/

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
            trv = true;
        }
        else
            trv = false;
    } while (trv);
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
            set_console_color(12);
            cout << bold_on << "[ERROR 002] Il sesso inserito non e' valido!!\n"
                 << bold_off;
            set_console_color(7);
#elif defined __APPLE__
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
            set_console_color(12);
            cout << bold_on << "[ERROR 003] Data di Nascita non valida!!\n"
                 << bold_off;
            set_console_color(7);
#elif defined __APPLE__
            cout << color(RED, BOLD, "[ERROR 003] Data di Nascita non valida!!\n");
#endif
            cout << "Inserisci Data di Nascita > ";
            fflush(stdin);
            getline(cin, dataNascita);
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
            set_console_color(12);
            cout << bold_on << "[ERROR 003] Data di Nascita non valida\n"
                 << bold_off;
            set_console_color(7);
#elif defined __APPLE__
            cout << color(RED, BOLD, "[ERROR 003] Data di nascita non valida\n");
#endif
            cout << "Inserisci data di nascita > ";
            fflush(stdin);
            getline(cin, dataNascita);

            annoIns = dataNascita.substr(6, 4);
            meseIns = dataNascita.substr(3, 2);
            giornoIns = dataNascita.substr(0, 2);

            annoI = stoi(annoIns);
            meseI = stoi(meseIns);
            giornoI = stoi(giornoIns);
        }
    } while (!t);
}

/*================== ESTRAZIONE DATI =================*/

string consonanti(string str, int &ind)
{
    /**----------------------------------------------
     **              consonanti
     *?  Archivio consonanti
     *@param str string
     *@param &ind int
     *@return string
     *---------------------------------------------**/

    string cons = "BCDFGHLMNPQRSTVZ", valide;
    for (int i = 0; i < str.size(); i++)
    {
        for (int j = 0; j < cons.size(); j++)
        {
            if (str[i] == cons[j])
            {
                valide += str[i];
                ind++;
            }
        }
    }
    return valide;
}

string vocali(string str)
{
    /**----------------------------------------------
     **              vocali
     *?  Archivio vocali
     *@param str string
     *@return string
     *---------------------------------------------**/

    string vc = "AEIOU", vocal;
    for (int i = 0; i < str.size(); i++)
    {
        for (int j = 0; j < vc.size(); j++)
        {
            if (str[i] == vc[j])
            {
                vocal += vc[j];
            }
        }
    }
    return vocal;
}

string estr_nome(string nome)
{
    /**----------------------------------------------
     **              estr_nome
     *?  Estre i caratteri dal nome x la composizione del codice
     *@param nome string
     *@return string
     *---------------------------------------------**/

    string trv, con, v;
    int conta = 0, calc;
    con = consonanti(nome, conta); //Controlla i caratteri che sono consonati
    v = vocali(nome);              //Controlla i caratteri che sono vocali
    if (conta <= 2)
    {
        trv += con.substr(0, 2);
    }
    if (conta == 3)
    {
        trv += con.substr(0, 3);
    }
    if (conta > 3)
    {
        trv += con.substr(0, 1);
        trv += con.substr(2, 2);
    }

    calc = trv.size();
    if (calc < 3)
    {
        calc = 3 - calc;
        trv += v.substr(0, calc);
    }

    return trv;
}

string estr_cognome(string cognome)
{
    /**----------------------------------------------
     **              estr_cognome
     *?  Estre i caratteri dal cognome x la composizione del codice
     *@param cognome string
     *@return string
     *---------------------------------------------**/

    string trv, con, v;
    int conta = 0, calc;
    con = consonanti(cognome, conta);
    v = vocali(cognome);
    if (conta <= 2)
    {
        trv += con.substr(0, 2);
    }
    if (conta >= 3)
    {
        trv += con.substr(0, 3);
    }
    calc = trv.size();
    if (calc < 3)
    {
        calc = 3 - calc;
        trv += v.substr(0, calc);
    }
    return trv;
}

void estr_data(string data, char sesso, string &giorno, string &anno)
{
    /**----------------------------------------------
     **              estr_data
     *?  Estre la data di nascita
     *@param data, &giorno, &anno string
     *@param sesso char
     *@return void
     *---------------------------------------------**/

    anno = data.substr(8, 2);
    giorno = data.substr(0, 2);
    if (sesso == 'F') //Se l'utente e di sesso femminile al giorno di nascita deve essere aggiunto 40
    {
        int x = stoi(giorno);
        x += 40;
        giorno.clear();
        giorno.append(to_string(x));
    }
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

void card(string codice, string nome, string cognome, string lugoNascita, string dataNascita, char sesso)
{
    /**========================================================================
     **                           card
     *?  Grafica x stampa finale
     *@param codice, nome, cognome, luogoNascita, dataNascita string
     *@param sesso char
     *@return void
     *========================================================================**/
#ifdef _WIN32 //Windows code
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
    set_console_color(10);
    cout << "| \t\t\t" << bold_on << codice << bold_off << endl;
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
    cout << "| LUOGO DI NASCITA: " << bold_on << lugoNascita << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| DATA DI NASCITA: " << bold_on << dataNascita << bold_off << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| \n";
    cout << ".                                                                    .\n";
    cout << " =====================================================================\n";
#elif defined __APPLE__ //MacOs code

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
    cout << "| \t\t\t" << color(GREEN, BOLD, codice) << endl;
    cout << "| ------------------------------------------------------------------ |\n";
    cout << ".                                                                    .\n";
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| COGNOME: " << color(WHITE, BOLD, cognome) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| NOME: " << color(WHITE, BOLD, nome) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| SESSO: " << color(WHITE, BOLD, sesso) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| LUOGO DI NASCITA: " << color(WHITE, BOLD, lugoNascita) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| DATA DI NASCITA: " << color(WHITE, BOLD, dataNascita) << endl;
    cout << "| ------------------------------------------------------------------|\n";
    cout << "| \n";
    cout << ".                                                                    .\n";
    cout << " =====================================================================\n";
#endif
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
    cout << "\t\t\tBy: Francesco Pio Nocerino\n";
    set_conosle_color(7);

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

void loading()
{
    /**----------------------------------------------
     **              loading
     *?  Schermata di carcamento (solo x uso grafico)
     *@param void  
     *@return void
     *---------------------------------------------**/
    cl();

    const int time = 4, time1 = 1, time2 = 2;
    int conta = 1;

    cout << "CALCOLO IN CORSO\n";
    cout << "[";

    while (conta <= time)
    {
        cout.flush();
        cout << "=============";
        slp(time1);
        conta++;
    }

    cout << "]";
    cout << endl;

    slp(time2);
    cl();
}

/*=========================================== FINE PROGRAMMA ===========================================*/
