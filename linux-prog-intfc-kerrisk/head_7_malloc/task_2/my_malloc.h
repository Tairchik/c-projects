#include <sys/user.h>
#define CHUNK_SIZE PAGE_SIZE * 4

typedef struct FreeBlock {
    size_t size;               // Поле L (8 байт)
    struct FreeBlock *prev;    // Поле P (8 байт)
    struct FreeBlock *next;    // Поле N (8 байт)
} FreeBlock;

void* my_malloc(size_t size);
void my_free(void* ptr);