#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compartimento_hash.h"

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

Cliente* criaCliente(int c, char* n, int id){
    Cliente* new = (Cliente*) malloc(sizeof(Cliente));
    new->codigo = c;
    new->idade = id;
    new->liberado = -1;
    new->prox = -1;
    strcpy(new->nome, n);

    return new;
}

CltIdade* criaCltIdade(int c, char* n, int id){
    CltIdade* new = (CltIdade*) malloc(sizeof(CltIdade));
    new->endereco = -1;
    new->codigo = c;
    new->idade = id;
    return new;
}

void criaTeste(FILE* tabHash){
	int i;
	int j = -1;	

	Cliente* vazio = criaCliente(j, "Vazio", -1);
    vazio->liberado = 1;


	for(i=0;i<7;i++){
		escreveCliente(tabHash, vazio);
		j--;
		vazio->codigo = j;
	}
}

void escreveCliente(FILE* out, Cliente* e){
    Cliente* aux;
    for(int i = 0; i <= contaRegistros(out); i++)
    {
        aux = leCliente(out);
    }
    fwrite(&e->codigo, sizeof(int), 1, out);
    fwrite(e->nome, sizeof(char), sizeof(e->nome), out);
    fwrite(&e->idade, sizeof(int), 1, out);
    fwrite(&e->liberado, sizeof(int), 1, out);
    fwrite(&e->prox, sizeof(int), 1, out);
}

int contaRegistros(FILE* arq){
    rewind(arq);
    int retorno = -1;
    Cliente* aux;

    while(!feof(arq))
    {
        aux = leCliente(arq);
        retorno++;
    }
    rewind(arq);
    return retorno;
}

int contaRegistros_Idade(FILE* arq){
    rewind(arq);
    int retorno = -1;
    CltIdade* aux;

    while(!feof(arq))
    {
        aux = leCliente_idade(arq);
       // printf("oi2\n");
        retorno++;
    }
    return retorno;
}

int contaRegistrosA8(FILE* arq){
    rewind(arq);
    int retorno = -1;
    Cliente* aux;
    int prox;

    while(!feof(arq))
    {
        aux = leCliente(arq);
        fread(&prox, sizeof(int), 1, arq);
        retorno++;
    }
    rewind(arq);
    return retorno;
}

Cliente* leCliente(FILE* in){
    Cliente* lido = (Cliente*) malloc(sizeof(Cliente));
    if (0 >= fread(&lido->codigo, sizeof(int), 1, in))
    {
        free(lido);
        return NULL;
    }

    fread(lido->nome, sizeof(char), sizeof(lido->nome), in);
    fread(&lido->idade, sizeof(int), 1, in);
    fread(&lido->liberado, sizeof(int), 1, in);
    fread(&lido->prox, sizeof(int), 1, in);

    return lido;
}

CltIdade* leCliente_idade(FILE* in){
    CltIdade* lido = (CltIdade*) malloc(sizeof(CltIdade));
    if (0 >= fread(&lido->endereco, sizeof(int), 1, in))
    {
        free(lido);
        //printf("oi\n");
        return NULL;
    }

    //fread(lido->nome, sizeof(char), sizeof(lido->nome), in);
    fread(&lido->codigo, sizeof(int), 1, in);
    fread(&lido->idade, sizeof(int), 1, in);
    //fread(&lido->liberado, sizeof(int), 1, in);
    //fread(&lido->prox, sizeof(int), 1, in);

    return lido;
}

void imprimeArquivo(FILE *f){

	printf("Arquivo Clientes:\n\n");
    int n = contaRegistros(f);
    Cliente* aux;

    rewind(f);

    for(int i = 0; i < n; i++){

        aux = leCliente(f);
        
        if(aux->liberado == -1){ //&& aux->prox != 0){
            printf("Cliente %d:\n", i+1);
            imprimeCliente(aux);
        }

    }
}

void imprimeArquivo_idade(FILE *f){

	printf("Arquivo Clientes_IDADE:\n\n");
    int n = contaRegistros_Idade(f);
    CltIdade* aux;
    int i;
    rewind(f);
	//printf("oi1\n");
    for(i = 0; i < n; i++){

        aux = leCliente_idade(f);
        
        //if(aux->liberado == -1){ //&& aux->prox != 0){
            printf("CltIdade %d:\n", i);
            imprimeCliente_idade(aux);
        //}

    }
}

