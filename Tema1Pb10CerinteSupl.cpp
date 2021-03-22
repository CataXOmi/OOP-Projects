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
    lista(nod *p){prim = p ;ult = NULL ;nr_crt=1;}
    ~lista();//checked
    lista(const lista&);//checked
    void adaug(int,int);//checked
    friend istream& operator>>(istream&,lista&);//checked
    friend ostream& operator<<(ostream&,lista&);//checked
    lista& operator=(const lista&);//checked
    void sterg(int);//checked
    lista(bool,const lista&);
    friend lista operator+(lista&,lista&);//checked
    void afisdim();//checked
    friend lista operator-(lista&);
    friend lista operator--(lista&);
    friend int operator!=(lista&,lista&);
};

class nr_obiecte
{
 int n;
 lista *v;
 public:
     void citire(int);
     void afisare(int);
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

lista::lista(bool t, const lista& l)
{if(t==1)
    {int val=1,poz;//am considerat 1 ca true
     cout << "Dati pozitia pe care doriti sa adaugati in lista";
     cin >> poz;
     this->adaug(val,poz);
    }
 if(t==0)
    {int val=0,poz;//am considerat 0 ca false
     cout << "Dati pozitia pe care doriti sa adaugati in lista";
     cin >> poz;
     this->adaug(val,poz);
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

lista operator-(lista& l1)
{lista l;
 int i=0;
 nod * crt = l1.prim;
 while(crt != NULL)
    {if(crt->getinfo()==0)
        {
         l.adaug(crt->getinfo(),i);
         i++;
         crt=crt->getnext();
        }
     else
        {
         l.adaug(crt->getinfo()*(-1),i);
         i++;
         crt=crt->getnext();
        }
    }
 return l;
}

lista operator--(lista& l1)
{lista l;
 int i=0;
 nod * crt = l1.prim;
 while (crt != NULL)
    {
     l.adaug(crt->getinfo()-1,i);
     i++;
     crt=crt->getnext();
    }
 return l;
}

int operator!=(lista& l1,lista& l2)
{nod * crt1 = l1.prim;
 nod * crt2 = l2.prim;
 int ok=0;
 int i=0,j=0;
 while(crt1 != NULL || crt2 !=NULL)
    {if(crt1->getinfo() != crt2->getinfo())
                ok=1;
     i++;
     j++;
     if((i==l1.nr_crt || j==l2.nr_crt) && i!=j)
        {
          ok=1;
        }
     else
        {crt1=crt1->getnext();
         crt2=crt2->getnext();
        }
    }
 return ok;
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
             cout << "Pozitia data nu se afla in lista noastra, dar este mai mare ca dimensiunea acesteia asa ca vom sterge ultimul element" << endl;
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
             cout << "Pozitia data nu se afla in lista noastra, dar este mai mica ca pozitia primului element asa ca il vom sterge pe acesta" << endl;
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
        cout << "Lista este vida" << endl;
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
{int expr;
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
        {int nobj;
         nr_obiecte vectlist;
         nobj=vectlist.nr_elem();
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
                cout << endl <<i <<". Concatenati doua liste pe care le doriti din vector";
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
                 vectlist.citire(nobj);
                }
             if(optiune==2)
                {
                 vectlist.afisare(nobj);
                }
             if(optiune==3)
                {int poz1,poz2;
                 lista concat;
                 cout << endl << "Alegeti doua elemente pe care doriti sa le concatenati ";
                 cin >> poz1 >> poz2;
                 concat=vectlist.getlista(poz1) + vectlist.getlista(poz2);
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
                cout << endl <<i <<". Concatenati obiecte";
             if(i==4)
                cout << endl <<i <<". Adaugati in obiectul dorit";
             if(i==5)
                cout << endl <<i <<". Stergeti din obiectul respectiv";
             i++;
            }
         cout << endl << "Alegeti optiunea dorita din meniu ";
         cin >> optiune;
         lista obj1,obj2;
         while(optiune)
            {
             if(optiune==1)
                {
                 cin >> obj1;
                 cin >> obj2;
                }
             if(optiune==2)
                {
                 cout << obj1;
                 cout << endl <<obj2;
                }
             if(optiune==3)
                {
                 lista concat;
                 concat=obj1+obj2;
                 cout << endl << "Lista rezultata este : " << concat;
                }
             if(optiune==4)
                {
                 int poz,val;
                 cout << endl <<"Dati valoarea si pozitia nodului pe care doriti sa-l adaugati in lista : ";
                 cin >> val >> poz;
                 obj1.adaug(val,poz);
                 cout << obj1;
                }
             if(optiune==5)
                {
                 int poz;
                 cout << endl <<"Dati pozitia nodului pe care doriti sa-l stergeti din lista : ";
                 cin >>  poz;
                 obj1.sterg(poz);
                 cout << obj1;
                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
            }
         break;
        }
     case 3:
        {int nobj;
         nr_obiecte vectlist;
         nobj=vectlist.nr_elem();
         lista obj1,obj2;
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
                cout << endl <<i <<". Concatenati doua liste pe care le doriti din vector";
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
                cout << endl <<i <<". Concatenati obiecte";
             if(i==10)
                cout << endl <<i <<". Adaugati in obiectul dorit";
             if(i==11)
                cout << endl <<i <<". Stergeti din obiectul respectiv";
             if(i==12)
                cout << endl <<i <<". Concatenati un obiect cu o lista din vector";
             i++;
            }
         cout << endl << "Alegeti optiunea dorita din meniu ";
         cin >> optiune;
         while(optiune)
            {
             if(optiune==1)
                {
                 vectlist.citire(nobj);
                }
             if(optiune==2)
                {
                 vectlist.afisare(nobj);
                }
             if(optiune==3)
                {int poz1,poz2;
                 lista concat;
                 cout << endl << "Alegeti doua elemente pe care doriti sa le concatenati ";
                 cin >> poz1 >> poz2;
                 concat=vectlist.getlista(poz1) + vectlist.getlista(poz2);
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
             if(optiune==7)
                {
                 cin >> obj1;
                 cin >> obj2;
                }
             if(optiune==8)
                {
                 cout << obj1;
                 cout << endl <<obj2;
                }
             if(optiune==9)
                {
                 lista concat;
                 concat=obj1+obj2;
                 cout << endl << "Lista rezultata este : " << concat;
                }
             if(optiune==10)
                {
                 int poz,val;
                 cout << endl <<"Dati valoarea si pozitia nodului pe care doriti sa-l adaugati in lista : ";
                 cin >> val >> poz;
                 obj1.adaug(val,poz);
                 cout << obj1;
                }
             if(optiune==11)
                {
                 int poz;
                 cout << endl <<"Dati pozitia nodului pe care doriti sa-l stergeti din lista : ";
                 cin >>  poz;
                 obj1.sterg(poz);
                 cout << obj1;
                }
             if(optiune==12)
                {
                 int pozlista;
                 cout << endl <<"Alegeti lista pe care doriti sa o concatenati cu un obiect din afara vectorului ";
                 cin >> pozlista;
                 lista concat;
                 concat=vectlist.getlista(pozlista)+obj1;
                 cout << endl << "Lista rezultata este : " << concat;
                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
            }
         break;
        }
    }
 lista l;
 cout << "l = "<<endl;
 cin >> l;
 l = --l;
 cout << endl <<l;
 lista v[4];
 cout << "v[1] = "<<endl;
 cin >> v[1];
 cout << v[1];
 v[2]=v[3]=(v[1]+v[1]);
 cout << endl <<v[2];
 if(v[1]!=v[2])
    cout << "Cele doua liste au cel putin un element diferit";
 else
    cout << "Cele doua liste nu difera";
     return 0;
}
