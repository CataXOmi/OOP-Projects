#include <iostream>

using namespace std;

class lista;

class nod
{
 private:
    int info;
    nod *prev , *next;
 public:
     nod(const nod&);
     int getinfo(){return info;}
     nod *getnext(){return next;}
     nod *getprev(){return prev;}
     nod(int);
     ~nod();
     friend class lista;
     friend istream& operator>>(istream&,lista&);
     friend ostream& operator<<(ostream&,lista&);
};

class lista
{
 private:
    nod *prim, *ult;
    int nr_crt;
 public:
    lista(){prim = NULL;ult = NULL;nr_crt = 0;}//checked
    ~lista();//checked
    lista(const lista&);//checked
    void adaug(int,int);//checked
    friend istream& operator>>(istream&,lista&);//checked
    friend ostream& operator<<(ostream&,lista&);//checked
    lista& operator=(const lista&);//checked
    void sterg(int);//checked
    friend lista operator+(lista&,lista&);//checked
    void afisdim();//checked
};

class nr_obiecte
{
 int n;
 lista *v;
 public:
     void citire(int );
     void afisare(int );
     int nr_elem();
     lista& getlista(int);
     ~nr_obiecte();
};

nod::nod(const nod &p)
{
 info = p.info;
 prev = p.prev;
 next = p.next;
}

nod::nod(int x=10)
{
 info = x;
 prev = NULL;
 next = NULL;
}

nod::~nod()
{

}

lista::~lista()
{
 nod *crt = prim;
 nod *temp;
 while(crt != NULL)
    {
     temp = crt;
     crt = crt->next;
     delete temp;
    }
}

lista::lista(const lista& l)
{
 prim = ult = NULL;
 nod * crt = l.prim;
 int i = 0;
 while(crt != NULL)
    {
     this->adaug(crt->info,i);
     i++;
     crt = crt->next;
    }
 nr_crt = i;
}

lista& lista::operator=(const lista& l)
{
 nod *crt = prim;
 nod *temp;
 while(crt != NULL)
    {
     temp = crt;
     crt = crt->next;
     delete temp;
    }
 prim = ult = NULL;
 crt = l.prim;
 int i = 0;
 while(crt != NULL)
    {
     this->adaug(crt->info,i);
     i++;
     crt = crt->next;
    }
 nr_crt = i;
 return *this;
}

lista operator+(lista& l1,lista& l2)
{
 lista l;
 l = l1;
 int i = l.nr_crt;
 nod * crt = l2.prim;
 while(crt != NULL)
    {
     l.adaug(crt->getinfo(),i);
     i++;
     crt=crt->getnext();
    }
 return l;
}

istream& operator>>(istream& in, lista& l)
{
 string s;
 int val,poz;
 //Prin conventie am stabilit ca "adaug" sa fie introdus pentru a putea citi elementele listei
 cout<<"Dati s egal cu adaug pentru a pune elemente in lista : ";
 in >> s;
 while(s == "adaug")//prin conventie
    {cout << "Dati valoarea si pozitia pe care doriti sa le adaugati : ";
     in >> val >> poz;
     l.adaug(val,poz);
     cout << "Dati s : ";
     in >> s;
    }
 return in;
}

ostream& operator<<(ostream& out,lista& l)
{
 // afisare de la stanga la dreapta
 nod *p = l.prim;
 out << "Lista afisata de la stanga la dreapta este urmatoarea : ";
 while(p != NULL)
    {
        out << p->info << " ";
        p = p->next;
    }
 // afisare de la dreapta la stanga
 nod *t = l.ult;
 out << endl << "Lista afisata de la dreapta la stanga este urmatoarea : ";
 while(t != NULL)
    {
        out << t->info << " ";
        t = t->prev;
    }
 return out;
}

void lista::afisdim()
{
    cout << nr_crt;
}

