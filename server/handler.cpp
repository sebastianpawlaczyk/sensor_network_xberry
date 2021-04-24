#include "handler.hpp"

#include <iostream>

#include <boost/bind.hpp>

Handler::Handler(boost::asio::io_service& io_service,
	std::unique_ptr<Buffer>& buffer)
: socket_(io_service)
, buffer_(buffer)
{}

boost::asio::ip::tcp::socket& Handler::getSocket()
{
	return socket_;
}

void Handler::onHandle()
{
	boost::asio::async_read_until(socket_, stream_buf_, "\n",
		boost::bind(&Handler::read, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Handler::read(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
	{
		std::istream is(&stream_buf_);
		std::string msg;
		std::getline(is, msg);
		buffer_->pushData(msg);
		onHandle();
	}
	else
	{
		std::cout << "Error: " << error.message() << std::endl;
		socket_.close();
	}
}
