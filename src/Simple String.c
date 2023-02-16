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

#include <Simple String.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String
{
    char* data;
    unsigned int len, bytes;
    int refrenced;
} *String;

unsigned int String_StringSize(const char* text)
{
    unsigned int current = 0;
    while(text[current] != '\0')
    {
        current++;
    }

    return current;
}

int String_HasFreeSpace(String str)
{
    if(str->len+1 < str->bytes)
        return 1;
    else
        return 0;
}

String String_CreateSizeOf(unsigned int size)
{
    String str = malloc(sizeof(String));

    unsigned int len = size;
    unsigned int bytes = size+1;
    str->len = len;
    str->bytes = bytes;
    str->data = (char*)malloc(bytes);
    str->data[len] = '\0';

    return str;
}

String String_Create(const char* text)
{
    String str = malloc(sizeof(String));

    if(text != NULL)
    {
        unsigned int len = String_StringSize(text);
        unsigned int bytes = len+1;
        str->len = len;
        str->bytes = bytes;
        str->data = (char*)malloc(bytes);
        memcpy(str->data, text, len);
        str->data[len] = '\0';
    }
    else
    {
        str->len = 0;
        str->bytes = 1;
        str->data = (char*)malloc(1);
        str->data[0] = '\0';
    }

    return str;
}

String String_CreateFromFile(const char* path)
{
    FILE* file = fopen(path, "rb");

    if(file == NULL)
    {
        fclose(file);
    }

    fseek(file, 0, SEEK_END);
    unsigned int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    String str = String_CreateSizeOf(fileSize);

    fread(str->data, 1, fileSize, file);
    fclose(file);

    return str;
}

String String_SubString(String str, unsigned int start, unsigned int end)
{
    unsigned int len = 0;

    for(unsigned int i = start; i < end; i++)
    {
        len++;
    }

    String result = String_CreateSizeOf(len);

    for(unsigned int i = start; i < end; i++)
    {
        result->data[i-start] = str->data[i];
    }

    result->data[result->len] = '\0';

    return result;
}

void String_Destroy(String str)
{
    if(str->refrenced == 0)
        free(str->data);

    free(str);
}

//WIP
void String_Swap(String str1, String str2)
{
    String str3 = String_Create(String_GetString(str1));
    String_Destroy(str1);
    str1 = String_Create(String_GetString(str2));
    String_Destroy(str2);
    str2 = String_Create(String_GetString(str3));

    String_Destroy(str3);
}

