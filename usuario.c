#include <stdio.h>
#include <string.h>
#include "sgc.h"

#define MAX_NAME_LENGTH 50
#define MAX_NOME 50
#define MAX_PEDIDOS 50
#define MAX_PRODUTOS 100
#define MAX_USUARIOS 50



void menuUsuarioConvencional(Produto *estoque, int num_produtos, Usuario *usuario, int *num_pedidos, Usuario *usuarios, int num_usuarios) {
    int opcao;
    do {
        printf("\n---- Menu do Usuário Convencional ----\n");
        printf("1. Ver Produtos Disponíveis\n");
        printf("2. Fazer Pedido\n");
        printf("3. Ver Meus Pedidos\n");
        printf("0. Entrar como usuário Admin\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirProdutos(estoque, num_produtos);
                break;
            case 2:
                fazerPedido(estoque, num_produtos, usuario, num_pedidos);
                break;
            case 3:
                exibirPedidos(estoque, num_produtos, usuarios, num_usuarios);
                break;
            case 0:
                printf("Entrando como usuário Admin...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void fazerPedido(Produto *estoque, int num_produtos, Usuario *usuario, int *num_pedidos) {
    if (usuario->nivel_privilegio == 0) {  // Verifica se o usuário é convencional
        char nomeProduto[MAX_NOME];
        int quantidade;

        printf("Digite o nome do produto desejado: ");
        fgets(nomeProduto, sizeof(nomeProduto), stdin);

        nomeProduto[strcspn(nomeProduto, "\n")] = '\0';

        int indexProduto = -1;
        for (int i = 0; i < num_produtos; i++) {
            if (strcmp(estoque[i].nome, nomeProduto) == 0) {
                indexProduto = i;
                break;
            }
        }

        if (indexProduto != -1) {
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade);

            if (quantidade <= estoque[indexProduto].quantidade) {

                if (*num_pedidos < MAX_PEDIDOS) {

                    strcpy(usuario->pedidos[*num_pedidos].nome_produto, nomeProduto);
                    usuario->pedidos[*num_pedidos].quantidade = quantidade;
                    usuario->pedidos[*num_pedidos].total = quantidade * estoque[indexProduto].preco;


                    estoque[indexProduto].quantidade -= quantidade;

                    (*num_pedidos)++;

                    printf("Pedido realizado com sucesso!\n");
                } else {
                    printf("Capacidade máxima de pedidos atingida. Não é possível fazer mais pedidos.\n");
                }
            } else {
                printf("Quantidade indisponível no estoque. Pedido não realizado.\n");
            }
        } else {
            printf("Produto não encontrado no estoque. Pedido não realizado.\n");
        }
    } else {
        printf("Apenas usuários convencionais podem fazer pedidos.\n");
    }
}
