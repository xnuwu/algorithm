#pragma once
#include "List.h"
#include "Vector.h"
#include "Graph.h"

template <typename Tv, typename Te>
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
	List<Edge<Te>*> edgePtrList;
	Vertex(Tv const& d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX), edgePtrList(List<Edge<Te>*>()) {}
};

template <typename Te>
class Edge {
public:
	Te data;
	int weight;
	EStatus status;
	int vertexIndex;
	Edge(Te const& d, int v, int w) : data(d), vertexIndex(-1), weight(w), status(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class AdjListMatrix : public Graph<Tv, Te> {
private:
	Vector<Vertex<Tv, Te>> V;

public:
	AdjListMatrix() { this->n = this->e = 0; }

	virtual ~AdjListMatrix() {
		for (int i = 0; i < this->n; i++) {
			while (!V[i].edgePtrList.empty())
			{
				delete V[i].edgePtrList.remove(V[i].edgePtrList.first());
			}
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
		this->n++;
		Vertex<Tv, Te> vertex(data);
		return V.insert(vertex);
	}

	virtual Tv remove(int i) {
		while (!V[i].edgePtrList.empty()) {
			delete V[i].edgePtrList.remove(V[i].edgePtrList.first());
		}
		this->n--;
		for (int j = 0; j < this->n; j++) {
			if (!V[j].edgePtrList.empty()) {
				Edge<Te>* edgePtr = V[j].edgePtrList.first();
				while (edgePtr->succ != nullptr) {
					if (edgePtr->vertexIndex == i) {
						delete V[j].edgePtrList.remove(edgePtr);
						V[j].inDegree--;
						this->e--;
					}
					else {
						edgePtr = edgePtr->succ;
					}
				}
			}
		}

		Tv data = vertex(i);
		V.remove(i);
		return data;
	}

	/************************************ 边的操作 ************************************/

	virtual bool exists(int i, int j) {
		if (!V[i].edgePtrList.empty()) {
			Edge<Te>* edgePtr = V[i].edgePtrList.first();
			while (edgePtr -> succ != nullptr) {
				if (edgePtr->vertexIndex == j) {
					return true;
				}
				else {
					edgePtr = edgePtr->succ;
				}
			}
		}

		return false;
	}

	virtual EStatus& status(int i, int j) {
		return E[i][j]->status;
	}

	virtual Te& edge(int i, int j) {
		return E[i][j]->data;
	}

	virtual int& weight(int i, int j) {
		return E[i][j]->weight;
	}

	virtual void insert(Te const& edge, int w, int i, int j) {
		if (exists(i, j)) return;
		E[i][j] = new Edge<Te>(edge, w);
		this->e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}

	virtual Te remove(int i, int j) {
		Te data = edge(i, j);
		delete E[i][j];
		E[i][j] = nullptr;
		V[i].outDegree--;
		V[j].inDegree--;
		this->e--;
		return data;
	}
};