
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <unordered_map>
using namespace std;


class elev
{
private:
    int id_elev;
    string nume;
    string prenume;

public:
    elev(int,string,string);
    elev(elev&);
    ~elev();
    friend istream& operator>>(istream& in, elev& z);
    friend ostream& operator<<(ostream& out, elev &z);
    void citire_elev(istream& in);
    void afisare_elev(ostream& out);
    friend class examen;
    elev& operator=(elev& z);

};

elev::elev( int id=0, string nume="", string prenume="")
{
    id_elev=id;
    nume=nume;
    prenume=prenume;
}

elev::elev(elev& z)
{

    id_elev=z.id_elev;
    nume=z.nume;
    prenume=z.prenume;
}

elev::~elev()
{

}

void elev::citire_elev(istream& in)
{
    cout<<"Cititi id-ul elevului: ";
    in>>id_elev;
    cout<<endl;

    cout<<"Cititi numele elevului: ";
    string s;
    in>>s;
    nume=s;
    cout<<endl;

    cout<<"Cititi prenumele elevului: ";
    in.get();
    in>>s;
    prenume=s;
    cout<<endl;
}

istream &operator>>(istream& in, elev& z)
{
    z.citire_elev(in);
    return in;
}

void elev::afisare_elev(ostream& out)
{
    out<<"ID-ul elevului este: "<<id_elev<<endl;
    out<<"Numele elevului este: "<<nume<<endl;
    out<<"Prenumele elevului este "<<prenume<<endl;
}

ostream &operator<<(ostream &out, elev& z)
{
    z.afisare_elev(out);
    return out;
}

elev &elev::operator=(elev& z)
{
    if(this!=&z)
    {
        id_elev=z.id_elev;
        nume=z.nume;
        prenume=z.prenume;

    }
    return *this;
}


//--------------------------------------------------------------------

class examen
{
protected:
    static int nr_examene;
    int nr;
    int id_examen;
    string materie;
    float *notaScris;
    elev* e;

public:
    examen(int,int,string, float*,elev*);
    virtual ~examen();
    examen(const examen &);
    friend istream& operator>>(istream& in, examen& z);
    friend ostream& operator<<(ostream& out, examen& z);
    virtual void citire(istream &in);
    virtual void afisare(ostream& out);
    examen& operator =(examen &z);
};

int examen::nr_examene=0;

examen::examen(int nr=0, int id=0, string materie="", float nota[]=0,elev* E=NULL)
{
    nr_examene++;
    nr=nr;
    id_examen=id;
    materie=materie;
    notaScris=new float[nr];
    int i;
    E=new elev[nr];
    for(i=0; i<nr; i++)
    {
        e[i]=E[i];
    }

    for(i=0; i<nr; i++)
    {
        notaScris[i]=nota[i];
    }

}

examen::~examen()
{
    nr_examene--;
    delete[]notaScris;
}

examen::examen(const examen& z)
{
    nr_examene++;
    id_examen=z.id_examen;
    nr=z.nr;
    materie=z.materie;
    int i;
    notaScris=new float[nr];
    for(i=0; i<nr; i++)
    {
        notaScris[i]=z.notaScris[i];
        e[i]=z.e[i];
    }
}

