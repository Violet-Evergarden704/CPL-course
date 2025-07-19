#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 定义元素类型枚举
typedef enum
{
    ELEMENT_UNKNOWN,
    ELEMENT_H,
    ELEMENT_P,
    ELEMENT_IMG,
    ELEMENT_DIV
} ElementType;

// 定义属性类型枚举
typedef enum
{
    ATTRIBUTE_UNKNOWN,
    ATTRIBUTE_COLOR,
    ATTRIBUTE_EM,
    ATTRIBUTE_I,
    ATTRIBUTE_U,
    ATTRIBUTE_SRC,
    ATTRIBUTE_WIDTH,
    ATTRIBUTE_W,
    ATTRIBUTE_H,
    ATTRIBUTE_DIRECTION,
    ATTRIBUTE_ALIGN_ITEMS,
    ATTRIBUTE_JUSTIFY_CONTENT
} AttributeType;

// 元素结构体
typedef struct Element
{
    ElementType type;
    struct Element *parent;
    struct Element **children;
    int childCount;
    char *content;
    char color[10];
    int em;
    int i;
    int u;
    char *src;
    int width;
    int w;
    int h;
    char direction[10];
    char alignItems[20];
    char justifyContent[20];
} Element;

// 创建新元素
Element *createElement(ElementType type)
{
    Element *element = (Element *)malloc(sizeof(Element));
    element->type = type;
    element->parent = NULL;
    element->children = NULL;
    element->childCount = 0;
    element->content = NULL;
    element->src = NULL;
    element->width = 0;
    element->w = 0;
    element->h = 0;
    element->em = 0;
    element->i = 0;
    element->u = 0;
    strcpy(element->color, "");
    strcpy(element->direction, "row");
    strcpy(element->alignItems, "start");
    strcpy(element->justifyContent, "start");
    return element;
}

// 释放元素内存
void freeElement(Element *element)
{
    if (element == NULL)
        return;
    free(element->content);
    free(element->src);
    for (int i = 0; i < element->childCount; i++)
    {
        freeElement(element->children[i]);
    }
    free(element->children);
    free(element);
}

// 添加子元素
void addChild(Element *parent, Element *child)
{
    child->parent = parent;
    parent->children = (Element **)realloc(parent->children, sizeof(Element *) * (parent->childCount + 1));
    parent->children[parent->childCount++] = child;
}

// 解析属性
AttributeType parseAttribute(const char *attrName)
{
    if (strcmp(attrName, "color") == 0)
        return ATTRIBUTE_COLOR;
    else if (strcmp(attrName, "em") == 0)
        return ATTRIBUTE_EM;
    else if (strcmp(attrName, "i") == 0)
        return ATTRIBUTE_I;
    else if (strcmp(attrName, "u") == 0)
        return ATTRIBUTE_U;
    else if (strcmp(attrName, "src") == 0)
        return ATTRIBUTE_SRC;
    else if (strcmp(attrName, "width") == 0)
        return ATTRIBUTE_WIDTH;
    else if (strcmp(attrName, "w") == 0)
        return ATTRIBUTE_W;
    else if (strcmp(attrName, "h") == 0)
        return ATTRIBUTE_H;
    else if (strcmp(attrName, "direction") == 0)
        return ATTRIBUTE_DIRECTION;
    else if (strcmp(attrName, "align-items") == 0)
        return ATTRIBUTE_ALIGN_ITEMS;
    else if (strcmp(attrName, "justify-content") == 0)
        return ATTRIBUTE_JUSTIFY_CONTENT;
    else
        return ATTRIBUTE_UNKNOWN;
}

// 解析开始标签
Element *parseOpeningTag(char *tag, Element *parent)
{
    ElementType type = ELEMENT_UNKNOWN;
    if (strstr(tag, "<h") != NULL)
        type = ELEMENT_H;
    else if (strstr(tag, "<p") != NULL)
        type = ELEMENT_P;
    else if (strstr(tag, "<img") != NULL)
        type = ELEMENT_IMG;
    else if (strstr(tag, "<div") != NULL)
        type = ELEMENT_DIV;

    Element *element = createElement(type);
    if (parent != NULL)
        addChild(parent, element);

    char *token = strtok(tag + 1, " >");
    while (token != NULL)
    {
        if (strcmp(token, "/") == 0)
            break;
        char *attrValue = strchr(token, '=');
        if (attrValue != NULL)
        {
            *attrValue = '\0';
            attrValue++;
            AttributeType attrType = parseAttribute(token);
            switch (attrType)
            {
            case ATTRIBUTE_COLOR:
                strcpy(element->color, attrValue + 1);
                element->color[strlen(attrValue) - 1] = '\0';
                break;
            case ATTRIBUTE_EM:
                element->em = 1;
                break;
            case ATTRIBUTE_I:
                element->i = 1;
                break;
            case ATTRIBUTE_U:
                element->u = 1;
                break;
            case ATTRIBUTE_SRC:
                element->src = strdup(attrValue + 1);
                element->src[strlen(attrValue) - 1] = '\0';
                break;
            case ATTRIBUTE_WIDTH:
                element->width = atoi(attrValue + 1);
                break;
            case ATTRIBUTE_W:
                element->w = atoi(attrValue + 1);
                break;
            case ATTRIBUTE_H:
                element->h = atoi(attrValue + 1);
                break;
            case ATTRIBUTE_DIRECTION:
                strcpy(element->direction, attrValue + 1);
                element->direction[strlen(attrValue) - 1] = '\0';
                break;
            case ATTRIBUTE_ALIGN_ITEMS:
                strcpy(element->alignItems, attrValue + 1);
                element->alignItems[strlen(attrValue) - 1] = '\0';
                break;
            case ATTRIBUTE_JUSTIFY_CONTENT:
                strcpy(element->justifyContent, attrValue + 1);
                element->justifyContent[strlen(attrValue) - 1] = '\0';
                break;
            default:
                break;
            }
        }
        token = strtok(NULL, " >");
    }
    return element;
}

