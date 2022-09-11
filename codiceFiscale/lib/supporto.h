#ifndef F547B775_DD55_4742_AA0C_5D2270319D10
#define F547B775_DD55_4742_AA0C_5D2270319D10
/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   supporto.h
 *  Versione: 1.0
 *  Descrizione:
 * ? Libreria di supporto alle altre
 *================================================================================================**/
#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <unistd.h>
#endif

#include <iostream>
#include <string>
using namespace std;

int annoCorrente(); // Restituisce l'anno corrente
void slp(int d);
void upper(string &str);             // Trasforma in Maiuscolo la stringa
void upper_Char(char &c);            // Trasforma in Maiuscolo il carattere
char lettera_mese(string data);      // Dato il mese di nascita viene restituita la lettere corrispondente al mese
char carattere_cntrl(string codice); // Carattere di controllo
int carattere_pari(char t);          // Valori caratteri in posizione pari
int carattere_dispari(char t);       // Valori caratteri in posizione dispari

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
    d *= 2000;
    Sleep(d);
#elif defined(__APPLE__) || defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
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

char lettera_mese(string data)
{
    /**----------------------------------------------
     **              lettere_mese
     *?  Ogni mese corrisponde ad un carattere, verrà restituito il carattere in base al mese dato
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
        // In base al resto calcolato verrà restituito il carattere di controllo
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

#endif /* F547B775_DD55_4742_AA0C_5D2270319D10 */
