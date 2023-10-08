#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <cassert>
#include "essentialPack.h"
#include <limits>

using namespace std;
/////////////////////////////

/* The C++ inline function is typically used with classes. If a function is inline,
the compiler places a copy of the function's code wherever the function is called at compile time.
Any modifications to the inline function will require all clients of the function to be recompiled,
because the compiler will need to replace all the code once or the old function will continue to be used.

If you want to define a function as an inline function, you need to place the keyword inline in front of
the function name, and you need to define the function before calling it. If more than one line of
functions is defined, the compiler ignores the inline qualifier.*/

inline int Max(int x, int y)
{
    return (x > y) ? x : y;
}

int thisInlineFunction(void)
{
    cout << "Max (20,10): " << Max(20, 10) << endl;
    cout << "Max (0,200): " << Max(0, 200) << endl;
    cout << "Max (100,1010): " << Max(100, 1010) << endl;
    return 0;
}

struct Books
{
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

int dataStructureOperator(void)
{
    Books Book1; // 定义结构体类型 Books 的变量 Book1
    Books Book2; // 定义结构体类型 Books 的变量 Book2

    // Book1 详述
    strcpy(Book1.title, "C++ 教程");
    strcpy(Book1.author, "Runoob");
    strcpy(Book1.subject, "编程语言");
    Book1.book_id = 12345;

    // Book2 详述
    strcpy(Book2.title, "CSS 教程");
    strcpy(Book2.author, "Runoob");
    strcpy(Book2.subject, "前端技术");
    Book2.book_id = 12346;

    // 输出 Book1 信息
    cout << "第一本书标题 : " << Book1.title << endl;
    cout << "第一本书作者 : " << Book1.author << endl;
    cout << "第一本书类目 : " << Book1.subject << endl;
    cout << "第一本书 ID : " << Book1.book_id << endl;

    // 输出 Book2 信息
    cout << "第二本书标题 : " << Book2.title << endl;
    cout << "第二本书作者 : " << Book2.author << endl;
    cout << "第二本书类目 : " << Book2.subject << endl;
    cout << "第二本书 ID : " << Book2.book_id << endl;

    return 0;
}

int basicIoOperator(void)
{
    cout << setiosflags(ios::left | ios::showpoint); // 设左对齐，以一般实数方式显示
    cout.precision(5);                               // 设置除小数点外有五位有效数字
    cout << 123.456789 << endl;
    cout.width(10);                   // 设置显示域宽10
    cout.fill('*');                   // 在显示区域空白处用*填充
    cout << resetiosflags(ios::left); // 清除状态左对齐
    cout << setiosflags(ios::right);  // 设置右对齐
    cout << 123.456789 << endl;
    cout << setiosflags(ios::left | ios::fixed); // 设左对齐，以固定小数位显示
    cout.precision(3);                           // 设置实数显示三位小数
    cout << 999.123456 << endl;
    cout << resetiosflags(ios::left | ios::fixed);    // 清除状态左对齐和定点格式
    cout << setiosflags(ios::left | ios::scientific); // 设置左对齐，以科学技术法显示
    cout.precision(3);                                // 设置保留三位小数
    cout << 123.45678 << endl;
    return 0;
}

int timeNdate(void)
{
    // 基于当前系统的当前日期/时间
    time_t now = time(0);

    cout << "1970 到目前经过秒数:" << now << endl;

    tm *ltm = localtime(&now);

    // 输出 tm 结构的各个组成部分
    cout << "年: " << 1900 + ltm->tm_year << endl;
    cout << "月: " << 1 + ltm->tm_mon << endl;
    cout << "日: " << ltm->tm_mday << endl;
    cout << "时间: " << ltm->tm_hour << ":";
    cout << ltm->tm_min << ":";
    cout << ltm->tm_sec << endl;

    return 0;
}

double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double &setValues(int i)
{
    double &ref = vals[i];
    return ref; // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
}

int referenceAsReturnValue(void)
{
    cout << "改变前的值" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    setValues(1) = 20.23; // 改变第 2 个元素
    setValues(3) = 70.8;  // 改变第 4 个元素

    cout << "改变后的值" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }
    return 0;
}

void swap4(int &x, int &y)
{
    int temp;
    temp = x; /* 保存地址 x 的值 */
    x = y;    /* 把 y 赋值给 x */
    y = temp; /* 把 x 赋值给 y  */

    return;
}

int referenceAsParameter(void)
{
    // 局部变量声明
    int a = 100;
    int b = 200;

    cout << "交换前，a 的值:" << a << endl;
    cout << "交换前，b 的值:" << b << endl;

    /* 调用函数来交换值 */
    swap4(a, b);

    cout << "交换后，a 的值:" << a << endl;
    cout << "交换后，b 的值:" << b << endl;

    return 0;
}

