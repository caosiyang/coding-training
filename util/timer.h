#pragma once

#include <time.h>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

class Timer {
public:
	static void Start() {
		clock_gettime(CLOCK_MONOTONIC, &ts_start);
	}

	static void End() {
		clock_gettime(CLOCK_MONOTONIC, &ts_end);
	}

	static std::string Delta() {
		float n = float((ts_end.tv_sec * 1000000000 + ts_end.tv_nsec) - (ts_start.tv_sec * 1000000000 + ts_start.tv_nsec)) / 1000000;
		std::stringstream ss;
		ss << n << " ms";
		return ss.str();
	}

private:
	static struct timespec ts_start;
	static struct timespec ts_end;
};

struct timespec Timer::ts_start = {0, 0};
struct timespec Timer::ts_end = {0, 0};

static std::chrono::steady_clock::time_point t1, t2;

void time_stat_start() {
	t1 = std::chrono::steady_clock::now();
}

void time_stat_end() {
	t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "time used: " << time_span.count() << std::endl;
}
