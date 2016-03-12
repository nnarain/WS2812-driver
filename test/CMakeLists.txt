
cmake_minimum_required(VERSION 2.8.3)

include_directories(
	../include/
	include/
)

add_avr_executable(test
	main.cpp
)
