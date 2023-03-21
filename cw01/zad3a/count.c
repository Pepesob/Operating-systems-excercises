#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mem_block.h"

#define BUFF_SIZE 512


char* file_data(){
    char* buff = calloc(BUFF_SIZE,sizeof(char));
    if (buff == NULL){
        printf("Error with memory allocation!\n");
    }
    char ch;
    int count=0;
    FILE* fptr;
    fptr=fopen("tmp/temp1.txt","r");
    while((ch=fgetc(fptr))!=EOF || count < BUFF_SIZE) {
        buff[count] = ch;
        count++;
    }
    buff[count] = '\0';
    count++;
    fclose(fptr);
    buff = realloc(buff,count*sizeof(char));
    if (buff == NULL){
        printf("Error with memory allocation!\n");
    }
    return buff;
}

void wc_to_file(const char* file_name){
    char command[BUFF_SIZE];
    command[0] = '\0';
    strcat(command, "wc ");
    strcat(command, file_name);
    strcat(command, " > tmp/temp1.txt");

    printf("%s\n", command);

    system("mkdir tmp 2> /dev/null");
    system(command);
}

//First function
memory_block* make_memory_block(size_t size){
    memory_block* block = malloc(sizeof(memory_block));
    if (block == NULL){
        printf("Error with memory allocation!\n");
        return NULL;
    }

    block->pointers = calloc(size,sizeof(void*));
    block->memory_size = size;
    block->i = 0;
    return block;
}

//Second function
void write_to_block(memory_block* block, const char* filename){
    if (block->i >= block->memory_size){
        printf("Niewystarczająco pamięci w bloku!\n");
        return;
    }
    wc_to_file(filename);
    block->pointers[block->i] = file_data();
    block->i++;
    int status = remove("tmp/temp1.txt");
    int status2 = remove("tmp");
    if (status < 0 || status2 < 0){
        printf("Blad przy uswuwaniu pliku temp1.txt!\n");
        return;
    }
}


//Third function
char* get_data(memory_block* block, int i){
    if (i >= block->i || i < 0){
        printf("Błędny indeks!\n");
        return NULL;
    }
    return block->pointers[i];
}

//Fourth function
void delete_data(memory_block* block, int i){
    if (i >= block->i || i < 0){
        printf("Błędny indeks!\n");
        return;
    }
    free(block->pointers[i]);
    for (int j = i; j < block->i-1; j++){
        block->pointers[j] = block->pointers[j+1];
    }
    block->i--;
}

//Fifth function
void free_pointers(memory_block* block){
    for (int i = 0; i < block->i; i++){
        free(block->pointers[i]);
    }
    block->i = 0;
}


/*
int main() {
    memory_block *block = make_memory_block(20);
    write_to_block(block, "direct/tests.txt");
    //printf("%s\n", get_data(block, 0));
    return 0;
}
*/
