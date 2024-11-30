# Manipulação de Grafos e Cálculo de Somatório Máximo em C

## Descrição

Este projeto implementa um conjunto de funções em C para manipulação de grafos e cálculo do somatório máximo possível de inteiros a partir de uma matriz de inteiros de dimensões arbitrárias. O projeto utiliza uma estrutura de lista de adjacências para representar o grafo.

## Funcionalidades Principais

- Leitura de dados de grafo a partir de um ficheiro de texto
- Impressão do grafo
- Adição e remoção de arestas e vértices
- Cálculo do somatório máximo de inteiros

## Estrutura do Projeto

O projeto é composto por cinco arquivos principais:

1. `header.h`: Contém as declarações de estruturas e funções principais.
2. `queue.h`: Declara funções para manipulação de uma fila.
3. `amqueue.c`: Implementa as funções da fila declaradas em `queue.h`.
4. `source.c`: Implementa as funções principais declaradas no `header.h`.
5. `main.c`: Programa principal que utiliza as funções implementadas.

## Estrutura de Dados

O grafo é representado por uma lista de adjacências, onde:
- Cada nó (vértice) contém adjacências para outros vértices
- As conexões são definidas para vértices na mesma linha ou coluna
