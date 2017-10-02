/*
________________________________________________________
|                 INT VECTOR LIBRARY                    |
|                       C FILE                          |
|                 BY: BRADLEY KOHLER                    |
|                                                       |
|                                                       |
|_______________________________________________________|

*/

/*----------Includes-----------*/

#include "vector_i.h"

/*----------Private Functions--*/


int POW_10(int exp){
int i;
int output=1;
if(exp>0){
	for(i=0 ; i<exp ; i++){
		output = output*10;
	}
}
else{
	output = 1;
}
return output;
}

/*----------Functions----------*/

//Initialize a one dimentional array
/*
Used to initialize a one dimentional array (typedef struct array)
Values are initialized to 0
*/
void initArray(array *a, size_t initial_size){
a->array = (int *) malloc(initial_size * sizeof(int));
a->size = initial_size;
}

//Initialize a two dimentional array
/*
Used to initialize a two dimentional array (typedef struct darray)
Values are initialized to 0
*/
void initDArray(darray *da, size_t initial_row_size, size_t initial_column_size){
int i;
da->darray = (int **) malloc(initial_row_size * sizeof(int *));
da->row_size = initial_row_size;
for (i = 0 ; i < da->row_size ; i++){
	da->darray[i] = (int *) malloc(initial_column_size * sizeof(int));
	da->column_size = initial_column_size;
}
}

//Initialize a two dimentional spider array
/*
Used to initialize a two dimentional spider array (typedef struct sparray)
Values are initialized to 0
*/
void initSpArray(sparray *sp, size_t initial_row_size, size_t *initial_column_size){
int i;
sp->sparray = (int**) malloc(initial_row_size * sizeof(int *));
sp->row_size = initial_row_size;
sp->column_size = (size_t *) malloc(sp->row_size * sizeof(size_t));
for (i = 0 ; i < sp->row_size ; i++){
	sp->sparray[i] = (int *) malloc(initial_column_size[i] *sizeof(int));
	sp->column_size[i] = initial_column_size[i];
}
}

//Build a one dimentional array from a file
/*
Used to build a one dimentional array from a file
*/
void buildArray(array *a, char * file_name){

FILE * file;
if((file = fopen(file_name, "r")) == NULL){
	perror("No file");
	return;
}

char temp;
int i, temp_int;

freeArray(a);
initArray(a,0);

array buffer;
initArray(&buffer,0);

while((fscanf(file , "%c" , &temp))!=EOF){

	if(temp!=' ' && temp!='\n'){
	appendArray(&buffer,(int) temp - 48);
	}

	else{
		temp_int = 0;
		for(i=0 ; i<buffer.size ; i++){
			temp_int = temp_int + buffer.array[i] * POW_10((buffer.size - i-1));
		}

		appendArray(a,temp_int);
		freeArray(&buffer);
		initArray(&buffer,0);
	}
}
}

//Build a two dimentional array from a file
/*
Used to build a two dimentional array from a file
*/
void buildDArray(darray *da, char * file_name){
FILE * file;
if((file = fopen(file_name, "r")) == NULL){
	perror("No file");
	return;
}

char temp;
int i, temp_int;
int row_count = 0;
int column_count = 0;

freeDArray(da);
initDArray(da,0,0);

array buffer;
initArray(&buffer,0);

while((fscanf(file , "%c" , &temp))!=EOF){

	if(temp!=' ' && temp != '\n'){
		appendArray(&buffer,((int) temp - 48));
	}

	else{

		temp_int = 0;
		for(i=0 ; i<buffer.size ; i++){
			temp_int = temp_int + buffer.array[i] * POW_10((buffer.size - i-1));
		}
			insertDArray(da,temp_int,row_count,column_count);
			freeArray(&buffer);
			initArray(&buffer,0);
			if(temp == ' '){
				column_count++;
			}
			else{
				column_count = 0;
				row_count++;
			}
	}

}
}

