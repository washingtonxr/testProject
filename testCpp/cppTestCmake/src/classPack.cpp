#include "classPack.h"
#include <iostream>
#include <assert.h>

using namespace std;
 
class Box
{
    double width;
    public:
        double length;   // 长度
        double breadth;  // 宽度
        double height;   // 高度
        // 成员函数声明
        double get(void);
        void set( double len, double bre, double hei );
        friend void printWidth( Box box );
        void setWidth( double wid );
        friend class BigBox;

        double getVolume(void)
        {
            return length * breadth * height;
        }

        // 重载 + 运算符，用于把两个 Box 对象相加
        Box operator+(const Box& b)
        {
            Box box;
            box.length = this->length + b.length;
            box.breadth = this->breadth + b.breadth;
            box.height = this->height + b.height;
            return box;
        }
        Box operator*(const Box& b)
        {
            Box box;
            box.length = this->length * b.length;
            box.breadth = this->breadth * b.breadth;
            box.height = this->height * b.height;
            return box;
        }
};

class BigBox
{
public :
    void Print(int width, Box &box)
    {
        // BigBox是Box的友元类，它可以直接访问Box类的任何成员
        box.setWidth(width);
        cout << "Width of box : " << box.width << endl;
    }
};

// 请注意：printWidth() 不是任何类的成员函数
void printWidth( Box box )
{
   /* 因为 printWidth() 是 Box 的友元，它可以直接访问该类的任何成员 */
   cout << "Width of box : " << box.width <<endl;
}

// 成员函数定义
double Box::get(void)
{
    return length * breadth * height;
}
 
void Box::set( double len, double bre, double hei)
{
    length = len;
    breadth = bre;
    height = hei;
}

void Box::setWidth( double wid )
{
    width = wid;
}

int testClass(void)
{
    Box Box1;        // 声明 Box1，类型为 Box
    Box Box2;        // 声明 Box2，类型为 Box
    Box Box3;        // 声明 Box3，类型为 Box
    Box Box4;        // 声明 Box4，类型为 Box
    Box Box5;        // 声明 Box5，类型为 Box
    BigBox big;
    double volume = 0.0;     // 用于存储体积

    // box 1 详述
    Box1.height = 5.0; 
    Box1.length = 6.0; 
    Box1.breadth = 7.0;

    // box 2 详述
    Box2.height = 10.0;
    Box2.length = 12.0;
    Box2.breadth = 13.0;

    // box 1 的体积
    volume = Box1.height * Box1.length * Box1.breadth;
    cout << "Box1 的体积：" << volume <<endl;

    // box 2 的体积
    volume = Box2.height * Box2.length * Box2.breadth;
    cout << "Box2 的体积：" << volume <<endl;


    // box 3 详述
    Box3.set(16.0, 8.0, 12.0); 
    volume = Box3.get(); 
    cout << "Box3 的体积：" << volume <<endl;

    Box4.set(16.0, 8.0, 12.0); 
    Box4.setWidth(10.0);
    printWidth(Box4);
    big.Print(20, Box4);

    Box5 = Box1 + Box2;

    // Box5 的体积
    volume = Box5.getVolume();
    cout << "Volume of Box5 : " << volume << endl;


    Box5 = Box1 * Box2;
    // Box5 的体积
    volume = Box5.getVolume();
    cout << "Volume of Box5 : " << volume << endl;

    return 0;
}

class Box2
{
   public:
      double length;         // 长度
      double breadth;        // 宽度
      double height;         // 高度
 
      // 成员函数声明
      double getVolume(void);
      void setLength( double len );
      void setBreadth( double bre );
      void setHeight( double hei );
};
 
// 成员函数定义
double Box2::getVolume(void)
{
    return length * breadth * height;
}
 
void Box2::setLength( double len )
{
    length = len;
}
 
void Box2::setBreadth( double bre )
{
    breadth = bre;
}
 
void Box2::setHeight( double hei )
{
    height = hei;
}
 
