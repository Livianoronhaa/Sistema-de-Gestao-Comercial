#define MAX_NOME 50
#define MAX_SENHA 20
#define MAX_PEDIDOS 50

// Estrutura para produtos
typedef struct {
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Produto;

// Estrutura para pedidos
typedef struct {
    char nome_produto[MAX_NOME];
    int quantidade;
    float total;
} Pedido;

// Estrutura para usuários
typedef struct {
    char nome[MAX_NOME];
    char senha[MAX_SENHA];
    int nivel_privilegio;
    Pedido pedidos[MAX_PEDIDOS];
    int num_pedidos;
} Usuario;

// Funções do sgc
int autenticarAdministrador(const char *senha);
void exibirMenu(int nivel_privilegio);
void menuUsuarioConvencional(Produto *estoque, int num_produtos, Usuario *usuario, int *num_pedidos, Usuario *usuarios, int num_usuarios);
void adicionarProduto(Produto *estoque, int *num_produtos);
void exibirProdutos(Produto *estoque, int num_produtos);
void adicionarUsuario(Usuario *usuarios, int *num_usuarios);
void excluirUsuario(Usuario *usuarios, int *num_usuarios);
void fazerPedido(Produto *estoque, int num_produtos, Usuario *usuario, int *num_pedidos);
void exibirPedidos(Produto *estoque, int num_produtos, Usuario *usuarios, int num_usuarios);
void atualizarArquivoUsuarios(Usuario *usuarios, int num_usuarios);
void carregarUsuariosDoArquivo(Usuario *usuarios, int *num_usuarios);
void salvarUsuariosNoArquivo(Usuario *usuarios, int num_usuarios);
void carregarEstoqueDoArquivo(Produto *estoque, int *num_produtos);
void salvarEstoqueNoArquivo(Produto *estoque, int num_produtos);




