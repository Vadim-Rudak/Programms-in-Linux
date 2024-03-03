#include <stdio.h>

int filesum(char *name1, char *name2)
{
    FILE *file1, *file2;
    if(!((file1 = fopen(name1, "r")) && (file2 = fopen(name2, "w"))))
        return 1;
    char c = 0;
    while ((c = fgetc(file1)) != EOF)
        fputc(c, file2);
    return 0;
}

int main(int argc, char **argv)
{
    if(filesum(argv[1], argv[2]))
        puts("Ошибка");
        return 0;
}
