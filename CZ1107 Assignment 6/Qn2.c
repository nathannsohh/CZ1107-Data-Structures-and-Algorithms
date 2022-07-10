#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
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
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
   //Write your code here

   int compare = 0;
   int n = hash1(key);

//     for(int i = 0; i < TABLESIZE; i++){
//         int n = hash1(key + i*hash2(key));

//         if(hashTable[n].indicator == EMPTY){
//             hashTable[n].indicator = USED;
//             hashTable[n].key = key;
//             return compare;
//         }

//         else if(hashTable[n].indicator == DELETED){
//             for(int j = i+1; j < TABLESIZE; j++){
//                 int n2 = hash1(key + j*hash2(key));
//                 if(hashTable[n2].indicator == USED && hashTable[n2].key == key){
//                     compare++;
//                     return -1;
//                 }
//                 else if(hashTable[n2].indicator == USED){
//                     compare++;
//                     if(compare == TABLESIZE) return compare;
//                 }
//                 else if(hashTable[n2].indicator == EMPTY){
//                     break;
//                 }
//             }
//             hashTable[n].indicator = USED;
//             hashTable[n].key = key;
//             return compare;
//         }
//         else if(hashTable[n].key == key && hashTable[n].indicator == USED) return -1;
//         else if(hashTable[n].key != key && hashTable[n].indicator == USED) compare++;
//     }
//     if(compare == TABLESIZE) return compare;


    if(hashTable[n].indicator != USED){
        hashTable[n].key = key;
        hashTable[n].indicator = USED;
        return compare;
    }
    if(hashTable[n].key == key && hashTable[n].indicator == USED) return -1;

    compare++;
    
    while(compare != TABLESIZE){
        n = hash1((hash1(key) + compare*hash2(key)));
        if(hashTable[n].key == key && hashTable[n].indicator == USED) return -1;
        else if(hashTable[n].indicator == DELETED){
            for(int j = compare+1; j < TABLESIZE; j++){
                int n2 = hash1(key + j*hash2(key));
                if(hashTable[n2].indicator == USED && hashTable[n2].key == key){
                    compare++;
                    return -1;
                }
                else if(hashTable[n2].indicator == USED){
                    compare++;
                    if(compare == TABLESIZE) return compare;
                }
                else if(hashTable[n2].indicator == EMPTY){
                    break;
                }
            }
            hashTable[n].key = key;
            hashTable[n].indicator = USED;
            return compare;
        }
        compare++;
    }
    return compare;

}

int HashDelete(int key, HashSlot hashTable[])
{
   //Write your code here
    int compare = 1;
    int n = hash1(key);

    if(hashTable[n].key == key && hashTable[n].indicator != DELETED){
        hashTable[n].indicator = DELETED;
        return compare;
    }

    while(compare != TABLESIZE){
        n = hash1((hash1(key) + compare*hash2(key)));
        if(hashTable[n].key == key && hashTable[n].indicator != DELETED){
            hashTable[n].indicator = DELETED;
            return compare+1;
        }
        compare++;
    }
    return -1;

}
