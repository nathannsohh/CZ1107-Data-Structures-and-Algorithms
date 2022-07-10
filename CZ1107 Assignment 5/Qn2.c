#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);
int prec(char ch);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

int prec(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 
  
    case '*': 
    case '/': 
        return 2; 
  
    } 
    return -1; 
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    int i;
    char total[100] = "", rev[100];

    int count = 0, end;
    while(infix[count] != '\0')
        count++;
    
    end = count - 1;
    for(i = 0; i < count; i++){
        rev[i] = infix[end];
        end--;
    }
    rev[i] = '\0';
    i = 0;

    for(i = 0; rev[i] != '\0'; i++){
        if(rev[i] == '(') rev[i] = ')';
        else if(rev[i] == ')') rev[i] = '(';
    }

    Stack s;
    s.head = NULL;
    s.size = 0;

    for(i = 0; rev[i] != '\0'; i++){
        if(isdigit(rev[i])){
            strncat(total,&rev[i], 1);
            if(rev[i+1] == '+' || rev[i+1] == '-' || rev[i+1] == '*' || rev[i+1] == '/' || rev[i+1] == '(' || rev[i+1] == ')' || rev[i+1] == '\0'){
                char str[100]="";
                int k, count2 = 0;
                while (total[count2] != '\0'){
                    count2++;
                }
                k = count2 - 1;
                for (int l = 0; l < count2; l++){
                    str[l] = total[k];
                    k--;
                }
                insertNode(inExpLL, atoi(str), OPERAND);
                strcpy(total, "");
            }
        }
        else if(rev[i] == ')'){
            while(peek(s) != '('){
                insertNode(inExpLL, peek(s), OPT);
                pop(&s);
            }
            pop(&s);
        }
        else if(rev[i] == '('){
            push(&s, rev[i]);
        }
        else{
            while(!isEmptyStack(s) && peek(s) != '(' && prec(peek(s)) > prec(rev[i])){
                insertNode(inExpLL, peek(s), OPT);
                pop(&s);
            }
            push(&s, rev[i]);
        }
    }
    while(!isEmptyStack(s)){
        insertNode(inExpLL, peek(s), OPT);
        pop(&s);
    }
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}