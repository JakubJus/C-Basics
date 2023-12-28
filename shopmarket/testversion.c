#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define SIZE 100 + 1
#define STORLEK 20 + 1


// -------------Vara Paket--------//
typedef struct{
    int varunummer;
    char namn[STORLEK];
    int saldo;
} varor;

//-------------------------------------//

void skriva_ut(varor varorILager[], int hylla);
void registrera(varor nyaVara[], int *pHylla);
void lada_varor(varor gamlaVaror[], int *pPlats, char fil[]);
void spara_varor(varor nyVara[], int plats, char fil[]);
void sok_vara(varor varorILager[], int hylla, char avsluta);
void sokEfterNamn(varor aVarorILager[],int aHylla);
void sokEfterSaldo(varor aVarorILager[],int aHylla);
void sokEfterNummer(varor aVarorILager[],int aHylla);
void andra_saldo(varor aVarorILager[], int *pPlats);
void sortera_varunummer(varor VarorSomFinnsILager[], int plats);
void sortera_saldo(varor VarorSomFinnsILager[], int plats);
void sortera_namn(varor VarorSomFinnsILager[], int plats);
void sortera_varor(varor VarorSomFinnsILager[], int *pHylla);
void ta_bort(varor VarorILager[], int *pHylla);
void las_bort(); ///fanns inte med i uppgiften men om användaren skriver fel da crashar inte programmet helt

int main(void){
    char cmd,fil[SIZE],rulla;
    int lagerPlats = 0;
    varor Lager[SIZE];
    puts("Du har startat lagerprogrammet v.01");
    printf("Ange fil namn: ");
    scanf("%s",&fil);
    las_bort();
    lada_varor(Lager, &lagerPlats, fil);

    do{
        printf("\n(1) Registrera Varor\n(2) Skriva ut varor\n(3) Sok varor\n(4) Andra lager saldo\n(5) Sortera varor\n(6) Avregistrera varor\n(7) Avsluta programmet\n> ");
        cmd = getchar();
        las_bort();

        switch (cmd){
            case '1': registrera(Lager, &lagerPlats); break;
            case '2': skriva_ut(Lager, lagerPlats);break;
            case '3': rulla='a';sok_vara(Lager, lagerPlats,rulla); break;
            case '4': andra_saldo(Lager, &lagerPlats); break;
            case '5': sortera_varor(Lager, &lagerPlats);break;
            case '6': ta_bort(Lager, &lagerPlats);break;
            case '7': puts("\nQUITING..."); break;
            default: puts("Fel bokstav eller siffra");break;
        }
    }while (cmd != '7');

    spara_varor(Lager, lagerPlats, fil);
    return 0;
}
//--------------------------------------------------------//

//---------------skriva-ut-varor-paket---------------------------------//
void skriva_ut(varor varorILager[], int hylla){
    if (hylla == 0)
    {
        printf("Inga registrerade varor\n");
        return;
    }
    printf("%-11s%-11s%s\n", "Varunummer", "Namn", "Lagersaldo");
    for (int k = 0; k < hylla; k++){
        printf("%-11d%-11s%d\n", varorILager[k].varunummer, varorILager[k].namn, varorILager[k].saldo);
    }
}
//------------------------------------------------//

//----------------Ny-Vara-paket-----------------//

void registrera(varor nyVara[], int *pHylla){
    int check, i=0;
    char cmd[STORLEK]; 

    if (*pHylla >= SIZE){
        printf("Maximala storleken pa arrayen har natts");
        return;
    }

    printf("Ange varunummer (0 for avslut): ");
    scanf("%19s", cmd);
    las_bort();
    
   
    for (int k = 0; k < STORLEK && cmd[k] != '\0'; k++){
        //puts("DBG");
        if (cmd[k]>='0' && cmd[k]>='9'){
            puts("\nDu har mattat in fel tangent");
            registrera(nyVara,pHylla);
            return;
        }
    }
    sscanf(cmd,"%d",&check);
    if(check==0){
        return;
    }

    for (int j = 0; j < *pHylla; j++){
        if (check == nyVara[j].varunummer){
            puts("\nEj unikt nummer");
            registrera(nyVara, pHylla);
            return;
        }
    }

    nyVara[*pHylla].varunummer = check;
    printf("Ange namn: ");
    scanf("%s", nyVara[*pHylla].namn);
    
    while (nyVara[*pHylla].namn[i]!='\0') {
        nyVara[*pHylla].namn[i] = tolower(nyVara[*pHylla].namn[i]);
        i++;
    }

    las_bort();
    printf("Ange saldo: ");
    scanf("%d", &nyVara[*pHylla].saldo);
    las_bort();
    (*pHylla)++;
    registrera(nyVara, pHylla);
}

