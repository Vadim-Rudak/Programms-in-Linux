#include <stdio.h>
#include <stdlib.h>

void enterChars(FILE *f)
{
    char ch;
    for( ; ; )
    {
        scanf("%c", &ch);
        if(ch == '@')
        {
            printf("Выход\n");
            fclose(f);
		 break;
        }
	   else
	  {
            if(!ferror(f))
               fputc(ch, f);
            else printf("Ошибка записи!\n");
        }
    }
}
int main(int argc, char *argv[])
{
    FILE *f;
    
    if((f=fopen(argv[1], "w")) == NULL)
    {
        printf("Ошибка, нет возможности открыть файл!\n");
        exit(1);
    }
    else
    { 
        printf("Файл открыт\n");
        enterChars(f);
    }
    return 0;
}
