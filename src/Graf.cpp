#include "Graf.h"
#include<stdarg.h>
#include<iostream>
using namespace std;


bool operator< (const Graf &graf1, const Graf &graf2)
{
    if(graf1.numar_noduri==graf2.numar_noduri)
        return (graf1.numar_muchii<graf2.numar_muchii);
    return (graf1.numar_noduri < graf2.numar_noduri);
}

bool operator> (const Graf &graf1, const Graf &graf2)
{

    if(graf1.numar_noduri==graf2.numar_noduri)
        return (graf1.numar_muchii>graf2.numar_muchii);
    return (graf1.numar_noduri > graf2.numar_noduri);
}

Graf::Graf()
{
    numar_muchii=0;
    numar_noduri=0;
}

Graf::Graf(Graf *graf)
{
    *this=graf;
}

Graf::~Graf()
{
    delete [] lista_vecini;
    numar_muchii=0;
    numar_noduri=0;
}

Graf::Graf(int numar_noduri_init, int numar_muchii_init,...)
{
    numar_noduri=numar_noduri_init;
    numar_muchii=numar_muchii_init;

va_list argument_curent;
va_start(argument_curent,numar_muchii);

for(int i=0;i<numar_muchii;i++)
{
    nod *nod_aux;
    nod *nod1=new nod;
    nod *nod2=new nod;

    nod1->nod_info=va_arg(argument_curent,int);
    nod1->nod_next=NULL;

    nod2->nod_info=va_arg(argument_curent,int);
    nod2->nod_next=NULL;

    if((nod1->nod_info>0)&&(nod1->nod_info<=numar_noduri)&&(nod2->nod_info>0)&&(nod2->nod_info<=numar_noduri))
    {
        if(!lista_vecini[nod1->nod_info-1])
        lista_vecini[nod1->nod_info-1]=nod2;
        else
        {
            nod_aux=lista_vecini[nod1->nod_info-1];

                while(nod_aux->nod_next)
                    nod_aux=nod_aux->nod_next;

                nod_aux->nod_next=nod2;
        }

        if(!lista_vecini[nod2->nod_info-1])
        lista_vecini[nod2->nod_info-1]=nod1;
        else
        {
            nod_aux=lista_vecini[nod2->nod_info-1];

                while(nod_aux->nod_next)
                    nod_aux=nod_aux->nod_next;

                nod_aux->nod_next=nod1;
        }

}
}

va_end(argument_curent);

}


void Graf::adaugareMuchie(int nod1, int nod2)
{
    if((nod1>0)&&(nod1<=numar_noduri)&&(nod2>0)&&(nod2<=numar_noduri))
        {
        nod* nod_aux;
        bool ok=1;
        nod_aux=lista_vecini[nod1-1];
        while(nod_aux)
        {
            if(nod_aux->nod_info==nod2)
                ok=0;
            nod_aux=nod_aux->nod_next;
        }
     if(ok==1)
     {
        nod *nod_1=new nod;
        nod *nod_2=new nod;


        nod_1->nod_info=nod1;
        nod_2->nod_info=nod2;
        nod_1->nod_next=0;
        nod_2->nod_next=0;


              if(!lista_vecini[nod_1->nod_info-1])
        lista_vecini[nod_1->nod_info-1]=nod_2;
        else
        {
            nod_aux=lista_vecini[nod_1->nod_info-1];

                while(nod_aux->nod_next)
                    nod_aux=nod_aux->nod_next;

                nod_aux->nod_next=nod_2;
        }

        if(!lista_vecini[nod_2->nod_info-1])
        lista_vecini[nod_2->nod_info-1]=nod_1;
        else
        {
            nod_aux=lista_vecini[nod_2->nod_info-1];

                while(nod_aux->nod_next)
                    nod_aux=nod_aux->nod_next;

                nod_aux->nod_next=nod_1;
        }

        numar_muchii++;
     }
}
}

