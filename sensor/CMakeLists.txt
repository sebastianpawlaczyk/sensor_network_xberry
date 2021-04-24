add_executable(sensor main.cpp)

target_sources(sensor
	PRIVATE
		sensor.hpp

		sensor.cpp
)

target_link_libraries(sensor
	boost_system
)
