#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 10001
#define INPUT_SIZE 10001

char table[10][50];
int flag = 0;
int cnt_row = 0, cnt_column = 0;
int count = 0;
// int dcount[100][100];//记录每个元素是第几个div里面的第几个元素
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

mydiv div[10001];
int div_count = 0;

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
    int div_index,child_index;
    mydiv *father[10];
} h;
h head[10001];


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
    int div_index,child_index;
    mydiv *father[10];
} p;

p para[10001];

typedef struct image
{
    char *src;
    int width;
    int height;
    int x, y;
    int div_index,child_index;
} img;

img image[10001];



typedef struct {
    int top;
    mydiv data[STACK_SIZE];
} Stack;

Stack *s;

void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == STACK_SIZE - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, mydiv value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = value;
}

mydiv pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[(s->top)--];
}

mydiv peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    int tmp=s->top;
    return s->data[tmp--];
}


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
            while (tmp != '"')
            {
                tmp = getchar();
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
            while (tmp != '"')
            {
                tmp = getchar();
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


void get_father_p(p *para){
    int i=0;
    while(!isEmpty(s)){
        para->father[i++] = &peek(s);
    }
}
void get_father_h(h *head){
    int i=0;
    while(!isEmpty(s)){
        head->father[i++] = &peek(s);
    }
}
void get_father_img(img *image){
    int i=0;
    while(!isEmpty(s)){
        image->father[i++] = &peek(s);
    }
}

void analyze_p(p *para){
    int i=0;
    int len=0;

}

void get_element_d(void){
    char tmp;
    int child_count = 0;
    while(1){
        while((tmp = getchar()) != '>'){
            if(tmp == 'w'){
                while((tmp = getchar()) != '"');
                tmp = getchar();
                div[div_count].w = 0;
                while(tmp != '"'){
                    div[div_count].w = div[div_count].w * 10 + atoi(&tmp);
                    tmp = getchar();
                }
            }
            if(tmp == 'h'){
                while((tmp = getchar()) != '"');
                tmp = getchar();
                div[div_count].h = 0;
                while(tmp != '"'){
                    div[div_count].h = div[div_count].h * 10 + atoi(&tmp);
                    tmp = getchar();
                }
            }
            if(tmp == '/'){
                tmp=getchar();
                if(tmp == 'd'){
                    pop(&s);
                    child_count = 0;
                } 
                continue;
            }
            if(tmp == 'd'){
                push(&s,div[++div_count]);
            }
            if(tmp == 'p'){
                get_father_p(&para[count]);
                para[count].child_index = child_count++;
                para[count].div_index = div_count;
                get_element_p(&para[count]);
                get_content_p(&para[count]);
                analyze_p(&para[count]);
                continue;
            }
            if(tmp == 'h'){
                get_father_h(&head[count]);
                get_element_h(&head[count]);
                get_content_h(&head[count]);
                analyze_h(&head[count]);
                continue;
            }
            if(tmp == 'i'){
                get_father_img(&image[count]);
                get_element_img(&image[count]);
                analyze_img(&image[count]);
                continue;
            }
        }
        if (tmp == EOF)
        {
            break;
        }
    }
}
//先进栈，再解析，再更新father尺寸，用father尺寸确定子元素的xy坐标
void explain_h(h *head)
{

    for (int i = 0; i < head->width; i++)
    {
        table[cnt_row][cnt_column++] = toupper(head->content[i]);
    }
    cnt_column = 0;
    cnt_row++;
    flag = 0;
}

void explain_p(p *para)
{

    for (int i = 0; i < para->width; i++)
    {
        table[cnt_row][cnt_column++] = para->content[i];
    }
    cnt_column = 0;
    cnt_row++;
    flag = 0;
}

void explain_img(img *image)
{
    int len = strlen(image->src);
    int h = len / image->width;
    image->height = h;
    for (int i = 0; i < h; i++)
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
        int flag = 0;
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
                get_element_img(&image[count]);
                explain_img(&image[count]);
                count += image[count].height;
            }
            if(temp == 'd'){
                push(&s, div[++div_count]);
                get_element_d();
            }
        }
    }
    Print();

    return 0;
}
