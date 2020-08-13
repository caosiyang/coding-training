#include "bstree.h"

template <typename TreeType, typename NodeType>
TreeType* BinarySearchTree<TreeType, NodeType>::Insert(int val) {
	this->root_ = insert(this->root_, val);
	return this->root_;
}

template <typename TreeType, typename NodeType>
TreeType* BinarySearchTree<TreeType, NodeType>::Delete(int val) {
	this->root_ = remove(this->root_, val);
	return this->root_;
}

template <typename TreeType, typename NodeType>
TreeType* BinarySearchTree<TreeType, NodeType>::remove(TreeType *t, int val) {
	if (!t) {
		return nullptr;
	}
	if (val < t->val) {
		t->left = remove(t->left, val);
	} else if (val > t->val) {
		t->right = remove(t->right, val);
	} else { // found
		if (t->left && t->right) { // t has two children
			NodeType *n = FindMin(t->right);
			t->val = n->val;
			t->right = remove(t->right, n->val);
		} else if (t->left) { // t has left child
			NodeType *p = t->left;
			this->free_node(t);
			t = p;
		} else if (t->right) { // t has right child
			NodeType *p = t->right;
			this->free_node(t);
			t = p;
		} else { // t is leaf node
			this->free_node(t);
			t = nullptr;
		}
	}
	return t;
}

template <typename TreeType, typename NodeType>
NodeType* BinarySearchTree<TreeType, NodeType>::Find(int val) const {
	return find(this->root_, val);
}

template <typename TreeType, typename NodeType>
NodeType* BinarySearchTree<TreeType, NodeType>::FindMin(TreeType *t) const {
	if (!t) {
		return nullptr;
	}
	NodeType *n = t;
	while (n->left) {
		n = n->left;
	}
	return n;
}


template <typename TreeType, typename NodeType>
NodeType* BinarySearchTree<TreeType, NodeType>::FindMax(TreeType *t) const {
	if (!t) {
		return nullptr;
	}
	NodeType *n = t;
	while (n->right) {
		n = n->right;;
	}
	return n;
}


template <typename TreeType, typename NodeType>
TreeType* BinarySearchTree<TreeType, NodeType>::insert(TreeType *t, int val) {
	if (!t) {
		t = this->alloc_node(val);
	} else {
		if (val < t->val) {
			t->left = insert(t->left, val);
		} else {
			t->right = insert(t->right, val);
		}
	}
	return t;
}


template <typename TreeType, typename NodeType>
NodeType* BinarySearchTree<TreeType, NodeType>::find(TreeType *t, int val) const {
	if (!t) {
		return nullptr;
	}
	if (t->val == val) {
		return t;
	} else { 
		if (val < t->val) {
			return find(t->left, val);
		} else {
			return find(t->right, val);
		}
	}
}
