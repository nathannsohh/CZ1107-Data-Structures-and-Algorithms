#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int matching(Graph g, int Std, int Prj, int Mtr);
int BFS (Graph g, int v, int w, int parent[]);
void printGraphList(Graph g);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////


int main()
{
    int Prj, Std, Mtr; //Project, Student and Mentor;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);

    int np,nm; //number of projects and number of mentors
	
    //build graph
	Graph g;
    g.V = Std + Prj + Mtr + 2;
    g.list = (ListNode **) malloc((g.V)*sizeof(ListNode *));

    for(int i = 0; i < g.V; i++)
        g.list[i] = NULL;

    for(int i = 0; i < Prj; i++)
        insertAdjVertex(&g.list[0], i+1+1);
    
    for(int i = 0; i < Mtr; i++)
        insertAdjVertex(&g.list[Std+Prj+i+1], g.V-1+1);

    //Write your code                           // First group -> Prj, Second group -> Student, Third group -> Mentor
    for(int i = 0; i < Std; i++){
        scanf("%d %d", &np, &nm);
        for(int j = 0; j < np; j++){
            int ID;
            scanf("%d", &ID);
            insertAdjVertex(&g.list[ID], Prj+i+1+1);
            g.E++;
        }
        for(int j = 0; j < nm; j++){
            int ID2;
            scanf("%d", &ID2);
            insertAdjVertex(&g.list[1+Prj+i], Prj+Std+ID2+1);
            g.E++;
        }
        
    }
    //apply Ford Fulkerson algorithm
    // use DFS or BFS to find a path
    printGraphList(g);
	maxMatch = matching(g, Std, Prj, Mtr);
    printf("%d\n", maxMatch);
    return 0;
}

int BFS (Graph g, int v, int w, int parent[]){

 // Write your code here
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int i = 0;
    int *list = (int*)calloc(g.V, sizeof(int));
    

    enqueue(&q, v);
    list[v-1] = 1;
    parent[v-1] = -1;
    while(!isEmptyQueue(q)){
        int u = getFront(q);
        dequeue(&q);
        ListNode *cur = g.list[u-1];
        while(cur != NULL){
            if(cur->vertex == w){
                parent[cur->vertex-1] = u;
                return 1;
            }
            else{
                if(list[cur->vertex-1] == 0){
                    enqueue(&q, cur->vertex);
                    list[cur->vertex-1] = 1;
                    parent[cur->vertex-1] = u;
                }
                cur = cur->next;
            }
        }
        
    }
    return 0;
}

int matching(Graph g, int Std, int Prj, int Mtr)
{
    //Write your code
    Graph rg = g;
    int max_flow = 0;
    int parent[g.V];
    while(BFS(g, 1, g.V, parent)){
        for(int i = g.V-1; i != 0; i = parent[i]-1){
            int u = parent[i]-1;
            removeAdjVertex(&g.list[u], i+1);

            if(i > Prj && i <= Std + Prj){
                for(int j = 1; j <= Prj; j++){
                    ListNode *temp = g.list[j];
                    int marker = 0;
                    while(temp != NULL){
                        if(temp->vertex == i+1){
                            marker = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                    if(marker == 1){
                        removeAdjVertex(&g.list[j], i+1);
                    } 

                }
            }
            
        }
            max_flow++;

    }

    return max_flow;
}

void removeAdjVertex(ListNode** AdjList,int vertex)
{
    ListNode *temp, *preTemp;
    if(*AdjList != NULL)
    {
        if((*AdjList)->vertex ==vertex){//first node
            temp = *AdjList;
            *AdjList = (*AdjList)->next;
            free(temp);
            return;
        }
        preTemp = *AdjList;
        temp = (*AdjList)->next;
        while(temp!=NULL && temp->vertex != vertex)
        {
            preTemp= temp;
            temp = temp->next;
        }
        preTemp->next = temp->next;
        free(temp);
    }

}
void insertAdjVertex(ListNode** AdjList,int vertex)
{
    ListNode *temp;
    if(*AdjList==NULL)
    {
        *AdjList = (ListNode *)malloc(sizeof(ListNode));
        (*AdjList)->vertex = vertex;
        (*AdjList)->next = NULL;
    }
    else{
        temp = (ListNode *)malloc(sizeof(ListNode));
        temp->vertex = vertex;
        temp->next = *AdjList;
        *AdjList = temp;
    }
}
void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}

void printQ(QueueNode *cur){
    if(cur==NULL) printf("Empty");

    while (cur != NULL){
        printf("%d ", cur->vertex);
        cur = cur->next;
    }
    printf("\n");
}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}



void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}