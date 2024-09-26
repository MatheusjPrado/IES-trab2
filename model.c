#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

// Variável global para armazenar o nome do arquivo de atendentes
char nomeArquivo[50];

// Funcao para carregar o nome do arquivo a partir do config.txt
int carregarConfig() {
    FILE *config = fopen("conf.properties", "r");
    if (config == NULL) {
        printf("Erro ao abrir o arquivo de configuracao.\n");
        return 0;
    }
    
    char linha[100];
    while (fgets(linha, sizeof(linha), config) != NULL) {
        if (sscanf(linha, "nome_arquivo=%s", nomeArquivo) == 1) {
            fclose(config);
            return 1;
        }
    }

    fclose(config);
    return 0;
}


// Funcao para ler os dados de um atendente do usuário
Atendente alterarAtendenteAux() {
    Atendente novoAtendente;
    printf("Informe o nome: ");
    scanf("%s", novoAtendente.nome);
    printf("Informe o login (5 caracteres): ");
    scanf("%s", novoAtendente.login);
    printf("Informe a senha (5 caracteres): ");
    scanf("%s", novoAtendente.senha);
    return novoAtendente;
}

// Funcao para ler os dados de um atendente do usuário
Atendente lerAtendente() {
    Atendente novoAtendente;
    printf("Informe a matricula (5 digitos): ");
    scanf("%d", &novoAtendente.matricula);
    printf("Informe o nome: ");
    scanf("%s", novoAtendente.nome);
    printf("Informe o login (5 caracteres): ");
    scanf("%s", novoAtendente.login);
    printf("Informe a senha (5 caracteres): ");
    scanf("%s", novoAtendente.senha);
    return novoAtendente;
}

// Funcao para adicionar um novo atendente
int adicionarAtendente(Atendente novoAtendente) {
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de atendentes.\n");
        return 0;
    }

    fprintf(arquivo, "%d %s %s %s\n", novoAtendente.matricula, novoAtendente.nome, novoAtendente.login, novoAtendente.senha);
    fclose(arquivo);
    return 1;
}

// Funcao para consultar todos os atendentes
void consultarAtendentes() {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de atendentes.\n");
        return;
    }

    Atendente atendente;
    printf("Matricula\tNome\t\tLogin\t\tSenha\n");
    printf("----------------------------------------------------\n");
    while (fscanf(arquivo, "%d %49s %5s %5s", &atendente.matricula, atendente.nome, atendente.login, atendente.senha) != EOF) {
        printf("%d\t\t%s\t\t%s\t\t%s\n", atendente.matricula, atendente.nome, atendente.login, atendente.senha);
    }

    fclose(arquivo);
}

// Funcao para alterar os dados de um atendente existente
int alterarAtendente(int matricula, Atendente atendenteAlterado) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de atendentes.\n");
        return 0;
    }

    // Vetor temporário para armazenar todos os atendentes
    Atendente listaAtendentes[100];
    int totalAtendentes = 0;
    Atendente temp;

    // Ler os atendentes existentes no arquivo
    while (fscanf(arquivo, "%d %49s %5s %5s", &temp.matricula, temp.nome, temp.login, temp.senha) != EOF) {
        listaAtendentes[totalAtendentes++] = temp;
    }
    fclose(arquivo);

    // Buscar o atendente pelo número de matricula e atualizar
    int encontrado = 0;
    for (int i = 0; i < totalAtendentes; i++) {
        if (listaAtendentes[i].matricula == matricula) {
            listaAtendentes[i] = atendenteAlterado;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Atendente com matricula %d nao encontrado.\n", matricula);
        return 0;
    }

    // Reescrever o arquivo com os dados atualizados
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 0;
    }

    for (int i = 0; i < totalAtendentes; i++) {
        fprintf(arquivo, "%d %s %s %s\n", listaAtendentes[i].matricula, listaAtendentes[i].nome, listaAtendentes[i].login, listaAtendentes[i].senha);
    }
    fclose(arquivo);

    return 1;
}

// Funcao para excluir um atendente com base na matricula
int excluirAtendente(int matricula) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de atendentes.\n");
        return 0;
    }

    // Vetor temporário para armazenar todos os atendentes
    Atendente listaAtendentes[100];
    int totalAtendentes = 0;
    Atendente temp;

    // Ler os atendentes existentes no arquivo
    while (fscanf(arquivo, "%d %49s %5s %5s", &temp.matricula, temp.nome, temp.login, temp.senha) != EOF) {
        listaAtendentes[totalAtendentes++] = temp;
    }
    fclose(arquivo);

    // Remover o atendente com a matricula fornecida
    int encontrado = 0;
    int indiceRemover = -1;
    for (int i = 0; i < totalAtendentes; i++) {
        if (listaAtendentes[i].matricula == matricula) {
            encontrado = 1;
            indiceRemover = i;
            break;
        }
    }

    if (!encontrado) {
        printf("Atendente com matricula %d nao encontrado.\n", matricula);
        return 0;
    }

    // Remover o atendente do vetor
    for (int i = indiceRemover; i < totalAtendentes - 1; i++) {
        listaAtendentes[i] = listaAtendentes[i + 1];
    }
    totalAtendentes--;

    // Reescrever o arquivo com os dados atualizados
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 0;
    }

    for (int i = 0; i < totalAtendentes; i++) {
        fprintf(arquivo, "%d %s %s %s\n", listaAtendentes[i].matricula, listaAtendentes[i].nome, listaAtendentes[i].login, listaAtendentes[i].senha);
    }
    fclose(arquivo);

    return 1;
}