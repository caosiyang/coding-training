#include <iostream>
#include <string>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_nums(int nums[], size_t cnt, std::string prefix) {
	if (!prefix.empty()) {
		std::cout << prefix;
	}
	for (size_t i = 0; i < cnt; ++i) {
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;
}

// rotate the first N elements to back
// e.g.:
// 1 2 3 4 5 with N = 3 to
// 4 5 1 2 3
void rotate(int nums[], int count, int n) {
	std::cout << "start is " << *nums << ", count == " << count << ", n == " << n << std::endl;
	if (n == count) {
		return;
	}
	int range1 = n;
	int range2 = count - n;
	int pos1 = 0;
	int pos2;
	if (range1 > range2) {
		pos2 = n;
		for (int i = 0; i < range2; ++i) {
			swap(nums + pos1, nums + pos2);
			++pos1;
			++pos2;
		}
		rotate(nums + pos1, range1, range1 - range2);
	} else {
		pos2 = count - n;
		for (int i = 0; i < range1; ++i) {
			swap(nums + pos1, nums + pos2);
			++pos1;
			++pos2;
		}
		rotate(nums, range2, range1);
	}
}

int search(int nums[], int start, int end, int val) {
	std::cout << "search " << val << " in [" << start << ", " << end << "]" << std::endl;

	int num_start = *(nums + start);
	int num_end = *(nums + end);

	if (num_start > num_end && val < num_start && val > num_end) {
		return -1;
	}

	if (val == num_start) {
		return start;
	}
	if (val == num_end) {
		return end;
	}

	int count = end - start + 1;
	if (count == 2) {
		return -1;
	}

	int mid = start + count / 2;
	int num_mid = *(nums + mid);
	if (val == num_mid) {
		return mid;
	}

	if (num_mid > num_start) {
		if (val > num_start && val < num_mid) {
			return search(nums, start, mid, val);
		} else {
			return search(nums, mid, end, val);
		}
	} else {
		if (val > num_mid && val < num_end) {
			return search(nums, mid, end, val);
		} else {
			return search(nums, start, mid, val);
		}
	}
}

void search(int nums[], size_t cnt, int val) {
	int idx = search(nums, 0, cnt - 1, val);
	if (idx < 0) {
		std::cout << "Result: not found " << val << std::endl;
	} else {
		std::cout << "Result: found " << val << ", pos == " << idx << std::endl;
	}
}

int main(int argc, char **argv) {
	std::cout << "Step 1: rotate" << std::endl;
	int nums[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 16, 17, 21, 23, 24};
	int count = sizeof(nums) / sizeof(int);

	print_nums(nums, count, "Input: ");
	rotate(nums, count, 6);
	print_nums(nums, count, "Output: ");

	std::cout << std::endl;

	std::cout << "Step 2: search" << std::endl;
	search(nums, count, 1);
	search(nums, count, 2);
	search(nums, count, 17);
	search(nums, count, 24);
	search(nums, count, 20);

	return 0;
}
