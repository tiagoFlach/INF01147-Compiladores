/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */
#pragma once

#include <stdio.h>

#define HASH_SIZE 997

enum hashConst {
	HASH_IDT,
	HASH_VAR,
	HASH_VEC,
	HASH_FUN,

	HASH_LIT_I,
	HASH_LIT_C,
	HASH_LIT_F,
	HASH_LIT_S
};

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
void hashPrintByType(int type);