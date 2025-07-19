//TODO:对musician的信息进行管理，创造信息管理系统
//个人信息没有成为一个有机的整体，输入输出有难度
//如果要打印各个信息，有好多项，void Print函数要有很多参数列表
//定义一个类型，叫做musician，有很多属性包括姓，名，成绩...
//用struct来创造一个新的类型
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct{
    char *first_name;//8 bits
    char *last_name;//8 bits
    char gender;//f和m表示性别,1 bit

    char *first_album;//第一个专辑名字,8 bits

    int c_score;//4 bits
    int java_score;//4 bits
    int python_score;//各个科目的分数,4 bits
//只是在声明类型而不是变量，所以不用初始化
//struct里面的类型可以不一样
}cui,luo,*zhang_ptr;

//struct的末尾要加分号，大括号后面跟上想声明的变量名字
//也可以声明指针变量，声明多个变量
//相当于把大括号整体看成类似int，char之类的
//但是如果要在main函数里面使用，就要把struct一整块复制过去，不方便
//在第九行struct后面加一个musician作为标签，现在类型名字叫做struct musician
//要用类型的时候：struct musician cui（变量名字）={(里面输入初始化的值)
//}
//如何初始化：1，按照struct声明的成员顺序依次赋值，顺序要一致 缺点：可能不知道每个成员顺序
//2，用.来初始化：
/*
struct musician luo = {
        .first_name = "Dayou",
        .last_name = "Luo",
        .gender = MALE,
        .first_album = "ZhiHuZheYe",
        .c_score = 20,
        .java_score = 10,
        .python_score = 30,
        
    };

加上.就不用按照顺序一个一个赋值了，

*/
/*
typedef struct musician{
    char *first_name;
    char *last_name;
    char gender;//f和m表示性别

    char *first_album;//第一个专辑名字

    int c_score;
    int java_score;
    int python_score;
}Musician;
Musician就成为了一个别名，比如说Musician zhang={

}

*/
//接下来写打印函数
void Print_before(Musician m){
    //如何访问结构体变量中的成员并且打印出来？
    printf("%s %s %c %s %d %d %d\n",m.first_name,m.last_name
    ,m.gender,m.first_album,m.c_score,m.java_score,m.python_score)
    //用.来访问struct里面的成员，成员访问运算符
}
//直接用Musician m的话，可能结构体很大，每次调用都有拷贝，影响性能

void Print(Musician *m){
    //如何访问结构体变量中的成员并且打印出来？
    printf("%s %s %c %s %d %d %d\n",
    (*m).first_name,
    (*m).last_name,
    (*m).gender,
    (*m).first_album,
    (*m).c_score,
    (*m).java_score,
    (*m).python_score)//因为.的优先级更高，所以要加一个括号，先解引用
    //如果不加括号，意思是先访问成员，成员是指针，对成员解引用
}
//c提供了语法糖，每次这样写很麻烦(*m).first_name，可以用箭头运算符
//m->first_name, 这样写，用箭头运算符


int CompareMusicianByScore(const void *left,const void *right){
//left right的实际类型是Musician*
const Musician*n1=left;//先类型转换
const Musician*n2=right;
int c_score1=n1->c_score;
int c_score2=n2->c_score;
return c_score1-c_score2;
}
/*
再按照first_name排序，写一个cmp函数
int CompareMusicianByScore(const void *left,const void *right){

const Musician*n1=left;
const Musician*n2=right;

return strcmp(n1->first_name,n2->first_name);
}

另外一个形式：
int CompareMusicianByScore(const void *left,const void *right){
char *const*m1_first_name_ptr=left;
char *const*m2_first_name_ptr=right;

return strcmp(*m1_first_name_ptr,*m2_first_name_ptr);
}
在这个版本中，我们没有把left转成Musician*类型，而是转成char**类型
两个都对，跟结构体类型的变量在内存中布局有关系
因为struct里面第一个成员是char*类型，left指向他，所以他是char**类型
跟Musician*是一样的，因为是同一个地址
成员在内存中按照声明顺序依次排列
*/




/*
对struct进行sizeof发现，占了48个字节，但是每个成员加起来只有37个字节
与填充有关，填充字节，padding
一种是internal padding，在成员直接填充一些字节
另外一种是有可能的填充，tail padding，在最后一个成员后面填充
绝对不会在第一个成员前面填充字节

internal padding：对每个成员做内存对齐，alignment
比如说int类型占4个字节，要求他的第一个字节一定要放在能被四整除的内存地址
同样的char *类型也要在被八整除的地址，所以需要填充一些字节来满足这些要求

tail padding：
要求结构体排放的时候起始位置和末尾位置要被成员占最大字节的那个数字整除
比如说要被8整除，因为char*是最大的，是8


填充之后，可以提高访问效率
*/



