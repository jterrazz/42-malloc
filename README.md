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
