#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "c_printf.h"

// We define colors in ANSI escape codes.

#define NORMAL              "\e[0m"
#define BLACK               "\e[0;30m"
#define L_BLACK             "\e[1;30m"
#define RED                 "\e[0;31m"
#define L_RED               "\e[1;31m"
#define GREEN               "\e[0;32m"
#define L_GREEN             "\e[1;32m"
#define BROWN               "\e[0;33m"
#define YELLOW              "\e[1;33m"
#define BLUE                "\e[0;34m"
#define L_BLUE              "\e[1;34m"
#define MAGENTA 	   	 	"\e[0;35m"
#define L_PURPLE            "\e[1;35m"
#define CYAN                "\e[0;36m"
#define L_CYAN              "\e[1;36m"
#define GRAY                "\e[0;37m"
#define WHITE               "\e[1;37m"
#define BOLD                "\e[1m"
#define UNDERLINE           "\e[4m"
#define BLINK               "\e[5m"
#define REVERSE             "\e[7m"
#define HIDE                "\e[8m"
#define CLEAR               "\e[2J"
#define CLRLINE             "\r\e[K" //or "\e[1K\r"


// Because I want and easy to use library
// to print colors, I am going to define
// key values for every color code. So, will
// be more easier to include in the output.
static const char *c_key(char k) {
	switch(k){
	// Maybe I will add the word instead of a letter
	// or both. Let's see whats better.
	case 'r': return RED;
	case 'g': return GREEN;
	case 'y': return YELLOW;
	case 'b': return BLUE;
	case 'm': return MAGENTA;
	case 'c': return CYAN;
	case 'w': return WHITE;
	case 'u': return UNDERLINE;
	case 'n': return NORMAL;
	default:
		// Yes, we use c_printf lib on c_printf source. :)
		// Best dogfooding example?
		c_printf("[r]%s[-]%c\n", " - ERROR: invalid key for color: ", k);
		exit(1);
	}
}

// Counts occurences of character in string.
static int howMany(const char *s, char c) {
	int n = 0;
	while(*s){
		if(*s == c)
			++n;
		++s;
	}
	return n;
}

// This is to append characters to string.
// There's a better way for this?
static void c_append(char *s, char c) {
	s += strlen(s);
	s[0] = c;
	s[1] = 0;
}

// Reads printf format string, replacing color-indicating
// characters with their respective color codes.
static char *c_f(const char *f) {
	char *r = malloc(strlen(f) * 8);
	if(!r)
		return NULL;
	*r = 0;

	strcat(r, NORMAL);
	while(*f){
		if(f[0] == '[' && f[2] == ']'  && f[3] == '%'){
			strcat(r, c_key(f[1])), f += 3;
			while(!isalpha(*f))
				c_append(r, *f), ++f;
			c_append(r, *f), ++f;
			strcat(r, NORMAL);
		} else{
			c_append(r, *f);
			++f;
		}
	}
	strcat(r, NORMAL);
	return r;
}

// c_printf main function.
// What we really want to use
int c_printf(const char *cf, ...) {
	va_list args;
	va_start(args, cf);
	char *f = c_f(cf);
	if(f){
		vprintf(f, args);
		free(f);
		va_end(args);
		return 0;
	}
	return 1;
}
