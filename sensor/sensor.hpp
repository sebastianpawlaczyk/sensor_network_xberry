#pragma once

#include <thread>
#include <string>
#include <mutex>

#include <boost/asio.hpp>

class Sensor
{
public:
	explicit Sensor(const uint32_t number, const uint32_t delay, std::mutex& logMutex);

	void run();
private:
	void connect(const boost::system::error_code& error);
	void transmit();
	void send(const std::string& msg, const boost::system::error_code& error);

	boost::asio::io_service io_service_;
    boost::asio::ip::tcp::socket socket_;
    std::thread pingThread;
    const uint32_t number_;
    const uint32_t delay_;
    std::mutex& logMutex_;
};
