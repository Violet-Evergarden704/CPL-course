
#include <stdio.h>
//#include <stddef.h>
#define offsetof(TYPE, MEMBER) ((size_t) &(((TYPE *)0)->MEMBER))
/*这一句是什么意思？想要求成员对于首地址的偏移，应该是两个地址相减
这里意思是如果我要求b的偏移，如果结构体首地址是0，那b的偏移就是他的地址
他先把常数0转换成一个指向结构体TYPE的指针，把0号地址看成一个虚拟的结构体
然后取他的成员MEMBER，之后再取他的地址
由于首地址这时候是0，所以他的地址就是他的偏移
再用size_t转换一下，这个无所谓
*/
/*
NULL的定义是void *0 
这里也是把0转换类型，还是一个NULL，用箭头运算符的时候会对NULL取地址
对NULL取地址实际上是一个未定义行为，具体的定义依赖于编译器
gcc编译器：
我只是在算他的地址而已，不是要解引用来拿到他的成员
所以避开了对NULL解引用

*/
//上面是offset的定义，是一个宏，看上去像一个函数，使用方式和函数调用是一样的
//用这个的时候，就发生宏的替换，也就是在引用位置发生((size_t) &(((TYPE *)0)->MEMBER))代码
//TYPE就是ABC，MEMBER就是a或者b或者c，相当于是文本上的替换


//#define OffsetOf(TYPE, MEMBER) (&(((TYPE *)0)->MEMBER))



#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

/*
这个宏就是通过指向某个成员的指针来获得指向整个结构体的指针
三个参数，第一个是指向内部成员的指针，第二个是结构体的类型，第三个是这个指向内部成员的指针指向的成员

实际上就是做了一个减法
先ptr变成了一个另外一个指针__mptr
用offset可以求出成员的偏移量，做个减法，先转成char * 类型，用他去减offset
最后得到的是char *类型，要再转一次转成type *

typeof是用来拿到这个表达式的类型的,实际上就是member的类型
所以__mptr就是指向member的一个指针，也就是ptr的实际上的类型
然后做指针的运算，offset知道偏移量，指针减去偏移量大小就得到指向首地址的一个指针
减之前转成char *类型，不转的话就会跳过offset个b的空间
得到的指针还是char *类型，最后再类型转换成type *类型
*/

typedef struct abc {
    char a;//1 bit
    int b;//4 bits
    char c;//1 bit
} ABC;

int main(void) {
    printf("sizeof(ABC) = %zu\n", sizeof(ABC));
    printf("offsetof(ABC, a) = %zu\n", offsetof(ABC, a));
    printf("offsetof(ABC, b) = %zu\n", offsetof(ABC, b));
    printf("offsetof(ABC, c) = %zu\n", offsetof(ABC, c));
//offset就是偏移，算出来他跟首地址偏移了多少个字节

//TODO：通过已知的某个成员的指针，来得到整个结构体的指针

    ABC abc = {'a', 42, 'c'};
  const int *b_ptr = &abc.b;
  ABC *abc_ptr = container_of(b_ptr, ABC, b);
    printf("address: %p\t%p\n", abc_ptr, &abc);

    return 0;
}