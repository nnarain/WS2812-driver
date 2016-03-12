
cmake_minimum_required(VERSION 2.8.3)

include_directories(
	../include/
	include/
)

add_avr_executable(basic_timer
	basic_timer.cpp
)


add_avr_executable(basic_interrupts
	basic_interrupts.cpp
)