void examen::citire(istream&in)
{


    cout<<"Citire ID examen: ";
    in>>id_examen;
    try
    {
        if(id_examen<=0)
            throw 10;

    }
    catch(int x)
    {
        cout<<"ID-ul trebuie sa fie un numar pozitiv"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<endl;
    string s;
    cout<<"Denumirea materiei: ";
    in.get();
    in>>s;
    materie=s;
    cout<<endl;

    cout<<"Citire numar elevi: ";
    in>>nr;
    cout<<endl;

    int i;
    e=new elev[nr];
    notaScris=new float[nr];
    for(i=0; i<nr; i++)
    {
        cout<<"Citire date elev "<<i+1<<" : "<<endl;
        in>>e[i];
        cout<<"Cititre nota scris: ";
        in>>notaScris[i];
        try
        {
            if(notaScris[i]<1 || notaScris[i]>10)
                throw 10;
        }
        catch(int x)
        {
            cout<<"Nota trebuie sa fie cuprinsa intre 1 si 10"<<endl;
            exit(EXIT_FAILURE);
        }
        cout<<endl;
    }
    cout<<endl;

}

istream& operator>>(istream&in, examen& z)
{
    z.citire(in);
    return in;
}

void examen::afisare(ostream& out)
{
    out<<"ID examen: ";
    out<<id_examen;
    out<<endl;
    out<<"Denumirea materiei: "<<materie<<endl;
    out<<"Numarul de elevi: "<<nr<<endl;
    int i;
    for(i=0; i<nr; i++)
    {
        out<<"Date elev "<<i+1<<" : "<<endl;
        out<<e[i];
        out<<"Nota elevului la scris: "<<notaScris[i]<<endl;
    }

    out<<endl;


}

ostream& operator<<(ostream &out, examen &z)
{
    z.afisare(out);
    return out;
}

examen &examen::operator =(examen& z)
{
    if(this!= &z)
    {
        id_examen=z.id_examen;
        materie=z.materie;
        nr=z.nr;
        e=new elev[nr];
        notaScris=new float[nr];
        int i;
        for(i=0; i<nr; i++)
        {
            e[i]=z.e[i];
            notaScris[i]=z.notaScris[i];
        }
    }

    return *this;
}

//-----------------------------------------------

class partial:public examen
{
protected:
    float *notaOral;

public:
    partial(int,int,string,float*,elev*,float*);
    ~partial();
    partial(partial&);
    friend istream &operator>>(istream& in,partial &z);
    friend ostream &operator<<(ostream &out, partial &z);
    void citire(istream &in);
    void afisare(ostream &out);
    partial &operator =(partial &z);

};

partial::partial(int nr=0, int id=0,string materie="", float nota[]=0,elev* E=NULL,float oral[]=0):examen(nr,id,materie,nota,E)
{
    int i;
    notaOral=new float[nr];
    for(i=0; i<nr; i++)
    {
        notaOral[i]=oral[i];
    }
}

partial::~partial()
{
    delete[]notaOral;
}

partial::partial(partial &z)
{
    id_examen=z.id_examen;
    materie=z.materie;
    nr=z.nr;
    int i;
    notaScris=new float[nr];
    e=new elev[nr];
    notaOral=new float[nr];
    for(i=0; i<nr; i++)
    {
        e[i]=z.e[i];
        notaScris[i]=z.notaScris[i];
        notaOral[i]=z.notaOral[i];
    }

}

partial &partial::operator=(partial &z)
{
    if(&z!=this)
    {
        examen::operator=(z);
        int i;
        e=new elev[nr];
        notaScris=new float[nr];
        notaOral=new float[nr];
        for(i=0; i<nr; i++)
        {
            e[i]=z.e[i];
            notaScris[i]=z.notaScris[i];
            notaOral[i]=z.notaOral[i];
        }
    }
    return *this;
}

void partial::citire(istream&in)
{
    examen::citire(in);
    int i;
    notaOral=new float[nr];
    for(i=0; i<nr; i++)
    {
        cout<<"Citire nota oral"<<": ";
        in>>notaOral[i];
        try
        {
            if(notaOral[i]<1 || notaOral[i]>10)
                throw 10;

        }
        catch(int x)
        {
            cout<<"Nota trebuie sa fie cuprinsa intre 1 si 10"<<endl;
            exit(EXIT_FAILURE);
        }
        cout<<endl;
    }
    cout<<endl;
}


istream &operator>>(istream &in, partial&z)
{
    z.citire(in);
    return in;
}

void partial::afisare(ostream &out)
{
    examen::afisare(out);
    int i;
    for(i=0; i<nr; i++)
    {
        out<<"Nota la oral al elevului"<<" este : "<<notaOral[i]<<endl;
    }
}

ostream &operator<<(ostream &out, partial &z)
{
    z.afisare(out);
    return out;
}

//--------------------------------------------------

class examenFinal:public partial
{
private:
    float *extraPuncte;

public:
    examenFinal(int, int, string, float*,elev*,float*);
    examenFinal(const examenFinal&);
    ~examenFinal();
    friend istream& operator>>(istream&in, examenFinal& z);
    friend ostream& operator<<(ostream&out, examenFinal& z);
    void citire(istream&in);
    void afisare(ostream&out);
    examenFinal &operator=(examenFinal &z);
    void refacere_partial();

};

examenFinal::examenFinal(int nr=0, int id=0,string materie="", float nota[]=0,elev* E=NULL,float extra[]=0):partial(nr,id,materie,nota,E)
{
    int i;
    extraPuncte=new float[nr];
    for(i=0; i<nr; i++)
        extraPuncte[i]=extra[i];
}

examenFinal::~examenFinal()
{
    delete[]extraPuncte;
}

void examenFinal::refacere_partial()
{
    int i;
    for(i=0; i<nr; i++)
    {
        if(notaOral[i] < 5)
        {
            cout<<"Dati noua nota la partial pentru elevul "<<i+1<<" : ";
            float x;
            cin>>x;
            notaOral[i]=x;
            cout<<endl;
        }
    }
}

void examenFinal::citire(istream&in)
{
    partial::citire(in);
    int i;
    for(i=0; i<nr; i++)
    {
        cout<<"Extra-punctele elevului: "<<i+1<<" : ";
        in>>extraPuncte[i];
        cout<<endl;
    }
    refacere_partial();
    cout<<endl;
}


istream& operator>>(istream&in, examenFinal &z)
{
    z.citire(in);
    return in;
}



void examenFinal::afisare(ostream&out)
{
    partial::afisare(out);
    int i;
    //unordered_map<int, vector<elev>> ump;
    for(i=0; i<nr; i++)
    {
        out<<"Afisare extra-puncte: "<<extraPuncte[i]<<endl;
        if(notaScris[i]<5)
        {
           // ump.insert({id_examen,e[i]});
        }
    }
}

ostream& operator<<(ostream& out, examenFinal& z)
{
    z.afisare(out);
    return out;
}

examenFinal &examenFinal::operator=(examenFinal& z)
{
    if(this!=&z)
    {
        partial::operator=(z);
        int i;
        extraPuncte=new float[nr];
        for(i=0; i<nr; i++)
        {
            extraPuncte[i]=z.extraPuncte[i];
        }
    }
    return *this;
}


//---------------------------------------------------------


class quiz
{
private:
    int nrGrile;

public:
    quiz(int);
    quiz(quiz&);
    ~quiz();
    friend istream& operator>>(istream &in, quiz& z);
    friend ostream& operator<<(ostream& out, quiz& z);
    void citire_quiz(istream& in);
    void afisare_quiz(ostream& out);

};

quiz::quiz(int nr=0)
{
    nrGrile=nr;
}

quiz::quiz(quiz& z)
{
    nrGrile=z.nrGrile;
}

quiz::~quiz() {};

void quiz::citire_quiz(istream& in)
{
    cout<<"Cititi numarul de itemi tip grila: ";
    in>>nrGrile;
    cout<<endl;
}

istream& operator>>(istream& in, quiz& z)
{
    z.citire_quiz(in);
    return in;
}

void quiz::afisare_quiz(ostream& out)
{
    out<<"Nunarul de itemi tip grila este: "<<nrGrile<<endl;
}



//-------------------------------------------------------

void tip(examen *&p, int &i)
{
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul examenului "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="partial")
        {
            p=new partial;
            cin>>*p;
            i++;
        }
        else if(s=="final")
        {
            p=new examenFinal;
            cin>>*p;
            i++;
        }
        else
            throw 10;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un tip valid. Incercati partial, sau final.\n ";
    }
}


