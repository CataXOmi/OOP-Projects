#include <iostream>
#include <tuple>
#include <set>
#include <typeinfo>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

class personal
{
protected:

	char* nume, * cnp, * nume_film;
	unsigned int procent;
	static unsigned int numar_angajati;

public:

	///constructori si destructori
	personal();
	personal(char*, char*, char*, unsigned int);
	~personal();

	///constructor de copiere + operator de atribuire
	personal(const personal&);
	personal& operator= (const personal&);

	///get functions
	char* get_nume() const;
	char* get_cnp() const;
	char* get_nume_film() const;
	unsigned int get_procent() const;

	///static get function
	static unsigned int get_numar_angajati() { return numar_angajati; };

	///set functions
	void set_nume(char*);
	void set_cnp(char*);
	void set_nume_film(char*);
	void set_procent(unsigned int);

	///overloading
	friend istream& operator>> (istream& in, personal&);

	///virtual function pentru afisare
	virtual void afis_date()
	{
		//cout << "Tip personal: Alti membri ai echipei" << endl;
		cout << "Nume: " << nume << endl;
		cout << "CNP: " << cnp << endl;
		cout << "Nume film: " << nume_film << endl;
		cout << "Procent din venit: " << procent << "%" << endl << endl;
	}
};

unsigned int personal::numar_angajati = 0;

///constructori si destructori
personal::personal()
{
	nume = NULL;
	cnp = NULL;
	nume_film = NULL;
	procent = 0;

	numar_angajati++;
}

personal::personal(char* cnume, char* ccnp, char* cnume_film, unsigned int cprocent)
{
	nume = new char[strlen(cnume) + 1];
	strcpy(nume, cnume);
	cnp = new char[strlen(ccnp) + 1];
	strcpy(cnp, ccnp);
	nume_film = new char[strlen(cnume_film) + 1];
	strcpy(nume_film, cnume_film);
	procent = cprocent;

	numar_angajati++;
}

personal::~personal()
{
	delete nume;
	delete cnp;
	delete nume_film;
	numar_angajati--;

	cout << "Destroyed1" << endl;
}

///constructor de copiere + operator de atribuire
personal::personal(const personal& ang)
{
	nume = new char[strlen(ang.nume) + 1];
	strcpy(nume, ang.nume);
	cnp = new char[strlen(ang.cnp) + 1];
	strcpy(cnp, ang.cnp);
	nume_film = new char[strlen(ang.nume_film) + 1];
	strcpy(nume_film, ang.nume_film);
	procent = ang.procent;

	numar_angajati++;
}

personal& personal::operator=(const personal& pers)
{
	if (this == &pers)
		return *this;
	delete nume;
	delete cnp;
	delete nume_film;
	nume = new char[strlen(pers.nume) + 1];
	strcpy(nume, pers.nume);
	cnp = new char[strlen(pers.cnp) + 1];
	strcpy(cnp, pers.cnp);
	nume_film = new char[strlen(pers.nume_film) + 1];
	strcpy(nume_film, pers.nume_film);
	procent = pers.procent;

	return *this;
}

///get functions
char* personal::get_nume() const
{
	return nume;
}

char* personal::get_cnp() const
{
	return cnp;
}

char* personal::get_nume_film() const
{
	return nume_film;
}

unsigned int personal::get_procent() const
{
	return procent;
}

///set functions
void personal::set_nume(char* x)
{
	nume = new char[strlen(x) + 1];
	strcpy(nume, x);
}

void personal::set_cnp(char* x)
{
	cnp = new char[strlen(x) + 1];
	strcpy(cnp, x);
}

void personal::set_nume_film(char* x)
{
	nume_film = new char[strlen(x) + 1];
	strcpy(nume_film, x);
}

void personal::set_procent(unsigned int x)
{
	procent = x;
}

