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

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Hmotnost produktu a obalu. Hmotnost zabaleneho produktu je suctom obidvoch zloziek
struct Weight {
    int product; // hmotnost produktu
    int packing; // hmotnost balenia
};
void swap(int& a, int& b);
void printArray(int *array, const size_t length);
//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data', od najvacsieho prvku po najmensi.
    Pouzite algoritmus bubble sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNA PODMIENKA:
        ak 'length' > 0, tak 'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/
void bubbleSort(int *data, const size_t length) {
    for(std::size_t i=0; i<length; i++){
        for(std::size_t j=0; j<length-i-1; j++){
            if(data[j]<data[j+1]){
                swap(data[j], data[j+1]);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' podla celkovej hmotnosti zabaleneho tovaru, t.j. podla suctu zloziek ('product' a 'packing').
    Poradie usporiadania je od najtazsieho zabaleneho tovaru po najlahsi zabaleny tovar.
    Pouzite algoritmus bubble sort.

    Podmienka porovnania struktur:
    Pri porovnavani prvkov funkcia scita hodnoty 'product' a 'packing' oboch porovnavanych struktur.
    Struktury s vacsim suctom zloziek budu po usporiadani pred strukturami s mensim suctom zloziek.

    Vzajomne usporiadanie struktur s rovnakym suctom poloziek:
    Pri bodovom hodnoteni nezalezi na vzajomnom usporiadani struktur s rovnakym suctom poloziek (aj ked hodnoty poloziek mozu byt rozne).
    Lepsie je vsak implementovat stabilne triedenie (struktury s rovnakym suctom poloziek nemenia vzajomne usporiadanie).

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNA PODMIENKA:
        ak 'length' > 0, tak 'data' ukazuje na platne pole

    PRIKLADY:
        ((10, 1), (20, 2), (5, 2)) -> ((20, 2), (10, 1), (5, 2)) pretoze 20+2=22, 10+1=11, 5+2=7 a 22 > 11 > 7
        ((11, 1), (2, 1), (10, 2), (15, 7)) -> ((15, 7), (11, 1), (10, 2), (2, 1))
        () -> ()

    POZNAMKA:
        Priklady jednoducheho vytvorenia pola v testovacom kode:
        Weight baliky[] = {{10, 1}, {20, 2}, {5,2}};
        Weight baliky[] = {{.product = 10, .packing = 1}, {.product = 20, .packing = 2}, {.product = 5, .packing = 2}}; // od C++ 20
*/
void bubbleSort(Weight *data, const size_t length) {
    for(std::size_t i=0; i<length; i++){
        //std::cout<<data[i].product<<"+"<<data[i].packing<<"="<<data[i].product+data[i].packing<<std::endl;    
        for(std::size_t j=0; j<length-i-1; j++){
            if((data[j].product+data[j].packing)<(data[j+1].product+data[j+1].packing)){
                /*
                int temp_product=data[j].product;
                int temp_packing=data[j].packing;
                data[j].product=data[j+1].product;
                data[j].packing=data[j+1].packing;
                data[j+1].product=temp_product;
                data[j+1].packing=temp_packing;*/
                swap(data[j].product, data[j+1].product);
                swap(data[j].packing, data[j+1].packing);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vyberie pivota a vrati jeho index.
    Pivota vyberie ako median prvkov:
      - data[low]
      - data[(high+low)/2]
      - data[high-1]

    PARAMETRE:
        [in] data - pole, v ktoreho casti s indexami 'low' ... 'high'-1, funkcia vybera pivot
        [in] low  - index prveho prvku casti pola, v ktorej funkcia hlada pivot
        [in] high - index za poslednym prvkom casti pola, v ktorej funkcia hlada pivot

    NAVRATOVA HODNOTA:
        index pivota

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole
        'low' < 'high'

    PRIKLADY:
        data: (10, 20, 2000, 30, 1000, 40, 5000, 50, 60, 70), low: 2, high: 7 -> return 2
        data: (10, 20, 1000, 30, 2000, 40, 5000, 50, 60, 70), low: 2, high: 7 -> return 4
        data: (10, 20, 5000, 30, 1000, 40, 2000, 50, 60, 70), low: 2, high: 7 -> return 6

        data: (10, 20, 1000, 30, 40, 2000, 50, 5000, 60, 70), low: 2, high: 8 -> return 5

        data: (10, 20, 1000, 2000, 30, 40, 50),               low: 2, high: 4 -> return 3
        data: (10, 20, 2000, 1000, 30, 40, 50),               low: 2, high: 4 -> return 3

        data: (10, 20, 1000, 30, 40),                         low: 2, high: 3 -> return 2
*/
size_t getPivotIndex(const int *data, const size_t low, const size_t high)
{
    int temp[]={data[low],data[(high+low)/2],data[high-1]};
    bubbleSort(temp, 3);
    int median=temp[1];
    for(std::size_t i=low; i<high; i++){
        if(data[i]==median){
            return i;
        }
    }
    return ~0; 
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona partition (cast algoritmu quick sort) a vrati novy index pivota.
    Pouzite styl algoritmu Lomuto.
    Poradie usporiadania:
        Najprv (vlavo) budu prvky vacsie alebo rovne ako pivot,
        potom pivot,
        potom (vpravo) prvky mensie ako pivot.

    PARAMETRE:
        [in, out] data - pole, v ktoreho casti 'low' ... 'high'-1 bude vykonane partition
        [in] pivot     - index pivota (pred vykonanim partition)
        [in] low       - index prveho prvku casti pola, v ktorej bude vykonany partition
        [in] high      - index za poslednym prvkom casti pola, v ktorej bude vykonany partition

    NAVRATOVA HODNOTA:
        Index pivota po vykonani partition.

    VSTUPNE PODMIENKY:
        'low' <= 'pivot' < 'high' (index pivota moze byt lubovolny v rozsahu 'low'...'high'-1, napriklad v pripade nahodneho vyberu pivota)
        'data' ukazuje na platne pole

    PRIKLADY:
        1. priklad:
            vstup:  data: (10, 20, 30, 40, 50, 60, 70, 80, 90), pivot: 5, low: 2, high: 7
            vystup: data: (10, 20, 70, 60, 50, 30, 40, 80, 90), return 3

        2. priklad:
            vstup:  data: (10, 20, 30, 40, 50, 60, 70, 50, 80, 90), pivot: 4, low: 2, high: 8
            vystup: data: (10, 20, 50, 60, 70, 50, 30, 40, 80, 90), return 5
*/
size_t partition(int *data, const size_t pivot, const size_t low, const size_t high)
{
    /*
    swap(data[pivot],data[high-1]);   
    int i=low-1;
    for(std::size_t j=low; j<high; j++){
        if(data[j]>=data[high-1]){             
            i++;
            swap(data[i], data[j]);     
        }
    }
    swap(data[++i], data[high-1]);
    std::size_t index=i;
    return index-1; 
*/
    swap(data[pivot],data[high-1]);  
    std::size_t i=low;
    for(std::size_t j=low; j<high; j++){
        if(data[j]>=data[high-1]){
            swap(data[j], data[i]);
            i++;
        }
    }
    return i-1;
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada cast pola 'data' (s indexami 'low' ... 'high'-1).
    Pouzite algoritmus quick sort, styl Lomuto.
    Poradie usporiadania je od najvacsieho prvku po najmensi.

    PARAMETRE:
        [in, out] data - pole, ktoreho cast funkcia usporiada
        [in] low       - index prveho prvkou casti pola, ktoru funkcia usporiada
        [in] high      - index za posledny prvok casti pola, ktoru funkcia usporiada

    VSTUPNA PODMIENKA:
        ak 'low' < 'high', tak 'data' ukazuje na platne pole

    PRIKLAD:
        data: (1, 2, 3, 4, 5, 6, 7, 8, 9), low: 2, high: 7 -> data: (1, 2, 7, 6, 5, 4, 3, 8, 9)
*/
void quickSort(int *data, const size_t low, const size_t high)
{
    if(low+1<high){
        std::size_t pivot=getPivotIndex(data, low, high);
        pivot=partition(data, pivot, low, high);
        quickSort(data, low, pivot);
        quickSort(data, pivot+1, high);
    }  
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

//pri rieseni uloh tykajucich sa quick sort algoritmu mi pomohlo video od "Bro Code", link: https://www.youtube.com/watch?v=Vtckgz38QHs

void swap(int& a, int& b){
    int temp=a;
    a=b;
    b=temp;
}

void printArray(int *array, const size_t length){
    for(std::size_t i=0; i<length; i++){
        std::cout<<array[i]<<" ";
    }
    std::cout<<std::endl;
}

void printStruct(Weight *data, const size_t length){
    for(std::size_t i=0; i<length; i++){
        std::cout<<"("<<data[i].product<<","<<data[i].packing<<")";
    }
    std::cout<<std::endl;
}

int main() {

    //int data[]={9, 1, 8, 2, 7, 3, 6, 4, 5};
    //std::size_t length=sizeof(data)/sizeof(data[0]);
    //printArray(data, length);
    //bubbleSort(data, length);
    //printArray(data, length);
    //Weight baliky[] = {{11, 1}, {2, 1}, {10, 2}, {15, 7}};
    //std::size_t length=sizeof(baliky)/sizeof(baliky[0]);
    //printStruct(baliky, length);
    //bubbleSort(baliky, length);
    //printStruct(baliky, length);
    //int data[]={1, 2, 3, 4, 5, 6, 7, 8, 9};
    //printArray(data, sizeof(data)/sizeof(data[0]));
    //std::cout<<partition(data, 4, 2, 8)<<std::endl;
    //quickSort(data, 2, 7);
    //printArray(data, sizeof(data)/sizeof(data[0]));
    //std::cout<<getPivotIndex(data, 2, 3)<<std::endl;
    return 0;
}