void lista::adaug(int val,int poz)
{
 nod *p = new nod;
 p->info = val;
 if(prim != NULL)
    {if(poz >= nr_crt)
        {
         p->prev = ult;
         p->next = NULL;
         ult->next = p;
         ult = p;
        }
     if(poz <= 0)
        {
         p->prev = NULL;
         p->next = prim;
         prim->prev = p;
         prim = p;
        }
     if(poz < nr_crt && poz > 0)
        {
         int i = 0;
         nod *temp = prim;
         while(i != poz)
            {
             temp = temp->next;
             i++;
            }
         p->next = temp;
         p->prev = temp->prev;
         temp->prev->next = p;
         temp->prev = p;
        }
    }
 else
    {
     p->next = NULL;
     p->prev = NULL;
     prim = ult = p;
    }
 nr_crt++;
}

void lista::sterg(int poz)
{
 if(prim != NULL)
    {
     if(poz >= nr_crt)
        {
         if(poz>nr_crt)
         {
             cout << "Pozitia data nu se afla in lista noastra, dar este mai mare ca dimensiunea acesteia asa ca vom sterge ultimul element";
         }
         nod * t = ult;
         ult = ult -> prev;
         if(ult != NULL)
            ult -> next = NULL;
         delete t;
        }
     if(poz <= 0)
        {
         if(poz<0)
         {
             cout << "Pozitia data nu se afla in lista noastra, dar este mai mica ca pozitia primului element asa ca il vom sterge pe acesta";
         }
         nod * t = prim;
         prim = prim -> next;
         if(prim != NULL)
            prim -> prev = NULL;
         delete t;
        }
     if(poz < nr_crt && poz > 0)
        {
         int i = 0;
         nod *temp = prim;
         while(i != poz)
            {temp = temp -> next;
             i++;
            }
         temp->prev->next = temp->next;
         temp->next->prev = temp->prev;
         delete temp;
        }
     nr_crt--;
     if(nr_crt == 0)
            prim = ult = NULL;
    }
  else
    {
        cout << "Lista este vida";
    }
}

int nr_obiecte::nr_elem()
{
 cout << "Numarul de obiecte n este egal cu ";
 cin >> n;
 v = new lista [n];
 return n;
}

void nr_obiecte::citire(int n)
{
 for(int i=0; i<n; i++)
    cin >> v[i];

}

void nr_obiecte::afisare(int n)
{
 cout << "Cele " << n << " liste sunt urmatoarele : "<<endl;
 for(int i=0; i<n; i++)
    cout<< v[i] <<endl;
}

lista& nr_obiecte::getlista(int index)
{
  return v[index];
}

 nr_obiecte::~nr_obiecte()
 {
     delete []v;
 }

