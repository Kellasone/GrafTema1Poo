#ifndef GRAF_H
#define GRAF_H
#include<iostream>
using namespace std;



struct nod
{
    int nod_info;
    nod* nod_next;
};

class Graf
{
    int numar_muchii;
    int numar_noduri;
    nod *lista_vecini[100];


    public:
        Graf();
        Graf(int, int , ...);
        virtual ~Graf();
        Graf(Graf *);
        int *operator[](int); //implementare nefunctionala
        void adaugareMuchie(int ,int);
        int numarMuchii();
        int numarNoduri();
        int *parcurgereAdancime(int);
        int *parcurgereLatime(int);
        Graf operator=(Graf);
        int drumNoduri(int, int); //implementare nereusita
        int componenteConexe();
        int verificareArbore(); //implementare nereusita

        friend bool operator< (const Graf &graf1, const Graf &graf2); //implementare nefunctionala
        friend bool operator> (const Graf &graf1, const Graf &graf2); //implementare nefunctionala

        friend istream& operator>> (istream &,Graf *);
        friend ostream& operator<< (ostream & out,Graf*);



};

#endif // GRAF_H
