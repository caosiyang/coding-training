#include <cassert>
#include <cstring>
#include <iostream>
#include "../util/common.h"
#include "../util/timer.h"

void bubble_sort(int nums[], size_t count) {
	for (int j = count - 1; j > 0; --j) {
		for (int i = 0; i < j; ++i) {
			if (nums[i] > nums[i+1]) {
				swap(nums[i], nums[i + 1]);
			}
		}
	}
}

void selection_sort(int nums[], size_t count) {
	for (int i = 0; i < count - 1; ++i) {
		int pos = i;
		int val = nums[i];
		for (int j = i + 1; j < count; ++j) {
			if (nums[j] < val) {
				pos = j;
				val = nums[j];
			}	
		}
		if (pos != i) {
			swap(nums[i], nums[pos]);
		}
	}
}

void insertion_sort(int nums[], size_t count) {
	for (int i = 1; i < count; ++i) {
		int val = nums[i];
		int j;
		for (j = i; j > 0 && nums[j - 1] > val; --j) {
			nums[j] = nums[j - 1];
		}
		nums[j] = val;
	}
}

void shell_sort(int nums[], size_t count) {
	size_t span = count / 2;
	while (span != 0) {
		for (int i = 0; i < span; ++i) {
			size_t n = count / span;
			int arr[n];
			for (int j = 0; j < n; ++j) {
				arr[j] = nums[i + j * span];
			}
			insertion_sort(arr, n);
			for (int j = 0; j < n; ++j) {
				nums[i + j * span] = arr[j];
			}

		}
		span /= 2;
	}
}

void merge(int nums[], size_t count) {
	if (count < 2) {
		return;
	}

	int tmp[count];
	memcpy(tmp, nums, count * sizeof(nums[0]));
	int mid = count / 2;
	int i = 0, j = 0, k = mid;
	while (j < mid && k < count) {
		if (tmp[j] < tmp[k]) {
			nums[i++] = tmp[j++];
		} else {
			nums[i++] = tmp[k++];
		}
	}
	while (j < mid) {
		nums[i++] = tmp[j++];
	}
	while (k < count) {
		nums[i++] = tmp[k++];
	}
}

void merge_sort(int nums[], size_t count) {
	int mid = count / 2;
	if (mid != 0) {
		merge_sort(nums, mid);
		merge_sort(nums + mid, count - mid);
	} else {
		merge(nums, count);
	}
	merge(nums, count);
}

void qsort(int *low, int *high) {
	assert(low && high);
	if (low >= high) {
		return;
	}

	int pivot = *high;
	int *p1 = low, *p2 = high - 1;
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

	swap(p1, high);

	qsort(low, p1 - 1);
	qsort(p1 + 1, high);
}

void quick_sort(int nums[], size_t count) {
	qsort(nums, nums + count - 1);
}

void max_heap_append(int nums[], size_t pos, int val) {
	if (pos == 0) {
		nums[pos] = val;
	} else {
		size_t parent = (pos - 1) / 2;
		if (val > nums[parent]) {
			nums[pos] = nums[parent];
			max_heap_append(nums, parent, val);
		} else {
			nums[pos] = val;
		}
	}
}

void max_heap_update(int heap[], size_t heap_size, size_t pos, int val) {
	if (heap_size == 0) {
		return;
	}

	assert(pos < heap_size);

	bool has_left = (pos * 2 + 1) < heap_size;
	bool has_right = (pos * 2 + 2) < heap_size;

	if (has_left && has_right) {
		int left = heap[pos * 2 + 1];
		int right = heap[pos * 2 + 2];

		if (val < left && val < right) {
			int new_val = (left > right) ? left : right;
			int new_pos = (left > right) ? (pos * 2 + 1) : (pos * 2 + 2);
			heap[pos] = new_val;
			max_heap_update(heap, heap_size, new_pos, val);
		} else if (val < left) {
			heap[pos] = left;
			max_heap_update(heap, heap_size, pos * 2 + 1, val);
		} else if (val < right) {
			heap[pos] = right;
			max_heap_update(heap, heap_size, pos * 2 + 2, val);
		} else {
			heap[pos] = val;
		}
	} else if (has_left) {
		int left = heap[pos * 2 + 1];
		if (val < left) {
			heap[pos] = left;
			max_heap_update(heap, heap_size, pos * 2 + 1, val);
		} else {
			heap[pos] = val;
		}
	} else {
		heap[pos] = val;
	}
}

int* max_heap_build(int nums[], size_t count) {
	int *array = new int[count];
	for (size_t i = 0; i < count; ++i) {
		max_heap_append(array, i, nums[i]);
	}
	return array;
}

void max_heap_sort(int nums[], size_t count) {
	int *heap = max_heap_build(nums, count);
	for (int i = 0, heap_size = count; i < count; ++i) {
		int tail_val = heap[heap_size - 1];
		heap[heap_size - 1] = heap[0];
		--heap_size;
		max_heap_update(heap, heap_size, 0, tail_val);
	}
	memcpy(nums, heap, count * sizeof(int));
	delete[] heap;
}

void sort_with(std::string name, void (*sort_func)(int nums[], size_t count), int input_nums[], size_t count) {
	assert(count > 0);
	int nums[count];
	memcpy(nums, input_nums, count * sizeof(int));
	std::cout << name << std::endl;
	std::cout << "Input: " << to_string(nums, count) << std::endl;

	Timer::Start();
	sort_func(nums, count);
	Timer::End();

	assert(valid_order(nums, count, asc));
	std::cout << "Output: " << to_string(nums, count) << std::endl;
	std::cout << "cost " << Timer::Delta() << std::endl;
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {
	size_t count = 100;
	if (argc > 1) {
		int n = atoi(argv[1]);
		assert(n > 0);
		count = n;
	}
	int *input_nums = gen_nums(count);
	int nums[count];
	
	sort_with("Bubble Sort", bubble_sort, input_nums, count);
	sort_with("Selection Sort", selection_sort, input_nums, count);
	sort_with("Insertion Sort", insertion_sort, input_nums, count);
	sort_with("Shell Sort", shell_sort, input_nums, count);
	sort_with("Merge Sort", merge_sort, input_nums, count);
	sort_with("Quick Sort", quick_sort, input_nums, count);
	sort_with("Heap Sort", max_heap_sort, input_nums, count);

	return 0;
}
