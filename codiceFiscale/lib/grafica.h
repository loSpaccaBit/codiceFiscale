#ifndef A9EF67DA_93A6_4A07_A3B8_EBC8018B6A9F
#define A9EF67DA_93A6_4A07_A3B8_EBC8018B6A9F
/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   grafica.h
 *  Versione: 1.0
 *  Descrizione:
 * ? Libreria a scopo grafico
 *================================================================================================**/

#include <iostream>
using namespace std;

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

#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
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

/*==============================================================*/

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
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
//! overloading color
void size_shell_MacOS(string h, string w);            //* Ridimensiona shell
string color(string word, string back, string frase); //* Colori x MacOS
string color(string word, string back, char frase);
string color(string word, string back, int num);
string color(string word, string back, float num);
#endif
void card(string codice, string nome, string cognome, string lugoNascita, string dataNascita, char sesso); //* Grafica x stampa finale
void banner();                                                                                             //* Banner intestazione nome programma
void loading();

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
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
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
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)

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
#ifdef _WIN32 // Windows code
    set_console_color(YELLOW);
    cout << bold_on << "NB: E' POSSIBILE CHE DUE PERSONE ABBIANO LO STESSO CODICE FISCALE IN QUESTO CASO L'AGENZIA DELLE ENTRATE PROVVEDE A SOSTITUIRE ALCUNI CARATTERI\n"
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
    set_console_color(GREEN);
    cout << "| \t\t\t" << bold_on << codice << bold_off << endl;
    cout << "| ------------------------------------------------------------------ |\n";
    set_console_color(WHITE);
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
    cout << "> Preme un tasto per terminare...\n";
    cin.get();
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)

    cout << color(RED, BOLD, "NB: E' POSSIBILE CHE DUE PERSONE ABBIANO LO STESSO CODICE FISCALE IN QUESTO CASO L'AGENZIA DELLE ENTRATE PROVVEDE A SOSTITUIRE ALCUNI CARATTERI\n");
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
    set_console_color(GREEN);
    cout << "   ____          _ _          _____ _               _\n";
    cout << "  / ___|___   __| (_) ___ ___|  ___(_)___  ___ __ _| | ___\n";
    set_console_color(WHITE_OFF);
    cout << " | |   / _ \\ / _` | |/ __/ _ \\ |_  | / __|/ __/ _` | |/ _ \\ \n";
    cout << " | |__| (_) | (_| | | (_|  __/  _| | \\__ \\ (_| (_| | |  __/ \n";
    set_console_color(RED);
    cout << "  \\____\\___/ \\__,_|_|\\___\\___|_|   |_|___/\\___\\__,_|_|\\___| \n";
    set_console_color(YELLOW);
    cout << endl;
    cout << "\t\t\tBy: Francesco Pio Nocerino\n\n";
    set_console_color(WHITE_OFF);

#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
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
     *?  Schermata di caricamento (solo x uso grafico)
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

#endif /* A9EF67DA_93A6_4A07_A3B8_EBC8018B6A9F */