///overloading
istream& operator>> (istream& in, personal& pers)
{
	char temp_nume[255], temp_cnp[255], temp_nume_film[255];
	unsigned int temp_procent;

	cout << "Introduceti numele: ";
	in >> temp_nume;
	cout << "Introduceti cnp-ul: ";
	in >> temp_cnp;
	cout << "Introduceti numele filmului: ";
	in >> temp_nume_film;
	cout << "Introduceti procentul: ";
	in >> temp_procent;

	pers.nume = new char[strlen(temp_nume) + 1];
	strcpy(pers.nume, temp_nume);
	pers.cnp = new char[strlen(temp_cnp) + 1];
	strcpy(pers.cnp, temp_cnp);
	pers.nume_film = new char[strlen(temp_nume_film) + 1];
	strcpy(pers.nume_film, temp_nume_film);
	pers.procent = temp_procent;

	return in;
}

class actor : public personal
{
	bool personaj_principal;

public:

	///cosntructori si destructori
	actor() :personal() { personaj_principal = 0; }
	actor(char* cnume, char* ccnp, char* cnume_film, unsigned int cprocent, bool cpersonaj_principal) :personal(cnume, ccnp, cnume_film, cprocent)
	{
		personaj_principal = cpersonaj_principal;
		verif_actor();
	}
	~actor() { cout << "Destroyed4" << endl; }

	///constructor de copiere si operator de atribuire
	actor(const actor& A) :personal(A)
	{
		personaj_principal = A.personaj_principal;
	}
	actor& operator=(const actor&);

	///get function
	bool get_personaj_principal();

	///set function
	void set_personaj_principal(bool);

	///overloading
	friend istream& operator>> (istream&, actor&);

	///virtual function pentru afisare
	void afis_date()
	{
		cout << "Tip personal: Actor" << endl;
		personal::afis_date();
		cout << "E personaj principal? R: ";
		if (personaj_principal)
			cout << "Da.";
		else
			cout << "Nu.";
		cout << endl << endl;
	}

	///Others
	void verif_actor();
};

///operator de atribuire
actor& actor::operator=(const actor& A)
{
	if (this == &A)
		return *this;
	this->personaj_principal = A.personaj_principal;
	this->personal::operator=(A);

	return *this;
}

///get function
bool actor::get_personaj_principal()
{
	return personaj_principal;
}

///set function
void actor::set_personaj_principal(bool x)
{
	personaj_principal = x;
}

///overloading
istream& operator>> (istream& in, actor& A)
{
	/*char temp_nume[255],temp_cnp[255],temp_nume_film[255];
	unsigned int temp_procent,*/

	unsigned int temp_personaj_principal;

	/*cout << "Introduceti numele: " ;
	in >> temp_nume;
	cout << "Introduceti cnp-ul: ";
	in >> temp_cnp;
	cout << "Introduceti numele filmului: ";
	in >> temp_nume_film;
	cout << "Introduceti procentul: ";
	in >> temp_procent;*/

	///in >> (personal&)A;
	in >> dynamic_cast<personal&>(A);
	cout << "Introduceti daca este personaj principal: ";
	in >> temp_personaj_principal;

	/*A.set_nume(temp_nume);
	A.set_cnp(temp_cnp);
	A.set_nume_film(temp_nume_film);
	A.set_procent(temp_procent);*/

	A.personaj_principal = temp_personaj_principal;

	/*A.nume = new char[strlen(temp_nume)+1];
	strcpy(A.nume,temp_nume);
	A.cnp = new char[strlen(temp_cnp)+1];
	strcpy(A.cnp,temp_cnp);
	A.nume_film = new char[strlen(temp_nume_film)+1];
	strcpy(A.nume_film,temp_nume_film);
	A.procent = temp_procent;
	A.personaj_principal = temp_personaj_principal;*/

	return in;
}

///Others
void actor::verif_actor()
{
	if (personaj_principal)
		set_procent(get_procent() + 10);
}

class regizor : public personal
{
	unsigned int suma;

public:

	///constructori si desctructori
	regizor() :personal() { suma = 0; }
	regizor(char* cnume, char* ccnp, char* cnume_film, unsigned int cprocent, unsigned int csuma) :personal(cnume, ccnp, cnume_film, cprocent)
	{
		suma = csuma;
	}
	~regizor() { cout << "Destroyed3" << endl; }