//Build a two dimentional spider array from a file
/*
Used to build a two dimentional spider array from a file
*/
void buildSpArray(sparray *sp, char * file_name){
FILE * file;
if((file = fopen(file_name, "r")) == NULL){
	perror("No file");
	return;
}

char temp;
int i, temp_int;
int row_count = 0;
int column_count = 0;

freeSpArray(sp);
initSpArray(sp,0,NULL);

array buffer;
initArray(&buffer,0);

while((fscanf(file , "%c" , &temp))!=EOF){

	if(temp!=' ' && temp != '\n'){
		appendArray(&buffer,((int) temp - 48));
	}

	else{

		temp_int = 0;
		for(i=0 ; i<buffer.size ; i++){
			temp_int = temp_int + buffer.array[i] * POW_10((buffer.size - i-1));
		}
			insertSpArray(sp,temp_int,row_count,column_count);
			freeArray(&buffer);
			initArray(&buffer,0);
			if(temp == ' '){
				column_count++;
			}
			else{
				column_count = 0;
				row_count++;
			}
	}

}
}


//Write a one dimentional array to a file
/*
Used to write a one dimentional array to file
*/
void writeArray(array *a, char * file_name){
FILE * file;
if((file = fopen(file_name, "w")) == NULL){
	perror("No file");
	return;
}

int i,k;
int count=0;

array buffer , temp_buffer;
initArray(&buffer,0);
initArray(&temp_buffer,0);


for(i = 0 ; i < a->size ; i++){

	//Appending process to buffer
	if(a->array[i] == 0){
		appendArray(&buffer,a->array[i]);
	}

	while(a->array[i]/POW_10(count)!=0){
		appendArray(&buffer,a->array[i]%POW_10(count+1));
		count++;
	}

	count = 0;

	//Subtraction process to buffer
	for(k = buffer.size ; k > 0 ; k--){
		buffer.array[k] = buffer.array[k]-buffer.array[k-1];
	}

	freeArray(&temp_buffer);
	initArray(&temp_buffer,buffer.size);

	//Copy process from buffer to temp_buffer
	for(k = 0 ; k < buffer.size ;k++){
		temp_buffer.array[k] = buffer.array[k];
	}

	//Inversion process to buffer
	for(k = 0 ; k < buffer.size ; k++){
		buffer.array[k] = temp_buffer.array[temp_buffer.size-k-1];
	}

	freeArray(&temp_buffer);

	count = 0;

	//Division process to buffer
	for(k = 0 ; k < buffer.size ; k++){
		buffer.array[k] = buffer.array[k]/(POW_10(buffer.size-k-1));
	}

	//Writing process from buffer to file
	for(k = 0 ; k < buffer.size ; k++){
		fputc((char) buffer.array[k]+48, file);
	}

	freeArray(&buffer);
	initArray(&buffer,0);

	if(i<(a->size-1)){
	fputc(' ', file);
	}
}

}

//Write a two dimentional array to a file
/*
Used to write a two dimentional array to a file
*/
void writeDArray(darray *da, char * file_name){
FILE * file;
if((file = fopen(file_name, "w")) == NULL){
	perror("No file");
	return;
}

int i,j,k;
int count=0;

array buffer , temp_buffer;
initArray(&buffer,0);
initArray(&temp_buffer,0);

for(i = 0 ; i < da->row_size ; i++){
	for(j = 0 ; j < da->column_size ; j++){

		//Appending process to buffer
		if(da->darray[i][j] == 0){
			appendArray(&buffer,da->darray[i][j]);
		}

		while(da->darray[i][j]/POW_10(count)!=0){
			appendArray(&buffer,da->darray[i][j]%POW_10(count+1));
			count++;
		}


		count = 0;

		//Subtraction process to buffer
		for(k = buffer.size ; k > 0 ; k--){
			buffer.array[k] = buffer.array[k]-buffer.array[k-1];
		}

		freeArray(&temp_buffer);
		initArray(&temp_buffer,buffer.size);

		//Copy process from buffer to temp_buffer
		for(k = 0 ; k < buffer.size ;k++){
			temp_buffer.array[k] = buffer.array[k];
		}

		//Inversion process to buffer
		for(k = 0 ; k < buffer.size ; k++){
			buffer.array[k] = temp_buffer.array[temp_buffer.size-k-1];
		}

		freeArray(&temp_buffer);

		count = 0;

		//Division process to buffer
		for(k = 0 ; k < buffer.size ; k++){
			buffer.array[k] = buffer.array[k]/(POW_10(buffer.size-k-1));
		}

		//Writing process from buffer to file
		for(k = 0 ; k < buffer.size ; k++){
			fputc((char) buffer.array[k]+48, file);
		}

		freeArray(&buffer);
		initArray(&buffer,0);

		if(j<(da->column_size-1)){
			fputc(' ', file);
		}
		else if(j == da->column_size-1){
			fputc('\n', file);
		}
	}
}
}

