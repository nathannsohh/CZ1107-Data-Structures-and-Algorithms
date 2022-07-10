#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

void sumToC(LinkedList* ll, int C, ArrayList* al)
{
   //3 cases to tackle! Sum<C, Sum>C, Sum==C
    ListNode *curLL1, *curLL2;

    ArrayNode *curAL;
    curAL = al->head;

    int i, i2;

    if(ll->sum == C) //CASE 1 !!!
        {
         if(al->size==0) //when AL is empty
            {
               al->head = malloc(sizeof(ArrayNode));
               al->head->next = NULL;
               al->head->sizeArray= ll->size;
               al->head->itemArray = malloc(sizeof(int)*(ll->size));
                i = (ll->size)-1;
                curLL1 = ll->head;
                while(curLL1 != NULL)
                 {
                    (al->head)->itemArray[i] = (curLL1)->item;
                    curLL1 = (curLL1)->next;
                    i--;
                 }
               (al->size)++;
            }

            else // AL not empty
            {
                while(curAL->next != NULL) //move to next available spot
                {
                    curAL = curAL->next;
                }
                curAL = malloc(sizeof(ArrayNode)); //create space on AL
                curAL->next = NULL;
                curAL->sizeArray= ll->size;
                curAL->itemArray = malloc(sizeof(int)*(ll->size));

                curLL2 = ll->head;
                i2 = (ll->size)-1;
//                while(curLL2 != NULL)
//                 {
//                    (curAL)->itemArray[i2] = (curLL2)->item;
//                    curLL2 = (curLL2)->next;
//                    i2--;
//                 }
                (al->size)++;
            }
            return;
        }

    if(ll->sum > C) //CASE 2 !!!
        return;

    int m;
    for(m=1;m<=C;m++)
    {
        if(ll->head == NULL)
            insertNode(ll,0,m); //adding in the first node
        else
        {
            if((ll->head)->item >= m)
                continue;
            else
                insertNode(ll,0,m);
        }

        sumToC(ll,C,al); //recursive function
        removeNode(ll,0);

    }//end of for loop

}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
	ll->sum =0;
}
