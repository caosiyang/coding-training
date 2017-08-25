#include <stdlib.h>
#include <iostream>
#include "../util/util.h"

void qsort(int *start, int *end) {
    if (!(start && end && end > start)) {
        return;
    }
    int sentinel = *start;
    int *p1, *p2;
    for (p1 = start + 1, p2 = end; p1 <= p2; ) {
        if (*p1 >= sentinel && *p2 < sentinel) {
            *p1 = *p1 + *p2;
            *p2 = *p1 - *p2;
            *p1 = *p1 - *p2;
            ++p1;
            --p2;
        } else {
            if (*p1 < sentinel) ++p1;
            if (*p2 >= sentinel) --p2;
        }
    }

    *start = *(p1-1);
    *(p1-1) = sentinel;

    qsort(start, p1-2);
    qsort(p1, end);
}

int main(int argc, char **argv) {
    int total = 40;
    int range = 1000;
    if (argc > 1) {
        total = atoi(argv[1]);
    }

    int nums[total] = {0};
    srand(time(NULL));
    for (int i = 0; i < total; ++i) {
        nums[i] = rand() % range;
    }

    std::cout << "input:" << std::endl;
    std::cout << output(nums, total) << std::endl;

    Timer::Start();
    qsort(nums, nums + total - 1);
    Timer::End();

    std::cout << "output:" << std::endl;
    std::cout << output(nums, total) << std::endl;

    if (valid(nums, nums + total - 1, asc)) {
        std::cout << "pass: " << Timer::Delta() <<std::endl;
    } else {
        std::cout << "error" << std::endl;
    }
    return 0;
}
