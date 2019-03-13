#pragma once
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <unordered_map>
#include <string>
using namespace std;
class TreeNode
{
public:
   unordered_map<string, TreeNode*> children;
   string value;
};

#endif // !TREE_NODE_H
