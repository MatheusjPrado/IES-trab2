#include <stdio.h>
#include "controller.h"
#include "model.h"

// Funcao principal do controlador
void executarSistema() {
    int opcao;
    if (!carregarConfig()) {
        printf("Erro ao carregar o arquivo de configuracao.\n");
        return;
    }

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Atendente novoAtendente = lerAtendente();
                if (adicionarAtendente(novoAtendente)) {
                    printf("Atendente incluido com sucesso!\n");
                } else {
                    printf("Erro ao incluir atendente.\n");
                }
                break;
            }
            case 2: {
                int matricula = lerMatricula();
                Atendente atendenteAlterado = alterarAtendenteAux();
                atendenteAlterado.matricula = matricula;  // Mantém a matricula original
                if (alterarAtendente(matricula, atendenteAlterado)) {
                    printf("Atendente alterado com sucesso!\n");
                } else {
                    printf("Erro ao alterar atendente.\n");
                }
                break;
            }
            case 3: {
                int matricula = lerMatricula();
                if (excluirAtendente(matricula)) {
                    printf("Atendente excluido com sucesso!\n");
                } else {
                    printf("Erro ao excluir atendente.\n");
                }
                break;
            }
            case 4:
                consultarAtendentes();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
}
