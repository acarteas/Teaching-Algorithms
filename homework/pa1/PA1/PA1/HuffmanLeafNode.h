#ifndef HUFFMAN_LEAF_NODE
#define HUFFMAN_LEAF_NODE

//leaf nodes in Huffman trees have the values
#include "HuffmanNode.h"
template <typename T>
class HuffmanLeafNode : public HuffmanNode<T>
{
private:
	T _value;
public:
	HuffmanLeafNode(const T &value, const int &frequency) : HuffmanNode<T>()
	{
		_value = value;
        HuffmanNode<T>::_weight = frequency;
	}

	const T &getValue()
	{
		return _value;
	}

	virtual bool isLeaf()
	{
		return true;
	}
};

#endif
