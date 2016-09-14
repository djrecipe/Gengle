#include "GlobalTools.h"

#include <iostream>	
#include <stdarg.h>
#include <windows.h>

using namespace std;

void __cdecl dprint(const GLchar *format, ...)
{
	// --- Construct String --- //
	GLchar buf[8192], *p = buf;
	// ~ Parse Arguements
	va_list args;
	va_start(args, format);
	int n = _vsnprintf(p, sizeof buf - 3, format, args); // buf-3 is room for CR/LF/NUL
	va_end(args);
	p += (n < 0) ? sizeof buf - 3 : n;
	// ~ Fill Blankspace w/ Nulls
	while (p>buf && isspace(p[-1]))
		*--p = '\0';
	// ~ "Attach Rear" to String
	*p++ = '\r';
	*p++ = '\n';
	*p = '\0';
	// --- Output String --- //
	OutputDebugString(buf);
	return;
}