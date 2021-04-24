#pragma once

/* Fake client notifier.
*  It should allow client to subscribe it
*  using also tcp connection, but for now it only
*  prints buffer data on stdout to demonstrate received messages from sensors.
*/

#include <thread>

#include <boost/asio.hpp>

#include "buffer.hpp"

class Notifier
{
public:
	Notifier(std::unique_ptr<Buffer>& buffer);

	void notify();

private:
	std::unique_ptr<Buffer>& buffer_;
	std::thread notifierThread;
};

