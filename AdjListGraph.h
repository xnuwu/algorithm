#pragma once
#include "List.h"
#include "Vector.h"
#include "Graph.h"

template <typename Tv>
class Vertex {
public:
	Tv data;
	int inDegree;
	int outDegree;
	VStatus status;
	int dTime;
	int fTime;
	int parent;
	int priority;
	Vertex(Tv const& d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te>
class Edge {
public:
	Te data;
	int weight;
	EStatus status;
	int dest;
	Edge(Te const& d, int dest, int w) : data(d), dest(dest), weight(w), status(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class AdjListGraph : public Graph<Tv, Te> {
private:
	Vector<Vertex<Tv>> V;
	Vector<List<Edge<Te>*>*> E;

public:
	AdjListGraph() {
		this->n = this->e = 0;
	}

	virtual ~AdjListGraph() {
		for (int i = this -> n - 1; 0 <= i; i--) {
			while (!(E[i]->empty()))
			{
				delete (E[i]->remove(E[i]->first()));
			}
			List<Edge<Te>*>* ptr = E.remove(i);
			delete ptr;
		}
	}

	/************************************ 顶点的操作 ************************************/

	virtual Tv& vertex(int i) {
		return V[i].data;
	}

	virtual int inDegree(int i) {
		return V[i].inDegree;
	}

	virtual int outDegree(int i) {
		return V[i].outDegree;
	}

	virtual int firstNbr(int i) {
		return nextNbr(i, this->n);
	}

	virtual int nextNbr(int i, int j) {
		while (-1 < j && !exists(i, --j));
		return j;
	}

	virtual VStatus& status(int i) {
		return V[i].status;
	}

	virtual int& priority(int i) {
		return V[i].priority;
	}

	virtual int& parent(int i) {
		return V[i].parent;
	}

	virtual int& dTime(int i) {
		return V[i].dTime;
	}

	virtual int& fTime(int i) {
		return V[i].fTime;
	}

	virtual int insert(Tv const& data) {
		List<Edge<Te>*>* edgePtrList = new List<Edge<Te>*>;
		E.insert(edgePtrList);
		this->n++;
		Vertex<Tv> vertex(data);
		return V.insert(vertex);
	}

	virtual Tv remove(int i) {
		while (!E.empty() && !(E[i]->empty())) {
			delete E[i]->remove(E[i]->first());
		}
		delete E.remove(i);
		this->n--;
		for (int j = 0; j < this->n; j++) {
			if (E[j] && !(E[j]->empty())) {
				ListNodePos(Edge<Te>*) nodePtr = E[j]->first();
				while (nodePtr->succ != nullptr) {
					if (nodePtr->data->dest == i) {
						delete E[j]->remove(nodePtr);
						V[j].inDegree--;
						this->e--;
						break;
					}
					nodePtr = nodePtr->succ;
				}
			}
		}

		Tv data = vertex(i);
		V.remove(i);
		return data;
	}

	/************************************ 边的操作 ************************************/

	ListNodePos(Edge<Te>*) getEdgeNodePtr(int i, int j) {
		if (!E.empty() && E[i] && !(E[i]->empty())) {
			ListNodePos(Edge<Te>*) nodePtr = E[i]->first();
			while (nodePtr->succ != nullptr) {
				if (nodePtr->data->dest == j) {
					return nodePtr;
				}
				nodePtr = nodePtr->succ;
			}
		}

		return nullptr;
	}

	virtual bool exists(int i, int j) {
		return ((0 <= i) && (i < this->n) && (0 <= j) && (j < this->n)) && getEdgeNodePtr(i, j) != nullptr;
	}

	virtual EStatus& status(int i, int j) {
		ListNodePos(Edge<Te>*) nodePtr = getEdgeNodePtr(i, j);
		return nodePtr->data->status;
	}

	virtual Te& edge(int i, int j) {
		ListNodePos(Edge<Te>*) nodePtr = getEdgeNodePtr(i, j);
		return nodePtr->data->data;
	}

	virtual int& weight(int i, int j) {
		ListNodePos(Edge<Te>*) nodePtr = getEdgeNodePtr(i, j);
		return nodePtr->data->weight;
	}

	virtual void insert(Te const& edge, int w, int i, int j) {
		if (exists(i, j)) return;
		Edge<Te>* edgePtr = new Edge<Te>(edge, j, w);
		this->e++;
		E[i]->insertAsLast(edgePtr);
		V[i].outDegree++;
		V[j].inDegree++;
	}

	virtual Te remove(int i, int j) {
		ListNodePos(Edge<Te>*) nodePtr = getEdgeNodePtr(i, j);
		Te data = nodePtr->data->data;
		delete E[i]->remove(nodePtr);
		V[i].outDegree--;
		V[j].inDegree--;
		this->e--;
		return data;
	}
};