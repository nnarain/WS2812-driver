
cmake_minimum_required(VERSION 2.8.3)

find_package(SimAvr)

include_directories(
	../include/
	include/
	${SIMAVR_INCLUDE_DIR}
)

add_vcd_trace(ws2812driver ${AVR_MCU} 16000000
	"LED_SIGNAL,5,PORTB"
	"LED_SIGNAL_EN,5,DDRB"
	"TEST,4,PORTB"
)

add_avr_executable(ws2812driver
	ws2812_test.cpp
	${ws2812driver_VCD_TRACE_FILE}
)

add_avr_executable(driver_test
	driver_test.cpp
	${ws2812driver_VCD_TRACE_FILE}
)