// 程序的主函数
int testClass2(void)
{
   Box2 Box1;                // 声明 Box1，类型为 Box
   Box2 Box2;                // 声明 Box2，类型为 Box
   double volume = 0.0;     // 用于存储体积
 
   // box 1 详述
   Box1.setLength(6.0); 
   Box1.setBreadth(7.0); 
   Box1.setHeight(5.0);
 
   // box 2 详述
   Box2.setLength(12.0); 
   Box2.setBreadth(13.0); 
   Box2.setHeight(10.0);
 
   // box 1 的体积
   volume = Box1.getVolume();
   cout << "Box1 的体积：" << volume <<endl;
 
   // box 2 的体积
   volume = Box2.getVolume();
   cout << "Box2 的体积：" << volume <<endl;
   return 0;
}

class Box3
{
   public:
      double length;
      void setWidth( double wid );
      double getWidth( void );
 
   private:
      double width;
};
 
// 成员函数定义
double Box3::getWidth(void)
{
    return width ;
}
 
void Box3::setWidth( double wid )
{
    width = wid;
}

int privateClass(void)
{
   Box3 box;
 
   // 不使用成员函数设置长度
   box.length = 10.0; // OK: 因为 length 是公有的
   cout << "Length of box : " << box.length <<endl;
 
   // 不使用成员函数设置宽度
   // box.width = 10.0; // Error: 因为 width 是私有的
   box.setWidth(10.0);  // 使用成员函数设置宽度
   cout << "Width of box : " << box.getWidth() <<endl;
 
   return 0;
}

class Box4
{
   protected:
      double width;
      double length;
};
 
class SmallBox:Box4 // SmallBox 是派生类
{
   public:
      void setSmallWidth(double wid);
      void setSmallLength(double len);
      double getSmallWidth(void);
      double getSmallLength(void);
      double getArea(void);
};
 
// 子类的成员函数
double SmallBox::getArea(void)
{
    return width*length;
}

double SmallBox::getSmallWidth(void)
{
    return width ;
}

double SmallBox::getSmallLength(void)
{
    return length;
}
 
void SmallBox::setSmallWidth(double wid)
{
    width = wid;
}

void SmallBox::setSmallLength(double len)
{
    length = len;
}
 
// 程序的主函数
int protectClass(void)
{
    SmallBox box;

    // 使用成员函数设置宽度
    box.setSmallWidth(5.0);
    box.setSmallLength(3.3);
    cout << "Width of box : "<< box.getSmallWidth() << endl;
    cout << "Length of box: "<< box.getSmallLength() << endl;
    cout << "Area of box: "<< box.getArea() << endl;
    return 0;
}

// 基类
class A_Common{
    public:
        int a;
        A_Common(void){
            a1 = 1;
            a2 = 2;
            a3 = 3;
            a = 4;
        }
        void fun(){
            cout << a << endl;    //正确
            cout << a1 << endl;   //正确
            cout << a2 << endl;   //正确
            cout << a3 << endl;   //正确
        }
    public:
        int a1;
    protected:
        int a2;
    private:
        int a3;
};

// 派生类
class B_Public : public A_Common {
    public:
        int a;
        B_Public(int i){
            A_Common();
            a = i;
        }
        void fun(){
            cout << a << endl;       //正确，public成员
            cout << a1 << endl;       //正确，基类的public成员，在派生类中仍是public成员。
            cout << a2 << endl;       //正确，基类的protected成员，在派生类中仍是protected可以被派生类访问。
            //cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
        }
};

/*
 *  ============Access control and inheritance============
 *  ------------------------------------------------------
 *  | Access        |  public  |  protected  |  private  |
 *  ------------------------------------------------------
 *  | Same Class    |  yes     |  yes        |  yes      |
 *  ------------------------------------------------------
 *  | Drived class  |  yes     |  yes        |  no       |
 *  ------------------------------------------------------
 *  | Outside class |  yes     |  no         |  no       |
 *  ------------------------------------------------------
 */
int publicInheritance(void)
{
    B_Public b(10);
    cout << "publicInheritance" << b.a << endl;
    cout << "publicInheritance" << b.a1 << endl;   //正确
    //cout << b.a2 << endl;   //错误，类外不能访问protected成员
    //cout << b.a3 << endl;   //错误，类外不能访问private成员
    //system("pause");
    return 0;
}

