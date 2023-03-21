#include <stdio.h>
#include <stdlib.h>
#include "mem_block.h"
#include <string.h>
#include <time.h>

#define BUFF_SIZE 512
#define COMMAND_LEN 30

extern memory_block* make_memory_block(size_t size);
extern void write_to_block(memory_block* block, const char* filename);
extern char* get_data(memory_block* block, int i);
extern void delete_data(memory_block* block, int i);
extern void free_pointers(memory_block* block);


void print_chars(const char* command) {
    printf("vvvvvvv(DEBUG)vvvvvvv\n");
    for(int i =0; command[i] != '\0'; i++){
        char c = command[i];
        switch (c) {
            case '\n':
                printf("\\n\n");
                break;
            case ' ':
                printf("(SPACE)\n");
                break;
            default:
                printf("%c\n", c);
                break;
        }
    }
    printf("^^^^^^^(DEBUG)^^^^^^^\n");
}

int valid_command(char* command){
    //print_chars(command);
    if (strcmp(command, "init") == 0) {
        return 0;
    }
    else if (strcmp(command, "count") == 0) {
        return 1;
    }
    else if (strcmp(command, "show") == 0){
        return 2;
    }
    else if (strcmp(command, "delete index") == 0) {
        return 3;
    }
    else if (strcmp(command, "destroy") == 0) {
        return 4;
    }
    else if (strcmp(command, "exit") == 0){
        return 5;
    }
    else {
        return -1;
    }
}

int convert_to_int(const char* argument){
    //print_chars(argument);
    int number = 0;
    if (argument[0] == '\0' || argument[0] == '\n' || argument[0] == ' ' || argument[0] == 13){
        return -2;
    }
    for (int i = 0; argument[i] != '\0' && argument[i] != ' ' && argument[i] != 13; i++){
        number *= 10;
        switch (argument[i]) {
            case '0':
                number += 0;
                break;
            case '1':
                number += 1;
                break;
            case '2':
                number += 2;
                break;
            case '3':
                number += 3;
                break;
            case '4':
                number += 4;
                break;
            case '5':
                number += 5;
                break;
            case '6':
                number += 6;
                break;
            case '7':
                number += 7;
                break;
            case '8':
                number += 8;
                break;
            case '9':
                number += 9;
                break;
            default:
                return -1;
        }
        if (number >= 1000000000) {
            return -3;
        }
    }
    return number;
}


int parse_input(char* buff, char* command, char* arg_char){
    for (int i = 0; buff[i] != '\0' || i < BUFF_SIZE; i++){
        if (buff[i] == '\n'){
            buff[i] = '\0';
            break;
        }
    }
    char* temp = strtok(buff, " ");
    if (temp == NULL){
        printf("Błędna komenda!\n");
        return -1;
    }
    strncpy(command,temp, COMMAND_LEN);

    if (strcmp(command, "delete") == 0) {
        char* second_word = strtok(NULL, " ");
        if (second_word == NULL || strcmp(second_word, "index") != 0){
            printf("Blenda komenda!\n");
            return -1;
        }
        else {
            strcat(command, " ");
            strcat(command, second_word);
        }
    }

    int command_id = valid_command(command);

    if (command_id == -1) {
        printf("Blenda komenda!\n");
        return -1;
    }
    
    temp = strtok(NULL, " ");
    if (temp == NULL) {
        strncpy(arg_char, "\0", COMMAND_LEN);
        return 0;
    }

    strncpy(arg_char, temp, COMMAND_LEN);
    return 0;
}


int main(int argc, char* argv[]){
    memory_block* block = NULL;
    int flag = 1;
    char buff[BUFF_SIZE];

    int arg_int;
    char command[COMMAND_LEN];
    char arg_char[COMMAND_LEN];

    struct timespec user_start, user_end, sys_start, sys_end;
    double user_time, sys_time;

    int parse_state;
    while (flag){
        printf(">>>  ");
        clock_gettime(CLOCK_MONOTONIC_RAW, &user_start);
        fgets(buff, BUFF_SIZE, stdin);
        clock_gettime(CLOCK_MONOTONIC_RAW, &user_end);
        clock_gettime(CLOCK_MONOTONIC_RAW, &sys_start);
        parse_state = parse_input(buff,command,arg_char);
        if (parse_state < 0){
            clock_gettime(CLOCK_MONOTONIC_RAW, &sys_end);
            user_time = ((double)user_end.tv_nsec - user_start.tv_nsec) / 1000000000.0 +
                        ((double)user_end.tv_sec  - user_start.tv_sec);
            sys_time = ((double)sys_end.tv_nsec - sys_start.tv_nsec) / 1000000000.0 +
                       ((double)sys_end.tv_sec  - sys_start.tv_sec);
            printf("Czas uzytkownika: %f\nCzas systemowy: %f\nCzas calkowity: %f\n", user_time, sys_time, user_time+sys_time);
            continue;
        }
        switch (valid_command(command)){

            case -1:
                printf("Blendna komenda!\n");
                break;

            case 0: // init
                arg_int = convert_to_int(arg_char);
                if (arg_int <= 0){
                    printf("Blendy argument!\n");
                }
                else if (block != NULL){
                    printf("Tablica jest już stworzona!\n");
                }
                else {
                    block = make_memory_block(arg_int);
                }
                break;

            case 1: // count
                if (block == NULL){
                    printf("Blok nie został zainicjalizowany!\n");
                }
                else {
                    write_to_block(block, arg_char);
                }
                break;

            case 2: // show
                arg_int = convert_to_int(arg_char);
                if (block == NULL){
                    printf("Blok nie został zainicjalizowany!\n");
                }
                else if (arg_int < 0){
                    printf("Blendy argument!\n");
                }
                else {
                    char* data = get_data(block, arg_int);
                    if (data != NULL){
                        printf("%s\n", data);
                    }
                }
                break;

            case 3: // delete index
                arg_int = convert_to_int(arg_char);
                if (arg_int < 0){
                    printf("Blendy argument!\n");
                }
                else {
                    delete_data(block, arg_int);
                }
                break;

            case 4: // destroy
                if (block == NULL){
                    printf("Blok nie zostal zainicjalizowany!\n");
                }
                else {
                    free_pointers(block);
                    free(block->pointers);
                    free(block);
                    block = NULL;
                }
                break;

            case 5: // exit - wyjscie z programu
                flag = 0;
                break;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &sys_end);
        user_time = ((double)user_end.tv_nsec - user_start.tv_nsec) / 1000000000.0 +
                    ((double)user_end.tv_sec  - user_start.tv_sec);
        sys_time = ((double)sys_end.tv_nsec - sys_start.tv_nsec) / 1000000000.0 +
                   ((double)sys_end.tv_sec  - sys_start.tv_sec);
        printf("Czas uzytkownika: %f\nCzas systemowy: %f\nCzas calkowity: %f\n", user_time, sys_time, user_time+sys_time);
    }

    if (block != NULL){
        free_pointers(block);
        free_pointers(block);
        free(block->pointers);
        free(block);
        block = NULL;
    }
    return 0;
}