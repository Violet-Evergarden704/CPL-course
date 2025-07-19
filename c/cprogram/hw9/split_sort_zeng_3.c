#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sz;

int mystrcmp(const void * stra, const void * strb) {
    char * a =  *(char ** )stra;
    char * b =  *(char ** )strb;
    while (((*a) != '\0') && ((*b) != '\0')) {
        if ((*a) != (*b)) {
            return (*a) - (*b);
        }
        a++; b++;
    }
    return (*a) - (*b);
}

char ** strsplit(char * s, char * tag) {
    char ** res, ** p;
    char * ptr;
    while (*s != '\0') {
        if (*s == *tag) {
            s++;
            continue;
        }
        char * tmp = (char *)malloc(101 * sizeof(char));
        ptr = tmp;
        sz++;
            p = (char **)malloc(sz * sizeof(char *));
        for (int i = 0; i < sz - 1; i++) {
        p[i] = res[i];
        }
        if (sz > 1) free(res);
        res = p;
        p = nullptr;
        res[sz - 1] = tmp;
        while (*s != '\0' && *s != *tag) {
         *ptr = *s;
        s++; ptr++;
        }
        *ptr = '\0';
    }
    char ** ret = res;
    return ret;
}

int main() {
    char str[10001], c[2];
    scanf("%s %s", str, c);
        char ** table = strsplit(str, c);
        qsort(table, sz, sizeof(char *), mystrcmp);
    for (int i = 0; i < sz; i++) {
        printf("%s\n", (*table));
        table++;
    }
    return 0;
}