//----------------------------------------------------------


template <class t> class CatalogIndividual
{
private:
    static int nr_matricol;
    int nr_examene;
    t *v;

public:


    CatalogIndividual(int nr=0,t* c=NULL)
    {
        nr_matricol++;
        nr_examene=nr;
        c=new t[nr_examene];
        if(nr_examene!=0)
        {
            int i;
            for(i=0; i<nr_examene; i++)
                v[i]=c[i];
        }
    }


    ~CatalogIndividual()
    {
        delete[]v;
        nr_matricol--;
    }


    CatalogIndividual(const CatalogIndividual<t> &z)
    {
        nr_matricol=z.nr_matricol;
        nr_examene=z.nr_examene;
        v=new t[nr_examene];
        int i;
        for(i=0; i<nr_examene; i++)
        {
            v[i]=z.v[i];
        }
    }


    int get_nr() const
    {
        return nr_examene;
    }


    t get_v(int i)
    {
        return v[i];
    }


    friend istream& operator>>(istream&in, CatalogIndividual<t> &z)
    {
        cout<<"Introduce-ti numarul de examene: ";
        in>>z.nr_examene;
        cout<<endl;
        z.v=new t[z.nr_examene];
        cout<<"Introduce-ti obiectele: "<<endl;
        int i;
        for(i=0; i<z.nr_examene; i++)
        {
            in>>z.v[i];
            cout<<endl;
        }
        return in;
    }


    friend ostream& operator<<(ostream&out, CatalogIndividual<t> &z)
    {
        out<<"Afisare numar examene: "<<z.nr_examene<<endl;
        int i;
        for(i=0; i<z.nr_examene; i++)
        {
            out<<endl<<"Afisare date despre examenul "<<i+1<<" : "<<endl;
            out<<z.v[i];
        }
        return out;
    }

    CatalogIndividual<t> operator=(const CatalogIndividual<t> &z)
    {
        nr_examene=z.nr_examene;

    }


};

