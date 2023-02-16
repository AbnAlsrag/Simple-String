/*
    ███████╗██╗███╗   ███╗██████╗ ██╗     ███████╗    ███████╗████████╗██████╗ ██╗███╗   ██╗ ██████╗ 
    ██╔════╝██║████╗ ████║██╔══██╗██║     ██╔════╝    ██╔════╝╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝ 
    ███████╗██║██╔████╔██║██████╔╝██║     █████╗      ███████╗   ██║   ██████╔╝██║██╔██╗ ██║██║  ███╗
    ╚════██║██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝      ╚════██║   ██║   ██╔══██╗██║██║╚██╗██║██║   ██║
    ███████║██║██║ ╚═╝ ██║██║     ███████╗███████╗    ███████║   ██║   ██║  ██║██║██║ ╚████║╚██████╔╝
    ╚══════╝╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝    ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ 

    This Library Was Made by ABN ALSRAG
    Simple String
    
    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
        claim that you wrote the original software. If you use this software
        in a product, an acknowledgment in the product documentation would be
        appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
*/

#ifndef Simple_String
#define Simple_String

typedef struct String *String;

String String_Create(const char* text);
String String_CreateFromFile(const char* path);
String String_SubString(String str, unsigned int start, unsigned int end);
void String_Destroy(String str);
void String_Swap(String str1, String str2);
int String_CompareString(String str1, String str2);
void String_CopyString(String dst, String src);
void String_Append(String str, const char* text);
void String_AppendString(String str, String text);
void String_AppendChar(String str, const char text);
void String_Insert(String str, const char* text, unsigned int pos);
void String_InsertString(String str, String text, unsigned int pos);
void String_InsertChar(String str, const char text, unsigned int pos);
void String_Replace(String str, const char* text, unsigned int start);
void String_ReplaceString(String str, String text, unsigned int start);
void String_ReplaceChar(String str, const char text, unsigned int start);
void String_Move(String str, unsigned int start1, unsigned int end1, unsigned int pos);
void String_Remove(String str, unsigned int start, unsigned int end);
const char* String_GetString(String str);
unsigned int String_GetSize(String str);

#endif