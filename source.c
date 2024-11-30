/*****************************************************************//**
 * @file    source.c
 * @brief   Implementação de funções que manipulam um Grafo
 * @author  André Silva n20750
 * @date    Maio 2024
 *********************************************************************/

#include <stdbool.h> 
#include <stdio.h>  
#include <stdlib.h> 
#include <malloc.h> 
#include "header.h"
#include "queue.h"

#define MAX 100
#pragma warning (disable:4996)

#pragma region GerirVertices

 /**
  * @brief   Liberta a memória alocada para um vértice.
  *
  *
  * @param ptNode Ponteiro para o vértice a ser destruído.
  */
void DestroiVertice(Node* ptNode) {			
	free(ptNode);
}

/**
	@brief	Cria um novo vértice para um grafo.
	@param  id Identificador do vértice a ser criado.
	@return   Ponteiro para o novo vértice, ou NULL se a alocação de memória falhar.
**/
Node* CriaVertice(int id) {
	Node* aux = (Node*)malloc(sizeof(Node));
	if (aux == NULL)
	{
		return NULL;
	}
	aux->id = id;
	aux->nextVertice = NULL;
	aux->nextAdjacent = NULL;
	return aux;
}

/**
	@brief  Insere Vertice ordenado
	@param  vertices Ponteiro para o primeiro vértice na lista de vértices
	@param  novo     Ponteiro para o vértice a ser inserido.
	@param  res      Ponteiro para um booleano que indica se a inserção foi bem-sucedida.
	@return  Ponteiro para o primeiro vértice na lista de vértices após a inserção.
**/
Node* InsereVertice(Node* vertices, Node* novo, bool* res) {
	*res = false;

	//Insere no grafo vazio
	if (vertices == NULL) {
		*res = 1;
		vertices = novo;
		return vertices;
	}

	//verificar se V j� existe na lista de vertices...
	if (ExisteVertice(vertices, novo->id)) {
		return vertices;
	}
	else {
		//procura onde inserir
		Node* ant = NULL;
		Node* aux = vertices;
		while (aux != NULL && aux->id < novo->id)
		{
			ant = aux;
			aux = aux->nextVertice;
		}
		//Insere
		*res = true;
		if (ant == NULL) {
			novo->nextVertice = vertices;	//insere � cabe�a
			vertices = novo;
		}
		else {
			novo->nextVertice = aux;
			ant->nextVertice = novo;
		}
	}
		return vertices;
}


/**
	@brief  Verifica se determinado vertice existe
	@param  inicio -
	@param  id     -
	@retval        -
	@date   23.04.2024
**/
bool ExisteVertice(Node* inicio, int id) {
	if (inicio == NULL) return false;
	Node* aux = inicio;
	while (aux) {
		if (aux->id == id) return true;
		aux = aux->nextVertice;
	}
	return false;
}

/**
	@brief  Verifica se determinado vertice existe.
			Devolve o vertice, caso exista
	@param  inicio -
	@param  id     -
	@retval        -
	@date   23.04.2024
**/
Node* OndeEstaVertice(Node* inicio, int id) {
	if (inicio == NULL) return NULL;
	Node* aux = inicio;
	while (aux) {
		if (aux->id == id) return aux;
		aux = aux->nextVertice;
	}
	return NULL;
}


/**
	@brief  Apaga vertice na lista de vertices de um grafo
	@param  vertices   -
	@param  codVertice -
	@param  res        -
	@retval            -
	@date   29.04.2024
**/
Node* EliminaVertice(Node* vertices, int codVertice, bool* res) {
	*res = false;
	if (vertices == NULL) return NULL;

	//procurar vertice
	Node* aux = vertices;
	Node* ant = NULL;
	while (aux->id != codVertice) {
		ant = aux;
		aux = aux->nextVertice;
	}
	if (!aux) return vertices;	//signifca que n�o existe o vertice

	//apaga vertice no inicio
	if (ant == NULL)
	{
		//apaga todas adjacencias do vertice a eliminar
		aux->nextAdjacent = ElimiminaAllAdj(aux->nextAdjacent, res);
		if (*res == false) return vertices;
		vertices = aux->nextVertice;
	}
	else {
		//apaga vertice
		ant->nextVertice = aux->nextVertice;
	}
	DestroiVertice(aux);
	*res = true;
	return vertices;
}

