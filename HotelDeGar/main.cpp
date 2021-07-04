#include <iostream>
#include <stdio.h>
#include <string.h>
#include "HDG.h"


using namespace std;
//inicio classe usucario
class usuario
{
public:
    char nome[50], cargo[15];
    int cogigo, telefoneF;
    float salario;
};
//fim classe usuario

//inicio classe cliente
class cliente
{
public:
    char nome[50], endereco[100];
    int codigo, telefone;
};
//fim class cliente.

//inicio classe Estadia.
class estadia
{
public:
    int codigoEstadia, checkIn, checkOut, codigoCliente, apto;
};
//fim classe estadia.

// inicio classe quarto.
class quarto
{
public:
    int status; // 1=Ocupado 0=Disponivel
    int numero, quantidadeHospede;
    float valorDiaria, valorEstadia;
};
//fim classe quarto.


//Inicio fução cadastrar quarto
void cadastraQuarto()
{
    FILE *quartoH;//mude os nomes dos arquivos como desejar
    setlocale(LC_ALL,"portuguese");
    if ((quartoH = fopen("quartoH.txt", "r+b"))==NULL) // arquivo existe
    {
        printf("Arquivo não existia ... criando arquivo\n!");
        if((quartoH = fopen("quartoH.txt", "w+b"))==NULL) //arq não existe
        {
            printf("Erro na criação do arquivo quartoH.txt!!");//mude o nome
            exit(1);
        }
        system("pause");
    }
    quarto q;
    int flag;
    q.numero=1;
    while (flag!=-1)
    {
        printf("Digite '-1' para parar:");
        scanf("%d",&flag);

        q.numero++;
        printf ("numero do quarto e: %d",q.numero);
        fprintf(quartoH,"Número: %i",q.numero);
        printf("Digite 1 para ocupado e 0 para disponivel: ");
        scanf("%d",&q.status);
        if (q.status==0)
        {
            printf("quarto disponivel");
            fprintf(quartoH, "quarto disponivel");
        }
        if (q.status==1)
        {
            printf("quarto indisponivel");
            fprintf(quartoH, "quarto indisponivel");
        }
        if (q.numero%2==0) // quarto com pares quantidade de hospede 2
        {
            q.quantidadeHospede=2;
            q.valorDiaria=150.00;
            fprintf(quartoH,"Quarto duplo");
            fprintf(quartoH,"Valor da diaria: %.2f",q.valorDiaria);
        }
        else  // quarto impares quantidade de hospede 1
        {
            q.quantidadeHospede=1;
            q.valorDiaria=100.00;
            fprintf(quartoH,"Quarto individual");
            fprintf(quartoH,"Valor da diaria: %.2f",q.valorDiaria);
        }


        fprintf(quartoH,"numero: %i",q.numero);
    }

    fclose(quartoH);
}
//Fim fução cadastrar quarto


//Inicio Função localizar quarto disponivel
int retornaQuarto(FILE *quartoH, int codigo)
{
    quarto q;
    int apto;
    int posicao=-1, achou=0;
    fseek(quartoH,0,SEEK_SET);
    fread(&q, sizeof(q),1, quartoH);
    while((!feof(quartoH)) && (achou==0))
    {
        posicao++;
        if (q.status==0)
        {
            achou=1;
        }
        fread(&q, sizeof(q),1, quartoH);
    }
    if (achou==1)
    {
        return posicao;
    }
    else
    {
        return -1;
    }

    return apto;
}
//Fim Função localizar quarto disponivel


//inicio função calcular estadia.
void cadastraEstadia()
{
    FILE *estadiaH, *hospedeH;
    if ((estadiaH = fopen("estadiaH.txt", "w"))==NULL) // arquivo existe
    {
        printf("Arquivo não existia ... criando arquivo\n!");
        if((estadiaH = fopen("estadiaH.txt", "w"))==NULL) //arq não existe
        {
            printf("Erro na criação do arquivo estadiaH.txt!!");//mude o nome
            exit(1);
        }
        system("pause");
    }
    if ((hospedeH = fopen("hospedeH.txt", "w"))==NULL) // arquivo existe
    {
        printf("Arquivo não existia ... criando arquivo\n!");
        if((hospedeH = fopen("hospedeH.txt", "w"))==NULL) //arq não existe
        {
            printf("Erro na criação do arquivo hospedeH.txt!!");//mude o nome
            exit(1);
        }
        system("pause");
    }
    int dd, quantidadeHospede;
    Data in, out;
    quarto q;
    estadia e;
    cliente c;
    printf("Digite o nome do Hospede: ");
    fflush(stdin);
    gets(c.nome);
    fprintf(hospedeH,"Nome: %s",c.nome);
    printf("Digite o Endereço do Hospede: ");
    fflush(stdin);
    gets(c.endereco);
    fprintf(hospedeH,"Endereço: %s",c.endereco);
    printf("Qual o telefone do Hospede: ");
    scanf("%d",&c.telefone);
    fprintf(hospedeH,"Telefone: %i",c.telefone);

    printf("Coloque data de check-in no formato: dia/mes/ano\n");
    scanf("%d/%d/%d", &in.dia, &in.mes, &in.ano);
    fprintf(estadiaH,"Check-in: %d/%d/%d", in.dia, in.mes, in.ano);
    printf("Coloque data de check-out no formato: dia/mes/ano\n");
    scanf("%d/%d/%d", &out.dia, &out.mes, &out.ano);
    fprintf(estadiaH,"Check-in: %d/%d/%d", in.dia, in.mes, in.ano);

    printf("Qual a quantidade de Hospede: ");
    scanf("%d",&quantidadeHospede);
    if (quantidadeHospede==1)
    {
        q.valorDiaria=100;
    }
    else
    {
        q.valorDiaria=75*quantidadeHospede;
    }
    e.apto=retornaQuarto(quarto);
    dd=dist_dias(in, out);
    q.valorEstadia=dd*q.valorDiaria;
    printf("O valor da estadia sera: R$ %.2f",q.valorEstadia);
    fprintf(estadiaH,"O valor da estadia sera: R$ %.2f",q.valorEstadia);
    fprintf(estadiaH,"Estadia gravada quarto %i",e.apto);
    fclose(estadiaH);
    fclose(hospedeH);
}
//Fim função calcular estadia.


int main()
{
    setlocale(LC_ALL,"portuguese");
    int op;
    do
    {
        printf ("\n======Hotel Descanço Garantido=================\n");
        printf ("| 01 - Cadastrar Quarto |\n");
        printf ("| 02 - Cadastrar Estadia |\n");
        printf ("\n=================================");
        printf ("\n| DIGITE 8 PARA SAIR |\n");
        printf ("=================================\n");
        switch (op)
        {
        case '1':
            cadastraQuarto();
            break;
        case '2':
            cadastraEstadia();
            break;
        }
    }
    while(op!='8');
    return 0;
}
