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
(8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
    : value(value)
    , smaller(smaller)
    , greater(greater)
    {
    }
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
    : root(root)
    {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho vyhladavacieho stromu.
    Napriklad, pri hladani minima treba prejst len cez potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
    if(tree->root==nullptr){
        throw ValueNotExistsException();
    }
    Node* tmp = tree->root;
    while(tmp->smaller!=nullptr){
        tmp=tmp->smaller;
    }
    return tmp->value; 
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

unsigned depth(const BinarySearchTree *tree, int value) {
    if(!tree->root) throw ValueNotExistsException();
    Node* tmp = tree->root;
    unsigned h=0;
    while(tmp){
        if(tmp->value < value){
            if(tmp->greater!=nullptr){
                tmp=tmp->greater;
                h++;
            }
            else throw ValueNotExistsException();
        }
        else if (tmp->value > value){
            if(tmp->smaller!=nullptr){
                tmp=tmp->smaller;
                h++;
            }
            else throw ValueNotExistsException();
        }
        else break;
    }
    return h;
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    list<int> l;
    Node* tmp = tree->root;
    while(tmp){
        l.push_back(tmp->value);
        if(tmp->value < value){
            if(tmp->greater!=nullptr){
                tmp=tmp->greater;
            }
            else break;
        }
        else if (tmp->value > value){
            if(tmp->smaller!=nullptr){
                tmp=tmp->smaller;
            }
            else break;
        }
        else break;
    }
    return l;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/

size_t count(const Node* node){
    size_t poc=1;
    if(node==nullptr){
        return 0;
    }
    else{
        poc+=count(node->smaller);
        poc+=count(node->greater);
        return poc;
    }
}

size_t count(const BinarySearchTree *tree) noexcept {
    size_t poc=count(tree->root);
    return poc; 
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/
void all(Node* node, list<int> l, list<int>::iterator i){
    if(node){
        all(node->smaller, l, i);
        l.insert(i, node->value);
        all(node->greater, l, i);
    }
}
list<int> all(const BinarySearchTree *tree) noexcept {
    list<int> l;
    auto i=l.begin();
    all(tree->root,l,i);
    return l; 
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/

size_t countGreater(const Node* node, int value){
    if(node==nullptr){
        return 0;
    }
    int poc = countGreater(node->greater, value);
    if(node->value>value){
        poc+=1+countGreater(node->smaller, value);
    }
    return poc;
}

size_t countGreater(const BinarySearchTree *tree, int value) noexcept { 
    size_t poc=countGreater(tree->root, value);
    return poc;
    /*
    //pouzil som level order traversal z PT cvika (ut 8:00 29.11.2022)
    size_t poc=0;
    if(tree->root){
        queue<Node*> q;
        Node* tmp;
        q.push(tree->root);
        while (!q.empty()){
            tmp=q.front();
            if(tmp->value>value) poc++;
            if(tmp->smaller) q.push(tmp->smaller);
            if(tmp->greater) q.push(tmp->greater);
            q.pop();
        }
    }
    return poc;*/
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/
void clear(Node* node){
    if(!node){
        return;
    }
    clear(node->greater);
    clear(node->smaller);
    delete node;
}

void clear(BinarySearchTree *tree) noexcept {
    clear(tree->root);
    tree->root=nullptr;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/

unsigned contains(const vector<int> & data, int value) noexcept {
    //if(data.size()==0) return 0;
    unsigned poc=0;
    int low=0;
    int mid=0;
    int high=data.size();
    while(high-low!=0){
        poc++;
        //cout<<"mid="<<(high+low)/2<<endl;
        mid=(high+low)/2; //low+(high-low)/2
        if(data[mid]==value){
            return poc;
        }
        if(data[mid]>value){
            high=mid;
        }
        if(data[mid]<value){
            low=mid+1;
        }
        //cout<<low<<" "<<mid<<" "<<high<<endl;
        if(high==low || low==mid) return poc;
    }
    return poc; 
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> & data) noexcept {
    map<string, size_t> h;
    for(string i : data){
        ++h[i];
    }
    return h; 
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> & data) noexcept {
    map<string, set<size_t>> h;
    for(string i : data){
        h[i].insert({});
    }
    for(string i : data){
        for(auto itr=data.begin(); itr!=data.end(); itr++){
            if(*itr==i){
                h[i].insert(distance(data.begin(), itr));
            }
        }
    } 
    return h; 
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

Node *insertNode(Node* node, int value){
    if(node){
        if(value > node->value){
            node->greater=insertNode(node->greater, value);
        }
        else{
            node->smaller=insertNode(node->smaller, value);
        }
        return node;
    }
    return new Node{value, nullptr, nullptr};
}

void printList(list<int> data){
    for(auto itr = data.begin(); itr != data.end(); itr++){
        cout<<'{'<<*itr<<"}";
    }
    cout<<endl;
}

int main() {
    /*
    BinarySearchTree* tree = new BinarySearchTree;
    tree->root=nullptr;
    for(int i : {50,30,70,20,40,60,80,10,35,45,55,65}){
        tree->root=insertNode(tree->root, i);
    }*/

    //std::cout<<min(tree)<<std::endl;
    //std::cout<<depth(tree,30)<<std::endl;
    //list<int> data=path(tree, 20);
    //printList(data);
    //std::cout<<count(tree)<<std::endl;
    //std::cout<<countGreater(tree, 36)<<std::endl;
    //list<int> l=all(tree);
    //printList(l);

    //vector<int> data={100, 102, 104, 106, 108, 110};
    //cout<<contains(data, 104)<<endl;

    /*
    vector<string> data={"pocitac", "lietadlo", "luk", "pocitac", "pocitac", "okno", "luk"};
    map<string, size_t> m=histogram(data);
    for(const auto& i : m){
        cout<<i.first<<"->"<<i.second<<endl;
    }
    */

   /*
   vector<string> data={"pocitac", "lietadlo", "luk", "pocitac", "pocitac", "okno", "luk"};
    map<string, set<size_t>> m=index(data);
    for(const auto& i : m){
        cout<<i.first<<"->";
        for(const auto& j : i.second){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    */

    return 0;
}
