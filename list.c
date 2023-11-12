#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

// estruturação da função que cria a lista
lista_encadeada cria_lista()
{
    // aloca dinamicamente a memoria para receber o tamanho de uma lista encadeada
    lista_encadeada container = malloc(sizeof(Lista_encadeada));
    // inicializa o fim da lista como -1
    container->fim_lista = -1;
    // inicializa o primeiro elemento da lista como null
    container->comeco_lista = NULL;
    // retorna a lista
    return container;
}

// função de deletar a lista encadeada

void deletar(lista_encadeada container)
{
    // verifica se a lista não é nula
    if (container != NULL)
    {
        // se coloca como o elemento selecionado o começo da lista
        lista elemento_atual = container->comeco_lista;
        // enquanto não se chega no final da lista
        while (elemento_atual != NULL)
        {
            // o começo da lista se passa para o proximo elemento da lista dinamica
            container->comeco_lista = elemento_atual->proximo_elemento;
            container->fim_lista--;
            // libera o elemento em questão
            free(elemento_atual);
            // volta pro começo da lista
            elemento_atual = container->comeco_lista;
        }
        // libera a estrutura da lista
        free(container);
    }
}

/*Determina o tamanho da lista dada */
int tamanho_da_lista(lista_encadeada container)
{
    // verifica se lista não é nula e se pega a quantidade de elementos que estam na lista
    if (container != NULL)
        return container->fim_lista + 1;
    return 0;
}

/*verifica se a lista dada não contem elementos (nula)*/
bool lista_vazia(lista_encadeada container)
{
    return tamanho_da_lista(container) == 0;
}

/*verifica se a lista já está com a quantidade maxima de elementos pré definidos */
bool lista_cheia(lista_encadeada container)
{
    return tamanho_da_lista(container) == MAX_LIST_SIZE;
}

// printa os elementos da lista
bool mostra_lista(lista_encadeada container)
{
    // verifica se a lista é vazia
    if (lista_vazia(container))
    {
        printf("A lista não possui elementos");
        return false;
    }
    // começa um for no começo da lista e vai até o elemento ser NULL (final da lista)
    for (lista i = container->comeco_lista; i != NULL; i = i->proximo_elemento)
        printf("%d ", i->elemento);
    printf("\n");

    return true;
}

// pesquisa de elemento conforme a posição dada -> recebe a lista, a chave a ser procurada, e a sua posição na lista
bool pesquisa_elemento(lista_encadeada container, int chave, int *index)
{
    // verifica se a lista é vazia
    if (lista_vazia(container))
    {
        printf("A lista não possui elementos");
        return false;
    }
    // vai passando de elemento por elemento para ver se bate com o elemento a ser procurado
    lista aux = container->comeco_lista;
    while (aux != NULL)
    {
        // compara se o elemento bate com a chave dada, se não bater vai para o proximo elemento
        *index += 1;
        if (aux->elemento == chave)
        {
            return true;
        }
        aux = aux->proximo_elemento;
    }
    *index = -1;
    return false;
}

// função que insere um elemento na lista  -> receb qual elemento a ser inserido, a chave e sua posição
bool inserir_elemento(lista_encadeada container, int *elemento, int index)
{
    // verifica se a lista tem espaço para inserir arquivos
    if (lista_cheia(container))
    {
        printf("não há espaço para inserir elementos");
        return false;
    }
    // verifica se não vai inserir um elemento antes do primeiro elemento da lista OU depois do ultimo elemento definido
    if (index < 0 || index > container->fim_lista + 1)
    {
        printf("A posição está ou no começo da lista ou no elemento final da lista");
        return false;
    }

    container->fim_lista++;
    // aloca memoria dinamicamente para o elemento a ser inserido
    lista inserir_elemento = malloc(sizeof(struct Lista));
    // atribui o valor para o ponteiro que referencia o elemento
    inserir_elemento->elemento = *elemento;
    // passa o valor NULL -> "final da lista" para o proximo elemento
    inserir_elemento->proximo_elemento = NULL;

    if (index == 0)
    {
        // inserir no primeiro elemento da lista
        inserir_elemento->proximo_elemento = container->comeco_lista;
        container->comeco_lista = inserir_elemento;
        return true;
    }

    // insere em sequencia na lista
    lista inicio = container->comeco_lista;
    int iterador = 0;
    while (iterador < index - 1)
    {
        iterador++;
        inicio = inicio->proximo_elemento;
    }
    // o elemento a ser inserido é o proximo elemento da lista
    inserir_elemento->proximo_elemento = inicio->proximo_elemento;
    inicio->proximo_elemento = inserir_elemento;
    return true;
}

// remove elementos pela posição passada
bool remove_index(lista_encadeada container, int index)

{
    // verifica se a lista ta vazia
    if (lista_vazia(container))
    {
        printf("a lista esta vazia");
        return false;
    }
    // verifica se a posição não esta nos extremos
    if (index < 0 || index > container->fim_lista + 1)
    {
        printf("A posição está ou no começo da lista ou no elemento final da lista");
        return false;
    }

    lista aux = NULL;
    container->fim_lista--;
    // se quer inserir no começo
    if (index == 0)
    {
        // se quer remover o primeiro elemento -> ele é removido e passado para o index 0 o proximo elemento da lista
        aux = container->comeco_lista->proximo_elemento;
        free(container->comeco_lista);
        container->comeco_lista = aux;
        return true;
    }

    // aponta para o inicio da lista e vai passando até a posição do elemento da lista igualar com a posição do elemento a ser retirado
    // vai passando pelos elementos da lista e ao mesmo tempo é atualizado o elemento anterior correspondente
    aux = container->comeco_lista;
    lista anterior = NULL;
    int elemento = 0;
    while (elemento < index)
    {
        anterior = aux;
        elemento++;
        aux = aux->proximo_elemento;
    }
    anterior->proximo_elemento = aux->proximo_elemento;
    // libera o elemento a ser removido
    free(aux);
    return true;
}

