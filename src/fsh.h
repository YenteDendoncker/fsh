#ifndef FSH_FSH_H
#define FSH_FSH_H

#include <stddef.h>
#include <stdio.h>

// THe supported operating systems and their variations:
// - Windows 7/10
// - Unix/Posix - Linux
// - Unix/Posix - Mac OS X
// TODO: Add more later such as IOS, android and DOS
// see https://github.com/gpakosz/whereami/blob/master/src/whereami.h
// for inspiration.


#if defined(_WIN32) || defined(_WIN64)
#define FSH_WINDOWS
#elif (defined(__APPLE__) && defined(__MACH__))
#define FSH_MAC_OS
#elif (defined(__linux__) || defined(linux) || defined(__linux))
#define FSH_LINUX
#else
#error "OS not supported."
#endif

// TODO: Load these
#define FSH_PATH_MAX 4000
#define FSH_FILE_MAX 500

#ifdef PATH_MAX
#define FSH_PATH_MAX PATH_MAX
#endif
#ifdef FILE_MAX // TODO: Probably wrong.
#define FSH_FILE_MAX FILE_MAX
#endif


#if defined(FSH_WINDOWS)
#define FSH_PATH_SEP '\\'
#define FSH_PATH_SEP2 '/'
#elif defined(FSH_LINUX)
#define FSH_PATH_SEP '/'
#define FSH_PATH_SEP2 '/'
#elif defined(FSH_MAC_OS)
#define FSH_PATH_SEP '/'
#define FSH_PATH_SEP2 '/'
#else
#error "OS path seperators not found."
#endif


#include "env_fopen.h"
#include "get_cwd.h"
#include "get_execd.h"
#include "is_absolute.h"



#endif // FSH_FSH_H