/**
	@brief  Apaga uma determinada adjacencia em todos os vertices
	@param  vertices -
	@param  codAdj   -
	@param  res      -
	@retval          -
	@date   29.04.2024
**/
Node* EliminaAdjacenciaAllVertices(Node* vertices, int codAdj, bool* res) {
	*res = false;
	if (vertices == NULL)
		return NULL;

	Node* aux = vertices;
	while (aux) {
		aux->nextAdjacent = ElimiminaAdj(aux->nextAdjacent, codAdj, res);
		aux = aux->nextVertice;
	}
	*res = true;
	return vertices;
}


/**
	@brief
	@param graph -
	@date  23.04.2024
**/
void ShowGraph(Node* graph) {
	Node* current = graph;
	while (current != NULL) {
		printf("%d-> ", current->id);
		Adjacent* currentAdjacent = current->nextAdjacent;
		while (currentAdjacent != NULL)
		{
			printf("\t");
			printf("adjacent: %d\n", currentAdjacent->id);
			printf("\t");
			printf("dist: %d\n\n", currentAdjacent->dist);
			currentAdjacent = currentAdjacent->next;
		}
		current = current->nextVertice;
	}
}

#pragma endregion

#pragma region GerirLeituraFicheiro
/**
 * @brief Lê os dados de um ficheiro de texto e cria uma matriz a partir deles.
 *
 * @param ficheiroTxt Nome do ficheiro de texto.
 * @param graph Grafo para o qual os dados serão lidos e processados.
 * @return Ponteiro para o início do grafo.
 */

Graph* LerFicheiro(char* ficheiroTxt, Graph* graph) {
	FILE* ficheiro = fopen(ficheiroTxt, "r");
	if (ficheiro == NULL) {
		return NULL;
	}

	Node* vertices = NULL;
	int valor;
	char delimitador;
	int res;
	int contador = 0; 
	int numcolunas = 0;
	bool b = true;
	while (fscanf(ficheiro, "%d%c", &valor, &delimitador) > 0) {
		contador++;
		Node* novoVertice = CriaVertice(contador);
		if (novoVertice == NULL) {
			fclose(ficheiro);
			return graph; // Retorna a lista de vértices até o momento
		}
		vertices = InsereVerticeGrafo(graph, novoVertice, &res);
		if (delimitador == '\n' && b) {
			b = false; //para entrar apenas 1 vez
			numcolunas = contador;
		}
	}
	int cont = 1;
	rewind(ficheiro); //volta a ler desde o inicio
	while (fscanf(ficheiro, "%d%c", &valor, &delimitador) > 0) {
		if (cont == 1) {
			InsereAdjaGrafo(graph, cont , cont , NULL,  &res, numcolunas );
			InsereAdjaGrafo(graph, cont , cont + 1, NULL, &res, numcolunas);
			InsereAdjaGrafo(graph, cont , cont + numcolunas, NULL, &res, numcolunas);
			cont++;
		}
		else {			
			InsereAdjaGrafo(graph, cont, cont + 1, NULL, &res,  numcolunas);
			InsereAdjaGrafo(graph, cont, cont + numcolunas, NULL, &res,  numcolunas);
			cont++;
		}					
	}

	fclose(ficheiro);
	return graph;
}

/**
 * @brief Procura e retorna um valor num ficheiro de texto.
 *
 * @param ficheiroTxt Nome do ficheiro de texto.
 * @param v Valor a ser procurado.
 * @return Ponteiro para o valor encontrado.
 */
int* ProcurarValor(char* ficheiroTxt, int v) {
	FILE* ficheiro = fopen(ficheiroTxt, "r");
	if (ficheiro == NULL) {
		return NULL;
	}
	int valor;
	char delimitador;
	int contador = 0;
	while (fscanf(ficheiro, "%d%c", &valor, &delimitador) > 0){
		contador++;
		if (v == contador){			
			return valor;
			break;
		}
	}
}
#pragma endregion

