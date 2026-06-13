#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

struct file_handler
{
    char* path;
    
    char* buf;

};

struct file_handler* init_file_handler (char *filepath);

void read_file_from_arguman (struct file_handler* f);

size_t get_file_size (struct file_handler* f);

void save_file (struct file_handler* f, char* buffer);

void clean_up_file (struct file_handler* f);

#endif