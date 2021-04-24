#include "server.hpp"

#include <iostream>
#include <cstdint>

#include <boost/bind.hpp>

Server::Server(boost::asio::io_service& io_service)
: acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234))
{
	buffer_ = std::make_unique<Buffer>(5);
	notifier_ = std::make_unique<Notifier>(buffer_);
	accept();
}

void Server::run()
{
	acceptor_.get_io_service().run();
}

void Server::accept()
{
	boost::shared_ptr<Handler> handler(new Handler(acceptor_.get_io_service(),
		buffer_));
	acceptor_.async_accept(handler->getSocket(),
		boost::bind(&Server::handle, this, handler,
			boost::asio::placeholders::error));
}

void Server::handle(boost::shared_ptr<Handler> handler,
	const boost::system::error_code& error)
{
	std::cout << "SERVER: CONNECTION WITH NEW SENSOR!" << "\n";
	if (!error) handler->onHandle();
	accept();
}

void Server::changeBufferSize(const uint32_t new_size)
{
	buffer_->changeSize(new_size);
}