#pragma region GereAdjacencias

/**
	@brief  Cria mem�ria para uma nova Adjac�ncia
	@param  id -
	@retval    -
	@date   1.05.2024
**/
Adjacent* NewAdjacent(int id, int dist)
{
	Adjacent* adjacent;

	adjacent = (Adjacent*)malloc(sizeof(Adjacent));
	if (adjacent == NULL)
	{
		return NULL;
	}
	adjacent->id = id;
	adjacent->dist = dist;
	adjacent->next = NULL;
	return adjacent;
}

/**
	@brief Elimina mem�ria alocada para uma adjac�ncia
	@param ptAdjacent -
	@date  1.05.2024
**/
void AdjacentDestroy(Adjacent* ptAdjacent)
{
	free(ptAdjacent);
}

/**
	@brief  Apaga adjacencia na Lista de Adjacencias
	@param  listAdj -
	@param  codAdj  -
	@param  res     -
	@retval         -
	@date   29.04.2024
**/
Adjacent* ElimiminaAdj(Adjacent* listAdj, int codAdj, bool* res) {
	*res = false;
	if (listAdj == NULL) return NULL;
	//procura adjacencia
	Adjacent* aux = listAdj;
	Adjacent* ant = NULL;
	while (aux && aux->id != codAdj) {
		ant = aux;
		aux = aux->next;
	}
	if (!aux) return listAdj;	//adjacencia n�o existe
	//apaga adjacencia no inicio
	if (ant == NULL)
	{
		//apaga todas adjacencias do vertice a eliminar
		listAdj = aux->next;
	}
	else {
		//apaga vertice
		ant->next = aux->next;
	}
	AdjacentDestroy(aux);
	*res = true;
	return listAdj;
}

/**
	@brief  Apaga todas as adjac�ncias de uma LA
	@param  listAdj -
	@param  res     -
	@retval         -
	@date   29.04.2024
**/
Adjacent* ElimiminaAllAdj(Adjacent* listAdj, bool* res) {
	*res = false;
	if (listAdj == NULL) return NULL;

	//percorre lista de adjacencia
	Adjacent* aux = listAdj;
	while (aux) {
		if (aux)
			listAdj = aux->next;
		AdjacentDestroy(aux);
		aux = listAdj;
	}
	listAdj = NULL;
	*res = true;
	return listAdj;
}

/**
	@brief  Insere nova adjacencia na LA (opcao 1)
			Adjac�ncia criada dentro da fun��o
	@param  listaAdja -
	@param  idDestino -
	@retval           -
	@date   29.04.2024
**/
Adjacent* InsereAdj(Adjacent* listaAdja, int idDestino, int dist) {
	Adjacent* newAdj;
	
	if (dist == NULL){
		dist = ProcurarValor("dados.txt", idDestino); //altterar istto
	}
	
	if ((newAdj = NewAdjacent(idDestino, dist)) == NULL)
	{
		return listaAdja;	//se n�o conseguiu criar nova adjacencia
	}

	//se lista de adjacencia estava vazia
	if (listaAdja == NULL) {
		listaAdja = newAdj; //insere a nova adjacencia no inicio
	}
	else
	{
		//por op��o, inserir no fim da LA
		Adjacent* aux = listaAdja;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = newAdj;
	}
	return listaAdja;
}

/*
Adjacent* InsereDist(Adjacent* listaAdja, int idDestino, int dist) {


	Adjacent* aux = listaAdja;
	if (aux->id == idDestino) {

	}
	while (aux->dist != NULL)
	{
		aux = aux->dist;
	}
	aux->dist = dist;
	return listaAdja;
}
*/
#pragma endregion

#pragma region GereGrafo

/**
	@brief  Cria mem�ria para a estrutura Grafo
	@param  tot -
	@retval     -
	@date   1.05.2024
**/
Graph* CriaGraphH3() {
	//valida��es
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	//testar
	if (graph != NULL) {
		graph->inicioGraph = NULL;
		graph->numeroVertices = NULL;
		//aux->totVertices = tot;		//numa LA pode n�o fazer sentido
	}
	return graph;
}


