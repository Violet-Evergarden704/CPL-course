#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM 101

char str_read[10010], len, c;
int substr_num;
char sub_str[110][110];
int pos;
char * ans[110];

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

int main() {
    scanf("%s", str_read);
    len = strlen(str_read);
    getchar();
    c = getchar();
        while (pos < len) {
        int cnt = 0;
    while (str_read[pos] != c) {
        sub_str[substr_num][cnt++] = str_read[pos++];
        }
        pos++;
        ans[substr_num] = sub_str[substr_num];
        substr_num++;
    }
    qsort(ans, substr_num, sizeof(char *), mystrcmp);
    for (int i = 0; i < substr_num; i++) {
        printf("%s\n", ans[i]);
    }
    return 0;
}