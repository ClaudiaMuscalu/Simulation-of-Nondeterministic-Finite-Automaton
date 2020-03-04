#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;

void citire(unsigned int &nr_stari, unsigned int &stare_i, unsigned int &nr_finale, unsigned int stari_finale[ ],
            char cuvant[ ], char M[ ][100][50])
{
    ifstream fin("citiredate");
    unsigned int i,x,j;
    char l;
    //folosesc un vector de frecventa in care marchez cu 1 daca o stare este finala
    for(i=0;i<100;i++)
     stari_finale[i]=0;


    fin>>nr_stari;
    fin>>stare_i;
    fin>>nr_finale;


    //citirea starilor finale
    for(i=0;i<nr_finale;i++)
    {
        fin>>x;
        stari_finale[x]++;
    }

    //initial pun '\0' in toata matricea
     for(i=0;i<100;i++)
     {
         for(j=0;j<100;j++)

            M[i][j][0]='\0';

     }

     unsigned int b,nr,k;

     fin>>nr;//numarul muchiile citite din fisier

     for(k=0;k<nr;k++)
     {fin>>i>>j>>l;
      //daca initial nu este nicio litera pe acea pozitie o pun pe pozitia 0
      if(M[i][j][0]=='\0')
        {M[i][j][0]=l;
         M[i][j][1]='\0';

        }

      else
         {b=strlen(M[i][j]);
          M[i][j][b]=l;
          M[i][j][b+1]='\0';
         }
     }
     //citirea cuvantului ce urmeaza a fi verificat
     fin>>cuvant;
     fin.close();
}

void afisare(unsigned int nr_stari, unsigned int stare_i, unsigned int nr_finale, unsigned int stari_finale[ ],
             char cuvant[ ], char M[][100][50])
{
    ofstream fout("verificare_citire");

    fout<<nr_stari<<'\n';
    fout<<stare_i<<'\n';
    fout<<nr_finale<<'\n';

    unsigned int i;
    for(i=0;i<100;i++)
        if(stari_finale[i]!=0)
        fout<<i<<" ";
    fout<<'\n';

    fout<<cuvant<<'\n';

    unsigned int j;

    for(i=0;i<nr_stari;i++)

    {
        for(j=0;j<nr_stari;j++)
            {if(M[i][j][0]!='\0')
            fout<<M[i][j]<<" ";
            else
                fout<<"-"<<" ";}

        fout<<'\n';
    }
    fout.close();

}



void verificare_cuvant(unsigned int poz, unsigned int &ok, unsigned int start, unsigned int nr_stari, unsigned int stari_finale[ ],
                       char cuvant[ ], char M[ ][100][50])
   {
    unsigned int i,b,j;

    //am ajuns la ultima pozitie din cuvant si starea curenta este stare nula
    if(cuvant[poz]=='\0'&&stari_finale[start]==1)
        ok=1;

    for(i=0;i<nr_stari;i++)
    {
     if(M[start][i][0]!='\0')
     {
      b=strlen(M[start][i]);
      for(j=0;j<b;j++)
      {
          if(M[start][i][j]==cuvant[poz])

           verificare_cuvant(poz+1,ok,i,nr_stari,stari_finale,cuvant,M);
      }
     }
    }
   }


int main()
{
    unsigned int nr_stari;//numarul de stari
    unsigned int stare_i;
    unsigned int nr_finale;//numarul de stari finale
    unsigned int stari_finale[100];//folosesc un vector de frecventa pentru a memora starile
    char M[100][100][50];
    char cuvant[100];

    citire(nr_stari,stare_i,nr_finale,stari_finale,cuvant,M);
    afisare(nr_stari,stare_i,nr_finale,stari_finale,cuvant,M);


    unsigned int ok=0;
    unsigned int poz=0;

    verificare_cuvant(poz,ok,stare_i,nr_stari,stari_finale,cuvant,M);
    if(ok==1)
        cout<<"Cuvantul "<<cuvant<<" este acceptat de automat.";
    else
        cout<<"Cuvantul "<<cuvant<<" nu este acceptat de automat.";
    return 0;
}