	///constructor de copiere si operator de atribuire
	regizor(const regizor& R) :personal(R)
	{
		suma = R.suma;
	}
	regizor& operator=(const regizor&);

	///get function
	unsigned int get_suma();

	///set function
	void set_suma(unsigned int);
	///overloading
	friend istream& operator>> (istream&, regizor&);

	///virtual function pentru afisare
	void afis_date()
	{
		cout << "Tip personal: Regizor" << endl;
		personal::afis_date();
		cout << "Suma regizor: " << suma << "$" << endl << endl;
	}
};

///operator de atribuire
regizor& regizor::operator= (const regizor& R)
{
	if (this == &R)
		return *this;
	this->suma = R.suma;
	this->personal::operator=(R);

	return *this;
}

///get function
unsigned int regizor::get_suma()
{
	return suma;
}

///set function
void regizor::set_suma(unsigned int s)
{
	suma = s;
}

///overloading
istream& operator>> (istream& in, regizor& R)
{
	/*char temp_nume[255],temp_cnp[255],temp_nume_film[255];
	unsigned int temp_procent, temp_suma;*/

	unsigned int temp_suma;

	/*cout << "Introduceti numele: " ;
	in >> temp_nume;
	cout << "Introduceti cnp-ul: ";
	in >> temp_cnp;
	cout << "Introduceti numele filmului: ";
	in >> temp_nume_film;
	cout << "Introduceti procentul: ";
	in >> temp_procent;*/

	///in >> (personal&)A;
	in >> dynamic_cast<personal&>(R);
	cout << "Introduceti suma regizorului: ";
	in >> temp_suma;

	/*R.set_nume(temp_nume);
	R.set_cnp(temp_cnp);
	R.set_nume_film(temp_nume_film);
	R.set_procent(temp_procent);*/

	R.suma = temp_suma;

	/*R.nume = new char[strlen(temp_nume)+1];
	strcpy(R.nume,temp_nume);
	R.cnp = new char[strlen(temp_cnp)+1];
	strcpy(R.cnp,temp_cnp);
	R.nume_film = new char[strlen(temp_nume_film)+1];
	strcpy(R.nume_film,temp_nume_film);
	R.procent = temp_procent;
	R.suma = temp_suma;*/

	return in;
}

class film
{
protected:

	char* nume, * tip;
	unsigned int durata; //in minute

public:

	///constructori si destructori
	film();
	film(char*, char*, unsigned int);
	~film();

	///operator de atribuire + constructor de copiere
	film(const film&);
	film& operator= (const film&);

	///get functions
	char* get_nume();
	char* get_tip();
	unsigned int get_durata();

	///set functions
	void set_nume(char*);
	void set_tip(char*);
	void set_durata(unsigned int);

	///overloading
	friend istream& operator>> (istream&, film&);
	friend ostream& operator<< (ostream&, film&);

	/*///virtual function pentru afisare
	virtual void afisare_date()
	{
		cout << "Descriere film: " << endl;
		cout << "Denumire: " << nume << endl;
		cout << "Tip: " << tip << endl;
		cout << "Durata: " << durata << endl;
	}*/
};

///constructori si destructori
film::film()
{
	nume = NULL;
	tip = NULL;
	durata = 0;
}

film::film(char* cnume, char* ctip, unsigned int cdurata)
{
	nume = new char[strlen(cnume) + 1];
	strcpy(nume, cnume);
	tip = new char[strlen(ctip) + 1];
	strcpy(tip, ctip);
	durata = cdurata;
}

film::~film()
{
	delete nume;
	delete tip;
	cout << "Destroyed2" << endl;
}

///operator de atribuire + constructor de copiere
film::film(const film& cop)
{
	nume = new char[strlen(cop.nume) + 1];
	strcpy(nume, cop.nume);
	tip = new char[strlen(cop.tip) + 1];
	strcpy(tip, cop.tip);
	durata = cop.durata;
}

film& film::operator=(const film& cop)
{
	if (this == &cop)
		return *this;
	delete nume;
	delete tip;
	nume = new char[strlen(cop.nume) + 1];
	strcpy(nume, cop.nume);
	tip = new char[strlen(cop.tip) + 1];
	strcpy(tip, cop.tip);
	durata = cop.durata;

	return *this;
}

