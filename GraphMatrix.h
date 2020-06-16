#pragma once
#include "Vector.h"
#include "Graph.h"

template <typename Tv> 
class Vertix {
public:
	Tv data;
	int inDegree;
	int outDegree;
	VStatus status;
	int dTime;
	int fTime;
	int parent;
	int priority;
	Vertix(Tv const& d = (Tv)0 ) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te> 
class Edge {
public:
	Te data;
	int weight;
	EStatus status;
	Edge(Te const& d, int w) : data(d), weight(w), status(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {

};