/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */
#include <string.h>
#include <stdlib.h>
#include "hash.h"

HASH_NODE *Table[HASH_SIZE];

void hashInit()
{
	int i;
	for (i = 0; i < HASH_SIZE; ++i)
		Table[i] = 0;
}

int hashAddress(char *text)
{
	int i;
	int address = 1;
	for (i = 0; i < strlen(text); ++i)
		address = (address * text[i]) % HASH_SIZE + 1;
	
	return address - 1;
}

HASH_NODE *hashFind(char *text)
{
	HASH_NODE *node;
	int address = hashAddress(text);
	for (node = Table[address]; node; node = node->next)
		if (strcmp(node->text, text) == 0)
			return node;

	return 0;
}

HASH_NODE *hashInsert(char *text, int type)
{
	HASH_NODE *newnode;
	int address = hashAddress(text);

	if ((newnode = hashFind(text)) != 0)
		return newnode;

	newnode = (HASH_NODE *) calloc(1, sizeof(HASH_NODE));
	newnode->type = type;
	newnode->text = (char *) calloc(strlen(text) + 1, sizeof(char));
	strcpy(newnode->text, text);

	newnode->next = Table[address];
	Table[address] = newnode;

	return newnode;
}

void hashPrint(void)
{
	int i;
	HASH_NODE *node;
	for (i = 0; i < HASH_SIZE; ++i)
		for (node = Table[i]; node; node = node->next)
			printf("Table[%d] has %d: %s\n", i, node->type, node->text);
}

void hashPrintByType(int type)
{
	int i;
	HASH_NODE *node;
	printf("\nType %d:\n", type);
	for (i = 0; i < HASH_SIZE; ++i)
		for (node = Table[i]; node; node = node->next)
			if (node->type == type)
				printf("%s\n", node->text);
}