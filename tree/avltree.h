#pragma once

#include "bstree.hpp"

class AVLTree : public BinarySearchTree<AvlTree, AvlNode> {
public:
	AVLTree() = default;
	virtual ~AVLTree() = default;

	virtual AvlTree* Insert(int val);
	virtual AvlTree* Delete(int val);

	virtual int Height(AvlTree *t) const;

private:
	AvlTree* insert(AvlTree *t, int val);
	AvlTree* remove(AvlTree *t, int val);

	AvlTree* single_rotate_with_left(AvlTree *t);
	AvlTree* single_rotate_with_right(AvlTree *t);
	AvlTree* double_rotate_with_left(AvlTree *t);
	AvlTree* double_rotate_with_right(AvlTree *t);
};
