#include <iostream>
#include <string.h>

using namespace std;

class coada;

class nod
{
 protected:
    char *info;
    nod *next;
 public:
    nod();//initializare
    nod(const nod&);//copiere
    nod(char *);//parametrizat
    nod operator= (const nod&);
    char *getinfo(){return info;}
    nod *getnext(){return next;}
    friend istream &operator>> (istream&, nod&);
    friend ostream &operator<< (ostream&, nod&);
    ~nod();//destructor
    friend class coada;
    friend class DEQUE;
    friend class DEQUE_MARCAJ;
    friend class Hibrid;
    friend istream &operator>> (istream&, coada&);
    friend ostream &operator<< (ostream&, coada&);
};

nod::nod(const nod &p)
{
 /*info = new char [strlen(p.info)+1];
 memcpy(info,p.info,(strlen(p.info)+1)*sizeof(char));*/
 info = p.info;
 next = p.next;
}

nod::nod(char *p)
{
 info = new char [strlen(p)+1];
 info = p;
 next = NULL;
}

nod::nod()
{
 info = NULL;
 next = NULL;
}

nod::~nod()
{
 delete []info;
 delete next;
}

nod nod::operator=(const nod&p)
{
 /*this->info = new char [strlen(p.info)+1];
 memcpy(this->info,p.info,(strlen(p.info)+1)*sizeof(char));*/
 this->info = p.info;
 this->next = p.next;
 return *this;
}

istream &operator>>(istream &in, nod &p)
{
 int dim;
 cout << "Dati dimensiunea cuvantului dorit ";
 in >> dim;
 p.info = new char[dim+1];
 in >> p.info;
 return in;
}

ostream &operator<<(ostream& out, nod &p)
{
 out << p.info;
 return out;
}

class coada
{
 protected:
    nod *prim, *ultim;
    int dim_max; // pentru tratarea exceptiilor
 public:
     coada();//
     coada(nod *);//
     coada(const coada&);//
     coada operator= (const coada&);//
     bool isempty();//
     virtual void inserare(char *);//
     char* top();//
     virtual void pop();//
     void golire();//
     virtual void afis();
     friend class Hibrid;
     friend istream &operator>> (istream&, coada&);//
     friend ostream &operator<< (ostream&, coada&);//
     ~coada();//
};

coada::coada()
{
    prim = ultim = NULL;
    dim_max = 0;
};

coada::coada(nod *p)
{
 prim = p;
 ultim = NULL;
 dim_max = 1;
}

coada::coada(const coada &qu)
{
 int cont = 0;
 nod *temp = qu.prim;
 nod *temp_this;
 while(temp != NULL)
    {
        temp_this = new nod;
        temp_this -> info = new char [strlen(temp->info)+1];
        memcpy(temp_this ->info, temp->info, strlen(temp->info)*sizeof(char));
        if(cont == 0)
            {
             prim = ultim = temp_this;
             cont++;
            }
        else
            {
             ultim->next = temp_this;
             ultim = temp_this;
            }
        temp = temp->next;
    }

}

coada coada::operator=(const coada &qu)
{
 while(!this -> isempty())
    {
        this -> pop();
    }
 nod *temp = qu.prim;
 while(temp != NULL)
    {
        this -> inserare(temp -> info);
        temp = temp->next;
    }
 return *this;
}

bool coada::isempty()
{
 return (this -> prim == NULL);
}

void coada::inserare(char *cuv)
{
 nod *crt = new nod;
 crt -> info = new char[strlen(cuv)+1];
 memcpy(crt -> info, cuv, (strlen(cuv)+1)*sizeof(char));
 crt -> next = NULL;
 if (isempty())
            prim = ultim = crt;
 else
    {
        ultim -> next = crt;
        ultim = crt;
    }
}

char* coada::top()
{
 if(isempty())
    {
        cout<<"Coada este goala";
        return 0;
    }
 return prim -> info;
}

