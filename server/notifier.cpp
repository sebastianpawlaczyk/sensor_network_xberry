#include "notifier.hpp"

#include <iostream>

Notifier::Notifier(std::unique_ptr<Buffer>& buffer)
: buffer_(buffer)
{
	notifierThread = std::thread(&Notifier::notify, this);
}

void Notifier::notify()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(15));
		for (const auto& msg : buffer_->getData())
		{
			std::cout << "NOTIFIER: " << msg << std::endl;
		}
		std::cout << "------------------------------------" << "\n";
		buffer_->clearData();
	}
}
