#include <iostream>
#include <string.h>
#include <typeinfo>
using namespace std;

class IF
{
    unsigned int nr_locuri, procent, nr_taxa;

 public:

    ///constructor si destructor
    IF()
      {
        nr_locuri = 0;
        procent = 0;
      }
    IF(unsigned int nr_a, unsigned int proc_b)
      {
          nr_locuri = nr_a;
          procent = proc_b;
          nr_taxa = nr_locuri - (procent*nr_locuri)/100;
      }
    ~IF(){};

    ///get functions
    unsigned int get_nr_locuri(){return nr_locuri;}
    unsigned int get_procent(){return procent;}
    unsigned int get_nr_taxa(){return nr_taxa;}

    ///set functions
    void set_nr_locuri(unsigned int x)
        {
            nr_locuri = x;
        }
    void set_procent(unsigned int x)
        {
            procent = x;
        }
    void set_nr_taxa()
        {
            nr_taxa = nr_locuri - (procent*nr_locuri)/100;
        }
};

class ID
{
    unsigned int nr_locuri, procent, nr_taxa;

 public:

    ///constructor si destructor
    ID()
      {
        nr_locuri = 0;
        procent = 0;
      }
    ID(unsigned int nr_a, unsigned int proc_b)
      {
          nr_locuri = nr_a;
          procent = proc_b;
          nr_taxa = nr_locuri - (procent*nr_locuri)/100;
      }
    ~ID(){};

    ///get functions
    unsigned int get_nr_locuri(){return nr_locuri;}
    unsigned int get_procent(){return procent;}
    unsigned int get_nr_taxa(){return nr_taxa;}

    ///set functions
    void set_nr_locuri(unsigned int x)
        {
            nr_locuri = x;
        }
    void set_procent(unsigned int x)
        {
            procent = x;
        }
    void set_nr_taxa()
        {
            nr_taxa = nr_locuri - (procent*nr_locuri)/100;
        }
};

class candidat
{
    char *nume;
    float medie_bac;

 public:

    ///constructori si destructori
    candidat()
        {
            nume = NULL;
            medie_bac = 0;
        }
    candidat(char *x, float cmedie_bac)
        {

        }
    ~candidat(){delete nume;}

    ///constructori de copiere si operator de atribuire
    candidat(const candidat&);
    candidat &operator=(const candidat&);

    ///get
    char * get_nume(){return nume;}
    float get_medie_bac(){return medie_bac;}

    ///set

    ///afisare si citire
    friend istream &operator >>(istream& , candidat& );
    virtual void afisare()
        {
            cout << "Candidatul are numele: " << nume << endl;
            cout << "Candidatul are media: " << medie_bac << endl;
            cout << endl;
        }
};

candidat::candidat(const candidat &cand)
{
    nume = new char [strlen(cand.nume)+1];
    strcpy(nume, cand.nume);
    medie_bac = cand.medie_bac;
}

candidat& candidat::operator=(const candidat& cand)
{
    if(this == &cand)
        return *this;

    nume = new char [strlen(cand.nume)+1];
    strcpy(nume, cand.nume);
    medie_bac = cand.medie_bac;

    return *this;
}

istream &operator>>(istream &in, candidat& cand)
{
    cout << "Dati numele candidatului: ";
    in >> cand.nume;
    cout << "Dati media de bacalaureat a candidatului: ";
    in >> cand.medie_bac;

    return in;
}

class a2f : public candidat
{
    char* prog_studii;
    float medie_absolvire;
    bool v_a2f;

 public:

    ~a2f(){delete prog_studii;}
    ///get
    char* get_prog_studii(){return prog_studii;}
    float get_medie_absolvire(){return medie_absolvire;}
    bool get_v_a2f(){return v_a2f;}
    ///afisare si citire
    friend istream &operator >>(istream&, a2f&);
    void afisare()
        {
         candidat::afisare();
         if (check_a2f())
            {
                cout << "Programul de studii este: " << prog_studii << endl;
                cout << "Media de absolvire este: " << medie_absolvire << endl;
                cout << "Aplica pentru a doua facultate" << endl << endl;
            }
         else
                cout << "Nu aplica pentru a doua facultate" << endl << endl;
        }

    int check_a2f()
    {
        if(v_a2f)
            return 1;
        return 0;
    }
};

istream& operator>>(istream& in, a2f& temp_a2f)
{
    in >> dynamic_cast <candidat&> (temp_a2f);

    cout << "Dati programul de studii: ";
    in >> temp_a2f.prog_studii;

}
class adm_id : public a2f
{
     float nota_mate;

 public:

};

class adm_if : public a2f
{

};

int main()
{
    return 0;
}
