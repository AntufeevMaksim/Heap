
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

/* 
 both structures Block_struct and mmap_Block_struct
 must have 'size' field type of size_t on firts place
 because of free() function realization
*/

typedef struct Block_struct
{
    size_t size;
    struct Block_struct* next;
    struct Block_struct* prev;
    int is_empty;

} Block;

typedef struct mmap_Block_struct
{
    size_t size;
} mmap_Block;


#define BLOCK_STRUCT_SIZE (sizeof(Block))
#define MMAP_BLOCK_STRUCT_SIZE (sizeof(mmap_Block));

#define PAGE_SIZE 4096

static Block* first_block = NULL;


static void init()
{
    //
}

static void* use_sbrk_alloc(size_t size)
{
    void* addr = NULL;

    Block* curr_block = first_block;
    while (curr_block != NULL)
    {
        if (curr_block->is_empty && curr_block->size >= size)
        {
            curr_block->is_empty = 0;
            addr = (void*) (curr_block + 1);
            break;
        }
        curr_block = curr_block->next;
    }
    
    if (addr == NULL)
    {
        Block* new_block = (Block*) sbrk(0);
        sbrk(size + BLOCK_STRUCT_SIZE);

        new_block->is_empty = 0;
        new_block->next = first_block;
        new_block->prev = NULL;
        new_block->size = size;

        if (first_block != NULL)
        {
            first_block->prev = new_block;
        }

        first_block = new_block;

        addr = (void*) (first_block + 1);
    }

    return addr;

}

static void use_sbrk_free(void* ptr)
{
    Block* block = ((Block*) ptr) - 1;
    block->is_empty = 1;
}


static void* use_mmap_alloc(size_t size)
{
    size += MMAP_BLOCK_STRUCT_SIZE;

    void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    mmap_Block* block_ptr = (Block*) ptr;

    block_ptr->size = size;

    return (void*) block_ptr + 1;
}

static void use_mmap_free(void* ptr)
{
    mmap_Block* block = ((mmap_Block*) ptr) - 1;

    munmap((void*) block, block->size);
}


void* my_malloc(size_t size)
{
    void* ptr;
    if (size <= 128 * 1024)
    {
        ptr = use_sbrk_alloc(size);
    }
    else
    {
        ptr = use_mmap_alloc(size);
    }
    
    return ptr;
}

void my_free(void* ptr)
{
    size_t size = *((size_t*) ptr);

    if (size <= 128*1024)
    {
        use_sbrk_free(ptr);
    }
    else
    {
        use_mmap_free(ptr);
    }
}
