#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 10



typedef struct node {
	int key;
	struct node *next;
} Node;

Node* node[MAX_GRAPH_SIZE];
int visited[MAX_GRAPH_SIZE];
int queue[MAX_GRAPH_SIZE];

int front = 0;
int rear = 0;

void enQueue(int key);
int deQueue();

void printGraph();
void BreathFirstSearch();
void DepthFirstSearch(int key);
void initvisited();
int initializeG();
int freeG();
int insertVertex(int key);
int insertEdge(int key1, int key2);
Node* outNode(int key);


int main()
{
	char command;
	int key1, key2;

	do{
		printf("\n\n");
        printf("------------[      [Won Jong Min] [2019038014]      ]-----------\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeG();                             //그래프 초기화
			break;
		case 'q': case 'Q':
			freeG();                                    //그래프 메모리 초기화
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key1);
			insertVertex(key1);                              //정점 생성
			break;
		case 'e': case 'E':
			printf("Your Key1 = ");
			scanf("%d", &key1);
			printf("Your Key2 = ");
			scanf("%d", &key2);
			insertEdge(key1, key2);                                //간선 생성
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key1);
			initvisited();
			DepthFirstSearch(key1);                                 //깊이우선탐색
			break;
		case 'b': case 'B':
			printf("Your Key = ");
			scanf("%d", &key1);
			initvisited();
			BreathFirstSearch(key1);                                //너비우선탐색
			break;
		case 'p': case 'P':
			printGraph();                                       //그래프 출력
			break;

		default:
			printf("\n-------------------     Rewrite command!    --------------------\n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}




int initializeG(){
	if (node != NULL) {
		freeG();
		for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
			node[i] = NULL;
		}
	}
	return 1;
}

int freeG(){
	for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
		if (node[i]) {
		Node* n = outNode(i);
		Node* m = n;
		n = n->next;
		if(n != NULL) {
			free(m);
			m = n;
			n = n->next;
		}
		free(n);
		}
	}
	return 1;
}



int insertVertex(int key){
	if (key < 0 || key > 9) {
		printf("Select between 0 and 9!\n");
		return -1;
	}
	
	if (!node[key]) {
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->key = key;
		newnode->next = NULL;
		node[key] = newnode;
	}else {
		printf("Already have this Vertex!\n");
	}

	return 1;
}

int insertEdge(int key1, int key2){
	if (key1 < 0 || key1 > 9) {
		printf("Select key1 between 0 and 9!\n");
		return -1;
	}

	if (key2 < 0 || key2 > 9) {
		printf("Select key2 between 0 and 9!\n");
		return -1;
	}

	if (!node[key1]){
		printf("Key1 is Not in Graph\n");
		return -1;
	}else if(!node[key2]) {
		printf("Key2 is Not in Graph\n");
		return -1;
	}
	
	Node* newnode1 = (Node*)malloc(sizeof(Node));
	newnode1->next = NULL;
	newnode1->key = key1;
	
	Node* newnode2 = (Node*)malloc(sizeof(Node));
	newnode2->next = NULL;
	newnode2->key = key2;

	if (key1 == key2) {
		
	}
	

	if (node[key1]->next == NULL && node[key2]->next == NULL) {
		node[key1]->next = newnode2;
		node[key2]->next = newnode1;
		return 1;
	}else if (node[key1]->next != NULL && node[key2]->next != NULL) {
		int check = 0;
		Node* n;
		Node* prev;
		n = node[key1]->next;
		prev = node[key1];
		while (n != NULL) {
			if (n->key < key2) {
				prev = n;
				n = n->next;
			}else if (n->key == key2) {
				printf("Already have This Keys!\n");
				return -1;
			}else {
				if (node[key1]->next == n) {
					newnode2->next = n;
					node[key1]->next = newnode2;
				}else {
					newnode2->next = n;
					prev->next = newnode2;
				}
				break;
			}
		}
		if (!check) {
			prev->next = newnode2;
		}

		check = 0;
		n = node[key2]->next;
		prev = node[key2];
		while (n != NULL) {
			if (n->key < key1){
				prev = n;
				n = n->next;
			}else {
				if (node[key2]->next == n) {
					check += 1;
					newnode1->next = n;
					node[key2]->next = newnode1;
				}else {
					newnode1->next = n;
					prev->next = newnode1;
				}
				break;
			}
		}
		if (!check) {
			prev->next = newnode1;
		}
		
		return 1;
	}else {
		if (node[key1]->next != NULL) {
			Node* n = node[key1]->next;
			Node* prev = node[key1];
			while (n != NULL) {
				if (n->key < key2) {
					prev = n;
					n = n->next;
				}else {
					if (node[key1]->next == n) {
						newnode2->next = n;
						node[key1]->next = newnode2;
					}else {
						newnode2->next = n;
						prev->next = newnode2;
					}
					node[key2]->next = newnode1;
					return 1;
				}
			}
			prev->next = newnode2;
			node[key2]->next = newnode1;
			return 1;
		}else if(node[key2]->next != NULL) {
			Node* n = node[key2]->next;
			Node* prev = node[key2];
			while (n != NULL) {
				if (n->key < key1) {
					prev = n;
					n = n->next;
				}else {
					if (node[key2]->next == n) {
						newnode1->next = n;
						node[key2]->next = newnode1;
					}else {
						newnode1->next = n;
						prev->next = newnode1;
					}
					node[key1]->next = newnode2;
					return 1;
				}
			}
			prev->next = newnode1;
			node[key1]->next = newnode2;
			return 1;
		}
	}
	
	return 1;
}

void printGraph(){				//그래프 출력
	int check = 0;
	for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
		if (!node[i]) {
			continue;
		}
		check += 1;
		Node* n = outNode(i);
		printf("[ [%d] ", n->key);
		n = n->next;
		while (n != NULL) {
			printf("--> [%d] ", n->key);
			n = n->next;
		}
		printf(" ]\n");
	}
	if (!check) {
		printf("Nothing to print....\n");	//출력할 것이 없음
		return;
	}
	
	
	return;
}

Node* outNode(int key) {
	return node[key];
}


void BreathFirstSearch(int key){
	Node* n;

	front = rear = 0;

	printf("%5d",key);
	visited[key] = 1;
	enQueue(key);

	while (front != rear) {
		key = deQueue();
		for (n = node[key]; n; n = n->next) {
			if (!visited[n->key]) {
				printf("%5d", n->key);
				enQueue(n->key);
				visited[n->key] = 1;
			}
		}
	}
	printf("\n");
	
}

void DepthFirstSearch(int key){
	Node* n;
	visited[key] = 1;
	printf("%5d", key);
	for (n = node[key]; n; n = n->next) {
		if (!visited[n->key]) {
			DepthFirstSearch(n->key);
		}
	}
}

void initvisited(){
	for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
		visited[i] = 0;
	}
}

int deQueue() {
	if (front == rear) {
		return -1;
	}

	front = (front + 1) % MAX_GRAPH_SIZE;
	return queue[front];

}

void enQueue(int key) {
	
	if (front == rear+1) {
		return;
	}

	rear = (rear + 1) % MAX_GRAPH_SIZE;
	queue[rear] = node[key]->key;
}