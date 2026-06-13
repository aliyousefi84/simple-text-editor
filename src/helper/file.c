#include "file.h"



struct file_handler* init_file_handler (char *filepath) {
    struct file_handler* f = (struct file_handler *) malloc (sizeof(struct file_handler));
    
    f->path = filepath;

    return f;
};



void read_file_from_arguman (struct file_handler* f) {
    int fd = open (f->path , O_RDONLY);
    if (fd == -1)
    {
        f->buf = malloc(1024);
        f->capacity = 1024;
        f->size = 0;
        f->cursor_pos = 0;
        return;
    }

    struct stat st;
    fstat (fd, &st);
    f->size = st.st_size;
    f->capacity = f->size + 1024;

    f->buf = malloc (f->capacity);
    read (fd , f->buf , f->size);
    close (fd);

    f->cursor_pos = st.st_size;
    
    write (STDOUT_FILENO , f->buf , strlen(f->buf));
};

void editor_insert (struct file_handler* f,char ch) {
    if (f->size + 1 >= f->capacity)
    {
        f->capacity *= 2;
        f->buf = realloc (f->buf , f->capacity);
    }

    memmove (&f->buf[f->cursor_pos +1] , &f->buf[f->cursor_pos] , f->size - f->cursor_pos);

    f->buf[f->cursor_pos] = ch;
    f->size++;
    f->cursor_pos++;
};

void editor_backspace (struct file_handler* f) {
    if (f->cursor_pos > 0)
    {
        f->cursor_pos--;

        memmove (&f->buf[f->cursor_pos] , &f->buf[f->cursor_pos +1],f->size - f->cursor_pos -1);
        f->size--;
    }   
}

void save_file (struct file_handler* f) {
    int fd = open (f->path , O_WRONLY | O_CREAT | O_TRUNC);

    if (fd == -1)
    {
        printf ("can not open this file\n");
        exit(1);
    }

    write (fd , f->buf , f->size);
    close (fd);
    
}

/*
void save_file (struct file_handler* f, char* buffer) {
    int fd = open (f->path , O_WRONLY | O_APPEND);

    if (fd == -1)
    {
        printf ("can not open this file\n");
        exit(1);
    }

    write (fd , buffer, strlen(buffer));
    close (fd);
}
*/
void clean_up_file (struct file_handler* f) {
    free (f->buf);
    free (f);
}