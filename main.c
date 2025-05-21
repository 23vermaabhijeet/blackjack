#include "lib.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SALDO_INIZIALE 1000
//#include "conio2.h"

int main() {

    int cartaUtente = 0, cartaBanco = 0, bet = 0, soldi = 0, mScelta = 0, i = 0, j = 0;
    int somUtente = 0, somBanco = 0, creditUtente = 0, flag = 0, sommaCaricheFatte = 0;
    int doubleD = 0;
    char risp;

    char bj[] = {"\t @@@@@@@     @@        @@@@@@@@@   @@@@@@@    @@@    @@@    "
                    "@@@@@@@@@    @@@@@@@@@    @@@@@@@  @@@    @@@\n"
                    "\t @@   @@     @@        @@     @@   @@         @@@   @@@      "
                    "   @@       @@     @@    @@       @@@   @@@ \n"
                    "\t @@   @@     @@        @@     @@   @@         @@@  @@@       "
                    "   @@       @@     @@    @@       @@@  @@@ \n"
                    "\t @@@@@@@     @@        @@@@@@@@@   @@         @@@ @@@        "
                    "   @@       @@@@@@@@@    @@       @@@ @@@ \n"
                    "\t @@   @@     @@        @@     @@   @@         @@@  @@@      "
                    "@   @@       @@     @@    @@       @@@  @@@ \n"
                    "\t @@   @@     @@        @@     @@   @@         @@@   @@@     "
                    "@   @@       @@     @@    @@       @@@   @@@ \n"
                    "\t @@@@@@@      @@@@@@@@  @@     @@   @@@@@@@    @@@    @@@ @@@@@@       @@     @@    @@@@@@@  @@@    @@@ \n"};


    Carte multipleBanco[SUP];
    Carte multipleUtente[SUP];
    system("color f2");
    srand(time(NULL));
    do { /*Ciclo iterativo che itera finché l'utente non sceglie opzione FINE*/
        textcolor(GREEN);
        textbackground(WHITE);
        printf("\n %s", bj); /*Stamap della scritta BlackJack*/
        drawTable(bet, soldi);
        risp = 'y';
        mScelta = menu(); /*Visualizzazione menu*/


        switch (mScelta) {
            case 1:
                printRegolamento();
                break;
            case 2:
                getCashIn(&soldi);
                sommaCaricheFatte += soldi;
                soldi = sommaCaricheFatte;
                break;
            case 3:

                if (soldi > 0) {
                    do {
                        i = 0, j = 0;
                        somUtente = 0, somBanco = 0;
                        creditUtente = 0, flag = 1;
                        do {
                            printf("\n Bet (Disponibile: %d): ", soldi);
                            scanf("%d", &bet);
                        } while (bet <= 0 || bet > soldi);

                        textcolor(BLACK);
                        cartaBanco = getCarta(&somBanco, &multipleBanco[j]); /*Genere la prima carta del banco e lo memorizza nell'array di struct Carte*/
                        printf("\n Prima carta banco: %d", cartaBanco);
                        drawMultipleCards(j, multipleBanco); /*Disegna la carta*/

                        cartaUtente = getCarta(&somUtente, &multipleUtente[i]); /*Genere la prima carta dell'utente e lo memorizza nell'array di struct Carte*/
                        printf("\n Prima carta utente: %d",cartaUtente);

                        i++;
                        cartaUtente = getCarta(&somUtente, &multipleUtente[i]); /*Genere la seconda carta dell'utente e lo memorizza nell'array di struct Carte*/
                        printf("\n Seconda carta utente: %d (TOTALE: %d)", cartaUtente, somUtente);


                        drawMultipleCards(i, multipleUtente); /*Disegna le carte dell'utente*/

                        if (somUtente == SOGLIA) {
                            creditUtente = 2;
                        } else if (somUtente > SOGLIA) {
                            creditUtente = 0;
                        } else if ((somUtente > SOGLIA && somBanco > SOGLIA) || (somUtente == SOGLIA && somBanco == SOGLIA)) {
                            creditUtente = 3;
                        } else {
                            do {
                                do {
                                    printf("\n Cosa si vuole fare? (c = CARTA; s = STAI; d = DOUBLE DOWN): ");
                                    while (getchar() != '\n');
                                    scanf("%c", &risp);
                                    risp = tolower(risp);
                                } while (risp != 'c' && risp != 's' && risp != 'd'); /*Controllo sulla risposta*/

                                switch (risp) {
                                    case 's': /*Stai*/
                                        do {
                                            j++;
                                            cartaBanco = getCarta(&somBanco, &multipleBanco[j]); /*Genera le carte per il banco*/

                                            printf("\n Carta banco: %d (TOTALE: %d)", cartaBanco, somBanco);
                                        } while (somBanco < 17); /*Genera carte finchè la somma sia minore di 17*/

                                        printf("\n\n");
                                        drawMultipleCards(j, multipleBanco); /*Stampa le carte del banco*/

                                        if (somBanco > SOGLIA) { /*Controllo se il banco ha superato la soglis*/
                                            creditUtente = 1;
                                        } else if (somBanco < somUtente) {
                                            creditUtente = 1;
                                        }
                                        break;

                                    case 'c':
                                        i++;
                                        cartaUtente = getCarta(&somUtente, &multipleUtente[i]); /*Genera carta se l'utente desidera un'altra carta*/

                                        printf("\n Carta utente: %d (TOTALE: %d)", cartaUtente, somUtente);
                                        drawMultipleCards(i, multipleUtente);

                                        if (somUtente > SOGLIA) { /*Fa il controllo per credit, cioè se l'utente ha vinto o perso ecc.*/
                                            creditUtente = -1;
                                        } else if (somUtente == SOGLIA) {
                                            creditUtente = 2;
                                        }
                                        break;

                                    case 'd':
                                        i++;
                                        cartaUtente = getCarta(&somUtente, &multipleUtente[i]);

                                        printf("\n Carta utente: %d (TOTALE: %d)", cartaUtente, somUtente);
                                        drawMultipleCards(i, multipleUtente);

                                        if (somUtente > SOGLIA) {
                                            creditUtente = -1;
                                        } else if (somUtente == SOGLIA) {
                                            creditUtente = 4;
                                        }
                                        doubleD = 1;
                                }
                            } while (somUtente < SOGLIA && risp == 'c' && creditUtente >= 0 && doubleD == 0);
                          }

                        if (somUtente == somBanco) {
                            creditUtente = 3;
                        }
                        switch (creditUtente) {
                            case -1:
                                printf("\n Hai perso!");
                                soldi -= bet;
                                break;
                            case 0:
                                printf("\n Hai perso!");
                                soldi -= bet;
                                break;
                            case 1:
                                printf("\n Cheer! Hai vinto!");
                                soldi += 2 * bet;
                                break;
                            case 2:
                                printf("\n Hurray! Blackjack!!");
                                soldi += 3 * bet;
                                break;
                            case 3:
                                printf("\n Push! Nessun vincitore! ");
                                break;
                            case 4:
                                printf("\n Cheer! Hai vinto facendo double down!");
                                soldi += 2 * (bet * 2);
                        }

                        printf("\n Saldo disponibile: %d", soldi);

                        if (soldi > 0) {
                            do {
                                printf("\n Vuoi giocare di nuovo (y o n)? ");
                                while (getchar() != '\n')
                                ;
                                scanf("%c", &risp);
                                risp = tolower(risp);
                            } while (risp != 'y' && risp != 'n');
                        }

                    } while (risp == 'y' && soldi > 0);

                } else {
                    printf("\n CARICA IL SALDO!");
                }
                break;

            case 4:
                printf("\n Ti ringraziamo per aver giocato con noi\n");
                stampaGuadagno(soldi, sommaCaricheFatte, flag);
        }

        textcolor(GREEN);
        printf("\n\n Presso ENTER to continue...");
        getche();
        //    clrscr();
        system("cls");
    } while (mScelta >= 1 && mScelta <= 3);
    return 0;
}
