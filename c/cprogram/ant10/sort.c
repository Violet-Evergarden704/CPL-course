//运用qsort来排序整数数组和字符串数组
//void qsort(void *ptr数组的首地址, size_t count数组的元素个数,size_t size数组每个元素占字节大小,
//int (*comp)(const void*, const void *) 是一个比较函数，排序的标准，类似strcmp的规定)
//comp是一个指针，指针指向一个函数，函数接受两个const void*,返回int，所以一定要constvoid

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef int (*Comp)(const void *, const void *);//自己定义一个类型，可以省很多

int CompareInts(const void *left, const void *right);
int CompareStrs(const void *left, const void *right);
int CompareStrsWrong(const void *left, const void *right);

int StrCmpStd(const char *s1, const char *s2);

void PrintInts(const int integers[], size_t len);
void PrintStrs(const char *str[], size_t len);

int main() {
    int integers[] = {-2, 99, 0, -743, 2, INT_MIN, 4};
    int size_of_integers = sizeof integers / sizeof *integers;

    PrintInts(integers, size_of_integers);
  // TODO: Sort integers using qsort
    Comp comp = CompareInts;
//  int (*comp)(const void *, const void *) = CompareInts;comp就成为一个函数指针
  qsort(integers, size_of_integers, sizeof *integers,
        comp);
    PrintInts(integers, size_of_integers);

  const char *names[] = {
    "Luo Dayou",
    "Cui Jian",
    "Dou Wei",
    "Zhang Chu",
    "Wan Qing",
    "Li Zhi",
    "Yao",
    "ZuoXiao",
    "ErShou Rose",
    "Hu Mage",
    };
  size_t size_of_names = sizeof names / sizeof *names;

    PrintStrs(names, size_of_names);
  // TODO: Sort strings using qsort
    comp = CompareStrs;
//  qsort(names, size_of_names, sizeof *names,
//        comp);
  qsort(names, size_of_names, sizeof *names,
        CompareStrsWrong);
    PrintStrs(names, size_of_names);
}

// left, right: int * 先写一个排序int的cmp函数
int CompareInts(const void *left, const void *right) {
  int left_val = *(const int *)left;//转换成int*先，再解引用，比较他俩谁大
  int right_val = *(const int *)right;

    return (left_val > right_val) - (left_val < right_val);

//  if (left_val < right_val) {
//    return -1;
//  }
//  if (left_val > right_val) {
//    return 1;
//  }
//  return 0;
//这个太长了，只要我返回小于零大于零的数字就行，不需要一定是1 -1或者0
//如果直接写return left_val-right_val，可能会溢出int范围
}

// left, right: char ** left和right实际上是什么？是指向字符串的指针
//所以left和right实际上是char **
int CompareStrs(const void *left, const void *right) {
  char * const *left_str = left;
  char * const *right_str = right;//先做类型转换，要加个const的话就加在中间
  //原先有const，应该加回来，const保护的实际上是left指向的元素，所以加const在中间
  return strcmp(*left_str, *right_str);//用strcmp来比较，参数是char*所以要解引用
}

//写一个错误版本的compare_string函数
int CompareStrsWrong(const void *left, const void *right) {
  const char *pp1 = left;
  const char *pp2 = right;//你可能会想，转换成char**之后return里面还要解引用
  //那么为什么不直接转换成char*呢
  //这样的cmp函数试一下发现qsort根本没排序，跟原本的是一样的
  //到底在compare什么？实际上是字符串的地址，字符串都放在只读空间里，按照声明顺序排好了
  //所以要搞对类型信息，两个*意思不一样，char *pp1实际上跟left一样是字符串的地址
    printf("pp1: %p\n pp2: %p\n", pp1, pp2);
//  return strcmp(pp1, pp2);
    return StrCmpStd(pp1, pp2);
}

int StrCmpStd(const char *s1, const char *s2) {
  for (; *s1 == *s2; s1++, s2++) {
    if (*s1 == '\0') {
    return 0;
    }
    }

  const unsigned char s1_char = *((const unsigned char *) s1);
  const unsigned char s2_char = *((const unsigned char *) s2);

  return * ((const unsigned char *) s1) -
      * ((const unsigned  char *) s2);
}

void PrintInts(const int integers[], size_t len) {
    printf("\n");
    for (int i = 0; i < len; i++) {
    printf("%d ", integers[i]);
    }
    printf("\n");
}

void PrintStrs(const char *str[], size_t len) {
    printf("\n");
    for (int i = 0; i < len; i++) {
    printf("%s\n", str[i]);
    }
    printf("\n");
}