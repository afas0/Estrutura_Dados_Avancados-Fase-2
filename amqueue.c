/*****************************************************************//**
 * @file    amqueue.c
 * @brief   Funções para manipulação de queues
 * @author  André Silva n20750
 * @date    Maio 2024
 *********************************************************************/
#include "queue.h"
 /**
  * @brief   Insere um elemento na queue.
  *
  * @param queue Array da queue.
  * @param rear Ponteiro para o final da queue.
  * @param data Dados a serem inseridos.
  * @return  Verdadeiro se a inserção for bem-sucedida.
  */
bool insertQueue(int queue[], int* rear, int data) {
	queue[(*rear)++] = data;
	return true;
}
/**
 * @brief   Remove um elemento da queue.
 *
 * @param queue Array da queue.
 * @param front Ponteiro para a frente da queue.
 * @return  Elemento removido.
 */
int removeQueue(int queue[], int* front) {
	return queue[(*front)++];
}
/**
 * @brief   Verifica se a queue está vazia.
 *
 * @param rear Final da queue.
 * @param front Frente da queue.
 * @return  Valor.
 */
bool isQueueEmpty(int rear, int front) {
	return rear == front;
}


