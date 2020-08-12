#pragma once

#include <cstdlib>
#include <sstream>
#include <vector>

void swap(int &m, int &n) {
	if (m != n) {
		m = m ^ n;
		n = m ^ n;
		m = m ^ n;
	}
}

void swap(int *m, int *n) {
	if (m != n) {
		*m = *m ^ *n;
		*n = *m ^ *n;
		*m = *m ^ *n;
	}
}

int* gen_nums(size_t count, size_t range = 0) {
	assert(count > 0);
	srand(time(NULL));
	int *nums = new int[count];
	if (range != 0) {
		for (int i = 0; i < count; ++i) {
			*(nums + i) = rand() % range;
		}
	} else {
		std::vector<int> vec;
		for (int i = 0; i < count; ++i) {
			vec.push_back(i);
		}
		for (int *p = nums; p < nums + count; ++p) {
			std::vector<int>::const_iterator it = vec.begin() + rand() % vec.size();
			*p = *it;
			vec.erase(it);
		}
	}
	return nums;
}

// ascending order
template <typename T>
int asc(T a, T b) {
	if (a > b) {
		return 1;
	} else if (a < b) {
		return -1;
	} else {
		return 0;
	}
}

// descending order
template <typename T>
int desc(T a, T b) {
	if (a > b) {
		return -1;
	} else if (a < b) {
		return 1;
	} else {
		return 0;
	}
}

template <typename T>
bool validate_order(T *start, T *end, int (*cmp)(T a, T b)) {
	int *p = start;
	while (p < end) {
		if (cmp(*(p + 1), *p) < 0) {
			return false;
		}
		++p;
	}
	return true;
}

template <typename T>
std::string to_string(const T *start, int count) {
	std::stringstream ss;
	for (int i = 0; i < count; ++i) {
		ss << *(start + i) << ", ";
	}
	return ss.str();
}
