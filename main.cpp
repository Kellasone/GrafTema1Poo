#include <iostream>
#include "Graf.h"

using namespace std;

int main()
{
    int *raspuns;

    Graf *graf_test=new Graf();

    cin>>graf_test;
    cout<<graf_test;

    cout<<"Metoda numarNoduri(); afiseaza: "<<graf_test->numarNoduri()<<endl;
    cout<<"Metoda numarMuchii(); afiseaza: "<<graf_test->numarMuchii();

    cout<<endl<<"Implementam graful prin constructor cu parametrii si il afisam."<<endl;
    Graf *graf_test2=new Graf(4,2,1,3,2,4);
    cout<<graf_test2;
    cout<<endl<<"Adaugam muchia 1-4 si afisam din nou graful."<<endl;
    graf_test2->adaugareMuchie(1,4);
    cout<<graf_test2;

    cout<<"Parcurgerea in adancime din nodul 1 : ";
    raspuns=graf_test2->parcurgereAdancime(1);
    while(*raspuns)
    {
        cout<<*raspuns<<" ";
        raspuns++;
    }

    cout<<endl<<"Parcurgerea in latime din nodul 1: ";
    raspuns=graf_test2->parcurgereLatime(1);
    while(*raspuns)
    {
        cout<<*raspuns<<" ";
        raspuns++;
    }
    cout<<endl;
    cout<<"Numarul de componente conexe din graf este: ";
    cout<<graf_test2->componenteConexe()<<endl;

}

