#pragma once

typedef int Rank;
#define ListNodePos(T) ListNode<T>*

template <typename T>
class ListNode
{
public:
	T data;
	ListNodePos(T) pred;
	ListNodePos(T) succ;

	ListNode() {}
	ListNode(T e, ListNodePos(T) pred = nullptr, ListNodePos(T) succ = nullptr) : data(e), pred(pred), succ(succ) {}
	ListNodePos(T) insertAsPred(T const& e);
	ListNodePos(T) insertAsSucc(T const& e);
};

template<typename T>
ListNodePos(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePos(T) node = new ListNode(e, pred, this);
	pred->succ = node;
	pred = node;
	return node;
}

template <typename T>
ListNodePos(T) ListNode<T>::insertAsSucc(T const& e) {
	ListNodePos(T) node = new ListNode(e, this, succ);
	succ->pred = node;
	succ = node;
	return node;
}
