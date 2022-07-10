#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char*);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    gets(postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}


double exePostfix(char* postfix)
{
	// Write your code here
    Stack temp;
    temp.head = NULL;
    temp.size = 0;

    double op1, op2, result;
    
    for(int i = 0; *(postfix + i) != '\0'; i++){
        
        if(*(postfix+i) != '+' && *(postfix+i) != '-' && *(postfix+i) != '*' && *(postfix+i) != '/'){
            push(&temp, (*(postfix+i) - '0'));
        }
        else{
            op1 = peek(temp);
            pop(&temp);
            op2 = peek(temp);
            pop(&temp);
            if(*(postfix+i) == '+') result = op2 + op1;
            else if(*(postfix+i) == '-') result = op2 - op1;
            else if(*(postfix+i) == '*') result = op2 * op1;
            else if(*(postfix+i) == '/') result = op2 / op1;
            push(&temp, result);
        }
    }
    result = peek(temp);
    return result;
}

void push(Stack *sPtr, double item){
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

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