int thisReferenceOperator(void)
{
    // 声明简单的变量
    int i;
    double d;

    // 声明引用变量
    int &r = i;
    double &s = d;
    i = 5;
    cout << "Value of i : " << i << endl;
    cout << "Value of i reference : " << r << endl;

    d = 11.7;
    cout << "Value of d : " << d << endl;
    cout << "Value of d reference : " << s << endl;

    return 0;
}

static int *getRandom2(void)
{
    static int r[10];

    // 设置种子
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; ++i)
    {
        r[i] = rand();
        cout << r[i] << endl;
    }

    return r;
}

int functionReturePointer(void)
{
    // 一个指向整数的指针
    int *p;

    p = getRandom2();
    for (int i = 0; i < 10; i++)
    {
        cout << "*(p + " << i << ") : ";
        cout << *(p + i) << endl;
    }

    return 0;
}

static double getAverage2(int *arr, int size)
{
    int i, sum = 0;
    double avg;

    for (i = 0; i < size; ++i)
    {
        sum += arr[i];
    }

    avg = double(sum) / size;

    return avg;
}

int functionWithPointerParemeter(void)
{
    // 带有 5 个元素的整型数组
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg;

    // 传递一个指向数组的指针作为参数
    avg = getAverage2(balance, 5);

    // 输出返回值
    cout << "Average value is: " << avg << endl;

    return 0;
}

int pointerPointToPointer(void)
{
    int var;
    int *ptr;
    int **pptr;

    var = 3000;

    // 获取 var 的地址
    ptr = &var;

    // 使用运算符 & 获取 ptr 的地址
    pptr = &ptr;

    // 使用 pptr 获取值
    cout << "var 值为 :" << var << endl;
    cout << "*ptr 值为:" << *ptr << endl;
    cout << "**pptr 值为:" << **pptr << endl;

    return 0;
}

const int MAX = 3;
int pinterArray(void)
{
    int var[MAX] = {10, 100, 200};
    int *ptr[MAX];

    for (int i = 0; i < MAX; i++)
    {
        ptr[i] = &var[i]; // 赋值为整数的地址
    }

    for (int i = 0; i < MAX; i++)
    {
        cout << "Value of var[" << i << "] = ";
        cout << *ptr[i] << endl;
    }
    return 0;
}

int pointerAndArray(void)
{
    int var[MAX] = {10, 100, 200};
    int *ptr;

    // 指针中的数组地址
    ptr = var;
    for (int i = 0; i < MAX; i++)
    {
        cout << "var[" << i << "]的内存地址为 ";
        cout << ptr << endl;
        cout << "var[" << i << "] 的值为 ";
        cout << *ptr << endl;
        // 移动到下一个位置
        ptr++;
    }
    return 0;
}

int pointerArithmetic3(void)
{
    int var[MAX] = {10, 100, 200};
    int *ptr;

    // 指针中第一个元素的地址
    ptr = var;
    int i = 0;
    while (ptr <= &var[MAX - 1])
    {
        cout << "Address of var[" << i << "] = ";
        cout << ptr << endl;
        cout << "Value of var[" << i << "] = ";
        cout << *ptr << endl;
        // 指向上一个位置
        ptr++;
        i++;
    }
    return 0;
}

int pointerArithmetic2(void)
{
    int var[MAX] = {10, 100, 200};
    int *ptr;

    // 指针中最后一个元素的地址
    ptr = &var[MAX - 1];
    for (int i = MAX; i > 0; i--)
    {
        cout << "Address of var[" << i << "] = ";
        cout << ptr << endl;

        cout << "Value of var[" << i << "] = ";
        cout << *ptr << endl;

        // 移动到下一个位置
        ptr--;
    }
    return 0;
}

int pointerArithmetic1(void)
{
    int var[MAX] = {10, 100, 200};
    int *ptr;

    // 指针中的数组地址
    ptr = var;
    for (int i = 0; i < MAX; i++)
    {
        cout << "Address of var[" << i << "] = ";
        cout << ptr << endl;

        cout << "Value of var[" << i << "] = ";
        cout << *ptr << endl;

        // 移动到下一个位置
        ptr++;
    }
    return 0;
}

int nullPointer(void)
{
    int *ptr = NULL;

    cout << "ptr 的值是 " << ptr;

    return 0;
}

int pointerOperator(void)
{
    int var = 20; // 实际变量的声明
    int *ip;      // 指针变量的声明

    ip = &var; // 在指针变量中存储 var 的地址

    cout << "Value of var variable: ";
    cout << var << endl;

    // 输出在指针变量中存储的地址
    cout << "Address stored in ip variable: ";
    cout << ip << endl;

    // 访问指针中地址的值
    cout << "Value of *ip variable: ";
    cout << *ip << endl;

    return 0;
}

