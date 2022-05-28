#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 10				//0~9 의 갯수



typedef struct node {
	int key;
	struct node *next;					//엣지를 위한 구조체
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
void initvisited();						//visit flag 초기화
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
	if (node != NULL) {									//정점이 하나라도 있다면
		freeG();										//정점에 연결된 간선 초기화 후
		for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
			node[i] = NULL;								//정점 초기화
		}
	}

	initvisited();										//visit flag 초기화

	return 1;
}

int freeG(){											//메모리 반환
	for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
		if (node[i]) {									//정점이 있다면
		Node* n = outNode(i);							//정점을 빼내서
		Node* m = n;
		n = n->next;
		if(n != NULL) {									//간선들의 메모리 초기화
			free(m);
			m = n;
			n = n->next;
		}
		free(n);										//마지막 간선도 메모리 초기화
		}
	}
	return 1;
}



int insertVertex(int key){
	if (key < 0 || key > 9) {							//0~9이외의 숫자가 들어온다면 오류출력
		printf("Select between 0 and 9!\n");
		return -1;
	}
	
	if (!node[key]) {									//이미 있는 숫자가 아니라면
		Node* newnode = (Node*)malloc(sizeof(Node));	//노드 생성 후 정점 삽입
		newnode->key = key;
		newnode->next = NULL;
		node[key] = newnode;
	}else {
		printf("Already have this Vertex!\n");			//이미 있는 숫자라면 있다고 출력
	}

	return 1;
}

