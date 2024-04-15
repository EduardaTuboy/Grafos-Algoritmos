#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

// Estrutura de uma lista de adjacência
typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

// Estrutura de um grafo
typedef struct {
  Node *adjList[MAX_VERTICES]; // Lista de adjacência
  int visited[MAX_VERTICES];   // Lista de nós visitados
  int stack[MAX_VERTICES];     // Pilha para ordem topológica
  int top;                     // Índice do topo da pilha
} Graph;

// Função para criar um novo nó na lista de adjacência
Node *createNode(int v) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph *graph, int src, int dest) {
  Node *newNode = createNode(dest);
  newNode->next = graph->adjList[src];
  graph->adjList[src] = newNode;
}

// Função para preencher a ordem topológica recursivamente
void fillOrder(Graph *graph, int v) {
  // Marcar o nó atual como visitado
  graph->visited[v] = 1;
  printf("%d cinza\n", v);

  // Iterar sobre todos os nós adjacentes
  Node *temp = graph->adjList[v];
  while (temp != NULL) {
    int adjVertex = temp->vertex;
    if (!graph->visited[adjVertex])
      fillOrder(graph, adjVertex);
    temp = temp->next;
  }

  // Empilhar o nó atual
  graph->stack[++graph->top] = v;
  printf("%d preto\n", v);
}

// Função para transpor o grafo (inverter as direções das arestas)
Graph *getTranspose(Graph *graph, int V) {
  Graph *transposedGraph = (Graph *)malloc(sizeof(Graph));
  for (int v = 0; v < V; v++) {
    transposedGraph->adjList[v] = NULL;
    transposedGraph->visited[v] = 0;
  }
  for (int v = 0; v < V; v++) {
    Node *temp = graph->adjList[v];
    while (temp != NULL) {
      addEdge(transposedGraph, temp->vertex, v);
      temp = temp->next;
    }
  }
  return transposedGraph;
}

// Função para imprimir a pilha
void printStack(Graph *graph) {
  printf("Ordem Topologica Reversa (pilha): ");
  for (int i = graph->top; i >= 0; i--) {
    printf("%d ", graph->stack[i]);
  }
  printf("\n");
}

// Função para imprimir os componentes fortemente conectados
void printStronglyConnectedComponents(Graph *graph, int V, int v, int v2) {
  graph->visited[v] = 1;
  printf("%d faz parte do cfc do %d\n", v, v2);
  Node *temp = graph->adjList[v];
  while (temp != NULL) {
    int adjVertex = temp->vertex;
    if (!graph->visited[adjVertex]) {
      printStronglyConnectedComponents(graph, V, adjVertex, v2);
    } else {
      printf("%d já estava visitado (v2: %d)\n", v, v2);
    }
    temp = temp->next;
  }
}

// Função principal do algoritmo de Kosaraju
void kosaraju(Graph *graph, int V) {
  graph->top = -1; // Inicializar o topo da pilha como -1

  // Preencher a ordem topológica
  for (int i = 0; i < V; i++) {
    if (!graph->visited[i])
      fillOrder(graph, i);
  }

  // Obter o grafo transposto
  Graph *transposedGraph = getTranspose(graph, V);

  // Resetar a lista de nós visitados
  for (int i = 0; i < V; i++) {
    graph->visited[i] = 0;
  }

  // Imprimir a ordem topológica reversa (pilha)
  printStack(graph);

  // Realizar uma DFS no grafo transposto usando a ordem topológica reversa
  printf("Componentes fortemente conectados:\n");
  while (graph->top >= 0) {
    int v = graph->stack[graph->top--];
    if (!transposedGraph->visited[v]) {
      printf("Condição de teste: O vértice %d não foi visitado no grafo "
             "transposto\n",
             v);
      printf("Componente fortemente conectado: ");
      printStronglyConnectedComponents(transposedGraph, V, v, v);
      printf("\n");
    } else {
      printf("%d já estava visitado\n", v);
    }
  }
}

// Função principal para teste
int main() {
  int V = 9; // Número de vértices do grafo
  Graph *graph = (Graph *)malloc(sizeof(Graph));

  // Inicializar o grafo
  for (int i = 0; i < V; i++) {
    graph->adjList[i] = NULL;
    graph->visited[i] = 0;
  }

  // Adicionar arestas ao grafo
  addEdge(graph, 0, 1);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);
  addEdge(graph, 2, 4);
  addEdge(graph, 3, 0);
  addEdge(graph, 4, 5);
  addEdge(graph, 5, 6);
  addEdge(graph, 6, 4);
  addEdge(graph, 7, 6);
  addEdge(graph, 7, 8);

  // Executar o algoritmo de Kosaraju
  kosaraju(graph, V);

  return 0;
}