int stringClass(void)
{
    string str1 = "runoob";
    string str2 = "google";
    string str3;
    int len;

    // 复制 str1 到 str3
    str3 = str1;
    cout << "str3 : " << str3 << endl;

    // 连接 str1 和 str2
    str3 = str1 + str2;
    cout << "str1 + str2 : " << str3 << endl;

    // 连接后，str3 的总长度
    len = str3.size();
    cout << "str3.size() :  " << len << endl;

    return 0;
}

int thisAboutString(void)
{
    char str1[13] = "runoob";
    char str2[13] = "google";
    char str3[13];
    int len;

    // 复制 str1 到 str3
    strcpy(str3, str1);
    cout << "strcpy( str3, str1) : " << str3 << endl;

    // 连接 str1 和 str2
    strcat(str1, str2);
    cout << "strcat( str1, str2): " << str1 << endl;

    // 连接后，str1 的总长度
    len = strlen(str1);
    cout << "strlen(str1) : " << len << endl;

    return 0;
}

static int *getRandom(void)
{
    static int r[10];

    // 设置种子
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; ++i)
    {
        r[i] = rand();
        cout << r[i] << endl;
    }

    return r;
}

int functionRetureAnArray(void)
{
    // 一个指向整数的指针
    int *p;

    p = getRandom();
    for (int i = 0; i < 10; i++)
    {
        cout << "*(p + " << i << ") : ";
        cout << *(p + i) << endl;
    }

    return 0;
}

static double getAverage(int arr[], int size)
{
    int i, sum = 0;
    double avg;

    for (i = 0; i < size; ++i)
    {
        sum += arr[i];
    }

    avg = double(sum) / size;

    return avg;
}

int passAnArrayToFunction(void)
{
    // 带有 5 个元素的整型数组
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg;

    // 传递一个指向数组的指针作为参数
    avg = getAverage(balance, 5);

    // 输出返回值
    cout << "平均值是:" << avg << endl;

    return 0;
}

int arrayPointToPointer(void)
{
    // 带有 5 个元素的双精度浮点型数组
    double runoobAarray[5] = {1000.0, 2.0, 3.4, 17.0, 50.0};
    double *p;

    p = runoobAarray;

    // 输出数组中每个元素的值
    cout << "使用指针的数组值 " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "*(p + " << i << ") : ";
        cout << *(p + i) << endl;
    }

    cout << "使用 runoobAarray 作为地址的数组值 " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "*(runoobAarray + " << i << ") : ";
        cout << *(runoobAarray + i) << endl;
    }

    return 0;
}

int multidimensionalArray(void)
{
    // 一个带有 5 行 2 列的数组
    int a[5][2] = {{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}};

    // 输出数组中每个元素的值
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
        {
            cout << "a[" << i << "][" << j << "]: ";
            cout << a[i][j] << endl;
        }

    return 0;
}

#include <iomanip>
using std::setw;

int accessingAnArray(void)
{
    int n[10]; // n 是一个包含 10 个整数的数组

    // 初始化数组元素
    for (int i = 0; i < 10; i++)
    {
        n[i] = i + 100; // 设置元素 i 为 i + 100
    }
    cout << "Element" << setw(13) << "Value" << endl;

    // 输出数组中每个元素的值
    for (int j = 0; j < 10; j++)
    {
        cout << setw(7) << j << setw(13) << n[j] << endl;
    }

    return 0;
}

int randomNumber(void)
{
    int i, j;

    // 设置种子
    srand((unsigned)time(NULL));

    /* 生成 10 个随机数 */
    for (i = 0; i < 10; i++)
    {
        // 生成实际的随机数
        j = rand();
        cout << "随机数: " << j << endl;
    }

    return 0;
}

int mathematicalOperator(void)
{
    // 数字定义
    // short  s = 10;
    int i = -1000;
    // long   l = 100000;
    float f = 230.47;
    double d = 200.374;

    // 数学运算
    cout << "sin(d) :" << sin(d) << endl;
    cout << "abs(i)  :" << abs(i) << endl;
    cout << "floor(d) :" << floor(d) << endl;
    cout << "sqrt(f) :" << sqrt(f) << endl;
    cout << "pow( d, 2) :" << pow(d, 2) << endl;

    return 0;
}

int thisNumberial(void)
{
    // 数字定义
    short s;
    int i;
    long l;
    float f;
    double d;

    // 数字赋值
    s = 10;
    i = 1000;
    l = 1000000;
    f = 230.47;
    d = 30949.374;

    // 数字输出
    cout << "short  s :" << s << endl;
    cout << "int    i :" << i << endl;
    cout << "long   l :" << l << endl;
    cout << "float  f :" << f << endl;
    cout << "double d :" << d << endl;

    return 0;
}

