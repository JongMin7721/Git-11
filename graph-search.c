#include <stdio.h>
#include <stdlib.h>



typedef struct node {		//정점
	int key;
	struct node *next;		//다음정점
	struct edge *nedge;		//해당 정점의 간선들
} Node;

typedef struct edge {		//간선
	int key;
	struct edge *next;		//간선의 다음 간선
} Edge;


void printGraph(Node* head);
void BreathFirstSearch(Node* head);
void DepthFirstSearch(Node* head);
int initializeG(Node** h);
int freeG(Node* head);
void freeEdge(Edge* ptr);
void freeNode(Node* ptr);
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
	(*h)->nedge = NULL;
	(*h)->key = -1;

	return 1;
}

void freeNode(Node* ptr) {
	if(ptr) {					//현재정점가 있으면 실행
		freeEdge(ptr->nedge);		//정점의 모든 간선 반환
		freeNode(ptr->next);	//정점의 다음으로 이동
		free(ptr);				//정점 메모리 반환
	}
}

void freeEdge(Edge* ptr) {
	if(ptr) {					//현재간선이 있으면 실행
		freeEdge(ptr->next);	//간선의 다음으로 이동
		free(ptr);				//간선 메모리 반환
	}
}

int freeG(Node* head) {			//모든 노드 메모리 반환 함수
	if (head->next == NULL) {		//헤드의 다음이 없다면
		free(head);				//헤드 메모리 반환 후 리턴
		return 1;
	}

	freeNode(head->next);		//헤드의 모든 정점 반환
	free(head);					//헤드 메모리 반환

	return 1;
	
}

int insertVertex(Node* head, int key){		//정점을 오름차순으로 연결리스트로 구성
	if (head == NULL) {											//그래프 초기화를 하지 않았을 때
		printf("Initialize First!\n");							//오류 출력
		return -1;
	}
	
	if (key < 0 || key > 9) {									//정점의 값이 0~9 사이의 값이 아닐 경우
		printf("Select between 0 and 9!\n");					//오류 출력
		return -1;
	}

	Node* newnode = (Node*)malloc(sizeof(Node));			//노드생성
	newnode->key = key;										//정점의 값 입력
	newnode->next = NULL;
	newnode->nedge = NULL;

	if (head->next == NULL) {						//헤드가 가르키는 값이 없을 경우
		head->next = newnode;						//헤드의 다음을 새로 만든 노드로 설정
		return 1;
	}
	
	Node* ptr = head->next;				//임시로 가르키는 노드
	Node* pptr = head;					//위 노드의 이전노드

	while (ptr != NULL) {				//노드가 비어있지 않다면 반복
		if (ptr->key == key) {			//입력받은 값과 정점의 값이 같다면
			printf("Already have this Vertex!\n");		//이미 있는 값이라고 출력
			return 1;
		}else if (ptr->key < key) {			//정점의 값 < 입력받은 값
			pptr = ptr;						//다음노드로 이동 및 이전노드 설정
			ptr = ptr->next;	
		}else {							//정점의 값 > 입력받은 값
			pptr->next = newnode;		//정점의 이전값의 다음을 새로만든 노드로
			newnode->next = ptr;		//새로만든 노드의 다음을 현재 정점으로 설정
			return 1;
		}
		
	}

	pptr->next = newnode;		//마지막에 연결해야 하는 정점일경우
	return 1;
}

int insertEdge(Node* head, int key){



}

void printGraph(Node* head){				//그래프 출력
	if(head == NULL) {						//헤드가 없다면
		printf("Nothing to print....\n");	//출력할 것이 없음
		return;
	}

	Node* ptr = head->next;

	printf("\n---PRINT\n");			//프린트 시작

	while (ptr != NULL) {			//정점이 끝날 때까지 반복
		printf("[ [%d] --", ptr->key);	//정점출력
		Edge* line = ptr->nedge;		//간선 설정
		
		if (line == NULL) {				//간선이 없다면
			printf(" NULL ]");			//NULL출력
		}
		
		while (line != NULL) {			//간선이 끝날 때까지 반복
			printf("-> [%d] ", line->key);		//간선을 순서대로 춮력
			line = line->next;					//다음 간선으로 이동
		}
		printf(" ]\n");							//마지막 마무리 출력
		ptr = ptr->next;						//다음 정점으로 이동
	}
}

void BreathFirstSearch(Node* head){

}

void DepthFirstSearch(Node* head){

}