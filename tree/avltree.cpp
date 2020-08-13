#include "avltree.h"
#include "../util/common.h"

#include <iostream>
#include <algorithm>

AvlTree* AVLTree::Insert(int val) {
	root_ = insert(root_, val);
	return root_;
}

AvlTree* AVLTree::Delete(int val) {
	root_ = remove(root_, val);
	return root_;
}

int AVLTree::Height(AvlTree *t) const {
	if (!t) {
		return -1;
	}
	return t->height;
}

AvlTree* AVLTree::insert(AvlTree *t, int val) {
	if (!t) {
		t = alloc_node(val);
	} else {
		if (val < t->val) {
			t->left = insert(t->left, val);
			if (Height(t->left) - Height(t->right) == 2) {
				if (val < t->left->val) {
					t = single_rotate_with_left(t);
				} else {
					t = double_rotate_with_left(t);
				}
			}
		} else if (val > t->val) {
			t->right = insert(t->right, val);
			if (Height(t->right) - Height(t->left) == 2) {
				if (val > t->right->val) {
					t = single_rotate_with_right(t);
				} else {
					t = double_rotate_with_right(t);
				}
			}
		}
	}
	t->height = std::max(Height(t->left), Height(t->right)) + 1;
	return t;
}

AvlTree* AVLTree::remove(AvlTree *t, int val) {
	if (!t) {
		return nullptr;
	}
	if (val < t->val) {
		t->left = remove(t->left, val);
		if (Height(t->right) - Height(t->left) == 2) {
			if (Height(t->right->left) > Height(t->right->right)) {
				t = double_rotate_with_right(t);
			} else {
				t = single_rotate_with_right(t);
			}
		}
	} else if (val > t->val) {
		t->right = remove(t->right, val);
		if (Height(t->left) - Height(t->right) == 2) {
			if (Height(t->left->left) < Height(t->left->right)) {
				t = double_rotate_with_left(t);
			} else {
				t = single_rotate_with_left(t);
			}
		}
	} else { // found
		if (t->left && t->right) { // t has two children
			AvlNode *n = FindMin(t->right);
			t->val = n->val;
			t->right = remove(t->right, n->val);
		} else if (t->left) { // t has left child
			AvlNode *p = t->left;
			this->free_node(t);
			t = p;

		} else if (t->right) { // t has right child
			AvlNode *p = t->right;
			this->free_node(t);
			t = p;
		} else { // t is leaf node
			this->free_node(t);
			t = nullptr;
		}
	}
	if (t) {
		t->height = std::max(Height(t->left), Height(t->right)) + 1;
	}
	return t;
}

// single rotate and return new root
AvlTree* AVLTree::single_rotate_with_left(AvlTree *t) {
	AvlNode *p = t->left;
	t->left = p->right;
	p->right = t;

	t->height = std::max(Height(t->left), Height(t->right)) + 1;
	p->height = std::max(Height(p->left), t->height) + 1;

	return p;
}

// single rotate and return new root
AvlTree* AVLTree::single_rotate_with_right(AvlTree *t) {
	AvlNode *p = t->right;
	t->right = p->left;
	p->left = t;

	t->height = std::max(Height(t->left), Height(t->right)) + 1;
	p->height = std::max(t->height, Height(p->right)) + 1;

	return p;
}

// double rotate and return new root
AvlTree* AVLTree::double_rotate_with_left(AvlTree *t) {
	t->left = single_rotate_with_right(t->left);
	AvlNode *p  = single_rotate_with_left(t);
	return p;
}

// double rotate and return new root
AvlTree* AVLTree::double_rotate_with_right(AvlTree *t) {
	t->right = single_rotate_with_left(t->right);
	AvlNode *p = single_rotate_with_right(t);
	return p;
}

int main(int argc, char* argv[]) {
	size_t count = 10;
	int *nums = gen_nums(count);
	std::cout << "Input: " << to_string(nums, count) << std::endl;

	AVLTree avltree;
	for (int i = 0; i < count; ++i) {
		avltree.Insert(nums[i]);
	}

	avltree.PreorderTraverse();
	avltree.InorderTraverse();
	avltree.PostorderTraverse();

	avltree.Delete(6);
	avltree.Delete(10);
	avltree.Delete(4);

	for (int i = 0; i < count; ++i) {
		AvlNode *n = avltree.Find(nums[i]);
		if (n) {
			int depth = avltree.Depth(n);
			int height = avltree.Height(n);
			std::cout << nums[i] << " found, "
					  << "depth " << depth << ", "
					  << "height " << height << std::endl;
		} else {
			std::cout << nums[i] << " not found" << std::endl;
		}
	}

	std::cout << "exit" << std::endl;
	return 0;
}
