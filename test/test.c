#include <Simple String.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    String str = String_Create("Marwan");
    String str2 = String_CreateFromFile("test.txt");

    String_Swap(str, str2);

    String_AppendChar(str, (char)100);

    printf("\nString1: %s\nString2: %s\n", String_GetString(str), String_GetString(str2));

    String_Destroy(str);
    String_Destroy(str2);
}