int Graf::numarMuchii()
{
    return numar_muchii;
}

int Graf::numarNoduri()
{
    return numar_noduri;
}

int *Graf::parcurgereAdancime(int nod_start)
//implementarea algoritmului de parcurgere in adancime a grafului.
{
    static int raspuns[100];
    int pozitie=0;
    if((nod_start>0)&&(nod_start<=numar_noduri))
        {
            int viz[numar_noduri];
            for(int i=0;i<numar_noduri;i++)
                viz[i]=0;
            nod *stiva=new nod;

            stiva->nod_info=nod_start-1;
            stiva->nod_next=NULL;
            viz[nod_start-1]=1;


            while(stiva)
                {
                    int nod_curent;
                    nod* nod_parcurgere;
                    nod_curent=stiva->nod_info;
                    stiva=stiva->nod_next;

                    raspuns[pozitie++]=nod_curent+1;
                    viz[nod_curent]=1;

                    nod_parcurgere=lista_vecini[nod_curent];

                        while(nod_parcurgere)
                            {
                                if(viz[nod_parcurgere->nod_info-1]==0)
                                    {
                                        nod* nod_aux=new nod;
                                        nod_aux->nod_info=nod_parcurgere->nod_info-1;
                                        nod_aux->nod_next=stiva;
                                        stiva=nod_aux;
                                        viz[nod_parcurgere->nod_info-1]=1;
                                    }
                        nod_parcurgere=nod_parcurgere->nod_next;
            }
        }
    }
    return raspuns;
}


int *Graf::parcurgereLatime(int nod_start)
//implementarea algoritmului de parcurgere in latime a grafului
{
    static int raspuns[100];
    int pozitie=0;
    if((nod_start>0)&&(nod_start<=numar_noduri))
        {
            int viz[numar_noduri];
            for(int i=0;i<numar_noduri;i++)
                viz[i]=0;

            nod *coada=new nod;
            coada->nod_info=nod_start-1;
            coada->nod_next=NULL;
            viz[nod_start-1]=1;

            while(coada)
                {
                    int nod_curent;
                    nod* nod_parcurgere;
                    nod* aux_adaugare;
                    nod_curent=coada->nod_info;
                    coada=coada->nod_next;

                    raspuns[pozitie++]=nod_curent+1;;
                    viz[nod_curent]=1;

                    nod_parcurgere=lista_vecini[nod_curent];

                        while(nod_parcurgere)
                        {
                            if(viz[nod_parcurgere->nod_info-1]==0)
                            {
                                nod* nod_aux=new nod;
                                nod_aux->nod_info=nod_parcurgere->nod_info-1;
                                nod_aux->nod_next=NULL;
                                aux_adaugare=coada;
                            if(!coada)
                                coada=nod_aux;
                                else
                                    {
                                        while(aux_adaugare->nod_next)

                                                aux_adaugare=aux_adaugare->nod_next;
                                                aux_adaugare->nod_next=nod_aux;

                                    }
                                viz[nod_parcurgere->nod_info-1]=1;
                            }
                        nod_parcurgere=nod_parcurgere->nod_next;
                    }
                }
        }
    return raspuns;
}

Graf Graf::operator=(Graf graf2)
//supraincarcarea operatorului = pentru atribuire
{
    numar_muchii=graf2.numar_muchii;
    numar_noduri=graf2.numar_noduri;

    for(int i=0;i<graf2.numar_noduri;i++)
       lista_vecini[i]=graf2.lista_vecini[i];

    return *this;
}

