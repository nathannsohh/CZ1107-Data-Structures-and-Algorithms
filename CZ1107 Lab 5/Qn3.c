#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int prec(char ch);

void in2Pre(char*, char*);

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Pre(infix,prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);

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

void in2Pre(char* infix, char* prefix)
{
 // Write your code here
 Stack temp;
    temp.head = NULL;
    temp.size = 0;

    int i,j, count = 0, index = 0,end;
    char rev[100];
    while(infix[count] != '\0')
        count++;
    
    end = count - 1;
    for(i = 0; i < count; i++){
        rev[i] = infix[end];
        end--;
    }
    rev[i] = '\0';
    i = 0;
    while(rev[i] != '\0'){
        if(rev[i] == '(') rev[i] = ')';
        else if(rev[i] == ')') rev[i] = '(';
        i++;
    }

    for(i = 0; rev[i] != '\0'; i++){
        if(rev[i] != '+' && rev[i] != '-' && rev[i] != '*' && rev[i] != '/' && rev[i] != ')' && rev[i] != '('){
            *(prefix + index) = rev[i];
            index++;
        }
        else if(rev[i] == ')'){
            while(peek(temp) != '('){
                *(prefix + index) = peek(temp);
                pop(&temp);
                index++;
            }
            pop(&temp);
        }
        else if(rev[i] == '(')
            push(&temp, rev[i]);
        else{
            while(!isEmptyStack(temp) && peek(temp) != '(' && prec(peek(temp)) > prec(rev[i])){ // take note of the > here
                *(prefix + index) = peek(temp);
                pop(&temp);
                index++;
            }
            push(&temp, rev[i]);            
        }
    }
    while(!isEmptyStack(temp)){
        *(prefix + index) = peek(temp);
                pop(&temp);
                index++;
    }
    *(prefix + index) = '\0';
    strrev(prefix);

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