static void swap3(int &x, int &y)
{
    int temp;
    temp = x; /* 保存地址 x 的值 */
    x = y;    /* 把 y 赋值给 x */
    y = temp; /* 把 x 赋值给 y  */

    return;
}

int referenceFunction(void)
{
    // 局部变量声明
    int a = 100;
    int b = 200;

    cout << "交换前，a 的值:" << a << endl;
    cout << "交换前，b 的值:" << b << endl;

    /* 调用函数来交换值 */
    swap3(a, b);

    cout << "交换后，a 的值:" << a << endl;
    cout << "交换后，b 的值:" << b << endl;

    return 0;
}

static void swap2(int *x, int *y)
{
    int temp;
    temp = *x; /* 保存地址 x 的值 */
    *x = *y;   /* 把 y 赋值给 x */
    *y = temp; /* 把 x 赋值给 y */

    return;
}

int passPointerFunction(void)
{
    // 局部变量声明
    int a = 100;
    int b = 200;

    cout << "交换前，a 的值:" << a << endl;
    cout << "交换前，b 的值:" << b << endl;

    /* 调用函数来交换值
     * &a 表示指向 a 的指针，即变量 a 的地址
     * &b 表示指向 b 的指针，即变量 b 的地址
     */
    swap2(&a, &b);

    cout << "交换后，a 的值:" << a << endl;
    cout << "交换后，b 的值:" << b << endl;

    return 0;
}

static void swap1(int x, int y)
{
#if 1
    int temp;

    temp = x; /* 保存 x 的值 */
    x = y;    /* 把 y 赋值给 x */
    y = temp; /* 把 x 赋值给 y */
#else
#if 0
   x = x + y;
   y = x - y;
   x = x - y;
#else
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
#endif
#endif
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    return;
}

int passValueFunction(void)
{
    // 局部变量声明
    int a = 100;
    int b = 200;

    cout << "交换前，a 的值:" << a << endl;
    cout << "交换前，b 的值:" << b << endl;

    // 调用函数来交换值
    swap1(a, b);

    cout << "交换后，a 的值:" << a << endl;
    cout << "交换后，b 的值:" << b << endl;

    return 0;
}

int neatedSwitchOperator(void)
{
    // 局部变量声明
    int a = 100;
    int b = 200;

    switch (a)
    {
    case 100:
        cout << "这是外部 switch 的一部分" << endl;
        switch (b)
        {
        case 200:
            cout << "这是内部 switch 的一部分" << endl;
        }
    }
    cout << "a 的准确值是 " << a << endl;
    cout << "b 的准确值是 " << b << endl;

    return 0;
}

int thisSwitchOperator(void)
{
    // 局部变量声明
    char grade = 'D';

    switch (grade)
    {
    case 'A':
        cout << "很棒！" << endl;
        break;
    case 'B':
    case 'C':
        cout << "做得好" << endl;
        break;
    case 'D':
        cout << "您通过了" << endl;
        break;
    case 'F':
        cout << "最好再试一下" << endl;
        break;
    default:
        cout << "无效的成绩" << endl;
    }
    cout << "您的成绩是 " << grade << endl;

    return 0;
}

int neatedIfOperator(void)
{
    // 局部变量声明
    int a = 100;
    int b = 200;

    // 检查布尔条件
    if (a == 100)
    {
        // 如果条件为真，则检查下面的条件
        if (b == 200)
        {
            // 如果条件为真，则输出下面的语句
            cout << "a 的值是 100，且 b 的值是 200" << endl;
        }
    }
    cout << "a 的准确值是 " << a << endl;
    cout << "b 的准确值是 " << b << endl;

    return 0;
}

int thisIfElseOperator(void)
{
    // 局部变量声明
    int a = 100;

    // 检查布尔条件
    if (a == 10)
    {
        // 如果 if 条件为真，则输出下面的语句
        cout << "a 的值是 10" << endl;
    }
    else if (a == 20)
    {
        // 如果 else if 条件为真，则输出下面的语句
        cout << "a 的值是 20" << endl;
    }
    else if (a == 30)
    {
        // 如果 else if 条件为真，则输出下面的语句
        cout << "a 的值是 30" << endl;
    }
    else
    {
        // 如果上面条件都不为真，则输出下面的语句
        cout << "没有匹配的值" << endl;
    }
    cout << "a 的准确值是 " << a << endl;

    return 0;
}

int thisIfOperator(void)
{
    // 局部变量声明
    int a = 10;

    // 使用 if 语句检查布尔条件
    if (a < 20)
    {
        // 如果条件为真，则输出下面的语句
        cout << "a 小于 20" << endl;
    }
    cout << "a 的值是 " << a << endl;

    return 0;
}

