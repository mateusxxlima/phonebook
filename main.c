/*
 Este é um esqueleto que deve ser utilzado como base para implementação da Agenda.
	- As funções não tem os parâmetros definidos e os parâmetros caso necessários, devem ser incluídos.
    - Caso seja necessário novas funções podem ser incluídas
 	- Devem ser respeitados os nomes dados para o métodos e estruturas, porém novas estruturas e funções podem ser criados, caso julgue necessário
	- Faça os includes necessários
	- A organização das funções fica a critério do programador
	- Códigos não identados sofrerão duras penalidades
	- Não serão toleradas variaveis globais
	- Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/

#include <stdio.h> 


#define EXIT 10  // valor fixo para a opção que finaliza a aplicação


// Estrutura que contém os campos dos registros da agenda
struct MREC {
       char name[30];
       char email[40];
       char phone[15];
	   struct MREC *next; // implemente como lista, como árvore BST, AVL...
	   struct MREC *prev;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu() {
    int op=0;
    while (op!=EXIT) {
        printf("%d Finaliza",EXIT);
        printf("\n: ");
        scanf("%d",&op);       
    }
    return op;
}

// Permite o cadastro de um contato
void insContact() {
     return;
}

// Permite excluir um contato da agenda
void delContact () {
     return;
}

// Lista o conteudo da agenda (todos os campos)
void listContacts () {
     return;
}

// Permite consultar um contato da agenda por nome
void queryContact () {
     return;
}


// Programa principal
int main() {
    int op=0;
    Contact MContact;

    while (op!=EXIT) {
        op=menu();
        switch(op) {
            case 1 : insContact();
            case 2 : delContact();
            case 3 : queryContact();
            case 4 : listContacts();
        }
    }
    return 0;
}
