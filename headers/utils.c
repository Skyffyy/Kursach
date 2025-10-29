#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Небольшие реализации строковых утилит без <string.h> */

int strEqual(const char *a, const char *b){
    if(!a || !b) return 0;
    int i = 0;
    while(a[i] && b[i]){
        if(a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

void strCopy(char *dest, const char *src){
    if(!dest || !src) return;
    int i = 0;
    while(src[i]){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int strLen(const char *s){
    if(!s) return 0;
    int i = 0;
    while(s[i]) i++;
    return i;
}

char* strDup(const char *s){
    if(!s) return NULL;
    int n = strLen(s);
    char *p = malloc(n + 1);
    if(!p) return NULL;
    for(int i=0;i<=n;i++) p[i] = s[i];
    return p;
}

/* Лексикографическое сравнение, как strcmp */
int strCompare(const char *a, const char *b){
    if(!a || !b){
        if(a==b) return 0;
        return a ? 1 : -1;
    }
    int i = 0;
    while(a[i] && b[i]){
        unsigned char ca = (unsigned char)a[i];
        unsigned char cb = (unsigned char)b[i];
        if(ca != cb) return ca - cb;
        i++;
    }
    return (unsigned char)a[i] - (unsigned char)b[i];
}