#include <cassert>
#include <iostream>
#include "../util/common.h"
#include "../util/timer.h"

void quick_sort(int *low, int *high) {
	if (!(low && high && high > low)) {
		return;
	}

	int pivot = *low;
	int *p1 = low + 1, *p2 = high;
	while (p1 <= p2) {
		if (*p1 > pivot && *p2 <= pivot) {
			swap(p1, p2);
			++p1;
			--p2;
		} else {
			if (*p1 <= pivot) ++p1;
			if (*p2 > pivot) --p2;
		}
	}

	int *p = p1 - 1;
	swap(low, p);

	quick_sort(low, p - 1);
	quick_sort(p + 1, high);
}

int main(int argc, char **argv) {
	int count = 10;
	if (argc > 1) {
		count = atoi(argv[1]);
	}
	int *nums = gen_nums(count, 1000);

	std::cout << "Quick Sort" << std::endl;
	std::cout << "input:" << std::endl;
	std::cout << to_string(nums, count) << std::endl;

	Timer::Start();
	quick_sort(nums, nums + count - 1);
	Timer::End();

	std::cout << "output:" << std::endl;
	std::cout << to_string(nums, count) << std::endl;

	if (validate_order(nums, nums + count - 1, asc)) {
		std::cout << "PASS in " << Timer::Delta() <<std::endl;
	} else {
		std::cout << "ERROR" << std::endl;
	}
	return 0;
}
