#include "bstree.hpp"
//#include "common.h"
#include "../util/common.h"

#include <iostream>

int main(int argc, char* argv[]) {
	size_t count = 10;
	int *nums = gen_nums(count);
	std::cout << "Input: " << to_string(nums, count) << std::endl;

	BinarySearchTree<> bstree;
	for (size_t i = 0; i < count; ++i) {
		bstree.Insert(nums[i]);
	}

	bstree.PreorderTraverse();
	bstree.InorderTraverse();
	bstree.PostorderTraverse();

	bstree.Delete(7);

	for (size_t i = 0; i < count; ++i) {
		Node *n = bstree.Find(nums[i]);
		if (n) {
			int depth = bstree.Depth(n);
			int height = bstree.Height(n);
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
