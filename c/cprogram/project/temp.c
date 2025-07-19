#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 10001
#define INPUT_SIZE 10001

char table[10][50];
char input[2];
char buffer[10001] = {0};
int myindex = 0, flag = 0;
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
    int color; // 0:unknown,1:red,2:blue,3:green
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
    int width;
    int x, y;
} h;

h head[10001];
int count = 0;

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
    int width;
    int x, y;
} p;

p para[10001];

typedef struct image
{
    char *src;
    int width;
} img;

img image[10001];
int img_count = 0;

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

void get_element_h(h *head)
{
    char tmp;
    while ((tmp = getchar()) != '>')
    {
        if (tmp == 'c')
        {
            flag = 1;
            while (tmp != '"')
            {
                tmp = getchar();
            }

            tmp = getchar();
            if (tmp == 'r')
            {
                head->color = RED1;
                element[count][0].color = 1;
            }
            if (tmp == 'b')
            {
                head->color = BLUE1;
                element[count][0].color = 2;
            }
            if (tmp == 'g')
            {
                head->color = GREEN1;
                element[count][0].color = 3;
            }
        }
        if (tmp == 'm')
        {
            flag = 1;
            head->em = 1;
            element[count][0].em = 1;
        }
        if (tmp == 'i')
        {
            flag = 1;
            head->i = 1;
            element[count][0].i = 1;
        }
        if (tmp == 'u')
        {
            flag = 1;
            head->u = 1;
            element[count][0].u = 1;
        }
    }
}

void get_element_p(p *para)
{
    char tmp;
    while ((tmp = getchar()) != '>')
    {
        if (tmp == 'c')
        {
            flag = 1;
            while (tmp != '"')
            {
                tmp = getchar();
            }

            tmp = getchar();
            if (tmp == 'r')
            {
                para->color = RED;
                element[count][0].color = 1;
            }
            if (tmp == 'b')
            {
                para->color = BLUE;
                element[count][0].color = 2;
            }
            if (tmp == 'g')
            {
                para->color = GREEN;
                element[count][0].color = 3;
            }
        }
        if (tmp == 'm')
        {
            flag = 1;
            para->em = 1;
            element[count][0].em = 1;
        }
        if (tmp == 'i')
        {
            flag = 1;
            para->i = 1;
            element[count][0].i = 1;
        }
        if (tmp == 'u')
        {
            flag = 1;
            para->u = 1;
            element[count][0].u = 1;
        }
    }
}

void get_element_img(img *image)
{
    char tmp;
    char *src = malloc(1000);
    int width = 0;
    while (1)
    {
        tmp = getchar();
        if (tmp == '"')
        {
            break;
        }
    }
    int i = 0;
    while (1)
    {
        src[i++] = getchar();
        if (src[i - 1] == '"')
        {
            src[i - 1] = '\0';
            break;
        }
    }
    image->src = src;
    while (1)
    {
        tmp = getchar();
        if (tmp == '"')
        {
            break;
        }
    }
    tmp = getchar();
    while (tmp != '"')
    {
        width = width * 10 + atoi(&tmp);
        tmp = getchar();
    }
    image->width = width;
    scanf("%*s");
}

void explain_h(h *head)
{

    for (int i = 0; i < head->width; i++)
    {
        table[cnt_row][cnt_column++] = toupper(head->content[i]);
    }
    cnt_column = 0;
    cnt_row++;
}

void explain_p(p *para)
{

    for (int i = 0; i < para->width; i++)
    {
        table[cnt_row][cnt_column++] = para->content[i];
    }
    cnt_column = 0;
    cnt_row++;
}

void explain_img(img *image)
{
    int len = strlen(image->src);
    int height = len / image->width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            table[cnt_row][cnt_column++] = image->src[i * image->width + j];
        }
        cnt_row++;
        cnt_column = 0;
    }
}

void get_content_h(h *head)
{
    int i = 0;
    char ch;
    while ((ch = getchar()) != '<')
    {
        head->content[i++] = ch;
    }
    head->content[i] = '\0'; // 确保字符串以空字符结尾
    head->width = strlen(head->content);
    if (flag)
        element[count][head->width - 1].o = 1;
}
void get_content_p(p *para)
{
    int i = 0;
    char ch;
    while ((ch = getchar()) != '<')
    {
        para->content[i++] = ch;
    }
    para->content[i] = '\0'; // 确保字符串以空字符结尾
    para->width = strlen(para->content);
    if (flag)
        element[count][para->width - 1].o = 1;
}

void Print(void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (element[i][j].color == 1)
            {
                printf("%s", ascii[0]);
            }
            if (element[i][j].color == 2)
            {
                printf("%s", ascii[1]);
            }
            if (element[i][j].color == 3)
            {
                printf("%s", ascii[2]);
            }
            if (element[i][j].em == 1)
            {
                printf("%s", ascii[3]);
            }
            if (element[i][j].i == 1)
            {
                printf("%s", ascii[4]);
            }
            if (element[i][j].u == 1)
            {
                printf("%s", ascii[5]);
            }

            printf("%c", table[i][j]);

            if (element[i][j].o == 1)
            {
                printf("%s", ascii[6]);
            }
        }
        printf("\n");
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
        if (temp == '<')
        {
            temp = getchar();
            if (temp == 'h')
            {
                head[count].content = malloc(100);
                if (head[count].content == NULL)
                {
                    fprintf(stderr, "Memory allocation failed for headline content\n");
                    exit(1);
                }
                get_element_h(&head[count]);
                get_content_h(&head[count]);
                explain_h(&head[count]);
                count++;
            }
            if (temp == 'p')
            {
                para[count].content = malloc(100);
                if (para[count].content == NULL)
                {
                    fprintf(stderr, "Memory allocation failed for paragraph content\n");
                    exit(1);
                }
                get_element_p(&para[count]);
                get_content_p(&para[count]);
                explain_p(&para[count]);
                count++;
            }
            if (temp == 'i')
            {
                get_element_img(&image[img_count]);
                explain_img(&image[img_count]);
                img_count++;
            }
        }
        Print();

        return 0;
    }
}