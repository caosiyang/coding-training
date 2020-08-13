#pragma once

#include "tree_types.h"
#include "binary_tree.h"

template <typename TreeType = Tree, typename NodeType = Node>
class BinarySearchTree : public BinaryTree<TreeType, NodeType> {
public:
	BinarySearchTree() = default;
	virtual ~BinarySearchTree() = default;

	virtual TreeType* Insert(int val);
	virtual TreeType* Delete(int val);
	virtual NodeType* Find(int val) const;
	virtual NodeType* FindMin(TreeType *t) const;
	virtual NodeType* FindMax(TreeType *t) const;

private:
	TreeType* insert(TreeType *t, int val);
	TreeType* remove(TreeType *t, int val);
	NodeType* find(TreeType *t, int val) const;
};
