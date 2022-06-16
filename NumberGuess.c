#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

int nakljucno(int zgornjaMeja, int spodnjaMeja);
int stopnja1(int zgornjaMeja);//1-10
int stopnja2(int zgornjaMeja);//1-100
int stopnja3(int zgornjaMeja);//1-500
int stopnja4(int zgornjaMeja);//1-1000
bool skener(int poskusi, int tocke);//skenira PISNE UKAZE
int skenerStevil();//skenira stevila ki jih uporabnik zapise(ne pusti nam zapisati crke namesto stevilke)
void zapustitevIgre();//zapre program
void ukazi();//printf vse ukaze ki so na voljo v meniju
void pomocnik(int uporabnik, int generirana);//sprejme stevilko, ki si jo je spomnil racunalnik in igralec, ter pomaga uporabniku z izpisom "vecje" ali "manjse"
void stava(int tocke, int poskusi, int *vrnitevTock, int *stPoskusov, int *ceIzgubi);//se aktivira ko igralec zahteva stavo
int aliStava(int stevilo, int generirana, int num);//odsteva stevilo poskusov, s katerimi smo stavili
int posodobitevTock(int tocke, int posodobljeneTocke);//vrne nove tocke, glede na dano razliko(koliko smo jih usvojili s stavo ali izgubili)
int rezultatStave(int stevilo, int generiraj, int stPoskusov);//izpise ali smo zmagali ali izgubili v stavi in poklice ustrezne ostale funkcije za pretok stavljenih tock
bool stavaDaNe();//preverja ali igralec želi staviti
void glavnaIgra(int stevilo, int stStopnje, int poskusi, int velikostSt, int tocke, int *tockeP, int *poskusiP);//glavna igra, ki se vrti v while loop-u v vsaki stopnji

const int TOCKE = 100;
const int POSKUSI_STOPNJA1 = 5;
const int POSKUSI_STOPNJA2 = 10;
const int POSKUSI_STOPNJA3 = 20;
const int POSKUSI_STOPNJA4 = 40;

const int velikostSt1 = 10;
const int velikostSt2 = 100;
const int velikostSt3 = 500;
const int velikostSt4 = 1000;



int main() {
    printf("----------IGRA UGANI ŠTEVILKO----------\nIgra: Računalnik si izmisli število, ti pa jo moraš uganiti. Na voljo imaš omejeno poskusov in točk ki jih lahko staviš.\nVsaka stopnja je težja od prejšnje in ti doda nekaj poskusov.\n\n");
    ukazi();
    //dodatne spremenljivke za shranjevanje pointerjev
    int tockeP;
    int poskusiP;
    
    //spremenljivki v startu dodelimu constanto tock, ki so definirane globalno
    int tocke = TOCKE;

    //1.STOPNJA
    int stStopnje = 1;
    int poskusi = POSKUSI_STOPNJA1;
    
    if (skener(poskusi, tocke)) 
    {
        glavnaIgra(0, stStopnje, poskusi, velikostSt1, tocke, &tockeP, &poskusiP);
    }
    tocke = tockeP;
    poskusi = poskusiP;


    //2.STOPNJA
    stStopnje++;
    poskusi += POSKUSI_STOPNJA2;
    ukazi();
    if (skener(poskusi, tocke))
    {
        glavnaIgra(0, stStopnje, poskusi, velikostSt2, tocke, &tockeP, &poskusiP);
    }
    tocke = tockeP;
    poskusi = poskusiP;


    //3.STOPNJA
    stStopnje++;
    poskusi += POSKUSI_STOPNJA3;
    ukazi();
    if (skener(poskusi, tocke))
    {
        glavnaIgra(0, stStopnje, poskusi, velikostSt3, tocke, &tockeP, &poskusiP);
    }
    tocke = tockeP;
    poskusi = poskusiP;


    //4.STOPNJA
    stStopnje++;
    poskusi += POSKUSI_STOPNJA4;
    ukazi();
    if (skener(poskusi, tocke))
    {
        glavnaIgra(0, stStopnje, poskusi, velikostSt4, tocke, &tockeP, &poskusiP);
    }
    tocke = tockeP;
    poskusi = poskusiP;
    if (stStopnje == 4)
    {
        printf("ČESTITAM! KONČAL SI IGRO.\nOb koncu igre ti je ostalo:\n%i točk,\n%i preostalih poskusov.\n", tocke, poskusi);
    }
        
}

