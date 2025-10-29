#include "utils.h"

int strEqual(const char *a, const char *b){
    int i=0;
    while(a[i] && b[i]){
        if(a[i]!=b[i]) return 0;
        i++;
    }
    return a[i]==b[i];
}

void strCopy(char *dest, const char *src){
    int i=0;
    while(src[i]){ dest[i]=src[i]; i++; }
    dest[i]='\0';
}

int strCompare(const char *a, const char *b){
    int i=0;
    while(a[i] && b[i]){
        if(a[i]!=b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        i++;
    }
    return (unsigned char)a[i] - (unsigned char)b[i];
}