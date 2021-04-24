#include <iostream>

#include <thread>
#include <boost/asio.hpp>

#include "server.hpp"

int main()
{
	try
    {
	    boost::asio::io_service io_service;  
	    Server server(io_service);
      std::thread threadService(&Server::run, &server);

      std::this_thread::sleep_for(std::chrono::seconds(50));
      server.changeBufferSize(3);

      threadService.join();
    }
  	catch(std::exception& e)
    {
    	std::cerr << e.what() << std::endl;
    }
  		return 0;
}