int thisGotoOperator(void)
{
    // 局部变量声明
    int a = 10;

// do 循环执行
LOOP:
    do
    {
        if (a == 15)
        {
            // 跳过迭代
            a = a + 1;
            goto LOOP;
        }
        cout << "a 的值:" << a << endl;
        a = a + 1;
    } while (a < 20);

    return 0;
}

int thisDoLoopOperator(void)
{
    // 局部变量声明
    int a = 10;

    // do 循环执行
    do
    {
        if (a == 15)
        {
            // 跳过迭代
            a = a + 1;
            continue;
        }
        cout << "a 的值:" << a << endl;
        a = a + 1;
    } while (a < 20);

    return 0;
}

#if 0
int infiniteLoopOperator(void)
{
   for( ; ; )
   {
      printf("This loop will run forever.\n");
   }

   return 0;
}
#endif

int breakOperator(void)
{
    // 局部变量声明
    int a = 10;

    // do 循环执行
    do
    {
        cout << "a 的值:" << a << endl;
        a = a + 1;
        if (a > 15)
        {
            // 终止循环
            break;
        }
    } while (a < 20);

    return 0;
}

int nestedLoopOperator(void)
{
    int i, j;
    for (i = 2; i < 100; i++)
    {
        for (j = 2; j <= (i / j); j++)
        {
            if (!(i % j))
            {
                break; // 如果找到，则不是质数
            }
        }
        if (j > (i / j))
        {
            cout << i << " 是质数\n";
        }
    }
    return 0;
}

int doWhileOperator(void)
{
    // 局部变量声明
    int a = 10;

    // do 循环执行
    do
    {
        cout << "a 的值:" << a << endl;
        a = a + 1;
    } while (a < 20);

    return 0;
}

int whileOperator(void)
{
    int y = 10;
    int count = 0;
    while (y--)
    {
        ++count;
        cout << "第" << count << "次: y =" << y << endl;
    }
    cout << "最后y的值:" << y << endl;
    return 0;
}

int forOperator(void)
{
    // 局部变量声明
    int a = 10;

    // while 循环执行
    while (a < 20)
    {
        cout << "a 的值:" << a << endl;
        a++;
    }

    return 0;
}

int operatorPrecedenceOperator(void)
{
    int a = 20;
    int b = 10;
    int c = 15;
    int d = 5;
    int e;

    e = (a + b) * c / d; // ( 30 * 15 ) / 5
    cout << "(a + b) * c / d 的值是 " << e << endl;

    e = ((a + b) * c) / d; // (30 * 15 ) / 5
    cout << "((a + b) * c) / d 的值是 " << e << endl;

    e = (a + b) * (c / d); // (30) * (15/5)
    cout << "(a + b) * (c / d) 的值是 " << e << endl;

    e = a + (b * c) / d; //  20 + (150/5)
    cout << "a + (b * c) / d 的值是 " << e << endl;

    return 0;
}

int assigningOperator(void)
{
    int a = 21;
    int c;

    c = a;
    cout << "Line 1 - =  运算符实例，c 的值 = : " << c << endl;

    c += a;
    cout << "Line 2 - += 运算符实例，c 的值 = : " << c << endl;

    c -= a;
    cout << "Line 3 - -= 运算符实例，c 的值 = : " << c << endl;

    c *= a;
    cout << "Line 4 - *= 运算符实例，c 的值 = : " << c << endl;

    c /= a;
    cout << "Line 5 - /= 运算符实例，c 的值 = : " << c << endl;

    c = 200;
    c %= a;
    cout << "Line 6 - %= 运算符实例，c 的值 = : " << c << endl;

    c <<= 2;
    cout << "Line 7 - <<= 运算符实例，c 的值 = : " << c << endl;

    c >>= 2;
    cout << "Line 8 - >>= 运算符实例，c 的值 = : " << c << endl;

    c &= 2;
    cout << "Line 9 - &= 运算符实例，c 的值 = : " << c << endl;

    c ^= 2;
    cout << "Line 10 - ^= 运算符实例，c 的值 = : " << c << endl;

    c |= 2;
    cout << "Line 11 - |= 运算符实例，c 的值 = : " << c << endl;

    return 0;
}
int bitwiseOperator(void)
{
    unsigned int a = 60; // 60 = 0011 1100
    unsigned int b = 13; // 13 = 0000 1101
    int c = 0;

    c = a & b; // 12 = 0000 1100
    cout << "Line 1 - c 的值是 " << c << endl;

    c = a | b; // 61 = 0011 1101
    cout << "Line 2 - c 的值是 " << c << endl;

    c = a ^ b; // 49 = 0011 0001
    cout << "Line 3 - c 的值是 " << c << endl;

    c = ~a; // -61 = 1100 0011
    cout << "Line 4 - c 的值是 " << c << endl;

    c = a << 2; // 240 = 1111 0000
    cout << "Line 5 - c 的值是 " << c << endl;

    c = a >> 2; // 15 = 0000 1111
    cout << "Line 6 - c 的值是 " << c << endl;

    return 0;
}

