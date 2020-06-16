const char* get_file(int argc, char** argv); 

const char* remove_extensions(const char* file_name);

void make_obj_file(FILE* makefile, const char* file);

void make_program(FILE* makefile, const char* file);