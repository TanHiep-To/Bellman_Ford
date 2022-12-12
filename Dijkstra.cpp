#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <queue>
#include <time.h>

using namespace std;
const int N = 1e5 + 7;
const int oo = 1e9 + 7;

typedef pair<int, int> ii;
vector<ii> adj[N];

int weigth[N];
int trace[N];

int n, m;

void Init(int& n, int& m, vector<ii> a[]);
void dijkstra(int x, vector<ii> a[]);
void restorePath(int s, int t);


int main()
{
	Init(n, m, adj);
	dijkstra(1, adj);

	clock_t s, e;
	double time_use;
	s = clock();

	cout << "Shortest Path from 1 --> " << n << " :  ";
	cout << weigth[n] << '\n';

	cout << "Path : ";
	restorePath(1, n);

	e = clock();
	time_use = (double)(e - s) / CLOCKS_PER_SEC;

	cout << "Dijkstra algorithm runtime is: " << time_use << endl;

	return 0;
}

void Init(int& n, int& m, vector<ii> a[])
{
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		a[u].emplace_back(make_pair(v, w));
		//a[v].emplace_back(make_pair(u, w));

	}
}

void dijkstra(int x, vector<ii> a[])
{
	for (int i = 1; i <= n; ++i)
		weigth[i] = oo;

	weigth[x] = 0;

	priority_queue<ii, vector<ii>, greater<ii>> q;

	q.push(make_pair(x, 0));

	while (!q.empty())
	{
		pair<int, int> X = q.top();
		q.pop();

		int u = X.first;
		int du = X.second;

		if (du != weigth[u]) continue;

		for (int i = 0; i < a[u].size(); i++)
		{
			int v = a[u][i].first;
			int uv = a[u][i].second;

			if (weigth[v] > du + uv)
			{
				weigth[v] = du + uv;
				trace[v] = u;
				q.push(make_pair(v, weigth[v]));
			}
		}
	}
}

void restorePath(int s, int t)
{
	vector<int> path;

	for (int v = t; v != s; v = trace[v])
		path.emplace_back(v);

	path.emplace_back(s);

	reverse(path.begin(), path.end());

	for (int u = 0; u < path.size(); u++)
	{
		if (u == path.size() - 1)
			cout << path[u] << "\n\n";
		else cout << path[u] << " --> ";
	}
}
