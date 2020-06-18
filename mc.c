#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "mc.h"

int main(int argc, char** argv) {
    // note: rename this file(mf) into Makefile later. can't do it
    //  now because of conflict with project Makefile
    FILE* makefile = fopen("mf", "w");
    if (!makefile) {
        perror("file opening failed");
        return EXIT_FAILURE;
    }

    const char* program = get_program(argc, argv);
    const char* build_dir = "./bd"; // temp name because of conflict

    make_obj_file(makefile, program, build_dir);
    make_program(makefile, program, build_dir);

    create_build_dir(build_dir);
    return 0;
}

void create_build_dir(const char* dir) {
    struct stat st = {0};
    // checks existance of build_dir
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

const char* get_program(int argc, char** argv) {
    // change this function to return an array of the arguments passed
    // or just move this function over to the main function 
    // and use a loop along with it(using argc)
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

void make_obj_file(FILE* makefile, const char* file, const char* build_dir) {
    // create object file
    fprintf(makefile, "%s.o: %s\n\tgcc -c %s\n", 
                        remove_extensions(file), file, file);
    fprintf(makefile, "\tmv %s.o %s/\n\n", remove_extensions(file), build_dir);
}

void make_program(FILE* makefile, const char* file, const char* build_dir) {
        // create executable file
    fprintf(makefile, "%s: %s.o\n\tgcc %s/%s.o -o %s\n\n",
                        remove_extensions(file),
                        remove_extensions(file),
                        build_dir,
                        remove_extensions(file),
                        remove_extensions(file));
}
