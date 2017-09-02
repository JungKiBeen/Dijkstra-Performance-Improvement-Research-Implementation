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
		return v1.dist > v2.dist;	// ���� ������ �̴´�
	}
};

vector<priority_queue<vertex, vector<vertex>, Comp> > pq;
vector<vector<pair<int, int> > > adj;	// �׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<int> L;

int v, e, k, q;

// -�����Ϸ��� vertex�� ��ȣ�� ���� � ���̳ʸ� ��(�켱����ť)�� ���ԵǾ� �ϴ��� �� �� �ִ�.

//- vertex number / q�� ���� ���� �Ǿ���� ���̳ʸ� ���� ��ȣ�̴�.

//- 0���� q - 1 ������ vertex ��ȣ�� q�� ������ �� ���� 0�̹Ƿ�, 0��° ���̳ʸ� ���� ����ȴ�.����������, q���� 2q - 1 ������ vertex ��ȣ�� q�� ������ �� ���� 1�̹Ƿ�, 1��° ���̳ʸ� ���� ����ȴ�.

void push(int _dist, int _num)
{
	vertex t;
	t.dist = _dist;	t.number = _num;

	int pq_num = (_num / q) % (k*q);
	pq[pq_num].push(t);
}

//-����, ������� ���� ���̳ʸ� ���� min ���� ��� ���� ���Ѵ�.
//- ���� ���� ���� min_dist, �׿� �ش��ϴ� ���̳ʸ� ���� ��ȣ�� min_idx�� ���Ѵ�.
//- �� ��, min_dist�� min_idx�� ��ȯ�Ͽ� ���� ���� f(v)�� ������ v�� �� �� �ֵ��� �Ѵ�.
//- ���������� ���� ���̳ʸ������� �ش� vertex�� pop(����)�Ѵ�.


bool top(vertex& vtx)
{
	int min_idx = -1;
	int min_dist = INF;

	for (int i = 0; i < k*q; i++)
	{
		if (pq[i].empty()) continue;	// ����ִ� ���̳ʸ� ���� �����Ѵ�.

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
		return false;	// false ��ȯ�� �켱���� ť�� ����ٴ� ���� �ǹ�
	}
}


// empty()�Լ��� ��� ���̳ʸ� ���� empty�� ��� true�� ��ȯ�ϵ��� �����Ͽ���.
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

	vector<int> dist(v, INF);		// dist�� �ִ� ��� ��� �迭�̴�.

	pq.resize(k*q);		// k*q�� �켱���� ť�� ����
	dist[src] = 0;

	push(0, src);

	while (!empty()) {

		vertex t;
		if (top(t) == false)	break;
		int cost = t.dist;
		int here = t.number;

		// ���� ���� ���� �ͺ��� �� ª�� ��θ� �˰� �ִٸ� ���� ���� ���� �����Ѵ�.
		if (dist[here] < cost) continue;

		// ������ �������� ��� �˻��Ѵ�.
		for (int i = 0; i < (int)adj[here].size(); ++i) {

			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			// �� ª�� ��θ� �߰��ϸ�, dist[]�� �����ϰ� �켱���� ť�� �ִ´�.
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

	// 1. ������ ��(v), ������ ��(E), K�� �Է¹ް� L�� �����. RAND �Լ� �̿�

	// 2. �׷����� ���� ����� �ʱ�ȭ �Ѵ�. : INF - ����ȵ�, 0 - i=i, val - �����
	//

	// 
	// 3.  RAND �Լ��� �̿��Ͽ� ������ �Ҵ� �Ѵ�. �߿��� ���� L�� ���� �̿��ؾ� �Ѵٴ� ���̴�.


	srand((unsigned int)time(NULL));

	cout << "�����Ǽ��� �Է� �Ͻÿ� : ";
	cin >> v;

	cout << "�����Ǽ��� �Է� �Ͻÿ� : ";
	cin >> e;


	cout << "���� �ٸ� ���̸� ������ ������ ���� �Է��Ͻÿ� �Է� �Ͻÿ� : ";
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