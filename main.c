#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct
{
    long unsigned int codigo, telefone;
    float salario;
    char nome[50], cargo[20];
} funcionario;
void cadastrarFuncionario(funcionario *f, int q)
{
    int codigoRepetido;
    srand(time(NULL));
    printf("Digite as informações do novo funcionário\nNome: ");
    fflush(stdin);
    gets(f[q].nome);
    printf("Telefone: ");
    scanf("%li", &f[q].telefone);
    printf("Salário: ");
    scanf("%f", &f[q].salario);
    printf("Cargo: ");
    fflush(stdin);
    gets(f[q].cargo);
    do
    {
        codigoRepetido=0;
        f[q].codigo=rand()%89999+10000;
        for(int c=0; c<q; c++)
        {
            if(f[c].codigo==f[q].codigo)
            {
                codigoRepetido=1;
            }
        }
    }
    while(codigoRepetido!=0);
    printf("Código: %li\n", f[q].codigo);
}
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int q;
    funcionario *f;
    FILE *func;
    if((func=fopen("funcionarios.txt", "r"))==NULL)
    {
        q=0;
    }
    else
    {
        fscanf(func, "%i", &q);
    }
    f=malloc(sizeof(funcionario)*(q));
    for(int c=0; c<q; c++)
    {
        fgets(f[c].nome, 50, func);
        fgets(f[c].nome, 50, func);
        fscanf(func, "%li", &f[c].telefone);
        fscanf(func, "%f", &f[c].salario);
        fgets(f[c].cargo, 20, func);
        fgets(f[c].cargo, 20, func);
        fscanf(func, "%li", &f[c].codigo);
    }
    fclose(func);
    f=realloc(f, sizeof(funcionario)*(q+1));
    cadastrarFuncionario(f, q);
    q++;
    printf("%s\n", f[1].cargo);
    func=fopen("funcionarios.txt", "w");
    fprintf(func, "%i\n", q);
    for(int c=0; c<q; c++)
    {
        fprintf(func, "%s\n%li\n%.2f\n%s\n%li\n", f[c].nome, f[c].telefone, f[c].salario, f[c].cargo, f[c].codigo);
    }
    fclose(func);
    return 0;
}
