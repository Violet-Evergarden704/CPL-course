#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACK_SIZE 10001
#define INPUT_SIZE 10001
char table[10][50];
char input[2];
char buffer[10001] = {0};
int myindex = 0;
int cnt_row = 0, cnt_column = 0;
char ascii[10][50] = {
    "\033[31m", // red
    "\033[34m", // blue
    "\033[32m", // green
    "\033[1m",  // bold
    "\033[3m",  // italic
    "\033[4m",  // underline
    "\033[0m"   // reset
};

typedef struct elements
{
    int color;//0:unknown,1:red,2:blue,3:green
    int em;
    int i;
    int u;
    int o;
    char a;
} elements;
elements element[10][50];

typedef struct headline
{
    enum colorh
    {
        unknown1,
        RED1,
        GREEN1,
        BLUE1
    } color;
    int em;
    int i;
    int u;
    char *content;
} h;
h head[10001];
int h_count = 0;
// h元素
typedef struct paragraph
{
    enum colorp
    {
        unknown,
        RED,
        GREEN,
        BLUE
    } color;
    int em;
    int i;
    int u;
    char *content;
} p;
p para[10001];
int p_count = 0;
// p元素
typedef struct image
{
    char *src;
    int width;
} img;
img image[10001];
int img_count = 0;
// img元素
typedef struct division
{
    int w; // width
    int h; // height
    enum direction
    {
        ROW,
        COLUMN
    } direction;
    enum align_items
    {
        START1,
        CENTER1,
        END1,
        SPACE_EVENLY1
    } align_items;
    enum justify_content
    {
        START,
        CENTER,
        END,
        SPACE_EVENLY
    } justify_content;
} mydiv;
// div元素


void Init(void)
{
    for (int i = 0; i < myindex; i++)
    {
        buffer[i] = 0;
    }
    myindex = 0;
}

void p_check(const char a[])
{
    int flag = 0;
    char *tmp = strchr(a, ">");
    int element_len = tmp - a + 1;
    char *element = malloc(element_len + 10);
    element = strncpy(element, a, element_len);
    if (strstr(element, "red") != NULL)
    {
        printf("%s", ascii[0]);
        flag = 1;
    }
    if (strstr(element, "blue") != NULL)
    {
        printf("%s", ascii[1]);
        flag = 1;
    }
    if (strstr(element, "green") != NULL)
    {
        printf("%s", ascii[2]);
        flag = 1;
    }
    if (strstr(element, " em"))
    {
        printf("%s", ascii[3]);
        flag = 1;
    }
    if (strstr(element, " i"))
    {
        printf("%s", ascii[4]);
        flag = 1;
    }
    if (strstr(element, " u"))
    {
        printf("%s", ascii[5]);
        flag = 1;
    }
    int len = 0;
    for (int i = element_len; i < myindex - 4; i++)
    {
        printf("%c", a[i]);
        len++;
    }
    if (flag)
    {
        printf("%s\n", ascii[6]);
    }
    len=50-len;
    while (len--)
    {
        printf("%c", ' ');
    }
}
void h_check(char a[])
{
    int flag = 0;
    char *tmp = strstr(a, ">");
    int element_len = tmp - a + 1;
    char *element = malloc(element_len + 1);
    element = strncpy(element, a, element_len);
    if (strstr(element, "red") != NULL)
    {
        printf("%s", ascii[0]);
        flag = 1;
    }
    if (strstr(element, "blue") != NULL)
    {
        printf("%s", ascii[1]);
        flag = 1;
    }
    if (strstr(element, "green") != NULL)
    {
        printf("%s", ascii[2]);
        flag = 1;
    }
    if (strstr(element, " em"))
    {
        printf("%s", ascii[3]);
        flag = 1;
    }
    if (strstr(element, " i"))
    {
        printf("%s", ascii[4]);
        flag = 1;
    }
    if (strstr(element, " u"))
    {
        printf("%s", ascii[5]);
        flag = 1;
    }
    int len = 0;
    for (int i = element_len; i < myindex - 4; i++)
    {
        printf("%c", toupper(a[i]));
        len++;
    }

    if (flag)
    {
        printf("%s\n", ascii[6]);
    }
    len=50-len;
    while (len--)
    {
        printf("%c", ' ');
    }
}

void img_check(char a[])
{
    char *tmp = strstr(a, "src=");
    tmp += 5;
    char *src = malloc(100);
    while (*tmp != '"')
    {
        *src = *tmp;
        src++;
        tmp++;
    }
    char *temp = strstr(a, "width=");
    temp += 7;
    int width = 0;
    while (*temp != '"')
    {
        width = width * 10 + (*temp - '0');
        temp++;
    }
    image[img_count].src = src;
    image[img_count].width = width;
    img_count++;
    int len = strlen(src);
    int height = len / width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            table[cnt_row][cnt_column++] = *src;
            src++;
        }
        cnt_row++;
    }

    int main()
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                table[i][j] = ' ';
            }
        }
        while (1)
        {
            int flag = 0;
            char temp = getchar();
            if (temp == EOF)
                break;
            else
                buffer[myindex++] = temp;
            if ((strstr(buffer, "<p") != NULL) && (strstr(buffer, "</p>") != NULL))
            {
                p_check(buffer);
                Init();
                continue;
            }

            if ((strstr(buffer, "<h") != NULL) && (strstr(buffer, "</h>") != NULL))
            {
                h_check(buffer);
                Init();
                continue;
            }

            if ((strstr(buffer, "<img") != NULL) && (strstr(buffer, "</img>") != NULL))
            {
                img_check(buffer);
                Init();
                continue;
            }
        }
        return 0;
    }
