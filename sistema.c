#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TADs principais

typedef struct user {
	char *nome;
	char *email;
} Usuario; 

typedef struct livr {
	int id;
	char *titulo;
	char *autor;
	int dataPub;
	int status;
	char *email;
} Livro; 

// TADs para Estrutura de Dados

typedef struct nodol {
	Livro *valor;
	struct nodol *right, *left;
} NodeLivro; 

typedef struct nodou {
	Usuario *valor;
	struct nodou *right, *left;
} NodeUsuario;

typedef struct tree {
	NodeLivro *raizLivro;
	NodeUsuario *raizUsuario;
} Arvore;

// Funções gerais para a Arvore

Arvore *iniciaArvore(void) {
	Arvore *novo = (Arvore *)malloc(sizeof(Arvore));
	novo->raizLivro = NULL;
	novo->raizUsuario = NULL;
	return novo;
}

// Funções para Arvore de Livros

NodeLivro *iniciaNodeLivro(Livro *livro) {
	NodeLivro *novo = (NodeLivro *)malloc(sizeof(NodeLivro));
	novo->valor = livro;
	novo->right = NULL;
	novo->left = NULL;
	return novo;
}

NodeLivro *adicionaLivro(NodeLivro *raiz, NodeLivro *novo) {
	if (raiz == NULL) {
		return novo;
	} else {
		if (raiz->valor->id >= novo->valor->id) raiz->right = adicionaLivro(raiz->right, novo); 
		else raiz->left = adicionaLivro(raiz->left, novo);
	}
	return raiz;
}

NodeLivro *achaLivro(NodeLivro *raiz, int id) {
	if (raiz == NULL || raiz->valor->id == id) {
		return raiz;
	}
	if (raiz->valor->id > id) return achaLivro(raiz->right, id);
	else return achaLivro(raiz->left, id);
	return raiz;
}

void trocaLivro(NodeLivro *raiz, Livro *livro) {
	if (raiz == NULL) {
		printf("\nLivro não encontrado.");
		return;
	}
	if (raiz->valor->id == livro->id) {
		raiz->valor = livro;
	}
	if (raiz->valor->id > livro->id) trocaLivro(raiz->right, livro);
	else trocaLivro(raiz->left, livro);
}

// Funções para Arvore de Usuarios

NodeUsuario *iniciaNodeUsuario(Usuario *usuario) {
	NodeUsuario *novo = (NodeUsuario *)malloc(sizeof(NodeUsuario));
	novo->valor = usuario;
	novo->right = NULL;
	novo->left = NULL;
	return novo;
}

NodeUsuario *adicionaUsuario(NodeUsuario *raiz, NodeUsuario *novo) {
	if (raiz == NULL) {
		return novo;
	} else {
		if (strcmp(raiz->valor->nome, novo->valor->nome) >= 0) raiz->right = adicionaUsuario(raiz->right, novo); 
		else raiz->left = adicionaUsuario(raiz->left, novo);
	}
	return raiz;
}

NodeUsuario *achaUsuarioNome(NodeUsuario *raiz, char* nome) {
	if (raiz == NULL || strcmp(raiz->valor->nome, nome) == 0) {
		return raiz;
	}
	if (strcmp(raiz->valor->nome, nome) >= 0) return achaUsuarioNome(raiz->right, nome);
	else return achaUsuarioNome(raiz->left, nome);
	return raiz;
}

NodeUsuario *achaUsuarioEmail(NodeUsuario *raiz, char* email) {
	if (raiz == NULL || strcmp(raiz->valor->email, email) == 0) {
		return raiz;
	}
	if (strcmp(raiz->valor->email, email) >= 0) return achaUsuarioEmail(raiz->right, email);
	else return achaUsuarioEmail(raiz->left, email);
	return raiz;
}

void trocaUsuario(NodeUsuario *raiz, Usuario *usuario) {
	if (raiz == NULL) {
		printf("\nUsuario não encontrado.");
		return;
	}
	if (strcmp(raiz->valor->email, usuario->email) == 0) {
		raiz->valor = usuario;
	}
	if (strcmp(raiz->valor->email, usuario->email) >= 0) trocaUsuario(raiz->right, usuario);
	else trocaUsuario(raiz->left, usuario);
}

// Main

int main(void)
{
	Arvore *arvore = iniciaArvore();
	
	Livro *livro = (Livro *)malloc(sizeof(Livro));
	livro->id = 1;
	
	NodeLivro *novo = iniciaNodeLivro(livro);
	
	arvore->raizLivro = adicionaLivro(arvore->raizLivro, novo);
	
	printf("%p\n",achaLivro(arvore->raizLivro, 1));
	
	return 0;
}

