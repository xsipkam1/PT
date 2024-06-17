/*
Meno a priezvisko: Michal Šípka

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <climits>
#include <string.h>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Pozicia v rovine
struct Position {
    int x; // x-ova suradnica
    int y; // y-ova suradnica
};

// Datum
struct Date {
    int year;  // rok
    int month; // mesiac
    int day;   // den
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia na standardny vystup vytlaci udaje v strukture.
    V implementacii musi byt pouzity 'std::cout'.

    Format tlace musi byt podla nasledujucich prikladov. Bez odriadkovania. Bez uvodzoviek. Dodrzte pouzitie medzier.
    Priklady:
        "x: 10, y: 20"
        "x: -12345, y: 2"

    PARAMETER:
        [in] position - pozicia, ktora bude vytlacena
*/
void print(const Position *position) {
    std::cout << "x: " << position->x << ", y: "<< position->y;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Implementujte rovnaku funkcionalitu ako v prvom priklade. Rozdiel je len typ parametra funkcie.
*/

void print(const Position &position) {
    std::cout << "x: " << position.x << ", y: "<< position.y;
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zo standardneho vstupu nacita postupne dve cisla. Ulozi ich ako x-ovu a y-ovu zlozku pozicie 'position'.
    V implementacii musi byt pouzity 'std::cin' a formatovany vstup.

    PARAMETER:
        - [out] position - pozicia, ktorej hodnoty sa nastavia podla udajov zo standardneho vstupu.

    VSTUPNE PODMIENKY:
        Text zadany na standardny vstup obsahuje dve cele cisla, ktore mozno reprezetovat typom 'int'.
        Nemusite osetrovat moznost chybnych udajov na standardnom vstupe.
 */
void readFromStandardInput(Position *position) {
    int x=0,y=0;
    std::cin>>x;
    std::cin>>y;
    position->x=x;
    position->y=y;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najvacsiu hodnotu prvku pola 'data' a nastavi 'result' podla uspesnosti hladania.

    Ak pole obsahuje prvky, tak vrati ich maximum a nastavi 'result' na 'SUCCESS'.
    Ak pole neobsahuje ziadne prvky (jeho dlzka je nulova),
    tak vrati minimalnu hodnotu, ktoru moze reprezentovat datovy typ 'int' a nastavi result na 'FAILURE'.

    PARAMETRE:
        [in] data    - adresa zaciatku pola
        [in] length  - pocet prvkov pola (dlzka pola)
        [out] result - indikuje uspesnost najdena maxima

    NAVRATOVA HODNOTA:
        Ak pole obsahuje prvky, tak vrati hodnotu najvacsieho prvku pola 'data'.
        Ak pole neobsahuje prvky, tak vrati minimalnu hodnotu reprezentovatelnu datovym typom 'int'.

    PRIKLADY:
        vstup: (1, 2, 5, 0, 1) => navratova hodnota: 5,  result: 'Result::SUCCESS'
        vstup: (-5, -2, -10)   => navratova hodnota: -2, result: 'Result::SUCCESS'
        vstup: () => navratova hodnota: minimalna hodnota reprezentovatelna datovym typom 'int', result: 'Result::FAILURE'
*/
int maximum(const int *data, std::size_t length, Result *result) {
    if(length==0){
        *result=Result::FAILURE;
        return INT_MIN;
    }
    else{
        int max=data[0];
        for(std::size_t i=0; i<length; i++){
            if(data[i]>max){
                max=data[i];
            }
        }
        *result=Result::SUCCESS;
        return max;
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet znakov, ktore su potrebne na zapis cisla 'value' (v desiatkovej ciselnej sustave).

    PARAMETER:
        - [in] value - analyzovana hodnota

    NAVRATOVA HODNOTA:
        Pocet znakov, potrebnych pre textovu reprezentaciu hodnoty 'value'

    PRIKLADY:
        - vstup: 18002 => vystup: 5
        - vstup: 2     => vystup: 1
        - vstup: 0     => vystup: 1
        - vstup: -500  => vystup: 4
*/
int numDigits(int value) {
    int poc;
    int temp=value;
    if(value<=0) {
        if(value==INT_MIN) value++;
        value=-value;
    }
    for((temp<=0) ? poc=1 : poc = 0; value>0; poc++){
        value = value / 10;
    }
    return poc;
    /*
    std::string x=std::to_string(value);
    return x.length();
    */
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytlaci na standardny vystup datum, podla zadaneho formatu.

    Vytlaceny text bude obsahovat kopiu textu vo 'format', ale
    znak 'D' nahradi dnom,
    znak 'M' nahradi mesiacom,
    znak 'Y' nahradi rokom v datume.

    PARAMETRE:
        - [in] date - datum
        - [in] format - format vylacenia datumu

    PRIKLADY:
        Nech datum je 10. aprila 2020
        - format: "D. M. Y" => "10. 4. 2020"
        - format: "D. M."   => "10. 4."
        - format: "Pisomka bude D. M. Y, v miestnosti BC 300" => "Pisomka bude 10. 4. 2020, v miestnosti BC 300"
        - format: "M/D/Y"   => "4/10/2020"
        - format: "Y-M-D"   => "2020-4-10"

    POZNAMKA:
        Vsimnite si pretazenie funkcie. Tento zdrojovy subor obsahuje 3 funkcie s nazvom 'print'.
*/
void print(const Date *date, const char *format) {
    for(std::size_t i=0; i<strlen(format); i++){
        if(format[i]=='D'){
            std::cout<<date->day;
        }
        else if(format[i]=='M'){
            std::cout<<date->month;
        }
        else if(format[i]=='Y'){
            std::cout<<date->year;
        }
        else std::cout<<format[i];
    }
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy datum podla parametrov a vrati jeho adresu.
    Pre dynamicku alokaciu pamate pouzite operator 'new'.

    PARAMETRE:
        [in] day   - den v datume
        [in] month - mesiac v datume
        [in] year  - rok v datume

    NAVRATOVA HODNOTA:
        Adresa na dynamicky alokovany datum, ktoreho obsah je dany parametrami
*/
Date* create(int day, int month, int year) {
    Date* datum = new Date;
    datum->day = day;
    datum->month = month;
    datum->year = year;
    return datum; 
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia dealokuje datum. Smernik na datum nastavi na 'nullptr'.
    Na dealokaciu pamate pouzite operator 'delete'.

    PARAMETER:
        [in, out] date - adresa smernika na datum

    VYSTUPNE PODMIENKY:
        Datum na adrese (*date) je dealokovany.
        (*date) ma hodnotu 'nullptr'.
*/
void destroy(Date **date) {
    delete *date;
    *date=nullptr;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci je rok v datume priestupny.

    PARAMETER:
        [in] date - datum

    NAVRATOVA HODNOTA:
        'true'  - ak rok je priestupny
        'false' - ak rok nie je priestupny

    VSTUPNA PODMIENKA:
        Rok v datume je kladne cislo

    URCENIE PRIESTUPNEHO ROKU:
        Rok delitelny cislom 4 je priestupny okrem pripadu, ked je delitelny cislom 100, ale nie je delitelny cislom 400.
        Priklady:
            - priestupne roky: 2000, 2004, 2008
            - nepriestupne roky: 2001, 2002, 2003, 2005, 2006, 2007, 2009, 2010
            - priestupne roky: 1600, 2000, 2400
            - nepriestupne roky: 1500, 1700, 1800, 1900, 2100, 2200, 2300, 2500
*/
bool isInLeapYear(const Date *date) {
    if(date->year>0 && date->year%4==0 && (date->year%100!=0 || date->year%400==0)){
        return true;
    }
    return false; 
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci je datum platny.

    Treba overit, ci datum moze existovat. Napriklad
    v januari moze byt den od 1 do 31,
    vo februari od 1 do 28 alebo 29, podla toho, ci je rok priestupny.
    Rok ma mesiac 1 az 12.

    PARAMETER:
        [in] date - datum

    NAVRATOVA HODNOTA:
        'true'  - ak datum je platny
        'false' - ak datum nie je platny

    VSTUPNA PODMIENKA:
        Rok v datume je kladne cislo
*/
bool isValid(const Date *date) {
    if(date->year>0 && date->month>0 && date->month<=12){
        if(date->month==1 || date->month==3 || date->month==5 || date->month==7 || date->month==8 || date->month==10 || date->month==12){
            if(date->day>0 && date->day<=31) return true;
        }
        else if(date->month==4 || date->month==6 || date->month==9 || date->month==11){
            if(date->day>0 && date->day<=30) return true;
        }
        else{
            if(isInLeapYear(date)&&date->day>0&&date->day<=29) return true;
            else if(!isInLeapYear(date)&&date->day>0&&date->day<=28) return true;
        }
    }
    return false; 
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    /*
    Position p;
    p.x=20;
    p.y=10;
    */
    //print(&p);    //1

    //print(p);     //2

    //readFromStandardInput(&p); //3
    //print(&p);

    //std::cout<<numDigits(2000000000);  //5

    //4
    /*
    Result r;
    const int pole[]={2};
    std::cout<<maximum(pole, 1, &r);
    */

    //6
    
    //Date date;
    //date.day=31;
    //date.month=5;
    //date.year=2022;
    //print(&date, "M/D/Y");

    //7
    //Date* datum = create(1,2,3);
    //std::cout<<create(1,2,3)<<std::hex; 

    //std::cout<<isInLeapYear(&date);
    //std::cout<<isValid(&date);
    
    /*
    Date* datum = new Date;
    datum->day=31;
    datum->month=5;
    datum->year=2022;
    destroy(&datum);
    std::cout<<datum<<std::endl;
    */
    return 0;
}
