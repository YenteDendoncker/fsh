#include "env_fopen.h"

#include <stdarg.h>
#include <string.h>

#include "fsh.h"



// Example usage: env_fopen("test/file", "r", 2, "/env1", "env2");
// If the first argument is a valid absolute path (e.g. "/test/file" on linux) this will:
// * Check for absolute path "/test/file (1)
// If the first argument is not a valid absolute path (e.g. test/file on linux) this will:
// * Check for working directory with filename appended "{working directory}/test/file" (2)
// * Check for executable directory with filename appended "{executable directory}/test/file" (3)
// * It will then check for each environment:
//   - If the environment is a valid absolute (e.g. "/env" on linux) path:
//     * Check for absolute path env with filename appended "/env/test/file" (4)
//   - If the environment is not a valid absolute path (e.g. "env")
//     * Check for working directory with environment and then filename appended "{working directory}/env/test/file" (5)
//     * Check for executable directory with environment and then filename appended "{executable directory}/env/test/file" (6)
// In that order. If at any point a file is found it returns a filepointer to that file and stops searching.
FILE* fsh_env_fopen(const char* filepath, const char* mode, int env_count, ...) {
    static char execd[FSH_PATH_MAX];
    static size_t execd_len = 0;
    static int init_execd = 0;
    if (!init_execd) {
        execd_len = fsh_get_execd(execd, FSH_PATH_MAX);
        init_execd = 1;
    }
    FILE* fp;
    printf("Checking (1 2) %s...\n", filepath);
    fp = fopen(filepath, mode); // (1) and (2)
    if (fp) {
        return fp;
    }
    char check_filepath[FSH_PATH_MAX + FSH_FILE_MAX];
    if (fsh_is_absolute(filepath)) {
        return NULL;
    }
    strncpy(check_filepath, execd, FSH_PATH_MAX + FSH_FILE_MAX);
    strncat(check_filepath, filepath, FSH_PATH_MAX + FSH_FILE_MAX);
    printf("Checking (3  ) %s...\n", check_filepath);
    fp = fopen(check_filepath, mode); // (3)
    if (fp) {
        return fp;
    }
    va_list envs;
    va_start(envs, env_count);
    for (int i = 0; i < env_count; i += 1) {
        const char* env = va_arg(envs, const char*);
        size_t env_len = strlen(env);
        strncpy(check_filepath, env, FSH_PATH_MAX + FSH_FILE_MAX);
        if (check_filepath[env_len-1] != FSH_PATH_SEP && check_filepath[env_len-1] != FSH_PATH_SEP2) {
            check_filepath[env_len] = FSH_PATH_SEP;
            check_filepath[env_len+1] = '\0';
        }
        strncat(check_filepath, filepath, FSH_PATH_MAX + FSH_FILE_MAX);
        printf("Checking (4 5) %s...\n", check_filepath);
        fp = fopen(check_filepath, mode); // (4) and (5)
        if (fp) {
            va_end(envs);
            return fp;
        }
        if (!fsh_is_absolute(env)) {
            strncpy(check_filepath, env, FSH_PATH_MAX + FSH_FILE_MAX);
            if (check_filepath[env_len-1] != FSH_PATH_SEP && check_filepath[env_len-1] != FSH_PATH_SEP2) {
                check_filepath[env_len] = FSH_PATH_SEP;
                check_filepath[env_len+1] = '\0';
            }
            strncat(check_filepath, filepath, FSH_PATH_MAX + FSH_FILE_MAX);
            strncpy(check_filepath, execd, FSH_PATH_MAX + FSH_FILE_MAX);
            strncat(check_filepath, env, FSH_PATH_MAX + FSH_FILE_MAX);
            size_t total_len = strlen(check_filepath);
            if (check_filepath[total_len-1] != FSH_PATH_SEP && check_filepath[total_len-1] != FSH_PATH_SEP2) {
                check_filepath[total_len] = FSH_PATH_SEP;
                check_filepath[total_len+1] = '\0';
            }
            strncat(check_filepath, filepath, FSH_PATH_MAX + FSH_FILE_MAX);
            printf("Checking (6  ) %s...\n", check_filepath);
            fp = fopen(check_filepath, mode); // (6)
            if (fp) {
                va_end(envs);
                return fp;
            }
        }
    }
    va_end(envs);
    return NULL; // No files found.
}