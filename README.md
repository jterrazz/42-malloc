> Hey there, app enthusiasts! 👋 Ready to dive into the world of game-changing apps? At [jterrazz.com](https://jterrazz.com), I'm all about crafting useful applications and sharing the journey! Discover coding insights, self-improvement hacks, and sneak peeks of my latest projects (psst... my next app is all about leveling up in life! 🚀). Come along for the ride - you might just find the spark for your next big idea! 💡💻

# Malloc

Custom C implementation of the malloc library functions. It creates the shared library `libft_malloc.so` which can be used to replace malloc in any system commands.

[Access the related medium article here](https://medium.com/a-42-journey/how-to-create-your-own-malloc-library-b86fedd39b96)

It exposes the following methods:

```c
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t count, size_t size);
void *reallocf(void *ptr, size_t size);

// Debug calls

void show_alloc_mem(); // Print informations about allocated zones
void show_alloc_mem_ex(); // Print a hex dump of the heaps
```

## Commands

### Build

```bash
make
make clean # Clean temporary built files
make fclean # Clean all built files
```

> gcc uses -fPIC to generate position independent code (PIC) for shared libraries.

### Testing

```bash
# Use malloc with a ${CMD}
sh insert_lib.sh ${CMD} # ex: sh insert_lib.sh ls

# Run unit test
cd test
make && sh ./run_test.sh
```

## Implementation

To understand in detail this implementation, [**please refer to the medium article**](https://medium.com/a-42-journey/how-to-create-your-own-malloc-library-b86fedd39b96) of this project.

Bonus:
- `calloc()`, `reallocf()`
- Defragmentation of freed space
- Multi-thread safe with pthread
- Show hex dump of allocated zones with `show_alloc_mem_ex()`
- Debug environment variables: MyMallocStackLogging, MyMallocScribble, MyMallocFullLogging

### Structure

The **heap** stores data about a `mmap` zone

```c
typedef struct s_heap {
    struct s_heap	*prev;
    struct s_heap	*next;
    t_heap_group	group;
    size_t		    total_size;
    size_t		free_size;
    size_t		block_count;
} t_heap;
```

A **block** stores data about a `malloc` call.

```c
typedef struct s_block {
    struct s_block	*prev;
    struct s_block	*next;
    size_t		data_size;
    t_bool		freed;
} t_block;
```

### Constants

For better performance, we preallocate heaps for small malloc calls. We define 3 heap types: TINY, SMALL, LARGE.

```c
#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
#define SMALL_HEAP_ALLOCATION_SIZE (32 * getpagesize())
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)
```
