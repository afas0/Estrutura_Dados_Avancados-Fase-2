/*****************************************************************//**
 * @file    main.c
 * @brief   Função principal do programa
 * @author  André Silva n20750
 * @date    Maio 2024
 *********************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "header.h"


int main() {
#pragma region
	int res;
	char* nomeFicheiro = "dados.txt";
	Graph* graph = CriaGraphH3();
	graph = LerFicheiro(nomeFicheiro, graph);
	if (graph->inicioGraph == NULL) {
		printf("Erro ao ler a matriz do ficheio.\n");
		return 1;
	}
	ShowGraph(graph->inicioGraph);
	Node* novo1 = CriaVertice(100);
	graph = InsereVerticeGrafo(graph, novo1, &res);
	printf("\nApos Adiconar Vertice %d\n\n", novo1->id);
	graph = InsereAdjaGrafo(graph, 25, 100, 30, &res, NULL);
	ShowGaphLA(graph);
	printf("\nApos Eliminar Vertice %d\n\n", 100);
	graph = EliminaVerticeGraph(graph, 100, &res);
	ShowGaphLA(graph);
	graph = EliminaAdjGraph(graph, 25, 100, &res);
	printf("\nApos Eliminar Aresta %d - %d\n\n", 2, 100);
	ShowGaphLA(graph);
	graph->inicioGraph = ResetVertices(graph->inicioGraph);
	
	int* listaCaminho = NULL;
	int tamanho = 0;
	int max = 0;
	bool succ = BreadthFirstSearchCaminhoGrafoLA(graph, 1, 25, graph->numeroVertices, &listaCaminho, &tamanho, &max);
	if (succ) {
		printf("Caminho: ");
		for (int i = tamanho - 1; i >= 0; i--) {
			printf("%d", listaCaminho[i]);
			if (i != 0) printf(" -> ");
		}
		printf("\n");
	}
	else {
		printf("Caminho nao encontrado.\n");
	}
	printf("Maximo encontrado: %d\n\n", max); //Para imprimir o valor maximo

	graph->inicioGraph = ResetVertices(graph->inicioGraph);



	int caminho[5] = { 2, 3, 8, 9, 14 };
	int totdist = 0;
	int size = sizeof(caminho) / sizeof(caminho[0]);

	for (int i = 0; i < size - 1; i++) {
		int Vorigin = caminho[i];
		int valor = caminho[i + 1];
		graph->inicioGraph = ResetVertices(graph->inicioGraph);
		succ = BreadthFirstSearchCaminhoLA(graph, Vorigin, valor, &totdist);
	}
	if (succ) {
		printf("Distancia entre o caminho pretendido: %d\n\n", totdist);
	}
	

#pragma endregion

	return 0;
}
