#pragma warning(disable : 6262)
#include <iostream>
#include <math.h>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <iterator>
#include <stack>

using namespace std;

const int N = 1e4 + 9;
const int oo = 1e7 + 9;

int weight[N][N];
int trace[N][N];

int n, m;

void Init(int& n, int& m);

void Floyd();

void Paths(int u, int v);

bool negativeCycle(int n);

void traceCycle();

int main()
{
	clock_t start, end;
	double time_use;

	Init(n, m);

	start = clock();

	Floyd();

	bool checkNegative = negativeCycle(n);

	if (!checkNegative)
	{
		cout << "\nShortest Path from 1 --> " << n << " :  ";
		cout << weight[1][n] << '\n';

		cout << "\nPath : ";
		Paths(1, n);
	}
	else
	{
		traceCycle();
	}

	end = clock();
	time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Run time : " << time_use << endl;

	return 0;
}


void Init(int& n, int& m)
{
	cin >> n >> m;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			weight[i][j] = oo;

	for (int i = 1; i < N; i++)
		weight[i][i] = 0;

	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;

		weight[u][v] = w;
		//weight[v][u] = w;

		trace[u][v] = v;
		//trace[v][u] = u;

	}

}

void Floyd()
{

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{

				if (weight[i][j] > weight[i][k] + weight[k][j])
				{
					weight[i][j] = weight[i][k] + weight[k][j];

					trace[i][j] = trace[i][k];
				}
			}

}

void Paths(int u, int v)
{
	int Save[N] = { 0 };

	vector<int> path;
	do {
		path.push_back(u);
		u = trace[u][v];

	} while (path.back() != v);

	for (int u = 0; u < path.size(); u++)
	{
		if (u != path.size() - 1)
			cout << path[u] << " --> ";

		else cout << path[u] << "\n\n";
	}

}

bool negativeCycle(int n)
{
	bool checkNegative = false;

	for (int i = 1; i <= n; ++i)
		if (weight[i][i] < 0)
			checkNegative = true;

	return checkNegative;
}


void traceCycle()
{
	bool checkCycle = negativeCycle(n);

	if (!checkCycle)
	{
		cout << "NO NEGATIVE CYCLE FOUND.\n";
		return;
	}

	cout << "GRAPH HAS NEGATIVE CYCLE .\n";


}