void glavnaIgra(int stevilo, int stStopnje, int poskusi, int velikostSt, int tocke, int *tockeP, int *poskusiP) {
    int stavljeneTocke;
    int ceIzgubi;
    int stPoskusov;
    
    
    //
    printf("----------STOPNJA %i----------\nUganjuj med števili 1 in %i!\n", stStopnje, velikostSt);
    int generiraj = stopnja1(velikostSt);
    int i = 1;
    
    bool tmp = 0;
    bool p = 1;
    while (stevilo != generiraj)
    {
        //preveri ali se imamo kaj poskusov, drugace zapusti igro.
        if(poskusi == 0){zapustitevIgre();}
        //preveri ali imamo se kaj tock, ali smo vse zakockali
        if(tocke == 0){zapustitevIgre();}
        
        //pomaga ali je stevilo vecje ali manjse
        if(stevilo!=0){pomocnik(stevilo, generiraj);printf("---------------------\n");}
        
        //STAVA JA-NE
        if (!tmp){tmp = stavaDaNe();}
        //preveri ali hocemo staviti, ce ja si zapomni koliko poskusov smo stavili, in koliko tock.
        if(tmp && p) {
            stava(tocke, poskusi, &stavljeneTocke, &stPoskusov, &ceIzgubi);
            p = 0;
        }


        
        // vpisemo stevilko, steje poskuse in nam jih hkrati odsteva
        printf("Poskus %i: ", i);
        stevilo = skenerStevil();
        i++;
        poskusi--;

        

        //funkcionalnost za stavo, ce smo karkoli stavili.
        if (tmp)
        {
            stPoskusov = aliStava(stevilo, generiraj, stPoskusov);

            int zacasno = rezultatStave(stevilo, generiraj, stPoskusov);

            if (zacasno == 1) {
                tocke = posodobitevTock(tocke, stavljeneTocke);
                tmp = 0;
                p=1;
                
            } else if (zacasno == 2) {
                tocke = posodobitevTock(tocke, ceIzgubi);
                tmp = 0;
                p=1;
            } 
        }    
    }
    printf("Uganil si število!\n");
    printf("---------------------\n");
    *tockeP = tocke;
    *poskusiP = poskusi;
}

bool stavaDaNe() {
    printf("Želite staviti? -> d(Da) (Ne-kakršnakoli črka)\n");
    char ch;
    scanf(" %c", &ch);
    if (ch == 'd')
    {
        return 1;
    } else {
        return 0;
    } 
}

int rezultatStave(int stevilo, int generiraj, int stPoskusov) {
    if (stPoskusov > 0 && stevilo == generiraj)
    {
        printf("Stavil si uspešno. Točke posodobljene.\n");
        return 1;
    } else if (stPoskusov == 0) {
        printf("Žal tvoja stava ni bila uspešna. Izgubil si stavljene točke.\n");
        return 2;
    } else {
        return 0;
    }
}

int posodobitevTock(int tocke, int posodobljeneTocke) {
    return tocke + posodobljeneTocke;
}

int aliStava(int stevilo, int generirana, int num) {
    if (stevilo == generirana)
    {
        return num;
    } else {
        num--;
        return num;
    }
    
}

