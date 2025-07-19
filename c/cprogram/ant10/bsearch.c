//bsearch函数：
//void *bsearch(const void *key要查找的东西，必须的指针，因为不知道搜的东西的类型
//所以只能用void型，加上指针，其他参数一样的包括cmp函数)
//bsearch的返回值是找到的元素的地址，如果没找到那就是NULL
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//用一个类型别名，代替，来声明bsearch里面的形式参数
typedef int (*cmp_func_t)(const void *a, const void *b);


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
    int CompareStrs(const void *left, const void *right) {
    char * left_str = left;
    char * right_str = right;//先做类型转换，要加个const的话就加在中间
  //原先有const，应该加回来，const保护的实际上是left指向的元素，所以加const在中间
    return strcmp(left_str, right_str);//用strcmp来比较，参数是char*所以要解引用
}
int main(void) {
    const char *key_name="Zhang Chu";
    char **ptr =bsearch(&key_name,names,sizeof names/sizeof *names,
    sizeof *names,CompareStrs);
    if(ptr==NULL)printf("not found");
    else{
        printf("found at %lld\n",ptr-(char**)names);
    }
    return 0;
}

