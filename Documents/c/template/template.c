#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define true 1
#define false 0
#define bool short
#define ll long long
#define ull unsigned ll
#define pow2(n) (1 << (n))

/* -- Utility function -- */
int strLength(char x[])
{
    int i;
    for(i = 0;x[i];++i);
    return i;
}

int strCompare(char x[], char y[])
{
    int i = 0;
    while(x[i] && y[i]){
        if(x[i] < y[i])
            return 1;
        else if(x[i] > y[i])
            return -1;
        ++i;
    }

    if(x[i])
        return -1;
    else if(y[i])
        return 1;
    return 0;
}

void strCopy(char from[], char dest[])
{
    int i;
    for(i = 0;from[i];++i)
        dest[i] = from[i];
    dest[i] = '\0';
}

int min(int x, int y)
{
    return x > y ? y : x;
}

int max(int x, int y)
{
    return x > y ? x : y;
}

ll power(ll a, ll b)
{
    ll ret = 1;
    while(b > 0){
        if(b % 2 == 1)
            ret *= a;
        
        a *= a;
        b /= 2;
    }

    return ret;
}
/* -- Utility function -- */

void solve()
{
    ;
}

int main()
{
    int t = 1;
    /* scanf("%d", &t); */
    for(int tc = 1;tc <= t;++tc){
        /* printf("Case #%d: ", tc); */
        solve();
    }
}
