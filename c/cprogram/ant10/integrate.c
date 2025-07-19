#include <stdio.h>
#include <math.h>

#define NUM_OF_PARTITIONS 1000000 //分成多少个小区间，把小方块矩形加起来（微分法）

double Integrate(double low, double high, double (*func)(double));
//func是被积函数，接收double返回double
//函数调用运算符高于*优先级，所以意思是func是一个函数，接收double参数，
//返回一个指向double的指针
//改变优先级，*func括号括起来，表示func是一个指针，指向一个double，也接受double
double Square(double x);

double *Function(double);

int main() {
    double low = 0.0;//积分下限
    double high = 1.0;//积分上限
    double integration = 0.0;

    integration = Integrate(low, high, sin);
    //直接把函数名放进来，自动转成函数指针类型
    printf("Sin(0.0, 1.0) = %f\n", integration);

    integration = Integrate(low, high, cos);
    printf("Cos(0.0, 1.0) = %f\n", integration);

    integration = Integrate(low, high, Square);
    printf("Square(0.0, 1.0) = %f\n", integration);


    double (*funcs[])(double) = {sin, cos, Square};
    //把函数放入一个数组里面去，数组类型就要有[]，每一个元素是一个函数指针
    //接受一个double返回一个double
    //数组优先级高，*funcs[]说明这是一个数组，每个元素是个指针，指向
    //接受double返回double的函数

    //如果不写括号变成 double *funcs[](double)，首先是有语法错误，
    //意思是funcs是一个数组，每个元素是一个函数，接受一个double返回一个double指针
    //搞一个Function是接收double返回double指针的函数，放进double *funcs[](double)
    //还是有语法错误，因为不能把函数类型放入数组，要放函数指针进去
    ////  double *(*funcs[])(double) = { Function};实际上才是函数指针的样子

    for (int i = 0; i < 3; ++i) {
    printf("Integration = %f\n", Integrate(low, high, funcs[i]));
    }

    return 0;
}

double Integrate(double low, double high,
        double (*func)(double)) {
    double interval = (high - low) / NUM_OF_PARTITIONS;//每一个区间的长度
    //也就是矩形的宽

    double sum = 0;
    for (int i = 0; i < NUM_OF_PARTITIONS; ++i) {
    double xi = low + interval * i;
    double yi = (*func)(xi);//解引用之后马上又变成函数指针
//    double yi = func(xi)也可以，推荐用，不用解引用;函数名被转为函数指针

    sum += yi * interval;
    }

    return sum;
}

double Square(double x) {
  return x * x;
}
//搞一个平方的函数