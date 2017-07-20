#include <stdio.h>
#include <ctype.h>
#include "tlp_parse.h"

void hexdump (void *_data,  unsigned int size)
{
	const unsigned char *data = (const unsigned char *)_data;
	unsigned int offset = 0, i;
	unsigned int n;

	while (offset < size) {
		printf("0x%08x  ", offset + (unsigned int)_data);
		n = size - offset;
		if (n > 16) {
			n = 16; 
		}   

		for (i = 0; i < 16; ++i) {
			if (i == 8) {
				printf(" ");
			}   

			if (offset + i < size) {
				printf("%02x ", data[offset + i]);
			} else {
				printf("   ");            }   
		}   
		printf(" ");

		for (i = 0; i < n; ++i) {
			if (isprint(data[offset + i])) {
				printf("%c", data[offset + i]);
			} else {
				printf(".");
			}   
		}   
		printf("\n");
		offset += 16; 
	} 
}  
