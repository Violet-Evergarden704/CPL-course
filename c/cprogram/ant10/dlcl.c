// Created by hengxin on 2024/12/04.

int main() {
  char **argv;

  int *names[10];
//10个元素的数组，每个元素是指针
    int (*musician_score_table)[10];
//是一个指针，指向一个有10个int的数组
  char *StrCpyStd(char *dest, const char *src);
//是一个函数，接受两个参数，返回一个char的指针
  int (*comp)(const void *left, const void *right);
//这是一个指针，指向一个函数，函数接受两个参数，返回int
    int atexit(void (*func)(void));
//这是一个函数，接受一个函数指针，返回int
//接受的函数没有参数也没有返回值
    typedef void (*handler)(int);
    handler signal(int sig, handler h);
//signal是一个函数，接受一个int参数和一个函数指针
//这个函数指针指向接受一个int返回void
//signal返回一个函数，这个函数也是接受一个int返回void
//  void (*signal(int sig, void (*handler)(int)))(int);

    char (*(*func(int num, char *str))[3])(void);
//func接受两个参数，返回一个指针，指向一个大小是3的数组
//数组每个元素是指针，指针指向char

    char (*(*arr[3])(void))[5];

}