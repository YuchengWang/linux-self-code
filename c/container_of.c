#include <stdio.h>

/*
 * Copied from include/linux/...
 */

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})


int main(int argc, char* argv[]){

	/* statement, the x result is 5*/
	int x = ({1; 2;}) + 3;
	printf("%d\n", x);

	x = 5;
	typeof(x) y = 6;
	printf("%d %d\n", x, y);

	struct s {
		char m1;
		char m2;
	}s_t;
	char *m1, *m2;
	m1 = &(s_t.m1);
	m2 = &(s_t.m2);

	/* This will print 1 */
	printf("m1 %d\n", &((struct s*)0)->m1);
	printf("m2 %d\n", &((struct s*)0)->m2);

	printf("s  addr:0x%08x\n", &s_t);
	printf("m1 addr:0x%08x\n", m1);
	printf("m2 addr:0x%08x\n", m2);
	printf("m1 addr:0x%08x\n", container_of(m1, struct s, m1));
	printf("m2 addr:0x%08x\n", container_of(m2, struct s, m2));


	return 0;
}
