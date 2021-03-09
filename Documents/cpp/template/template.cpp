#include<bits/stdc++.h>

// PBDS
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
using namespace std;

template<class T> using pqueue = priority_queue<T>;
template<class T> using rpqueue = priority_queue<T, vector<T>, greater<T> >;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

ll power(ll a, ll b);
int gcd(int a, int b);
void fileopen();
const int INF = 1e9 + 9;

void solve()
{
    ;
}

int main()
{
    // fileopen();

    int t = 1;
    // scanf("%d", &t);
    for(int tc = 1; tc <= t;++tc){
        // printf("Case #%d: ", tc);
        solve();
    }
}

void fileopen()
{
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
}

ll power(ll a, ll b)
{
    if(b == 0)
        return 1;
    if(b == 1)
        return a;
    if(b % 2 == 0)
    {
        ll ret = power(a, b / 2);
        return ret * ret;
    }
    return power(a, b - 1) * a;
}

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b);
}
