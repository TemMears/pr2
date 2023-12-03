#pragma once
#include "server.h"

typedef struct NodeHash {
    char* key;
    char* value;
    bool occupied;
} NodeHash;
typedef struct HashTable {
    NodeHash table[SIZE];
} HashTable;

typedef struct Node {
    char* value;
    struct Node* next;
} Node;
typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;

typedef struct NodeSet {
    char* value;
    struct NodeSet* next;
} NodeSet;
typedef struct Set {
    NodeSet* table[SIZE];
} Set;

typedef struct NodeStack {
    char* value;
    struct NodeStack* next; 
} NodeStack;
typedef struct Stack {
    NodeStack* head;
} Stack;

Stack* createStack();
void addEl(Stack* stack, char* value);
char* delEl(NodeStack** head);
void printStack(Stack* stack);

int hash(const char* key);
int hash2(const char* key);
HashTable* createHashTable();
void printHashMap(const HashTable* hashTable);
bool addEntry(HashTable* hashTable, char* key, char* value);
char* getValue(HashTable* hashTable, char* key);
bool removeEntry(HashTable* hashTable, char* key);

int hashSet(char* value);
NodeSet* createNode(char* value);
bool removeElement(Set* set, char* value);
bool contains(Set* set, char* value);
bool insert(Set* set, char* value);
void printSet(Set* set);

Queue* createQueue();
void addQ(Queue* queue, char* value);
char* delQ(Queue* q);
void printQueue(Queue* queue);

char* pr2(char* str);
