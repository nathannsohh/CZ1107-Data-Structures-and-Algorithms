#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

    calDegreeV(g,degreeV);

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void adjM2adjL(Graph *g)
{
 // Question 1
 // Write your code here
if (g->type == ADJ_LIST) {printf("Error"); return;}
if (g->V == 0) {printf("List Empty!"); return;}

ListNode **temp = malloc(sizeof(ListNode) * g->V);
ListNode *head = NULL;
for(int k = 0; k < g->V; k++) temp[k] = NULL;

for(int i = 0; i < g->V; i++){
    for(int j = 0; j < g->V; j++){
        if(g->adj.matrix[i][j] == 1){
            ListNode *cur, *newNode = malloc(sizeof(ListNode));
            newNode->next = NULL;
            newNode->vertex = j + 1;
            if(head == NULL){
                head = newNode;
                cur = head;
            }
            else{
                cur->next = newNode;
                cur = cur->next;
            }
            }
        }
        temp[i] = head;
        head = NULL;
    }
    g->type = ADJ_LIST;

    for(int i = 0; i < g->V; i++){
        free(g->adj.matrix[i]);
    }
    free(g->adj.matrix);
    g->adj.list = temp;
}


void adjL2adjM(Graph *g){
	// Question 2
    // Write your code here
    if (g->type == ADJ_MATRIX) {printf("Error"); return;}
    if (g->V == 0) {printf("List Empty!"); return;}

    int **matrix = malloc(sizeof(int*)*g->V);
    for(int i=0; i < g->V; i++)
        matrix[i] = (int *)malloc(g->V*sizeof(int));

    for(int i = 0; i < g->V; i++)
        for(int j = 0; j < g->V; j++)
            matrix[i][j] = 0;
    
    for(int i = 0; i < g->V; i++){
        ListNode *cur = g->adj.list[i];
        while(cur != NULL){
            matrix[i][(cur->vertex)-1] = 1;
            cur = cur->next;
        }
    }
    g->type = ADJ_MATRIX;
    for(int i = 0; i < g->V; i++) free(g->adj.list[i]);
    free(g->adj.list);
    g->adj.matrix = matrix;

}

void calDegreeV(Graph g, int *degreeV)
{
	// Question 3
    // Write your code here
    if(g.type == ADJ_MATRIX){
        for(int i = 0; i < g.V; i++){
            int count = 0;
            for(int j = 0; j < g.V; j++){
                if(g.adj.matrix[i][j] ==  1) count++;
            }
            degreeV[i] = count;
        }
    }

    else{
        for(int i = 0; i < g.V; i++){
            ListNode *cur = g.adj.list[i];
            int count = 0;
            while(cur != NULL){
                count++;
                cur = cur->next;
            }
            degreeV[i] = count;
        }
    }
}
