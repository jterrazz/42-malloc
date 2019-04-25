// Realloc de 0
// Realloc from LARGE to TINY

#include "test.h"

void        print(char *s)
{
	write(1, s, strlen(s));
}

static void test_1()
{
	char    *addr1;
	char    *addr2;
	char    *addr3;

	addr1 = (char *)malloc(1 * M1);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char *)malloc(16 * M1);
	addr3 = (char *)realloc(addr1, 128* M1);
	addr3[127 * M1] = 42;
	print(addr3);
	show_alloc_mem();
	free(addr3);
	free(addr2);
	free(addr1);
}

void run_realloc_tests(void)
{
    printf("Running malloc tests\n");
    test_1();
}
