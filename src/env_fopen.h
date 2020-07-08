#ifndef FSH_ENV_FOPEN_H
#define FSH_ENV_FOPEN_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

FILE* fsh_env_fopen(const char* filepath, const char* mode, int env_count, ...);

#ifdef __cplusplus
} // Extern C
#endif

#endif // FSH_ENV_FOPEN_H