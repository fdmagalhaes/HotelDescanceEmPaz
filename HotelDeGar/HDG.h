#ifndef HDG_H_INCLUDED
#define HDG_H_INCLUDED


typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

int bissexto (int ano);
unsigned long dist_dias (Data inicio, Data fim);

#endif // HDG_H_INCLUDED
