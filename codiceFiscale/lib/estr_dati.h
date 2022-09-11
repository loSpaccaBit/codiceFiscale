#ifndef C6103DE1_415E_4C06_997C_49F3AC00080C
#define C6103DE1_415E_4C06_997C_49F3AC00080C
/**================================================================================================
 * *                                           INFO
 *  Autore: Francesco Pio Nocerino
 *  @site:  https://github.com/KekkoDev/codiceFiscale/wiki
 *  @email: nocerpio9@gmail.com
 *  File:   estr_dati.h
 *  Versione: 1.0
 *  Descrizione:
 * ? Libreria impiegata nell'estrazione dei dovuti dati passati dall'utente
 *================================================================================================**/
#include <iostream>
#include <string>
using namespace std;

string consonanti(string str, int &ind);                               // Archivio consonanti
string vocali(string str);                                             // Archivio vocali
string estr_nome(string nome);                                         // Estrazione lettere dal nome
string estr_cognome(string congnome);                                  // Estrazione lettere dal cognome
void estr_data(string data, char sesso, string &giorno, string &anno); // Estrazione data giorno-anno

/*==============================================================*/

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
    con = consonanti(nome, conta); // Controlla i caratteri che sono consonanti
    v = vocali(nome);              // Controlla i caratteri che sono vocali
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
     *?  Estrae i caratteri dal cognome x la composizione del codice
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
    if (sesso == 'F') // Se l'utente e di sesso femminile al giorno di nascita deve essere aggiunto 40
    {
        int x = stoi(giorno);
        x += 40;
        giorno.clear();
        giorno.append(to_string(x));
    }
}

#endif /* C6103DE1_415E_4C06_997C_49F3AC00080C */
