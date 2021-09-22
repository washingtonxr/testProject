#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "algorithmPack.h"
using namespace std;

/* In the Filter Code Lookup by 2 to 100 prime numbers. */
int lookUpPrimeNumbers(void)
{
    int i,j;
    for(i=2;i<100;i++)
    {
        for(j=2;j<=(double)sqrt((double)i);j++)
        {
            if(!(i%j))
                break;//不是质数
        }
        if(j>(double)sqrt((double)i))
            cout<<i<<"是质数\n";
    }
        return 0;
}

/* Based on multiples of prime numbers is definitely not prime, 
    using linear Sieve Method, you can have the time to reach an O ( n ). */
#define MAXN_N 1000001
int v[MAXN_N],primes[MAXN_N];//primes用来存储素数
int linearSieveMethod(void)
{
    int n,m=0;//m 是素数的数目 
    cout << "输入 n 的值：" << endl;
    //scanf("%d",&n);
    n = 10;
    memset(v,0,sizeof(v));
    for(int i=2;i<=n;i++)
    {
        if(v[i]==0)//i是素数 
        {
            v[i]=i;
            primes[++m]=i;
        }
        for(int j=1;j<=m;j++)
        {
            if(primes[j]>v[i]||primes[j]>n/i)break;//i有比primes[j]更小的质因子，或者超出范围
            v[i*primes[j]]=primes[j];//primes[j]是合数i*primes[j]的最小质因子 
        }
    }
    for(int i=1;i<=m;i++)
        cout<<primes[i]<<" ";

    cout << endl;
    return 0;
}

int multidimensionalArrayVector(void)
{
    vector< vector<int> > arry; //写成arry(5) 可理解为设定大小5行 
    vector<int> d;        //定义一个一维的数组; 
    signed int i, j, n;
    signed int number;
#if 0
    scanf("%d", &n );
#else
    n = 5;
#endif
    /*可以这样实现对vector二维的初始化，得到的是n行n列的矩阵*/ 
    for( i=0; i<n; i++ ){ 
        for( j=0; j<n; j++ ){
#if 0
            scanf("%d", &number );
#else
            number = 10;
#endif
            d.push_back( number ); 
        }
        sort( d.begin(), d.end() ); //pai xu xuyao头文件algorithm 
        arry.push_back( d );
        //d.clear();        //清空一维的数组 
        d.resize(0);
    }
    /*遍历输出*/ 
    if( arry.empty() )
        printf("0\n");
    else{
        for( i=0; i<(signed int)arry.size(); i++ ) {
            for( j=0; j<(signed int)arry[0].size(); j++ ){
                printf("%d ", arry[i][j] );
            }
            printf("\n");
        }
    } 
    
    return 0;
}
/* End of this file. */
