#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <libgen.h>
#define __USE_XOPEN
#include <time.h>
#include <locale.h>
 
char *timetostr(time_t time, char *buf, int buf_len) {
    struct tm *info;
    memset(&info, 0, sizeof(struct tm*));
    info = localtime(&time);
    strftime(buf, buf_len, "%d %b %Y", info);
    return buf;
}
 
time_t strtotime (const char *date) {
    struct tm result;
    memset(&result, 0, sizeof(struct tm));
    strptime(date, "%d/%m/%Y", &result);
    return mktime(&result);
}
 
void listfiles(const char *name, FILE *f, int size1, int size2, time_t date1, time_t date2, char *exefile) {
 
	DIR *dir;
	struct stat info;
	struct dirent *entry;
	char *date;
 
	if ( !(dir = opendir(name))) {
		fprintf(stderr, "%s : %s : error opening\n", exefile, name);
		return;
	}
 
	while ( (entry = readdir(dir)) != NULL ) {
		char *path = (char *) malloc(sizeof(char)*(strlen(name)+strlen(entry->d_name) ));
		sprintf(path, "%s/%s", name, entry->d_name);
 
		if (entry->d_type == DT_DIR) {
			if ( strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		        	continue;
		    	listfiles(path, f, size1, size2, date1, date2, exefile);
		} 
		else if (entry->d_type == DT_REG) {
			stat(path, &info); 
 
		    	if (info.st_size >= size1 && info.st_size <= size2 && difftime(date2, info.st_mtime) >= 0 
		               && difftime(info.st_mtime, date1) >= 0) {
					int date_size = sizeof(char) * 100;
		        	date = (char *)malloc(date_size);
			    	printf("%s %ld %s\n", path, info.st_size, timetostr(info.st_mtime, date, date_size));
 
			    	if (fprintf(f, "%s %ld %s\n", path, info.st_size, timetostr(info.st_mtime, date, date_size)) < 0)
						fprintf( stderr, "%s : %s : error writing to file\n", exefile, path);		
			    	free(date);
		    	}
		}
		free(path);
	}
 
	if ( closedir(dir) != 0 ) {
		fprintf( stderr, "%s : %s : %s\n", exefile, name, strerror(errno));
		return;	
	}
}
 
int main(int argc, char *argv[]) {
 
    char *exefile = basename(argv[0]);
	FILE *file_list;
	setlocale(LC_TIME,"ru_RU.UTF-8");
 
	if (argc != 7) {
		fprintf( stderr, "%s: incorrect number of arguments!\n", exefile);
		return 1;
	}
 
	if ( (file_list = fopen(argv[2], "w")) == NULL) {
		fprintf(stderr, "%s : %s : unable to open file\n", exefile, argv[2]);
		return 1;
	}
 
	int size1 = atoi(argv[3]);
	int size2 = atoi(argv[4]); 
	time_t date1 = strtotime(argv[5]);
	time_t date2 = strtotime(argv[6]);
	char *fullpath=(char *)malloc(sizeof(char)*512);
 
	if (! (size2 < 0 || size2 < size1)) {
        	if (! (date1 < 0 || date2 < 0) ) {                   
	                if (realpath(argv[1], fullpath) != NULL) {
 
	                	listfiles(fullpath, file_list, size1, size2, date1, date2, exefile);
	                } 
	                else {
	                	fprintf(stderr, "%s : %s \n", exefile, strerror(errno));
	                } 
	          }  
		  else {
		        fprintf(stderr, "%s : wrong date arguments\n", exefile);
		  }   
	 } 
         else {
         	fprintf(stderr, "%s : wrong size arguments\n", exefile);
	 } 
 
	 if ( fclose(file_list) == EOF) {
		fprintf(stderr, "%s : %s : %s \n", exefile, argv[2], strerror(errno)); 	
	 }   
 
	 free(fullpath);
	 return 0;
}
