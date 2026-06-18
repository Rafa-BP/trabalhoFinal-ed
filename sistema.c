#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TADs principais

typedef struct user {
	char nome[30];
	char email[50];
} Usuario; 

typedef struct livr {
	int id;
	char titulo[30];
	char autor[30];
	int anoPubli;
	int status;
	char email[50];
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

// TAD lista simples (Para a busca por autor)

typedef struct nodo {
	Livro *valor;
	struct nodo *next;
} NodeLista;

void printaLista(NodeLista *f) {
	NodeLista *aux = f;
	while (aux != NULL) {
		char* status = "Emprestado";
		if (aux->valor->status == 0) {
			status = "Disponivel";
		}
		printf("\nTitulo: %s\nAutor: %s\nAno de Publicação: %d\nStatus: %s\nEmail: %s\n\n", aux->valor->titulo, aux->valor->autor, aux->valor->anoPubli, status, aux->valor->email);
		aux = aux->next;
	}
}

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
		if (raiz->valor->id <= novo->valor->id) raiz->right = adicionaLivro(raiz->right, novo); 
		else raiz->left = adicionaLivro(raiz->left, novo);
	}
	return raiz;
}

 NodeLivro *achaLivro(NodeLivro *raiz, int id) {
	if (raiz == NULL || raiz->valor->id == id) {
		return raiz;
	}
	if (raiz->valor->id < id) return achaLivro(raiz->right, id);
	else return achaLivro(raiz->left, id);
	return raiz;
}

NodeLista *achaLivroAutor(NodeLivro *raiz, char *autor, NodeLista *first) {
	if (raiz == NULL) return first;
	first = achaLivroAutor(raiz->left, autor, first);
	if (strcmp(raiz->valor->autor, autor) == 0) {
		NodeLista *novo = (NodeLista *)malloc(sizeof(NodeLista));
		novo->valor = raiz->valor;
		novo->next = NULL;
		if (first == NULL) {
			first = novo;
		} else {
			NodeLista *aux = NULL;
			// Percorre lista ate achar o ultimo nodo
			for (aux=first;aux->next!=NULL;aux=aux->next);
			aux->next = novo;
		}
	}
	first = achaLivroAutor(raiz->right, autor, first);
	return first;
}

NodeLista *achaLivroEmail(NodeLivro *raiz, char *email, NodeLista *first) {
	if (raiz == NULL) return first;
	first = achaLivroAutor(raiz->left, email, first);
	if (strcmp(raiz->valor->email, email) == 0) {
		NodeLista *novo = (NodeLista *)malloc(sizeof(NodeLista));
		novo->valor = raiz->valor;
		novo->next = NULL;
		if (first == NULL) {
			first = novo;
		} else {
			NodeLista *aux = NULL;
			// Percorre lista ate achar o ultimo nodo
			for (aux=first;aux->next!=NULL;aux=aux->next);
			aux->next = novo;
		}
	}
	first = achaLivroAutor(raiz->right, email, first);
	return first;
}

