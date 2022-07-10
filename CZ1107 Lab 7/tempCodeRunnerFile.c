if(g->adj.matrix[i][j] == 1){
            ListNode *cur, *newNode;
            cur = temp.adj.list[i];
            if(cur->vertex == -1){
                cur->vertex = j+1;
                printf("%d", cur->vertex);
            } 
            else{
                while(cur != NULL) cur = cur->next;
                newNode = malloc(sizeof(newNode));
                newNode->vertex = j+1;
                newNode->next = NULL;
                cur = newNode;
            }
        }