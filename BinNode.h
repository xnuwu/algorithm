#pragma once
#define BinNodePosi(T) BinNode<T>* 
#define stature(p) ((p) ? (p)->height, -1)
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && ((&x) == (x).parent -> lChild))
#define IsRChild(x) (!IsRoot(x) && ((&x) == (x).parent -> rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(p) ? (p) -> parent -> rChild : (p) -> parent -> lChild)
#define uncle(p) (*(IsLChild(p -> parent)) ? (p) -> parent -> parent -> rChild : (p) -> parent -> parent -> lChild)
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent -> lChild : (x).parent -> rChild ))

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
class BinNode {
public:
	BinNodePosi(T) parent, lChild, rChild;
	T data;
	int height;
	int size();

	BinNodePosi(T) insertAsLc(T const& e);
	BinNodePosi(T) insertAsRc(T const& e);

	BinNode() : height(0), parent(nullptr), lChild(nullptr), rChild(nullptr) {};
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) l = nullptr, BinNodePosi(T) r = nullptr, int h = 0) : data(e), parent(p), lChild(l), rChild(r), height(h) {};

	//��ǰ�ڵ��ֱ�Ӻ��(�������)
	BinNodePosi(T) succ();

	//�����㼶����
	template <typename VST> void travLevel(VST&);

	//�����������
	template <typename VST> void travPre(VST&);
	
	//�����������
	template <typename VST> void travIn(VST&);
	
	//�����������
	template <typename VST> void travPost(VST&);

	//�Ƚ������е���
	bool operator<(BinNode const& bn) {
		return data < bn.data;
	}

	bool operator=(BinNode const& bn) {
		return data == bn.data;
	}
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