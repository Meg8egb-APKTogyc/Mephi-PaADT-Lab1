#include "../headers/ErrorHandler.h"
#include <string.h>

const char* error_str(ErrorCode error) {
    switch (error) {
        case EH_OK: return "No error";
        case EH_ERROR_NULL_POINTER: return "Null pointer detected";
        case EH_ERROR_INDEX_OUT_OF_RANGE: return "Index out of range";
        case EH_ERROR_MEMORY_ALLOCATION: return "Memory allocation failed";
        case EH_ERROR_INVALID_INPUT: return "Invalid input parameters";
        case EH_ERROR_FILE_IO: return "File I/O error";
        default: return "Unknown error";
    }
}