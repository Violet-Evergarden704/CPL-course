#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
int q;
typedef struct node {
    int val;
    int id;
    struct node *next;
} Node;

Node nnode[10086];

typedef struct ll {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

void Init(LinkedList *list){
    list -> size=1;
    int n=0;
    scanf("%d%d",&n,&q);
    nnode[list -> size].val=n;
    nnode[list -> size].id=0;
    list->head=&nnode[list->size];
}

bool IsEmpty(LinkedList *list) {
    return list->head == NULL;
}

void Appendfront(LinkedList *list, int num) {
    if (list == NULL) return; // 检查空指针
    Node *node = malloc(sizeof(*node)); // malloc不一定成功
    if (node == NULL) {
        return;
    }
    node->val = num;
    node->id = 0;

    if (IsEmpty(list)) {
        list->head = node;
        list->tail = node;
        node->next = NULL;
    } else {
        list->head->val--; // 分裂了，变一半
        node->next = list->head;
        list->head = node;
    }
    list->size++;
}

void Print(LinkedList *list) {
    if (list == NULL || IsEmpty(list)) return; // 检查空指针
    Node *node = list->head;
    while (node != NULL) {
        printf("%d ", node->id);
        node = node->next;
    }
    printf("\n");
}

void Question(LinkedList *list) {
    if (list == NULL) return; // 检查空指针
    printf("%d\n", list->size);
    Print(list);
}

Node *Match(int lgm, LinkedList *list) {
    if (list == NULL || IsEmpty(list)) return NULL; // 检查空指针
    Node *node = list->head;
    while (node != NULL) {
        if (node->val == lgm&&node->id==0) return node;
        node = node->next;
    }
    return NULL;
}

void Assert(int id, int lgm, LinkedList *list) {
    if (list == NULL) return; // 检查空指针
    while(true) {
        Node *matchedNode=Match(lgm,list);
        if(matchedNode!=NULL){
            matchedNode->id=id;
            break;
        }
        else Appendfront(list,list->head->val-1);
    }
}

int main(){
    LinkedList *list = malloc(sizeof(LinkedList)); // 分配内存
    if (list == NULL) {
        return 1; // 内存分配失败，退出程序
    }
    Init(list);
    while(q--){
        char inquiry[2];
        scanf("%s",inquiry);
        if(inquiry[0]=='Q'){
            Question(list);
        }
        else {
            int id=0,m=0;
            scanf("%d%d",&id,&m);
            int lgm=ceil(log2(m));
            Assert(id,lgm,list);
        }
    }
    
    free(list);
    return 0;
}