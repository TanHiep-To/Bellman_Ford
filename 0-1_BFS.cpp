#include <iostream>
#include <queue>
#include <stack>
#include <time.h>

#define MAX_SIZE 100007

using namespace std;

vector<pair<int, int>> adj[MAX_SIZE];
int edge = 0;
int vertex = 0;
bool visited[MAX_SIZE];
int trace[MAX_SIZE];
int weight[MAX_SIZE];

void input()
{
	cin >> vertex >> edge;
	for (int i = 0; i < edge; i++)
	{
		int x, y, s;
		cin >> x >> y >> s;
		adj[x].push_back({ y, s });
		//adj[y].push_back({ x, s });
	}
	for (int i = 0; i < vertex; i++)
	{
		visited[i] = false;
	}
}

void BFS(int start_vertex)
{

	queue <int> q;
	q.push(start_vertex);
	visited[start_vertex] = true;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (auto i = 0; i < adj[v].size(); i++)
		{
			if (visited[adj[v][i].first] == false)
			{
				q.push(adj[v][i].first);
				visited[adj[v][i].first] = true;
				trace[adj[v][i].first] = v;
				weight[v] = adj[v][i].second;
			}

		}

	}
}

void printShortestPath(int start_vertex, int finish_vertex)
{
	int weight_sum = 0;
	stack<int> shortest_trace;
	shortest_trace.push(finish_vertex);

	int j = finish_vertex;
	while (trace[j] != start_vertex)
	{
		shortest_trace.push(trace[j]);
		j = trace[j];
		weight_sum += weight[j];
	}
	shortest_trace.push(start_vertex);
	weight_sum += weight[start_vertex];

	cout << shortest_trace.top();
	shortest_trace.pop();

	while (!shortest_trace.empty())
	{
		cout << " --> " << shortest_trace.top();
		shortest_trace.pop();
	}

	cout << "\nShortest path: " << weight_sum << endl;
	cout << endl;
}

int main()
{


	input();
	int start_vertex = 1;
	int finish_vertex = vertex;

	clock_t s, e;
	double time_use;
	s = clock();

	BFS(start_vertex);
	cout << "\nShortest path from " << start_vertex << " to " << finish_vertex << endl;

	printShortestPath(start_vertex, finish_vertex);
	e = clock();
	time_use = (double)(e - s) / CLOCKS_PER_SEC;
	
	cout << "BFS algorithm runtime is: " << time_use << endl;
	return 0;
}
