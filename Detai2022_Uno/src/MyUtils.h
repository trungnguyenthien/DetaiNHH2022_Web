#include <stdio.h>

char *int2Char(int n)
{
    char buf[100];
    return itoa(n, buf, 10);
}

char *float2Char(float f)
{
    char buffer[100];
    snprintf(buffer, 100, "%f", f);
    return buffer;
}