//---------------------Sok-vara----------------------------//
void sok_vara(varor varorILager[], int hylla, char avsluta){
    char sok[SIZE],cmd;

    puts("Sok efter varunamn (1)\nSok efter Lagersaldo (2)\nSok efter varunummer (3)");
    printf("Anvand (q) for at lamna\n>");
    cmd=tolower(getchar());
    las_bort();
    if(cmd=='q'){
        return;
    }
    printf("Sok vara:");
    switch(cmd){
        case '1': sokEfterNamn(varorILager,hylla);printf("\n"); break;
        case '2': sokEfterSaldo(varorILager,hylla);break;
        case '3': sokEfterNummer(varorILager,hylla);break;
        default: printf("Fel inmatning");
    }
    if(avsluta=='q'){
        return;
    }
    sok_vara(varorILager,hylla,avsluta);
}
//-------------------------------------------------------//

//-----------sok-hjalpfunktioner----------------------//
void sokEfterNamn(varor aVarorILager[],int aHylla){
    char sok[STORLEK];
    scanf("%s",sok);
    for(int k=0;k<aHylla;k++){
        sok[k]=tolower(sok[k]);
    }
    las_bort();
    sok[strcspn(sok, "\n")] = 0; // Remove trailing newline character
    printf("%-11s%-11s%s\n", "Varunummer", "Namn", "Lagersaldo");
    for (int k = 0; k < aHylla; k++){
        if (strstr(aVarorILager[k].namn, sok) != NULL){
            printf("%-11d%-11s%d\n", aVarorILager[k].varunummer, aVarorILager[k].namn, aVarorILager[k].saldo);
        }
    }
}

void sokEfterSaldo(varor aVarorILager[],int aHylla){
    int check;
    scanf("%d",&check);
    las_bort();
    printf("%-11s%-11s%s\n", "Varunummer", "Namn", "Lagersaldo");
    for (int k = 0; k < aHylla; k++){
        if(check==aVarorILager[k].saldo){
            printf("%-11d%-11s%d\n", aVarorILager[k].varunummer, aVarorILager[k].namn, aVarorILager[k].saldo);
        }
    }

}

void sokEfterNummer(varor aVarorILager[],int aHylla){
    int check;
    scanf("%d",&check);
    las_bort();
    printf("%-11s%-11s%s\n", "Varunummer", "Namn", "Lagersaldo");
    for (int k = 0; k < aHylla; k++){
        if(check==aVarorILager[k].varunummer){
            printf("%-11d%-11s%d\n", aVarorILager[k].varunummer, aVarorILager[k].namn, aVarorILager[k].saldo);
        }
    }

}

//------------------------------------------------------//
//-----------------------------------------------------//

//-----------andra-saldlo-paket-----------------------//
void andra_saldo(varor aVarorILager[], int *pPlats){
    int nummer, antal;
    char avslut='q';
    sok_vara(aVarorILager, *pPlats,avslut);
    printf("Ange varunummer: ");
    scanf("%d", &nummer);
    las_bort();
    
    for (int k = 0; k < *pPlats; k++)
    {
        if (aVarorILager[k].varunummer == nummer)
        {
            printf("Hur mycket vill du forandra antalet(anvand - for  att minska): ");
            scanf("%d", &antal);
            las_bort();
            aVarorILager[k].saldo += antal;
            printf("Lagersaldo for %s har uppdaterats till %d.\n", aVarorILager[k].namn, aVarorILager[k].saldo);
            return;
        }
    }
    printf("Hittade ingen vara med varunummer %d.\n", nummer);
}
//-----------------------------------------------------//

//------------------sort-package-----------------//


void sortera_varor(varor VarorSomFinnsILager[], int *pHylla)
{
    char cmd;
    printf("Hur vill du sortera varorna\nSortera efter varunummer(1)\nSortera efter namn(2)\nSortera efter saldo(3)\n>");
    scanf("%c", &cmd);
    las_bort();
    switch (cmd){
    case '1':sortera_varunummer(VarorSomFinnsILager, *pHylla);break;
    case '2':sortera_namn(VarorSomFinnsILager, *pHylla);break;
    case '3':sortera_saldo(VarorSomFinnsILager, *pHylla);break;
    default:printf("ERROR\n You entered wrong number or letter try again\n\n");sortera_varor(VarorSomFinnsILager, pHylla);return;
    }
}

