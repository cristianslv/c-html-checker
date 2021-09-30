// Criando estrutura da Pilha
struct Nodo {
    char tag[50];
    struct Nodo *abaixo;
};

struct Pilha {
    int tamanhoPilha;
    struct Nodo *topo;
};

// Criando tipagem para a Pilha
typedef struct Nodo nodo;
typedef struct Pilha pilha;

// Função que inicia a Pilha
void iniciaPilha(pilha *pilha);

// Função que verifica se pilha está vazia
int vazia(pilha *pilha);

// Função que exibe a pilha
void exibePilha(pilha *p);

// Função que empilha um novo elemento na Pilha
void empilharTag(pilha *p, char tag[50]);

// Função que desempilha o primeiro elemento da Pilha
void desempilharTag(pilha *p);

// Função que valida se é uma tag com fechamento HTML
bool validaTagComFechamento(char tag[50]);

// Função que valida se a tag de fechamento está sendo aberta
bool verificarTagAberturaNaPilha(pilha *p, char tag[50]);