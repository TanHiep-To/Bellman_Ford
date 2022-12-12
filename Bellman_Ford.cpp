#include <stdio.h>
#include <queue>
#include <math.h>
#include <algorithm>
#include <iostream>
#include<ctime>

using namespace std;

#define X first
#define Y second
const int N = 1e5 + 7;
typedef pair<int, int> ii;
vector<ii> a[N];
int n, m;

int d[N];
bool P[N] = { false };

int trace[N];

void bellman(int u) {
    queue<int> qu;

    for (int i = 1; i <= n; i++)
        d[i] = 1e5 + 7;
    d[u] = 0;
    qu.push(u);
    P[u] = true;
    int cnt = 0;

    while (qu.size()) {
        u = qu.front();
        P[u] = false;
        qu.pop();
        cnt++;
        if (cnt == n) break;

        for (int i = 0; i < a[u].size(); i++) {
            int v = a[u][i].Y;
            int uv = a[u][i].X;
            if (d[v] > d[u] + uv) {
                d[v] = d[u] + uv;
                trace[v] = u;

                if (!P[v]) {

                    qu.push(v);
                    P[v] = true;
                }
            }
        }
    }
}

void Path(int u, int v)
{
    if (d[v] == 1e5 + 7)
    {
        cout << "No path from " << u << " to  " << v << '\n';
        return;
    }

    vector<int>path;

    for (int i = v; i != u; i = trace[i])
        path.emplace_back(i);

    path.emplace_back(u);

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        if (i < path.size() - 1)
            cout << path[i] << " -> ";
        else cout << path[i] << '\n';
    }

}

bool negativeCyclePath()
{
    vector<int> d(n + 1);
    vector<int> p(n + 1, -1);
    int x;
    for (int u = 1; u <= n; ++u) {
        x = -1;
        for (int i = 0; i < a[u].size(); i++)
        {
            int v = a[u][i].Y;
            int uv = a[u][i].X;

            if (d[v] > d[u] + uv)
            {
                d[v] = d[u] + uv;
                p[v] = u;
                x = v;
            }
        }
    }


    if (x == -1) {
        return false;
    }
    else {
        for (int i = 0; i < n; ++i)
            x = p[x];

        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());

        cout << "Negative cycle: ";
        for (int v = 0; v < cycle.size(); v++)
        {
            if (v < cycle.size() - 1)
                cout << cycle[v] << " -> ";
            else cout << cycle[v] << '\n';
        }

    }
    return true;
}

int main() {
    int u, v;
    cin >> n >> m >> u >> v;

    clock_t start, end;
    double time_use;

    while (m--) {
        int p, q, w;
        cin >> p >> q >> w;

        a[p].push_back(ii(w, q));
    }

    start = clock();
    bool check = negativeCyclePath();
    if (!check) {
        bellman(u);
        Path(u, v);
        cout << "Distance : " << d[v];
    }

    end = clock();  
    time_use = (double)(end - start) / CLOCKS_PER_SEC;   
    cout << "\nRun time : " << time_use << endl;
}
/*
4 4 1 4
1 2 -3
2 4 -4
3 1 1
4 1 1

4 5 1 4
1 2 -1
2 3 4
3 4 -2
2 4 3
4 1 2
*/