//Write a two dimentional spider array to a file
/*
Used to write a two dimentional spider array to a file
*/
writeSpArray(sparray *sp, char * file_name){
FILE * file;
if((file = fopen(file_name, "w")) == NULL){
	perror("No file");
	return;
}

int i,j,k;
int count = 0;

array buffer , temp_buffer;
initArray(&buffer,0);
initArray(&temp_buffer,0);

for(i = 0 ; i < sp->row_size ; i++){
	for(j = 0 ; j < sp->column_size[i] ; j++){

		//Appending process to buffer
		if(sp->sparray[i][j] == 0){
			appendArray(&buffer,sp->sparray[i][j]);
		}

		while(sp->sparray[i][j]/POW_10(count)!=0){
			appendArray(&buffer,sp->sparray[i][j]%POW_10(count+1));
			count++;
		}

		//Subtraction process to buffer
		for(k = buffer.size ; k > 0 ; k--){
			buffer.array[k] = buffer.array[k]-buffer.array[k-1];
		}

		freeArray(&temp_buffer);
		initArray(&temp_buffer,buffer.size);

		//Copy process from buffer to temp_buffer
		for(k = 0 ; k < buffer.size ;k++){
			temp_buffer.array[k] = buffer.array[k];
		}

		//Inversion process to buffer
		for(k = 0 ; k < buffer.size ; k++){
			buffer.array[k] = temp_buffer.array[temp_buffer.size-k-1];
		}

		freeArray(&temp_buffer);

		count = 0;

		//Division process to buffer
		for(k = 0 ; k < buffer.size ; k++){
			buffer.array[k] = buffer.array[k]/(POW_10(buffer.size-k-1));
		}

		//Writing process from buffer to file
		for(k = 0 ; k < buffer.size ; k++){
			fputc((char) buffer.array[k]+48, file);
		}

		freeArray(&buffer);
		initArray(&buffer,0);

		if(j<(sp->column_size[i]-1)){
			fputc(' ', file);
		}
		else if(j == sp->column_size[i]-1){
			fputc('\n', file);
		}
	}
}
}

//Append to a one dimetional array
/*
Used to append a single int to the end of a one dimentional array
*/
void appendArray(array *a, int append){
a->size++;
a->array = (int *) realloc(a->array, a->size * sizeof(int));
a->array[a->size - 1] = append;
}

//Append to a two dimentional array row
/*
Used to append a single int to the end of a two dimentional array row
row_size is increased by 1
new values are initialized to zero
*/
void appendDArrayRow(darray *da, int append, int row_num){
int i;
da->column_size++;
for (i = 0 ; i < da->row_size ; i++){
	da->darray[i] = (int *) realloc(da->darray[i], da->column_size * sizeof(int));
	if (i == row_num){
		da->darray[i][da->column_size - 1] = append;
	}
	else{
		da->darray[i][da->column_size-1] = 0;
	}
}
}

//Append to a to dimentional array column
/*
Used to append a single int to the end of a two dimentional array column
column_size is increased by 1
new values are initialized to zero
*/
void appendDArrayColumn(darray *da, int append, int column_num){
int i;
da->row_size++;
da->darray = (int **) realloc(da->darray, da->row_size * sizeof(int *));
da->darray[da->row_size-1] = (int *) malloc(da->column_size * sizeof(int));
for (i = 0 ; i < da->column_size ; i++){
	da->darray[da->row_size-1][i] = 0;
}
da->darray[da->row_size-1][column_num] = append;
}

//Insert to a one dimentional array
/*
Used to insert to a one dimentional array at loc
ins overwrites the value of the one dimentional array at loc
*/
void insertArray(array *a, int ins, int loc){
int i = 0;
int olsize = a->size;
if(loc >= a->size){
	a->size = (size_t) loc+1;
	a->array = (int *) realloc(a->array, a->size * sizeof(int));

	for(i = olsize; i < a->size; i++){
		a->array[i] = 0;
	}
	a->array[loc] = ins;
	}
else{
a->array[loc] = ins;
}
}

