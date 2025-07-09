#pragma once
#include <array>
#include <stdexcept>

template <typename T, std::size_t N>
class InplaceVector
{
	std::size_t size_;
	std::array<T, N> data_;
public:
	using value_type = T;
	using size_type = std::size_t;
	using reference = T&;
	using const_reference = const T&;

	InplaceVector() : size_(0) {}

	void push_back(const T& value)
	{
		if (size_ >= N)
			throw std::out_of_range("InplaceVector: exceeded maximum size");
		data_[size_++] = value;
	}

	size_type size() const { return size_; }
	bool empty() const { return size_ == 0; }

	auto begin() { return data_.data(); }
	auto end() { return data_.data() + size_; }
	
	reference operator[](size_type index) { return data_[index]; }
	const_reference operator[](size_type index) const { return data_[index]; }
};
