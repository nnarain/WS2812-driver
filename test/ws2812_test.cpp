
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "stdperiph/gpio_port.h"
#include "stdperiph/gpio_pin_ref.h"

using namespace stdperiph;

// setup Gpio port B
/*GPIO(PORTB, DDRB, GpioB);
typedef GpioPinRef<GpioB, 5> signal;*/

/* ASM Delays */

#define NOP   "nop\n\t"
#define NOP2  NOP NOP
#define NOP4  NOP2 NOP2
#define NOP8  NOP4 NOP4
#define NOP16 NOP8 NOP8

#define DELAY_CODE_1_HI() asm volatile(NOP8 NOP4);
#define DELAY_CODE_1_LO() asm volatile(NOP4 NOP);

#define DELAY_04_US NOP4 NOP2

/* Pixel Buffer */
static const unsigned int LED_COUNT = 10;
static const unsigned int PIXEL_BUFFER_SIZE = LED_COUNT * 3;

static uint8_t pixels[PIXEL_BUFFER_SIZE];

static void setPixelColor(uint16_t pixel, uint8_t g, uint8_t r, uint8_t b)
{
	uint16_t idx = pixel * 3;
	pixels[idx + 0] = g;
	pixels[idx + 1] = r;
	pixels[idx + 2] = b;
}

static inline void writeOneLed()
{
	uint8_t count = 24;
	while(count--)
	{
		asm volatile (
	  		"sbi %0, 5"
	  		: 
	  		: "I" (_SFR_IO_ADDR(PORTB))
	  	);

		DELAY_CODE_1_HI();

	  	asm volatile (
	  		"cbi %0, 5"
	  		:
	  		: "I" (_SFR_IO_ADDR(PORTB))
	  	);

	  	DELAY_CODE_1_LO();
	}
}

static inline void sendBuffer(uint8_t * buffer, uint16_t len)
{
	if(len == 0) return;

	uint8_t byte;
	uint8_t bitcount;
	uint8_t mask = (1 << 5);

	// mask off interrupts
	cli();

	while(len--)
	{
		// read byte from buffer
		byte = *buffer++;
		bitcount = 8;

		asm volatile(
			"loop:	" 					"\n\t"
			"		out %[port],%[maskhigh]" "\n\t"
			DELAY_04_US
			"		sbrs %[data],7" 	"\n\t"
			"		out %[port],%[masklow]" "\n\t"
			DELAY_04_US
			"		out %[port],%[masklow]" "\n\t"
			DELAY_04_US
			"		lsl %[data]" 		"\n\t"
			"		dec %[bitcount]" 	"\n\t"
			"		brne loop" 			"\n\t"
			: 
			: [port] "I" (_SFR_IO_ADDR(PORTB)), [data] "r" (byte), [bitcount] "d" (bitcount), [maskhigh] "d" (mask), [masklow] "d" (~mask)
		);
	}

	// re-enable interrupts
	sei();

	// hold for 50 us to send reset code
	_delay_us(50);
}

static inline void testWrite()
{
	cli();

	uint8_t count = 24;
	while(count--){
		asm volatile(
			"sbi %[port], 5" "\n\t"
			DELAY_04_US
			DELAY_04_US
			"cbi %[port], 5" "\n\t"
			DELAY_04_US

			:
			: [port] "I" (_SFR_IO_ADDR(PORTB))
		);
	}

	sei();
}

static inline void testWrite2()
{
	uint8_t count;

	cli();

	asm volatile(
		"					ldi %[count], 24"		"\n\t"
		"loop_testwrite2:	" 						"\n\t"
		"					sbi %[port], 5" 		"\n\t"
		DELAY_04_US
		DELAY_04_US
		"					cbi %[port], 5" 		"\n\t"
		DELAY_04_US
		"					dec %[count]"			"\n\t"
		"					brne loop_testwrite2" 	"\n\t"

		:
		: [count] "r" (count), [port] "I" (_SFR_IO_ADDR(PORTB))
	);

	sei();
}

