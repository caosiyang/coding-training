#pragma once

#include "bstree.hpp"

class RBTree : public BinarySearchTree<RbTree, RbNode> {
public:
	RBTree() = default;
	virtual ~RBTree() = default;

	virtual RbTree* Insert(int val);
	virtual RbTree* Delete(int val);

private:
	RbTree* insert(RbTree *t, int val);
	RbTree* remove(RbTree *t, int val);

	RbTree* single_rotate_with_left(RbTree *t);
	RbTree* single_rotate_with_right(RbTree *t);

	void set_red(RbNode *n) {
		assert(n);
		n->color = RED;
	}

	void set_black(RbNode *n) {
		//assert(n);
		if (n) {
		n->color = BLACK;
		}
	}

	bool is_red(const RbNode *n) const {
		return n && n->color == RED;
	}

	bool is_black(const RbNode *n) const {
		// NIL node is black
		return n == nullptr || n->color == BLACK;
	}
	
	bool is_root(const RbNode *n) const {
		assert(n);
		return n->parent == nullptr;
	}

	bool is_left(const RbNode *n) const {
		assert(n && n->parent);
		return n == n->parent->left;
	}

	bool is_right(const RbNode *n) const {
		assert(n && n->parent);
		return n == n->parent->right;
	}

	RbNode* sibling_of(const RbNode *n) const {
#ifdef DEBUG
		std::cout << __func__ << " " << n->val << std::endl;
#endif
		//assert(n && n->parent);
		assert(n);
		assert(n->parent);
		return n == n->parent->left ? n->parent->right : n->parent->left;
	}

	// n can be
	//   - new node added
	//   - root of subtree after rebalance
	void rebalance(RbNode *n) {
		assert(n);

#ifdef DEBUG
		std::cout << __func__ << " for " << n->val << std::endl;
#endif

		if (is_root(n)) {
			if (is_red(n)) {
				set_black(n);
			}
			root_ = n;
			return;
		}

		//////// node is black ////////

		if (is_black(n)) {
			return;
		}

		//////// node is red ////////

		if (is_root(n)) {
			set_black(n);
			root_ = n;
			return;
		}

		if (is_black(n->parent)) {
			return;
		}

		RbNode *parent_sibling = sibling_of(n->parent);
		if (is_red(parent_sibling)) {
			// set color
			set_black(n->parent);
			set_black(parent_sibling);
			set_red(n->parent->parent);

			RbTree *subtree_root = n->parent->parent;
			if (!subtree_root->parent) { // it's root of the whole tree
				// it's red now
				set_black(subtree_root);
				root_ = subtree_root;
				return;
			} else if (is_red(subtree_root->parent)) {
				// recursive rebalance
				rebalance(subtree_root);
			}
		} else {
			RbNode *subtree_root = nullptr;
			if (is_left(n->parent)) { // n's parent is on left
				if (is_left(n)) {
					// single rotate
					RbTree *p = single_rotate_with_left(n->parent->parent);
					// set color
					set_black(p);
					set_red(p->right);
					subtree_root = p;
				} else {
					// double rotate
					RbTree *p1 = single_rotate_with_right(n->parent);
					RbTree *p2 = single_rotate_with_left(p1->parent);
					// set color
					set_black(p2);
					set_red(p2->right);
					subtree_root = p2;
				}
			} else { // n's parent is on right
				if (is_right(n)) {
					// single rotate
					RbTree *p = single_rotate_with_right(n->parent->parent);
					// set color
					set_black(p);
					set_red(p->left);
					subtree_root = p;
				} else {
					// double rotate
					RbTree *p1 = single_rotate_with_left(n->parent);
					RbTree *p2 = single_rotate_with_right(p1->parent);
					// set color
					set_black(p2);
					set_red(p2->left);
					subtree_root = p2;
				}
			}
			if (!subtree_root->parent) { // it's root of the whole tree
				// it's black now
				root_ = subtree_root;
			}
		}
	}

};
