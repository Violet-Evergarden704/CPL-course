#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct node {
    char c;
    struct node *prev,       // 上一个节点
                *next,       // 下一个节点
                *last_same;  // 上一个大小写相同的节点
}Node;

typedef struct ll {
    Node *head;
    Node *tail;
}linkedlist;

linkedlist *list;
Node *last_upper;
Node *last_lower;

void Print(int x);
void Assert(char c);
void mydelete(int check);
void Init(void);

int main(){
    Init();
    int q=0;
    scanf("%d",&q);
    while(q--){
        char input=getchar();
        if(input=='?'){
            int x=0;
            scanf("%d",&x);
            getchar();
            Print(x);
        }
        else{
           do{
               if(input=='m'||input=='M'){
                   mydelete(isupper(input));
               }
               else Assert(input);
               input=getchar();
           }while(input!='\n');//输入方式部分借鉴李云浩同学
        }
    }
    return 0;
}

void Print(int x) {
    if (list == NULL || list->tail == NULL) return; // 检查空指针
    Node *node =malloc(sizeof(*node));
    node=list->head;
    while (x-- && node != NULL) {
        printf("%c", node->c);
        node = node->next;
    }
    printf("\n");
}

void Assert(char c){
    if (list == NULL) return; // 检查空指针
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return;
    }//malloc fail
    node->c = c;
    if(list->head==NULL){
        list->head=node;
        list->tail=node;
        node->prev=NULL;
        node->next=NULL;
        node->last_same=NULL;
        if(isupper(node->c)){
            last_upper=node;
        }
        else{
            last_lower=node;
        }
    }
    else{
        node->prev=list->tail;
        list->tail->next=node;
        list->tail=node;
        node->next=NULL;
        if(isupper(node->c)){
            Node *temp=node->prev;
            last_upper=node;
            while(temp!=NULL){
                if(isupper(temp->c)){
                    node->last_same=temp;
                    break;
                }
                temp=temp->prev;
            }
        }
        else{
            last_lower=node;
            Node *temp=node->prev;
            while(temp!=NULL){
                if(islower(temp->c)){
                    node->last_same=temp;
                    break;
                }
                temp=temp->prev;
            }
        }
    }
}

void mydelete(int check){
    if (check) {
        if (last_upper == NULL) return; // 检查空指针
        Node *to_delete = last_upper;
        last_upper = last_upper->last_same;
        if (to_delete->prev == NULL) {
            if (to_delete->next != NULL) {
                to_delete->next->prev = NULL;
            }
            list->head = to_delete->next;
        } else if (to_delete->next == NULL) {
            to_delete->prev->next = NULL;
            list->tail = to_delete->prev;
        } else {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
        }
        free(to_delete);
    } else {
        if (last_lower == NULL) return; // 检查空指针
        Node *to_delete = last_lower;
        last_lower = last_lower->last_same;
        if (to_delete->prev == NULL) {
            if (to_delete->next != NULL) {
                to_delete->next->prev = NULL;
            }
            list->head = to_delete->next;
        } else if (to_delete->next == NULL) {
            to_delete->prev->next = NULL;
            list->tail = to_delete->prev;
        } else {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
        }
        free(to_delete);
    }
}
void Init(void){
    last_upper=malloc(sizeof(*last_upper));
    last_lower=malloc(sizeof(*last_lower));
    list = malloc(sizeof(*list));
    if (list == NULL) {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
}