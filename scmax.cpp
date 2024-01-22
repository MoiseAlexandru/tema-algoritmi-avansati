#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
ifstream in("scmax.in");
ofstream out("scmax.out");
const int maxn = 100005;
int aint[maxn * 4];
int dp[maxn]; /// dp[i] = lungimea scmax care se in valoarea i
              /// dp[i] = max(dp[j]) + 1, unde j < i si v[j] < v[i]
int aux[maxn];
int v[maxn];
map <int, int> mp;
vector <int> sol;

void update(int nod, int x, int y, int poz, int val)
{
    if(poz < x || poz > y)
        return;
    if(x == y)
    {
        aint[nod] = val;
        return;
    }
    int mij = (x + y) / 2;
    update(nod * 2, x, mij, poz, val);
    update(nod * 2 + 1, mij + 1, y, poz, val);
    aint[nod] = max(aint[nod * 2], aint[nod * 2 + 1]);
}

int query(int nod, int st, int dr, int x, int y)
{
    if(dr < x || st > y)
        return 0;
    if(x <= st && dr <= y)
        return aint[nod];
    int mij = (st + dr) / 2;
    int q1 = query(nod * 2, st, mij, x, y);
    int q2 = query(nod * 2 + 1, mij + 1, dr, x, y);
    return max(q1, q2);
}

int main()
{
    int n;
    in >> n;
    for(int i = 1; i <= n; i++)
    {
        in >> v[i];
        aux[i] = v[i];
    }
    sort(aux + 1, aux + n + 1);
    int val = 0;
    for(int i = 1; i <= n; i++)
        if(aux[i] != aux[i - 1])
            mp[aux[i]] = ++val;
    for(int i = 1; i <= n; i++)
        aux[i] = v[i];
    for(int i = 1; i <= n; i++)
        v[i] = mp[v[i]];
    for(int i = 1; i <= n; i++)
    {
        dp[i] = query(1, 1, n, 1, v[i] - 1) + 1;
        update(1, 1, n, v[i], dp[i]);
    }
    int mx = 0, pozmx = 0;
    for(int i = 1; i <= n; i++)
    {
        if(mx < dp[i])
        {
            mx = dp[i];
            pozmx = i;
        }
    }
    out << mx << "\n";
    int last = (1 << 30);
    for(int i = pozmx; i >= 1; i--)
    {
        if(dp[i] == mx && v[i] < last)
        {
            sol.push_back(aux[i]);
            mx--;
            last = v[i];
        }
    }
    reverse(sol.begin(), sol.end());
    for(auto it : sol)
        out << it << " ";
    out << "\n";
    return 0;
}