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



vector<vector<pair<int, int> > > adj;	// �׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<int> L;

int v, e, k, q;

/*
- �� �ݺ��ø��� T ���͸� ������ �� ���� ���� f(v)�� ������ ������ ������.
- �ش� ������ ������ �������� �����Ͽ�, �� ª�� ��θ� �߰��� �� �ִ��� Ȯ���ϰ� �׷��ٸ� �ִܰ�θ� �����Ѵ�.
- ����, �� ������ T ���Ϳ� �����Ѵ�.

*/
vector<int> dijkstra(int src) {

	vector<int> dist(v, INF);
	vector <pair<int, int> > t;	// first : dist, second : num

	dist[src] = 0;
	t.push_back(make_pair(src, 0));


	while (!t.empty()) {

		sort(t.begin(), t.end());	// t[0]�� ���� ���� ��
		int cost = t[0].first;
		int here = t[0].second;

		t.erase(t.begin() + 0);

		// ���� ���� ���� �ͺ��� �� ª�� ��θ� �˰� �ִٸ� ���� ���� ���� �����Ѵ�.
		if (dist[here] < cost) continue;

		// ������ �������� ��� �˻��Ѵ�.
		for (int i = 0; i < (int)adj[here].size(); ++i) {

			int there = adj[here][i].first;		// ���� ��ȣ
			int nextDist = cost + adj[here][i].second;
			// �� ª�� ��θ� �߰��ϸ�, dist[]�� �����ϰ� �켱���� ť�� �ִ´�.
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