///get functions
char* film::get_nume()
{
	return nume;
}

char* film::get_tip()
{
	return tip;
}

unsigned int film::get_durata()
{
	return durata;
}

///set functions
void film::set_nume(char* x)
{
	nume = new char[strlen(x) + 1];
	strcpy(nume, x);
}

void film::set_tip(char* x)
{
	tip = new char[strlen(x) + 1];
	strcpy(tip, x);
}

void film::set_durata(unsigned int x)
{
	durata = x;
}

///overloading
istream& operator>> (istream& in, film& nou)
{
	char temp_nume[255], temp_tip[255];
	unsigned int temp_durata;
	cout << "Introduceti numele: ";
	in >> temp_nume;
	cout << "Introduceti tipul: ";
	in >> temp_tip;
	cout << "Introduceti durata: ";
	in >> temp_durata;

	nou.nume = new char[strlen(temp_nume) + 1];
	strcpy(nou.nume, temp_nume);
	nou.tip = new char[strlen(temp_tip) + 1];
	strcpy(nou.tip, temp_tip);
	nou.durata = temp_durata;

	return in;
}

ostream& operator<< (ostream& out, film& afis)
{
	out << "Descriere film: " << endl;
	out << "Denumire: " << afis.nume << endl;
	out << "Tip: " << afis.tip << endl;
	out << "Durata: " << afis.durata << endl;

	return out;
}

template <class T> class FirmaDistributie
{
	static int numar_persoane, numar_actori;
	const int an;

	unsigned int numar_filme;

	///structura alocata dinamic
	//personal **echipe;
	T** echipe;

	///stl
	vector<film> f;

public:

	///constructori si destructori
	FirmaDistributie();
	FirmaDistributie(int, int);
	virtual ~FirmaDistributie();

	///constructor de copiere si operator de atribuire
	FirmaDistributie(const FirmaDistributie&);
	FirmaDistributie& operator= (const FirmaDistributie&);

	///static get functions
	static int get_numar_persoane() { return numar_persoane; }
	static int get_numar_actori() { return numar_actori; }

	///incrementare automata
	template<class U>
	void adaugaPersonal(U oop);

	///functii de citire si afisare
	void citire();
	void afisare();
};

template<class T> int FirmaDistributie<T>::numar_persoane = 0;
template<class T> int FirmaDistributie<T>::numar_actori = 0;

///constructori si destructori
template<class T>
FirmaDistributie<T>::FirmaDistributie()
{
	echipe = NULL;
	numar_filme = 0;
	an = 2020;
}

template<class T>
FirmaDistributie<T>::FirmaDistributie(int can, int cnumar_filme) :an(can), numar_filme(cnumar_filme)
{
	//echipe = new personal*[numar_persoane];
	echipe = new T * [100]; // pot participa maximum 100 de persoane
}

template<class T>
FirmaDistributie<T>::~FirmaDistributie()
{
	cout << "Destroyed5" << endl;
	int i;
	for (i = 0; i < numar_persoane; i++)
		delete echipe[i];
	delete[]echipe;
}

///constructor de copiere si operator de atribuire
template <class T>
FirmaDistributie<T>::FirmaDistributie(const FirmaDistributie& cop)
{

	int i;

	try
	{
		if (!numar_persoane)
			throw "Memorie insuficienta pentru filme";
	}

	catch (string e)
	{
		cout << "A avut loc exceptia " << endl << e << endl;
	}

	T** copie;
	copie = new T * [numar_persoane];
	for (i = 0; i < numar_persoane; i++)
		copie[i] = echipe[i];
	numar_filme = cop.numar_filme;
	numar_persoane = cop.numar_persoane;
	numar_actori = cop.numar_actori;

	echipe = new T * [cop.numar_persoane];
	for (i = 0; i < numar_persoane; i++)
		echipe[i] = copie[i];
}