//Insert to a two dimentional array
/*
Used to insert to a two dimentional array at row, column
ins overwrites the value of the two dimentional array at row, column
*/
void insertDArray(darray *da, int ins, int row, int column){
int i, j;
int olrowsize = da->row_size;
int olcolumnsize = da->column_size;
	if(row >= da->row_size){
		da->row_size = row+1;
		da->darray = (int **) realloc(da->darray, da->row_size * sizeof(int *));
		for(i = olrowsize ; i < da->row_size ; i++){
			da->darray[i] = (int *) malloc(da->column_size * sizeof(int));
			for(j = 0 ; j < da->column_size ; j++){
				da->darray[i][j] = 0;
			}
		}
	}

	if(column >= da->column_size){
		da->column_size = column+1;
		for(i = 0 ; i < da->row_size ; i++){
			da->darray[i] = (int *) realloc(da->darray[i], da->column_size * sizeof(int));
			for(j = olcolumnsize ; j < da->column_size ; j++){
				da->darray[i][j] = 0;
			}
		}
	}
da->darray[row][column] = ins;
}

//insert to a two dimentional spider array
void insertSpArray(sparray *sp, int ins, int row, int column){
//
int i,j;
int olrowsize = sp->row_size;
int * olcolumnsize;
olcolumnsize = malloc(olrowsize * sizeof(size_t));

for(i = 0 ; i < olrowsize ; i++){
	olcolumnsize[i] = sp->column_size[i];
}

//memcpy(olcolumnsize,&sp->column_size,sizeof(sp->column_size));
	if(row >= sp->row_size){

		sp->row_size = (size_t) row+1;
		sp->sparray = (int **) realloc(sp->sparray, sp->row_size * sizeof(int *));
	  sp->column_size = (size_t *) realloc(sp->column_size, sp->row_size * sizeof(size_t));

		for(i = olrowsize ; i < sp->row_size ; i++){
			sp->column_size[i] = 0;
			sp->sparray[i] = NULL;
		}
	}

	if(column >= sp->column_size[row]){

		sp->column_size[row] = column+1;
		sp->sparray[row] = (int *) realloc(sp->sparray[row], sp->column_size[row] * sizeof(int));

		olcolumnsize = realloc(olcolumnsize,sizeof(sp->column_size));

		for(i = olcolumnsize[row] ; i < sp->column_size[row] ; i++){
			sp->sparray[row][i] = 0;
		}
	}
	sp->sparray[row][column] = ins;
}

//Free a one dimentional array
/*
Used to free a one dimentional array
*/
void freeArray(array *a){
free(a->array);
a->array = NULL;
a-> size = 0;
}

//Free a two dimentional array
/*
Used to free a two dimentional array
*/
void freeDArray(darray *da){
free(da->darray);
da->darray = NULL;
da->row_size = da->column_size = 0;
}

//Free a two dimentional spider array
/*
Used to free a two dimentional spider array
*/
void freeSpArray(sparray *sp){
free(sp->sparray);
sp->sparray = NULL;
sp->row_size = 0;
sp->column_size = NULL;
}

//Print a one dimentional array
/*
Used to print a one dimentional array to the screen
*/
void printArray(array *a){
int i;
printf("array:\n");
printf("[");
for(i = 0 ; i < a->size ; i++){
	printf("%d",a->array[i]);

	if(i+1 < a->size){
		printf(",");
	}
}
printf("]\n");
printf("size:\n%d\n",a->size);

}

//Print a two dimentional array
/*
Used to print a two dimentional array to the screen
*/
void printDArray(darray *da){
int i, j;
printf("darray:\n");
for(i = 0 ; i < da->row_size ; i++){
	printf("row_%d:\n", i);
	printf("[");
	for(j = 0 ; j < da->column_size ; j++){

		printf("%d",da->darray[i][j]);

		if(j+1 < da->column_size){
			printf(",");
		}
	}
	printf("]\n");

}
printf("row_size:\n%d\n",da->row_size);
printf("column_size:\n%d\n",da->column_size);
}

void printSpArray(sparray *sp){
int i,j;
printf("sparray:\n");
for(i = 0 ; i < sp->row_size ; i++){
	printf("row_%d:\n", i);
	printf("[");
	for(j = 0 ; j < sp->column_size[i] ; j++){

		printf("%d",sp->sparray[i][j]);

		if(j+1 < sp->column_size[i]){
			printf(",");
		}
	}
	printf("]\n");
}
}

//Get an element from a one dimentional array
/*
Used to get the value at pos of a one dimentional array
Returns the value at pos
*/
int returnArrayElement(array *a , int pos){
return a->array[pos];
}

//Get an element from a two dimentional array
/*
Used to get the value at row, column of a two dimentional array
Returns the value at row, column
*/
int returnDArrayElement(darray *da, int row, int column){
return da->darray[row][column];
}