int insertEdge(int key1, int key2){
	if (key1 < 0 || key1 > 9) {								//1번키 2번키 둘중 하나라도 0~9이외의 숫자라면 오류출력
		printf("Select key1 between 0 and 9!\n");
		return -1;
	}

	if (key2 < 0 || key2 > 9) {
		printf("Select key2 between 0 and 9!\n");
		return -1;
	}

	if (!node[key1]){										//1번키와 2번키 둘중 하나라도 없다면 오류출력
		printf("Key1 is Not in Graph\n");
		return -1;
	}else if(!node[key2]) {
		printf("Key2 is Not in Graph\n");
		return -1;
	}
	
	Node* newnode1 = (Node*)malloc(sizeof(Node));			//1번키에 대한 엣지
	newnode1->next = NULL;
	newnode1->key = key1;

	if (key1 == key2) {										//자기 자신을 가르킨다면
		Node *n =  node[key1]->next;
		Node *prev = n;							
		while (n != NULL) {									
			if (n->key < key1) {
				prev = n;
				n = n->next;
			}else if (n->key == key1) {					//이미 있다면 있다고 출력
				printf("Already have This Key!\n");
				return -1;
			}else {										
				if (node[key1]->next == n) {			//첫 노드에 삽입해야 하는 경우	
					node[key1]->next = newnode1;
				}else {
					prev->next = newnode1;				//노드 사이에 생성한 노드 삽입
				}
				newnode1->next = n;						//중복된 문장
				return 1;
			}
		}
		prev->next = newnode1;						//마지막까지 찾지 못했다면 마지막에 삽입
		return 1;
	}
		
	Node* newnode2 = (Node*)malloc(sizeof(Node));			//2번키에 대한 엣지
	newnode2->next = NULL;
	newnode2->key = key2;

	if (node[key1]->next == NULL && node[key2]->next == NULL) {		//두 정점의 엣지가 하나도 없다면
		node[key1]->next = newnode2;								//각 정점의 다음에 엣지 삽입
		node[key2]->next = newnode1;
		return 1;
	}else if (node[key1]->next != NULL && node[key2]->next != NULL) {		//두 정점 모두 엣지를 하나라도 가진다면
		Node* n = node[key1]->next;		//비교를 위한 노드
		Node* prev = node[key1];		
		while (n != NULL) {
			if (n->key < key2) {				//키보다 엣지가 작다면 다음으로 이동
				prev = n;
				n = n->next;
			}else if (n->key == key2) {			//같은 값이 있다면 오류 출력
				printf("Already have These Keys!\n");
				return -1;
			}else {
				if (node[key1]->next == n) {		//정점의 첫 엣지가 된다면 그 사이에 삽입
					node[key1]->next = newnode2;
				}else {
					prev->next = newnode2;		//그 외의 경우 오름차순으로 삽입
				}
				newnode2->next = n;				//중복된 문장
				break;
			}
		}
		prev->next = newnode2;				//마지막까지 삽입이 안됐다면 마지막에 삽입

		n = node[key2]->next;									//윗 로직과 같은 내용
		prev = node[key2];										//윗 로직은 1번정점에 대한 내용이고 아랫내용은 2번 정점에 대한 내용
		while (n != NULL) {
			if (n->key < key1){
				prev = n;
				n = n->next;
			}else {
				if (node[key2]->next == n) {
					node[key2]->next = newnode1;
				}else {
					prev->next = newnode1;
				}
				newnode1->next = n;
				break;
			}
		}
		prev->next = newnode1;
		
		return 1;
	}else {													//그 외의 둘 중 하나라도 정점이 있다면
		if (node[key1]->next != NULL) {				//1번정점에 엣지가 있다면
			Node* n = node[key1]->next;
			Node* prev = node[key1];
			while (n != NULL) {						
				if (n->key < key2) {					//오름차 순을 위한 다음 이동
					prev = n;
					n = n->next;
				}else {
					if (node[key1]->next == n) {			//맨 첫 엣지가 될 때
						newnode2->next = n;
						node[key1]->next = newnode2;
					}else {									//그 외의 경우
						newnode2->next = n;
						prev->next = newnode2;
					}
					node[key2]->next = newnode1;			//중복된 문장 합침
					return 1;
				}
			}
			prev->next = newnode2;
			node[key2]->next = newnode1;				//마지막까지 찾지 못한 경우 1번정점의 마지막에 연결 후 2번정점 첫 노드에 입력
			return 1;
		}else if(node[key2]->next != NULL) {			//2번 정점에 엣지가 있다면
			Node* n = node[key2]->next;
			Node* prev = node[key2];
			while (n != NULL) {							//윗 로직과 같은 내용
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
	int check = 0;					//확인을 위한 변수
	for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
		if (!node[i]) {
			continue;					//정점이 없다면 패스
		}
		check += 1;
		Node* n = outNode(i);				//정점 꺼내기
		printf("[ [%d] ", n->key);				//정점 출력 후
		n = n->next;
		while (n != NULL) {
			printf("--> [%d] ", n->key);		//정점에 연결된 엣지 출력
			n = n->next;
		}
		printf(" ]\n");						//보기 좋은 결과를 위한 출력
	}
	if (!check) {				//출력한 것이 없다면
		printf("Nothing to print....\n");	//출력할 것이 없음
		return;
	}
	
	
	return;
}

Node* outNode(int key) {		//정점을 꺼내기 위한 함수
	return node[key];
}


void BreathFirstSearch(int key){				//너비 우선 탐색
	Node* n;

	front = rear = 0;		//처음과 끝 초기화

	printf("%5d",key);		//현재 지나간 정점 표시
	visited[key] = 1;		//visit flag에 표시
	enQueue(key);			//현재 정점을 큐에 삽입

	while (front != rear) {		//큐가 비어있지 않을 동안 반복
		key = deQueue();		//큐의 제일 앞의 값을 받고
		for (n = node[key]; n; n = n->next) {	//그 정점에 연결된 엣지만큼 반복
			if (!visited[n->key]) {				//visit flag에 표시가 되어있지 않다면
				printf("%5d", n->key);			//현재 지나가고 있는 정점을 표시 후
				enQueue(n->key);				//지나가고 있는 정점의 다음 노드를 큐에 삽입
				visited[n->key] = 1;			//현재 지나간 정점에 대한 visit flag 표시
			}
		}
	}
	printf("\n");
	
}

void DepthFirstSearch(int key){				//깊이 우선 탐색
	Node* n;
	visited[key] = 1;			//visit flag에 표시
	printf("%5d", key);			//현재 지나간 정점 표시
	for (n = node[key]; n; n = n->next) {	
		if (!visited[n->key]) {		//visit에 표시가 되어있지 않다면
			DepthFirstSearch(n->key);	//근접정점으로 이동
		}
	}
}

void initvisited(){						//visit flag 초기화
	for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
		visited[i] = 0;
	}
}

int deQueue() {							//큐 제거
	if (front == rear) {				//큐가 비어있다면 오류 출력
		printf("Queue is Empty!");
		return -1;
	}

	front = (front + 1) % MAX_GRAPH_SIZE;
	return queue[front];					//프론트가 가르키는 큐 리턴

}

void enQueue(int key) {					//큐 삽입
	
	if (front == rear+1) {		//큐가 가득 차있다면 오류출력
		printf("Queue is Full!");
		return;
	}

	rear = (rear + 1) % MAX_GRAPH_SIZE;
	queue[rear] = node[key]->key;			//rear가 가르키는 곳에 정점의 값(= 정점) 입력
}