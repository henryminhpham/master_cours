#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>

int isRegular(char* name);

int seek_expression (char* name, regex_t* regexp);

int find_regexp(regex_t* regexp, char* content);

char* convert_path(char* name, int is_current, char* directory); 