void imprimeCliente(Cliente* e){
    if(e == NULL)
    {
        printf("Cliente nao encontrado!\n");
    }

    
    else if(e->liberado == 1)//liberado == 1 significa liberado
    {
       printf("\n");
       printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Liberado\nProximo Cliente: %d\n\n", e->codigo, e->nome, e->idade, e->prox);
    }
	
    else if(e->liberado == -1)//liberado == -1 significa ocupado
    {
    	if(e->prox != -1){
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente: Cliente %d\n\n", e->codigo, e->nome, e->idade, e->prox+1);
    	}
    	else{
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente: %d\n\n", e->codigo, e->nome, e->idade, e->prox);
    	}
        		
    }
}

void imprimeCliente_idade(CltIdade* e){
    if(e == NULL)
    {
        printf("Cliente_idade nao encontrado!\n");
    }

    
    else //if(e->liberado == 1)//liberado == 1 significa liberado
    {
       printf("\n");
       printf("Endereco: %d\nCodigo: %d\nIdade: %d\n\n", e->endereco, e->codigo, e->idade);
    }
	/*
    else if(e->liberado == -1)//liberado == -1 significa ocupado
    {
    	if(e->prox != -1){
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente: Cliente %d\n\n", e->codigo, e->nome, e->idade, e->prox);
    	}
    	else{
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente: %d\n\n", e->codigo, e->nome, e->idade, e->prox);
    	}
        		
    }
	*/
}

int insereCliente(Cliente* clt){

	FILE* tabHash = fopen("tabHash.dat", "r+b");

	Cliente* aux;
	Cliente* kira;

	int tamanho = contaRegistros(tabHash);
	int codNewCliente = funcHash(clt);
	Cliente* nulo = (Cliente*) malloc(sizeof(Cliente));
	
	char* nome = "";
	nulo->codigo = -1;
    strcpy(nulo->nome, nome);
    nulo->idade = -1;
    nulo->liberado = 1; 
    nulo->prox = -1;
    aux = nulo;
	
	int i = 0;
	int j;
	int k;

	rewind(tabHash);

	for(i = 0; i < codNewCliente; i++){
		aux = leCliente(tabHash); //leio os clientes
	}

	aux = leCliente(tabHash);
	rewind(tabHash);

	if(aux == NULL){
		aux = nulo;
	}
	if(aux->liberado == -1){//se o espaço onde quero adicionar está ocupado
		if(aux->codigo == clt->codigo){ //se o cliente auxiliar tiver o mesmo código do cliente que quero inserir
			printf("Cliente já existente!\n");
			return 0; //retorno 0, pois o cliente já existe e não foi gravado
		}else{
			//printf("oioi\n");

			while(aux->prox != -1 && aux->liberado == -1){
				//printf("-oioi\n");
				i = aux->prox % 7;
				fseek(tabHash, i * sizeof(Cliente), SEEK_SET);
				aux = leCliente(tabHash);
				
				if(aux->liberado == 1){
					i--;
					fseek(tabHash, i * sizeof(Cliente), SEEK_SET);
					aux = leCliente(tabHash);
					break;
				}
			}
			//funfando
			
			kira = aux;
			//printf("----\n");
			//imprimeCliente(kira);
			j = i;
			
			//inserção após a colisão
			while(i < 7){
				
				fseek(tabHash, i * sizeof(Cliente), SEEK_SET); //eu seto o ponteiro de volta
				aux = leCliente(tabHash);//leio o cliente pra saber se ele esta liberado
				//printf("oioi-\n");
				if(aux == NULL){
					aux = nulo;
				}
				if(aux->liberado == 1){
					//printf("oioi--\n");
					insercaoPropriamente(i, j, tabHash, kira, aux, clt);
					return 1;
				}
				i++;
			}

			//inserção antes da colisão
			rewind(tabHash);
			aux = leCliente(tabHash);
			rewind(tabHash);
			for(i = 0; i < j && j != -1; i++){
				aux = leCliente(tabHash);
				if(aux->liberado == 1){
					insercaoPropriamente(i, j, tabHash, kira, aux, clt);
					return 1;
				}

			}
			
			if(j != -1){
				printf("Arquivo Cheio\n");
			}
		}
	}
	else{
		clt->prox = aux->prox;
		fseek(tabHash, i * sizeof(Cliente), SEEK_SET); //eu seto o ponteiro de volta
		fwrite(clt, sizeof(Cliente), 1, tabHash); //reescrevo as informações com o cliente novo que inserirei
		printf("\nCliente Inserido\n\n");
		
		Lefkowitz_Idade(tabHash);
		//printf("oi\n");
		//imprimeArquivoA8(tabHash, tamanho);
		return 1;
	}

	return 2;
}

