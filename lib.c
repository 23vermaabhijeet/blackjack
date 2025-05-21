#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getRand(int inf, int sup) {
    int num = 0;
    num = inf + rand() % (sup - inf + 1);

    return num;
}

int menu() {
    textcolor(GREEN);
    int r = 0;
    printf("\n Benvenuto! Cosa desidera fare?");
    printf("\n\n\t [1] Regolamento\n");
    printf("\n\n\t [2] Cash-In (CARICA IL SALDO)\n");
    printf("\n\n\t [3] Gioca a BlackJack\n");
    printf("\n\n\t [4] Fine\n");
    do {
        printf("\n Inserire il codice dell'azione che si vuole eseguire: ");
        scanf("%d", &r);
    } while (r < 1 || r > 4);

    return r;
}

void printRegolamento() {
    textcolor(GREEN);
    printf(
    "\n 1) Nel blackjack, l'obiettivo e' avvicinarsi il piu' possibile a un "
    "punteggio di 21 senza superarlo. Se superi 21, perdi automaticamente.");
    printf("\n 2) Ogni carta ha un valore numerico: le carte numerate da 2 a 10 "
    "valgono il loro valore nominale, le carte"
    "facciali (J, Q, K) valgono 10, e l\'Asso puo' valere 1 o 11 a scelta "
    "del giocatore.");
    printf("\n 3) All'inizio del gioco, ricevi due carte coperte, mentre il "
    "banco ha una carta coperta e una scoperta.");
    printf("\n 4) Puoi decidere se chiedere altre carte (\"Hit\") per aumentare "
    "il tuo punteggio o rimanere con le carte attuali "
    "(\"Stand\") e passare al turno successivo.");
    printf("\n 5) Se ritieni che una sola carta aggiuntiva ti portera' a un "
    "punteggio vincente, puoi raddoppiare la tua puntata "
    "originale (\"Double Down\") e ricevere solo una carta aggiuntiva.");
    printf("\n 6) Una volta che hai fatto tutte le tue scelte, e' il turno del "
    "banco. Il banco deve tirare carte fino a raggiungere o superare un "
    "punteggio di 17");
    printf("\n 7) Alla fine, vinci se hai un punteggio piu' alto del banco senza "
    "superare 21. Se il banco supera 21, vinci "
    "automaticamente. Se i punteggi sono uguali, e' un pareggio "
    "(\"Push\") e recuperi la tua puntata.");
    printf("\n 8) E' importante tenere conto delle carte visibili del banco per "
    "prendere decisioni strategiche durante il gioco.\n\n\n\n");
}

int getCarta(int *somUtente, Carte *oneCard) {

    int numCard = 0;
    oneCard->numero = getRand(INF, SUP); /*Genera un numero della carta per salvarlo nello struct*/
    oneCard->seme = getRand(3, 6); /*Genera un numero del seme per salvarlo nello struct*/


    if(oneCard->numero == 12 || oneCard->numero == 13){ /*Se la carta generata è 12 o 13, ovvero K e Q, il valore di queste carte è 10*/
        *somUtente += 10;
        numCard = 10;
    }
    else{
        *somUtente += oneCard->numero;
        numCard = oneCard->numero;
    }
    return numCard;
}

void drawTable(int bet, int soldi) {
    textcolor(GREEN);
    textbackground(WHITE);
    printf("\n\n");
    printf("\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\t @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\t  @@@@@@                                                                                     @@@@@\n");
    printf("\t   @@@@@@                                                                                  @@@@@\n");
    printf("\t     @@@@@@                                                                              @@@@@\n");
    printf("\t       @@@@@@                                                                          @@@@@\n");
    printf("\t         @@@@@@                                                                      @@@@@\n");
    printf("\t           @@@@@@                                                                  @@@@@\n");
    printf("\t             @@@@@@                                                              @@@@@\n");
    printf("\t               @@@@@@                                                          @@@@@\n");
    printf("\t                 @@@@@@                                                      @@@@@\n");
    printf("\t                   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\t                                         Disponibile: %d Euro                        \n",soldi);
    textcolor(BLACK);
    textbackground(WHITE);
}

void drawMultipleCards(int numCarte, Carte *cards) {
    int i = 0, j = 0, dim_i = 11, dim_j = 11, c = 0;

    printf("\n");
    for (i = 0; i < dim_i; i++) {
        for (c = 0; c <= numCarte; c++) { /*Itera per il numero di carte*/
            for (j = 0; j < dim_j; j++) {
                stampaCornice(c, i, j, dim_i, dim_j, cards);
                textcolor(BLACK);
                textbackground(WHITE);
            }
        }
        printf("\n");
    }
}



void getCashIn(int *cash) {
    do {
        printf("\n Quanto vuoi caricare: ");
        scanf("%d", cash);
    } while (*cash <= 0);
}



void stampaGuadagno(int soldi, int sommaCaricheFatte, int flag){ /*Stampa il guadagno o perdita e il messaggio finale*/
    int guadagno = 0;
    guadagno = soldi - sommaCaricheFatte; /*Il guadagno viene calcolato come i soldi rimasti e la somma di tutte le cariche fatte*/

    if (flag == 1) {
        if (guadagno >= 0)
            printf("\n\n Guadagno totale: %d", guadagno);
        else {
            printf("\n\n Perdita totale: %d", abs(guadagno));
        }
    }
    printf("\n Gioca responsabilmente e ricorda che il gioco d'azzardo "
    "dovrebbe essere considerato un divertimento occasionale, "
    "mantenendo sempre il controllo sulle tue finanze");
}


void stampaNumero(Carte *card){ /*Sottoprogramma per stampare il numero*/
    if (card->numero == 10)
        printf("%c", card->numero + 64);
    else if(card->numero == 12)
        printf("%c", card->numero + 62);
    else if (card->numero == 13)
        printf("%c", card->numero + 68);
    else if (card->numero == 11)
        printf("%c", card->numero + 54);
    else
        printf("%d", card->numero);
}

void stampaCornice(int c, int i, int j,int dim_i, int dim_j, Carte *cards){
    if ((i == 0 && j == 0))
        printf("%c", 218);
    else if ((i == dim_i - 1 && j == dim_j - 1))
        printf("%c", 217);
    else if ((i == 0 && j == dim_j - 1))
        printf("%c", 191);
    else if ((i == dim_i - 1 && j == 0))
        printf("%c", 192);
    else if (i == 0 || i == dim_i - 1)
        printf("%c", 196);
    else if (j == 0 || j == dim_j - 1)
        printf("%c", 179);
    else if ((i == 1 && j == 1) ||(i == dim_i - 2 && j == dim_j - 2)){
        if (cards[c].seme == 3 || cards[c].seme == 4){
            textcolor(LIGHTRED);
            textbackground(WHITE);
            stampaNumero(&cards[c]);
        } else {
            stampaNumero(&cards[c]);
        }
    }
    // seme
    else if (i == (dim_i / 2) && j == (dim_j / 2)) {
        if (cards[c].seme == 3 || cards[c].seme == 4) {
            textcolor(LIGHTRED);
            textbackground(WHITE);
            printf("%c", cards[c].seme);
        } else {
            printf("%c", cards[c].seme);
        }
    } else {
        printf(" ");
    }
}

