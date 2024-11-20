/*BUDURAN Catalina-Andreea - 311 CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Tree.h"

TPixel **matrix(int rows, int columns ) {
    TPixel **matrix = (TPixel**)malloc(rows * sizeof(TPixel*));
    for (int i = 0;i < rows; i++) {
        matrix[i] = (TPixel*)malloc(columns * sizeof(TPixel));
    }
    return matrix;
}

int main(int argc, char *argv[]) {
    int size;
    TPixel **image;
    FILE *inputfile=NULL;
    FILE *outputfile=NULL;
    if (strcmp(argv[1], "-c1") == 0 || strcmp(argv[1], "-c2") == 0) {
        inputfile = fopen(argv[3], "rb");
        if(strcmp(argv[1], "-c2") == 0)
            outputfile = fopen(argv[4], "wb");
        else
            outputfile = fopen(argv[4], "w");
    } else 
        if (strcmp(argv[1], "-d") == 0) {
            inputfile = fopen(argv[2], "rb");
            outputfile = fopen(argv[3], "wb");
        }
    if(inputfile == NULL){
        printf("ERROR");
    }
    if (outputfile == NULL) {
        printf("ERROR output");
    }
    char tip_fisier[3];
    int width, height, max_val;
    fscanf(inputfile, "%s", tip_fisier);
    fgetc(inputfile);
    fscanf(inputfile, "%d %d", &width, &height);
    fgetc(inputfile);
    fscanf(inputfile, "%d\n", &max_val);

    image = (TPixel**)malloc(height * sizeof(TPixel*));
    for (int i = 0;i < height; i++) {
        image[i] = (TPixel*)malloc(width * sizeof(TPixel));
        }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            fread(&image[i][j].red, sizeof(unsigned char), 1, inputfile);
            fread(&image[i][j].green, sizeof(unsigned char), 1, inputfile);
            fread(&image[i][j].blue, sizeof(unsigned char), 1, inputfile);
        } 
    int nr_frunze = 0, dimensiune = 0, factor;
    TreeNode *node;
    factor = atoi(argv[2]);
    if (strcmp(argv[1], "-c1") == 0) {
        createTree(&node, image, 0, 0, height, &nr_frunze, &dimensiune, factor);
        fprintf(outputfile, "%d\n", DFS(node));
        fprintf(outputfile, "%d\n%d\n", nr_frunze, dimensiune);
    }
    if (strcmp(argv[1], "-c2") == 0) {
        createTree(&node, image, 0, 0, height, &nr_frunze, &dimensiune, factor);
        BFS(node, outputfile, height);
    }
    
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}