void coada::pop()
{
 if(isempty())
    {
        cout<<"Coada este goala";
        return;
    }
 nod *temp = prim;
 //cout << "Informatia elementului care va fi  eliminat din coada este " << temp -> info;
 prim = prim->next;
 delete temp;
}

void coada::golire()
{
 if(this->isempty())
        cout<<"Coada este goala";
 else
    {
     while(!this->isempty())
        this->pop();
    }
}

istream &operator>>(istream &in, coada &qu)
{
 int dim;
 cout << "Dati dimensiunea cuvantului dorit ";
 in >> dim;
 char *citire = new char [dim+1];
 in >> citire;
 /*cout << "Dati dimensiunea maxima a listei ";
 in >> qu.dim_max;*/
 qu.inserare(citire);
 return in;
}

ostream &operator<<(ostream &out, coada &qu)
{
 if (qu.isempty())
    out << "Coada goala";
 else
    while (!qu.isempty())
        {
         out << qu.prim -> info << endl;
         qu.pop();
        }
 return out;
}

coada::~coada()
{
  delete prim;
  delete ultim;
}

class Hibrid : public coada
{
 public:
        Hibrid():coada(){}
        void afis(){coada::afis();}
        friend ostream &operator<< (ostream&, Hibrid&);//
        ~Hibrid(){}
};

ostream& operator<<(ostream& out, Hibrid p)
{
 if (p.isempty())
    out << "Hibrid gol";
 else
    while (!p.isempty())
        {
         out << p.prim -> info << endl;
         p.pop();
        }
 return out;
}

class DEQUE : public coada
{
     char capat[100];
 public:
     DEQUE():coada()
        {
         strcpy(capat,"inceput");
        }
     friend istream &operator>> (istream&, DEQUE&);
     friend ostream &operator<< (ostream&, DEQUE&);
     void inserare(char *);
     void pop();
     ~DEQUE(){}
};

void DEQUE::inserare(char *cuv)
{
 cout << "Dati tipul de inserare pe care il doriti : ";
 cin >> capat;
 if(strcmp(capat,"sfarsit")==0)
    {
     coada::inserare(cuv);
    }
 if(strcmp(capat,"inceput")==0)
        {
         nod *crt = new nod;
         crt -> info = new char[strlen(cuv)+1];
         memcpy(crt -> info, cuv, (strlen(cuv)+1)*sizeof(char));
         crt -> next = prim;
         if (isempty())
            prim = ultim = crt;
         else
            {
             prim = crt;
            }
        }
}

void DEQUE::pop()
{
 cout << "Dati tipul de extragere pe care il doriti : ";
 cin >> capat;
 if(strcmp(capat,"inceput")==0)
    coada::pop();
 if(strcmp(capat,"sfarsit")==0)
    {
     if(isempty())
        {
         cout<<"Coada este goala";
         return;
        }
     if(prim == ultim)
        {
         nod *temp = ultim;
         prim = prim->next;
         delete temp;
        }
     else
        {
            nod *temp = prim;
            nod *tmp = ultim;
            while (temp->next != ultim)
                temp = temp -> next;
            temp -> next = NULL;
            delete tmp;
            ultim = temp;
        }
    }
}

istream &operator>> (istream &in, DEQUE &deq)
{
 int dim;
 cout << "Dati dimensiunea cuvantului dorit ";
 in >> dim;
 char *citire = new char [dim+1];
 in >> citire;
 /*cout << "Dati dimensiunea maxima a listei ";
 in >> qu.dim_max;*/
 deq.inserare(citire);
 return in;
}

ostream &operator<< (ostream &out, DEQUE &deq)
{
 if (deq.isempty())
    out << "Coada goala";
 else
    while (!deq.isempty())
        {
         out << deq.prim->getinfo() << endl;
         deq.pop();
        }
 return out;
}

