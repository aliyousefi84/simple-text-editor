#ifndef TERMINAL_H
#define TERMINAL_H
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "helper/file.h"

struct terminal_state {
    struct termios old_t;
    
    struct termios new_t; 
    
    unsigned char terminal_raw_byte;

    char* add_char;

    struct file_handler* file;

    
};

struct terminal_state* initialize (struct file_handler* f);

void terminal_main_loop (struct terminal_state* t);

void clear_page ();

void clean_up_terminal (struct terminal_state* t);

#endif