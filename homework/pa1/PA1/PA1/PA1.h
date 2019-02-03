#ifndef PA_1_H
#define PA_1_H

#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_map>
#include "BinaryFile.h"
#include "StringSplitter.h"


using namespace std;

class TreeComparer
{
public:
    bool operator()(HuffmanTree<char> * first, HuffmanTree<char> * second)
    {
        return first->getWeight() > second->getWeight();
    }
};

class PA1
{
public:


	//PA #1 TOOD: Generates a Huffman character tree from the supplied text
	static HuffmanTree<char> *huffmanTreeFromText(vector<string> data);

	//PA #1 TODO: Generates a Huffman character tree from the supplied encoding map
	//NOTE: I used a recursive helper function to solve this!
	static HuffmanTree<char> *huffmanTreeFromMap(unordered_map<char, string> huffmanMap);

	//PA #1 TODO: Generates a Huffman encoding map from the supplied Huffman tree
	//NOTE: I used a recursive helper function to solve this!
	static unordered_map<char, string> huffmanEncodingMapFromTree(HuffmanTree<char> *tree);

	//PA #1 TODO: Writes an encoding map to file.  Needed for decompression.
	static void writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name);

	//PA #1 TODO: Reads an encoding map from a file.  Needed for decompression.
	static unordered_map<char, string> readEncodingMapFromFile(string file_name);

	//PA #1 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
	static string decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap);

	//PA #1 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
	static vector<bool> toBinary(vector<string> text, unordered_map<char, string> huffmanMap);

};

#endif