class DEQUE_MARCAJ : public coada
{
    nod  *marcaj;
    char capat[100];
 public:
    DEQUE_MARCAJ():coada()
        {
         strcpy(capat,"inceput");
         char *marc = new char [2];
         memcpy(marc, "~", 2*sizeof(char));//am stabilit ca informatie de marcaj simbolul ~
         marcaj -> info = new char [2];
         memcpy(marcaj -> info, marc, 2*sizeof(char));
         marcaj -> next = prim;
         prim = marcaj;
        }
    friend istream &operator>> (istream&, DEQUE_MARCAJ&);
    friend ostream &operator<< (ostream&, DEQUE_MARCAJ&);
    void inserare(char *);
    void pop();
    ~DEQUE_MARCAJ(){}
};

void DEQUE_MARCAJ::inserare(char * cuv)
{
 /*if(prim == NULL)
    coada::inserare(marcaj->info);*/
 cout << "Dati tipul de inserare pe care il doriti : ";
 cin >> capat;
 if(strcmp(capat,"sfarsit")==0)
    {
     //coada::inserare();
     nod *crt = new nod;
     crt -> info = new char[strlen(cuv)+1];
     memcpy(crt -> info, cuv, (strlen(cuv)+1)*sizeof(char));
     crt -> next = marcaj;
     if (prim == marcaj)
            prim = ultim = crt;
     else
        {
         ultim -> next = crt;
         ultim = crt;
        }
    }
 if(strcmp(capat,"inceput")==0)
        {
         nod *crt = new nod;
         crt -> info = new char[strlen(cuv)+1];
         memcpy(crt -> info, cuv, (strlen(cuv)+1)*sizeof(char));
         crt -> next = prim;
         if (prim == marcaj && ultim == marcaj)
            prim = ultim = crt;
         else
            {
             prim = crt;
            }
        }
}

void DEQUE_MARCAJ::pop()
{
 /*if(prim==NULL)
    coada::inserare(marcaj->info);*/
 cout << "Dati tipul de extragere pe care il doriti : ";
 cin >> capat;
 if(strcmp(capat,"inceput")==0)
    {
     //coada::pop();
     if(prim==marcaj)
        {
         cout<<"Coada este goala";
         return;
        }
     nod *temp = prim;
     //cout << "Informatia elementului care va fi  eliminat din coada este " << temp -> info;
     prim = prim->next;
     delete temp;
    }
 if(strcmp(capat,"sfarsit")==0)
    {
     if(prim==marcaj)
        {
         cout<<"Coada este goala";
         return;
        }
     if(prim == marcaj &&  ultim == marcaj)
        {
         nod *temp = ultim;
         prim = prim -> next;
         delete temp;
        }
     else
        {
            nod *temp = prim;
            nod *tmp = ultim;
            while (temp->next != ultim)
                temp = temp -> next;
            temp -> next = NULL;
            delete tmp;
            ultim = temp;
        }
    }
}

istream &operator>> (istream &in, DEQUE_MARCAJ &deq)
{
 int dim;
 cout << "Dati dimensiunea cuvantului dorit ";
 in >> dim;
 char *citire = new char [dim+1];
 in >> citire;
 /*cout << "Dati dimensiunea maxima a listei ";
 in >> qu.dim_max;*/
 deq.inserare(citire);
 return in;
}

ostream &operator<< (ostream &out, DEQUE_MARCAJ &deq)
{
 if (deq.isempty())
    out << "Coada goala";
 else
    while (!deq.isempty())
        {
         out << deq.prim->getinfo() << endl;
         deq.pop();
        }
 return out;
}

class nr_ob
{
        int nr;
        coada *v;
    public:
        void citire(int);
        void afisare(int);
        void dimenmax(int,int);
        int citireNrob();
        coada getcoada(int);
        friend istream &operator>> (istream &in, coada &qu);
        friend ostream &operator<< (ostream &out, coada &qu);
        friend class coada;
        ~nr_ob(){ delete []v; }
};

int nr_ob::citireNrob()
{
  cout << "Dati numarul de obiecte de tip coada";
  cin >> nr;
  v = new coada[nr+1];
  return nr;
}

