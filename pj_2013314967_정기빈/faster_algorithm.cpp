#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <ctime>
using namespace std;
#define INF INT_MAX

struct vertex
{
public:
	int dist;
	int number;

};

struct Comp
{
	bool operator()(vertex v1, vertex v2)
	{
		return v1.dist > v2.dist;	// 낮은 순으로 뽑는다
	}
};

vector<priority_queue<vertex, vector<vertex>, Comp> > pq;
vector<vector<pair<int, int> > > adj;	// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<int> L;

int v, e, k, q;

// -삽입하려는 vertex의 번호를 통해 어떤 바이너리 힙(우선순위큐)에 삽입되야 하는지 알 수 있다.

//- vertex number / q의 몫이 삽입 되어야할 바이너리 힙의 번호이다.

//- 0부터 q - 1 까지의 vertex 번호는 q로 나눴을 때 몫이 0이므로, 0번째 바이너리 힙에 저장된다.마찬가지로, q부터 2q - 1 까지의 vertex 번호는 q로 나눴을 때 몫이 1이므로, 1번째 바이너리 힙에 저장된다.

void push(int _dist, int _num)
{
	vertex t;
	t.dist = _dist;	t.number = _num;

	int pq_num = (_num / q) % (k*q);
	pq[pq_num].push(t);
}

//-먼저, 비어있지 않은 바이너리 힙의 min 값을 모두 꺼내 비교한다.
//- 가장 작은 값을 min_dist, 그에 해당하는 바이너리 힙의 번호를 min_idx로 정한다.
//- 그 후, min_dist와 min_idx를 반환하여 가장 작은 f(v)를 가지는 v를 알 수 있도록 한다.
//- 마지막으로 꺼낸 바이너리힙에서 해당 vertex를 pop(삭제)한다.


bool top(vertex& vtx)
{
	int min_idx = -1;
	int min_dist = INF;

	for (int i = 0; i < k*q; i++)
	{
		if (pq[i].empty()) continue;	// 비어있는 바이너리 힙은 제외한다.

		int dist = (pq[i].top()).dist;
		if (min_dist > dist)
		{
			min_dist = dist;
			min_idx = i;
		}
	}

	if (min_idx != -1)
	{
		vtx = pq[min_idx].top();
		pq[min_idx].pop();

		return true;
	}

	else
	{
		return false;	// false 반환은 우선순위 큐가 비었다는 것을 의미
	}
}


// empty()함수는 모든 바이너리 힙이 empty일 경우 true를 반환하도록 구현하였다.
bool empty()
{
	for (int i = 0; i < k*q; i++)
	{
		if (!(pq[i].empty()))
			return false;
	}

	return true;
}

vector<int> dijkstra(int src) {

	vector<int> dist(v, INF);		// dist는 최단 경로 비용 배열이다.

	pq.resize(k*q);		// k*q는 우선순위 큐의 개수
	dist[src] = 0;

	push(0, src);

	while (!empty()) {

		vertex t;
		if (top(t) == false)	break;
		int cost = t.dist;
		int here = t.number;

		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
		if (dist[here] < cost) continue;

		// 인접한 정점들을 모두 검사한다.
		for (int i = 0; i < (int)adj[here].size(); ++i) {

			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				push(nextDist, there);
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
	if (q <= 2)
	{
		q = 2;
	}

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

	cout << "faster algorithm > " << (end - start).count() << " ns" << endl;

	return 0;
}