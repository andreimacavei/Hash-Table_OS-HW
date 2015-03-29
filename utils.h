
#ifndef UTILS_H_
#define UTILS_H_


#define DIE(assertion, call_description)                \
    do {                                \
        if (assertion) {                    \
            fprintf(stderr, "(%s, %d): ",           \
                    __FILE__, __LINE__);        \
            perror(call_description);           \
            exit(EXIT_FAILURE);             \
        }                           \
    } while (0)

#if defined DEBUG
#define dprintf(format, ...)                    \
    fprintf(stderr, " [%s(), %s:%u] " format,       \
            __func__, __FILE__, __LINE__,   \
            ##__VA_ARGS__)
#else
#define dprintf(format, ...)                    \
    do {                            \
    } while (0)
#endif

#endif