void nr_ob::citire(int nrcoada)
{
    cin >> v[nrcoada];
}

/*void nr_ob::dimenmax(int dimmax,int nrcoada)
{
 v[nrcoada].dim_max=dimmax;
}*/

void nr_ob::afisare(int nrcoada)
{
    cout << v[nrcoada];
}

coada nr_ob::getcoada(int nrcoada)
{
    return v[nrcoada];
}

class Obiect
{
 protected:
    int id;
    string denumire;
 public :
     Obiect(){id++;}
     Obiect(string);
     Obiect(const Obiect&);//copiere
     Obiect operator= (const Obiect&);
     friend class Obiect_Actualizat;
     friend class Obiect_Personalizat;
     friend class Proiect;
     friend istream &operator>> (istream&, Obiect&);
     friend ostream &operator<< (ostream&, Obiect&);
     ~Obiect(){}
};

Obiect::Obiect(string s)
{
 //id++;
 denumire = s;
}

Obiect::Obiect(const Obiect &p)
{
 /*info = new char [strlen(p.info)+1];
 memcpy(info,p.info,(strlen(p.info)+1)*sizeof(char));*/
 id = p.id;
 denumire = p.denumire;
}

Obiect Obiect::operator= (const Obiect& temp)
{
 this->id = temp.id;
 this->denumire = temp.denumire;
 return *this;
}

istream &operator>>(istream &in, Obiect &p)
{
 cout << "Dati denumirea cuvantului dorit ";
 in >> p.denumire;
 return in;
}

ostream &operator<<(ostream& out, Obiect &p)
{
 out << p.denumire;
 return out;
}

class Obiect_Actualizat : public Obiect
{
 protected:
    string data;
 public:
    Obiect_Actualizat():Obiect()
        {
            data = "Noiembrie";
        }
    Obiect_Actualizat(string s):Obiect()
        {
         data = s;
        }
     Obiect_Actualizat(const Obiect_Actualizat&);//copiere
     Obiect_Actualizat operator= (const Obiect_Actualizat&);
     friend istream &operator>> (istream&, Obiect_Actualizat&);
     friend ostream &operator<< (ostream&, Obiect_Actualizat&);
     ~Obiect_Actualizat(){}
};

Obiect_Actualizat::Obiect_Actualizat(const Obiect_Actualizat &p)
{
 /*info = new char [strlen(p.info)+1];
 memcpy(info,p.info,(strlen(p.info)+1)*sizeof(char));*/
 Obiect::Obiect(p);
 data=p.data;
}

Obiect_Actualizat Obiect_Actualizat()::operator= (const Obiect_Actualizat& temp)
{
 Obiect::operator=(temp);
 this->data=temp.data;
 return *this;
}

class Obiect_Personalizat : public Obiect
{
 protected:
    char* autor_proiect;
 public:
     Obiect_Personalizat():Obiect()
        {
         /*char s[1000];
         cout << "Dati autorul proiectului";
         cin >> s;
         char* autor_proiect = new char [strlen(s)+1];
         memcpy(autor_proiect, s, (strlen(s)+1)*sizeof(char));*/
         autor_proiect = NULL;
        }
     Obiect_Personalizat(char *x):Obiect()
        {
            autor_proiect = new char [strlen(x)+1];
            memcpy(autor_proiect, x , (strlen(x)+1)*sizeof(char));
        }
     Obiect_Personalizat(const Obiect_Personalizat&);//copiere
     Obiect_Personalizat operator= (const Obiect_Personalizat&);
     friend istream &operator>> (istream&, Obiect_Personalizat&);
     friend ostream &operator<< (ostream&, Obiect_Personalizat&);
     ~Obiect_Personalizat(){delete []autor_proiect;}
};

Obiect_Personalizat::Obiect_Personalizat(const Obiect_Personalizat &p)
{
 /*info = new char [strlen(p.info)+1];
 memcpy(info,p.info,(strlen(p.info)+1)*sizeof(char));*/
 Obiect::Obiect(p);
 autor_proiect=p.autor_proiect;
}

