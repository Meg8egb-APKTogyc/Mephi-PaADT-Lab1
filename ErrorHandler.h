#pragma once

typedef enum {
    EH_OK = 0,
    EH_ERROR_NULL_POINTER,
    EH_ERROR_INDEX_OUT_OF_RANGE,
    EH_ERROR_MEMORY_ALLOCATION,
    EH_ERROR_INVALID_INPUT,
    EH_ERROR_FILE_IO,
} ErrorCode;

const char* error_str(ErrorCode error);

#define RETURN_IF_ERROR_TYPE(condition, error_code, ret_type, ret_val) \
    do { \
        if ((condition)) { \
            if (error) *error = (error_code); \
            return (ret_type)(ret_val); \
        } \
    } while (0)

#define RETURN_IF_ERROR(condition, error_code, ret_val) \
    do { \
        if ((condition)) { \
            if (error) *error = (error_code); \
            return (ret_val); \
        } \
    } while (0)

#define CHECK_ERROR(error) \
    do { \
        if ((error) != EH_OK) { \
            fprintf(stderr, "Ошибка в %s:%d: %s\n", __FILE__, __LINE__, error_str(error)); \
            return; \
        } \
    } while (0)

