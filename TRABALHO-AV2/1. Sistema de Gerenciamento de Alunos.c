/* 1. Sistema de Gerenciamento de Alunos

Crie um programa que gerencie informações sobre alunos de uma escola. As informações devem ser
armazenadas em um arquivo e cada registro deve conter:
• Campos da struct:
o int matricula: Número de matrícula do aluno.
o char nome[50]: Nome do aluno.
o char curso[30]: Nome do curso que o aluno está matriculado.
o int idade: Idade do aluno.
• Funcionalidades do programa:
1. Incluir um novo aluno.
2. Alterar informações de um aluno (nome, curso ou idade).
3. Excluir um aluno pelo número de matrícula.
4. Consultar informações de um aluno.
5. Listar todos os alunos cadastrados. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100

typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;

Aluno alunos[MAX_ALUNOS];
int total_alunos = 0;

void salvarDados() {
    FILE *file = fopen("alunos.dat", "wb");
    if (file != NULL) {
        fwrite(alunos, sizeof(Aluno), total_alunos, file);
        fclose(file);
    }
}

void carregarDados() {
    FILE *file = fopen("alunos.dat", "rb");
    if (file != NULL) {
        total_alunos = fread(alunos, sizeof(Aluno), MAX_ALUNOS, file);
        fclose(file);
    }
}

void incluirAluno() {
    if (total_alunos >= MAX_ALUNOS) {
        printf("Não é possível adicionar mais alunos.\n");
        return;
    }
    Aluno novo;
    printf("Número de matrícula: ");
    scanf("%d", &novo.matricula);
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Curso: ");
    scanf(" %[^\n]", novo.curso);
    printf("Idade: ");
    scanf("%d", &novo.idade);
    alunos[total_alunos++] = novo;
    salvarDados();
    printf("Aluno adicionado com sucesso!\n");
}

void alterarAluno() {
    int matricula;
    printf("Número de matrícula do aluno a alterar: ");
    scanf("%d", &matricula);
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("Novo nome: ");
            scanf(" %[^\n]", alunos[i].nome);
            printf("Novo curso: ");
            scanf(" %[^\n]", alunos[i].curso);
            printf("Nova idade: ");
            scanf("%d", &alunos[i].idade);
            salvarDados();
            printf("Informações alteradas com sucesso!\n");
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void excluirAluno() {
    int matricula;
    printf("Número de matrícula do aluno a excluir: ");
    scanf("%d", &matricula);
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            for (int j = i; j < total_alunos - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            total_alunos--;
            salvarDados();
            printf("Aluno excluído com sucesso!\n");
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void consultarAluno() {
    int matricula;
    printf("Número de matrícula do aluno a consultar: ");
    scanf("%d", &matricula);
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("Nome: %s\n", alunos[i].nome);
            printf("Curso: %s\n", alunos[i].curso);
            printf("Idade: %d\n", alunos[i].idade);
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

void listarAlunos() {
    for (int i = 0; i < total_alunos; i++) {
        printf("Matrícula: %d\n", alunos[i].matricula);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Curso: %s\n", alunos[i].curso);
        printf("Idade: %d\n", alunos[i].idade);
        printf("--------------------\n");
    }
}

int main() {
    carregarDados();
    int opcao;
    do {
        printf("\n1. Incluir aluno\n");
        printf("2. Alterar aluno\n");
        printf("3. Excluir aluno\n");
        printf("4. Consultar aluno\n");
        printf("5. Listar alunos\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: incluirAluno(); break;
            case 2: alterarAluno(); break;
            case 3: excluirAluno(); break;
            case 4: consultarAluno(); break;
            case 5: listarAlunos(); break;
            case 6: salvarDados(); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 6);
    
    return 0;
}
