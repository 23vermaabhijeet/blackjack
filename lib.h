
#ifndef LIB_H
#define INF 1
#define SUP 13
#define LIB_H
#define SOGLIA 21
#define NUM_CARTE 12
#include "conio2.h"

typedef struct {
  int numero;
  int seme;
} Carte;

int getRand(int inf, int sup);
int menu();

void printRegolamento();

void makeCard(Carte cards);

int getCarta(int *somUtente, Carte *oneCard);

void drawTable(int bet, int soldi);

void drawMultipleCards(int numCarte, Carte *cards);

void stampaNumero(Carte *card);

void printOneCard(int i, int j, Carte *cards);

void getCashIn(int *cash);

void stampaCornice(int c, int i, int j,int dim_i, int dim_j, Carte *cards);

void stampaGuadagno(int soldi, int sommaCaricheFatte, int flag);
#endif // LIB_H

