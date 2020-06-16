#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mc.h"

int main(int argc, char** argv) {
    // note: rename this file(mf) into Makefile later. can't do it
    //  now because of conflict with project Makefile
    FILE* makefile = fopen("mf", "w");
    if (!makefile) {
        perror("file opening failed");
        return EXIT_FAILURE;
    }

    const char* file = get_file(argc, argv);

    make_obj_file(makefile, file);
    make_program(makefile, file);

    return 0;
}

const char* get_file(int argc, char** argv) {
    const char* file;
    char ch;
    while ((ch = getopt(argc, argv, "p:")) != EOF) {
        switch(ch) {
            case 'p':
                file = optarg;
                return file;
        }
    }
    argc -= optind;
    argv += optind;
}

const char* remove_extensions(const char* file_name) {
    size_t no_ext_length = strlen(file_name)-2; 
    char new_name[no_ext_length+1];
    char* final_name; 

    strncpy(new_name, file_name, no_ext_length); 
    new_name[no_ext_length] = '\0';
    final_name = new_name;

    return final_name;
}

void make_obj_file(FILE* makefile, const char* file) {
    // create object file
    fprintf(makefile, "%s.o: %s\n\tgcc -c %s\n\n", 
                        remove_extensions(file), file, file);
}

void make_program(FILE* makefile, const char* file) {
        // create executable file
    fprintf(makefile, "%s: %s.o\n\tgcc %s.o -o %s\n\n",
                        remove_extensions(file),
                        remove_extensions(file),
                        remove_extensions(file),
                        remove_extensions(file));
}