int removeCliente(int codigo){

    FILE* tabHash = fopen("tabHash.dat", "r+b");
	Cliente* auxiliar;
	Cliente* rohan;
	int tamanho = contaRegistros(tabHash);
    int proximo;
    int i;
    int j;
	rewind(tabHash);

	for(i = 0; i < tamanho; i++){ //percorro os clientes

        auxiliar = leCliente(tabHash); //leio o cliente

		if(auxiliar->codigo == codigo && auxiliar->liberado == -1){ //se o cliente é o que eu procuro

			proximo = auxiliar->prox;

            //parte responsável por liberar o registro
            rewind(tabHash);
            auxiliar->liberado = 1;//torna o registro liberado
            fseek(tabHash, sizeof(Cliente) * i, SEEK_SET);
			fwrite(auxiliar, sizeof(Cliente), 1, tabHash);
			printf("Cliente removido!\n\n");
            rewind(tabHash);
            

			return 1;
		}
	}

    printf("Cliente a remover inexistente!\n");
	return 0;
}

int funcHash(Cliente* clt){
    return clt->codigo % 7;
}

void insercaoPropriamente(int i, int j, FILE* tabHash, Cliente* kira, Cliente* aux, Cliente* clt){

	int tamanho = contaRegistros(tabHash);
	int codNewCliente;
	Cliente* novo;
	Cliente* nulo = (Cliente*) malloc(sizeof(Cliente));
	char* nome = "";
	fseek(tabHash, i * sizeof(Cliente), SEEK_SET); //eu seto o ponteiro de volta
	
	aux = leCliente(tabHash);



	if(aux == NULL){
		nulo->codigo = -1;
    	strcpy(nulo->nome, nome);
    	nulo->idade = -1;
    	nulo->liberado = 1; 
    	nulo->prox = -1;
    	aux = nulo;
	}
	clt->prox = aux->prox;
	//printf("oioi\n");

	fseek(tabHash, i * sizeof(Cliente), SEEK_SET); //eu seto o ponteiro de volta
	
	fwrite(clt, sizeof(Cliente), 1, tabHash); //reescrevo as informações com o cliente novo que inserirei
	kira->prox = i;
	//imprimeCliente(kira);
	//imprimeCliente(clt);
	codNewCliente = funcHash(kira);
	fseek(tabHash, j * sizeof(Cliente), SEEK_SET); //eu seto o ponteiro de volta
	fwrite(kira, sizeof(Cliente), 1, tabHash); //reescrevo as informações do cliente já inserido no campo proximo
	j == -1;//indico que achei um lugar para adicionar e paro com as tentativas de achar um
	printf("\nCliente Inserido\n\n");
	imprimeArquivo(tabHash);
	rewind(tabHash);
}

Cliente* buscaCliente(int codigo){

	FILE* tabHash = fopen("tabHash.dat", "r+b");

	Cliente* aux;
	Cliente* tem;

	int i;
	int yukako = codigo % 7;

	//fseek(tabHash, yukako * sizeof(Cliente), SEEK_SET);
	//tem = leCliente(tabHash);

	for(i = 0;i<7;i++){
		fseek(tabHash, yukako * sizeof(Cliente), SEEK_SET);
		aux = leCliente(tabHash);

		if(codigo == aux->codigo){
			if(aux->liberado = -1){
				return aux;
			}
			else{
				return NULL;
			}
		}
		else{
			//printf("yukako = %d\n",yukako);
			if(aux->prox != -1){
				yukako = aux->prox;
			}else{
				if(yukako == 6){
					yukako = 0;
				}
				else{
					yukako++;
				}
			}
		}
	}
	return NULL;
}

