#include <stdio.h>
#include "view.h"

// Funcao para mostrar o menu principal
void mostrarMenu() {
    printf("\nMenu do Sistema de Cadastro de Atendentes:\n");
    printf("1. Incluir Atendente\n");
    printf("2. Alterar Atendente\n");
    printf("3. Excluir Atendente\n");
    printf("4. Consultar Atendentes\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}


// Funcao para ler a matricula de um atendente (para alteracoes e exclusoes)
int lerMatricula() {
    int matricula;
    printf("Informe a matricula do atendente: ");
    scanf("%d", &matricula);
    return matricula;
}
