#include <stdio.h>
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a - b);
    return 0;
}
// 用VScode打开的文件或者文件夹，路径里面不能有：①中文②奇怪的符号（？、+、中文全角符号等）最好就是全部用英文和下划线，按照C语言变量命名的规则来给文件和文件夹命名