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
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};
void printArray(int *array, const size_t length);
//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/
void insertionSort(int *data, const size_t length) {
    bool insert=false;
    for(std::size_t i=1; i<length; i++){
        int tmp=data[i];
        int j=i-1;
        for(; j>=0; --j){
            if(data[j]<tmp){
                data[j+1]=data[j];
				insert=true;
            }
            else break;
        }
        if(insert){
			data[j+1]=tmp;
			insert=false;
		}
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    int length=0;
    for(int i=0; data[i]!=nullptr; i++){
        length++;
    }
    bool insert=false;
    for(int i=1; i<length; i++){
        const char *tmp=data[i];
        int j=i-1;
        for(; j>=0; --j){
            if(strcmp(data[j], tmp) < 0){
                data[j+1]=data[j];
                insert=true;
            }
            else break;
        }
        if(insert){
			data[j+1]=tmp;
			insert=false;
		}
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
    if(list->first!=nullptr){
        Node *curr=list->first->next;
        Node *prev=list->first;
        Node *tmp=list->first;
        Node *tmp_prev=tmp;
        while(curr){
            tmp=list->first;
            while(tmp){
                if(curr->data>tmp->data){
                    if(tmp==list->first){
                        prev->next=curr->next;
                        curr->next=tmp;
                        list->first=curr;
                        break;
                    }
                    else{
                        prev->next=curr->next;
                        curr->next=tmp;
                        tmp_prev->next=curr;
                        break;
                    }                    
                }
                if(tmp->next==curr) break; 
                tmp_prev=tmp;
                tmp=tmp->next;                            
            } 
            prev=curr; 
            curr=curr->next;
        }
    }  
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1], zvysne prvky v 'output' funkcia nemeni.
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    std::size_t i=low;
    std::size_t j=middle;
    std::size_t k=low;
    while(i<middle && j<high){
        if(input[i]>input[j]){
            output[k]=input[i];
            i++;
        }
        else{
            output[k]=input[j];
            j++;
        }
        k++;
    }
    for(; i<middle; i++, k++){
        output[k]=input[i];
    }
    for(; j<high; j++, k++){
        output[k]=input[j];
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
// void mergeSort(int *arrayA, int *arrayB, const size_t low, const size_t high) { // Priklad deklaracie rekurzivnej funkcie, v pripade pristupu top-down
// }
void mergeSort(int *arrayA, int *arrayB, const size_t low, const size_t high) { 
    if(low+1<high){
        int mid=(high+low)/2;
        mergeSort(arrayB, arrayA, low, mid);
        mergeSort(arrayB, arrayA, mid, high);
        mergeNeighbours(arrayA, arrayB, low, mid, high);
    } 
}
void mergeSort(int *data, const size_t length) {
    int *data2 = new int[length];
    for(std::size_t i=0; i<length; i++){
        data2[i]=data[i];
    }
    mergeSort(data, data2, 0, length);
    delete[] data2;
    data2=nullptr;
}
//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

void printArray(int *array, const size_t length){
    for(std::size_t i=0; i<length; i++){
        std::cout<<array[i]<<" ";
    }
    std::cout<<std::endl;
}

void printArray(const char *array[]){
    for(int i=0; array[i]!=nullptr; i++){
        std::cout<<array[i]<<" ";
    }
    std::cout<<std::endl;
}

void printList(List *list){
    Node* root=list->first;
    if(root==nullptr){
        return;
    }
    else{
        std::cout<<root->data<<" "; 
        while(root->next!=nullptr){
            root=root->next;
            std::cout<<root->data<<" "; 
        }
        std::cout<<std::endl;
    }
}

void appendNode(List *list, const int val) {
    Node* newNode = new Node;
    newNode->data=val;
    newNode->next=nullptr;

    if(list->first==nullptr){
        list->first=newNode;
    }
    else{    
        Node* temp = list->first;
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        temp->next=newNode;
    }
}

int main() {
    //int data[]={1,3,2};
    //std::size_t length=sizeof(data)/sizeof(data[0]);
    //const char *data[]={"Juraj", "Anabela", "Peter", "Andrej", nullptr};
    //printArray(data);
    //insertionSort(data);
    //printArray(data);
    //insertionSort(data, length);
    //printArray(data, length);
    //List* list = new List;
    //list->first=nullptr;
    //appendNode(list, 9);
    //appendNode(list, 1);
    //appendNode(list, 3);
    //appendNode(list, 2);
    //appendNode(list, 10);
    //printList(list);
    //insertionSort(list);
    //printList(list);
    //int input[]={10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10};
    //std::size_t length=sizeof(input)/sizeof(input[0]);
    //int output[]={20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
    //std::size_t length2=sizeof(output)/sizeof(output[0]);
    //int data[] = {0,9,4,5,2,7,3,1,8};
    //std::size_t length=sizeof(data)/sizeof(data[0]);
    //printArray(data, length);
    //mergeSort(data, length);
    //printArray(data, length);
    //mergeNeighbours(output, input, 4, 8, 12);
    //printArray(data, length);

    return 0;
}

