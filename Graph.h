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

template <typename Tv, typename Te> 
void Graph<Tv, Te>::DFS(int v, int& clock) {
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			status(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
		default:
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
	std::cout << "VISITED " << vertex(v) << " at " << dTime(v) << std::endl;
}

#define hca(x) (fTime(x))
template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& stack)
{
	dTime(v) = hca(v) = ++clock;
	status(v) = DISCOVERED;
	std::cout << "DISCOVERED " << vertex(v) << std::endl;
	stack.push(v);
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			parent(u) = v;
			status(v, u) = TREE;
			BCC(u, clock, stack);
			if (hca(u) < dTime(v)) {
				hca(v) = hca(u) < hca(v) ? hca(u) : hca(v);
			}
			else {
				while (v != stack.pop());
				stack.push(v);
				std::cout << "FIND BCC VERTEX " << vertex(v) << std::endl;
			}
			break;
		case DISCOVERED:
			status(v, u) = BACKWARD;
			if (u != parent(v)) {
				hca(v) = hca(v) < dTime(u) ? hca(v) : dTime(u); 
			}
			break;
		default:
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
}

#undef hca

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
	int v = s;
	int clock = 0;
	do {
		if (status(v) == UNDISCOVERED) {
			DFS(v, clock);
		}
	} while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s)
{
	int v = s;
	int clock = 0;
	Stack<int> stack;
	do {
		if (status(v) == UNDISCOVERED) {
			BCC(s, clock, stack);
			stack.pop();
		}
	} while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
	reset();
	int v = s;
	int clock = 0;
	Stack<Tv>* stackPtr = new Stack<Tv>;
	do {
		if (status(v) == UNDISCOVERED) {
			if (!TSort(v, clock, stackPtr)) {
				while (!stackPtr-> empty())
				{
					stackPtr->pop();
				}
				break;
			}
		}
	} while (s != (v = (++v % n)));

	return stackPtr;
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* s) {
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			status(v, u) = TREE;
			parent(u) = v;
			if (!TSort(u, clock, s)) {
				return false;
			}
			break;

		case DISCOVERED:
			status(v, u) = BACKWARD;	//环路
			return false;

		default:
			status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}
	}

	fTime(v) = ++clock;
	status(v) = VISITED;
	s->push(vertex(v));
	return true;
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU priorityUpdator) {
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	std::cout << "PFS VISITED " << vertex(s) << std::endl;
	while (true)
	{
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w)) {
			priorityUpdator(this, s, w);
		}
		for (int shortest = INT_MAX, w = 0; w < n; w++) {
			if (status(w) == UNDISCOVERED) {
				if (shortest > priority(w)) {
					shortest = priority(w);
					s = w;
				}
			}
		}
		if (status(s) == VISITED) {
			break;
		}
		status(s) = VISITED;
		status(parent(s), s) = TREE;
		std::cout << "PFS VISITED " << vertex(s) << std::endl;
	}
}

template<typename Tv, typename Te> 
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU priorityUpdator) {
	reset();
	int v = s;
	do {
		if (UNDISCOVERED == status(v)) {
			PFS(v, priorityUpdator);
		}
	} while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
class DfsPu {
public:
	virtual void operator()(Graph<Tv, Te>* graphPtr, int s, int v) {
		if (graphPtr->status(v) == UNDISCOVERED) {
			if (graphPtr->priority(v) > graphPtr->priority(s) - 1) {
				graphPtr->priority(v) = graphPtr->priority(s) - 1;
				graphPtr->parent(v) = s;
				return;
			}
		}
	}
};

template <typename Tv, typename Te>
class BfsPu {
public:
	virtual void operator()(Graph<Tv, Te>* graphPtr, int s, int v) {
		if (graphPtr->status(v) == UNDISCOVERED) {
			if (graphPtr->priority(s) + 1 < graphPtr->priority(v)) {
				graphPtr->priority(v) = graphPtr->priority(s) + 1;
				graphPtr->parent(v) = s;
			}
		}
	}
};

template<typename Tv, typename Te> 
class PrimUpdator {
public:
	virtual void operator()(Graph<Tv, Te>* graphPtr, int s, int v) {
		if (graphPtr->status(v) == UNDISCOVERED) {
			if (graphPtr->priority(v) > graphPtr->weight(s, v)) {
				graphPtr->priority(v) = graphPtr->weight(s, v);
				graphPtr->parent(v) = s;
			}
		}
	}
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s)
{
	PrimUpdator<Tv, Te> primUpdator;
	pfs(s, primUpdator);
}


template<typename Tv, typename Te>
class DijstraUpdator {
public:
	virtual void operator()(Graph<Tv, Te>* graphPtr, int s, int v) {
		if (graphPtr->status(v) == UNDISCOVERED) {
			if (graphPtr->priority(v) > graphPtr->priority(s) + graphPtr->weight(s, v)) {
				graphPtr->priority(v) = graphPtr->priority(s) + graphPtr->weight(s, v);
				graphPtr->parent(v) = s;
			}
		}
	}
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s)
{
	DijstraUpdator<Tv, Te> dijstraUpdator;
	pfs(s, dijstraUpdator);
}