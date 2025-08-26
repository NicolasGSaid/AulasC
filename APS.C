/*
    APS - Algoritmos de Ordenação em C

    Este código implementa três algoritmos de ordenação (QuickSort, MergeSort, HeapSort) e permite ao usuário escolher a origem dos dados.
    Abaixo estão os principais pontos do código e as linhas onde cada funcionalidade ocorre:

    1. Origem dos dados:
       - Menu de escolha: linha 109-114 (main)
       - Gerar aleatórios: linha 116-120 (main)
       - Digitar manualmente: linha 121 (main) e função lerDadosUsuario linha 67-77
       - Ler de arquivo txt: linha 123-129 (main) e função lerDadosArquivo linha 78-88

    2. Algoritmos de ordenação:
       - QuickSort: função quickSort linha 35-41, função partition linha 24-33
       - MergeSort: função mergeSort linha 61-66, função merge linha 44-59
       - HeapSort: função heapSort linha 101-106, função heapify linha 92-100

    3. Medição de tempo:
       - clock_t start, end; e double elapsed; linha 137-138 (main)
       - Medição para cada algoritmo: linha 141-157 (main)
       - Função timeDiff: linha 62-64

    4. Alocação dinâmica:
       - malloc dos vetores: linha 111-112 (main)
       - free dos vetores: linha 159-160 (main)

    5. Tratamento de erros:
       - Falha ao abrir arquivo: linha 80-83 (lerDadosArquivo)
       - Opção inválida: linha 131-134 (main)

    6. Modularidade:
       - Funções utilitárias: copyArray linha 65-67, timeDiff linha 68-70, lerDadosUsuario linha 71-81, lerDadosArquivo linha 82-92, testeArquivo linha 93-99

    Use esta referência para explicar cada parte do código durante sua apresentação.
*/

#include <stdio.h>      // Biblioteca para entrada e saída padrão (printf, scanf, FILE)
#include <stdlib.h>     // Biblioteca para funções utilitárias (malloc, free, rand, srand)
#include <time.h>       // Biblioteca para manipulação de tempo (clock, time)
#include <direct.h>     // Biblioteca para manipulação de diretórios (não usada diretamente aqui)

#define MAX 100000      // Define o tamanho máximo do vetor

// ----------------- QuickSort -----------------
/*
    QuickSort é um algoritmo eficiente de ordenação por comparação.
    Utiliza a estratégia de dividir e conquistar, escolhendo um pivô e particionando o vetor.
*/

// Função que realiza a partição do vetor em torno do pivô
int partition(int arr[], int low, int high) {
    int pivot = arr[high];           // Seleciona o último elemento como pivô
    int i = low - 1;                 // Inicializa o índice do menor elemento
    for (int j = low; j < high; j++) {   // Percorre o vetor da posição low até high-1
        if (arr[j] <= pivot) {           // Se o elemento atual é menor ou igual ao pivô
            i++;                         // Incrementa o índice do menor elemento
            int tmp = arr[i];            // Troca arr[i] com arr[j]
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1];                // Troca arr[i+1] com o pivô
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;                        // Retorna o índice do pivô após a partição
}

// Função recursiva principal do QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {                    // Se o subvetor tem mais de um elemento
        int pi = partition(arr, low, high);  // Particiona o vetor e obtém o índice do pivô
        quickSort(arr, low, pi - 1);         // Ordena recursivamente a parte à esquerda do pivô
        quickSort(arr, pi + 1, high);        // Ordena recursivamente a parte à direita do pivô
    }
}

// ----------------- MergeSort -----------------
/*
    MergeSort é um algoritmo estável de ordenação por comparação.
    Divide o vetor em duas partes, ordena cada uma e depois mescla.
*/

// Função que mescla dois subvetores ordenados
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;         // Calcula tamanhos dos subvetores
    int *L = (int*)malloc(n1 * sizeof(int)); // Aloca vetor temporário para a esquerda
    int *R = (int*)malloc(n2 * sizeof(int)); // Aloca vetor temporário para a direita

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];         // Copia elementos para L
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];     // Copia elementos para R

    int i = 0, j = 0, k = l;                                // Inicializa índices
    while (i < n1 && j < n2) {                              // Mescla L e R de volta em arr
        if (L[i] <= R[j]) arr[k++] = L[i++];                // Se L[i] menor, copia para arr
        else arr[k++] = R[j++];                             // Se R[j] menor, copia para arr
    }
    while (i < n1) arr[k++] = L[i++];                       // Copia o restante de L, se houver
    while (j < n2) arr[k++] = R[j++];                       // Copia o restante de R, se houver

    free(L); free(R);                                       // Libera memória dos vetores temporários
}

// Função recursiva principal do MergeSort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {                            // Se o subvetor tem mais de um elemento
        int m = l + (r - l) / 2;            // Calcula o meio do vetor
        mergeSort(arr, l, m);               // Ordena recursivamente a primeira metade
        mergeSort(arr, m + 1, r);           // Ordena recursivamente a segunda metade
        merge(arr, l, m, r);                // Mescla as duas metades ordenadas
    }
}

// ----------------- HeapSort -----------------
/*
    HeapSort é um algoritmo de ordenação baseado em heap binário.
    Constrói um heap máximo e extrai o maior elemento repetidamente.
*/

// Função que garante a propriedade do heap para o nó i
void heapify(int arr[], int n, int i) {
    int largest = i;                // Inicializa maior como raiz
    int l = 2 * i + 1;              // Calcula índice do filho esquerdo
    int r = 2 * i + 2;              // Calcula índice do filho direito

    if (l < n && arr[l] > arr[largest]) largest = l;   // Se filho esquerdo maior, atualiza largest
    if (r < n && arr[r] > arr[largest]) largest = r;   // Se filho direito maior, atualiza largest

    if (largest != i) {             // Se maior não é a raiz
        int tmp = arr[i];           // Troca arr[i] com arr[largest]
        arr[i] = arr[largest];
        arr[largest] = tmp;
        heapify(arr, n, largest);   // Recursivamente heapifica a subárvore afetada
    }
}

