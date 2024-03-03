#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    /*int i;
    printf("%d\n", argc);
    for(i=0; i<argc; i++)
        puts(argv[i]);*/
        
    FILE *f;
    int c = 0;
    char ch;
    int strNum = atoi(argv[2]);
    int strHop = strNum;
    if((f=fopen(argv[1], "r"))==NULL)
    {
        printf("Ошибка, нет возможности открыть файл!\n");
        exit(1);
    }
    else 
    {
        printf("Файл открыт\n");
        if(strNum == 0)
        {
            // Вывод всего текста сразу;
            while((ch=getc(f)) != EOF)
                printf ("%c", ch);
            fclose(f);
        }
        else
        {
            while((ch = getc(f)) != EOF){
                printf ("%c", ch);
                if(ch == '\n'){
                    // если обнаружен \n;
                    c++;	
                    if(c == (strNum)){
                        //printf("выведено strHop строк\n");
                        //Вывод следующей группы строк после ввода символа
                        getchar();
                        strNum += strHop;
                    }
                }
            }      
            fclose(f);       
        }
        
        return 0;
    }
}