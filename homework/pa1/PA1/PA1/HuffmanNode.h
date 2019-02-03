#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

template <typename T>
class HuffmanNode {
protected:
	int _weight;
public:
    HuffmanNode()
    {

    }

	//gets weight of huffman node and children
	virtual int getWeight()
	{
		return _weight;
	}

	//determines if node is a leaf or not
	virtual bool isLeaf() = 0;
};

#endif
