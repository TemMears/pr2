#include "server.h"
#include "struct.h"

Stack* createStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack)); 
	stack->head = NULL;
	return stack;
}
void addEl(Stack* stack, char* value) {
	NodeStack* newElement = (NodeStack*)malloc(sizeof(NodeStack));
	newElement->value = value;
	newElement->next = stack->head;
	stack->head = newElement;
}
char* delEl(Stack* stack) {
	if (stack == NULL || stack->head == NULL) {
		return "error";
	}
	NodeStack* removed = stack->head;
	stack->head = stack->head->next;
	char* res = _strdup(removed->value);
	free(removed->value);
	free(removed);
	return res;
}
void printStack(Stack* stack) {
	printf("Your stack: ");
	for (NodeStack* print = stack->head; print != NULL; print = print->next) {
		printf("%s ", print->value);
	}
	printf("\n");
}

int hash(const char* key) {
	int hashValue = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		hashValue += key[i];
	}
	return hashValue % SIZE;
}
int hash2(const char* key) {
	int hashValue = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		hashValue += key[i];
	}
	return (hashValue + 1) % SIZE;
}
HashTable* createHashTable() {
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (hashTable == NULL) {
		printf("error\n");
		return NULL;
	}
	for (int i = 0; i < SIZE; i++) {
		hashTable->table[i].key = NULL;
		hashTable->table[i].value = NULL;
		hashTable->table[i].occupied = false;
	}
	return hashTable;
}
void printHashMap(const HashTable* hashTable) {
	printf("Your hash map:\n");
	for (int i = 0; i < SIZE; i++) {
		if (hashTable->table[i].occupied) {
			printf("KEY %s  VALUE %s\n", hashTable->table[i].key, hashTable->table[i].value);
		}
	}
	printf("\n");
}
bool addEntry(HashTable* hashTable, char* key, char* value) {
	int index = hash(key);
	int step = hash2(key);
	while (hashTable->table[index].occupied) {
		if (strcmp(hashTable->table[index].key, key) == 0) {
			printf("The key is already exist\n");
			return false;
		}
		index = (index + step) % SIZE;
	}
	hashTable->table[index].key = _strdup(key);
	hashTable->table[index].value = _strdup(value);
	hashTable->table[index].occupied = true;
	return true;
}
char* getValue(HashTable* hashTable, char* key) {
	int index = hash(key);
	int step = hash2(key);
	while (hashTable->table[index].occupied) {
		if (strcmp(hashTable->table[index].key, key) == 0) {
			return hashTable->table[index].value;
		}
		index = (index + step) % SIZE;
	}
	return NULL;
}
bool removeEntry(HashTable* hashTable, char* key) {
	int index = hash(key);
	int step = hash2(key);
	int count = 0; 

	while (hashTable->table[index].occupied && count < SIZE - 1) {
		if (strcmp(hashTable->table[index].key, key) == 0) {
			free(hashTable->table[index].key);
			free(hashTable->table[index].value);
			hashTable->table[index].key = NULL;
			hashTable->table[index].value = NULL;
			hashTable->table[index].occupied = false;
			return true;
		}
		index = (index + step) % SIZE;
		count++;
	}

	return false;
}

int hashSet(char* value) {
	int hash = 0;
	for (int i = 0; i < strlen(value); i++) {
		hash = (hash * 31 + value[i]) % SIZE;
	}
	return hash;
}
NodeSet* createNode(char* value) {
	NodeSet* node = malloc(sizeof(NodeSet));
	int length = 0;
	char* src = value;
	while (*src) {
		length++;
		src++;
	}

	node->value = malloc(length + 1);


	char* dest = node->value;
	src = value;
	while (*src) {
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	node->next = NULL;
	return node;
}
bool removeElement(Set* set, char* value) {
	int index = hash(value);
	NodeSet* current = set->table[index];
	NodeSet* previous = NULL;

	while (current != NULL) {
		if (strcmp(current->value, value) == 0) {
			if (previous == NULL) {
				set->table[index] = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current->value);
			free(current);
			return true;
		}
		previous = current;
		current = current->next;
	}

	return false;
}
bool contains(Set* set, char* value) {
	int index = hash(value);
	NodeSet* current = set->table[index];

	while (current != NULL) {
		if (strcmp(current->value, value) == 0) {
			return true;
		}
		current = current->next;
	}

	return false;
}
bool insert(Set* set, char* value) {
	if (contains(set, value)) {
		return false;
	}

	int index = hash(value);
	NodeSet* node = createNode(value);

	if (set->table[index] == NULL) {
		set->table[index] = node;
	}
	else {
		NodeSet* current = set->table[index];
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = node;
	}
	return true;
}
void printSet(Set* set) {
	printf("Set: {");
	for (int i = 0; i < SIZE; i++) {
		NodeSet* current = set->table[i];
		while (current != NULL) {
			printf("%s", current->value);
			if (current->next != NULL) {
				printf(", ");
			}
			current = current->next;
		}
	}
	printf("}\n");
}

Queue* createQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL; 
	return queue;
}
void addQ(Queue* queue, char* value) {
	Node* newElement = (Node*)malloc(sizeof(Node));
	if (newElement == NULL) {
		printf("error\n");
		return;
	}
	newElement->value = value;
	newElement->next = NULL;

	if (queue->head == NULL) {
		queue->head = queue->tail = newElement;
	}
	else {
		queue->tail->next = newElement;
		queue->tail = newElement; 
	}
}
char* delQ(Queue* q)
{
	if (q->head == NULL) {
		return "Queue is empty";
	}
	char* value = q->head->value;
	Node* tmp = q->head;
	q->head = q->head->next;
	if (q->head == NULL)
		q->tail = NULL;

	free(tmp);

	return value;
}
void printQueue(Queue* queue) {
	printf("Your queue:\n");
	for (Node* print = queue->head; print != NULL; print = print->next) {
		printf("%s ", print->value);
	}
	printf("\n");
}


