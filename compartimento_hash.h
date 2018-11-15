#ifndef compartimento_hash_H
#define compartimento_hash_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cliente 
{
    int codigo;
    char nome[100];
    int idade;
    int liberado; 
    int prox;

} Cliente;

typedef struct CltIdade 
{
    int endereco;
    int codigo;
    int idade;

} CltIdade;

int cmpfunc (const void * a, const void * b);
Cliente* criaCliente(int c, char* n, int id);
Cliente* leCliente(FILE* in);
CltIdade* leCliente_idade(FILE* in);
void escreveCliente(FILE* out, Cliente* e);
void criaTeste(FILE* clientes);
int contaRegistros(FILE* arq);
int contaRegistros_Idade(FILE* arq);
void imprimeCliente(Cliente* e);
void imprimeCliente_idade(CltIdade* e);
void imprimeArquivo(FILE *f);
void imprimeArquivo_idade(FILE *f);
int funcHash(Cliente* clt);
int insereCliente(Cliente* clt);
int removeCliente(int indice);
void insercaoPropriamente(int i, int j, FILE* tabHash, Cliente* kira, Cliente* aux, Cliente* clt);
Cliente* buscaCliente(int codigo);
//novas funcoes do arquivo inverso
void Lefkowitz_Idade(FILE* A1);
void CriaA2_Idade(FILE* A1, FILE* A2);
void CriaA4_Idade(FILE* A2, FILE* A4);
void bubble_sort_vetCltIdade (CltIdade** vetor, int n);
void CriaA5_Idade(FILE* A4, FILE* A5);
void imprimirStructA5(FILE* A5);
void CriaA6_Idade(FILE* A4, FILE* A6);
void imprimirStructA6(FILE* A6);
void CriaA7_Idade(FILE* A4, FILE* A6, FILE* A7);
void bubble_sort_A7 (CltIdade** vetor, int n, int* proximos);
void CriaA8_Idade(FILE* A1, FILE* A7, FILE* A8);
void imprimeClienteA8(Cliente* e, int next);
int busca_idade(int idade);
int contaRegistrosA8(FILE* arq);
void imprimeArquivoA8(FILE* A8, int tamanho);

#endif