class B_Protect : protected A_Common{
    public:
        int a;
        B_Protect(int i){
            A_Common();
            a = i;
        }
        void fun(){
            cout << a << endl;       //正确，public成员。
            cout << a1 << endl;       //正确，基类的public成员，在派生类中变成了protected，可以被派生类访问。
            cout << a2 << endl;       //正确，基类的protected成员，在派生类中还是protected，可以被派生类访问。
            //cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
        }
};

int protectInheritance(void)
{
    B_Protect b(10);
    cout << "protectInheritance" << b.a << endl;       //正确。public成员
    //cout << b.a1 << endl;      //错误，protected成员不能在类外访问。
    //cout << b.a2 << endl;      //错误，protected成员不能在类外访问。
    //cout << b.a3 << endl;      //错误，private成员不能在类外访问。
    //system("pause");
    return 0;
}

class B_Private : private A_Common{
    public:
        int a;
        B_Private(int i){
            A_Common();
            a = i;
        }
        void fun(){
            cout << a << endl;       //正确，public成员。
            cout << a1 << endl;       //正确，基类public成员,在派生类中变成了private,可以被派生类访问。
            cout << a2 << endl;       //正确，基类的protected成员，在派生类中变成了private,可以被派生类访问。
            //cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
        }
};

int privateInheritance(void)
{
    B_Protect b(10);
    cout << "privateInheritance" << b.a << endl;       //正确。public成员
    //cout << b.a1 << endl;      //错误，private成员不能在类外访问。
    //cout << b.a2 << endl;      //错误，private成员不能在类外访问。
    //cout << b.a3 << endl;      //错误，private成员不能在类外访问。
    //system("pause");
    return 0;
}

class Line
{
    public:
        void setLength( double len );
        double getLength( void );
        Line();  // 这是构造函数
        ~Line();  // 这是构造函数
    private:
        double length;
};
 
// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}

Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}

void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}

int constructFunction(void)
{
   Line line;
 
   // 设置长度
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   return 0;
}
/* If the class does not define a copy constructor, the compiler itself defines one. 
If the class has a pointer variable, and dynamic memory allocation, it must have a copy constructor.*/
class Line2
{
   public:
      int getLength( void );
      Line2( int len );             // Simple Constructor Function.
#if 1
      Line2( const Line2 &obj);     // Copy Constructor Function.
#endif
      ~Line2();                     // Destructor Function.
 
   private:
      int *ptr;
};

Line2::Line2(int len)
{
    cout << "Call contructor function." << endl;
    ptr = new int; // 为指针分配内存
    cout << "Memory allocate:" << ptr << endl;
    *ptr = len;
}
#if 1
Line2::Line2(const Line2 &obj)
{
    cout << "Call copy contructor function." << endl;
    ptr = new int;
    cout << "Memory allocate:" << ptr << endl;
    *ptr = *obj.ptr; // Value copy.
}
#endif
Line2::~Line2(void)
{
    cout << "Release memory:" << ptr << endl;
    delete ptr;
}

int Line2::getLength( void )
{
    return *ptr;
}

void display(Line2 obj)
{
   cout << "line value : " << obj.getLength() << endl;
}

int copyConstructFunction(void)
{
   Line2 line(10);
 
   display(line);
 
   return 0;
}

int copyConstructFunction2(void)
{
   Line2 line1(10);
 
   Line2 line2 = line1; // 这里也调用了拷贝构造函数
 
   display(line1);
   display(line2);
 
   return 0;
}

class BoxX
{
    public:
        // 构造函数定义
        BoxX(double l=2.0, double b=2.0, double h=2.0)
        {
            cout <<"Constructor called." << endl;
            length = l;
            breadth = b;
            height = h;
        }
        double Volume()
        {
            return length * breadth * height;
        }
        int compare(BoxX box)
        {
            cout << "ThisVolume" << this->Volume() <<endl;
            cout << "boxVolume" << box.Volume() <<endl;
            return this->Volume() > box.Volume();
        }
    private:
        double length;     // Length of a box
        double breadth;    // Breadth of a box
        double height;     // Height of a box
};

