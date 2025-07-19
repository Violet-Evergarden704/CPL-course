#ifndef LL_H//if not define
#define LL_H//那么就做这些东西 这个名字可以随便取，一般大写，不同的.h文件里面要不一样的名字
/*这个是什么意思？
文件多了之后，b.h可能会include a.h 这个文件
c.c文件可以引用a.h b.h，gcc编译c.c的时候可能会出问题，b.h里面还有一个a.h
b.h里面有a.h的内容，a.h的内容就有两份拷贝，重复include同一个.h文件
那么可能会发生重定义问题，定义不通过

#ifndef LL_H
#define LL_H
#endif
这三行代码就是为了避免同时include同一个.h文件

第一行跑出来，如果没有定义过，那么是False，那么就接着跑第二行，定义宏
引用b.h的时候，a.h已经定义过了，所以第一行if就不成立，下面的就不会跑，被跳过了


*/





//add code here：
//可以声明一些类型，放一些宏，以及函数的声明
//通常.h文件里面就放这些

//下面开始实现链表

//1.先定义节点，每个节点是结构体
typedef struct node {
    int val;//士兵的编号
    struct node *next;//最重要的是这个指针，指向下一个结构体
    //这个指针是这个节点类型的一部分，指向下一个东西的类型是struct node
    //有点循环定义的感觉，但是在13行的时候这里的struct node是不完整类型，
    //在后面才把这个类型完整定义完，也就是我只是要知道是这个类型而已，不需要知道具体占内存大小之类的
    //但是这里不能改成Node，在18行才出现了Node，还是要写struct node
}Node;//可以用typedef，也可以不用

//2.如何表示链表本身
//不知道链表有多长，只放一个head就行
typedef struct ll {
    Node *head;
    Node *tail;//可放可不放，
    int size;//统计当前有多少个节点，可加可不加
    //要保证head始终指向头节点，tail指向尾节点，这样才能保证链表不变，
    //只要修改了链表，检查head和tail指针要不要调整
}LinkedList;
void Init(LinkedList *list);//链表初始化的函数
void Free(LinkedList *list);//链表里面空间是malloc出来的，所以需要free来释放掉
void Append(LinkedList *list,int num);
bool IsEmpty(LinkedList *list);
bool IsSingleton(LinkedList *list);
int GetHeadVal(LinkedList *list);
void Print(LinkedList *list);
void Delete(LinkedList *list, Node *prev);//这个node节点是被删节点的前一个节点，取名叫prev好一点

//还有一些常用的链表函数
Node *Search(LinkedList *list,int num);//查找出现的第一个值是num的节点
Node *Insert(LinkedList *list,Node *prev,int num);//插入一个节点，
//prev是被插入位置的前面一个节点,num是节点的值


#endif //结束if