#ifndef FSH_GET_CWD_H
#define FSH_GET_CWD_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t fsh_get_cwd(char* buffer, int buffer_size);

#ifdef __cplusplus
} // Extern C
#endif

#endif // FSH_GET_CWD_H