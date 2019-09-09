#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>

int (*someSecretFunctionPrototype)(const int value);

bool init_library(char* lib_name, char* fun_name) {
    char str_lib_name[80];
    sprintf(str_lib_name, "./%s", lib_name);
    void *hdl = dlopen(str_lib_name, RTLD_LAZY);
    if (NULL == hdl)
        return false;
    someSecretFunctionPrototype = (int (*)(const int))dlsym(hdl, fun_name);
    if (NULL == someSecretFunctionPrototype)
        return false;
    return true;
}

int main(int argc, char* argv[])
{
    int value = atoi(argv[3]);
    if (init_library(argv[1], argv[2]))
        printf("%d\n", someSecretFunctionPrototype(value));
    else
        printf("Library was not loaded\n");
    return 0;
}

