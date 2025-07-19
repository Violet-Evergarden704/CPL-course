#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1001

int cmp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
int check(char *a, char *b)
{
    int len1 = strlen(a);
    int num = 0;
    for (int i = 0; i < len1; i++)
    {
        if (a[i] == b[0])
            num++;
    }
    return num;
}

int main()
{
    char **ans = malloc(1000);
    char *tag = malloc(1);
    char input[LEN * LEN];
    scanf("%s", input);
    scanf("%c", tag);
    ans[0] = strtok(input, tag);
    int size = check(input, tag) + 1;
    for (int i = 1; i < size; i++)
    {
        ans[i] = strtok(0, tag);
    }
    qsort(ans, size, sizeof(*ans), cmp);
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", ans[i]);
    }
    return 0;
}