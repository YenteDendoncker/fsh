#include "fsh.h"

#include <stdio.h>
#include <stdlib.h>

int main0(int argc, char* argv[]) {
    size_t req_size;
    char* buffer;

    // Execd
    req_size = fsh_get_execd(NULL, 0);
    buffer = malloc(req_size);
    fsh_get_execd(buffer, req_size);
    printf("%s\n", buffer);
    free(buffer);

    // cwd
    req_size = fsh_get_cwd(NULL, 0);
    buffer = malloc(req_size);
    fsh_get_cwd(buffer, req_size);
    printf("%s\n", buffer);
    free(buffer);

    // absolute
    int is_absolute;
    is_absolute = fsh_is_absolute("/path/to/file");
    printf("%d\n", is_absolute);
    is_absolute = fsh_is_absolute("../path/to/file");
    printf("%d\n", is_absolute);

    // env_fopen
    if (argc < 2) {
        printf("No file argument given.\n");
        return 1;
    }
    FILE* fp = fsh_env_fopen(argv[1], "r", 2, "env1", "env2");
    if (!fp) {
        printf("File %s not found\n", argv[1]);
        return 1;
    }
    printf("File found.\n");

    return 0;
}

int main1(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No file argument given.\n");
        return 1;
    }
    FILE* fp = fsh_env_fopen(argv[1], "r", 2, "env1", "env2");
    if (!fp) {
        printf("File %s not found\n", argv[1]);
        return 1;
    }
    char buffer[500];
    fgets(buffer, 500, fp);
    printf("%s\n", buffer);
    return 0;
}

int main(int argc, char* argv[]) {
    return main0(argc, argv);
}