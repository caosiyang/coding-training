#include "rbtree.h"
#include "../util/common.h"

RbTree* RBTree::Insert(int val) {
	RbNode *p = alloc_node(val);

	if (!root_) {
		set_black(p);
		root_ = p;
		return root_;
	}

	// insert
	RbNode *curr = root_;
	while (curr) {
		if (val < curr->val) {
			if (curr->left) {
				curr = curr->left;
			} else {
				curr->left = p;
				p->parent = curr;
				break;
			}
		} else {
			if (curr->right) {
				curr = curr->right;
			} else {
				curr->right = p;
				p->parent = curr;
				break;
			}
		}
	}

	// rebalance
	if (is_red(p->parent)) {
		rebalance(p);
	}

	return root_;
}

RbTree* RBTree::Delete(int val) {
	// TODO
	return nullptr;
}

RbTree* RBTree::insert(RbTree *t, int val) {
	// TODO
	return nullptr;
}

RbTree* RBTree::remove(RbTree *t, int val) {
	// TODO
	return nullptr;
}


RbTree* RBTree::single_rotate_with_left(RbTree *t) {
#ifdef DEBUG
	std::cout << __func__ << " " << t->val << std::endl;
#endif

	RbNode *parent = t->parent;
	RbNode *p = t->left;


	t->left = p->right;
	if (p->right) {
		p->right->parent = t;
	}

	p->right = t;
	t->parent = p;

	p->parent = parent;
	if (parent) {
		if (parent->left == t) {
			parent->left = p;
		} else {
			parent->right = p;
		}
	}

	return p;
}

RbTree* RBTree::single_rotate_with_right(RbTree *t) {
#ifdef DEBUG
	std::cout << __func__ << " " << t->val << std::endl;
#endif

	RbNode *parent = t->parent;
	RbNode *p = t->right;

	t->right = p->left;
	if (p->left) {
		p->left->parent = t;
	}

	p->left = t;
	t->parent = p;

	p->parent = parent;
	if (parent) {
		if (parent->left == t) {
			parent->left = p;
		} else {
			parent->right = p;
		}
	}

	return p;
}

int main(int argc, char* argv[]) {
	size_t count = 10;
	int *nums = gen_nums(count);
	std::cout << "Input: " << to_string(nums, count) << std::endl;

	RBTree rbtree;
	for (int i = 0; i < count; ++i) {
		rbtree.Insert(nums[i]);
	}

	rbtree.PreorderTraverse();
	rbtree.InorderTraverse();
	rbtree.PostorderTraverse();

	for (int i = 0; i < count; ++i) {
		RbNode *n = rbtree.Find(nums[i]);
		if (n) {
			int depth = rbtree.Depth(n);
			int height = rbtree.Height(n);
			std::cout << nums[i] << " found, "
				      << "color " << (n->color == RED ? "red" : "black") << ", "
					  << "depth " << depth << ", "
					  << "height " << height << std::endl;
		} else {
			std::cout << nums[i] << "not found" << std::endl;
		}
	}

	std::cout << "exit" << std::endl;
	return 0;
}
