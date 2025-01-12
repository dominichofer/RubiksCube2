#pragma once
#include <cmath>
#include <functional>
#include <ranges>

struct WelfordResult
{
	double mean, variance, sample_variance;
};

template <typename T, typename P = std::identity>
WelfordResult welford(T first, T last, P proj = {})
{
	// From https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm

	double mean{ 0 }, M2{ 0 }, n{ 1 };
	for (; first != last; ++first, ++n)
	{
		double delta = proj(*first) - mean;
		mean += delta / n;
		double delta2 = proj(*first) - mean;
		M2 += delta * delta2;
	}
	return { mean, M2 / n, M2 / (n - 1) };
}

template <typename T, typename P = std::identity>
double average(T first, T last, P proj = {})
{
	return welford(first, last, std::move(proj)).mean;
}

template <std::ranges::range R, typename P = std::identity>
double average(R&& r, P proj = {})
{
	return average(std::begin(r), std::end(r), std::move(proj));
}

// population variance
template <typename T, typename P = std::identity>
double variance(T first, T last, P proj = {})
{
	return welford(first, last, std::move(proj)).sample_variance;
}

// population variance
template <std::ranges::range Range, typename P = std::identity>
double variance(Range&& r, P proj = {})
{
	return variance(std::begin(r), std::end(r), std::move(proj));
}

// population standard deviation
template <typename T, typename P = std::identity>
double standard_deviation(T first, T last, P proj = {})
{
	using std::sqrt;
	return sqrt(variance(first, last, std::move(proj)));
}

// population standard deviation
template <std::ranges::range Range, typename P = std::identity>
double standard_deviation(Range&& r, P proj = {})
{
	return standard_deviation(std::begin(r), std::end(r), std::move(proj));
}
