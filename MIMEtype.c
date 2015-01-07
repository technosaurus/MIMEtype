// Copyright Bradley Conroy 2014.
#define MAGIC_CHECK 0 //0 to avoid (slower) file access - only use ext.
#include <stdio.h>
#include <string.h>
#include <libgen.h> //basename TODO replace it with const version
#include <fcntl.h>  //open

#define APPLICATION "\x00"
#define AUDIO "\x01"
#define CHEMICAL "\x02"		
#define IMAGE "\x03"		
#define INODE "\x04"		
#define MESSAGE "\x05"		
#define MODEL "\x06"		
#define MULTIPART "\x07"		
#define TEXT "\08"		
#define VIDEO "\09"

const char *major_types[]={"application","audio","chemical","image","inode","message","model","multipart","text","video"};
#define LEN(x) (sizeof(x)/sizeof(x[0])-2)

#include "mimes0.h"
#include "mimes4.h"
#include "mimes.h"

static inline const char *mime_from_ext(const char *ext){
	/* "sane" fallback?
		static char guess[128]="application/x-";
		strcat(guess,ext);
	*/
	if (ext==NULL) return NULL;
	size_t bot=0, len=LEN(mimes), top=len, i=(top>>1)&(~1);
	int cmp;
	for (; bot<=top && i<=len; i=((bot+top)>>1)&(~1)){
		cmp=strcmp(ext,mimes[i]);
		if (! cmp) return mimes[i+1]; //match found
		else if (cmp>0) bot=i+2;
		else top=i-2;
	}
	ext=strchr(ext,'.');
	return (ext)?mime_from_ext(ext+1):NULL;
}

static inline void putmime(const char *s){
	if (!s) s=APPLICATION "octet-stream";
	printf("%s/%s\n",major_types[*s],s+1);
}

static inline void lowercase(char *s){
	while(*s){
		*s=tolower(*s);
		++s;
	}
}

static const char *mime_search(const char **mimes,size_t len,const char *buf){
	size_t bot=0, top=len, i=((bot+top)>>1)&(~1);
	int cmp;
	for (; bot<=top && i<=len; i=((bot+top)>>1)&(~1)){
		cmp=memcmp(buf,mimes[i]+1,*mimes[i]);
		if (! cmp) return mimes[i+1]; //match found
		else if (cmp>0) bot=i+2;
		else top=i-2;
	}
	return NULL;
}

static inline const char *mime_from_magic(int fd){
	#define BUFLEN 256 //must be larger than max offset + max magic length
	char buf[BUFLEN];
	const char *ret;
	return (read(fd,buf,BUFLEN) < BUFLEN)? NULL:
		( ret = mime_search(mimes0,LEN(mimes0),buf) ) ? ret :
		mime_search(mimes4,LEN(mimes4),buf+4);
		//TODO mimes8 and mimesX + adjust BUFLEN to accomodate
}


const char *get_mime(char *path){
	char temp[strlen(path)+1], *fname, *ext;
	strcpy(temp,path); //todo rewrite own basename to take const char*
	fname = basename(temp);
	ext = strchr(fname,'.');
	if (ext == NULL) ext = fname;
	else ext++;
	lowercase(ext);
	const char *ret=mime_from_ext(ext);
#if MAGIC_CHECK
	if (ret == NULL){
		int fd = open(path,04000);
		if (fd>=0){
			ret=mime_from_magic(fd);
			close(fd);
		}//else return something more useful than NULL?
	}
#endif
	return ret;
}

int main(int argc, char **argv){
	while (--argc){
		printf("%s : ",argv[argc]);
		putmime(get_mime(argv[argc]));
	}
	return 0;
}