// Função principal do HeapSort
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i); // Constrói o heap máximo
    for (int i = n - 1; i > 0; i--) {                        // Extrai elementos do heap um por um
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;     // Move a raiz para o final
        heapify(arr, i, 0);                                  // Heapifica o heap reduzido
    }
}

// ----------------- Utilitários -----------------

// Função para copiar um vetor para outro
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];    // Copia elemento a elemento
}

// Função para calcular a diferença de tempo em segundos
double timeDiff(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;  // Converte ticks para segundos
}

// Função para ler dados digitados pelo usuário
int lerDadosUsuario(int *vetor, int max) {
    int n;
    printf("Quantos numeros deseja ordenar (max %d)? ", max); // Pergunta quantidade
    scanf("%d", &n);                                          // Lê quantidade
    if (n > max) n = max;                                     // Limita ao máximo
    printf("Digite %d numeros separados por espaco:\n", n);   // Solicita números
    for (int i = 0; i < n; i++) {                            // Lê os números
        scanf("%d", &vetor[i]);
    }
    return n;                                                 // Retorna quantidade lida
}

// Função para ler dados de um arquivo texto
int lerDadosArquivo(const char *nome, int *vetor, int max) {
    FILE *f = fopen(nome, "r");                  // Abre arquivo para leitura
    if (!f) {                                    // Se não abriu, mostra erro
        printf("Erro ao abrir arquivo!\n");
        return 0;
    }
    int n = 0;
    while (n < max && fscanf(f, "%d", &vetor[n]) == 1) { // Lê números do arquivo
        n++;
    }
    fclose(f);                                   // Fecha arquivo
    return n;                                    // Retorna quantidade lida
}

// Função para testar abertura de arquivo (debug)
void testeArquivo() {
    FILE *f = fopen("dados.txt", "r");           // Tenta abrir arquivo dados.txt
    if (!f) {
        printf("Arquivo dados.txt nao abriu!\n"); // Mensagem de erro
    } else {
        printf("Arquivo dados.txt abriu!\n");     // Mensagem de sucesso
        fclose(f);
    }
}

// ----------------- Função principal -----------------
int main() {
    int n, escolha;                              // n: quantidade de dados, escolha: opção do usuário
    int *data = (int*)malloc(MAX * sizeof(int)); // Aloca vetor original
    int *arr = (int*)malloc(MAX * sizeof(int));  // Aloca vetor para ordenação

    printf("Escolha a origem dos dados:\n");     // Menu de escolha
    printf("1 - Gerar aleatorios\n");
    printf("2 - Digitar manualmente\n");
    printf("3 - Ler de arquivo txt\n");
    printf("Opcao: ");
    scanf("%d", &escolha);                       // Lê opção do usuário

    // Preenche o vetor conforme a escolha do usuário
    if (escolha == 1) {
        printf("Quantos numeros aleatorios (ate %d)? ", MAX); // Pergunta quantidade
        scanf("%d", &n);                                      // Lê quantidade
        srand((unsigned int)time(NULL));                      // Inicializa gerador de números aleatórios
        for (int i = 0; i < n; i++) data[i] = rand() % 100000; // Gera números aleatórios
    } else if (escolha == 2) {
        n = lerDadosUsuario(data, MAX);                       // Lê dados do usuário
    } else if (escolha == 3) {
        char nome[100];
        printf("Digite o nome do arquivo (ex: dados.txt): "); // Solicita nome do arquivo
        scanf("%s", nome);                                    // Lê nome do arquivo
        n = lerDadosArquivo(nome, data, MAX);                 // Lê dados do arquivo
        if (n == 0) {                                         // Se não leu nada, encerra
            free(data); free(arr);
            return 1;
        }
        printf("Lidos %d numeros do arquivo.\n", n);          // Mostra quantidade lida
    } else {
        printf("Opcao invalida!\n");                          // Opção inválida
        free(data); free(arr);
        return 1;
    }

    clock_t start, end;                                       // Variáveis para medir tempo
    double elapsed;                                           // Variável para armazenar tempo decorrido

    // Ordena e mede tempo com QuickSort
    copyArray(data, arr, n);                                  // Copia dados para arr
    start = clock();                                          // Marca início
    quickSort(arr, 0, n - 1);                                 // Ordena com QuickSort
    end = clock();                                            // Marca fim
    elapsed = timeDiff(start, end);                           // Calcula tempo
    printf("QuickSort: %.6f s\n", elapsed);                   // Exibe tempo

    // Ordena e mede tempo com MergeSort
    copyArray(data, arr, n);                                  // Copia dados para arr
    start = clock();                                          // Marca início
    mergeSort(arr, 0, n - 1);                                 // Ordena com MergeSort
    end = clock();                                            // Marca fim
    elapsed = timeDiff(start, end);                           // Calcula tempo
    printf("MergeSort: %.6f s\n", elapsed);                   // Exibe tempo

    // Ordena e mede tempo com HeapSort
    copyArray(data, arr, n);                                  // Copia dados para arr
    start = clock();                                          // Marca início
    heapSort(arr, n);                                         // Ordena com HeapSort
    end = clock();                                            // Marca fim
    elapsed = timeDiff(start, end);                           // Calcula tempo
    printf("HeapSort: %.6f s\n", elapsed);                    // Exibe tempo

    free(data);                                               // Libera memória do vetor original
    free(arr);                                                // Libera memória do vetor de ordenação
    return 0;                                                 // Encerra
}

