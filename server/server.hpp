#pragma once

#include <memory>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "handler.hpp"
#include "buffer.hpp"
#include "notifier.hpp"

class Server
{
public:
	explicit Server(boost::asio::io_service& io_service);

	void run();
	void changeBufferSize(const uint32_t new_size);

private:
	void accept();
	void handle(boost::shared_ptr<Handler> handler,
		const boost::system::error_code& error);
	void notify();

	boost::asio::ip::tcp::acceptor acceptor_;
	std::unique_ptr<Buffer> buffer_;
	std::unique_ptr<Notifier> notifier_;
};
