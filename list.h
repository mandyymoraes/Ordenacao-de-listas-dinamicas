#include <stdbool.h>
#define MAX_LIST_SIZE 100


/*Stuct criado para a estruturação da lista dinamica, 
aloca o valor do elemento e conecta ele ao proximo elemento da lista*/
struct Lista
{
    int elemento; 
    struct Lista *proximo_elemento; 
};

/*referencia do struct da estrutura da lista*/
typedef struct Lista* lista;

/*Struct que cria a lista em si, com os campos de primeiro elemento e ultimo*/
typedef struct 
{
    lista comeco_lista; 
    int fim_lista;
} Lista_encadeada;

/*referencia do struct dos elementos da lista*/
typedef Lista_encadeada* lista_encadeada;

//função que cria a estrutura da lista
lista_encadeada cria_lista();
// função que deleta a lista e seus dados
void deletar(lista_encadeada container);
// função que mostra os elementos da lista
bool mostra_lista(lista_encadeada container);
// função que pesquisa o elemento da lista 
bool pesquisa_elemento(lista_encadeada container, int chave, int *index);
// função que insere um elemento na lista
bool inserir_elemento(lista_encadeada container, int *elemento, int index);
// função que remove um elemento da lista pelo parametro do index
bool remove_index(lista_encadeada container, int index);
// função que remove um elemento da lista pelo parametro da chave
bool remove_chave(lista_encadeada container, int chave);
// função de insertion sort -> recebe a lista a ser ordenada 
void insertion_sort(lista_encadeada container);
// ordenação do quick sort para ascendente ou descendente
bool menor_elemento(int a, int b);
bool maior_elemento(int a, int b);
// printa o array criado
void print_array(int *array, int qntd_elementos, int opc);


/* funçaõ que ajuda na estruturaçaõ do quick sort por transformar a lista dinamica em um array 
para facilitar o particionamento dos pivos  
Utiliza como parametro a lista em si e seu tamanho que é deteminado pelos argumentos do argc */
int* lista_array(lista_encadeada container, int argc);

// função que estrutura o quick sort
void quick_sort(int *array, int pivo_inferior, int pivo_superior, bool (*compara)(int,int));