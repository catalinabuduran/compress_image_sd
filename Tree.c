/*BUDURAN Catalina-Andreea - 311 CD*/
#ifndef _TREE_C_
#define _TREE_C_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Tree.h"

void meanRGB(TPixel **grid, unsigned long long *red, unsigned long long *green, unsigned long long *blue, int x, int y, int size){
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++) {
            *red = *red + grid[i][j].red;
            *green = *green + grid[i][j].green;
            *blue = *blue + grid[i][j].blue;
        }
    *red  = floor(*red / (size * size));
    *green  = floor(*green / (size * size));
    *blue  = floor(*blue / (size * size));
}

void createTree(TreeNode **node, TPixel **grid, int x, int y, long long size, int *num_frunze, int *dimensiune, int factor) {
    unsigned long long suma = 0, red = 0, green = 0, blue = 0, mean;
    *node =(Tree)malloc(sizeof(TreeNode));
    meanRGB(grid, &red, &green, &blue, x, y, size);
    for (int i = x; i < x + size; i++){
        for (int j = y; j < y + size; j++){
            int a = (int)(red - grid[i][j].red);
            int b = (int)(green - grid[i][j].green);
            int c = (int)(blue - grid[i][j].blue);
            suma = suma + a*a + b*b +c*c;
        }
    }
    mean = floor(suma / (3.0 * size * size));
    if (mean <= factor) {
        (*node)->type = 1;
        (*node)->red = red;
        (*node)->green = green;
        (*node)->blue = blue;
        (*num_frunze)++;
        if (size > (*dimensiune))
            *dimensiune = size;
        return;
    } 
    (*node)->type = 0;
    createTree(&(*node)->children[0], grid, x, y, size/2, num_frunze, dimensiune, factor);
    createTree(&(*node)->children[1], grid, x, y + size/2, size/2, num_frunze, dimensiune, factor);
    createTree(&(*node)->children[2], grid, x + size/2, y + size/2, size/2, num_frunze, dimensiune, factor);
    createTree(&(*node)->children[3], grid, x + size/2, y, size/2, num_frunze, dimensiune, factor);
    
}

int DFS(Tree root) {
    if (root == NULL || (root->children[0] == NULL && root->children[1] == NULL && root->children[2] == NULL && root->children[3] == NULL))
        return 1;
    int maxim = 0, nivel[4];
    for (int i = 0; i < 4; i++) {
        nivel[i] = DFS(root->children[i]);
    }
    for (int i = 0; i < 4; i++) {
        if (nivel[i] > maxim)
            maxim = nivel[i];
    }
    return maxim + 1;
}

void destroy_queue(struct node **queue) {
    for (int i = 0; i < 4; i++) {
        free(queue[i]);
    }
    free(queue);
}

void BFS(Tree root, FILE *file, int size) {
    fwrite(&(size), sizeof(int), 1, file);
    struct node **queue = (struct node **)malloc(sizeof(struct node *));
    int front = 0, rear = 0;
    if (root == NULL) {
      return;
   }
   queue[rear] = root;
   while (front <= rear) {
        struct node *node_curent = queue[front++];
        if (node_curent->type == 1) {
            fwrite(&(node_curent->type), sizeof(unsigned char), 1, file);
            fwrite(&(node_curent->red), sizeof(unsigned char), 1, file);
            fwrite(&(node_curent->green), sizeof(unsigned char), 1, file);
            fwrite(&(node_curent->blue), sizeof(unsigned char), 1, file);
        }    
        if (node_curent->type == 0) {
            fwrite(&(node_curent->type), sizeof(unsigned char), 1, file);
            for (int i = 0; i < 4; i++) {
                if (node_curent->children[i] != NULL) {
                    queue = (struct node **)realloc(queue, (rear + 2) * sizeof(struct node *));
                    queue[++rear] = node_curent->children[i];          
                }
            }
        }
    }
   // destroy_queue(queue);
}


#endif
