//stack_arr.h
//Add documentation including Pre and Post conditions for functions

#include <stdio.h>
#include <stdbool.h>
//#include "stack_ll.h"
#include <stdlib.h>
#include <string.h>


typedef struct Pixel {
    int row;
    int col;
    char color;
} Pixel;

FILE *fptr;
char grid[25][25];
Pixel chosenPixel;
int numRows = 0;
int numCols = 0;
int selectedRow = 0;
int selectedCol = 0;

bool validityCheck(Pixel currentPixel){
    if(selectedRow == -1){
        exit(-1);
    }
    if(selectedRow < 1 || selectedRow > numRows){
        printf("\n""%s""\n""\n", "Invalid Row Selection");
        return false;
    }
    if(selectedCol == -1){
        exit(-1);
    }
    if(selectedCol < 1 || selectedCol > numCols){
        printf("\n""%s""\n""\n", "Invalid Column Selection");
        return false;
    }

    if(grid[currentPixel.row][currentPixel.col] == currentPixel.color){
        printf("\n""%s""\n""\n", "Location already floodfilled");
        return false;
    }
    return true;
}

void printPicture(int i){
    if (i == numRows){
        return;
    }
    printf("%s", grid[i]);
    i++;
    printPicture(i);
}

void filePrint(int i) {

        if (fgets(grid[i], sizeof(grid), fptr) != NULL) {
            printf("%s", grid[i]);
            numRows++;
            numCols = strlen(*grid) - 1;
            i++;
            filePrint(i);
        }
    }

void file(){

}

void changePicture(int currentRow, int currentCol, char correctColor, char colorToChange){
    if (grid[currentRow+1][currentCol] == colorToChange){
        grid[currentRow][currentCol] = correctColor;
        changePicture(currentRow+1, currentCol, correctColor, colorToChange);
    }
    if (grid[currentRow-1][currentCol] == colorToChange){
        grid[currentRow][currentCol] = chosenPixel.color;
        changePicture(currentRow-1, currentCol, correctColor, colorToChange);
    }
    if (grid[currentRow][currentCol+1] == colorToChange){
        grid[currentRow][currentCol] = correctColor;
        changePicture(currentRow, currentCol+1, correctColor, colorToChange);
    }
    if (grid[currentRow][currentCol-1] == colorToChange){
        grid[currentRow][currentCol] = chosenPixel.color;
        changePicture(currentRow, currentCol-1, correctColor, colorToChange);
    }
    if (grid[currentRow+1][currentCol+1] == colorToChange){
        grid[currentRow][currentCol] = correctColor;
        changePicture(currentRow+1, currentCol+1, correctColor, colorToChange);
    }
    if (grid[currentRow-1][currentCol-1] == colorToChange){
        grid[currentRow][currentCol] = chosenPixel.color;
        changePicture(currentRow-1, currentCol-1, correctColor, colorToChange);
    }
    if (grid[currentRow+1][currentCol-1] == colorToChange){
        grid[currentRow][currentCol] = correctColor;
        changePicture(currentRow+1, currentCol-1, correctColor, colorToChange);
    }
    if (grid[currentRow-1][currentCol+1] == colorToChange){
        grid[currentRow][currentCol] = chosenPixel.color;
        changePicture(currentRow-1, currentCol+1, correctColor, colorToChange);
    }
    grid[currentRow][currentCol] = correctColor;
    return;
}


void userSelection(){
    selectedRow = 0;
    selectedCol = 0;
    printf("Enter a row: ");
    scanf(" %d", &selectedRow);
    chosenPixel.row = selectedRow - 1;
    printf("Enter a column: ");
    scanf(" %d", &selectedCol);
    chosenPixel.col = selectedCol - 1;
    printf("Enter a color: ");
    scanf(" %c", &chosenPixel.color);
}

int main(int argc, char *argv[]){
    char fname[BUFSIZ];
    strcpy(fname, argv[1]);
    fptr = fopen(fname, "r");

    if (fptr == NULL) { //Error code if file does not open properly
        printf("error\n");
        exit(-1);
    }
    filePrint(0);
    printf("\n""\n");
    while(1) {
        userSelection();
        if (validityCheck(chosenPixel)) {
            Pixel currentPixel = {chosenPixel.row, chosenPixel.col, grid[chosenPixel.row][chosenPixel.col]};
            changePicture(currentPixel.row, currentPixel.col, chosenPixel.color, currentPixel.color);
        }
        printf("\n");
        printPicture(0);
        printf("\n""\n");
    }


    return 0;
}