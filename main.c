#include <stdio.h>
#include <stdlib.h>
#include "compartimento_hash.h"

void func();

int main(){
	
	func();
	//printf("tcahu\n");
	return 0;
}	

void func(){
	int opcao;
	int opcaop;
	int quebra = 0;
	int idade;
	int prox;
	int codigo;
	int lefko = 1;

	FILE* tabHash;
	FILE* A8;

	Cliente* usuario;
	Cliente* aux;
	
	char nome[100];
	

	printf("Bem-vindo ao trabalho. O que deseja?\n\n");	
	do{
		printf("1: Criar tabela hash vazia\n2: Imprimir arquivo clientes\n3: Inserir cliente\n");
		printf("4: Remover cliente\n5: Buscar cliente\n6: Aplicar Lefkowitz\n7: Sair\n");
		scanf("%d", &opcao);
		printf("\n");

		switch(opcao){
			case 1:
				tabHash = fopen("tabHash.dat", "w+b");
				criaTeste(tabHash);
				printf("Arquivo criado com sucesso.\n");
				fclose(tabHash);
				break;
			case 2:
				tabHash = fopen("tabHash.dat", "r+b");
				imprimeArquivo(tabHash);
				fclose(tabHash);
				break;	
			case 3:
				printf("Digite o codigo, o nome, e a idade do cliente:\n");
				scanf("%d %[^\n] %d", &codigo, nome, &idade);
				usuario = criaCliente(codigo, nome, idade);
				insereCliente(usuario);
				lefko = 0;
				break;
			case 4:
				printf("Digite o código do cliente a ser deletado:\n");
				scanf("%d", &codigo);
				removeCliente(codigo);
				lefko = 0;
				break;
			case 5:
				A8 = fopen("a8_idade.dat", "r+b");
				printf("Deseja buscar pelo codigo do cliente ou por idade?\n");
				printf("1: Codigo\n");
				printf("2: Idade\n");
				scanf("%d", &opcaop);
				if(opcaop == 1){
					printf("Digite o codigo do cliente a ser buscado:\n");
					scanf("%d", &codigo);
					aux = buscaCliente(codigo);
					printf("\n");
					if(aux == NULL){
						printf("Cliente inexiste\n");
					}
					else{
						fread(&prox, sizeof(int), 1, A8);
						imprimeCliente(aux);
					}
				}
				else if(opcaop == 2){
					if(lefko == 1){
						printf("Digite a idade do(s) cliente(s) a ser(em) buscado(s):\n");
						scanf("%d", &codigo);
						busca_idade(codigo);
					}else if(lefko == 0){
						printf("PROCESSO INTERROMPIDO\n--Aplique Lefkowitz--\n");
					}
				}
				fclose(A8);	
				break;
			case 6:
				tabHash = fopen("tabHash.dat", "r+b");
				Lefkowitz_Idade(tabHash);
				lefko = 1;
				fclose(tabHash);
				break;
			case 7:
				quebra = 1;
				break;
			default:
				printf("Valor inválido\n");
		}
		printf("---------------\n");
	}while(quebra == 0);	
	//printf("oi\n");	
}