#include "src/terminal.h"
#include "src/helper/file.h"
#include <stdio.h>

int main (int argc , char **argv) {
    if (argc < 2) {
        printf ("pass the filename\n");
        return 0;
    }

    struct file_handler* f = init_file_handler(argv[1]);
    struct terminal_state *terminal = initialize (f);
    read_file_from_arguman (f);
    terminal_main_loop (terminal);
    clean_up_file (f);
    
}