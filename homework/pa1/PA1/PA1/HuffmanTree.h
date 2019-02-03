#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "HuffmanInternalNode.h"
#include "HuffmanLeafNode.h"
template <typename T>
class HuffmanTree
{
private:
	HuffmanNode<T> *_root;

public:
	HuffmanTree(const T& value, const int &weight)
	{
		_root = new HuffmanLeafNode<T>(value, weight);
	}

	HuffmanNode<T> *getRoot()
	{
		return _root;
	}

	HuffmanTree(HuffmanTree<T> *left, HuffmanTree<T> *right)
	{
		_root = new HuffmanInternalNode<T>(left->getRoot(), right->getRoot());
	}

	HuffmanTree(HuffmanInternalNode<T> *root)
	{
		_root = root;
	}

	~HuffmanTree()
	{
		vector<HuffmanNode<T> *> nodes{};
		nodes.push_back(_root);
		while (nodes.size() > 0)
		{
			HuffmanNode<T> *last = nodes[nodes.size() - 1];
			nodes.pop_back();
			HuffmanInternalNode<T> *casted_node = dynamic_cast<HuffmanInternalNode<T> *>(last);

			//make sure that we're dealing with an actual
			//binary node
			if (casted_node != nullptr)
			{
				//add last's children to the stack
				nodes.push_back(casted_node->getLeftChild());
				nodes.push_back(casted_node->getRightChild());

				//having gotten all of the information out of
				//last, we can now delete the node
				delete casted_node;
			}
		}
	}

	virtual int getWeight()
	{
		return _root->getWeight();
	}
};

#endif