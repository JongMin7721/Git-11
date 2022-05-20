#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *next;
} Node;


void printGraph(Node* head);
void BreathFirstSearch(Node* head);
void DepthFirstSearch(Node* head);
int initializeG(Node** h);
int freeG(Node* head);
int insertVertex(Node* head, int key);
int insertEdge(Node* head, int key);

int main()
{
	char command;
	int key;
	Node* head = NULL;

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
			initializeG(&head);                             //그래프 초기화
			break;
		case 'q': case 'Q':
			freeG(head);                                    //그래프 메모리 초기화
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(head, key);                              //정점 생성
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			insertEdge(head, key);                                //간선 생성
			break;
		case 'd': case 'D':
			DepthFirstSearch(head);                                 //깊이우선탐색
			break;
		case 'b': case 'B':
			BreathFirstSearch(head);                                //너비우선탐색
			break;
		case 'p': case 'P':
			printGraph(head);                                       //그래프 출력
			break;

		default:
			printf("\n-------------------     Rewrite command!    --------------------\n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}




int initializeG(Node** h){
    if(*h != NULL){
		freeG(*h);
	}
	
	*h = (Node*)malloc(sizeof(Node));
	(*h)->next = NULL;
	(*h)->key = -1;

	return 1;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->next);
		free(ptr);
	}
}

int freeG(Node* head){
	if (head->next == NULL)
	{
		free(head);
		return 1;
	}

	freeNode(head->next);
	free(head);

	return 1;
	
}

int insertVertex(Node* head, int key){
	if (head == NULL) {
		printf("Initialize First!\n");
		return -1;
	}
	
	if (key < 0 || key > 9) {
		printf("Select between 0 and 9!\n");
		return -1;
	}

	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->key = key;
	newnode->next = NULL;

	if (head->next == NULL) {
		head->next = newnode;
		return 1;
	}
	
	Node* ptr = head->next;
	Node* pptr = ptr;

	while (ptr != NULL) {
		if (ptr->key == key) {
			printf("Already have this Vertex!\n");
			return 1;
		}else if (ptr->key < key) {
			pptr = ptr;
			ptr = ptr->next;	
		}else {
			if (head->next == ptr) {
				head->next = newnode;
			}else{
				pptr->next = newnode;
			}
			newnode->next = ptr;
			return 1;
		}
		
	}
	


	return 1;
}

int insertEdge(Node* head, int key){

}

void printGraph(Node* head){

}

void BreathFirstSearch(Node* head){

}

void DepthFirstSearch(Node* head){

}