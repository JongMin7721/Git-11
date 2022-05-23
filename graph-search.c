#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 10



typedef struct node {
	int key;
	struct node *next;
} Node;

Node* node[MAX_GRAPH_SIZE];

void printGraph();
void BreathFirstSearch();
void DepthFirstSearch();
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
			DepthFirstSearch();                                 //깊이우선탐색
			break;
		case 'b': case 'B':
			BreathFirstSearch();                                //너비우선탐색
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

void BreathFirstSearch(){

}

void DepthFirstSearch(){

}