template <class T>
FirmaDistributie<T>& FirmaDistributie<T>::operator=(const FirmaDistributie& FD)
{
	int i;

	T** copie;
	copie = new T * [numar_persoane];
	for (i = 0; i < numar_persoane; i++)
		copie[i] = echipe[i];

	if (this == &FD)
		return *this;
	numar_filme = FD.numar_filme;
	numar_persoane = FD.numar_persoane;
	numar_actori = FD.numar_actori;

	echipe = new T * [FD.numar_persoane];
	for (i = 0; i < numar_persoane; i++)
		echipe[i] = copie[i];

	return *this;
}

///automatic incrementation
template<class T> template<class U>
void FirmaDistributie<T>::adaugaPersonal(U oop)
{
	int i;
	T** copie;
	copie = new T * [numar_persoane];
	for (i = 0; i < numar_persoane; i++)
		copie[i] = echipe[i];

	echipe = new T * [numar_persoane];
	for (i = 0; i < numar_persoane; i++)
		echipe[i] = copie[i];

	cin >> oop;
	echipe[numar_persoane] = oop;

	if (strstr(typeid(*(echipe[numar_persoane])).name(), "Actor") != NULL)
		numar_actori++;
	numar_persoane++;
}

///functii de citire si afisare
template<class T>
void FirmaDistributie<T>::citire()
{
	int i;
	cout << "Dati numarul de filme din anul " << an << ": ";
	cin >> numar_filme;

	film x;

	for (i = 0; i < numar_filme; i++)
	{
		cout << "x=";
		cin >> x;
		f.push_back(x);
	}

	T* temp_ob = new T();
	//temp_ob->citire();
	cin >> temp_ob;
	adaugaPersonal(temp_ob);
	/*T **copie;
	copie = new T* [numar_persoane];
	for (i=0;i<numar_persoane;i++)
		copie[i] = echipe[i];

	echipe = new T* [numar_persoane];
	for (i=0;i<numar_persoane;i++)
		echipe[i] = copie[i];
	echipe[numar_persoane] = temp_ob;
	numar_persoane++;*/
}

template<class T>
void FirmaDistributie<T>::afisare()
{
	int i;
	cout << "Filmele care au avut loc in anul " << an << ":" << endl;
	vector<film>::iterator p;
	for (p = f.begin(); p < f.end(); p++)
		cout << *p << endl;
	cout << endl;

	cout << "Personaulul are " << numar_persoane - 1 << "membri" << endl;
	cout << "Acestia sunt urmatorii: " << endl;
	for (i = 0; i < numar_persoane; i++)
	{
		echipe[i]->afis_date();
		cout << endl;
	}
	cout << "Numarul de actori este " << numar_actori - 1;
}

///specializare pentru tipul actor
template<>
class FirmaDistributie<actor>
{
	//static
	unsigned int numar_actori_principali;
	int nr;
	vector<actor> act;

public:

	///constructori+destructori
	FirmaDistributie();
	FirmaDistributie(int p)
	{
		numar_actori_principali = 0;
		nr = p;
	}
	~FirmaDistributie() { cout << "Destroyed6" << endl; }
	///get function
	//static
	unsigned int get_numar_actori_principali() { return numar_actori_principali; }

	///functii de citire si afisare
	void citire();
	void afisare();

	///aflare numar de actori principali
	unsigned int checker();
};

//unsigned int FirmaDistributie<actor>::numar_actori_principali = 0;
///constructor
FirmaDistributie<actor>::FirmaDistributie()
{
	numar_actori_principali = 0;
	nr = 0;
}

///verificare
unsigned int FirmaDistributie<actor>::checker()
{
	int i;

	for (i = 0; i < nr; i++)
		if (act[i].get_personaj_principal())
			numar_actori_principali++;
	numar_actori_principali -= 1;

	return numar_actori_principali;
}

///citire si afisare
void FirmaDistributie<actor>::citire()
{
	int nr;

	cout << "Dati numarul de actori: ";
	cin >> nr;

	actor x;
	cin >> x;
	act.push_back(x);
}

void FirmaDistributie<actor>::afisare()
{
	int i;

	try
	{
		if (numar_actori_principali < 0)
			throw "Something went wrong";
	}
	catch (string expr)
	{
		cout << "A avut loc exceptia " << endl << expr << endl;
	}

	cout << "Numarul de actori este: " << nr << endl;
	cout << "Dintre acestia principali sunt: " << numar_actori_principali << endl;
	for (i = 0; i < nr; i++)
		if (act[i].get_personaj_principal())
			act[i].afis_date();
}