void sortera_varunummer(varor VarorSomFinnsILager[], int plats){
    varor temp;

    for (int i = 0; i < plats - 1; i++){
        for (int j = 0; j < plats - i - 1; j++){
            if (VarorSomFinnsILager[j].varunummer-VarorSomFinnsILager[j+1].varunummer > 0){
                temp = VarorSomFinnsILager[j];
                VarorSomFinnsILager[j] = VarorSomFinnsILager[j + 1];
                VarorSomFinnsILager[j + 1] = temp;
            }
        }
    }
    printf("\nHar sorterat varorna efter varunummer\n");
}

void sortera_saldo(varor VarorSomFinnsILager[], int plats){
    varor temp;

    for (int i = 0; i < plats - 1; i++){
        for (int j = 0; j < plats - i - 1; j++){
            if (VarorSomFinnsILager[j].saldo-VarorSomFinnsILager[j+1].saldo > 0){
                temp = VarorSomFinnsILager[j];
                VarorSomFinnsILager[j] = VarorSomFinnsILager[j + 1];
                VarorSomFinnsILager[j + 1] = temp;
            }
        }
    }
    printf("\nHar sorterat varorna efter saldo\n");
}

void sortera_namn(varor VarorSomFinnsILager[], int plats){
    varor temp;

    for (int i = 0; i < plats - 1; i++){
        for (int j = 0; j < plats - i - 1; j++){
            if (strcmp(VarorSomFinnsILager[j].namn, VarorSomFinnsILager[j+1].namn) > 0){
                temp = VarorSomFinnsILager[j];
                VarorSomFinnsILager[j] = VarorSomFinnsILager[j + 1];
                VarorSomFinnsILager[j + 1] = temp;
            }
        }
    }
    printf("\nHar sorterat varorna efter varunamn\n");
}

//-------------------------------------------------//



//-------------------ta-bort-paket---------------------//
void ta_bort(varor VarorILager[], int *pHylla){
    int nummer;
    char avslut='q';
if (*pHylla == 0){
    printf("Inga registrerade varor\n");
    return;
}
sok_vara(VarorILager, *pHylla,avslut);
printf("Ange varunummer (eller 0 for avslut): ");
scanf("%d", &nummer);
las_bort();
if (nummer == 0){
    return;
}

for (int j = 0; j < *pHylla; j++){
    if (VarorILager[j].varunummer == nummer)
    {
        for (int k = j; k < *pHylla - 1; k++){
            VarorILager[k] = VarorILager[k + 1];
        }
        (*pHylla)--;
        printf("Varan med varunummer %d har tagits bort.\n", nummer);
        ta_bort(VarorILager,pHylla);
        return; 
    }
}
printf("Hittade ingen vara med varunummer %d.\n", nummer);
ta_bort(VarorILager,pHylla);
return;
}
//---------------------------------------------------//

//------------packa-upp-filen-paket-----------//
void lada_varor(varor gamlaVaror[], int *pPlats, char fil[])
{
    FILE *pBf;
    
    if ((pBf = fopen(fil, "r")) != NULL)
    {
        printf("\n[Laddar ");
        while ((*pPlats < SIZE-1) && (fscanf(pBf, "%s %d %d", gamlaVaror[*pPlats].namn, &gamlaVaror[*pPlats].saldo, &gamlaVaror[*pPlats].varunummer) == 3))
        {
            (*pPlats)++;
            printf("*");
        }
        fclose(pBf);
        puts("]\n");
    }
    else
    {
        puts("Fel kunde inte ladda Eller sa ar filen tom\n");
    }
}
//-------------------------------------------------//

//----------spara-filen-packet---------------------///
void spara_varor(varor nyaVaror[], int plats, char fil[])
{
    FILE *pBf;
   
    if ((pBf = fopen(fil, "w")) != NULL){
     printf("[ Sparar ");
    
        for (int k = 0; k < plats; k++)
        {
            fprintf(pBf, "%s %d %d\n", nyaVaror[k].namn, nyaVaror[k].saldo, nyaVaror[k].varunummer);
            printf("*");
        }
        fclose(pBf);
        puts("]\n");
    }
    else
    {
        puts("Kunde inte spara\n");
    }
    
}
//----------------------------------------------------------------------//

//------------------fel-inmating-verktyg-------------------------------//
void las_bort()
{
    char cmd;
    cmd = getchar();
    if (cmd != '\n')
    {
        las_bort();
    }
}
//----------------------------------------------------------------------//