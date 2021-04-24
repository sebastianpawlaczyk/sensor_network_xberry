#include <mutex>
#include <thread>
#include <unistd.h> 

#include "sensor.hpp"

int main()
{
	if (true)
	{
		std::mutex logMutex;
		Sensor sensor(1, 2, logMutex);
		Sensor sensor2(2, 6,logMutex);
		std::thread threadSensor1(&Sensor::run, &sensor);
		std::thread threadSensor2(&Sensor::run, &sensor2);

		std::this_thread::sleep_for(std::chrono::seconds(30));
		Sensor sensor3(3, 1,logMutex);
		std::thread threadSensor3(&Sensor::run, &sensor3);

		threadSensor1.join();
		threadSensor2.join();
		threadSensor3.join();
	}
	// only for potential use with process
	else
	{
		int i = 1;
		while (i <= 2)
		{
			if (fork() == 0)
			{
				std::mutex logMutex;
				Sensor sensor(i, 5, logMutex);
				sensor.run();
			}
			i++;
		}
	}
	return 0;
}
