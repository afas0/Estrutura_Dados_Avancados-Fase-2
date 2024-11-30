/*****************************************************************//**
 * @file    queue.h
 * @brief   Declarações das funções de queue
 * @author  André Silva n20750
 * @date    Maio 2024
 *********************************************************************/
#pragma once

#include <stdbool.h>


bool insertQueue(int queue[], int* rear, int data);
int removeQueue(int queue[], int* front);
bool isQueueEmpty(int rear, int front);