typedef struct score{
    int c_score;//4 bits
    int java_score;//4 bits
    int python_score;//各个科目的分数,4 bits
}Score;//这两个可以同名，因为不在同一个命名空间,为了不搞混，大写


//那么第一个struct里面的成员就可以修改，结构体变量可以作为另外一个结构体的成员
/*
struct{
    char *first_name;//8 bits
    char *last_name;//8 bits
    char gender;//f和m表示性别,1 bit

    char *first_album;//第一个专辑名字,8 bits

    Score score;
}cui,luo,*zhang_ptr;


初始化时候，可以不改变，按照原来的方式初始化
另外一种方式是用.
用点就要嵌套，比如.score.c_score=20,
或者：.score={
.c_score=20,
.java_score=10,
.python_score=30,
}这样非常容易理解
*/


//下面来看枚举类型enum
//对于一个类型，他的范围如果很少，可以枚举出来，就用enum
typedef enum gender{
    MALE,
    FEMALE,
    SECRET,
    GENDER_KIND,//因为实际上是整数，而且是按顺序递增的
    //所以如果MALE是0，那么GENDER_KIND就是3，就可以知道有多少种gender
}Gender;//也可以用typedef，也可以不用
//这样之后struct里面的char *gender可以改成Gender gender；
//好处在于char *可能不知道什么意义，但是用了enum就知道了
//初始化的时候，每一个枚举的常量实际上的一个整数，枚举类型实际上不安全
//可以对enum里面的枚举常量赋值，初始化的时候如果写一个M也不会报错
//但是最好按照枚举常量来写，写MALE或者其他的

//最后来看union 联合体

/*
struct的成员在内存中分布是不会有交叠的，但是union成员共用同一个内存空间
可以把union放在struct里面，写个例子

typedef struct musician {
  char *first_name; 
  char *last_name; 

    Gender gender;

  char *first_album; 

    Score score;

    union （可以不写tag，写一个也可以）{
    int performance;//演出
    double funding;//赚了多少经费
    int awards;//获奖
    char *text;//写一段文字总结
    } year_end_summary;
//写年终总结的时候，汇报，union里面的成员要支持不同类型，
//每个人汇报只能讲一件事情，四个成员占用同一个内存空间，
//以占最大字节的，开辟一个8个字节的union，和struct不一样
//如何使用？初始化的时候，只能选某一个成员去赋值
//比如我选择开演出，.year_end_summary.performance = 20,
//获奖： .year_end_summary.awards = 2,
//因为所有成员共用一块空间，所以只能用union里面的其中一个成员，不管是初始化还是使用的时候
    

    配合枚举类型一起使用
    可以设计他是什么类型的
    看看他要做什么类型的年终总结

    enum {
    PERFORMANCE,
    FUNDING,
    AWARDS,
    TEXT,
    } summary_type;
} Musician;这个是struct的类型替代名字

Print函数里面，就要依赖于枚举类型，用switch-case语句
switch(m->summary_type){
case PERFORMANCE:
printf("...");
break;
...
}

总体而言还是struct用的多，无非就是浪费一些空间
只有对内存要很高要求的才是用union
*/

int main(void) {
    printf("%zu\n", sizeof(Gender));
    printf("%zu\n", sizeof(Musician));
    struct musician cui = {
        "Jian",
        "Cui",
        MALE,
        "XinChangZhengLuShangDeYaoGun",
        10,
        20,
        30,
        .year_end_summary.funding = 2.5,
        .summary_type = FUNDING,
    };

    struct musician luo = {
        .first_name = "Dayou",
        .last_name = "Luo",
        .gender = MALE,
        .first_album = "ZhiHuZheYe",
        .score = {
            .c_score = 20,
            .java_score = 10,
            .python_score = 30,
        },
        .year_end_summary.performance = 20,
        .summary_type = PERFORMANCE,
    };

    Musician zhang = {
        .first_name = "Chu",
        .last_name = "Zhang",
        .gender = MALE,
        .first_album = "YiKeBuKenMeiSuDeXin",
        .score = {
            .c_score = 20,
            .java_score = 10,
            .python_score = 30,
        },
        .year_end_summary.awards = 2,
        .summary_type = AWARDS,
    };

    Musician musicians[] = {cui, zhang, luo};
    //用Musician声明一个结构体数组，跟int之类的是一样的
    for (int i = 0; i < 3; ++i) {
    Print(musicians + i);
    }

    //TODO:对音乐家进行排序，依照某个标准，写一个按照cji排序的版本
  qsort(musicians, sizeof musicians / sizeof *musicians,
        sizeof *musicians, CompareMusicianByScore);
    for (int i = 0; i < 3; ++i) {
    Print(musicians + i);
    }

    Musician guo = zhang;
//对结构体做赋值，就像int一样，这种赋值方式是相应的成员一一对应的赋值，包括内部嵌套的结构体
//如果里面有指针，就要小心，带来的效果是指向同一个位置，修改是可能会同时改变

    return 0;
}