int main()
{/*int expr,ng;
nr_obiecte vectlist;
ng=vectlist.nr_elem();
 int i=1;
 while(i<=3)
     {
      if(i==1)
         cout << "1.Lucrati cu un vector de obiecte de tipul lista";
      if(i==2)
         cout << endl << "2.Lucrati cu obiecte de tipul lista";
      if(i==3)
         cout << endl << "3.Lucrati atat cu un vector de obiecte de tipul lista cat si cu obiecte de tipul lista";
      i++;
     }
 cout << endl << "Alegeti una din cele trei optiuni mentionate anterior ";
 cin >> expr;
 switch(expr)
    {
     case 1:
        {
         cout << "Ati ales sa lucrati cu un vector de obiecte de tipul lista";
         cout << endl << "Aveti meniul urmator : ";
         int i=1,optiune;
         while(i<=6)
            {
             if(i==1)
                cout << endl <<i <<". Citire vector de obiecte";
             if(i==2)
                cout << endl <<i <<". Afisare vector de obiecte";
             if(i==3)
                cout << endl <<i <<". Concatenati un numar dat de elemente din vector";
             if(i==4)
                cout << endl <<i <<". Adaugati in lista dorita";
             if(i==5)
                cout << endl <<i <<". Stergeti din lista respectiva";
             if(i==6)
                cout << endl <<i <<". Afisati o lista din vectorul de obiecte lista";
             i++;
            }
         cout << endl << "Alegeti optiunea dorita din meniu ";
         cin >> optiune;
         while(optiune)
            {
             if(optiune==1)
                {
                 vectlist.citire();
                }
             if(optiune==2)
                {
                 vectlist.afisare();
                }
             if(optiune==3)
                {int nrelem,i;
                 lista concat,aux;
                 cout << endl << "Dati numarul elementelor pe care doriti sa le concatenati ";
                 cin >> nrelem;
                 for(i=0;i<nrelem;i++)
                    {concat=aux+vectlist.getlista(i);
                     aux=concat;
                    }
                 cout << endl << "Lista rezultata este : " << concat;
                }
             if(optiune==4)
                {int pozlista;
                 cout << endl << "Dati pozitia obiectului lista din vector ";
                 cin >> pozlista;
                 int val,poz;
                 cout << endl <<"Dati valoarea si pozitia nodului pe care doriti sa-l adaugati in lista : ";
                 cin >> val >> poz;
                 vectlist.getlista(pozlista).adaug(val,poz);
                 cout << vectlist.getlista(pozlista);
                }
             if(optiune==5)
                {int pozlista;
                 cout << endl << "Dati pozitia obiectului lista din vector ";
                 cin >> pozlista;
                 int poz;
                 cout << endl <<"Dati pozitia nodului pe care doriti sa-l stergeti din lista : ";
                 cin >>  poz;
                 vectlist.getlista(pozlista).sterg(poz);
                 cout << vectlist.getlista(pozlista);
                }
             if(optiune==6)
                {int pozlista;
                 cout << endl << "Dati pozitia obiectului lista din vector ";
                 cin >> pozlista;
                 cout << vectlist.getlista(pozlista);
                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
            }
         break;
        }
     case 2:
        {
         cout << "Ati ales sa lucrati cu obiecte de tipul lista";
         cout << endl << "Aveti meniul urmator : ";
         int i=1,optiune;
         while(i<=5)
            {
             if(i==1)
                cout << endl <<i <<". Citire obiecte";
             if(i==2)
                cout << endl <<i <<". Afisare obiecte";
             if(i==3)
                cout << endl <<i <<". Concatenati un numar dat de obiecte";
             if(i==4)
                cout << endl <<i <<". Adaugati in obiectul dorit";
             if(i==5)
                cout << endl <<i <<". Stergeti din obiectul respectiv";
             i++;
            }
         cout << endl << "Alegeti optiunea dorita din meniu ";
         cin >> optiune;
         while(optiune)
            {lista obj1,obj2;
             if(optiune==1)
                {
                 cin >> obj1;
                 cin >> obj2;
                }
             if(optiune==2)
                {
                 cout << obj1;
                 cout << obj2;
                }
             if(optiune==3)
                {
                 lista concat;
                 concat=obj1+obj2;
                }
             if(optiune==4)
                {

                }
             if(optiune==5)
                {

                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
            }
         break;
        }
     case 3:
        {
         cout << "Ati ales sa lucrati atat cu un vector de obiecte de tipul lista cat si cu obiecte de tipul lista";
         cout << endl << "Aveti meniul urmator : ";
         int i=1,optiune;
         while(i<=12)
            {
             if(i==1)
                cout << endl <<i <<". Citire vector de obiecte";
             if(i==2)
                cout << endl <<i <<". Afisare vector de obiecte";
             if(i==3)
                cout << endl <<i <<". Concatenati un numar dat de elemente din vector";
             if(i==4)
                cout << endl <<i <<". Adaugati in lista dorita";
             if(i==5)
                cout << endl <<i <<". Stergeti din lista respectiva";
             if(i==6)
                cout << endl <<i <<". Afisati o lista din vectorul de obiecte lista";
             if(i==7)
                cout << endl <<i <<". Citire obiecte";
             if(i==8)
                cout << endl <<i <<". Afisare obiecte";
             if(i==9)
                cout << endl <<i <<". Concatenati un numar dat de obiecte";
             if(i==10)
                cout << endl <<i <<". Adaugati in obiectul dorit";
             if(i==11)
                cout << endl <<i <<". Stergeti din obiectul respectiv";
             if(i==12)
                cout << endl <<i <<". Concatenati un numar dat de obiecte cu un numar dat de elemente din vector";
             i++;
            }
         cout << endl << "Alegeti optiunea dorita din meniu ";
         cin >> optiune;
         break;
        }
    }*/
     return 0;
}
