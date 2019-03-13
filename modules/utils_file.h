#ifndef __UTILITIES_FILE_H__
#define __UTILITIES_FILE_H__

#include "utils_types.h"
#include "utils_string.h"

/*----------------------------------------------------------------*/
unsigned long file_sizeof(const char* path);
char* file_read_text(const char* path);
void file_write_text(const char* path, const char* buffer);
char* file_get_extension(const char* path);
void file_append_line(const char* path, const char* line);
/*----------------------------------------------------------------*/

void file_append_line(const char* path, const char* line)
{
    /*
     *  @todo: applend a line text to file
     */
    char* buffer = (char*)malloc(file_sizeof(path) + strlen(line) + 1);
    char* content = file_read_text(path);
    if (content == NULL)
        file_write_text(path, line);
    else
    {
        sprintf(buffer, "%s%s", content, line);
        file_write_text(path, buffer);
        free(content);
    }
    free(buffer);
    return;
}

unsigned long file_sizeof(const char* path)
{
    /*
     *  todo @file_sizeof get size of @path
     *  if @path is not a file, return -1
    */
    FILE* fp = fopen(path, "r");
    if (fp == NULL) return -1;
    fseek(fp, 0L, SEEK_END);
    unsigned long fs = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    fclose(fp);
    return fs;
}

char* file_read_text(const char* path)
{
    /*
     *  todo @file_read_text read all text from @path
     *  if @path is not found, return NULL
    */
    FILE* fp = fopen(path, "r");
    if (fp == NULL) return NULL;
    int fs = file_sizeof(path);
    char* buffer = (char*)malloc(fs + 1);
    fread(buffer, fs, 1, fp);
    buffer[fs] = '\0';
    fclose(fp);
    return buffer;
}

void file_write_text(const char* path, const char* buffer)
{
    /*
    *  todo @file_write_text write @buffer to @path
    */
    FILE* fp = fopen(path, "w");
    if (fp == NULL) return;
    fwrite(buffer, strlen(buffer), 1, fp);
    fclose(fp);
}
char* file_get_extension(const char* path)
{
    /*
     *  todo @file_get_extension extension of a file
     *  usage:
     *      char* file_get_extension("hello.txt") -> txt
    */
    if (string_count_cha(path, '.') == 0) return "";
    char* ext = strdup(path);
    while(string_count_cha(ext, '.') > 0)
        ext = string_cut(ext, '.');
    return ext;
}

#endif // __UTILITIES_FILE_H__