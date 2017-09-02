#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
#define INF INT_MAX



vector<vector<pair<int, int> > > adj;	// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<int> L;

int v, e, k, q;

/*
- 매 반복시마다 T 벡터를 정렬한 후 가장 작은 f(v)를 가지는 정점을 꺼낸다.
- 해당 정점과 인접한 정점들을 조사하여, 더 짧은 경로를 발견할 수 있는지 확인하고 그렇다면 최단경로를 갱신한다.
- 또한, 그 정점을 T 벡터에 삽입한다.

*/
vector<int> dijkstra(int src) {

	vector<int> dist(v, INF);
	vector <pair<int, int> > t;	// first : dist, second : num

	dist[src] = 0;
	t.push_back(make_pair(src, 0));


	while (!t.empty()) {

		sort(t.begin(), t.end());	// t[0]은 가장 작은 값
		int cost = t[0].first;
		int here = t[0].second;

		t.erase(t.begin() + 0);

		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
		if (dist[here] < cost) continue;

		// 인접한 정점들을 모두 검사한다.
		for (int i = 0; i < (int)adj[here].size(); ++i) {

			int there = adj[here][i].first;		// 정점 번호
			int nextDist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				t.push_back(make_pair(nextDist, there));
			}

		}
	}

	return dist;
}

int main(void)
{

	// 1. 정점의 수(v), 간선의 수(E), K를 입력받고 L을 만든다. RAND 함수 이용

	// 2. 그래프의 인접 행렬을 초기화 한다. : INF - 연결안됨, 0 - i=i, val - 연결됨
	//

	// 
	// 3.  RAND 함수를 이용하여 간선을 할당 한다. 중요한 것은 L의 값을 이용해야 한다는 것이다.


	srand((unsigned int)time(NULL));

	cout << "정점의수를 입력 하시오 : ";
	cin >> v;

	cout << "간선의수를 입력 하시오 : ";
	cin >> e;


	cout << "서로 다른 길이를 가지는 간선의 수를 입력하시오 입력 하시오 : ";
	cin >> k;

	q = (v*k) / e;

	L.reserve(k);
	for (int i = 0; i < k; i++)
	{
		L.push_back((rand() + 1) % INF);
	}

	adj.resize(v);

	int t = e;

	for (int i = 0; i < v - 1; i++)
	{
		int cnt = e / v;

		for (int j = 0; j < cnt; j++)
		{
			adj[i].push_back(make_pair(j, L[rand() % k]));
		}
		t -= cnt;
	}

	int tt = t;
	for (int j = 0; j < tt; j++)
	{
		adj[v - 1].push_back(make_pair(j, L[rand() % k]));
		t--;
	}

	if (t != 0) return 0;

	
	auto start = chrono::high_resolution_clock::now();

	dijkstra(0);

	auto end = chrono::high_resolution_clock::now();

	cout << "slower algorithm > " << (end - start).count() << " ns" << endl;
	return 0;
}