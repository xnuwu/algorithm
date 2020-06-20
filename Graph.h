#pragma once
#include "Stack.h"
#include "Queue.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;


typedef enum {
	UNDETERMINED,	//待定边
	TREE,			//树边
	CROSS,			//跨边,
	FORWARD,		//向前边,父节点访问子节点, eg e(u,v) dTime(u) < dTime(v)
	BACKWARD		//向后边,子节点访问父节点, eg e(u,v) dTime(u) > dTime(v)
} EStatus;

template <typename Tv, typename Te>
class Graph {
private:
	void reset() {
		for (int i = 0; i < n; i++) {
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++) {
				if (exists(i, j)) {
					status(i, j) = UNDETERMINED;
				}
			}
		}
	}

	void BFS(int, int&);
	void DFS(int, int&);
	void BCC(int, int&, Stack<int>&);
	bool TSort(int, int&, Stack<Tv>*);

	template <typename PU> void PFS(int, PU);

public:

	//顶点
	int n;
	virtual int insert(Tv const&) = 0;
	virtual Tv remove(int) = 0;
	virtual Tv& vertex(int) = 0;
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;
	virtual int nextNbr(int, int) = 0;
	virtual VStatus& status(int) = 0;
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;

	//边
	int e;
	virtual bool exists(int, int) = 0;
	virtual void insert(Te const&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EStatus& status(int, int) = 0;
	virtual Te& edge(int, int) = 0;
	virtual int& weight(int, int) = 0;

	//算法algorithm
	void bfs(int);
	void dfs(int);
	void bcc(int);
	Stack<Tv>* tSort(int);
	void prim(int);
	void dijkstra(int);

	template<typename PU> void pfs(int, PU);
};

/************************************ 广度优先遍历 ************************************/
template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
	Queue<int> queue;
	queue.enqueue(v);
	status(v) = DISCOVERED;
	while (!queue.empty()) {
		v = queue.dequeue();
		dTime(v) = ++clock;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
			switch (status(u))
			{
			case UNDISCOVERED:
				status(u) = DISCOVERED;
				status(v, u) = TREE;
				parent(u) = v;
				queue.enqueue(u);
				break;

			default:
				status(v, u) = CROSS;
				break;
			}
		}
	
		std::cout << "visited " << vertex(v) << " at " << clock << std::endl;
		status(v) = VISITED;
	}
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
	reset();
	int clock = 0;
	int v = s;
	do {
		
		while (status(v) == UNDISCOVERED)
		{
			BFS(v, clock);
		}
	} while (s != (v = (++v % n)));
}