int main()
{
	personal ob_pers;
	actor ob_actor;
	regizor ob_regizor;
	film ob_film;
	//FirmaDistributie<int> ob_temp;
	FirmaDistributie<actor> ob_spec;

	cout << "Alegeti una din optiunile din lista urmatoare: " << endl;
	cout << "1. Lucrati cu obiect de tip personal" << endl;
	cout << "2. Lucrati cu obiect de tip actor" << endl;
	cout << "3. Lucrati cu obiect de tip regizor" << endl;
	cout << "4. Lucrati cu obiect de tip film" << endl;
	//cout << "5. Lucrati cu obiect de tip FirmaDistributie" << endl;
	cout << "6. Lucrati cu obiect de tip FirmaDistributie specializat pe actor" << endl;

	int expr;
	string opt;
	cin >> expr;

	while (expr)
	{
		if (expr == 1)
		{
			cout << "Ati ales sa lucrati cu clasa personal" << endl;
			cout << "Citim datele obiectului" << endl;
			cin >> ob_pers;
			cout << "Afisam datele memorate in obiect" << endl;
			ob_pers.afis_date();
		}
		if (expr == 2)
		{
			cout << "Ati ales sa lucrati cu clasa actor" << endl;
			cout << "Citim datele obiectului" << endl;
			cin >> ob_actor;
			cout << "Afisam datele memorate in obiect" << endl;
			ob_actor.afis_date();
		}
		if (expr == 3)
		{
			cout << "Ati ales sa lucrati cu clasa regizor" << endl;
			cout << "Citim datele obiectului" << endl;
			cin >> ob_regizor;
			cout << "Afisam datele memorate in obiect" << endl;
			ob_regizor.afis_date();
		}
		if (expr == 4)
		{
			cout << "Ati ales sa lucrati cu clasa film" << endl;
			cout << "Citim datele obiectului" << endl;
			cin >> ob_film;
			cout << "Afisam datele memorate in obiect" << endl << endl;
			cout << ob_film;
		}
		/*if(expr == 5)
			{
			 cout << "Ati ales sa lucrati cu clasa FirmaDistributie nespecializata" << endl;
			 cout << "Citim datele obiectului" << endl;
			 ob_temp.citire();
			 cout << "Afisam datele memorate in obiect" << endl << endl;
			 ob_temp.afisare();
			}*/
		if (expr == 6)
		{
			cout << "Ati ales sa lucrati cu clasa FirmaDistributie specializate pe tipul actor" << endl;
			cout << "Citim datele obiectului" << endl;
			ob_spec.citire();
			cout << "Afisam datele memorate in obiect" << endl << endl;
			ob_spec.afisare();
		}
		cout << "Doriti sa lucrati si cu alte clase?" << endl;
		cout << "Raspuns: ";
		cin >> opt;
		if (opt == "da" || opt == "Da" || opt == "dA" || opt == "DA")
		{
			cout << "Alegeti una din optiunile din lista urmatoare: " << endl;
			cout << "1. Lucrati cu obiect de tip personal" << endl;
			cout << "2. Lucrati cu obiect de tip actor" << endl;
			cout << "3. Lucrati cu obiect de tip regizor" << endl;
			cout << "4. Lucrati cu obiect de tip film" << endl;
			//cout << "5. Lucrati cu obiect de tip FirmaDistributie" << endl;
			cout << "6. Lucrati cu obiect de tip FirmaDistributie specializat pe actor" << endl;
			cin >> expr;
		}
		else
			break;
	}

	return 0;
}

