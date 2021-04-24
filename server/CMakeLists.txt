add_executable(server main.cpp)

target_sources(server
	PRIVATE
		server.hpp
		handler.hpp
		buffer.hpp
		notifier.hpp

		server.cpp
		handler.cpp
		buffer.cpp
		notifier.cpp
)

target_link_libraries(server
	boost_system
)
