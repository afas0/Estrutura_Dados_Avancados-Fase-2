/*****************************************************************//**
 * @file    header.h
 * @brief   Declarações das funções e estruturas 
 * @author  André Silva n20750
 * @date    Maio 2024
 *********************************************************************/
#pragma once

#include <stdbool.h>

 /**
  * @brief   Estrutura que representa as adjacêcias num grafo.
  */
typedef struct Adjacent {
    int id;                 /**< Identificador do vértice adjacente. */
    int dist;               /**< Distância para o vértice adjacente. */
    struct Adjacent* next;  /**< Ponteiro para o próximo vértice adjacente. */
} Adjacent;

/**
 * @brief   Estrutura que representa um vértice num grafo.
 */
typedef struct Node {
    int id;                     /**< Identificador do vértice. */
    bool visited;               /**< Indica se o vértice foi visitado durante uma travessia. */
    Adjacent* nextAdjacent;     /**< Ponteiro para o primeiro vértice adjacente. */
    struct Node* nextVertice;   /**< Ponteiro para o próximo vértice na lista de vértices do grafo. */
} Node;

/**
 * @brief   Estrutura que representa um grafo.
 */
typedef struct Graph {
    Node* inicioGraph;      /**< Ponteiro para o primeiro vértice na lista de vértices do grafo. */
    int numeroVertices;     /**< Número atual de vértices no grafo. */
} Graph;


//Leitura do Ficheiro de texto
Graph* LerFicheiro(char* ficheiroTxt, Graph* graph);
int* ProcurarValor(char* ficheiroTxt, int v);

//Vertices
Node* CriaVertice(int id);
bool ExisteVertice(Node* inicio, int id);
Node* InsereVertice(Node* inicio, Node* novo, bool* res);
Node* EliminaVertice(Node* vertices, int codVertice, bool* res);
Node* OndeEstaVertice(Node* inicio, int id);
void ShowGraph(Node* graph);

//Adjacencias
Adjacent* NewAdjacent(int id, int dist);
Adjacent* ElimiminaAdj(Adjacent* listAdj, int codAdj, bool* res);
Adjacent* ElimiminaAllAdj(Adjacent* listAdj, bool* res);
Node* EliminaAdjacenciaAllVertices(Node* vertices, int codAdj, bool* res);
Adjacent* InsereAdj(Adjacent* listaAdja, int idDestino, int dist);

//Grafo

void ShowGaphLA(Graph* gr);
Graph* InsereVerticeGrafo(Graph* g, Node* vertice, int* res);
Graph* EliminaVerticeGraph(Graph* g, int codVertice, bool* res);
Graph* EliminaAdjGraph(Graph* g, int origem, int destino, bool* res);
Node* OndeEstaVerticeGraph(Graph* g, int idVertice);
Graph* InsereAdjaGrafo(Graph* g, int idOrigem, int idDestino, int dist, bool* res, int numColunas);
Graph* CriaGraphH3();
bool ExisteVerticeGraph(Graph* inicio, int idVertice);

//Algoritmo de procura
void ProcessaVertice(Node* v);
bool BreadthFirstSearchCaminhoLA(Graph* g, int vOrigin, int vFinal, int* totdist);
bool BreadthFirstSearchCaminhoGrafoLA(Graph* g, int vOrigin, int vFinal, int numVert, int** listaCaminho, int* size, int* max);
Node* ResetVertices(Node* inicio);
#pragma endregion