///a doua optiune pentru template class
/*
template <class T> class FirmaDistributie
{
	static int numar_persoane, numar_actori;
	const int an;

	unsigned int numar_filme;

	///structura alocata dinamic
	film *f;
	//T *f;

	///stl
	vector<pair<T*, int>> echipa;

 public:

	///constructori si destructori
	FirmaDistributie();
	FirmaDistributie(int, int);
	virtual ~FirmaDistributie();

	///constructor de copiere si operator de atribuire
	FirmaDistributie(const FirmaDistributie&);
	FirmaDistributie& operator= (const FirmaDistributie&);

	///static get functions
	static int get_numar_persoane(){return numar_persoane;}
	static int get_numar_actori(){return numar_actori;}

	///incrementare automata
	void adaugaPersonal(U oop);

	///functii de citire si afisare
	void citire();
	void afisare();
};

template<class T> int FirmaDistributie<T>::numar_persoane = 0;
template<class T> int FirmaDistributie<T>::numar_actori = 0;

///constructori si destructori
template<class T>
FirmaDistributie<T>::FirmaDistributie()
{
	f = NULL;
	numar_filme = 0;
	an = 2020;
}

template<class T>
FirmaDistributie<T>::FirmaDistributie(int can, int cnumar_filme):an(can),numar_filme(cnumar_filme)
{
	f = new film*[numar_filme];
}

template<class T>
FirmaDistributie<T>::~FirmaDistributie()
{
	cout << "Destroyed5" << endl;

	delete []f;
}

///constructor de copiere si operator de atribuire
template <class T>
FirmaDistributie<T>::FirmaDistributie(const FirmaDistributie &cop)
{

	int i;

	try
		{
			if(!numar_filme)
				throw "Memorie insuficienta pentru filme";
		}

	catch(string e)
		{
			cout << "A avut loc exceptia " << endl << e << endl;
		}

	film *copie;
	copie = new film* [numar_filme];
	for (i=0;i<numar_filme;i++)
		copie[i] = f[i];
	numar_filme = cop.numar_filme;
	numar_persoane = cop.numar_persoane;
	numar_actori = cop.numar_actori;

	f = new filme*[cop.numar_filme];
	for (i=0;i<numar_filme;i++)
		f[i] = copie[i];
}

template <class T>
FirmaDistributie<T>& FirmaDistributie<T>::operator=(const FirmaDistributie &FD)
{
	int i;

	film *copie;
	copie = new film* [numar_filme];
	for (i=0;i<numar_filme;i++)
		copie[i] = f[i];

	if (this == &FD)
		return *this;
	numar_filme = FD.numar_filme;
	numar_persoane = FD.numar_persoane;
	numar_actori = FD.numar_actori;

	f = new filme*[FD.numar_filme];
	for (i=0;i<numar_filme;i++)
		f[i] = copie[i];

	return *this;
}

///automatic incrementation
template<class T>
void FirmaDistributie<T>::adaugaPersonal(T oop)
{
	int i;
	film *copie;
	copie = new film* [numar_filme];
	for (i=0;i<numar_persoane;i++)
		copie[i] = f[i];

	f = new film* [numar_filme];
	for (i=0;i<numar_filme;i++)
		f[i] = copie[i];

	cin >> oop;
	echipe.push_back(make_pair(oop,numar_persoane));
	numar_persoane++;

	if(strstr(typeid(*(echipe[numar_persoane-1])).name(),"Actor")!=NULL)
		numar_actori++;
}

///functii de citire si afisare
template<class T>
void FirmaDistributie<T>::citire()
{
	int i;
	cout << "Dati numarul de filme din anul " << an << ": ";
	cin >> numar_filme;

	f = new film[numar_filme];

	for(i=0;i<n;i++)
		cin >> f[i];
	for(i=0;i<numar_persoane;i++)
		{
		 T ob;
		 adaugaPersonal(ob);
		}
}

template<class T>
void FirmaDistributie<T>::afisare()
{
	int i;
	cout << "Filmele care au avut loc in anul " << an << ":" << endl;
	for(i=0;i<numar_filme;i++)
		cout << f[i] << endl;

	cout << "Personaulul are " << numar_persoane-1 << "membri" << endl;
	cout << "Acestia sunt urmatorii: " << endl;

	vector<T*>::iterator p;
	for(p=echipe.begin();p<echipe.end();p++)
		cout << *p->afis_date() << endl;

	cout << "Numarul de actori este " << numar_actori-1;
}

*/
