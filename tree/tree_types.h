#pragma once

#include <cstddef>

// types of binary tree

struct TreeNode {
	TreeNode(int val)
		: val(val)
		, left(nullptr)
		, right(nullptr) {}
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct AvlTreeNode {
	AvlTreeNode(int val)
		: val(val)
		, left(nullptr)
		, right(nullptr)
		, height(0) {}
	int val;
	struct AvlTreeNode *left;
	struct AvlTreeNode *right;
	int height;
};

enum Color {
	RED = 0,
	BLACK
};

struct RbTreeNode {
	RbTreeNode(int val)
		: val(val)
		, left(nullptr)
		, right(nullptr)
		, parent(nullptr)
		, color(RED) {}
	int val;
	struct RbTreeNode *left;
	struct RbTreeNode *right;
	struct RbTreeNode *parent;
	Color color;
};


typedef struct TreeNode Tree;
typedef struct TreeNode Node;

typedef struct AvlTreeNode AvlTree;
typedef struct AvlTreeNode AvlNode;

typedef struct RbTreeNode RbTree;
typedef struct RbTreeNode RbNode;
