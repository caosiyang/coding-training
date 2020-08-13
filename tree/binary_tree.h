#pragma once

#include "tree_types.h"

#include <cassert>
#include <iostream>
#include <algorithm>

template<typename TreeType, typename NodeType>
class BinaryTree {
public:
	BinaryTree() = default;
	virtual ~BinaryTree() = default;

	virtual TreeType* Insert(int val) = 0;
	virtual TreeType* Delete(int val) = 0;
	virtual NodeType* Find(int val) const = 0;
	virtual NodeType* FindMin(TreeType *t) const = 0;
	virtual NodeType* FindMax(TreeType *t) const = 0;

	virtual int Height() const {
		return Height(root_);
	}

	virtual int Height(TreeType *t) const {
		return get_height(t);
	}

	int get_height(TreeType *t) const {
		if (!t) {
			return -1;
		}
		if (!t->left && !t->right) { // leaf node
			return 0;
		}
		int h_l = get_height(t->left);
		int h_r = get_height(t->right);
		return std::max(h_l, h_r) + 1;
	}

	int Depth(NodeType *n) const {
		if (!n) {
			return -1;
		}
		return get_depth(root_, n);
	}

	int get_depth(TreeType *t, NodeType *n) const {
		if (!t) {
			return -1;
		}
		if (t == n) {
			return 0;
		}
		if (n->val < t->val) {
			return get_depth(t->left, n) + 1;
		} else {
			return get_depth(t->right, n) + 1;
		}
	}

	void PreorderTraverse() const {
		std::cout << "preorder traverse: ";
		preorder_traverse(root_);
		std::cout << std::endl;
	}

	void InorderTraverse() const {
		std::cout << "inorder traverse: ";
		inorder_traverse(root_);
		std::cout << std::endl;
	}

	void PostorderTraverse() const {
		std::cout << "postorder traverse: ";
		postorder_traverse(root_);
		std::cout << std::endl;
	}

	void HierarchyTraverse() const {
		std::cout << "hierarchy traverse: ";
		// todo
		std::cout << std::endl;
	}

protected:
	NodeType* alloc_node(int val) {
		NodeType *n = new (std::nothrow) NodeType(val);
		assert(n);
		return n;
	}

	void free_node(NodeType *n) {
		if (n) {
			delete n;
			n = nullptr;
		}
	}

private:
	void preorder_traverse(const TreeType *t) const {
		if (!t) {
			return;
		}
		std::cout << t->val << ", ";
		preorder_traverse(t->left);
		preorder_traverse(t->right);
	}

	void inorder_traverse(const TreeType *t) const {
		if (!t) {
			return;
		}
		inorder_traverse(t->left);
		std::cout << t->val << ", ";
		inorder_traverse(t->right);
	}

	void postorder_traverse(const TreeType *t) const {
		if (!t) {
			return;
		}
		postorder_traverse(t->left);
		postorder_traverse(t->right);
		std::cout << t->val << ", ";
	}

public:
	NodeType *root_ = nullptr;
};