void Lefkowitz_Idade(FILE* A1){
	FILE* A2 = fopen("a2_idade.dat", "w+b");
	FILE* A4 = fopen("a4_idade.dat", "w+b");
	FILE* A5 = fopen("a5_idade.dat", "w+b");
	FILE* A6 = fopen("a6_idade.dat", "w+b");
	FILE* A7 = fopen("a7_idade.dat", "w+b");
	FILE* A8 = fopen("a8_idade.dat", "w+b");
	
	

	CriaA2_Idade(A1, A2);
	//printf("a1->a2\n");
	CriaA4_Idade(A2, A4);
	//printf("a2->a4\n");
	//remove("a2_idade.dat");
	CriaA5_Idade(A4, A5);
	//printf("a4->a5\n");
	CriaA6_Idade(A4, A6);
	//printf("a4->a6\n");
	CriaA7_Idade(A4, A6, A7);
	//printf("a6->a7\n");
	CriaA8_Idade(A1, A7, A8);
	//printf("a1 e a7 -> a8\n");

	fclose(A2);
	fclose(A4);
	fclose(A5);
	fclose(A6);
	fclose(A7);
	fclose(A8);
}

void CriaA2_Idade(FILE* A1, FILE* A2){

	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	int i;
	Cliente* aux;
	//CltIdade* aux_id1;
	int num = contaRegistros(A1);
	rewind(A1);

	//printf("num = %d\n",num);

	for(i = 0; i < num; i++){
		
		aux = leCliente(A1);
		//imprimeCliente(aux);
		//printf("aux->liberado = %d\n",aux->liberado);
		if(aux->liberado == -1){
			//printf("bla\n");
			aux_id->endereco = i+1;
			aux_id->codigo = aux->codigo;
			aux_id->idade = aux->idade;
			fwrite(aux_id, sizeof(CltIdade), 1, A2);
			//imprimeCliente_idade(aux_id);
			//printf("-----\n");
		}
	}
	//imprimeArquivo_idade(A2);
}

void CriaA4_Idade(FILE* A2, FILE* A4){
	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	int tamanho = contaRegistros_Idade(A2);
	int i;
	int* idades = (int*) malloc(tamanho * sizeof(int));
	rewind(A2);
	CltIdade** vet_clt = (CltIdade**) malloc(tamanho*sizeof(CltIdade));

	for(i = 0; i < tamanho; i++){
		aux_id = leCliente_idade(A2);
		vet_clt[i] = aux_id; 
	}

	bubble_sort_vetCltIdade(vet_clt, tamanho);
	
	for(i = 0; i < tamanho; i++){
		fwrite(vet_clt[i], sizeof(CltIdade), 1, A4);
	}
	//imprimeArquivo_idade(A4);
	free(aux_id);
	free(idades);
	free(vet_clt);
}

