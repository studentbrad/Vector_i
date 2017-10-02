/*
________________________________________________________
|                 INT VECTOR LIBRARY                    |
|                    HEADER FILE                        |
|                 BY: BRADLEY KOHLER                    |
|                                                       |
|                                                       |
|_______________________________________________________|

*/

/*----------Includes-----------*/

#include <stdio.h>
#include <stdlib.h>

/*----------Structures---------*/

//One dimentional array structure
typedef struct{
int *array;
size_t size;
} array;

//Two dimentional array structure
typedef struct{
int **darray;
size_t row_size;
size_t column_size;
} darray;

//Two dimentional spider array structure
typedef struct{
int **sparray;
size_t row_size;
size_t *column_size;
}sparray;

/*----------Private Functions--*/

int POW_10(int exp);

/*----------Functions----------*/

//Initialize a one dimentional array
void initArray(array *a, size_t initial_size);
//Initialize a two dimentional array
void initDArray(darray *da, size_t initial_row_size, size_t initial_column_size);
//Initialize a two dimentional spider array
void initSpArray(sparray *sp, size_t initial_row_size, size_t *initial_column_size);
//Build a one dimentional array from a file
void buildArray(array *a, char * file_name);
//Build a two dimentional array from a file
void buildDArray(darray *da, char * file_name);
//Build a two dimentional spider array from a file
void buildSpArray(sparray *sp, char * file_name);
//Write a one dimentional array to a file
void writeArray(array *a, char * file_name);
//Write a two dimentional array to a file
void writeDArray(darray *da, char * file_name);
//Write a two dimentional spider array to a file
void writeSpArray(sparray *sp, char * file_name);
//Append to a one dimetional array
void appendArray(array *a, int append);
//Append to a two dimentional array row
void appendDArrayRow(darray *da, int append, int row_num);
//Append to a to dimentional array column
void appendDArrayColumn(darray *da, int append, int column_num);
//Insert to a one dimentional array
void insertArray(array *a, int ins, int loc);
//Insert to a two dimentional array
void insertDArray(darray *da, int ins, int row, int column);
//Insert to a two dimentional spider array
void insertSpArray(sparray *sp, int ins, int row, int column);
//Free a one dimentional array
void freeArray(array *a);
//Free a two dimentional array
void freeDArray(darray *da);
//Free a two dimentional spider array
void freeSpArray(sparray *sp);
//Print a one dimentional array
void printArray(array *a);
//Print a two dimentional array
void printDArray(darray *da);
//Get an element from a one dimentional array
int returnArrayElement(array *a , int pos);
//Get an element from a two dimentional array
int returnDArrayElement(darray *da, int row, int column);
//Get a pointer to an element in a one dimentional array
int* returnArrayPointerElement(array *a, int pos);
//Get a pointer to an element in a two dimentional array
int* returnDArrayPointerElement(darray *da, int row, int column);
//Multiply two, one dimentional arrays
void multiplyArray(array *a1 ,array *a2 ,array *ans);
//Multiply two, two dimentional arrays
void multiplyDArray(darray *da1, darray *da2, darray *ans);
//Add two, one dimentional arrays
void addArray(array *a1 ,array *a2 ,array *ans);
//Add two, two dimentional arrays
void addDArray(darray *da1, darray *da2, darray *ans);
//Subtract two, one dimentional arrays
void subtractArray(array *a1 ,array *a2,array *ans);
//Subtract two, two dimentional arrays
void subtractDArray(darray *da1, darray *da2, darray *ans);