int logicalOperator(void)
{
    int a = 5;
    int b = 20;

    if (a && b)
    {
        cout << "Line 1 - 条件为真" << endl;
    }
    if (a || b)
    {
        cout << "Line 2 - 条件为真" << endl;
    }
    /* 改变 a 和 b 的值 */
    a = 0;
    b = 10;
    if (a && b)
    {
        cout << "Line 3 - 条件为真" << endl;
    }
    else
    {
        cout << "Line 4 - 条件不为真" << endl;
    }
    if (!(a && b))
    {
        cout << "Line 5 - 条件为真" << endl;
    }
    return 0;
}

int arithemeticOperator(void)
{
    int a = 21;
    int b = 10;
    int c;

    c = a + b;
    cout << "Line 1 - c 的值是 " << c << endl;
    c = a - b;
    cout << "Line 2 - c 的值是 " << c << endl;
    c = a * b;
    cout << "Line 3 - c 的值是 " << c << endl;
    c = a / b;
    cout << "Line 4 - c 的值是 " << c << endl;
    c = a % b;
    cout << "Line 5 - c 的值是 " << c << endl;

    int d = 10; //  测试自增、自减
    c = d++;
    cout << "Line 6 - c 的值是 " << c << endl;

    d = 10; // 重新赋值
    c = d--;
    cout << "Line 7 - c 的值是 " << c << endl;
    return 0;
}

int relationalOperator(void)
{
    int a = 21;
    int b = 10;

    if (a == b)
    {
        cout << "Line 1 - a 等于 b" << endl;
    }
    else
    {
        cout << "Line 1 - a 不等于 b" << endl;
    }
    if (a < b)
    {
        cout << "Line 2 - a 小于 b" << endl;
    }
    else
    {
        cout << "Line 2 - a 不小于 b" << endl;
    }
    if (a > b)
    {
        cout << "Line 3 - a 大于 b" << endl;
    }
    else
    {
        cout << "Line 3 - a 不大于 b" << endl;
    }
    /* 改变 a 和 b 的值 */
    a = 5;
    b = 20;
    if (a <= b)
    {
        cout << "Line 4 - a 小于或等于 b" << endl;
    }
    if (b >= a)
    {
        cout << "Line 5 - b 大于或等于 a" << endl;
    }
    return 0;
}

int thisAssert(void)
{
    static_assert(4 <= sizeof(int), "siz eof(int) too small");
    // static_assert(0,"siz eof(int) too small");
    assert(1);
    // assert(0);
    return 0;
}