istream& operator>> (istream& in,Graf *graf)
//supraincarcarea operatorului >> pentru imput
{
    nod *nod1=new nod;
    nod *nod2=new nod;

    nod1->nod_next=NULL;
    nod2->nod_next=NULL;

    cout<<"Introduceti numarul de noduri : ";
    in>>graf->numar_noduri;
    cout<<"Introduceti numarul de muchii : ";
    in>>graf->numar_muchii;

    for(int i=0;i<graf->numar_muchii;i++)
       {
            nod *nod_aux;
            nod *nod1=new nod;
            nod *nod2=new nod;
            nod1->nod_next=NULL;
            nod2->nod_next=NULL;

            cout<<"Muchia "<<i+1<< " este intre nodul ";
            in>>nod1->nod_info;
            cout<<" si nodul ";
            in>>nod2->nod_info;

            if(!((nod1->nod_info>0)&&(nod1->nod_info<=graf->numar_noduri)&&(nod2->nod_info>0)&&(nod2->nod_info<=graf->numar_noduri)))
             {
                 cout<<"Date incorecte, reincercati!"<<endl;
                 i--;
             }
             else
                {
                    if(!graf->lista_vecini[nod1->nod_info-1])
                        graf->lista_vecini[nod1->nod_info-1]=nod2;
                    else
                        {
                            nod_aux=graf->lista_vecini[nod1->nod_info-1];
                            while(nod_aux->nod_next)
                            nod_aux=nod_aux->nod_next;
                            nod_aux->nod_next=nod2;
                        }
            if(!graf->lista_vecini[nod2->nod_info-1])
                graf->lista_vecini[nod2->nod_info-1]=nod1;
                    else
                        {
                            nod_aux=graf->lista_vecini[nod2->nod_info-1];
                            while(nod_aux->nod_next)
                            nod_aux=nod_aux->nod_next;
                            nod_aux->nod_next=nod1;
                        }

                }

        }
    return in;
}

ostream& operator<< (ostream& out,Graf *graf)
//supraincarcarea operatorului << pentru output
{
    out<<"Numarul de noduri este "<<graf->numar_noduri<<"."<<endl;
    out<<"Numarul de muchii este "<<graf->numar_muchii<<"."<<endl<<endl;

    if(graf->numar_muchii==0)
        cout<<"Nu exista muchii!"<<endl;
        else
            {
                for(int i=0;i<graf->numar_noduri;i++)
                    if(!graf->lista_vecini[i])
                        cout<<"Nodul "<<i+1<<" nu are vecini."<<endl;
                        else
                            {
                                nod* aux;
                                aux=graf->lista_vecini[i];
                                cout<<"Vecinii lui "<<i+1<<" sunt: ";
                                while(aux)
                                    {
                                        cout<<aux->nod_info<<" ";
                                        aux=aux->nod_next;
                                    }
                                cout<<endl;
                            }
            }
    return out;
}

int *Graf::operator[](int nod_curent)
//supraincarcarea operatorului[]. nu functioneaza cum intentioneaza.
{
    static int raspuns[100];
    int i=0;
    nod *nod_parcurgere;
    nod_parcurgere = lista_vecini[nod_curent-1];
        while(nod_parcurgere)
            {
                raspuns[i++]=nod_parcurgere->nod_info;
                nod_parcurgere=nod_parcurgere->nod_next;
            }
    return raspuns;
}



int Graf::componenteConexe()
//metoda care returneaza numarul de componente conexe
//prin parcurgerea in adancime si numararea ciclurilor de adaugare in stiva
{
    int viz[numar_noduri];
    for(int i=0;i<numar_noduri;i++)
        if(lista_vecini[i])
            viz[i]=1;
        else viz[i]=0;
   int nr_componente=0;

    for(int i=0;i<numar_noduri;i++)
        if(viz[i]==1)
        {
            nr_componente++;
            nod *stiva=new nod;
            stiva->nod_info=i;
            stiva->nod_next=NULL;
            viz[i]=0;

            while(stiva)
            {
                int nod_curent;
                nod* nod_parcurgere;
                nod_curent=stiva->nod_info;
                stiva=stiva->nod_next;

                viz[nod_curent]=0;

                nod_parcurgere=lista_vecini[nod_curent];

                while(nod_parcurgere)
                    {
                        if(viz[nod_parcurgere->nod_info-1]==1)
                        {
                            nod* nod_aux=new nod;
                            nod_aux->nod_info=nod_parcurgere->nod_info-1;
                            nod_aux->nod_next=stiva;
                            stiva=nod_aux;
                            viz[nod_parcurgere->nod_info-1]=0;
                        }
                    nod_parcurgere=nod_parcurgere->nod_next;
                    }
            }
        }

    return nr_componente;
}

