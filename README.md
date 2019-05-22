# Malloc
Ce projet consiste à écrire une librarie de gestion de l'allocation dynamique de la mémoire.

Le projet contient les fonctions:
- malloc()
- free()
- realloc()
- calloc()

Other functions included:
- show_alloc_mem(): Print the allocated zones
- show_alloc_mem_ex(): Print the hex dump of the mapped zones

``` bash
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
```


Realloc
- Does set to zero a calloced zone (like the real one)

Range divided in blocks
A range is a mapped zone
Metadatas are stocked on the mapped memory so we move



// Explain why we merge in readme => so we use the freed space more efficiently (bonus defrag)

Not using the return of munmap of purpose (because free doesnt return)


#include <sys/mman.h>
For mmap and munmap
