#pragma once

#include <cstdint>
#include <memory>

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "buffer.hpp"

class Handler : public boost::enable_shared_from_this<Handler>
{
public:
	Handler(boost::asio::io_service& io_service,
		std::unique_ptr<Buffer>& buffer);

	boost::asio::ip::tcp::socket& getSocket();

	void onHandle();

private:
	void read(const boost::system::error_code& error, size_t bytes_transferred);

	boost::asio::ip::tcp::socket socket_;
  	boost::asio::streambuf stream_buf_;
  	std::unique_ptr<Buffer>& buffer_;
};
