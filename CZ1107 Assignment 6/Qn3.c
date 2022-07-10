#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
 // Write your code here
    for(int i = 0; i < TABLESIZE; i++){
        if(hashTable[i].key == key && hashTable[i].indicator == USED) return -1;
    }

    int n = hash(key);
    if(hashTable[n].indicator == EMPTY){
        hashTable[n].key = key;
        hashTable[n].indicator = USED;
        return n;
    }

    else{
        int n2 = n, i = 0;
        while(hashTable[n2].indicator != EMPTY){ // to get the empty bucket with linear probing
            n2 = hash(n + i);
            i++;
            if(i == TABLESIZE) return i;
        }

        while(hashTable[n].next != -1) //to get the index with next = -1
            n = hashTable[n].next;
        
        hashTable[n2].key = key;
        hashTable[n2].indicator = USED;
        hashTable[n].next = n2;
        return n2;
    }
}

int HashFind(int key, HashSlot hashTable[])
{
 // Write your code here
    int n = hash(key);
    while(hashTable[n].key != key){
        n = hashTable[n].next;
        if(n == -1) return -1;
    }
    return n;
}