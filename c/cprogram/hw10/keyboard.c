#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define LEN 2000001

typedef struct node
{
    char c;
    struct node *prev, // 上一个节点
        *next,         // 下一个节点
        *last_same;    // 上一个大小写相同的节点
} Node;

typedef struct ll
{
    Node *head;
    Node *tail;
} linkedlist;

linkedlist *list;
char input[LEN];
Node *last_upper = NULL;
Node *last_lower = NULL;

void Print(int x);
void Assert(char c);
void mydelete(int check);
void Init(void);

int main()
{
    Init();
    int q = 0;
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s", input);
        int len = strlen(input);
        if (input[0] == '?')
        {
            int x = 0;
            scanf("%d", &x);
            Print(x);
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                if (input[i] == 'm' || input[i] == 'M')
                {
                    mydelete(isupper(input[i]));
                }
                else
                {
                    Assert(input[i]);
                }
            }
        }
    }
    return 0;
}

void Print(int x)
{
    if (list == NULL || list->tail == NULL)
        return; // 检查空指针
    Node *node = list->tail;
    x--;
    while (x-- && node != NULL)
    {
        node = node->prev;
    }
    while (node)
    {
        printf("%c", node->c);
        node = node->next;
    }
    printf("\n");
}

void Assert(char c)
{
    if (list == NULL)
        return; // 检查空指针
    Node *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        return;
    } // malloc fail
    node->c = c;
    node->last_same = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        node->prev = NULL;
        node->next = NULL;
        if (isupper(node->c))
        {
            last_upper = node;
        }
        else
        {
            last_lower = node;
        }
    }
    else
    {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        node->next = NULL;
        if (isupper(node->c))
        {
            Node *temp = node->prev;
            last_upper = node;
            while (temp)
            {
                if (isupper(temp->c))
                {
                    node->last_same = temp;
                    break;
                }
                temp = temp->prev;
            }
        }
        else if (islower(node->c))
        {
            last_lower = node;
            Node *temp = node->prev;
            while (temp != NULL)
            {
                if (islower(temp->c))
                {
                    node->last_same = temp;
                    break;
                }
                temp = temp->prev;
            }
        }
    }
}

void mydelete(int check)
{
    if (check)
    {
        if (last_upper == NULL)
            return; // 检查空指针
        Node *to_delete = malloc(sizeof(to_delete));
        to_delete = last_upper;
        last_upper = last_upper->last_same;
        if (to_delete->prev == NULL)
        {
            if (to_delete->next == NULL)
            {
                Init();
            }
            else
            {
                list->head = to_delete->next;
                list->head->prev = NULL;
            }
        }
        else if (to_delete->next == NULL)
        {
            to_delete->prev->next = NULL;
            list->tail = to_delete->prev;
        }
        else
        {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
        }
        free(to_delete);
    }
    else if (!check)
    {
        if (last_lower == NULL)
            return; // 检查空指针
        Node *to_delete = last_lower;
        last_lower = last_lower->last_same;
        if (to_delete->prev == NULL)
        {
            if (to_delete->next == NULL)
            {
                Init();
            }
            else
            {
                list->head = to_delete->next;
                list->head->prev = NULL;
            }
        }
        else if (to_delete->next == NULL)
        {
            to_delete->prev->next = NULL;
            list->tail = to_delete->prev;
        }
        else
        {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
        }
        free(to_delete);
    }
}
void Init(void)
{
    list = malloc(sizeof(list));
    if (list == NULL)
    {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
}