int essentialCheckVariableLength(bool bEnable)
{
    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    cout << "type: \t\t"
         << "************size**************" << endl;
    cout << "bool: \t\t"
         << "所占字节数:" << sizeof(bool);
    cout << "\t最大值:" << (numeric_limits<bool>::max)();
    cout << "\t\t最小值:" << (numeric_limits<bool>::min)() << endl;
    cout << "char: \t\t"
         << "所占字节数:" << sizeof(char);
    cout << "\t最大值:" << (numeric_limits<char>::max)();
    cout << "\t\t最小值:" << (numeric_limits<char>::min)() << endl;
    cout << "signed char: \t"
         << "所占字节数:" << sizeof(signed char);
    cout << "\t最大值:" << (numeric_limits<signed char>::max)();
    cout << "\t\t最小值:" << (numeric_limits<signed char>::min)() << endl;
    cout << "unsigned char: \t"
         << "所占字节数:" << sizeof(unsigned char);
    cout << "\t最大值:" << (numeric_limits<unsigned char>::max)();
    cout << "\t\t最小值:" << (numeric_limits<unsigned char>::min)() << endl;
    cout << "wchar_t: \t"
         << "所占字节数:" << sizeof(wchar_t);
    cout << "\t最大值:" << (numeric_limits<wchar_t>::max)();
    cout << "\t\t最小值:" << (numeric_limits<wchar_t>::min)() << endl;
    cout << "short: \t\t"
         << "所占字节数:" << sizeof(short);
    cout << "\t最大值:" << (numeric_limits<short>::max)();
    cout << "\t\t最小值:" << (numeric_limits<short>::min)() << endl;
    cout << "int: \t\t"
         << "所占字节数:" << sizeof(int);
    cout << "\t最大值:" << (numeric_limits<int>::max)();
    cout << "\t最小值:" << (numeric_limits<int>::min)() << endl;
    cout << "unsigned: \t"
         << "所占字节数:" << sizeof(unsigned);
    cout << "\t最大值:" << (numeric_limits<unsigned>::max)();
    cout << "\t最小值:" << (numeric_limits<unsigned>::min)() << endl;
    cout << "long: \t\t"
         << "所占字节数:" << sizeof(long);
    cout << "\t最大值:" << (numeric_limits<long>::max)();
    cout << "\t最小值:" << (numeric_limits<long>::min)() << endl;
    cout << "unsigned long: \t"
         << "所占字节数:" << sizeof(unsigned long);
    cout << "\t最大值:" << (numeric_limits<unsigned long>::max)();
    cout << "\t最小值:" << (numeric_limits<unsigned long>::min)() << endl;
    cout << "double: \t"
         << "所占字节数:" << sizeof(double);
    cout << "\t最大值:" << (numeric_limits<double>::max)();
    cout << "\t最小值:" << (numeric_limits<double>::min)() << endl;
    cout << "long double: \t"
         << "所占字节数:" << sizeof(long double);
    cout << "\t最大值:" << (numeric_limits<long double>::max)();
    cout << "\t最小值:" << (numeric_limits<long double>::min)() << endl;
    cout << "float: \t\t"
         << "所占字节数:" << sizeof(float);
    cout << "\t最大值:" << (numeric_limits<float>::max)();
    cout << "\t最小值:" << (numeric_limits<float>::min)() << endl;
    cout << "size_t: \t"
         << "所占字节数:" << sizeof(size_t);
    cout << "\t最大值:" << (numeric_limits<size_t>::max)();
    cout << "\t最小值:" << (numeric_limits<size_t>::min)() << endl;
    cout << "string: \t"
         << "所占字节数:" << sizeof(string) << endl;
    // << "\t最大值:" << (numeric_limits<string>::max)() << "\t最小值:" << (numeric_limits<string>::min)() << endl;
    cout << "type: \t\t"
         << "************size**************" << endl;
    return 0;
}

int essentialTypeConversion(bool bEnable)
{
    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    int i = 10;
    float f = static_cast<float>(i); // 静态将int类型转换为float类型

    cout << "f = " << f << endl;

    return 0;
}

/* Test content */
class cStudent
{
private:
    string sName;
    string sID;
    char cGender;
    int lAge;

public:
    void printInfo(void);
    int setInfo(const string &name_, const string &id_, int age_, char gender_);
    string getName(void);
};

void cStudent::printInfo(void)
{
    cout << "Name: " << sName << endl;
    cout << "ID: " << sID << endl;
    cout << "Gender: " << cGender << endl;
    cout << "Age: " << lAge << endl;
    return;
}

int cStudent::setInfo(const string &name_, const string &id_, int age_, char gender_)
{
    sName = name_;
    sID = id_;
    cGender = gender_;
    lAge = age_;
    return 0;
}

string cStudent::getName(void)
{
    return sName;
}

class cUndergraduateStudent : public cStudent
{
private:
    string sDepartment;

public:
    void qualificationCheck(bool bEnable)
    {
        cout << "Qualification " << bEnable << endl;
    }
    void printInfo(void)
    {
        cout << "==============" << endl;
        cStudent::printInfo();
        cout << "Department: " << sDepartment << endl;
    }
    void setInfo(const string &name_, const string &id_, char gender_,
                 int age_, const string &department_)
    {
        cStudent::setInfo(name_, id_, age_, gender_);
        sDepartment = department_;
    }
};

static int checkClassFundamental(bool bEnable)
{
    cStudent student1;
    cUndergraduateStudent student2, student3, student4;

    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    student2.setInfo("Harry Potter", "1234567890", 'M', 18, "Hogwarts");
    student3.setInfo("Hermione Granger", "1234567891", 'F', 18, "Hogwarts");
    student4.setInfo("Lord Voldemort", "1234567892", 'M', 18, "Hogwarts");

    cout << student2.getName() << " " << endl;

    student2.qualificationCheck(true);
    student3.qualificationCheck(true);
    student4.qualificationCheck(false);

    student2.printInfo();
    student3.printInfo();
    student4.printInfo();

    cout << "sizeof(string) = " << sizeof(string) << endl;
    cout << "sizeof(cStudent) = " << sizeof(cStudent) << endl;
    cout << "sizeof(cUndergraduateStudent) = " << sizeof(cUndergraduateStudent) << endl;

    return 0;
}

static int checkSum(int a, int b = 20)
{
    int result;
    result = a + b;
    return (result);
}

