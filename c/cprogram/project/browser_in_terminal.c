#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACK_SIZE 10001
#define INPUT_SIZE 10001
char table[10][50];
char input[2];
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
char buffer[10001] = {0};
int h_count = 0;
int myindex = 0;
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

void h_input(void)
{
    input[0] = getchar();
    while ((input[0] = getchar()) != '>')
    {
        if (input[0] == 'e')
        {
            head[h_count].em = 1;
        }
        if (input[0] == 'i')
        {
            head[h_count].i = 1;
        }
        if (input[0] == 'u')
        {
            head[h_count].u = 1;
        }
        if (input[0] == 'c')
        {
            char color[10];
            scanf("olor=%s%[^<]", color);
            if (strcmp(color, "red") == 0)
            {
                head[h_count].color = RED1;
            }
            if (strcmp(color, "green") == 0)
            {
                head[h_count].color = GREEN1;
            }
            if (strcmp(color, "blue") == 0)
            {
                head[h_count].color = BLUE1;
            }
        }
        continue;
    }
    head[h_count].content = (char *)malloc(100);
    if (head[h_count].content == NULL)
    {
        printf("malloc failed\n");
        return;
    }
    scanf("%s</h>", head[h_count].content);
    scanf("%*s");
    h_count++;
}

void p_input()
{
    input[0] = getchar();
    printf("%c", input[0]);
    while ((input[0] = getchar()) != '>')
    {
        if (input[0] == 'e')
        {
            para[p_count].em = 1;
        }
        if (input[0] == 'i')
        {
            para[p_count].i = 1;
        }
        if (input[0] == 'u')
        {
            para[p_count].u = 1;
        }
        if (input[0] == 'c')
        {
            char color[10];
            scanf("olor=%s%[^<]", color);
            if (strcmp(color, "red") == 0)
            {
                para[p_count].color = RED;
            }
            if (strcmp(color, "green") == 0)
            {
                para[p_count].color = GREEN;
            }
            if (strcmp(color, "blue") == 0)
            {
                para[p_count].color = BLUE;
            }
        }
        continue;
    }
    para[p_count].content = (char *)malloc(100);
    if (para[p_count].content == NULL)
    {
        printf("malloc failed\n");
        return;
    }
    scanf("%[^<]", para[p_count].content);
    scanf("%*s");
    p_count++;
}

void img_input()
{
    scanf("%*s");
    // getchar();
    char *src = (char *)malloc(100);
    char *str = (char *)malloc(100);
    int width;
    scanf("%s", str);
    // 使用 sscanf 从 str 中提取 src 的值
    sscanf(str, "src=\"%[^\"]\"", src);
    scanf("width=%d", &width);
    image[img_count].src = src;
    image[img_count].width = width;
    scanf("%*s");
    img_count++;
}

void p_check(char a[])
{
    int flag = 0;
    char *tmp = strstr(a, ">");
    int element_len = tmp - a + 1;
    for (int i = 0; i < element_len; i++)
    {
        if (strstr(a, "red") != NULL)
        {
            printf("%s", ascii[0]);
            flag = 1;
        }
        if (strstr(a, "blue") != NULL)
        {
            printf("%s", ascii[1]);
            flag = 1;
        }
        if (strstr(a, "green") != NULL)
        {
            printf("%s", ascii[2]);
            flag = 1;
        }
        if (strstr(a, "em"))
        {
            printf("%s", ascii[3]);
            flag = 1;
        }
        if (strstr(a, "i"))
        {
            printf("%s", ascii[4]);
            flag = 1;
        }
        if (strstr(a, "u"))
        {
            printf("%s", ascii[5]);
            flag = 1;
        }
    }
    for (int i = element_len; i < myindex - 4; i++)
    {
        printf("%c", a[i]);
    }

    if (flag)
    {
        printf("%s", ascii[6]);
    }
}
void h_check(char a[])
{
    int flag = 0;
    char *tmp = strstr(a, ">");
    int element_len = tmp - a + 1;
    for (int i = 0; i < element_len; i++)
    {
        if (strstr(a, "red") != NULL)
        {
            printf("%s", ascii[0]);
            flag = 1;
        }
        if (strstr(a, "blue") != NULL)
        {
            printf("%s", ascii[1]);
            flag = 1;
        }
        if (strstr(a, "green") != NULL)
        {
            printf("%s", ascii[2]);
            flag = 1;
        }
        if (strstr(a, "em"))
        {
            printf("%s", ascii[3]);
            flag = 1;
        }
        if (strstr(a, "i"))
        {
            printf("%s", ascii[4]);
            flag = 1;
        }
        if (strstr(a, "u"))
        {
            printf("%s", ascii[5]);
            flag = 1;
        }
    }
    for (int i = element_len; i < myindex - 4; i++)
    {
        printf("%c", toupper(a[i]));
    }

    if (flag)
    {
        printf("%s", ascii[6]);
    }
}

void img_check(char a[]){
    
}

void h_print(h head)
{
    int flag = 0;
    if (head.color == RED1)
    {
        printf("%s", ascii[0]);
        flag = 1;
    }
    if (head.color == BLUE1)
    {
        printf("%s", ascii[1]);
        flag = 1;
    }
    if (head.color == GREEN1)
    {
        printf("%s", ascii[2]);
        flag = 1;
    }
    if (head.em == 1)
    {
        printf("%s", ascii[3]);
        flag = 1;
    }
    if (head.i == 1)
    {
        printf("%s", ascii[4]);
        flag = 1;
    }
    if (head.u == 1)
    {
        printf("%s", ascii[5]);
        flag = 1;
    }
    char *tmp = head.content;
    while (tmp != NULL)
    {
        printf("%c", toupper(*tmp));
        tmp++;
    }
    if (flag)
        printf("%s", ascii[6]);
}

void p_print(p para)
{
    int flag = 0;
    if (para.color == RED)
    {
        printf("%s", ascii[0]);
        flag = 1;
    }
    if (para.color == BLUE)
    {
        printf("%s", ascii[1]);
        flag = 1;
    }
    if (para.color == GREEN)
    {
        printf("%s", ascii[2]);
        flag = 1;
    }
    if (para.em == 1)
    {
        printf("%s", ascii[3]);
        flag = 1;
    }
    if (para.i == 1)
    {
        printf("%s", ascii[4]);
        flag = 1;
    }
    if (para.u == 1)
    {
        printf("%s", ascii[5]);
        flag = 1;
    }
    printf("%s", para.content);
    if (flag)
        printf("%s", ascii[6]);
}

void img_print(img image)
{
    int height = 0;
    height = strlen(image.src) / image.width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            printf("%c", image.src[i * image.width + j]);
        }
        printf("\n");
    }
}

int main()
{
    int cnt_row = 0, cnt_column = 0;
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

        if((strstr(buffer, "<img") != NULL) && (strstr(buffer, "</img>") != NULL))
        {
            img_check(buffer);
            Init();
            continue;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            printf("%c", table[i][j]);
        }
        printf("\n");
    }

    return 0;
}