int String_CompareString(String str1, String str2)
{
    int result = 1;

    if(str1->len = str2->len)
    {
        for(unsigned int i = 0; i < str1->len; i++)
        {
            if(str1->data[i] != str2->data[i])
                result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}

void String_CopyString(String dst, String src)
{
    if(dst->refrenced == 0)
        free(dst->data);

    src->refrenced = 1;
    dst->data = src->data;
    dst->len = src->len;
    dst->bytes = src->bytes;
}

void String_Append(String str, const char* text)
{
    unsigned int textSize = String_StringSize(text);
    String result = String_CreateSizeOf(str->len+textSize);

    result->len = textSize + str->len;
    result->bytes = result->len+1;

    for(unsigned int i = 0; i < str->len; i++)
    {
        result->data[i] = str->data[i];
    }

    for(unsigned int i = str->len; i < result->len; i++)
    {
        result->data[i] = text[i-str->len];
    }

    result->data[result->len] = '\0';
    
    String_CopyString(str, result);
    String_Destroy(result);
}

void String_AppendString(String str, String text)
{
    String result = String_CreateSizeOf(str->len+text->len);

    for(unsigned int i = 0; i < str->len; i++)
    {
        result->data[i] = str->data[i];
    }

    for(unsigned int i = str->len; i < result->len; i++)
    {
        result->data[i] = text->data[i-str->len];
    }

    result->data[result->len] = '\0';
    
    String_CopyString(str, result);
    String_Destroy(result);
}

void String_AppendChar(String str, const char text)
{
    String result = String_CreateSizeOf(str->len+1);
    
    for(unsigned int i = 0; i < str->len; i++)
    {
        result->data[i] = str->data[i];
    }

    result->data[result->len-1] = text;
    result->data[result->len] = '\0';

    String_CopyString(str, result);
    String_Destroy(result);
}

void String_Insert(String str, const char* text, unsigned int pos)
{
    unsigned int textSize = String_StringSize(text), lastI;
    String result = String_CreateSizeOf(str->len+textSize+1);

    for(unsigned int i = 0; i <= pos; i++)
    {
        result->data[i] = str->data[i];
        lastI = i;
    }

    for(unsigned int i = pos; i < pos+textSize; i++)
    {
        result->data[i] = text[i-pos];
    }

    for(unsigned int i = pos+textSize; i <= result->len; i++)
    {
        result->data[i] = str->data[lastI+i-(pos+textSize)];
    }

    result->data[result->len] = '\0';
    String_CopyString(str, result);
    String_Destroy(result);
}

void String_InsertString(String str, String text, unsigned int pos)
{
    unsigned int textSize = text->len, lastI;
    String result = String_CreateSizeOf(str->len+textSize+1);

    for(unsigned int i = 0; i <= pos; i++)
    {
        result->data[i] = str->data[i];
        lastI = i;
    }

    for(unsigned int i = pos; i < pos+textSize; i++)
    {
        result->data[i] = text->data[i-pos];
    }

    for(unsigned int i = pos+textSize; i <= result->len; i++)
    {
        result->data[i] = str->data[lastI+i-(pos+textSize)];
    }

    result->data[result->len] = '\0';
    String_CopyString(str, result);
    String_Destroy(result);
}

void String_InsertChar(String str, const char text, unsigned int pos)
{
    unsigned int lastI;
    String result = String_CreateSizeOf(str->len+2);

    for(unsigned int i = 0; i <= pos; i++)
    {
        result->data[i] = str->data[i];
        lastI = i;
    }

    result->data[pos] = text;

    for(unsigned int i = pos+1; i <= result->len; i++)
    {
        result->data[i] = str->data[lastI+i-(pos+1)];
    }

    result->data[result->len] = '\0';
    String_CopyString(str, result);
    String_Destroy(result);
}

//TODO: WIP(Replace)
void String_Replace(String str, const char* text, unsigned int start)
{
    unsigned int textSize = String_StringSize(text);

    if(textSize < str->len)
    {
        for(unsigned int i = start; i < str->len && i-start < textSize; i++)
        {
            str->data[i] = text[i-start];
        }
    }
}

void String_ReplaceString(String str, String text, unsigned int start)
{
    if(text->len < str->len)
    {
        for(unsigned int i = start; i < str->len && i-start < text->len; i++)
        {
            str->data[i] = text->data[i-start];
        }
    }
}

void String_ReplaceChar(String str, const char text, unsigned int start)
{
    if(1 < str->len)
    {
        str->data[start] = text;
    }
}

//WIP
void String_Move(String str, unsigned int start1, unsigned int end1, unsigned int pos)
{

}

void String_Remove(String str, unsigned int start, unsigned int end)
{
    unsigned int lastI;
    String result = String_CreateSizeOf(str->len), new_Result;

    for(unsigned int i = 0; i < start; i++)
    {
        result->data[i] = str->data[i];
        lastI = i;
    }

    lastI++;

    for(unsigned int i = end; i <= result->len; i++)
    {
        result->data[lastI+(i-end)] = str->data[i];
    }

    result->data[result->len] = '\0';
    new_Result = String_CreateSizeOf(String_StringSize(result->data));

    for(unsigned int i = 0; i < new_Result->len; i++)
    {
        new_Result->data[i] = result->data[i];
    }

    String_CopyString(str, new_Result);

    free(new_Result);
    String_Destroy(result);
}

const char* String_GetString(String str)
{
    return str->data;
}

unsigned int String_GetSize(String str)
{
    return str->len;
}