Obiect_Personalizat Obiect_Personalizat()::operator= (const Obiect_Personalizat& temp)
{
 Obiect::operator=(temp);
 this->autor_proiect=temp.autor_proiect;
 return *this;
}

class Proiect : public Obiect_Actualizat, public Obiect_Personalizat
{
 public:
        Proiect():Obiect_Actualizat()
            {
                ;
            }
        Proiect():Obiect_Personalizat()
            {
                ;
            }
        Proiect(const Proiect&);
        Proiect operator= (const Proiect&);
        ~Proiect(){}
};

Proiect::Proiect (const Proiect &p)
{string s;
 cout << Dati tipul de obiect;
 cin >> s;
 if(s=="Actualizat")
    {
     Obiect_Actualizat::Obiect_Actualizat(p);
    }
 if(s=="Personalizat")
    {
     Obiect_Personalizat::Obiect_Personalizat(p);
    }
}

Proiect Proiect::operator=(const Proiect& temp)
{
 string s;
 cout << Dati tipul de obiect;
 cin >> s;
 if(s=="Actualizat")
    {
     Obiect_Actualizat::operator=(temp);
    }
 if(s=="Personalizat")
    {
     Obiect_Personalizat::operator=(temp);
    }
}
int main()
{
 nr_ob vect;
 coada q1,q2;
 DEQUE q3,q4;
 DEQUE_MARCAJ q5,q6;
 int i,nr,expr,dimmax,dimmaxtest;
 cout << "Introduceti numarul de cozi: ";
 nr = vect.citireNrob();
 cout << endl << "ATENTIE! ORICE COADA DIN CLASA DEQUE_MARCAJ VA INCEPE CU CARACTERUL ~" << endl;
 i=1;
 while(i<=4)
    {
      if(i==1)
         cout << "1.Lucrati cu un vector de obiecte de tipul coada";
      if(i==2)
         cout << endl << "2.Lucrati cu obiecte de tipul coada";
      if(i==3)
         cout << endl << "3.Lucrati cu obiecte de tipul DEQUE";
      if(i==4)
         cout << endl << "4.Lucrati cu obiecte de tipul DEQUE_MARCAJ";
      i++;
    }
 cout << endl << "Alegeti una din optiunile mentionate anterior ";
 cin >> expr;
 cout << "Dati numarul maxim general de cuvinte dintr-o coada ";
 cin >> dimmax;
 switch(expr)
    {
     case 1:
         {
          cout << "Dati numarul maxim de cuvinte dintr-o coada ";
          cin >>  dimmaxtest;
          try
            {
             cout << "Ati ales sa lucrati cu un vector de obiecte de tipul lista";
             if(dimmaxtest>dimmax)
                throw 123;
             cout << endl << "Aveti meniul urmator : ";
             int j=1,optiune;
             while(j<=2)
                {
                 if(j==1)
                    cout << endl <<j <<". Citire vector de obiecte";
                 if(j==2)
                    cout << endl <<j <<". Afisare vector de obiecte";
                 j++;
                }
             for( i = 1; i <= nr; i++)
                vect.dimenmax(dimmax,i);
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
             while(optiune)
                {
                 if(optiune==1)
                    {
                     for( i = 1; i <= nr; i++)
                        {
                         cout << "Introduceti elementele cozii numarul: " << i <<endl;
                         vect.citire(i);
                        }
                    }
                 if(optiune==2)
                    {
                     for( i = 1; i <= nr; i++)
                        vect.afisare(i);
                    }
                }
            }
          catch(int i)
            {
             dimmaxtest=dimmax;
            }
          break;
         }
     case 2:
        {
          cout << "Dati numarul maxim de cuvinte dintr-o coada ";
          cin >>  dimmaxtest;
          try
            {
             cout << "Ati ales sa lucrati cu obiecte de tipul coada";
             if(dimmaxtest>dimmax)
                throw 123;
             cout << endl << "Aveti meniul urmator : ";
             q1.dim_max=dimmaxtest;
             q2.dim_max=dimmaxtest;
             int j=1,optiune;
             while(j<=6)
                {
                 if(j==1)
                    cout << endl << j <<". Citire cozi";
                 if(j==2)
                    cout << endl << j <<". Afisare cozi";
                 if(j==3)
                    cout << endl << j <<". Insert cuvant in coada";
                 if(j==4)
                    cout << endl << j <<". Elimina cuvant din coada";
                 if(j==5)
                    cout << endl << j <<". Primul cuvant din coada";
                 if(j==6)
                    cout << endl << j <<". Golire coada";
                 j++;
                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
             while(optiune)
                {
                 if(optiune==1)
                    {
                     cout << endl <<"Cititi coada q1 ";
                     cin >> q1;
                     cout << endl <<"Cititi coada q2 ";
                     cin >> q2;
                    }
                 if(optiune==2)
                    {
                     cout << "Coada 1 este : " << endl;
                     cout << q1;
                     cout << "Coada 2 este : " << endl;
                     cout << q2;
                    }
                 if(optiune==3)
                    {char *cuvant;
                     int dim;
                     cout << "Dati dimensiunea cuvantului";
                     cin >> dim;
                     cuvant = new char [dim+1];
                     cout << "Dati cuvantul pe care doriti sa-l inserati ";
                     cin >> cuvant;
                     q1.inserare(cuvant);
                    }
                 if(optiune==4)
                    {
                     cout << "Coada initiala" << endl;
                     cout << q1;
                     q1.pop();
                     cout << "Coada dupa pop" << endl;
                     cout << q1;
                    }
                 if(optiune==5)
                    {
                     cout << "Primul cuvant este " << q1.top();
                    }
                 if(optiune==6)
                    {
                     q1.golire();
                     cout << q1;
                    }
                }
            }
         catch(int i)
                {
                 dimmaxtest=dimmax;
                }
         break;
        }
     case 3:
        {
          cout << "Dati numarul maxim de cuvinte dintr-o coada ";
          cin >>  dimmaxtest;
          try
            {
             cout << "Ati ales sa lucrati cu obiecte de tipul DEQUE";
             if(dimmaxtest>dimmax)
                throw 123;
             cout << endl << "Aveti meniul urmator : ";
             q1.dim_max=dimmaxtest;
             q2.dim_max=dimmaxtest;
             int j=1,optiune;
             while(j<=6)
                {
                 if(j==1)
                    cout << endl << j <<". Citire cozi";
                 if(j==2)
                    cout << endl << j <<". Afisare cozi";
                 if(j==3)
                    cout << endl << j <<". Insert cuvant in coada";
                 if(j==4)
                    cout << endl << j <<". Elimina cuvant din coada";
                 if(j==5)
                    cout << endl << j <<". Primul cuvant din coada";
                 if(j==6)
                    cout << endl << j <<". Golire coada";
                 j++;
                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
             while(optiune)
                {
                 if(optiune==1)
                    {
                     cout << endl <<"Cititi coada q3 ";
                     cin >> q3;
                     cout << endl <<"Cititi coada q4 ";
                     cin >> q4;
                    }
                 if(optiune==2)
                    {
                     cout << "Coada 3 este : " << endl;
                     cout << q3;
                     cout << "Coada 4 este : " << endl;
                     cout << q4;
                    }
                 if(optiune==3)
                    {char *cuvant;
                     int dim;
                     cout << "Dati dimensiunea cuvantului";
                     cin >> dim;
                     cuvant = new char [dim+1];
                     cout << "Dati cuvantul pe care doriti sa-l inserati ";
                     cin >> cuvant;
                     q3.inserare(cuvant);
                    }
                 if(optiune==4)
                    {
                     cout << "Coada initiala" << endl;
                     cout << q3;
                     q3.pop();
                     cout << "Coada dupa pop" << endl;
                     cout << q3;
                    }
                 if(optiune==5)
                    {
                     cout << "Primul cuvant este " << q3.top();
                    }
                 if(optiune==6)
                    {
                     q3.golire();
                     cout << q3;
                    }
                }
            }
         catch(int i)
                {
                 dimmaxtest=dimmax;
                }
         break;
        }
     case 4:
        {
          cout << "Dati numarul maxim de cuvinte dintr-o coada ";
          cin >>  dimmaxtest;
          try
            {
             cout << "Ati ales sa lucrati cu obiecte de tipul DEQUE_MARCAJ";
             if(dimmaxtest>dimmax)
                throw 123;
             cout << endl << "Aveti meniul urmator : ";
             q1.dim_max=dimmaxtest;
             q2.dim_max=dimmaxtest;
             int j=1,optiune;
             while(j<=6)
                {
                 if(j==1)
                    cout << endl << j <<". Citire cozi";
                 if(j==2)
                    cout << endl << j <<". Afisare cozi";
                 if(j==3)
                    cout << endl << j <<". Insert cuvant in coada";
                 if(j==4)
                    cout << endl << j <<". Elimina cuvant din coada";
                 if(j==5)
                    cout << endl << j <<". Primul cuvant din coada";
                 if(j==6)
                    cout << endl << j <<". Golire coada";
                 j++;
                }
             cout << endl << "Alegeti optiunea dorita din meniu ";
             cin >> optiune;
             while(optiune)
                {
                 if(optiune==1)
                    {
                     cout << endl <<"Cititi coada q5 ";
                     cin >> q5;
                     cout << endl <<"Cititi coada q6 ";
                     cin >> q6;
                    }
                 if(optiune==2)
                    {
                     cout << "Coada 5 este : " << endl;
                     cout << q5;
                     cout << "Coada 6 este : " << endl;
                     cout << q6;
                    }
                 if(optiune==3)
                    {char *cuvant;
                     int dim;
                     cout << "Dati dimensiunea cuvantului";
                     cin >> dim;
                     cuvant = new char [dim+1];
                     cout << "Dati cuvantul pe care doriti sa-l inserati ";
                     cin >> cuvant;
                     q5.inserare(cuvant);
                    }
                 if(optiune==4)
                    {
                     cout << "Coada initiala" << endl;
                     cout << q5;
                     q5.pop();
                     cout << "Coada dupa pop" << endl;
                     cout << q5;
                    }
                 if(optiune==5)
                    {
                     cout << "Primul cuvant este " << q5.top();
                    }
                 if(optiune==6)
                    {
                     q1.golire();
                     cout << q5;
                    }
                }
            }
         catch(int i)
                {
                 dimmaxtest=dimmax;
                }
         break;
        }
    }
 Obiect a("Obiect1");
 cout << a;
 Obiect_Personalizat b(a, "Ionescu");
 char s[100]="Proiectul ";
 strcat(s,a.denumire);
 strcat(s,"este actualizat de ");
 strcat(s,b.autor_proiect);
 cout<<s;
 int n,i;
 coada **v;
 cout << "Dati dimensiune vector";
 cin >> n;
 *v=new coada[n]
 for(i=0;i<n;i++)
    {
     v[i]=new Hibrid();
     v[i].afis();
    }
 try
    {cout << "Id ul este numar natural?"
     if(a.id<0 && a.id/10%10=='.')
            throw 1;
     cout << "Nu"
    }
 catch(unsigned int i)
    {
        a.id=(unsigned int)a.id;
    }
    Obiect_Actualizat c;
 try
    {
     cout << "Stringul are cifre?"
     if(strchr(a.denumire,"0123456789") || strchr(b.autor_proiect,"0123456789") || strchr(c.data,"0123456789"))
    }
 catch
    {

    }
 try
    {

    }
 catch
    {

    }
 return 0;
}
