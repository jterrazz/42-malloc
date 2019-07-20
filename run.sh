#!/bin/sh
export DYLD_LIBRARY_PATH=$PWD
export DYLD_INSERT_LIBRARIES=$PWD/libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