/*
Implementare nefunctionala;
int Graf::verificareArbore()
{
     int viz[numar_noduri];
        for(int i=0;i<numar_noduri;i++)
            viz[i]=0;
    if(componenteConexe()==1 )
    {

        nod *coada=new nod;

        coada->nod_info=1;
        coada->nod_next=NULL;
        viz[0]=1;

    int x[numar_noduri][numar_noduri];
    for(int i=0;i<numar_noduri;i++)
        for(int j=0;j<numar_noduri;j++)
        x[i][j]=0;

    for(int i=0;i<numar_noduri;i++)
    {
     nod* nod_aux;
      nod_aux=lista_vecini[i];
      while(nod_aux)
      {
          x[i][nod_aux->nod_info-1]=x[nod_aux->nod_info-1][i]=1;
      nod_aux=nod_aux->nod_next;
      }
 }



        while(coada)
        {
            int nod_curent;
            nod* nod_parcurgere;
            nod* aux_adaugare;
            nod_curent=coada->nod_info;
            coada=coada->nod_next;

            viz[nod_curent]=1;

            nod_parcurgere=lista_vecini[nod_curent];

            while(nod_parcurgere)
            {

                if(viz[nod_parcurgere->nod_info-1]==0)
                {

                    nod* nod_aux=new nod;
                    nod_aux->nod_info=nod_parcurgere->nod_info-1;
                    nod_aux->nod_next=NULL;

                    aux_adaugare=coada;
                    if(!coada)
                        coada=nod_aux;
                    else
                    {
                        while(aux_adaugare->nod_next)
                            aux_adaugare=aux_adaugare->nod_next;
                        aux_adaugare->nod_next=nod_aux;
                    }
                    viz[nod_parcurgere->nod_info-1]=1;
                    x[nod_parcurgere->nod_info-1][nod_curent]--; x[nod_curent][nod_parcurgere->nod_info-1]--;


                }

                nod_parcurgere=nod_parcurgere->nod_next;
            }
        }


         for(int i=0;i<numar_noduri;i++)
        {for(int j=0;j<numar_noduri;j++)
        cout<<x[i][j]<<" ";
        cout<<endl;}


 for(int i=0;i<numar_noduri;i++)
    for(int j=0;j<numar_noduri;j++)
        if(x[i][j]>1)
            return 0;


    return 1;
    }



}*/


/*
Implementare nefunctionala;
int Graf::drumNoduri(int inceput, int sfarsit)
{
    inceput--;
    sfarsit;
    if(inceput==sfarsit)
        return 0;

    nod* vecini;
    vecini=lista_vecini[inceput];

    while(vecini)
    {

        if(vecini->nod_info==sfarsit)
            return 1;
        vecini=vecini->nod_next;
    }

    vecini=lista_vecini[inceput];

    int minim=drumNoduri(vecini->nod_info, sfarsit);
    vecini=vecini->nod_next;

    while(vecini)
    {
        int x=drumNoduri(vecini->nod_info, sfarsit);
        if(x<minim)
            minim=x;
        vecini=vecini->nod_next;
    }
    return 1+minim;






    /*int distanta=0;


    if(inceput==sfarsit)
      return 0;

    nod* vecini;
    vecini=lista_vecini[inceput];
    while(vecini)
    {  if(vecini->nod_info==sfarsit)
            return 1;
        vecini=vecini->nod_next;
    }


}
*/
