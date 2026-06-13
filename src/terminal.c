#include "terminal.h"

struct terminal_state* initialize (struct file_handler* f) {
    struct terminal_state* t = (struct terminal_state *) malloc (sizeof(struct terminal_state));
    t->add_char = (char *) malloc (8000);
    t->file = f;
    tcgetattr (STDIN_FILENO , &t->old_t);

    t->new_t = t->old_t;

    t->new_t.c_lflag &= ~(ICANON | ECHO);
    t->new_t.c_iflag |= IUTF8;
    t->new_t.c_iflag |= ONLCR;
    t->new_t.c_oflag |= ONLCR;
    t->new_t.c_cc [VMIN] = 1;
    t->new_t.c_cc [VTIME] = 0;
    tcsetattr (STDIN_FILENO , TCSANOW , &t->new_t);
    clear_page ();  
    return t;
};

void clear_page () {
    write (STDOUT_FILENO , "\033[?1049h" , 8);
    write (STDOUT_FILENO , "\033[2J" , 4);
    write (STDOUT_FILENO , "\033[H" , 3);
};

void terminal_main_loop (struct terminal_state* t) {
    int count = 0;
    while (read (STDIN_FILENO , &t->terminal_raw_byte ,1) == 1)
    {
        
        if (t->terminal_raw_byte == 4) break;
        if (t->terminal_raw_byte == 27) {
            // \033[A   |
            char seq[2];
            read (STDIN_FILENO,seq,2);
            if (seq[0] == '[' && seq[1] == 'D') {
                write (STDOUT_FILENO , "\b" , 1);
            };

        }
        if (t->terminal_raw_byte == 10) {
            editor_insert (t->file , t->terminal_raw_byte);
            write (STDOUT_FILENO,"\n\r",2);
        }
        if (t->terminal_raw_byte == 127) {
            editor_backspace (t->file);
            write (STDOUT_FILENO,"\b \b" , 3);            
        } 

        if (t->terminal_raw_byte > 27 && t->terminal_raw_byte < 127)
        {
            editor_insert (t->file , t->terminal_raw_byte);
            write (STDOUT_FILENO , &t->terminal_raw_byte , 1);
        }          
        if (t->terminal_raw_byte == 24) {
            save_file (t->file);
        };
    }

    write (STDOUT_FILENO , "\033[?1049l" , 8);
    tcsetattr (STDIN_FILENO , TCSANOW , &t->old_t);
    clean_up_terminal (t);
}

void clean_up_terminal (struct terminal_state* t) {
    free(t->add_char);
    free (t);
}