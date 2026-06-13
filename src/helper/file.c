#include "file.h"



struct file_handler* init_file_handler (char *filepath) {
    struct file_handler* f = (struct file_handler *) malloc (sizeof(struct file_handler));
    
    f->path = filepath;

    return f;
};

size_t get_file_size (struct file_handler* f) {
    struct stat st;
    stat (f->path , &st);
    return st.st_size;
}

void read_file_from_arguman (struct file_handler* f) {
    int fd = open (f->path , O_RDONLY);
    struct stat st;
    stat (f->path , &st);
    size_t size = st.st_size;
    f->buf = (char *) malloc (size);
    if (fd == -1)
    {
        printf ("can not open this file , check permission or filepath !\n");
        exit (1);
    }

    int n = read (fd,f->buf,size);
    f->buf[n] = '\0';
    close (fd);
    write (STDOUT_FILENO , f->buf , strlen(f->buf));
};



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

void clean_up_file (struct file_handler* f) {
    free (f->buf);
    free (f);
}