#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <memory.h>

int getkol(char* dirn) 
{

int dsize=0;
DIR* dirs;
//if(*(dirn+(int)strlen(dirn)-1)==92) *(dirn+(int)strlen(dirn)-1)=0;
dirs = opendir(dirn);
if (dirs)
{
struct dirent* dirstr;
while(dirstr = readdir(dirs))
{

char* fnm=dirstr->d_name;
char* fullnm=(char*)alloca(strlen(dirn)+strlen(fnm)+1);
strcpy(fullnm,dirn);
strcat(fullnm,"/");
strcat(fullnm,fnm);
struct stat fst;
stat(fullnm,&fst); 

if(S_ISREG(fst.st_mode)&&!S_ISLNK(fst.st_mode)) 
{
dsize++;
} else

if(S_ISDIR(fst.st_mode)&&strcmp(fnm,".")&&strcmp(fnm,"..")&&!S_ISLNK(fst.st_mode))

{
dsize=dsize+getkol(fullnm); 
}

}
closedir(dirs); 
}

else printf("Couldn't open derictory - %s\n",dirn);

return dsize;

}

void getlist(int* _i,char** _str,char* dirn,int* _fsize)

{

DIR* dirs;

dirs = opendir(dirn);

if (dirs)

{

struct dirent* dirstr;

while(dirstr = readdir(dirs))

{
char* fnm=dirstr->d_name;
char* fullnm=(char*)alloca(strlen(dirn)+strlen(fnm)+1);
strcpy(fullnm,dirn);
strcat(fullnm,"/");
strcat(fullnm,fnm);
struct stat fst;
stat(fullnm,&fst);

if(S_ISREG(fst.st_mode)&&!S_ISLNK(fst.st_mode))

{

strcpy(_str[*_i],fullnm);

*(_fsize+*_i)=fst.st_size;

(*_i)++;

}

if(S_ISDIR(fst.st_mode)&&strcmp(fnm,".")&&strcmp(fnm,"..")&&!S_ISLNK(fst.st_mode))

{
getlist(_i,_str,fullnm,_fsize);
}

}
closedir(dirs);

}

else printf("Couldn't open derictory - %s\n",dirn);

}

int xfork(char *fnm1,char *fnm2,int* _fs)

{
int ppid = fork();
if(ppid==0)
{

int t=0;
FILE* fd1 = fopen(fnm1,"r");
FILE* fd2 = fopen(fnm2,"r");
while(abs(fgetc(fd1))==fgetc(fd2)) t++;

printf("\n****** PID: %d ******\n1> %s\n2> %s\n **** Result: %d of %d bytes match ****\n",getpid(),fnm1,fnm2,t,*_fs);
fclose(fd1);
fclose(fd2);

}

return ppid;

}

main(int argc, char *argv[])

{
if(argc>4)

{

puts("Put that info in argv: DIR1 DIR2 N");
exit(1);

}

char* fnm1=argv[1];
char* fnm2=argv[2];

int N;
if(!sscanf(argv[3],"%d",&N))
{ 
puts("Not whole number");
exit(1);
}

errno=0;
char** str1;
char** str2;
int* fsize1; 
int* fsize2;
int ksize1=getkol(argv[1]);
int ksize2=getkol(argv[2]);
printf("Total files found: %d ",ksize1+ksize2);

str1=malloc(ksize1*(sizeof(char*)));
str2=malloc(ksize2*(sizeof(char*)));
fsize1=malloc(ksize1*(sizeof(int)));
fsize2=malloc(ksize2*(sizeof(int)));
int i=0; 
while(i<ksize1)

{

*(str1+i)=malloc(512*sizeof(char));
i++;

}

i=0;
while(i<ksize2)

{

*(str2+i)=malloc(512*sizeof(char));
i++;

}

ksize1=0;
ksize2=0;
getlist(&ksize1,str1,argv[1],fsize1);
getlist(&ksize2,str2,argv[2],fsize2);
printf("Total files read: %d\n",ksize1+ksize2);

/*i=0;
while(i<ksize)

{

printf("%s -- %d bytes\n",*(str+i),*(size+i));

i++;

}*/

i=0; 
int fr=1; 
int k,n=0; 

while(i<ksize1)

{

k=0;
while(k<ksize2)

{

if(fr > 0)

{

if(*(fsize1+i)==*(fsize2+k))

{

if(n++>N) wait();

fr=xfork(*(str1+i),*(str2+k),fsize1+i);

}

k++;

} else break; 
}

i++;

}

if(fr>0)

{

while(wait()>0); 
char *err= strerror(errno);
printf("\nErrno result: %s \n",err);

}

i=0;
while(i<ksize1)

{

free(*(str1+i));
i++;

}

while(i<ksize2)

{

free(*(str2+i));
i++;

}

free(str1);
free(str2);
free(fsize1);
free(fsize2);
return 0;

}
