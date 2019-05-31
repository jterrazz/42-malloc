# Malloc
Ce projet consiste à écrire une librarie de gestion de l'allocation dynamique de la mémoire.
 is a shared library libft_malloc.so
Le projet contient les fonctions:
- malloc()
- free()
- realloc()
- calloc()

Other functions included:
- show_alloc_mem(): Print the allocated zones
- show_alloc_mem_ex(): Print the hex dump of the mapped zones

From the man
The function getpagesize() returns the number of bytes in a memory
       page, where "page" is a fixed-length block, the unit for memory
       allocation and file mapping performed by mmap(2).

You can type this command and it will always return the same value for your system/
```
getconf PAGE_SIZE
```
```
#define TINY_RANGE_ALLOCATION_SIZE (4 * getpagesize())
#define TINY_BLOCK_SIZE (TINY_RANGE_ALLOCATION_SIZE / 128)
#define SMALL_RANGE_ALLOCATION_SIZE (16 * getpagesize())
#define SMALL_BLOCK_SIZE (SMALL_RANGE_ALLOCATION_SIZE / 128)
```

Range size header: 48
Block size header: 32
For example, if getpagesize returns 4096,
We get a 1st header of 48 bytes, then 32 + block_size ...

Calc
16384 / 128 = 128 de 128 bytes (au minimum si pas de metadata) + 32 = 160 bytes ===> 102.4



``` bash
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
```

Range divided in blocks
A range is a mapped zone
Metadatas are stocked on the mapped memory so we move



// Explain why we merge in readme => so we use the freed space more efficiently (bonus defrag)

Not using the return of munmap of purpose (because free doesnt return)

// TODO On the readme show an integration by replacing free of the system with things like ls / ls -l / etc
// TODO explain how to inject in lib
// Make graph to show how memory behave


TEST
sh insert_lib.sh ls


SPECIAL CASES
realloc(NULL, 6);
realloc(ptr, 0);
Realloc with a size of zero is equivalent to free() on some C implementations, but not all.



realloc is conceptually equivalent to malloc + memcpy + free on the other pointer.

If the size of the space requested is zero, the behavior of realloc is implementation-defined. This is similar for all memory allocation functions that receive a size parameter of value 0. Such functions may in fact return a non-null pointer, but that must never be dereferenced.

Thus, realloc(ptr,0) is not equivalent to free(ptr). It may

be a "lazy" implementation and just return ptr
free(ptr), allocate a dummy element and return that
free(ptr) and return 0
just return 0 for failure and do nothing else.
So in particular the latter two cases are indistinguishable by application code.

This means realloc(ptr,0) may not really free/deallocate the memory, and thus it should never be used as a replacement for free.

##Testing
``` bash
make && sh ./run_test.sh
```

#include <sys/mman.h>
For mmap and munmap
