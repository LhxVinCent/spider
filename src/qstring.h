#ifndef _QSTRING_H_
#define _QSTRING_H_


extern char* strcat2(int argc,const char*str1,const char* str2);
extern char* strim(char* str);
extern char** strsplit(char* line,char delimeter,int* count,int limit);
extern int yesnotoi(char* str);
#endif