void trocaLivro(NodeLivro *raiz, Livro *livro) {
	if (raiz == NULL) {
		printf("\nLivro não encontrado.\n");
		return;
	}
	if (raiz->valor->id == livro->id) {
		Livro *aux = raiz->valor;
		raiz->valor = livro;
		free(aux);
		return;
	}
	if (raiz->valor->id < livro->id) trocaLivro(raiz->right, livro);
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

// Funções da biblioteca 

void cadastro(Arvore *arvore) {
	int seletor = 1;

	while (seletor != 0) {
		// Comando para limpar console
		system("clear");
		printf("Selecione uma das seguintes opções: \n1. Livros \n2. Usuarios \n0.Sair \n\nDigite sua escolha: ");
		scanf("%d", &seletor);	
		
		switch(seletor) {
			case 1:
				// Comando para limpar console
				system("clear");
				
				// Livro
				printf("Digite as informações para o livro: \n");
				
				Livro *novoL = (Livro *)malloc(sizeof(Livro));
				
				int id = 1;
				printf("Numero de identificação: ");
				scanf("%d", &id);
				while (achaLivro(arvore->raizLivro, id) != NULL) {
					printf("Numero de identificação já existente, favor digitar outro numero: ");
					scanf("%d", &id);
				}
				novoL->id = id;
				
				char titulo[30];
				printf("Titulo: ");
				scanf("%s", titulo);
				strcpy(novoL->titulo, titulo);
				
				char autor[30];
				printf("Autor: ");
				scanf("%s", autor);
				strcpy(novoL->autor, autor);
				
				int anoPubli = 0;
				printf("Ano de publicação: ");
				scanf("%d", &anoPubli);
				novoL->anoPubli = anoPubli;
				
				novoL->status = 0;
				
				arvore->raizLivro = adicionaLivro(arvore->raizLivro, iniciaNodeLivro(novoL));
				
				break;
			case 2:
				// Comando para limpar console
				system("clear");
				
				// Usuario
				
				// Livro
				printf("Digite as informações para o usuario: \n");
				
				Usuario *novoU = (Usuario *)malloc(sizeof(Usuario));
				 
				char nome[30];
				printf("Nome: ");
				scanf("%s", nome);
				strcpy(novoU->nome, nome);
				
				char email[50];
				printf("Email: ");
				scanf("%s", email);
				strcpy(novoU->email, email);
				
				arvore->raizUsuario = adicionaUsuario(arvore->raizUsuario, iniciaNodeUsuario(novoU));
				break;
		}	
	}
}

void consulta(Arvore *arvore) {
	int seletor = 1;

	while (seletor != 0) {
		// Comando para limpar console
		system("clear");
		printf("Selecione uma das seguintes opções: \n1. Livros \n2. Usuarios \n3. Emprestimos \n0. Sair \n\nDigite sua escolha: ");
		scanf("%d", &seletor);	
		
		switch(seletor) {
			case 1:
				// Comando para limpar console
				system("clear");
				
				// Livro
				int seletorLivro = 1;
				
				while (seletorLivro != 0) {
					printf("Gostaria de consultar o livro por: \n1. Código \n2. Autor \n0. Sair\n\nDigite sua escolha: ");
					scanf("%d", &seletorLivro);	
					switch(seletorLivro) {
						case 1:
							// Código
							int idProcura;
							printf("Digite o Id do livro que gostaria de procurar: ");
							scanf("%d", &idProcura);
							
							NodeLivro *livro = achaLivro(arvore->raizLivro, idProcura);
							
							if (livro != NULL) {
								char* status = "Emprestado";
								if (livro->valor->status == 0) {
									status = "Disponivel";
								}
								printf("Livro encontrado! \nTitulo: %s\nAutor: %s\nAno de Publicação: %d\nStatus: %s\nEmail: %s\n\n", livro->valor->titulo, livro->valor->autor, livro->valor->anoPubli, status, livro->valor->email);
							} else {
								printf("Livro não encontrado para este id.\n\n");
							}
							
							break;
						case 2:
							char autor[30];
							printf("Digite o autor dos livros que gostaria de procurar: ");
							scanf("%s", autor);
							
							NodeLista *lista = achaLivroAutor(arvore->raizLivro, autor, NULL);
							
							if (lista != NULL) {
								printf("Livros encontrados:\n");
								printaLista(lista);
							} else {
								printf("Nenhum livro encontrado para este autor.\n\n");
							}
							break;
					}
				}
				
				break;
			case 2:
				// Comando para limpar console
				system("clear");
			
				// Usuario
				int seletorUsuario = 1;
				
				while (seletorUsuario != 0) {
					printf("Gostaria de consultar os usuarios por: \n1. Nome \n2. Email \n0. Sair\n\nDigite sua escolha: ");
					scanf("%d", &seletorUsuario);	
					switch(seletorUsuario) {
						case 1:
							// Nome
							char nome[30];
							printf("Digite o nome do usuario que gostaria de consultar: ");
							scanf("%s", nome);
							
							NodeUsuario *usuarioN = achaUsuarioNome(arvore->raizUsuario, nome);
							
							if (usuarioN != NULL) {
								printf("Usuario encontrado! \nNome: %s\nEmail: %s\n\n", usuarioN->valor->nome, usuarioN->valor->email);
							} else {
								printf("Usuario não cadastrado neste nome.\n\n");
							}
							
							break;
						case 2:
							// Email
							char email[50];
							printf("Digite o email do usuario que gostaria de consultar: ");
							scanf("%s", email);
							
							NodeUsuario *usuarioE = achaUsuarioEmail(arvore->raizUsuario, email);
							
							if (usuarioE != NULL) {
								printf("Usuario encontrado! \nNome: %s\nEmail: %s\n\n", usuarioE->valor->nome, usuarioE->valor->email);
							} else {
								printf("Usuario não cadastrado neste email.\n\n");
							}
					}
				}
				break;
			case 3:
				// Comando para limpar console
				system("clear");
			
				// Emprestimo
				char email[50];
				printf("Digite o email do usuario que deseja ver os livros emprestados ao mesmo: ");
				scanf("%s", email);

				NodeLista *lista = achaLivroEmail(arvore->raizLivro, email, NULL);
							
				if (lista != NULL) {
					printf("Livros encontrados:\n");
					printaLista(lista);
				} else {
					printf("Nenhum livro emprestado a este usuario.\n\n");
				}
				break;
		}	
	}
}

void atualiza(Arvore *arvore) {
	int seletor = 1;
	
	while (seletor != 0) {
		// Comando para limpar console
		system("clear");
		
		printf("Selecione uma das seguintes opções: \n1. Livros \n2. Usuarios \n0. Sair \n\nDigite sua escolha: ");
		scanf("%d", &seletor);
		switch(seletor) {
			case 1:
				// Comando para limpar console
				system("clear");
					
				int seletorLivro = 1;
				
				while (seletorLivro != 0) {
					printf("O'que gostaria de atualizar? \n1. Titulo \n2. Autor \n3. Ano \n0. Sair \n\nDigite sua escolha: ");
					scanf("%d", &seletorLivro);
					
					int id = 0;
					printf("Digite o Id do livro que gostaria de atualizar: ");
					scanf("%d", &id);
					
					NodeLivro *livro = achaLivro(arvore->raizLivro, id);
					
					if (livro == NULL) {
						printf("Livro não encontrado.\n\n");
						break;
					}
					
					switch(seletorLivro) {
						case 1:
							char titulo[30];
							printf("Digite o novo titulo: ");
							scanf("%s", titulo);
							strcpy(livro->valor->titulo, titulo);
							break;
						case 2:
							char autor[30];
							printf("Digite o novo autor: ");
							scanf("%s", autor);
							strcpy(livro->valor->autor, autor);
							break;
						case 3:
							int anoPubli;
							printf("Digite o novo ano de publicação: ");
							scanf("%d", &anoPubli);
							livro->valor->anoPubli = anoPubli;				
							break;
					}
					trocaLivro(arvore->raizLivro, livro->valor);
				}
				break;
			case 2:
				char email[50];
				printf("Digite o email do usuario que gostaria de alterar: ");
				scanf("%s", email);
				
				NodeUsuario *usuario = achaUsuarioEmail(arvore->raizUsuario, email);
				
				if (usuario == NULL) {
					printf("Usuario não encontrado.\n\n");
					break;
				}
				
				char nome[30];
				printf("Digite o novo nome do usuario: ");
				scanf("%s", nome);
				strcpy(usuario->valor->nome, nome);
				
				trocaUsuario(arvore->raizUsuario, usuario->valor);
				
				break;
		}
	}
}

// Main

int main(void)
{
	Arvore *arvore = iniciaArvore();
	
	int seletor = 1;
	
	while (seletor != 0) {
		// Comando para limpar console
		system("clear");
		printf("Selecione uma das seguintes opções: \n1. Cadastro \n2. Consulta \n3. Atualização \n4. Exclusão \n5. Emprestimo \n6. Devolução \n0. Sair \n\nDigite sua escolha: ");
		scanf("%d", &seletor);
		
		switch(seletor) {
			case 1:
				cadastro(arvore);
				break;
			case 2:
				consulta(arvore);
				break;
			case 3:
				atualiza(arvore);
				break;
			case 4:
				
				break;
			case 5:
				
				break;
			case 6:
				
				break;
		}
	}
	
	system("clear");
	
	return 0;
}