static inline void testWrite3()
{
	uint8_t buffer[] = { 0x00, 0xFF, 0x00 };
	uint8_t * pBuf = buffer;
	uint8_t len = 3;
	uint8_t count;
	uint8_t data;

	cli();

	while(len--)
	{
		data = *pBuf++;

		asm volatile(
			"					ldi %[count], 8" 		"\n\t"
			"loop_testwrite3:"
			"					sbi %[port], 5"		 	"\n\t"
			DELAY_04_US
			"					sbrs %[data], 7"		"\n\t"
			"					cbi %[port], 5"			"\n\t"
			DELAY_04_US
			"					cbi %[port], 5"			"\n\t"
			DELAY_04_US
			"					lsl %[data]"			"\n\t"
			"					dec %[count]"			"\n\t"
			"					brne loop_testwrite3"	"\n\t"

			:
			: [count] "d" (count), [port] "I" (_SFR_IO_ADDR(PORTB)), [data] "r" (data)
		);
	}

	sei();
}

static inline void testWrite4()
{
	uint8_t buffer[] = { 0xFF, 0x00, 0x00 };
	uint8_t * pBuf = buffer;
	uint8_t len = 3;
	uint8_t count;
	uint8_t data;
	uint8_t mask = (1 << 5);

	cli();

	while(len--)
	{
		data = *pBuf++;

		asm volatile(
			"					ldi %[count], 8" 		"\n\t"
			"loop_testwrite3:"
			"					out %[port], %[maskhi]"	"\n\t"
			DELAY_04_US
			"					sbrs %[data], 7"		"\n\t"
			"					out %[port], %[masklo]"	"\n\t"
			DELAY_04_US
			"					out %[port], %[masklo]"	"\n\t"
			DELAY_04_US
			"					lsl %[data]"			"\n\t"
			"					dec %[count]"			"\n\t"
			"					brne loop_testwrite3"	"\n\t"

			:
			: [count] "d" (count), [port] "I" (_SFR_IO_ADDR(PORTB)), [data] "r" (data), [maskhi] "d" (mask), [masklo] "d" (~mask)
		);
	}

	sei();
}

/**
	Works !!!!!!!!!!!!! ----------------------------------
*/
static inline void testWrite5(uint8_t * buffer, uint16_t len)
{
	uint8_t * pBuf = buffer;
	uint8_t count;
	uint8_t data;
	uint8_t mask = (1 << 5);

	cli();

	while(len--)
	{
		data = *pBuf++;

		asm volatile(
			"					ldi %[count], 8" 		"\n\t"
			"loop_testwrite3:"
			"					out %[port], %[maskhi]"	"\n\t"
			DELAY_04_US
			"					sbrs %[data], 7"		"\n\t"
			"					out %[port], %[masklo]"	"\n\t"
			DELAY_04_US
			"					out %[port], %[masklo]"	"\n\t"
			DELAY_04_US
			"					lsl %[data]"			"\n\t"
			"					dec %[count]"			"\n\t"
			"					brne loop_testwrite3"	"\n\t"

			:
			: [count] "d" (count), [port] "I" (_SFR_IO_ADDR(PORTB)), [data] "r" (data), [maskhi] "d" (mask), [masklo] "d" (~mask)
		);
	}

	sei();
}

int main()
{
/*	signal::mode(BitMode::OUTPUT);
	signal::low();*/
	DDRB |= (1 << 5);
	PORTB = 0;

	for(int i = 0; i < LED_COUNT; ++i)
	{
		setPixelColor(i, 0, 0, 0xFF);
//		writeOneLed();
//		testWrite4();
	}

//	sendBuffer(pixels, PIXEL_BUFFER_SIZE);
	testWrite5(pixels, PIXEL_BUFFER_SIZE);

	for(;;);

	return 0;
}


