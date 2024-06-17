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
#include <iomanip>
#include <cassert>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <deque>
#include <algorithm>
#include <limits>

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Upravte definiciu metody 'T::met()' tak, aby informovala, ze metoda nemeni stav objektu.

    Pre kontrolu odkomentujte riadok v testovacej funkcii. Odkomentovany riadok musi byt kompilovatelny.
*/

class T {
public:
    void met() const {}
};

void testUloha1() {
    cout << "----- 1. uloha (metoda nemeni stav objektu) ------------------------------------" << endl;
    const T o;
    o.met(); // odkomentujte
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Upravte definiciiu konstruktora tak, aby bol konverznym konstruktorom.

    Zakomentovane riadky v testovacom kode musia byt kompilovatelne.
*/

class Number {
private:
    int number;
public:
    Number(int value) : number(value){
    }
    int getValue() const {
        return number;
    }
};

void fun(Number n) {
    cout << n.getValue() << endl;
}

void testUloha2() {
    cout << "----- 2. uloha (konverzny konstruktor) -----------------------------------------" << endl;

    Number a = 10; // ak existuje zodpovedajuci konverzny konstruktor, tak je tento riadok kompilovatelny
    cout << a.getValue() << endl;

    fun(20); // ak existuje zodpovedajuci konverzny konstruktor, tak je tento riadok kompilovatelny
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvorte triedu 'B', ktora je podtriedou triedy 'A'.
    Upravte definiciu metody 'A::met()' a definujte metodu 'B::met()' tak,
    aby bol testovaci kod po odkomentovani uspesne vykonany (aby bola vzdy volana spravna metoda).
*/

class A {
public:
    virtual char met() const {
        return 'a';
    }
};

class B: public A{
public:
    char met() const {
        return 'b';
    }
};

void testUloha3() {
    cout << "----- 3. uloha (volanie spravnej metody) ---------------------------------------" << endl;

    A a;
    B b;

    A *pa  = &a;
    A *pab = &b;
    B* pb  = &b;

    assert(pa->met()  == 'a'); // volanie A::met()
    assert(pab->met() == 'b'); // volanie B::met()
    assert(pb->met()  == 'b'); // volanie B::met()
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Upravte definicie destruktorov tried 'C' a 'D' tak, aby sa v testovacej funkcii zavolal spravny destruktor.
    Testovacia funkcia musi namiesto:
        C::~C()
    po uprave vypisat:
        D::~D()
        C::~C()
*/

class C {
public:
    virtual ~C() {
        cout << "C::~C()" << endl;
    }
};

class D : public C {
public:
    ~D() {
        cout << "D::~D()" << endl;
    }
};

void testUloha4() {
    cout << "----- 4. uloha (volanie spravneho destruktora) ---------------------------------" << endl;
    C *obj = new D;
    delete obj; // aby sa zavolal spravny detruktor
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvorte operator +=, ktory bude sluzit pre pripocitanie druheho komplexneho cisla ku prvemu.
    Operator definujte ako clena triedy.

    Pre kontrolu odkomentujte riadky v testovacom kode, kde je priklad pouzitia operatora.
*/

class Complex {
private:
    int real;
    int imaginary;
public:
    Complex(int realPart, int imaginaryPart)
    : real(realPart)
    , imaginary(imaginaryPart) {
    }
    int getRealPart() const {
        return real;
    }
    int getImaginaryPart() const {
        return imaginary;
    }
    // TODO tu pridajte operator +=
    Complex& operator+=(const Complex& x){
        this->real+=x.real;
        this->imaginary+=x.imaginary;
        return *this;
    }
};

void testUloha5() {
    cout << "----- 5. uloha (operator +=) ---------------------------------------------------" << endl;

    Complex a(1,2);
    Complex b(10, 20);
    Complex c(100, 200);

    c += b += a;

    assert(a.getRealPart() == 1);
    assert(a.getImaginaryPart() == 2);
    assert(b.getRealPart() == 11);
    assert(b.getImaginaryPart() == 22);
    assert(c.getRealPart() == 111);
    assert(c.getImaginaryPart() == 222);
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvorte operator <<, ktory zapise hodnotu objektu triedy 'Complex' (z predchadzajuceho prikladu)
    do textoveho prudu dat.
    Poznamka: Operator musi byt definovany ako globalny.

    Pre kontrolu odkomentujte riadky v testovacom kode.
*/

// TODO tu definujte operator <<
ostream& operator<<(ostream &stream, Complex &c){
    if(c.getImaginaryPart() > -1){
        stream<<c.getRealPart()<< "+"<< c.getImaginaryPart()<<"i";
    }
    else{
        stream<<c.getRealPart()<<c.getImaginaryPart()<<"i";
    }
    return stream;
}

void testUloha6() {
    cout << "----- 6. uloha (operator << ) --------------------------------------------------" << endl;

    Complex a( 1, 2);
    Complex b(-3,-4);
    cout << "a = " << a << ", b = " << b << endl;

    ostringstream stream;
    stream << a << " " << b;
    assert(stream.str() == "1+2i -3-4i");
}

//=================================================================================================
// STROM - definicia pre dalsie ulohy
//=================================================================================================

// Uzol stromu
struct Node {
    char value; // hodnota uzla
    list<Node*> children; // zoznam nasledovnikov

    explicit Node(char value) : value(value) {}
};

// Strom
struct Tree {
    Node * root; // koren stromu

    explicit Tree(Node *root = nullptr) : root(root) {}
};

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam vsetkych hodnot uzlov v strome 'tree', ktorych hodnotou je velke pismeno.
    Pouzite algoritmus hladania DO HLBKY.
    Pouzite iterativnu implementaciu.
    Doporucenie: pre identifikaciu velkych pismen pouzite funkciu 'std::isupper'

    VSTUPNA HODNOTA:
        [in] tree - prehladavany strom

    NAVRATOVA HODNOTA:
        zoznam velkych pismen, ktore su hodnotami uzlov v strome 'tree'

    VYSTUPNA PODMIENKA:
        Poradie vo vystupnom zozname musi zodpovedat postupnosti prehladavania algoritmom DO HLBKY.

    PRIKLAD:
        na obrazku
*/

list<char> depthFirstSearchUpperCases(const Tree *tree) {
    list<char> l;
    if(tree->root){
        Node* tmp = tree->root;
        stack<Node*> s;
        s.push(tmp);
        while(!s.empty()){
            tmp=s.top();
            s.pop();
            if(isupper(tmp->value)){
                l.push_back(tmp->value);   
            }
            if(!tmp->children.empty()){ 
               for(auto i : tmp->children){
                    s.push(i);
               } 
            }
        }
    }
    return l; 
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam vsetkych hodnot uzlov v strome 'tree', ktorych hodnotou je velke pismeno.
    Pouzite algoritmus hladania DO SIRKY.
    Pouzite iterativnu implementaciu.
    Doporucenie: pre identifikaciu velkych pismen pouzite funkciu 'std::isupper'

    VSTUPNA HODNOTA:
        [in] tree - prehladavany strom

    NAVRATOVA HODNOTA:
        zoznam velkych pismen, ktore su hodnotami uzlov v strome 'tree'

    VYSTUPNA PODMIENKA:
        Poradie vo vystupnom zozname musi zodpovedat postupnosti prehladavania algoritmom DO SIRKY.

    PRIKLAD:
        na obrazku
*/

list<char> breadthFirstSearchUpperCases(const Tree *tree) {
    list<char> l;
    if(tree->root){
        Node* tmp = tree->root;
        queue<Node*> s;
        s.push(tmp);
        while(!s.empty()){
            tmp=s.front();
            s.pop();
            if(isupper(tmp->value)){
                l.push_back(tmp->value);   
            }
            if(!tmp->children.empty()){ 
               for(auto i : tmp->children){
                    s.push(i);
               } 
            }
        }
    }
    return l; 
}

//=================================================================================================
// GRAF - definicia pre dalsie ulohy
//=================================================================================================
// Graf reprezentuje cestnu siet medzi obcami na planete.
// Uzol grafu reprezentuje obec.
// Hrana grafu reprezentuje "priame" cestne spojenie z jednej obce do druhej.
// Graf je orientovany -> Hrana grafu reprezentuje moznost jazdy len jednym smerom.
//  Preto je moznost "priamej" jazdy medzi obcami oboma smermy reprezentovana dvoma hranami grafu.
// Graf je ohodnoteny -> Mapa cestnej siete eviduje dlzky "priamych" cestnych spojeni medzi obcami.
// Obce nemusia byt prepojene cestnou sietou, napriklad ak sa nachadzaju na roznych pevninach.

// Forward deklaracie su potrebne, pretoze:
//  - definicie 'City' a 'RoadTo' su cyklicky zavisle:
//      - v definicii 'City' je pouzite 'RoadTo'
//      - a v definicii 'RoadTo' je pouzite 'City'
//  - definicie 'City' a 'SearchData' su cyklicky zavisle:
//      - v definicii 'City' je pouzite 'SearchData'
//      - a v definicii 'SearchData' je pouzite 'City'
struct RoadTo;
struct City;

// Udaje pouzite v algoritmoch hladania
struct SearchData {
    // Mozete si doplnit dalsie atributy a metody, ktore pouzijete v algoritmoch hladania
    bool discovered;
    unsigned distance;
    const City *previous;
    bool foundShortestPath;

    void clear() { // nastavi na implicitne hodnoty (tuto metodu mozete upravit (ale nie jej deklaracnu cast - nedoplnajte parametre))
        discovered = false;
        distance = numeric_limits<unsigned>::max();
        previous = nullptr;
        foundShortestPath = false;
    }
};

// Obec (uzol grafu)
struct City {
    string name; // nazov obce
    list<RoadTo> roads; // zoznam "priamych" jednosmernych cestnych spojeni do dalsich obci (zoznam vystupnych hran z tohto uzla grafu)
    SearchData searchData; // udaje pouzite v algoritmoch hladania

    // Mozete doplnit dalsi konstruktor alebo metody, ale tento konstruktor nemente
    explicit City(string name) : name(move(name)) {
        searchData.clear();
    };
};

// Jednosmerne "priame" cestne spojenie do dalsej obce (orientovana, ohodnotena hrana grafu)
struct RoadTo {
    City *city; // obec, do ktorej je toto "priame" cestne spojenie
    unsigned length; // dlzka tohto "priameho" spojenia

    // Mozete doplnit dalsi konstruktor alebo metody, ale tento konstruktor nemente
    RoadTo(City *city, unsigned length)
    : city(city)
    , length(length) {
    }
};

// Cestna mapa planety (orientovany, ohodnoteny graf)
struct Planet {
    list<City> cities; // zoznam obci na planete (zoznam vrcholov grafu)

    void clearSearchData() { // inicializuje atributy pouzite v algoritme hladania
        for(City &c : cities) {
            c.searchData.clear();
        }
    }
};

// Vyminka v pripade neexistencie obce so zadanym nazvom
class CityNotExistsException : exception {
    string cityName; // nazov obce
public:
    explicit CityNotExistsException(string name)
    : cityName(move(name)) {
    }
    const char * what() const noexcept override { // vrati nazov neexistujucej obce
        return cityName.c_str();
    }
};

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam nazvov vsetkych obci na planete 'planet',
    ktore su z obce s nazvom 'startCity' dosiahnutelne pomocou cestnej siete.
    Pouzite algoritmus hladania DO SIRKY.

    VSTUPNA HODNOTA:
        [in] planet - cestna siet na planete
        [in] startCity - nazov obce

    NAVRATOVA HODNOTA:
        zoznam nazvov vsetkych obci, dosiahnutelnych z obce 'startCity'

    VYNIMKA:
        CityNotExistsException - ak na planete 'planet' neexistuje obec s nazvom 'startCity'.
        Metoda 'CityNotExistsException::what()' vrati nazov neexistujucej obce (hodnota 'startCity').

    VYSTUPNE PODMIENKY:
        Vystupny zoznam obsahuje aj 'startCity'.
        Poradie vo vystupnom zozname musi zodpovedat postupnosti prehladavania algoritmom DO SIRKY.

    PRIKLAD:
        na obrazku

    POZNAMKA:
        Ak v implementacii pouziteje 'City::searchData',
        tak bude pravdepodobne potrebne na zaciatku zavolat 'planet->clearSearchData()',
        aj aby bolo osetrene viacnasobne volanie algoritmu s tym istym objektom 'planet'.
*/

City *getCity(const string &cityName, Planet *p){
    for (auto i = p->cities.begin(); i != p->cities.end(); i++){
        if ((*i).name == cityName){
            return &(*i);
        }
    }
    return nullptr;
}

//pri rieseni tejto ulohy mi pomohol kod zo seminara (6.12.2022)
list<string> breadthFirstSearchReachable(Planet * planet, const string & startCity) {
    City *c=getCity(startCity, planet);
    if(!c) throw CityNotExistsException(startCity);
    list<string> l;
    queue<City*> q;
    map<City*, bool> visited;
    for(City& i : planet->cities){
        visited[&i] = false;
    }
    visited[c] = true;
    l.push_back(c->name);
    q.push(c);
    while(!q.empty()){
        for(RoadTo& x : q.front()->roads){
            if(!visited[x.city]){
                visited[x.city] = true;
                l.push_back(x.city->name);
                q.push(x.city);
            }
        }
        q.pop();
    }
    return l; 
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najte dlzky najkratsich ciest z obce 'startCity' do vsetkych dosiahnutelnych obci.
    Pouzite Dijkstrov algoritmus.

    VSTUPNE HODNOTY:
        [in] planet - cestna siet na planete
        [in] startCity - nazov obce

    NAVRATOVA HODNOTA:
        Pre kazdu obec dosiahnutelnu zo 'startCity' (na planete 'planet') obsahuje dlzku najkratsej cesty zo 'startCity'.

    VYNIMKA:
        CityNotExistsException - ak na planete 'planet' neexistuje obec s nazvom 'startCity'.
        Metoda 'CityNotExistsException::what()' vrati nazov neexistujucej obce (hodnota 'startCity').

    VYSTUPNA PODMIENKA:
        Navratova hodnota obsahuje nazvy len tych miest, ktore su dosiahnutelne zo 'startCity'.
        Navratova hodnota obsahuje aj vzdialenost do 'startCity' (nula).

    PRIKLAD:
        na obrazku

    POZNAMKA:
        Ak v implementacii pouziteje 'City::searchData',
        tak bude pravdepodobne potrebne na zaciatku zavolat 'planet->clearSearchData()',
        aj aby bolo osetrene viacnasobne volanie algoritmu s tym istym objektom 'planet'.
*/

map<string, unsigned> dijkstra(Planet * planet, const string & startCity) {

    City *selectedCity=getCity(startCity, planet);
    if(!selectedCity) throw CityNotExistsException(startCity);
    planet->clearSearchData();
    map<string, unsigned> m;

    list<City*> to_visit;
    for(auto &i : planet->cities){
        to_visit.push_back(&i);
    }

    selectedCity->searchData.distance=0;

    while(!to_visit.empty()){

        for(auto i : to_visit){
            if(i->searchData.distance<selectedCity->searchData.distance){
                selectedCity=i;
            }
        }

        if(selectedCity->searchData.distance!=numeric_limits<unsigned>::max()){
            for(auto i : selectedCity->roads){
                if(selectedCity->searchData.distance+i.length<i.city->searchData.distance){
                    i.city->searchData.distance=selectedCity->searchData.distance+i.length;
                }
            }
            m.insert({selectedCity->name, selectedCity->searchData.distance});
        }
        
       to_visit.remove(selectedCity);
       selectedCity=to_visit.front();
    
    }
    
    return m; 
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

void addRoad(const string &startCity, const string &endCity, unsigned length, Planet *p){
    City *start=getCity(startCity, p);
    City *end=getCity(endCity, p);
    start->roads.push_back(RoadTo(end, length));
}

void printList(list<Node*> data){
    for(auto itr = data.begin(); itr != data.end(); itr++){
        cout<<(*itr)->value<<" ";
    }
    cout<<endl;
}

void printList(list<string> data){
    for(auto itr = data.begin(); itr != data.end(); itr++){
        cout<<(*itr)<<" ";
    }
    cout<<endl;
}

void printList(list<char> data){
    for(auto itr = data.begin(); itr != data.end(); itr++){
        cout<<*itr<<" ";
    }
    cout<<endl;
}

void printMap(map<string, unsigned> data){
    for(auto itr = data.begin(); itr != data.end(); itr++){
        cout<<itr->first<<":"<<itr->second<<" ";
    }
    cout<<endl;
}

int main() {
    //testUloha1();
    //testUloha2();
    //testUloha3();
    //testUloha4();
    //testUloha5();
    //testUloha6();
    /*
    Tree* tree=new Tree;
    tree->root=new Node('A');
    Node* b=new Node('B');
    Node* g=new Node('g');
    Node* i=new Node('I');
    tree->root->children.push_back(i);
    tree->root->children.push_back(g);
    tree->root->children.push_back(b);

    Node* j=new Node('j');
    Node* k=new Node('K');
    Node* m=new Node('M');
    Node* n=new Node('N');
    
    i->children.push_back(n);
    i->children.push_back(m);
    i->children.push_back(k);
    i->children.push_back(j);

    Node* l=new Node('L');
    k->children.push_back(l);
    Node* h=new Node('H');
    g->children.push_back(h);

    Node* c=new Node('C');
    Node* f=new Node('F');
    Node* d=new Node('D');
    Node* e=new Node('E');
    b->children.push_back(f);
    b->children.push_back(c);
    c->children.push_back(e);
    c->children.push_back(d);

    //printList(i->children);
    //list<char> data = depthFirstSearchUpperCases(tree);
    list<char> data = breadthFirstSearchUpperCases(tree);
    printList(data);
*/
    //Planet p;
    /*
    p.cities = list<City>({{City("London")}, {City("Wisdon")}, {City("Melon")}, {City("Tilon")}, {City("Lion")}, {City("Billon")}, {City("Turbilon")}, {City("Nylon")}, {City("Gulidon")}, {City("Etalon")}, {City("Tigron")}, {City("Gaucon")}});
    addRoad("London", "Wisdon", 1, &p);
    addRoad("London", "Melon", 1, &p);
    addRoad("Wisdon", "Tilon", 1, &p);
    addRoad("Wisdon", "Lion", 1, &p);
    addRoad("Melon", "Lion", 1, &p);
    addRoad("Melon", "Billon", 1, &p);
    addRoad("Tilon", "Turbilon", 1, &p);
    addRoad("Lion", "Nylon", 1, &p);
    addRoad("Turbilon", "Melon", 1, &p);
    addRoad("Nylon", "Wisdon", 1, &p);
    addRoad("Gulidon", "Nylon", 1, &p);
    addRoad("Gulidon", "Gaucon", 1, &p);
    addRoad("Etalon", "Tigron", 1, &p);
    p.clearSearchData();
    auto l = breadthFirstSearchReachable(&p, "London");
    printList(l);
    */
    /*
    p.cities = list<City>({City("London"), City("Haron"), City("Pecelon"), City("Ballon"), City("Nicudon"), City("Etalon"), City("Tigron")});
    addRoad("London", "Haron", 10, &p);
    addRoad("London", "Pecelon", 40, &p);
    addRoad("London", "Nicudon", 100, &p);
    addRoad("Haron", "Pecelon", 20, &p);
    addRoad("Pecelon", "Ballon", 10, &p);
    addRoad("Pecelon", "Nicudon", 50, &p);
    addRoad("Ballon", "Haron", 15, &p);
    addRoad("Ballon", "Nicudon", 50, &p);
    addRoad("Etalon", "Tigron", 10, &p);
    p.clearSearchData();
    auto l = dijkstra(&p, "London");
    printMap(l);*/
    
    return 0;
}
