/**
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1 - Etapa 1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 * Ainda sem grupo, providenciarei para a próxima etapa
 * 
 */

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>

#define HASH_SIZE 997

typedef struct hash_node
{
	int type;
	char *text;
	struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddresses(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

#endif