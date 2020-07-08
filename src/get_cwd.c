#include "get_cwd.h"

#include <string.h>

#include "fsh.h"


#if defined(FSH_WINDOWS)
#include <Windows.h>
size_t fsh_get_cwd(char* buffer, int buffer_size) {
    static char fsh_cwd_buffer[FSH_PATH_MAX];
    static size_t cwd_len = 0;
    if (cwd_len && buffer) {
        strcpy(buffer, fsh_cwd_buffer);
        return cwd_len;
    }
    DWORD success = GetCurrentDirectory(buffer_size, buffer);
    if (!success) {
        return 0;
    }
    cwd_len = strlen(fsh_cwd_buffer);
    if (fsh_cwd_buffer[cwd_len-1] != '/') {
        if (cwd_len+1 >= FSH_PATH_MAX) { // Not enough room for trailing '/'.
            return 0;
        }
        fsh_cwd_buffer[cwd_len] = '/';
        fsh_cwd_buffer[cwd_len+1] = '\0';
    }
    if (!buffer) {
        return cwd_len;
    }
    strcpy(buffer, fsh_cwd_buffer);
    return cwd_len;
}
#elif defined(FSH_LINUX) || defined(FSH_MAC_OS)
#include <unistd.h>
size_t fsh_get_cwd(char* buffer, int buffer_size) {
    static char fsh_cwd_buffer[FSH_PATH_MAX];
    static size_t cwd_len = 0;
    if (cwd_len && buffer) {
        strcpy(buffer, fsh_cwd_buffer);
        return cwd_len;
    }
    char* success = getcwd(fsh_cwd_buffer, FSH_PATH_MAX);
    if (!success) {
        return 0;
    }
    cwd_len = strlen(fsh_cwd_buffer);
    if (fsh_cwd_buffer[cwd_len-1] != '/') {
        if (cwd_len+1 >= FSH_PATH_MAX) { // Not enough room for trailing '/'.
            return 0;
        }
        fsh_cwd_buffer[cwd_len] = '/';
        fsh_cwd_buffer[cwd_len+1] = '\0';
    }
    if (!buffer) {
        return cwd_len;
    }
    strcpy(buffer, fsh_cwd_buffer);
    return cwd_len;
}
#else
#error "fsh_get_cwd not implemented for this platform."
#endif