//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);
	printf("\n");

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	// write your code here
	BTNode *temp;
	
	if(*node == NULL){
	*node = malloc(sizeof(BTNode));
	(*node)->item = value;
	(*node)->left = NULL;
	(*node)->right = NULL;
	return;
	}
	if((*node)->item < value)
		insertBSTNode(&((*node)->right), value);
	else if((*node)->item > value)
		insertBSTNode(&((*node)->left), value);

}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	// write your code here
	if(node==NULL){
		return;
	}
	printBSTInOrder(node->left);
	printf("%d ", node->item);
	printBSTInOrder(node->right);
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	// write your code here
	// if(min < node->item < max || node == NULL) return 1;

	// if(node->left!=NULL)
	// 	min = node->left->item;
	// else min = -1000000;

	// if(node->right!=NULL)
	// 	max = node->right->item;
	// else max = 1000000;
	
	// if(min > node->item)
	// 	return 0;
	// if(max < node->item)
	// 	return 0;
	// if(!isBST(node->left,min,max) || !isBST(node->right, min, max));
	// 	return 0;

	// return 1;

	if(node == NULL) return 1;
	if(node->item >= max && node->item <= min) return 0;

	return isBST(node->left, min, node->item) && isBST(node->right, node->item, max);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// write your code here
	BTNode *cur;
	cur = node;

	//getting the node with value
	while(cur->item!=value){
		if(value < cur->item) 
			cur = cur->left;
		else
			cur = cur->right;
	}

	if(cur->left == NULL && cur->right == NULL)
		cur = NULL;
	
	
		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////