// 解析结束标签
void parseClosingTag(char *tag, Element **stack, int *top)
{
    ElementType type = ELEMENT_UNKNOWN;
    if (strstr(tag, "</h") != NULL)
        type = ELEMENT_H;
    else if (strstr(tag, "</p") != NULL)
        type = ELEMENT_P;
    else if (strstr(tag, "</img") != NULL)
        type = ELEMENT_IMG;
    else if (strstr(tag, "</div") != NULL)
        type = ELEMENT_DIV;

    if (top > 0 && stack[*top - 1]->type == type)
    {
        *top -= 1;
    }
}

// 解析内容
void parseContent(char *content, Element *currentElement)
{
    if (currentElement != NULL)
    {
        currentElement->content = strdup(content);
    }
}

// 解析HTML
Element *parseHTML(char *html)
{
    Element *root = createElement(ELEMENT_UNKNOWN);
    Element *stack[100];
    int top = 0;
    Element *currentElement = root;

    char *token = strtok(html, "<>");
    while (token != NULL)
    {
        if (token[0] == '/')
        {
            parseClosingTag(token, stack, &top);
            if (top > 0)
            {
                currentElement = stack[top - 1];
            }
        }
        else if (strstr(token, " ") != NULL || strstr(token, "=") != NULL)
        {
            Element *newElement = parseOpeningTag(token, currentElement);
            stack[top++] = newElement;
            currentElement = newElement;
        }
        else
        {
            parseContent(token, currentElement);
        }
        token = strtok(NULL, "<>");
    }
    return root;
}

// 计算元素尺寸
void calculateDimensions(Element *element)
{
    if (element == NULL)
        return;
    if (element->type == ELEMENT_P || element->type == ELEMENT_H)
    {
        element->w = element->content ? strlen(element->content) : 0;
        element->h = 1;
    }
    else if (element->type == ELEMENT_IMG)
    {
        element->h = element->src ? strlen(element->src) / element->width : 0;
    }
    else if (element->type == ELEMENT_DIV)
    {
        if (element->w == 0 || element->h == 0)
        {
            int maxWidth = 0;
            int totalHeight = 0;
            for (int i = 0; i < element->childCount; i++)
            {
                calculateDimensions(element->children[i]);
                if (strcmp(element->direction, "row") == 0)
                {
                    maxWidth = maxWidth > element->children[i]->w ? maxWidth : element->children[i]->w;
                    totalHeight += element->children[i]->h;
                }
                else
                {
                    maxWidth += element->children[i]->w;
                    totalHeight = totalHeight > element->children[i]->h ? totalHeight : element->children[i]->h;
                }
            }
            if (element->w == 0)
                element->w = maxWidth;
            if (element->h == 0)
                element->h = totalHeight;
        }
    }
}

// 渲染元素到二维数组
void renderElement(Element *element, char output[10][50], int x, int y)
{
    if (element == NULL)
        return;
    if (element->type == ELEMENT_H)
    {
        char *text = element->content;
        int len = strlen(text);
        for (int i = 0; i < len; i++)
        {
            if (x + i < 50 && y < 10)
            {
                output[y][x + i] = toupper(text[i]);
            }
        }
    }
    else if (element->type == ELEMENT_P)
    {
        char *text = element->content;
        int len = strlen(text);
        for (int i = 0; i < len; i++)
        {
            if (x + i < 50 && y < 10)
            {
                output[y][x + i] = text[i];
            }
        }
    }
    else if (element->type == ELEMENT_IMG)
    {
        char *image = element->src;
        int imageLen = strlen(image);
        int height = imageLen / element->width;
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < element->width; col++)
            {
                if (x + col < 50 && y + row < 10)
                {
                    output[y + row][x + col] = image[row * element->width + col];
                }
            }
        }
    }
    else if (element->type == ELEMENT_DIV)
    {
        int xOffset = 0;
        int yOffset = 0;
        if (strcmp(element->direction, "row") == 0)
        {
            for (int i = 0; i < element->childCount; i++)
            {
                renderElement(element->children[i], output, x + xOffset, y + yOffset);
                xOffset += element->children[i]->w;
                yOffset += element->children[i]->h;
            }
        }
        else
        {
            for (int i = 0; i < element->childCount; i++)
            {
                renderElement(element->children[i], output, x + xOffset, y + yOffset);
                xOffset += element->children[i]->w;
            }
        }
    }
}

// 渲染网页
void renderWebpage(Element *root, char output[10][50])
{
    calculateDimensions(root);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            output[i][j] = ' ';
        }
    }
    renderElement(root, output, 0, 0);
}

// 输出带样式文本
void outputStyledText(char *text, char color[], int em, int i, int u)
{
    if (strcmp(color, "red") == 0)
        printf("\033[31m");
    else if (strcmp(color, "blue") == 0)
        printf("\033[34m");
    else if (strcmp(color, "green") == 0)
        printf("\033[32m");
    if (em)
        printf("\033[1m");
    if (i)
        printf("\033[3m");
    if (u)
        printf("\033[4m");
    printf("%s", text);
    printf("\033[0m");
}

// 输出渲染结果
void outputRenderedPage(char output[10][50])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            putchar(output[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char html[10000];
    fgets(html, sizeof(html), stdin);
    Element *root = parseHTML(html);
    char output[10][50];
    renderWebpage(root, output);
    outputRenderedPage(output);
    freeElement(root);
    return 0;
}