/**
	@brief  Insere Vertice num grafo (opcao 2)
	@param  g    - grafo
	@param  novo - Vertice a inserir
	@param  res  - controla sucesso da fun��o: sucesso=1
	@retval      - grafo alterado
	@date   23.04.2024
**/
Graph* InsereVerticeGrafo(Graph* g, Node* novo, int* res) {
	*res = 1;
	//valida��es
	if (novo == NULL) { //vertice invalido
		*res = 0;
		return g;
	}
	if (g == NULL) { // grafo vazio
		*res = -1;
		return NULL;
	}
	//verificar se V j� existe no grafo...
	if (ExisteVerticeGraph(g, novo->id)) { //vertice desconhecido
		*res = -2;
		return g;
	}
	g->inicioGraph = InsereVertice(g->inicioGraph, novo, res);
	if (*res == true)
		g->numeroVertices++;

	return g;
}

/**
	@brief  Insere nova adjacencia (opcao 2) no grafo
			Com controlo de sucesso
			Invoca fun��o que gere lista de adjacencias
	@param  g         -
	@param  idOrigem  -
	@param  idDestino -
	@param  res       -
	@retval           -
	@date   24.04.2024
**/
Graph* InsereAdjaGrafo(Graph* g, int idOrigem, int idDestino, int dist, bool* res, int numColunas) {

	*res = false;
	//Valida��es
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Node* originNode = OndeEstaVerticeGraph(g, idOrigem);
	if (originNode == NULL) return g;
	Node* destinyNode = OndeEstaVerticeGraph(g, idDestino);
	if (!destinyNode) return g;
	if ((idOrigem + 1 == idDestino) && (idOrigem % numColunas == 0)) {
		//para nao adicionar aadjacencias da ultima coluna com a primeira, por exemplo adjacencias: 15 -> 16, 20->21
	}
	else {
		originNode->nextAdjacent = InsereAdj(originNode->nextAdjacent, idDestino, dist);
	}
	*res = true;
	return g;
}

/**
	@brief  Apaga adjacencia entre dois vertices
	@param  g       -
	@param  origem  -
	@param  destino -
	@param  res     -
	@retval         -
	@date   29.04.2024
**/
Graph* EliminaAdjGraph(Graph* g, int origem, int destino, bool* res) {

	*res = false;

	//valida��es
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Node* originNode = OndeEstaVerticeGraph(g, origem);
	if (originNode == NULL) return g;
	Node* destinyNode = OndeEstaVerticeGraph(g, destino);
	if (!destinyNode) return g;

	originNode->nextAdjacent = ElimiminaAdj(originNode->nextAdjacent, destino, res);
	return g;
}

/**
	@brief  Procura determinado vertice num grafo
			Devolve o vertice, caso exista
	@param  g         -
	@param  idVertice -
	@retval           -
	@date   29.04.2024
**/
Node* OndeEstaVerticeGraph(Graph* g, int idVertice) {
	if (g == NULL) return NULL;
	return (OndeEstaVertice(g->inicioGraph, idVertice));
}

/**
	@brief  Verifica se determinado vertice existe num grafo
	@param  g         -
	@param  idVertice -
	@retval           -
	@date   23.04.2024
**/
bool ExisteVerticeGraph(Graph* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->inicioGraph, idVertice));
}

/**
	@brief  Apaga vertice de um grafo
	@param  g          -
	@param  codVertice -
	@param  res        -
	@retval            -
	@date   29.04.2024
**/
Graph* EliminaVerticeGraph(Graph* g, int codVertice, bool* res) {
	*res = false;
	if (g == NULL) return NULL;

	g->inicioGraph = EliminaVertice(g->inicioGraph, codVertice, res);
	g->inicioGraph = EliminaAdjacenciaAllVertices(g->inicioGraph, codVertice, res);
	if (*res == true) {
		g->numeroVertices--;
	}
	return g;
}