template <class t> int CatalogIndividual<t>::nr_matricol=0;




//---------------------------------------------------------------------

void menu_output()
{
    cout<<"RADU GEORGE-DANIEL, GRUPA 211, TEMA 3"<<endl;
    cout<<"----------MENU---------"<<endl;
    cout<<"OPTIUNEA 0: EXIT "<<endl;
    cout<<"OPTIUNEA 1: CITIREA OBIECTELOR DE TIP EXAMEN"<<endl;
    cout<<"OPTIUNEA 2: AFISAREA OBIECTELOR DE TIP EXAMEN"<<endl;
    cout<<"Optiunea 3: CATALOG INDIVIDUAL----(TEMPLATE PARTIAL)"<<endl;
    cout<<"Optiunea 4: CATALOG INDIVIDUAL----(TEMPLATE EXAMEN FINAL)"<<endl;
    cout<<"Optiunea 5: DOWNCAST"<<endl;

}

void menu_principal()
{
    int option,i=0,ok=0;
    option=0;
    int n=0;
    examen **ex;
    do
    {

        cout<<"Introduceti numarul optiunii: ";
        cin>>option;
        cout<<endl;

        if(option==1)
        {
            cout<<"Dati numarul de obiecte dorit: ";
            cin>>n;
            ex=new examen*[n];
            if(n>0)
            {
                for(i=0; i<n;)
                {
                    tip(ex[i],i);
                }
                ok=1;
            }
            else
                cout<<"Numarul trebuie sa fie pozitiv"<<endl;
            cout<<endl;

        }
        if(option==2)
        {
            if(ok==1)

            {
                for(i=0; i<n; i++)
                {
                    cout<<endl<<*ex[i];
                    cout<<endl;

                }
            }
            else
                cout<<"Nu s-au citit datele"<<endl;
        }

        if(option==3)
        {
            CatalogIndividual<partial> x;
            cin>>x;
            cout<<x;
        }

        if(option==4)
        {
            CatalogIndividual<examenFinal> x;
            cin>>x;
            cout<<x;
        }
        if(option==5)
        {
            int nr_partiale=0,nr_finale=0,i;
            if(n>0)
            {
                for(i=0; i<n; i++)
                {
                    partial *p1=dynamic_cast<partial*>(ex[i]);
                    examenFinal *p2=dynamic_cast<examenFinal*>(ex[i]);
                    if(p1)
                    {
                        nr_partiale++;
                    }

                    if(p2)
                    {
                        nr_finale++;
                    }

                }
                cout<<"S-au dat "<<nr_partiale<<" partiale si "<<nr_finale<<" examene finale "<<endl;
            }
            else
                cout<<"Nu s-au citit datele"<<endl;

        }


    }
    while(option!=0);
}

int main()
{
    menu_principal();
}
