//
//  main.c
//  AVL
//
//  Created by Narcélio Medeiros on 22/05/15.
//  Copyright (c) 2015 Narcélio Medeiros. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct NO{
	int chave;
	int alt; // altura do no
	struct NO *esq;
	struct NO *dir;
	
};

typedef struct NO* ArvAVL;

int maior (int x, int y);

int alt_NO(ArvAVL no);

int FatBal (ArvAVL no);

void Rot_Simp_dir (ArvAVL *raiz);

void Rot_Simp_esq (ArvAVL *raiz);

void Rot_dupla_direita_met2 (ArvAVL *raiz);

void Rot_dupla_esquerda_met2 (ArvAVL *raiz);

void Rot_dupla_dir (ArvAVL *raiz);

void Rot_dupla_esq (ArvAVL *raiz);

int insere_ArvAVL (ArvAVL *raiz, int chave);

ArvAVL* cria_ArvAVL();

void emOrdem_ArvAVL(ArvAVL *raiz);

int main() {
	// int x = insere_ArvAVL (raiz,valor);
	ArvAVL *arvore;
	
	arvore = cria_ArvAVL();
	
	int chave=1;
	
	while (chave!=0) {
		printf("\nDigite chave a ser inserida (zero para sair) : ");
		scanf("%d",&chave);
		if (chave!=0) {
			insere_ArvAVL(arvore, chave);
		}
		emOrdem_ArvAVL(arvore);
	}
	//emOrdem_ArvAVL(arvore);
	
	
	
	
	
	printf("Hello, World!\n");
    return 0;
}


void emOrdem_ArvAVL(ArvAVL *raiz){
	if(raiz == NULL)
		return;
	if(*raiz != NULL){
		emOrdem_ArvAVL(&((*raiz)->esq));
		printf("%d ",(*raiz)->chave);
		emOrdem_ArvAVL(&((*raiz)->dir));
	}
}

int maior (int x, int y){
	if(x>y)
		return x;
	else
		return y;
}
int alt_NO(ArvAVL no){
	if (no == NULL)
		return -1;
	else
		return no->alt;
}
int FatBal (ArvAVL no){
	return (alt_NO(no->dir) - alt_NO(no->esq)); //vou retornar o valor da altura da sub arvore da direita menos a da esquerda
}

void Rot_Simp_dir (ArvAVL *raiz){ // rotacao simples a direita: quer dizer que o no inserido ficou a esquerda da subarvore da esquerda, ocasionando um fatbal -2. o ponteiro de ponteiro recebido como raiz é deste nó com fatbal -2.
	ArvAVL no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = (*raiz);
	
	(*raiz)->alt = maior (alt_NO((*raiz)->esq),alt_NO((*raiz)->dir)) +1;
	no->alt = maior(alt_NO(no->esq), alt_NO(no->dir))+1;  // alteracao das alturas, sempre sera isso. pego a maior altura entre os dois filhos e acrescento um. faco recursivamente ate a folha que eh 0.
	
	*raiz = no; // se faz necessaria a troca pois estamos usando uma referencia e, portanto, temos que definir a nova raiz.
	
}

void Rot_Simp_esq (ArvAVL *raiz){  // rotacao simples a esquerda: quer dizer que o no inserido ficou a direida da subarvore da direita, ocasionando um fatbal +2. O ponteiro de ponteiro recebido como raiz é deste nó com fatbal +2.
	ArvAVL no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = (*raiz);
	
	(*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir))+1;
	no->alt = maior(alt_NO(no->dir), alt_NO(no->esq))+1;
	
	*raiz = no;
}

void Rot_dupla_direita_met2 (ArvAVL *raiz){  // metodo mais simplorio, baseado na compreensao nao ministrada em aula de que a rotacao dupla a direita eh a rotacao simples a esquerda do no esquerdo da raiz e após isso a rotacao simples a direita da raiz
 
	Rot_Simp_esq(&(*raiz)->esq);  // interessante - endereçamento do no esq da raiz, dereferenciamento do referenciamento ( nao eh possivel acessar o no da esquerda simplesmente fazendo "raiz->esq" pois trata-se de um ponteiro de ponteiro.
	
	Rot_Simp_dir(&(*raiz)); // == Rot_Simp_dir (raiz);
	// fazer uma rotacao simples a direita
}

void Rot_dupla_esquerda_met2 (ArvAVL *raiz){  // metodo mais simplorio, baseado na compreensao nao ministrada em aula de que a rotacao dupla a esquerda eh a rotacao simples a direita do no direito da raiz e após isso a rotacao simples a esquerda da raiz
 
	Rot_Simp_dir(&(*raiz)->dir);  // interessante - endereçamento do no dir da raiz
	Rot_Simp_esq(&(*raiz)); // fazer uma rotacao simples
}