/**
	@brief Apresenta grafo
	@param gr -
	@date  29.04.2024
**/
void ShowGaphLA(Graph* gr) {
	ShowGraph(gr->inicioGraph);
}

#pragma endregion

#pragma region GereAlgoritmoProcura
/**
 * @brief Processa um vértice.
 *
 * @param v Ponteiro para o vértice a ser processado.
 */
void ProcessaVertice(Node* v) {
	printf("%d | ", v->id);
}

/**
 * @brief Realiza a busca em largura em um grafo utilizando listas de adjacências para encontrar um caminho entre dois vértices.
 *
 * @param g Grafo no qual a busca será realizada.
 * @param vOrigin Vértice de origem.
 * @param vFinal Vértice de destino.
 * @param totdist Ponteiro para armazenar a distância total percorrida no caminho encontrado.
 * @return Verdadeiro se um caminho entre os vértices foi encontrado, falso caso contrário.
 */
bool BreadthFirstSearchCaminhoLA(Graph* g, int vOrigin, int vFinal, int* totdist)
{
	// Auxiliar variables
	// Queue
	int queue[MAX] = {0};
	int rear, front;
	rear = front = 0;

	bool succ = false;
	int nextVertice;
	Node* lstVertices = g->inicioGraph;
	//marca vertice como visitado 
	Node* aux = OndeEstaVertice(lstVertices, vOrigin);
	if (aux == NULL) return false;
	if (aux->id == vFinal) return true;
	aux->visited = true;

	//insere vertice na queue 
	succ = insertQueue(queue, &rear, vOrigin);
	if (!succ) return false;

	
	
	while (!isQueueEmpty(rear, front)) {
		//trata nodo da frente da queue
		nextVertice = removeQueue(queue, &front);
		aux = OndeEstaVertice(lstVertices, nextVertice);
		if (aux == NULL) return false;
		if (aux->id == vFinal) {
			Node* current = g->inicioGraph;		
			while (current != NULL) {  // novo loop para encontrar o dist no id em questao
				Adjacent* adja = current->nextAdjacent;
				while (adja != NULL) {
					if (adja->id == vFinal) {
						// Found the adjacency corresponding to the desired vertex
						*totdist += adja->dist;
						return true;
					}
					adja = adja->next;
				}
				
				current = current->nextVertice;
			}
		} 
		//ProcessaVertice(aux);

		Adjacent* adj = aux->nextAdjacent;
		while (adj) {
			aux = OndeEstaVertice(lstVertices, adj->id);
			if (aux->visited == false)
			{
				aux->visited = true;
				succ = insertQueue(queue, &rear, adj->id);
			}
			adj = adj->next;
		}
	}
	return false;
}

/**
 * @brief Realiza a busca em largura em um grafo utilizando listas de adjacências para encontrar um caminho entre dois vértices.
 *
 * @param g Grafo no qual a busca será realizada.
 * @param vOrigin Vértice de origem.
 * @param vFinal Vértice de destino.
 * @param numVert Número total de vértices no grafo.
 * @param listaCaminho Ponteiro para a lista de caminho encontrado.
 * @param size Ponteiro para armazenar o tamanho do caminho encontrado.
 * @param max Ponteiro para armazenar o tamanho máximo do caminho.
 * @return Verdadeiro se um caminho entre os vértices foi encontrado, falso caso contrário.
 */
