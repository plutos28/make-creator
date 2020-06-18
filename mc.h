const char* get_program(int argc, char** argv); 

const char* remove_extensions(const char* file_name);

void make_obj_file(FILE* makefile, const char* file, const char* build_dir);

void make_program(FILE* makefile, const char* file, const char* build_dir);

void create_build_dir(const char* dir); 


