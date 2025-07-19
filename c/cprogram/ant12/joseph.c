// 要用循环链表，犯人已经坐了一圈了
//先实现链表，再在main函数里面调用有关链表的函数
//在ll文件夹里面定义结构体，实现一些有关函数，在这个文件里面用ll里面实现的函数

//多文件的时候，用gcc-o，除了要写joseph.c之外，还依赖ll.c
//gcc joseph.c ll/ll.c -0 joseph       要这样写



#include "ll/ll.h"//不在一个文件夹，要写路径，引入.h头文件
#include <stdio.h>

#include <assert.h>

#define NUM 12

void SitAroundCircle(LinkedList *list, int num);//第一步，构建单向循环链表，并且初始化
void KillUntilOne(LinkedList *list);//不断杀人直到剩下最后一个的函数
int GetSurvivorValue(LinkedList *list);//返回幸存者编号

int main(void) {
    printf("I hate the Josephus game!\n");//面向printf的接口编程，不需要知道他是怎么实现的
    //printf的接收值，返回值等等，叫做接口信息或者原型信息
    //有两个角色，一个是printf的原型、声明，另外一个是printf的实现
    //类似的，可以把链表的类型声明和原型放在.h文件里面，具体实现放在.c文件里面
    
    
    LinkedList list;//声明一个链表结构体
    Init(&list);//构建一个空的链表，不要让指针乱指

    SitAroundCircle(&list, NUM);//坐成一圈，构建了大小为NUM的循环单链表

    GetSurvivorValue(&list);
    Print(&list);//把list的每个节点的val打印出来

    KillUntilOne(&list);
    int survivor = GetSurvivorValue(&list);
    printf("%d : %d\n", NUM, survivor);//一开始有多少士兵和幸存的士兵编号

    Free(&list);
    

    return 0;
}

void SitAroundCircle(LinkedList *list, int num) {
    for (int i = 1; i <= num; i++) {
    Append(list, i);//加一个节点在末尾，这种操作叫append
    }
}

void KillUntilOne(LinkedList *list) {
  Node *node = list->head;//先获得第一个节点，让他等于*node

    while (!IsSingleton(list)) {//结束的条件是只剩下一个节点
    Delete(list, node);//删除节点，每次删一个,删的是node的下一个节点
    node = node->next;//更新node，在delete函数里面更新了next指针，那么node是删掉的节点的下一个节点
    }
}//每隔一人杀一人，怎么做？用delete函数


int GetSurvivorValue(LinkedList *list) {
    //希望链表里面这时候只有一个节点了，但是从这个函数看不出来，如果list里面有多个节点，不妨碍我调用这个函数
    //我想要只有这个链表里面有一个节点的时候才能够让函数正常工作
    //用assert函数，动态检查调用这个函数的时候list里面是不是只有一个节点
    assert(IsSingleton(list));
    //assert是一个断言，当我程序运行到这里的时候，会检查其中条件是否成立，如果不成立，整个程序终止
    //可以把assert用来debug，让assert不起作用，在gcc里面传入一个-DNDEBUG参数，assert语句就被注释掉

    return GetHeadVal(list);//拿到头指针的值
}

//如果我想知道NUM从1到100，幸存者的编号是多少，那就套一个for循环从1到100