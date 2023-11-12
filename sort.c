#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void helper()
{
    printf("Compile o codigo 'gcc sort.c list.c sort ");
    printf("Digite em seguida para iniciar a aplicação 'sort [elementos da lista desejada - ex(1 2 3 ...)] '");
}

int main(int argc, char *argv[])
{
    // criar as listas vazias
    lista_encadeada container = cria_lista();
    lista_encadeada insert_sort_list = cria_lista();
    lista_encadeada quick_sort_list = cria_lista();

    // preencimento das litas -> paramentro argc -> quantidade de caracteres que foram digitados como elementos da lista
    for (int i = 1; i < argc; i++)
    {
        // vai listar os elementos passados pelo console e inseri-los nas listas criadas -> converte de string para int
        int elemento = atoi(argv[i]);
        inserir_elemento(container, &elemento, i - 1);
        inserir_elemento(insert_sort_list, &elemento, i - 1);
        inserir_elemento(quick_sort_list, &elemento, i - 1);
    }

    /* cria um array a partir da lista dinamica inserida*/
    int *quick_sort_array = lista_array(quick_sort_list, argc);

    // printa a lista original
    printf("Lista original: ");
    mostra_lista(container);

    // printa a lista após o insertion sort
    printf("Lista apos o insert sort: ");
    insertion_sort(insert_sort_list);
    mostra_lista(insert_sort_list);

    // pergunta ao usuário qual a ordem para ordenar a lista com o quick sort, decrescente ou crescente
    printf(" Se deseja ordenar o valor por qual ordem? [1] Decrescente [2] Crescente ");
    int opc;
    scanf("%d", &opc);
    printf("Lista apos o quick sort: ");
    if (opc == 1)// opção decrescente -> utiliza da função menor elemento definida para ordenar a partir dos menores elementos 
    {
        quick_sort(quick_sort_array, 0, argc - 1, menor_elemento);

        print_array(quick_sort_array, argc, opc);
    }
    else //opção crescente -> utiliza da função maior elemento definida para ordenar a partir dos maiores elementos 
    {
        quick_sort(quick_sort_array, 0, argc - 1, maior_elemento);

        print_array(quick_sort_array, argc, opc );
    }
    /* outras funções que estavam definidas:
    - inserir elemento em uma posição
    - remove dados por uma chave
    - remove dados com base nos valores

    */

    
    printf("\n");
    printf("Outras opcoes:");
    printf("[1] Inserir dados em uma posicao especifica \n");
    printf("[2] Remover dados por chave \n");
    printf("[3] Remover dados por valor \n");
    printf("[4] Nenhuma das opcoes \n");
    int opc2;
    scanf("%d", &opc2);
    // opção 1 -> inserir dados em um posição
    if (opc2 == 1)
    {
        int pos, v;
        printf("Digite a posicao e o novo valor que sera inserido na lista: \n");
        scanf("%d", &pos);
        scanf("%d", &v);
        inserir_elemento(container, &v, pos);
    }
    // opção 2 -> remover dados por chave
    else if (opc2 == 2)
    {
        printf("Digite o index a ser retirado: ");
        int pos;
        scanf("%d", &pos);
        remove_index(container, pos);
    }
    // opção 3 -> remover dados por valor
    else if (opc2 == 3)
    {
        int v;
        scanf("%d", &v);
        remove_chave(container, v);
    }
    // opção de pesquisar elemento 
    printf("Deseja pesquisar um elemento?");
    printf("[1] Sim [2] Nao");
    int opc_pesquisa;
    scanf("%d", &opc_pesquisa);
    if (opc_pesquisa == 1)
    {
        int v;
        scanf("%d", &v);
        int pos = 0;
        pesquisa_elemento(container, v, &pos);

        printf("%d : posicao %d.", v, pos);
    }

    // deleta as listas
    deletar(container);
    deletar(insert_sort_list);
    deletar(quick_sort_list);

    return 0;
}