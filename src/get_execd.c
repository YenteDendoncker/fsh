
#include "get_execd.h"

#include <string.h>

#include "fsh.h"

/**
 * fsh_get_execd
 * Gets the directory of the current running executable.
 */ 
#if defined(FSH_WINDOWS)
#include <Windows.h>
size_t fsh_get_execd(char* buffer, int buffer_size) {
    static char fsh_execd_buffer[FSH_PATH_MAX];
    static size_t execd_len = 0;
    if (execd_len && buffer) {
        // copy buffer
        strcpy(buffer, fsh_execd_buffer);
        return execd_len;
    }
    DWORD written_len = GetModuleFileName(NULL, fsh_execd_buffer, FSH_PATH_MAX);
    if (written_len == 0 || written_len == FSH_PATH_MAX) {
        return 0;
    }
    int i = strlen(fsh_execd_buffer);
    while(fsh_execd_buffer[i] != '\\' && i >= 0) {
        fsh_execd_buffer[i] = '\0';
        i -= 1;
    }
    execd_len = i;
    if (!buffer) {
        return execd_len;
    }
    strcpy(buffer, fsh_execd_buffer);
    return execd_len;
}
#elif defined(FSH_LINUX)
#include <unistd.h>
// TODO: add realpath
size_t fsh_get_execd(char* buffer, int buffer_size) {
    static char fsh_execd_buffer[FSH_PATH_MAX];
    static size_t execd_len = 0;
    if (execd_len && buffer) {
        strcpy(buffer, fsh_execd_buffer);
        return execd_len;
    }
    ssize_t written_len = readlink("/proc/self/exe", fsh_execd_buffer, FSH_PATH_MAX);
    if (written_len == -1 || written_len == FSH_PATH_MAX) {
        return 0;
    }
    int i = strlen(fsh_execd_buffer);
    while (fsh_execd_buffer[i] != '/' && i >= 0) {
        fsh_execd_buffer[i] = '\0';
        i -= 1;
    }
    execd_len = i;
    if (!buffer) {
        return execd_len;
    }
    strcpy(buffer, fsh_execd_buffer);
    return execd_len;
}
#elif defined(FSH_MAC_OS)
#include <mach-o/dyld.h>
// TODO: add realpath
size_t fsh_get_execd(char* buffer, int buffer_size) {
    static char fsh_execd_buffer[FSH_PATH_MAX];
    static size_t execd_len = 0;
    if (execd_len && buffer) {
        strcpy(buffer, fsh_execd_buffer);
        return execd_len;
    }
    uint32_t written_len = FSH_PATH_MAX;
    if (0 != _NSGetExecutablePath(fsh_execd_buffer, &written_len)) {
        return 0;
    }
    while (fsh_execd_buffer[i] != '/' && i >= 0) {
        fsh_execd_buffer[i] = '\0';
        i -= 1;
    }
    execd_len = i;
    if (!buffer) {
        return execd_len;
    }
    strcpy(buffer, fsh_execd_buffer);
    return execd_len;
}
#else
#error "fsh_get_exed not implemented for this platform."
#endif