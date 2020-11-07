# ROS_RTSP
 ————————————————————————————————————————————————————————————————————————————————————————————————
const char *转化为char *的方法
复制代码
直接将const char *赋值给char *是错误的，编译器不允许这种操作。

#include "stdio.h"
#include "string.h"
int main()
{
    //方式1 strcpy
    //方式1.1
    //const char *cpCh = "const char";
    //char ch[64]={0};
    //char *pCh = ch;　　//是不是画蛇添足啊??
    //strcpy(pCh, cpCh);

    //方式1.2
    const char *cpCh = "const char";
    int nLen = strlen(cpCh);
    char *pCh = new char[nLen + 1];
    strcpy(pCh, cpCh);


    //方式2 const_cast<>()
    //const char *cpCh = "const char";
    //char *pCh = const_cast<char *>(cpCh);//DO not forget '()'
    

    printf("%s", pCh);
    return 0;
}


——————————————————————————————————————————————————————————————————————————————————————————————————
C++ 中 string和char* 的区别 

1、定义：

string：string是STL当中的一个容器，对其进行了封装，所以操作起来非常方便。

char*：char *是一个指针，可以指向一个字符串数组，至于这个数组可以在栈上分配，也可以在堆上分配，堆得话就要你手动释放了。

2、区别：

string的内存管理是由系统处理，除非系统内存池用完，不然不会出现这种内存问题。
char *的内存管理由用户自己处理，很容易出现内存不足的问题。

当我们要存一个串，但是不知道其他需要多少内存时， 用string来处理就最好不过了。
当你知道了存储的内存的时候，可以用char *，但是不如用string的好，用指针总会有
隐患。

用string还可以使用各种成员函数来处理串的每一个字符，方便处理。
用char *处理串，就不如string的方便了，没有相应的函数来直接调用，而是要自己编
写函数来完成串的处理，而且处理过程中用指针还很容易出现内存问题。

char *s="string"的内容是不可以改的；char s[10]="string"的内容是可以改的

3、注意：

当我们定义了一个string，就不能用scanf("%s",s)和printf("%s",s)输入输出。主要是因为%s要求后面是对象的首地址

4、转化：

当 string 直接转化成 const char *时，可以通过两个函数c_str()，data成员函数，例如：


#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
    string s="xiaoming";
    const char *a=s.c_str();//去掉const会显示编译错误
    const char *b=s.data();
    printf("a:[%s],b:[%s]\n",a,b);
}

如果直接转化成char*也可以。但是我觉得这个还是挺麻烦的。

将char *转化成string，直接转化就可以。就是注意输出的问题：


#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
    char *a="xiaoming";
    string s;
    s=a;
    printf("%s\n",s.c_str());
}
