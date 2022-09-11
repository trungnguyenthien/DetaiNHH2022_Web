#include <stdio.h>

char *int2Char(int n)
{
    char *buf = new char[100];
    return itoa(n, buf, 10);
}

char *float2Char(float f)
{
    char *buffer = new char[100];
    snprintf(buffer, 100, "%f", f);
    return buffer;
}

bool skip()
{
    static int t = 0;
    t += 1;
    t = t % 250;
    return t != 1;
}

int number(bool next = false)
{
    static int currentNum = random(100, 130);
    if (next)
        currentNum++;
    return currentNum;
}