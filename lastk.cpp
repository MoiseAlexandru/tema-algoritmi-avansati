#include <iostream>
#include <queue>
using namespace std;
priority_queue <int> pq;
int main()
{
    int n, k, A, B, C, D;
    cin >> n >> k >> A >> B >> C >> D;
    int curent = A;
    for(int i = 1; i <= n; i++)
    {
        pq.push(-curent);
        if(pq.size() > k)
            pq.pop();
        curent = (1LL * B * curent + C) % D;
    }
    while(!pq.empty())
    {
        cout << -pq.top() << " ";
        pq.pop();
    }
    cout << "\n";
    return 0;
}