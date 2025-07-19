#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACK_SIZE 10001
#define INPUT_SIZE 10001
char table[10][50];
char input[2];
char buffer[10001] = {0};
int myindex = 0, flag = 0 ;
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
int count = 0;
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

int stack[STACK_SIZE];
int top = -1;

void push(char value)
{
    if (top >= STACK_SIZE - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = value;
}

int pop()
{
    if (top < 0)
    {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

int peek()
{
    if (top < 0)
    {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[top];
}

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == STACK_SIZE - 1;
}

void Init(void)
{
    for (int i = 0; i < myindex; i++)
    {
        buffer[i] = 0;
    }
    myindex = 0;
}

void check_print()
{
    
    for (int i = 0; i < count; i++)
    {
        if (head[i].color =="RED1" || para[i].color == "RED")
        {
            printf("%s", ascii[0]);
            flag=1;
        }
        if (head[i].color == "BLUE1" || para[i].color == "BLUE")
        {
            printf("%s", ascii[1]);
            flag=1;
        }
        if (head[i].color == "GREEN1" || para[i].color == "GREEN")
        {
            printf("%s", ascii[2]);
            flag=1;
        }
        if (head[i].em == 1 || para[i].em == 1)
        {
            printf("%s", ascii[3]);
            flag=1;
        }
        if (head[i].i == 1 || para[i].i == 1)
        {
            printf("%s", ascii[4]);
            flag=1;
        }
        if (head[i].u == 1 || para[i].u == 1)
        {
            printf("%s", ascii[5]);
            flag=1;
        }
        
    }
}

void p_check(const char a[])
{
    int flag = 0;
    char *tmp = strstr(a, ">");
    int element_len = tmp - a + 1;
    char *element = malloc(element_len + 1);
    element = strncpy(element, a, element_len);
    if (strstr(element, "red") != NULL)
    {
        para[count].color = RED;
    }
    if (strstr(element, "blue") != NULL)
    {
        para[count].color = BLUE;
    }
    if (strstr(element, "green") != NULL)
    {
        para[count].color = GREEN;
    }
    if (strstr(element, " em"))
    {
        para[count].em = 1;
    }
    if (strstr(element, " i"))
    {
        para[count].i = 1;
    }
    if (strstr(element, " u"))
    {
        para[count].u = 1;
    }

    for (int i = element_len; i < myindex - 4; i++)
    {
        table[cnt_row][cnt_column++] = a[i];
    }
    cnt_row++;
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
        head[count].color = RED1;
    }
    if (strstr(element, "blue") != NULL)
    {
        head[count].color = BLUE1;
    }
    if (strstr(element, "green") != NULL)
    {
        head[count].color = GREEN1;
    }
    if (strstr(element, " em"))
    {
        head[count].em = 1;
    }
    if (strstr(element, " i"))
    {
        head[count].i = 1;
    }
    if (strstr(element, " u"))
    {
        head[count].u = 1;
    }

    for (int i = element_len; i < myindex - 4; i++)
    {
        table[cnt_row][cnt_column++] = toupper(a[i]);
    }
    
    cnt_row++;
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

    for (int i = 0; i < 10; i++)
    {
        check_print();
        for (int j = 0; j < 50; j++)
        {
            printf("%c", table[i][j]);
        }
        printf("\n");
    }

    return 0;
}