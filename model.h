#ifndef MODEL_H
#define MODEL_H

// Definição da estrutura do atendente
typedef struct {
    int matricula;
    char nome[50];
    char login[6]; // 5 caracteres + 1 para o '\0'
    char senha[6]; // 5 caracteres + 1 para o '\0'
} Atendente;

// Funções do modelo
int carregarConfig();
int adicionarAtendente(Atendente novoAtendente);
int alterarAtendente(int matricula, Atendente atendenteAlterado);
int excluirAtendente(int matricula);
void consultarAtendentes();
Atendente lerAtendente();
Atendente alterarAtendenteAux();

#endif
