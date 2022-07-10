#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

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
int prec(char ch); // i added this

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
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

void in2Post(char* infix, char* postfix)
{
    // Write your code here
    Stack temp;
    temp.head = NULL;
    temp.size = 0;

    int i, index = 0;
    for(i = 0; *(infix + i) != '\0'; i++){
        if(*(infix+i) != '+' && *(infix+i) != '-' && *(infix+i) != '*' && *(infix+i) != '/' && *(infix + i) != ')' && *(infix + i) != '('){
            *(postfix + index) = *(infix+i);
            index++;
        }
        else if(*(infix + i) == ')'){
            while(peek(temp) != '('){
                *(postfix + index) = peek(temp);
                pop(&temp);
                index++;
            }
            pop(&temp);
        }
        else if(*(infix + i) == '(')
            push(&temp, *(infix + i));
        else{
            while(!isEmptyStack(temp) && peek(temp) != '(' && prec(peek(temp)) >= prec(*(infix+i))){
                *(postfix + index) = peek(temp);
                pop(&temp);
                index++;
            }
            push(&temp, *(infix+i));            
        }
    }
    while(!isEmptyStack(temp)){
        *(postfix + index) = peek(temp);
                pop(&temp);
                index++;
    }
    *(postfix + index) = '\0';
   
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
