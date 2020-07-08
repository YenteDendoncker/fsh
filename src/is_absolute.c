#include "is_absolute.h"

#include "fsh.h"

// TODO: If ever implementing for DOS see https://docs.microsoft.com/en-us/dotnet/standard/io/file-path-formats
/**
 * fsh_is_absolute
 * Checks if a filepath is an absolute filepath.
 **/ 
#if defined(FSH_WINDOWS)
#define FSH_IS_VALID_WIN_VOLUME(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
int fsh_is_absolute(const char* filepath) {
    char maybe_volume = filepath[0];
    char maybe_colon = filepath[1];
    char maybe_path_sep = filepath[2];
    if (FSH_IS_VALID_WIN_VOLUME(maybe_volume)) {
        if (maybe_colon == ':') {
            if (maybe_path_sep == '/' || maybe_path_sep == '\\') {
                // Absolute path from the root of given drive
                // e.g. C:\Documents\Newsletters\Summer2018.pdf
                return 1;
            }
            // Relative path with given drive
            // e.g. C:Projects\apilibrary\apilibrary.sln
            return 0;
        }
        // Relative path
        // e.g. temp\January.xlsx
    }
    if (filepath[0] == '/' || filepath[0] == '\\') {
        // Absolute filepath from the root of the current drive
        // e.g; \Program Files\Custom Utilities\StringFinder.exe
        return 1;
    }
    // Relative path, relative to the current workning directory
    // e.g. 2018\January.xlsx or ..\Publications\TravelBrochure.pd
    return 0;
}
#elif defined(FSH_LINUX)
int fsh_is_absolute(const char* filepath) {
    return filepath[0] == '/';
}
#elif defined(FSH_MAC_OS)
int fsh_is_absolute(const char* filepath) {
    return filepath[0] == '/';
}
#else
#error "is_absolute not implemented for this platform."
#endif