void bubble_sort_vetCltIdade (CltIdade** vetor, int n) {
    int k, j;
    CltIdade* aux;
    for (k = n - 1; k > 0; k--) {
      	for (j = 0; j < k; j++) {
        	if (vetor[j]->idade > vetor[j + 1]->idade) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void CriaA5_Idade(FILE* A4, FILE* A5){
	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	int tamanho = contaRegistros_Idade(A4);
	int* quant_idades = (int*) malloc(tamanho * sizeof(int));//vetor só com as quantidades de idades preenchidas 
	int* idades = (int*) malloc(tamanho * sizeof(int));//vetor com as idades
	int* primeiro_ed = (int*) malloc(tamanho * sizeof(int));//vetor com o primeiro endereço com cada idade preenchido
	int idade_aux;//idade do cliente que está sendo lido
	int idade_atual = -1;//idade do cliente que está atualmente sendo "repetido"
	int i;
	int j = -1;
	
	rewind(A4);
	
	for(i = 0; i < tamanho; i++){
		quant_idades[i] = 0;
	}

	for(i = 0; i < tamanho; i++){
		
		aux_id = leCliente_idade(A4);
		//printf("-----\n");
		//imprimeCliente_idade(aux_id);
		//printf("-----\n");
		idade_aux = aux_id->idade;
		if(idade_aux == idade_atual){
			quant_idades[j]++;
		}
		else{
			j++;
			primeiro_ed[j] = aux_id->endereco;
			idades[j] = idade_aux;
			quant_idades[j]++;
			idade_atual = idade_aux;
		}
	}

	for(i = 0; i < tamanho && quant_idades[i] != 0; i++){
	}

	for(j = 0; j < i; j++){
		//printf("idades = %d",idades[j]);
		fwrite(&idades[j], sizeof(int), 1, A5);
		fwrite(&primeiro_ed[j], sizeof(int), 1, A5);
		fwrite(&quant_idades[j], sizeof(int), 1, A5);
	}

	rewind(A5);
	/*
	for(j = 0; j < i; j++){
		imprimirStructA5(A5);
		printf("\n");
	}
	*/
	//free(quant_idades);
	//free(idades);
	//free(primeiro_ed);
}	

void imprimirStructA5(FILE* A5){
	int age;
	int adress;
	int quantity;


	fread(&age, sizeof(int), 1, A5);
	fread(&adress, sizeof(int), 1, A5);
	fread(&quantity, sizeof(int), 1, A5);

	printf("Idade = %d\n", age);
	printf("Endereco = %d\n", adress);
	printf("Quantidade = %d\n", quantity);
}

void CriaA6_Idade(FILE* A4, FILE* A6){
	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	CltIdade* aux_id_prox = (CltIdade*) malloc(sizeof(CltIdade));
	int i;
	int menosum = -1;	
	int tamanho = contaRegistros_Idade(A4);
	rewind(A4);

	aux_id_prox->idade = -1;

	for(i = 0; i < tamanho; i++){
		fseek(A4, i * (sizeof(CltIdade)), SEEK_SET);
		fseek(A6, i * (sizeof(CltIdade) + sizeof(int)), SEEK_SET);
		aux_id = leCliente_idade(A4);
		aux_id_prox = leCliente_idade(A4);
		if(aux_id_prox == NULL){
			fwrite(aux_id, sizeof(CltIdade), 1, A6);
			fwrite(&menosum, sizeof(int), 1, A6);
			break;
		}else{
			if(aux_id->idade == aux_id_prox->idade){
				fwrite(aux_id, sizeof(CltIdade), 1, A6);
				fwrite(&aux_id_prox->endereco, sizeof(int), 1, A6);
			}else{
				fwrite(aux_id, sizeof(CltIdade), 1, A6);
				fwrite(&menosum, sizeof(int), 1, A6);
			}	
		}
	}

	rewind(A6);
	/*
	for(i = 0; i < tamanho; i++){
		//fseek(A6, i * (sizeof(CltIdade) + sizeof(int)), SEEK_SET);
		imprimirStructA6(A6);
	}
	*/
}

void imprimirStructA6(FILE* A6){
	int next;
	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	aux_id = leCliente_idade(A6);
	imprimeCliente_idade(aux_id);
	fread(&next, sizeof(int), 1, A6);
	printf("prox = %d\n",next);
}

void CriaA7_Idade(FILE* A4, FILE* A6, FILE* A7){
	int i;
	int prox;
	int tamanho = contaRegistros_Idade(A4);
	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	CltIdade** vet_clt = (CltIdade**) malloc(tamanho*(sizeof(CltIdade)));
	int* proximos = (int*) malloc(tamanho * sizeof(int));

	rewind(A6);
	for(i = 0; i < tamanho; i++){
		aux_id = leCliente_idade(A6);
		vet_clt[i] = aux_id;
		fread(&prox, sizeof(int), 1, A6);
		proximos[i] = prox;
	}

	bubble_sort_A7(vet_clt,tamanho,proximos);
	rewind(A6);

	for(i = 0; i < tamanho; i++){
		fwrite(vet_clt[i], sizeof(CltIdade), 1, A7);
		fwrite(&proximos[i], sizeof(int), 1, A7);
	}

	rewind(A7);
}

void bubble_sort_A7 (CltIdade** vetor, int n, int* proximos) {
    int k, j;
    CltIdade* aux;
    int aux_int;
    for (k = n - 1; k > 0; k--) {
      	for (j = 0; j < k; j++) {
        	if (vetor[j]->endereco > vetor[j + 1]->endereco) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                
                aux_int = proximos[j];
                proximos[j] = proximos[j + 1];
                proximos[j + 1] = aux_int;
            }
        }
    }
}

void CriaA8_Idade(FILE* A1, FILE* A7, FILE* A8){
	Cliente* aux_cli = (Cliente*) malloc(sizeof(Cliente));
	CltIdade* aux_id = (CltIdade*) malloc(sizeof(CltIdade));
	Cliente* nulo = (Cliente*) malloc(sizeof(Cliente));
	int tamanho = contaRegistros(A1);
	int i;
	int prox;
	
	int menosum = -1;
	char* n = "";

	rewind(A1);
	rewind(A7);
	for(i = 0; i < tamanho; i++){
		aux_cli = leCliente(A1);
		aux_id = leCliente_idade(A7);
		fread(&prox, sizeof(int), 1, A7);
		fwrite(aux_cli, sizeof(Cliente), 1, A8);
		fwrite(&prox, sizeof(int), 1, A8);
	}
	
	rewind(A8);
	//printf("aqui\n");
	//printf("oi\n");
	imprimeArquivoA8(A8, tamanho);
	//printf("oi\n");
	
}

void imprimeClienteA8(Cliente* e, int next){
	if(e == NULL)
    {
        printf("Cliente nao encontrado!\n");
    }

    
    else if(e->liberado == 1)//liberado == 1 significa liberado
    {
       printf("\n");
       printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Liberado\nProximo Cliente(codigo): %d\nProximo Cliente(idade): %d\n\n", e->codigo, e->nome, e->idade, e->prox+1, next);
    }
	
    else if(e->liberado == -1)//liberado == -1 significa ocupado
    {
    	if(e->prox != -1 && next != -1){
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente(codigo): Cliente %d\nProximo Cliente(idade): Cliente %d\n\n", e->codigo, e->nome, e->idade, e->prox+1, next);
    	}
    	else if(e->prox != -1 && next == -1){
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente(codigo): Cliente %d\nProximo Cliente(idade): %d\n\n", e->codigo, e->nome, e->idade, e->prox+1, next);
    	}
    	else if(e->prox == -1 && next != -1){
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente(codigo): %d\nProximo Cliente(idade): Cliente %d\n\n", e->codigo, e->nome, e->idade, e->prox, next);
    	}
    	else{
    		printf("Codigo: %d\nNome: %s\nIdade: %d\nStatus: Ocupado\nProximo Cliente(codigo): %d\nProximo Cliente(idade): %d\n\n", e->codigo, e->nome, e->idade, e->prox, next);
    	}
        		
    }
}

void imprimeArquivoA8(FILE* A8, int tamanho){
	int i;
	int prox;
	Cliente* aux_cli;

	for(i = 0; i < tamanho; i++){
		//printf("i = %d\n",i );
		aux_cli = leCliente(A8);
		fread(&prox, sizeof(int), 1, A8);
		printf("Cliente %d:\n", i+1);
		imprimeClienteA8(aux_cli, prox);
	}
}

int busca_idade(int idade){

	FILE* A8 = fopen("a8_idade.dat", "r+b");
	FILE* A5 = fopen("a5_idade.dat", "r+b");

	Cliente* tem;
	Cliente* aux_cli;
	CltIdade* aux_id;

	int i;
	int j;
	int prox;

	rewind(A8);
	rewind(A5);

	for(i = 0; !feof(A5); i++){
		aux_id = leCliente_idade(A5);
		if(aux_id == NULL){
			printf("Nenhum registro possui essa idade");
			return 0;
		}
		else if(idade == aux_id->endereco){
			fseek(A8, ((aux_id->codigo)-1) * (sizeof(Cliente)+sizeof(int)), SEEK_SET);

			for(j = 0; j < aux_id->idade; j++){
				tem = leCliente(A8);
				fread(&prox, sizeof(int), 1, A8);
				printf("-----------\n");
				//printf("Cliente %d:\n", aux_id->codigo);
				imprimeClienteA8(tem, prox);
				if(prox != -1){
					fseek(A8, (prox-1) * (sizeof(Cliente)+sizeof(int)), SEEK_SET);
				}
			}
			//printf("-----------\n");
			return 1;
		}
		
	}
	printf("Nenhum registro possui essa idade");
	return 0;
}
