#include <Simple String.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    String str = String_Create("Hello, World!");

    printf("\nString: %s\n", String_GetString(str));

    String_Destroy(str);
}