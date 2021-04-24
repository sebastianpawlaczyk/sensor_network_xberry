#pragma once

#include <cstdint>
#include <deque>
#include <string>
#include <mutex>

class Buffer
{
public:
	explicit Buffer(const uint32_t size);

	void pushData(const std::string& msg);
	std::deque<std::string> getData();
	void clearData();
	void changeSize(const uint32_t new_size);

private:
	std::deque<std::string> data_;
	uint32_t size_;
	std::mutex bufferMutex_;
};
