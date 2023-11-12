#include <stdio.h>
#include "sgc.h"
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_USUARIOS 50
#define SENHA_ADMIN "123456"

// Declaração das variáveis globais
Produto estoque[MAX_PRODUTOS];
int num_produtos = 0;
Usuario usuarios[MAX_USUARIOS];
int num_usuarios = 0;
int num_pedidos = 0;
int indice_do_usuario;

int main() {

    carregarEstoqueDoArquivo(estoque, &num_produtos);
    carregarUsuariosDoArquivo(usuarios, &num_usuarios);
    menuUsuarioConvencional(estoque, num_produtos, &usuarios[indice_do_usuario], &num_pedidos, usuarios, num_usuarios); //O programa inicia com o menu do usuário  convencional.

    int opcao;
    int nivel_privilegio = 0;

   // Autenticação de administrador
    char senha_admin[MAX_SENHA];
    printf("Digite a senha de administrador: ");
    scanf("%s", senha_admin);


    if (!autenticarAdministrador(senha_admin)) {
        printf("Autenticação de administrador falhou. Programa encerrado!\n");
    }else{ 
   int opcao;
    int indice_do_usuario;
    do {
        printf("\n---- Menu ----\n");
        printf("1. Adicionar Produto\n");
        printf("2. Exibir Produtos\n");
        printf("3. Adicionar Usuário\n");
        printf("4. Excluir Usuário\n");
        printf("5. Fazer Pedido\n");
        printf("6. Exibir Pedidos\n");
        printf("0. Sair\n");
        printf("\nEscolha a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto(estoque, &num_produtos);
                break;
            case 2:
                exibirProdutos(estoque, num_produtos);
                break;
            case 3:
                adicionarUsuario(usuarios, &num_usuarios);
                break;
            case 4:
                excluirUsuario(usuarios, &num_usuarios);
                break;
            case 5:
                fazerPedido(estoque, num_produtos, &usuarios[indice_do_usuario], &num_pedidos);
                break;
            case 6:
                exibirPedidos(estoque, num_produtos, usuarios, num_usuarios);
                break;
            case 0:
                printf("Saindo do programa. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    salvarEstoqueNoArquivo(estoque, num_produtos);
    salvarUsuariosNoArquivo(usuarios, num_usuarios);
}
    return 0;
        }  

int autenticarAdministrador(const char *senha) { //compara a senha fornecida com a do admin
    return strcmp(senha, SENHA_ADMIN) == 0;
}


//As funções seguintes servem para quando o programa for reiniciado, continue lendo os produtos do estoque e os usuarios cadastrados.
void carregarEstoqueDoArquivo(Produto *estoque, int *num_produtos) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        return;
    }

    *num_produtos = 0; // Reinicializa o número de produtos

    while (fscanf(arquivo, "%s %f %d", estoque[*num_produtos].nome, &estoque[*num_produtos].preco, &estoque[*num_produtos].quantidade) == 3) {
        (*num_produtos)++;
    }

    fclose(arquivo);
}

void salvarEstoqueNoArquivo(Produto *estoque, int num_produtos) {
    FILE *arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque para escrita.\n");
        return;
    }

    for (int i = 0; i < num_produtos; i++) {
        fprintf(arquivo, "%s %.2f %d\n", estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }

    fclose(arquivo);
}

void carregarUsuariosDoArquivo(Usuario *usuarios, int *num_usuarios) {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    *num_usuarios = 0; // Reinicializa o número de usuários

    while (fscanf(arquivo, "%s %s %d", usuarios[*num_usuarios].nome, usuarios[*num_usuarios].senha, &usuarios[*num_usuarios].nivel_privilegio) == 3) {
        (*num_usuarios)++;
    }

    fclose(arquivo);
}

void salvarUsuariosNoArquivo(Usuario *usuarios, int num_usuarios) {
    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários para escrita.\n");
        return;
    }

    for (int i = 0; i < num_usuarios; i++) {
        fprintf(arquivo, "%s %s %d\n", usuarios[i].nome, usuarios[i].senha, usuarios[i].nivel_privilegio);
    }

    fclose(arquivo);
}

void atualizarArquivoUsuarios(Usuario *usuarios, int num_usuarios) {
    FILE *arquivo = fopen("usuarios.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo usuarios.txt para escrita.\n");
        return;
    }

    for (int i = 0; i < num_usuarios; i++) {
        fprintf(arquivo, "%s %s %d\n", usuarios[i].nome, usuarios[i].senha, usuarios[i].nivel_privilegio);
    }

    fclose(arquivo);
}





