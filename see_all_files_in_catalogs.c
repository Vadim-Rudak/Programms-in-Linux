#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <errno.h>

int find(const char *dirName, FILE *f, int minSize, int maxSize, int count)
{
    DIR* dir;
    struct dirent *de;
    struct stat st;    
    char argDir[PATH_MAX + 1];
    char insideDir[PATH_MAX + 1];
    if((dir = opendir(dirName)) == NULL)
        err(1, "opendir: '%s'", dirName);
    while((de = readdir(dir)) != NULL)
    {
        if(strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0)
            continue;
        realpath(de->d_name, argDir);
        realpath(de->d_name, insideDir);
        stat(argDir, &st);
        if(S_ISDIR(st.st_mode))
        {
            chdir(insideDir);
            count = find(insideDir, f, minSize, maxSize, count);
            chdir("..");
        }
        if(S_ISREG(st.st_mode))
        {
            if(st.st_size > minSize && st.st_size < maxSize)
                fprintf(f, "%s, Размер; %llu б.\n", argDir, st.st_size);
                //printf("%s, Размер; %llu б.\n", argDir, st.st_size);
            count++;
        }
    }
    if(closedir(dir) == -1)
        err(1, "closedir: '%s'", dirName);
    return count;
}

int main(int argc, char **argv)
{   
    FILE *f;
    int minSize = atoi(argv[2]);
    int maxSize = atoi(argv[3]);
    int count = 0;
    if((f = fopen(argv[4], "a")) == NULL)
        printf("Не удалось открыть файл");
    chdir(argv[1]);
    printf("Просмотрено файлов: %i \n", find(argv[1], f, minSize, maxSize, count));
    return 0;
}

