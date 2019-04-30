/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:24:51 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/30 19:19:31 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void DumpHex(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	int sizes[] = {16, 32, 6, 64, 50, 48, 49, 61, 68, 420};
	int last_sizes[420];
	char *mallocs[420];
	int i = 0;
	int size = 0;

	while (i < 420) {
		size = sizes[rand() % 10];
		last_sizes[i] = size;
		mallocs[i] = malloc(size);
		while (size) {
			size--;
			mallocs[i][size] = (i + 1) % 255;
		}
		i++;
	}

	while (i--) {
		DumpHex(mallocs[i], last_sizes[i]);
	}

	// add random rewriting and reallocs

	return 0;
}