void Rot_dupla_dir (ArvAVL *raiz){ // metodo explicado em aula, onde a rotacao dupla a direita sera tratada com trocas de ponteiros e o ajuste braçal da arvore, neste caso a raiz da sub-arvore da direita do filho da esquerda se tornara a raiz da subarvore principal tratada.
	ArvAVL no1;
	ArvAVL no2;
	no1 = (* raiz)-> esq;
	no2 = (* raiz)-> esq -> dir; // dupla rot para direita, no2 está na sub arvore da direita do filho da esquerda e se tornará a nova raiz desta subarvore
	
	no1->dir = no2->esq;
	(*raiz)->esq = no2->dir;
	no2->esq = no1;
	no2->dir = (* raiz);
	
	(*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir))+1;
	no1->alt = maior(alt_NO(no1->dir), alt_NO(no1->esq))+1;
	no2->alt = maior(alt_NO(no2->dir), alt_NO(no2->esq))+1;
	
	(*raiz) = no2;
	
}

void Rot_dupla_esq (ArvAVL *raiz){ // metodo explicado em aula, onde a rotacao dupla a esquerda sera tratada com trocas de ponteiros e o ajuste braçal da arvore, neste caso a raiz da sub-arvore da direita do filho da esquerda se tornara a raiz da subarvore principal tratada.
	ArvAVL no1;
	ArvAVL no2;
	no1 = (* raiz)-> dir;
	no2 = (* raiz)-> dir -> esq; // dupla rot para esq, no2 está na sub arvore da esquerda do filho da direita e se tornará a nova raiz desta subarvore
	
	no1->esq = no2->dir;
	(*raiz)->dir = no2->esq;
	
	no2->dir = no1;
	no2->esq = (* raiz);
	
	(*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir))+1;
	no1->alt = maior(alt_NO(no1->dir), alt_NO(no1->esq))+1;
	no2->alt = maior(alt_NO(no2->dir), alt_NO(no2->esq))+1;
	
	(*raiz) = no2;
	
}



int insere_ArvAVL (ArvAVL *raiz, int chave){
	int res;
	if(*raiz == NULL){ // arvore vazia ou no folha
		ArvAVL novo;
		novo = (ArvAVL)malloc(sizeof(ArvAVL));
		if(novo == NULL)
			return 0;
		
		novo->chave = chave;
		novo->alt = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return 1;
	}
	
	ArvAVL atual = *raiz;
	if(chave < atual->chave){  // inserção na sub arvore da esquerda
		if((res = insere_ArvAVL(&(atual->esq), chave)) == 1){
			atual->alt = maior(alt_NO(atual->esq),alt_NO(atual->dir)) + 1;
			if(FatBal(atual) <= -2){
				if(chave < (*raiz)->esq->chave ){
					Rot_Simp_dir(raiz);
				}else{
					Rot_dupla_direita_met2(raiz);
				}
			}
		}
	}
	
	else{
	
		if(chave > atual->chave){
			if((res = insere_ArvAVL(&(atual->dir), chave)) == 1){
				atual->alt = maior(alt_NO(atual->esq),alt_NO(atual->dir)) + 1;
				if(FatBal(atual) >= 2){
					if((*raiz)->dir->chave < chave){
						Rot_Simp_esq(raiz);
					}else{
						Rot_dupla_esquerda_met2(raiz);
					}
				}
			}
		}
		
		else{
			printf("Valor duplicado!!\n");
			return 0;
		}
	}
	
	return res;
}
/*
int remove_ArvAVL(ArvAVL *raiz, int chave){
	if(*raiz == NULL){// arvore vazia ou valor nao existe!!!
		printf("Chave não existe!!\n");
		return 0;
	}
	
	int res;
	if(chave < (*raiz)->chave){
		if((res = remove_ArvAVL(&(*raiz)->esq,chave)) == 1){ // foi possivel remover  logo é necessario a remocao da arvore da direita.
			if(FatBal(*raiz) >= 2){
				if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
					RotacaoRR(raiz);
				else
					RotacaoRL(raiz);
			}
		}
	}
	
	if((*raiz)->chave < chave){
		if((res = remove_ArvAVL(&(*raiz)->dir, chave)) == 1){
			if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
	}
	
	if((*raiz)->chave == chave){
		if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nÛ tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
				*raiz = (*raiz)->esq;
			else
				*raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nÛ tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->chave = temp->chave;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->chave);
			if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		return 1;
	}
	return res;
}*/

ArvAVL* cria_ArvAVL(){
	ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
	if(raiz != NULL)
		*raiz = NULL;
	return raiz;
}











