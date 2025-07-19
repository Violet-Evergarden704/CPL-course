#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define NUM 101

char str_read[10010], len, c;
int substr_num;
char sub_str[110][110];
int pos;
char * ans[110];

bool mystrcmp(char * stra, char * strb) {
    while (((*stra) != '\0') && ((*strb) != '\0')) {
        if (*stra != *strb) {
            return (*stra) < (*strb);
        }
        stra++; strb++;
    }
    return (*stra) < (*strb);
}

void quicksort(char ** arr, int l, int r) {
    if (l >= r) return;
    int posl = l, posr = r;
    while(posl < posr) {
        char * tmp;
        while (posl < posr && mystrcmp(arr[posl], arr[posr])) posr--;
        tmp = arr[posl]; arr[posl] = arr[posr]; arr[posr] = tmp;
        while (posl < posr && mystrcmp(arr[posl], arr[posr])) posl++;
        tmp = arr[posl]; arr[posl] = arr[posr]; arr[posr] = tmp;
    }
    quicksort(arr, l, posl - 1); quicksort(arr, posl + 1, r);
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
    quicksort(ans, 0, substr_num - 1);
    for (int i = 0; i < substr_num; i++) {
        printf("%s\n", ans[i]);
    }
    return 0;
}