int thisPointer(void)
{
   BoxX Box1(3.3, 1.2, 1.5);    // Declare box1
   BoxX Box2(8.5, 6.0, 2.0);    // Declare box2
 
   if(Box1.compare(Box2))
   {
      cout << "Box2 is smaller than Box1" <<endl;
   }
   else
   {
      cout << "Box2 is equal to or larger than Box1" <<endl;
   }
   return 0;
}

class BoxX2{
    public:
        BoxX2(){;}
        ~BoxX2(){;}
        BoxX2* get_address()   //得到this的地址
        {
            return this;    /* Type of this pointer can be understood as box*. */
        }
};

int thisPointer2(void)
{
    BoxX2 box1;
    BoxX2 box2;
    // BoxX2* 定义指针p接受对象box的get_address()成员函数的返回值，并打印

    BoxX2* p = box1.get_address();  
    cout << p << endl;

    p = box2.get_address();
    cout << p << endl; 

    return 0;
}

class BoxPointer
{
    public:
        static int objectCount;
        // 构造函数定义
        BoxPointer(double l=2.0, double b=2.0, double h=2.0)
        {
            cout <<"Constructor called." << endl;
            length = l;
            breadth = b;
            height = h;
            objectCount++;
        }
        double Volume()
        {
            return length * breadth * height;
        }
        static int getCount()
        {
            return objectCount;
        }
    private:
        double length;     // Length of a box
        double breadth;    // Breadth of a box
        double height;     // Height of a box
};

int BoxPointer::objectCount = 0;

int pointerPointToClass(void)
{
    BoxPointer Box1(3.3, 1.2, 1.5);    // Declare box1
    BoxPointer Box2(8.5, 6.0, 2.0);    // Declare box2
    BoxPointer *ptrBox;                // Declare pointer to a class.

    // 保存第一个对象的地址
    ptrBox = &Box1;

    // 现在尝试使用成员访问运算符来访问成员
    cout << "Volume of Box1: " << ptrBox->Volume() << endl;
    cout << "objectCount of Box1: " << ptrBox->getCount() << endl;

    // 保存第二个对象的地址
    ptrBox = &Box2;

    // 现在尝试使用成员访问运算符来访问成员
    cout << "Volume of Box2: " << ptrBox->Volume() << endl;
    cout << "objectCount of Box2: " << ptrBox->objectCount << endl;
    return 0;
}

class printData
{
   public:
      void print(int i) {
        cout << "整数为: " << i << endl;
      }
 
      void print(double  f) {
        cout << "浮点数为: " << f << endl;
      }
 
      void print(char c[]) {
        cout << "字符串为: " << c << endl;
      }
};
 
int reloadFunction(void)
{
   printData pd;
 
   // 输出整数
   pd.print(5);
   // 输出浮点数
   pd.print(500.263);
   // 输出字符串
   char c[] = "Hello C++";
   pd.print(c);
 
   return 0;
}

class Shape {
   protected:
      int width, height;
   public:
      Shape( int a=0, int b=0)
      {
         width = a;
         height = b;
      }
#if 0
      virtual int area()
      {
         cout << "Parent class area :" <<endl;
         return 0;
      }
#else
    virtual int area() = 0;
#endif
};

class Rectangle: public Shape{
   public:
      Rectangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Rectangle class area :" <<endl;
         return (width * height); 
      }
};
class Triangle: public Shape{
   public:
      Triangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Triangle class area :" <<endl;
         return (width * height / 2); 
      }
};

// 程序的主函数
int multiStatusFunction(void)
{
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);
 
   // 存储矩形的地址
   shape = &rec;
   // 调用矩形的求面积函数 area
   shape->area();
 
   // 存储三角形的地址
   shape = &tri;
   // 调用三角形的求面积函数 area
   shape->area();
   
   return 0;
}

double division(int a, int b)
{
    if( b == 0 )
    {
        throw "Division by zero condition!";
    }
    return (a/b);
}

int tryAndCatch(void)
{
    int x = 50;
    int y = 0;
    double z = 0;

    try {
        z = division(x, y);
        cout << z << endl;
    }catch (const char* msg) {
        cerr << msg << endl;
    }

    return 0;
}

/* End of this file. */