// remove um elemento a partir de uma chave passada
bool remove_chave(lista_encadeada container, int chave)
{
    int index = -1;
    // pesquisa o elemento a partir da chave para assim remove-lo
    if (pesquisa_elemento(container, chave, &index))
    {
        printf("%d", index);
        remove_index(container, index);
        return true;
    }
    printf("a chave passada não foi encontrada");
    return false;
}

// insertion sort
void insertion_sort(lista_encadeada container)
{
    // verificação se a lista é vazia
    if (lista_vazia(container) || tamanho_da_lista(container) == 1)
    {
        return;
    }

    lista organizacao = NULL;
    lista elemento_atual = container->comeco_lista;
    while (elemento_atual != NULL)
    {
        // faz a ordenação comparando os elementos -> se compara o elemento atual e o seu proximo
        //  se o proximo elemento se mostra maior que o está "selecionado" no momento ele é jogado sempre para o final da lista para questão de ordenação
        lista proximo_elemento = elemento_atual->proximo_elemento;

        if (organizacao == NULL || organizacao->elemento >= elemento_atual->elemento)
        {
            elemento_atual->proximo_elemento = organizacao;
            organizacao = elemento_atual;
        }
        else
        // aqui se faz a analise do se o elemento atual é maior que o anterior
        {
            lista aux = organizacao;
            while (aux->proximo_elemento != NULL && aux->proximo_elemento->elemento < elemento_atual->elemento)
            {
                aux = aux->proximo_elemento;
            }
            elemento_atual->proximo_elemento = aux->proximo_elemento;
            aux->proximo_elemento = elemento_atual;
        }

        elemento_atual = proximo_elemento;
    }

    container->comeco_lista = organizacao;
}

/*função que para facilitar a aplicação do quick sort a lista dinamica é transformada em array*/
int *lista_array(lista_encadeada container, int tamanho)
{
    // alocação de memória para o array
    int *array = malloc(tamanho * sizeof(int));

    // se passa pelos elementos da lista e as insere respectivamente na mesma posição no array e retorna o array para ser usado no quick sort
    int i = 0;
    for (lista elemento_atual = container->comeco_lista; elemento_atual != NULL; elemento_atual = elemento_atual->proximo_elemento)
    {
        array[i] = elemento_atual->elemento;
        i++;
    }
    return array;
}

// função que troca os elementos de posição -> funçao auxiliar para organizar as metades do array conforme a escolha do usuario
void troca_posicoes(int *array, int indexInicio, int indexFim)
{
    int aux = array[indexInicio];
    /*troca a posição dos elementos -> ajuda nas ordenações para trocar os elementos de lugares*/
    array[indexInicio] = array[indexFim];
    array[indexFim] = aux;
}

// determina o menor elemento em uma comparação
bool menor_elemento(int a, int b)
{
    return a <= b;
}

// determina o maior elemento em uma comparação
bool maior_elemento(int a, int b)
{
    return a >= b;
}

int dividir(int *array, int pivo_inferior, int pivo_superior, bool (*ordem)(int, int))
// função que pega o array e vai divindo ele para chegar as arrays de posições menores
{
    /*pega a metade do array e vai ordenando conforme as metades*/
    int meio = array[pivo_superior]; // pivo (valor maior do intervalo)
    int referencia = pivo_inferior;  // valores que vão ser comparados com o pivo
    // passa por cada elemento e o compara com o pivo
    for (int elemento = pivo_inferior; elemento < pivo_superior; elemento++)
        // se o elemento for menor que o pivo troca de ordem para ordenar conforme a função escolhida (crescente ou decrescente)
        if (ordem(meio, array[elemento]))
        {
            troca_posicoes(array, referencia, elemento);
            // utiliza a função de troca para ordenar
            referencia++;
        }
    // depois de realizar a ordenação de um pedaço se muda qual é o elemento que é tratado como pivô
    troca_posicoes(array, referencia, pivo_superior);
    return referencia;
}

// função que realiza o quick sort
void quick_sort(int *array, int pivo_inferior, int pivo_superior, bool (*compara)(int, int))
{
    if (pivo_inferior < pivo_superior)
    {
        int j;
        j = dividir(array, pivo_inferior, pivo_superior, compara);
        // dividi o array sempre na metade ai chamada a função para as duas metades
        // vai dividindo até chegar em elementos unicos para poder comparar e organizar as metades e depois junta-las
        quick_sort(array, pivo_inferior, j - 1, compara); // recursiva para a metade do lado esquerdo
        quick_sort(array, j + 1, pivo_superior, compara); // recursiva par a metade do lado direito
    }
}

// percorre os elementos do array
void print_array(int *array_da_lista, int qntd_elementos, int opcao_formatacao)
{
    if (opcao_formatacao == 1)
    {
        // se for decrescente a escolha, o endereço do elemento null aparece no inicio da lista, esse for retira esse arquivo par apenas printar os elementos da lista 
        for (int i = 1; i < qntd_elementos; i++)
            printf("%d ", array[i]);
        printf("\n");
    }
    else
    // se a opção for crescente o endereço do elemento null fica no final da lista, assim o loop for retira esse elemento para apenas mostrar os elementos da lista 
    {
        for (int i = 0; i < qntd_elementos - 1; i++)
            printf("%d ", array[i]);
        printf("\n");
    }
}
