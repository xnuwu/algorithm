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