static int checkMixFundamental(bool bEnable)
{
    int a = 100;
    // float f = 0;
    auto f = 0.0;

    class Example
    {
    public:
        int get_value() const
        {
            return value_; // const 关键字表示该成员函数不会修改对象中的数据成员
        }
        void set_value(int value) const
        {
            value_ = value; // mutable 关键字允许在 const 成员函数中修改成员变量
        }

    private:
        mutable int value_;
    } constTest;

    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    {
        int a = 500;
        cout << "a(IN block) = " << a << endl;
    }
    cout << "a(OUT block)  = " << a << endl;

    a = 85;
    cout << "a(OUT block)  = " << a << endl;
    a = 0123;
    cout << "a(OUT block)  = " << a << endl;
    a = 0x2b;
    cout << "a(OUT block)  = " << a << endl;
    a = 85l;
    cout << "a(OUT block)  = " << a << endl;
    a = 85ul;
    cout << "a(OUT block)  = " << a << endl;
    a = 85u;
    cout << "a(OUT block)  = " << a << endl;

    cout << "sizeof(float) = " << sizeof(float) << endl;
    f = 3.141592653979323846264338327950288;
    cout << "f = " << f << endl;
    f = 314159e-5L;
    cout << "f = " << f << endl;

    cout << "sizeof(long int) = " << sizeof(long int) << endl;
    cout << "sizeof(long long int) = " << sizeof(long long int) << endl;

    constTest.set_value(10);
    cout << constTest.get_value() << endl;

    cout << "Sum 1 = " << checkSum(100, 200) << endl;
    cout << "Sum 2 = " << checkSum(100) << endl;

    return 0;
}

/* Test end */

int checkRandomNumber(bool bEnable)
{
    int *p;
    int r[10];

    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    p = r;
    srand( (unsigned)time( NULL ) );
    for (int i = 0; i < 10; ++i)
    {
        r[i] = rand();
        cout << r[i] << endl;
    }

    for ( int i = 0; i < 10; i++ )
    {
        cout << "*(p + " << i << ") : ";
        cout << *(p + i) << endl;
    }

    return 0;
}

#define BST (+1)
#define CCT (+8)

int checkTime(bool bEnable)
{
    time_t tTime, tTimeStart, tTimeEnd;
    struct tm *pTimeInfo;
    clock_t tSysClockStart, tSysClockEnd;
    double dTotalTime;
    int lRet;
    char cBuffer[128];

    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    tSysClockStart = clock();
    time(&tTimeStart);

    tTime = time(NULL);
    cout << "The hour number from 1970-01-01 = " << tTime/3600 << endl;

    time(&tTime);
    cout << "Current time = " << ctime(&tTime) << endl;

    pTimeInfo = localtime(&tTime);
    cout << "Current local time & date = " << asctime(pTimeInfo) << endl;

    strftime(cBuffer, sizeof(cBuffer), "%Y-%m-%d %H:%M:%S", pTimeInfo);
    printf("格式化的日期 & 时间 : |%s|\n", cBuffer );

    time(&tTime);
    pTimeInfo = gmtime(&tTime);
    cout << "Current world time: "<< endl;
    cout << "London time: " << (pTimeInfo->tm_hour + BST)%24 << ":" << pTimeInfo->tm_min << endl;
    cout << "China time: " << (pTimeInfo->tm_hour + CCT)%24 << ":" << pTimeInfo->tm_min << endl;

    printf("当前的世界时钟：\n");
    printf("伦敦：%02d:%02d\n", (pTimeInfo->tm_hour+BST)%24, pTimeInfo->tm_min);
    printf("中国：%02d:%02d\n", (pTimeInfo->tm_hour+CCT)%24, pTimeInfo->tm_min);

    time(&tTime);
    pTimeInfo = gmtime(&tTime);
    lRet = mktime(pTimeInfo);
    if( lRet == -1 ) {
        printf("Error: unable to make time using mktime\n");
    } else {
        strftime(cBuffer, sizeof(cBuffer), "mktime %c\n", pTimeInfo );
        printf("%s\n", cBuffer);
    }

    time(&tTimeEnd);
    dTotalTime = difftime(tTimeEnd, tTimeStart);
    printf("执行时间 = %f\n", dTotalTime);

    tSysClockEnd = clock();
    dTotalTime = (double)(tSysClockEnd - tSysClockStart)/CLOCKS_PER_SEC;
    cout << "CPU escaped time = " << dTotalTime << endl;

    return 0;
}

int essentialTestAllInOne(bool bEnable)
{
    if (!bEnable)
    {
        cout << "The function" << __FUNCTION__ << "is not enable." << endl;
        return 0;
    }

    cout << "Function " << __FUNCTION__ << "Line " << __LINE__ << endl;

    /* Test content */
    checkClassFundamental(true);
    checkMixFundamental(true);
    checkRandomNumber(true);
    checkTime(true);

    return 0;
}
/* End of this file. */
