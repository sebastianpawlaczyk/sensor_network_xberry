#include "sensor.hpp"

#include <iostream>
#include <cstdlib>

#include <boost/bind.hpp>

Sensor::Sensor(const uint32_t number, const uint32_t delay, std::mutex& logMutex)
: socket_(io_service_)
, number_(number)
, delay_(delay)
, logMutex_(logMutex)
{
	socket_.async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234),
		boost::bind(&Sensor::connect, this, boost::asio::placeholders::error));
}

void Sensor::connect(const boost::system::error_code& error)
{
	if (!error)
	{
		transmit();
	}
	if (error)
	{
		std::cout << "SENSOR: ERROR: " << error.message() << std::endl;
		socket_.close();
	}
}

void Sensor::run()
{
	io_service_.run();
}

void Sensor::transmit()
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	auto number_data = rand() % 1000 + 1;
	std::string msg = "Sensor#";
	auto number_string = std::to_string(number_);
	msg.append(number_string);
	msg.append(" : Data#");
	auto number_data_to_string = std::to_string(number_data);
	msg.append(number_data_to_string);
	msg.append("\n");
	std::lock_guard<std::mutex> logGuard(logMutex_);
	socket_.async_write_some(boost::asio::buffer(msg),
		boost::bind(&Sensor::send, this, msg, boost::asio::placeholders::error));
}

void Sensor::send(const std::string& msg, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "SENSOR: Successfully sended : " << msg;
		std::this_thread::sleep_for(std::chrono::seconds(delay_));
		transmit();
	}
	else
	{
		std::cout << "SENSOR: ERROR: " << error.message() << std::endl;
		socket_.close();
	}
}
