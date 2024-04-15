#include <stdio.h>
#include <stdlib.h>
#define INF 1000000
#define NIL -1
#define WHITE 0
#define GRAY 1
#define BLACK 2

// fila
typedef struct Queue {
  int capacity;
  int size;
  int front;
  int rear;
  int *elements;
} Queue;

Queue *createQueue(int maxElements) {
  Queue *Q = (Queue *)malloc(sizeof(Queue));
  Q->elements = (int *)malloc(sizeof(int) * maxElements);
  Q->size = 0;
  Q->capacity = maxElements;
  Q->front = 0;
  Q->rear = -1;
  return Q;
}

void enqueue(Queue *Q, int element) {
  if (Q->size == Q->capacity) {
    printf("Queue is Full\n");
  } else {
    Q->size++;
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->elements[Q->rear] = element;
  }
}

int dequeue(Queue *Q) {
  if (Q->size == 0) {
    printf("Queue is Empty\n");
    return -1;
  } else {
    Q->size--;
    int result = Q->elements[Q->front];
    Q->front = (Q->front + 1) % Q->capacity;
    return result;
  }
}

int isEmpty(Queue *Q) { return Q->size == 0; }

// Definição da estrutura do nó da lista encadeada
typedef struct Node {
  int data;          // Valor do nó
  struct Node *next; // Ponteiro para o próximo nó
} Node;

// Definição da estrutura do TAD lista encadeada
typedef struct {
  Node *head; // Ponteiro para o primeiro nó na lista
} LinkedList;

// Função para criar uma nova lista encadeada vazia
LinkedList *createLinkedList() {
  LinkedList *newList = (LinkedList *)malloc(sizeof(LinkedList));
  newList->head = NULL;
  return newList;
}

// Função para adicionar um elemento no início da lista
void addToHead(LinkedList *list, int value) {
  // Criar um novo nó
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;

  // O próximo nó do novo nó é o atual primeiro nó da lista
  newNode->next = list->head;

  // O novo nó agora é o primeiro nó da lista
  list->head = newNode;
}

// Função para imprimir os elementos da lista
void printList(LinkedList *list) {
  Node *current = list->head;
  printf("Lista: ");
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

// ---------------------------------------------------------------------------------------

void print_BFS(int n, int color[], int p[], int d[]) {
  for (int i = 0; i < n; i++) {
    printf("color[%d]: % 8d | d[%d]: % 8d | p[%d]: % 8d\n", i, color[i], i,
           d[i], i, p[i]);
  }
  printf("\n");
}

/* busca em largura:
  s = nó inicial (start)
  n = tamanho do grafo
  path = caminho feito para chegar a cada nó do grafo
  d[] = distância em arestas de s até o objetivo
  p[] = de onde veio antes para chegar no 2
*/
void BFS(int G[5][5], int s, int n, int *path) {
  int color[n], d[n], p[n];
  // valores iniciais
  for (int i = 0; i < n; i++) {
    color[i] = WHITE;
    d[i] = INF;
    p[i] = NIL;
  }
  // comecei
  color[s] = GRAY;
  d[s] = 0;
  p[s] = NIL;

  Queue *Q = createQueue(n);
  enqueue(Q, s);
  print_BFS(5, color, p, d);
  // while serve para mudar o vértice u, indo para onde não fui
  while (!isEmpty(Q)) {
    int u = dequeue(Q);
    // for serve para, estando no vértice u, ele visita suas arestas
    for (int v = 0; v < n; v++) {
      // confiro se há aresta e se eu não passei por ele (u e v são vértices) e
      // anota na fila onde ainda não fui
      if (G[u][v] && color[v] == WHITE) {
        color[v] = GRAY;
        d[v] = d[u] + 1;
        p[v] = u;
        enqueue(Q, v);
        print_BFS(5, color, p, d);

      } else {
        printf("%d não estava branco ou sem aresta com %d\n\n", v, u);
      }
    }
    // acabando todas as possibilidades para o u, pinto te preto
    color[u] = BLACK;
    print_BFS(5, color, p, d);
  }

  // Recreate path for each vertex from s
  for (int i = 0; i < n; i++) {
    int current = i;
    int pathIdx = 0;
    while (current != s && current != NIL) {
      path[pathIdx++] = current;
      current = p[current];
    }
    if (current == s) {
      printf("Path to %d: %d ", i, s);
      for (int j = pathIdx - 1; j >= 0; j--) {
        printf("-> %d ", path[j]);
      }
      printf("\n");
    } else {
      printf("No path to %d\n", i);
    }
  }
}

void print_DFS(int n, int color[], int p[], int t[]) {
  for (int i = 0; i < n; i++) {
    printf("color[%d]: % 8d | t[%d]: % 8d | p[%d]: % 8d\n", i, color[i], i,
           t[i], i, p[i]);
  }
  printf("\n");
}

// Função auxiliar para realizar a DFS a partir de um vértice u
void DFS_Visit(int u, int G[5][5], int n, int color[], int t[], int p[],
               int *time, LinkedList *List) {
  color[u] = GRAY;
  t[u] = ++(*time);             // Tempo de descoberta (vértice ficar preto)
  print_DFS(n, color, p, t);    // Opcional: imprimir o estado atual
  for (int v = 0; v < n; v++) { // vejos os vizinhos válidos v de u
    if (G[u][v] && color[v] == WHITE) {
      p[v] = u; // u é pai de v
      DFS_Visit(v, G, n, color, t, p, time, List);
    }
  }
  color[u] = BLACK;          // quando já vi todos os filhos do nó
  addToHead(List, u);        // Ordenação Topológica
  print_DFS(n, color, p, t); // Opcional: imprimir o estado atual
}

void DFS(int G[5][5], int n, int *path) {
  int color[n], t[n], p[n], time = 0;
  LinkedList *List = createLinkedList();
  for (int i = 0; i < n; i++) {
    color[i] = WHITE;
    p[i] = NIL;
  }

  // Para cada vértice u do grafo G, faça DFS_Visit se u não foi visitado
  for (int u = 0; u < n; u++) {
    if (color[u] == WHITE) {
      DFS_Visit(u, G, n, color, t, p, &time, List);
    }
  }
  printList(List);
  // Não é necessário reconstruir o caminho para DFS como feito em BFS
}

int main() {
  int G[5][5] = {{0, 1, 0, 0, 1},
                 {1, 0, 1, 1, 1},
                 {0, 1, 0, 1, 0},
                 {0, 1, 1, 0, 1},
                 {1, 1, 0, 1, 0}};

  // int G[5][5] = {{0, 0, 0, 0, 1},
  //                {1, 0, 0, 0, 0},
  //                {0, 1, 0, 0, 0},
  //                {0, 0, 1, 0, 0},
  //                {0, 0, 0, 1, 0}};

  int path[5]; // Assuming the path will not have more than 5 vertices
  BFS(G, 0, 5, path);
  // DFS(G, 5, path);
  return 0;
}
