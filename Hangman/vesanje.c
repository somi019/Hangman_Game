
//Milos Djordjevic RT-7/21


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define MAX 100
#define MAX_POKUSAJI 7
int prvi=0;


void igraj();
void pravila();
char *biranje_reci();
int provera(char *rec, char *pokusaji, char slovo);
void crtanje(int br_Gresaka);

struct Korisnik {
    char ime[20];
    char prezime[20];
    char pol;
};
struct Korisnik k;

int main()
{
char izbor;

if(prvi==0)
{
	printf("\nCao, kako se zoves? ");
	gets(k.ime);
	printf("\nA prezime ti je? ");
	gets(k.prezime);
	do
	{
		printf("\nPol?(M za muski, Z za zenski): ");
		fflush(stdin);
		k.pol=getchar();
		if(toupper(k.pol)!='M' && toupper(k.pol)!='Z') printf("\nUnesite M ili Z!");
	}while(toupper(k.pol)!='M' && toupper(k.pol)!='Z');
	prvi=1;
}

poc:
// Meni
printf("1. Igraj\n");
printf("2. Pravila\n");
printf("3. Izadji\n");


printf("Izbor : ");
fflush(stdin);
scanf("%c", &izbor);

printf("\n\n\n\n");

// Izbor
switch (izbor)
{
    case '1':
        igraj();
        break;
    case '2':
        pravila();
        break;
    case '3':
		printf("\nVidimo se, %s! (pritisni ENTER da bi izasao)",k.ime);
		fflush(stdin);
		getchar();
        exit(0);
    default:
        printf("\nPogresan unos.\n\n\n");
		goto poc;
        
}

return 0;

}

// Funkcija za igru vesanja, nema ulaza a izlaz joj je vracanje u main funkciju, poziva se iz main funkcije i poziva funckije: biranje reci, provera i crtanje
void igraj()
{
char *rec = biranje_reci(),pokusaji[MAX],slovo,test[30]=" ";
int br_Gresaka= 0,i,ind,pobeda=1,prolaz=1,g=0;

// Petlja koja radi sve dok se igra vesanja ne zavrsi
while (br_Gresaka < MAX_POKUSAJI)
{
    //Stampanje reci na pocetku i pri unosenju slova
	printf("\n\t\t");
    for (i = 0; i < strlen(rec); i++)
    {
        if (strchr(pokusaji, rec[i]))
        {
            printf("%c ", rec[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");

    // Korisnik unosi slovo koje nije vec uneseno
	do
	{
		prolaz=1;
		printf("\n\nUnesite slovo: ");
		scanf(" %c", &slovo);
		if(isalpha(slovo))
		{
			for(i=0;i<strlen(test);i++)
			{
				if(test[i] == slovo)
				{
					prolaz=0;
				}
			if(prolaz == 0) break;
			}
		test[g++]=slovo;
	
		}
	else prolaz=0;
	if (prolaz == 0) 
		printf("\nVec uneto ili nije slovo!\n");
	
	}while(prolaz==0);

    // Provera da li je pretpostavljeno slovo u reci
    ind = provera(rec, pokusaji, slovo);
    if (!ind)
    {
        br_Gresaka++;
        crtanje(br_Gresaka);
    }
	else
	{
		crtanje(br_Gresaka);

	}

    // Provera da li je partija pobedjena
	pobeda=1;
    for (i = 0; i < strlen(rec); i++)
    {
        if (!strchr(pokusaji, rec[i]))
        {
            pobeda = 0;
            break;
        }
    }
    if (pobeda)
    {
		
        printf("\nBravo! Rec je bila: %s\n\n\n", rec);
        break;
    }
}

// U slucaju da igrac izgubi partiju
if (br_Gresaka == MAX_POKUSAJI)
{
    printf("\nCica Glisa je obesen. Rec je bila: %s\n\n\n", rec);
}

free(rec);
return main();
} 

// Funkcija za prikaz pravila igre, nema ulaza a izlaz joj je vracanje u main funckiju, poziva se iz main funkcije i ne poziva nijednu drugu funkciju
void pravila()
{
printf("Pravila igre vesanja su:\n");
printf("1. Kompjuter bira nasumicnu rec, ti moras pretpostaviti koja se slova nalaze u njoj.\n");
printf("2. Imas 6 sansi da pogresis.\n");
printf("3. Ako pretpostavis slovo koje je u reci, slovo ce biti prikazano.\n");
printf("4. Ako pretpostavis slovo koje nije u reci, deo cica Glisinog tela ce biti nacrtan.\n");
printf("5. Ako pretpostavis celu rec pre nego sto je nacrtan cica Glisa, pobedio si!\n");
printf("6. Ako ne pretpostavis rec u svojih 6 sansi, izgubio si.\n");
if (toupper(k.pol) == 'M')
	printf("Srecno ti bilo, brate!\n\n\n\n");
else
	printf("Srecno ti bilo, sestro!\n\n\n\n");
return main();
}

//Funkcija za biranje reci iz tekstualnog fajla, nema ulaza, izlaz joj je string. Poziva se iz funckije igraj i ne poziva nijednu drugu funckiju
char *biranje_reci()
{
// Otvaranje fajla
FILE *fp;
int broj_reci = 0,izabrana_rec,i;
char *rec;

fp = fopen("reci.txt", "r");

//Provera da li je fajl otvoren
if (fp == NULL)
{
printf("Greska pri otvaranju fajla.\n");
exit(1);
}

// Biranje nasumicne reci

rec = (char *)malloc(MAX * sizeof(char));
while (fscanf(fp, "%s", rec) == 1)
{
    broj_reci++;
}
rewind(fp);

srand(time(0));
izabrana_rec = rand() % broj_reci;
for (i = 0; i < izabrana_rec; i++)
{
    fscanf(fp, "%s", rec);
}

// Zatvaranje fajla i vracanje vrednosti u main funkciju
fclose(fp);
return rec;

}

// Funkcija koja proverava da li je pretpostavka tacna, ulaz su joj stringovi rec(trazena rec), pokusaji(slova koja su pogodjena do sad) i slovo(slovo koje je upravo uneto).
//Poziva se iz funkcije igraj i ne poziva nijednu drugu funkciju
int provera(char *rec, char *pokusaji, char slovo)
{
int ind = 0,i;
for (i = 0; i < strlen(rec); i++)
{
if (rec[i] == slovo)
{
ind = 1;
pokusaji[i] = slovo;
}
}
return ind;
}

// Funkcija za crtanje cica Glise, ulaz joj je broj gresaka koje je korisnik nacinio do sada, a izlaza nema(ne vraca nikakvu vrednost). Poziva se iz funckije igraj i ne poziva nijednu drugu funckiju.
void crtanje(int br_Gresaka)
{

switch (br_Gresaka){
	case 1:
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		break;
	
	case 2:
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		printf("  |     |\n");
		break;
	case 3:
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		printf("  |     |\n");
		printf("  |    /");
		break;
	case 4:	
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		printf("  |     |\n");
		printf("  |    /|");
		break;
	case 5:	
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		printf("  |     |\n");
		printf("  |    /|\\\n");
		break;
	case 6:
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		printf("  |     |\n");
		printf("  |    /|\\\n");
		printf("  |    /");
		break;
	case 7:
		printf(" ______\n");
		printf(" | |\n");
		printf("  |     O\n");
		printf("  |     |\n");
		printf("  |    /|\\\n");
		printf("  |    / \\\n");
		break;
		

}

} 