char* pr2(char* str) {
	static Stack* stack = NULL;
	if (stack == NULL)
	{
		stack = malloc(sizeof(Stack));
		stack->head = NULL;
	}
	static Queue* queue = NULL;
	if (queue == NULL)
	{
		queue = malloc(sizeof(Queue));
		queue->head = NULL;
	}
	static HashTable* hashTable = NULL;
	if (hashTable == NULL)
	{
		hashTable = malloc(sizeof(HashTable));
		for (int i = 0; i < SIZE; i++) {
			hashTable->table[i].key = NULL;
			hashTable->table[i].value = NULL;
			hashTable->table[i].occupied = false;
		}
	}
	static Set* set = { NULL };

	do {

		if (strstr(str, "stack") != NULL)
		{
			if (strstr(str, "SPOP") != NULL)
			{
				return delEl(stack);
			}
			else if (strstr(str, "SPUSH") != NULL)
			{
				char temp[] = " ";
				char* stroka;
				int count = 0;
				char value[100]; 
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(value, stroka);

						break;
					}
					stroka = strtok(NULL, temp);

				}
				char* copystr = _strdup(value);
				copystr[strlen(copystr) - 1] = '\0';

				addEl(stack, copystr);
				return "„^„|„u„}„u„~„„ „t„€„q„p„r„|„u„~ „r „ƒ„„„„{\n";

			}
			else {
				return"error\n";
			}
		}
		else if (strstr(str, "queue") != NULL)
		{
			if (strstr(str, "QPOP") != NULL)
			{
				return delQ(queue);

				system("pause");
				system("cls");
			}
			else if (strstr(str, "QPUSH") != NULL)
			{
				char temp[] = " ";
				char* stroka;
				int count = 0;
				char value[100]; 
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(value, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(value);
				copystr[strlen(copystr) - 1] = '\0';

				addQ(queue, copystr);
				return "„^„|„u„}„u„~„„ „t„€„q„p„r„|„u„~ „r „€„‰„u„‚„u„t„\n";

			}
			else {
				return"error\n";
			}
		}
		else if (strstr(str, "hash") != NULL)
		{
			if (strstr(str, "HSET") != NULL)
			{
				char temp[] = " ";
				char* stroka
					;
				int count = 0;
				char key[100];
				char value[100];
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(key, stroka);
					}
					if (count == 4) {
						strcpy(value, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				char* cl = _strdup(value);
				cl[strlen(cl) - 1] = '\0';
				if (addEntry(hashTable, copystr, cl) == true)
					return "„^„|„u„}„u„~„„ „t„€„q„p„r„|„u„~\n";

			}
			else if (strstr(str, "HGET") != NULL)
			{
				//„€„„„q„‚„p„ƒ„„r„p„~„y„u„}
				char temp[] = " ";
				char* stroka
					;
				int count = 0;
				char key[100];
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						//„ƒ„t„u„|„p„„„ „„„p„{„…„ „w„u „x„p„„y„ƒ„y„„„ „ƒ „Š„€„‚„„ „ƒ„ƒ„„|„{„€„z
						strcpy(key, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				copystr[strlen(copystr) - 1] = '\0';
				if (getValue(hashTable, copystr) != NULL)
				{
					return "%s\n", getValue(hashTable, copystr);
				}
				else return "error\n";
			}

			else if (strstr(str, "HDEL") != NULL)
			{
				char temp[] = " ";
				char* stroka;
				int count = 0;
				char key[100]; 
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(key, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				copystr[strlen(copystr) - 1] = '\0';
				if (removeEntry(hashTable, copystr) == true)
					return  "„^„|„u„}„u„~„„ „…„t„p„|„v„~\n";
				else return  "„S„p„{„€„s„€ „„|„u„}„u„~„„„p „~„u„„\n";
			}
			else
			{
				return"error\n";
			}
		}
		else if (strstr(str, "set") != NULL)
		{
			if (strstr(str, "SADD") != NULL)
			{
				char temp[] = " ";
				char* stroka;
				int count = 0;
				char key[100];
				char value[100];
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(key, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				copystr[strlen(copystr) - 1] = '\0';
				if (insert(&set, copystr) == true)
					return  "„^„|„u„}„u„~„„ „t„€„q„p„r„|„u„~.\n";
				else return  "„S„p„{„€„z „„|„u„}„u„~„„ „…„w„u „u„ƒ„„„.\n";

			}
			else if (strstr(str, "SREM") != NULL)
			{
				char temp[] = " ";
				char* stroka;

				int count = 0;
				char key[100];
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(key, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				copystr[strlen(copystr) - 1] = '\0';
				if (removeElement(&set, copystr) == true)
					return  "„^„|„u„}„u„~„„ „…„t„p„|„v„~\n";
				else return  "„S„p„{„€„s„€ „„|„u„}„u„~„„„p „~„u„„\n";

			}
			else if (strstr(str, "SISMEMBER") != NULL)
			{
				char temp[] = " ";
				char* stroka
					;
				int count = 0;
				char key[100]; 
				stroka = strtok(str, temp);
				while (stroka != NULL) {
					count++;
					if (count == 3) {
						strcpy(key, stroka);
						break;
					}
					stroka = strtok(NULL, temp);
				}
				char* copystr = _strdup(key);
				copystr[strlen(copystr) - 1] = '\0';
				if (contains(&set, copystr) == true)
				{
					return"is a member\n";
				}
				else return "not a member\n";

			}
			else
			{
				printf("error\n");

			}
		}
		else {
			return"error\n";
		}
	} while (1);
}