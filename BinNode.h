#pragma once
#define BinNodePosi(T) BinNode<T>* 

template <typename T>
class BinNode {
public:
	BinNodePosi(T) parent, lChild, rChild;
	T data;
	int height;
	int size();

	BinNodePosi(T) insertAsLc(T const& e);
	BinNodePosi(T) insertAsRc(T const& e);
	
	//当前节点的直接后继(中序遍历)
	BinNodePosi(T) succ();

	//子树层级遍历
	template <typename VST> void travLevel(VST&);

	//子树先序遍历
	template <typename VST> void travPre(VST&);
	
	//子树中序遍历
	template <typename VST> void travIn(VST&);
	
	//子树后序遍历
	template <typename VST> void travPost(VST&);
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLc(T const& e) {
	return lChild = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(T const& e) {
	return rChild = new BinNode(e, this);
}

template <typename T>
int BinNode<T>::size() {
	int s = 1;
	if (lChild) {
		s += lChild->size();
	}

	if (rChild) {
		s += rChild->size();
	}

	return s;
}