void stava(int tocke, int poskusi, int *vrnitevTock, int *stPoskusov, int *ceIzgubi) {
    bool b = 1;
    while (b)
    {
        printf("Koliko točk želite staviti? ");
        int stTock = skenerStevil();
        *ceIzgubi = -stTock;
        int a=0;
        if (tocke >= stTock)
        {
            printf("V koliko poskusih boste uganili število? ");
            int stPoskusov2 = skenerStevil();
            *stPoskusov = stPoskusov2;
            if (stPoskusov2 <= poskusi)
            {
                if (stPoskusov2 == 1)
                {
                    a = stTock * 10;
                    *vrnitevTock = a;
                }
                else if (stPoskusov2 == 2)
                {
                    a = stTock * 8;
                    *vrnitevTock = a;
                }
                else if (stPoskusov2 == 3)
                {
                    a = stTock * 5;
                    *vrnitevTock = a;
                }
                else if (stPoskusov2 == 4)
                {
                    a = stTock * 3;
                    *vrnitevTock = a;
                }
                else
                {
                    a = stTock * 2;
                    *vrnitevTock = a;
                } 
                printf("Stava sprejeta, če uganete boste prejeli toliko točk: %i\n", a);
                b=0;
            }
            else {
                printf("Napaka! Poskusite še enkrat!\n");
            }
            
        } 
        else 
        {
            printf("Ne morete staviti več kot imate! (max %i)\n", tocke);
            
        }
    }
    
    
    
}

void pomocnik(int uporabnik, int generirana) {
    if (uporabnik > generirana)
    {
        printf("Število je manjše!\n");
    } else if (uporabnik < generirana) {
        printf("Število je večje!\n");
    }
    
}

int skenerStevil() {
    //Pregleduje da uporabnik ne napise crke namesto stevilke.
    int x;
    while( scanf("%i",&x) != 1 )
    {
        printf("Napaka, poskusi Še enkrat: ");
        while ( getchar() != '\n' ); 
    }
    return x;
    
}

bool skener(int poskusi, int tocke) {
    char ukaz;
    bool igra = 1;
    while (igra)
    {
        scanf(" %c", &ukaz);
        if (ukaz == 'Z')
        {
            printf("Začetek igre!\n");
            igra = 0;
        }
        else if (ukaz == 'P')
        {
            printf("Na voljo imate: %i poskusov.\nPazite, da ne izgubite vseh poskusov, saj to pomeni konec igre!\n", poskusi);
            
        }
        else if (ukaz == 'T') 
        {
            printf("Na voljo imate: %i točk.\n", tocke);
            
        }
        else if (ukaz == 'S')
        {
            printf("Pred vsako potezo lahko zapišete 'd' in pričnete s stavo.\nPazite, da ne izgubite vseh točk, saj to pomeni konec igre!\n");
            
        }
        else if (ukaz == 'K')
        {
            zapustitevIgre();
            
        }
        else 
        {
            printf("Napačen ukaz! Poskusite še enkrat: \n");
        }
    }
    return 1;
}

void zapustitevIgre() {
    printf("Zapuščam igro...");
    exit(0);
}

void ukazi() {
    printf("Ukazi: Za začetek stopnje v igri napiši Z\n------ Za izpis se mogocih poskusov P\n------ Za izpis tvojih tock T\n------ Za informacije glede stave napiši S\n------ Za zapustitev igre napiši K\n");
}

int stopnja1(int zgornjaMeja) {
    return nakljucno(zgornjaMeja, 1);
}

int stopnja2(int zgornjaMeja) {
    return nakljucno(zgornjaMeja, 1);
}

int stopnja3(int zgornjaMeja) {
    return nakljucno(zgornjaMeja, 1);
}

int stopnja4(int zgornjaMeja) {
    return nakljucno(zgornjaMeja, 1);
}


int nakljucno(int zgornjaMeja, int spodnjaMeja) {
    return ((rand()%(zgornjaMeja - spodnjaMeja + 1)) + spodnjaMeja);
}

//Jakob Beber, 89211306