/*BUDURAN Catalina-Andreea - 311 CD*/
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pixel{
   unsigned char red, green, blue;
} TPixel;

typedef struct node {
    int type;
    int nivel;
    int x, y;
    // int size;
    float red, green, blue;
    struct node *children[4];
} TreeNode, *Tree;

void createTree(TreeNode *node, TPixel **grid, int x, int y, long long size, int *num_frunze, int *dimensiune, int factor) {
    unsigned long long suma = 0, red = 0, green = 0, blue = 0, mean;
    double red2 = 0, green2 = 0, blue2 = 0;
    node =(Tree)malloc(sizeof(TreeNode));
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++) {
            red = red + (int)grid[i][j].red;
            green = green + (int)grid[i][j].green;
            blue = blue + (int)grid[i][j].blue;
        }
    red  = red / (size * size);
    green  = green / (size * size);
    blue  = blue / (size * size);
    for (int i = x; i < x + size; i++){
        for (int j = y; j < y + size; j++){
            unsigned long long a = (unsigned long long )(red - grid[i][j].red);
            long long  b = (long long )(green - grid[i][j].green);
            long long  c = (long long )(blue - grid[i][j].blue);
            suma += a*a + b*b +c*c;
        }
    }
    printf("%lld\n", size);
    double mean2 = suma / (size * 1.0);
    mean = floor(mean2);
    mean2 = mean / (size * 1.0);
    mean = floor(mean2);
    mean2  = mean / 3.0;
    mean = floor(mean2);
    if (mean <= factor) { //nodul curent devine frunza
        node->type = 1;
        node->red = red;
        node->green = green;
        node->blue = blue;
        (*num_frunze)++;
        if (size > (*dimensiune))
            *dimensiune = size;
        return;
    } 
  //nodul curent are copii
        createTree(node->children[0], grid, x, y, size/2, num_frunze, dimensiune, factor);
        createTree(node->children[1], grid, x, y + size/2, size/2, num_frunze, dimensiune, factor);
        createTree(node->children[2], grid, x + size/2, y + size/2, size/2, num_frunze, dimensiune, factor);
        createTree(node->children[3], grid, x + size/2, y, size/2, num_frunze, dimensiune, factor);
    
}

int DFS(Tree root) {
    if (root == NULL || (root->children[0] == NULL && root->children[1] == NULL && root->children[2] == NULL && root->children[3] == NULL))
        return 0;
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