bool BreadthFirstSearchCaminhoGrafoLA(Graph* g, int vOrigin, int vFinal, int numVert, int** listaCaminho, int* size, int* max )
{	
	
	int* listaVertices = malloc(numVert * sizeof(int));
	int* listaValor = malloc(numVert * sizeof(int));
	int* listaAnterior = malloc(numVert * sizeof(int));
	//int* max = 0;

	for (int i = 0; i < numVert; i++) {
		listaVertices[i] = i+1;
		listaValor[i] = 0;
		listaAnterior[i] = 0;
	}
	printf("Lista de Vertices: \n");
	for (int i = 0; i < numVert; i++) {	
		printf("%d ", listaVertices[i]);
		printf("%d ", listaValor[i]); 
		printf("%d \n", listaAnterior[i]); 
	}
	
	// Auxiliar variables
	// Queue
	int queue[MAX] = { 0 };
	int rear, front;
	rear = front = 0;

	bool succ = false;
	int nextVertice;
	Node* lstVertices = g->inicioGraph;
	//marca vertice como visitado 
	Node* aux = OndeEstaVertice(lstVertices, vOrigin);
	if (aux == NULL) return false;
	if (aux->id == vFinal) return true;
	aux->visited = true;

	//insere vertice na queue 
	succ = insertQueue(queue, &rear, vOrigin);
	if (!succ) return false;

	while (!isQueueEmpty(rear, front)) {
		//trata nodo da frente da queue
		nextVertice = removeQueue(queue, &front);
		aux = OndeEstaVertice(lstVertices, nextVertice);
		if (aux == NULL) return false;
		if (aux->id == vFinal) {
			//Para converter das listas num caminho 
			//int* listaCaminho = NULL; // Pointer to listaCaminho, initially NULL
			int currentVertex = listaVertices[numVert - 1]; // Start from the last vertex
			// Allocate memory for listaCaminho and initialize its size to 1
			//int size = 1;
			*listaCaminho = malloc(sizeof(int));
			(*listaCaminho)[0] = currentVertex;
			*size = 1; // Initialize size

			// Traverse listaAnterior until reaching the first vertex
			while (currentVertex != 1) {
				currentVertex = listaAnterior[currentVertex - 1];
				(*size)++; // Increment size of listaCaminho
				*listaCaminho = realloc(*listaCaminho, (*size) * sizeof(int)); // Resize listaCaminho
				(*listaCaminho)[*size - 1] = currentVertex;
			}

			for (int i = 0; i < numVert; i++) {
				if (listaValor[i] > *max) {
					*max = listaValor[i];  //para determinar o maior na lista antes de voltar a tras
				}
			}
			//remover o printf depois de mostrar ao prof a tabela
			printf("Lista de Vertices: \n");
			for (int i = 0; i < numVert; i++) {
				printf("%d ", listaVertices[i]);
				printf("%d ", listaValor[i]);
				printf("%d \n", listaAnterior[i]);
			}
			return true;
		} 
		//ProcessaVertice(aux);
		Node* auxAnterior = aux;
		Adjacent* adj = aux->nextAdjacent;
		
		while (adj) {
			aux = OndeEstaVertice(lstVertices, adj->id);
			if (aux->visited == false)
			{
				aux->visited = true;
				if ((adj->dist + listaValor[auxAnterior->id - 1]) > (listaValor[aux->id - 1])) {  // apenas acrecentar na tabela se for maior do que lá já tem 
					listaValor[aux->id - 1] = adj->dist + listaValor[auxAnterior->id - 1];
					listaAnterior[aux->id - 1] = auxAnterior->id;
				}				
				succ = insertQueue(queue, &rear, adj->id);			
			}
			else {

				if ((adj->dist + listaValor[auxAnterior->id - 1]) > (listaValor[aux->id - 1])) {  // apenas acrecentar na tabela se for maior do que lá já tem 
					listaValor[aux->id - 1] = adj->dist + listaValor[auxAnterior->id - 1];
					listaAnterior[aux->id - 1] = auxAnterior->id;
				}
				adj = adj->next;
			}
			
		}
		
		/*
		printf("Lista de Vertices: \n");
		for (int i = 0; i < numVert; i++) {
			printf("%d ", listaVertices[i]);
			printf("%d ", listaValor[i]);
			printf("%d \n", listaAnterior[i]);
		}
		*/
	}
	
	return false;
}

/**
 * @brief Reseta o estado de visitado de todos os vértices na lista.
 *
 * @param inicio Ponteiro para o início da lista de vértices.
 * @return Ponteiro para o início da lista de vértices após o reset.
 */
Node* ResetVertices(Node* inicio) {
	Node* aux = inicio;
	while (aux) {
		aux->visited = false;
		aux = aux->nextVertice;
	}
	return inicio;
}

#pragma endregion