//Get a pointer to an element in a one dimentional array
/*
Used to get a pointer that points to the value at pos in a one dimentional array
Returns a pointer that points to the value at pos
NOTE:
Pointer does not become NULL upon reallocation of the one dimentional array
*/
int* returnArrayPointerElement(array *a, int pos){
return &a->array[pos];
}

//Get a pointer to an element in a two dimentional array
/*
Used to get a pointer that points to the value at row, cloumn in a two dimentional array
Returns a pointer that points to the value at row, column
NOTE:
Pointer does not become NULL upon reallocation of the two dimentional array
*/
int* returnDArrayPointerElement(darray *da, int row, int column){
return &da->darray[row][column];
}

//Multiply two, one dimentional arrays
/*
Used to multiply two, one dimentional arrays (a1 and a2)
The size of a1 and a2 must be the same
Store the resulting one dimentional array in ans
*/
void multiplyArray(array *a1 ,array *a2 ,array *ans){

if(a1->size != a2->size){
	perror("Array Size");
	return;
}

freeArray(ans);
initArray(ans,a1->size);

int i;
for(i = 0 ; i < a1->size ; i++){
	ans->array[i] = a1->array[i] * a2->array[i];
}
}

//Multiply two, two dimentional arrays
/*
Used to multiply two, two dimentional arrays (da1 and da2)
The column size of da1 must be the same as the row size of da2
Store the resulting two dimentional array in ans
*/
void multiplyDArray(darray *da1, darray *da2, darray *ans){

if(da1->column_size != da2->row_size){
	perror("DArray Size");
	return;
}

freeDArray(ans);
initDArray(ans,da1->row_size,da2->column_size);

int i, j, l;
for(i = 0 ; i < da1->row_size ; i++){
	for(j = 0 ; j < da2->column_size ; j++){
		for(l = 0 ; l < da1->column_size ; l++){
			ans->darray[i][j] = ans->darray[i][j] + da1->darray[i][l] * da2->darray[l][j];
		}
	}
}
}

//Add two, one dimentional arrays
/*
Used to add two, one dimentional arrays
The size of a1 and a2 must be the same
Store the resulting one dimentional array in ans
*/
void addArray(array *a1 ,array *a2 ,array *ans){

if(a1->size != a2->size){
	perror("Array Size");
	return;
}

freeArray(ans);
initArray(ans, a1->size);

int i;
for(i = 0 ; i < a1->size ; i++){
	ans->array[i] = a1->array[i] + a2->array[i];
}
}

//Add two, two dimentional arrays
/*
Used to add two, two dimentional arrays
The row size and column size of da1 and da2 must be the same
Store the resulting two dimentional array in ans
*/
void addDArray(darray *da1, darray *da2, darray *ans){

if(da1->row_size != da2->row_size || da1->column_size != da2->column_size){
	perror("DArray Size");
	return;
}

freeDArray(ans);
initDArray(ans, da1->row_size, da1->column_size);

int i,j;
for(i=0 ; i < da1->row_size ; i++){
	for(j=0 ; j < da1->column_size ; j++){
		ans->darray[i][j] = da1->darray[i][j] + da2->darray[i][j];
	}
}
}

//Subtract two, one dimentional arrays
/*
Used to subtract two, one dimentional arrays
The size of a1 and a2 must be the same
Store the resulting one dimentional array in ans
*/
void subtractArray(array *a1 ,array *a2,array *ans){

if(a1->size != a2->size){
	perror("Array Size");
	return;
}

freeArray(ans);
initArray(ans, a1->size);

int i;
for(i = 0 ; i < a1->size ; i++){
	ans->array[i] = a1->array[i] - a2->array[i];
}
}

//Subtract two, two dimentional arrays
/*
Used to subtract two, two dimentional arrays
The row size and column size of da1 and da2 must be the same
Store the resulting two dimentional array in ans
*/
void subtractDArray(darray *da1, darray *da2, darray *ans){

if(da1->row_size != da2->row_size || da1->column_size != da2->column_size){
	perror("DArray Size");
	return;
}

freeDArray(ans);
initDArray(ans, da1->row_size, da1->column_size);

int i,j;
for(i=0 ; i < da1->row_size ; i++){
	for(j=0 ; j < da1->column_size ; j++){
		ans->darray[i][j] = da1->darray[i][j] - da2->darray[i][j];
	}
}
}
