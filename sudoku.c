#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) 
{
    int i;
    int j;
    int num;
    for (i = 0; i < 9; i++) 
    {
        int revisarfila[10] = {0};  
        for (j = 0; j < 9; j++) {
            num = n->sudo[i][j];
            if (num != 0) {  
                if (revisarfila[num] == 1) 
                {  
                    return 0;
                }
                revisarfila[num] = 1;  
            }
        }
    }
    
    for (j = 0; j < 9; j++) {
        int revisarcol[10] = {0};  
        for (i = 0; i < 9; i++) {
            num = n->sudo[i][j];
            if (num != 0) { 
                if (revisarcol[num] == 1) 
                {  
                    return 0;
                }
                revisarcol[num] = 1; 
            }
        }
    }
    
    for (int k = 0; k < 9; k++) 
    {
        int revisarsubmatriz[10] = {0};  
        for (int p = 0; p < 9; p++) 
        {
            int i = 3 * (k / 3) + (p / 3);  
            int j = 3 * (k % 3) + (p % 3);  
            
            num = n->sudo[i][j];
            if (num != 0) 
            {  
                if (revisarsubmatriz[num] == 1) 
                {  
                    return 0;
                }
                revisarsubmatriz[num] = 1; 
            }
        }
    }

    return 1;  
}


List* get_adj_nodes(Node* n)
{
  List* list=createList();

  int fila = -1;
  int col = -1;
  for (int i = 0; i < 9 && fila == -1; i++) 
  {
    for (int j = 0; j < 9 && col == -1; j++) 
    {
      if (n->sudo[i][j] == 0) {  
        fila = i;
        col = j;
        break;  
      }
    }
  }

  if (fila == -1 || col == -1) 
  {
    return list;
  }

  for (int k = 1; k <= 9; k++) 
  {
    Node* copia = copy(n);  
    copia->sudo[fila][col] = k;  
    

    if (is_valid(copia)) {  
      pushBack(list, copia);  
    } else {
      free(copia);  
    }
  }
    
    return list;
}


int is_final(Node* n){
    if (n == NULL) return 0;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
        {
            if (n->sudo[i][j] == 0) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* n, int* cont)
{
    if (cont) *cont = 0;
    if (n == NULL) return NULL;

    Stack* pila = createStack();
    push(pila, n);

    while (!is_empty(pila))
    {
        Node* actual = (Node*) top(pila);
        pop(pila);
        if (cont) (*cont)++;

        if (is_final(actual)) return actual;

        List* adj = get_adj_nodes(actual);
        Node* aux = (Node*) firstList(adj);
        while (aux != NULL) 
        {
        push(pila, aux);
        aux = (Node*) nextList(adj);
        }

        free(actual);
    }
    return NULL;  
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/