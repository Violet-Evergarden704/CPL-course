//.c文件里面放函数的实现，原型在.h里面
//#include <ll.h>//加了这个头文件之后就可以看函数类型有没有冲突
//但是不能用<>去写，要用""
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "ll.h"
//预处理阶段，include就是拷贝一份文件到这个位置，
//那么到哪里去找ll.h这个文件，如果是<>的话他回到系统路径之中去找
//但是ll.h不在系统路径，只是在一个普通文件夹里面，所以他找不到，要用""
//双引号意思就是先在本地工程里面找一下，找不到再去系统路径下找

void Init(LinkedList *list){
    //也就是要创造一个没有节点的结构体，也就是head和tail是空指针
    list -> head = NULL;
    list -> tail = NULL;
}


bool IsEmpty(LinkedList *list){
    //只要看头或者尾是不是空指针
    return list -> head == NULL;
}

bool IsSingleton(LinkedList *list){
    return (!IsEmpty(list)) && list -> head == list -> tail);
    //注意list可能是空的,如果是空的也满足相等的条件但是不是只有一个节点的链表

}


void Free(LinkedList *list){
    //用一个循环来free，能不能一个一个free？如果把head free了，下面的就找不到了
    //可以借助delete函数去free
    while(!IsEmpty(list)){
        Delete(list,list -> head);//free掉head的下一个，直到删除自己
    }
}


void Append(LinkedList *list,int num){
    Node *node = malloc(sizeof *node);//malloc不一定成功
    if(node == NULL){
        return;
    }
    node -> val = num;// node里面的数据是num

    if(IsEmpty(list)){
        list -> head = node;
        list -> tail = node;
        list -> tail -> next = list -> head;
    }
    else{
        list -> tail -> next =node;//list的成员tail的next指针指向node这个新的节点
        list -> tail = node;//tail指针也要指向node
        node -> next = list->head;// node的next指针要指向list里面的head节点
//可以换成list -> tail -> next = list->head;保证tail节点的next指针指向head节点，
//也就是保证是一个循环单链表
    }
    

    
}


//写链表相关函数的时候，如果修改了链表的结构，要考虑特殊的边界情况：
//1.链表是不是空的，head和tail都是null的时候是空的
//2.链表是不是只有一个节点
//3.修改的时候有没有碰到头节点和尾节点

//所以上面的代码有问题，要单独处理链表为空的情况,用一个isempty函数
//if-else里面有两行代码是一样的，可以放出if-else，但是不方便理解，可读性不强

//对链表中的指针操作，经常会看到很多指针操作连在一起，并且顺序不能换，
//比如else语句里面一二行互换意思就不一样了



int GetHeadVal(LinkedList *list){
    if(IsEmpty(list)){
        return -1;
    }
    else return list -> head -> val ;
}






void Print(LinkedList *list){
    if(IsEmpty(list)){
    return ;
    }
    Node *node = list -> head;//先拿到第一个节点
    /*
    while(node ){//遍历每一个节点,循环条件不可以写node！=tail，因为最后一个节点就打印不出来
        //循环条件很难写，于是用do-while
        printf("%d ",node -> val);
        node = node -> next;
    }
    */
    do{
        printf("%d ",node -> val);
        node = node -> next;
    }while(node != list -> head);//因为是循环链表，所以他最后会回到head节点
    //要考虑特殊情况，链表如果是空的，node和head一样是空指针，不能对空指针解引用
    printf("\n");
}

void Delete(LinkedList *list, Node *prev){
    //先通过prev这个节点的指针拿到current节点和Next节点的指针 Next节点与next指针作大小区分
    
    //边界条件非常重要
    //1.链表是不是空的 如果是，那么prev是一个空指针
    if(IsEmpty(list)){
        return;
    }
    //2.链表是不是只有一个节点 那么prev就是那一个节点，要把自己删掉
    if(IsSingleton(list)){
        Init(list);//直接初始化就好了
        //这个节点就没人访问了，出现内存泄漏，需要释放
        free(list->head);
        return;
    }
    //除开以上两种情况，都可以正常删除这个节点了
    
    Node *current = prev -> next;
    Node *Next = current -> next;
    prev -> next = Next;//调整指针，让prev的指针指向Next节点,跳过current

    //3.修改的时候有没有碰到头节点和尾节点 如果删掉的current节点是头或者尾？
    if(current == list -> head){
        //画图理解，cur删掉之后，prev的next指向Next，head改变
        list -> head = Next;
    }
    if(current == list -> tail){
        list -> tail = prev;
    }
    //还差一点点,有内存泄漏的问题
    free(current);//释放被删除的current节点
}
//Append函数负责malloc，free的时候在另外的函数(也就是delete)