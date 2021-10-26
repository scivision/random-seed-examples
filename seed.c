#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    srand(0);
    printf("%d %d %d\n", rand(), rand(), rand());
}

// GNU,Intel,IntelLLVM,MSVC: 21238 7719 38
