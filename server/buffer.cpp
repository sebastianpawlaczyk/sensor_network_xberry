#include "buffer.hpp"

#include <iostream>

Buffer::Buffer(const uint32_t size)
: size_(size)
{

}

void Buffer::pushData(const std::string& msg)
{
	std::lock_guard<std::mutex> bufferLG(bufferMutex_);
	if (data_.size() == size_) data_.pop_front();
	data_.push_back(msg);
}

std::deque<std::string> Buffer::getData()
{
	std::lock_guard<std::mutex> bufferLG(bufferMutex_);
	return data_;
}

void Buffer::clearData()
{
	std::lock_guard<std::mutex> bufferLG(bufferMutex_);
	data_.clear();
}

void Buffer::changeSize(const uint32_t new_size)
{
	std::lock_guard<std::mutex> bufferLG(bufferMutex_);
	size_ = new_size;
}
