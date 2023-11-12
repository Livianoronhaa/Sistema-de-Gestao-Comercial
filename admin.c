#include <stdio.h>
#include <string.h>
#include "sgc.h"

#define MAX_PRODUTOS 100
#define MAX_USUARIOS 50


void excluirUsuario(Usuario *usuarios, int *num_usuarios) {
    if (*num_usuarios > 0) {
        char nomeUsuario[MAX_NOME];
        int encontrado = 0;

        printf("Digite o nome do usuário a ser removido: ");
        scanf("%s", nomeUsuario);

        // Procurar o usuário no array
        for (int i = 0; i < *num_usuarios; i++) {
            if (strcmp(usuarios[i].nome, nomeUsuario) == 0) {
                // Remover o usuário encontrado
                for (int j = i; j < (*num_usuarios - 1); j++) {
                    strcpy(usuarios[j].nome, usuarios[j + 1].nome);
                    strcpy(usuarios[j].senha, usuarios[j + 1].senha);
                    usuarios[j].nivel_privilegio = usuarios[j + 1].nivel_privilegio;
                }
                (*num_usuarios)--;
                printf("Usuário removido com sucesso!\n");
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Usuário não encontrado.\n");
        }
    } else {
        printf("Nenhum usuário registrado. Não é possível remover usuários.\n");
    }

    atualizarArquivoUsuarios(usuarios, *num_usuarios);
}


void adicionarProduto(Produto *estoque, int *num_produtos) {
    FILE *arquivo = fopen("estoque.txt", "a"); 

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo estoque.txt\n");
        return;
    }

    if (*num_produtos < MAX_PRODUTOS) {
        printf("Digite o nome do novo produto: ");
        scanf("%s", estoque[*num_produtos].nome);

        printf("Digite o preço do novo produto: ");
        scanf("%f", &estoque[*num_produtos].preco);

        printf("Digite a quantidade disponível do novo produto: ");
        scanf("%d", &estoque[*num_produtos].quantidade);

        fprintf(arquivo, "%s %.2f %d\n", estoque[*num_produtos].nome, estoque[*num_produtos].preco, estoque[*num_produtos].quantidade);

        (*num_produtos)++;
    }

    fclose(arquivo);
}

void exibirProdutos(Produto *estoque, int num_produtos) {
    if (num_produtos > 0) {
        printf("\nLista de produtos:\n");
        printf("%-20s %-10s %-10s\n", "Nome", "Preço", "Quantidade");
        for (int i = 0; i < num_produtos; i++) {
            printf("%-20s %-10.2f %-10d\n", estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
        }
    } else {
        printf("Nenhum produto disponível no estoque.\n");
    }
}

void adicionarUsuario(Usuario *usuarios, int *num_usuarios) {
    FILE *arquivo = fopen("usuarios.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo usuarios.txt\n");
        return;
    }

    if (*num_usuarios < MAX_USUARIOS) {
        printf("Digite o nome do novo usuário: ");
        scanf("%s", usuarios[*num_usuarios].nome);

        printf("Digite a senha do novo usuário: ");
        scanf("%s", usuarios[*num_usuarios].senha);

        printf("Digite o nível de privilégio (0 para convencional, 1 para administrador): ");
        scanf("%d", &usuarios[*num_usuarios].nivel_privilegio);

        usuarios[*num_usuarios].num_pedidos = 0;

        fprintf(arquivo, "%s %s %d\n", usuarios[*num_usuarios].nome, usuarios[*num_usuarios].senha, usuarios[*num_usuarios].nivel_privilegio);

        (*num_usuarios)++;
    }

    fclose(arquivo);
}


void exibirPedidos(Produto *estoque, int num_produtos, Usuario *usuarios, int num_usuarios) {
    printf("---- Lista de Pedidos ----\n");

    for (int i = 0; i < num_usuarios; i++) {
        Usuario *usuario = &usuarios[i];

        if (usuario->num_pedidos > 0) {
            printf("Pedidos de %s:\n", usuario->nome);

            for (int j = 0; j < usuario->num_pedidos; j++) {
                printf("Pedido %d:\n", j + 1);
                printf("Produto: %s\n", usuario->pedidos[j].nome_produto);
                printf("Quantidade: %d\n", usuario->pedidos[j].quantidade);
                printf("Total: %.2f\n", usuario->pedidos[j].total);
                printf("--------------------------\n");
            }
        } else {
            printf("O usuário %s não fez nenhum pedido.\n", usuario->nome);
        }
    }
}