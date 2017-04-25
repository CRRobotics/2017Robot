/*
 * LEDs.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: adam
 */

#include "LEDs.h"
#include "../Commands/LEDs/LEDRefresh.h"
#include <algorithm>
#include <vector>

LEDs::LEDs(unsigned number) : Subsystem("LEDs") {
	// TODO Auto-generated constructor stub
	this->number = number;
	this->led_number = number;
	this->offset = 0;
	this->cycle = true;
	colors = new std::vector<struct color>(number);
	spif = fopen("/dev/spidev0.0", "wb");
	increment = 1;
	for(unsigned i = 0; i < number; i++){
		(*colors)[i].__brightness = 0xff;
		(*colors)[i].r = 0;
		(*colors)[i].g = 0;
		(*colors)[i].b = 0;
	}
	SmartDashboard::PutBoolean("LED RUNNING", false);
}

void LEDs::InitDefaultCommand(){
	SetDefaultCommand(new LEDRefresh());
}

LEDs::~LEDs() {
	delete colors;
	fclose(spif);
	// TODO Auto-generated destructor stub
}

void LEDs::ChangeMode(LEDMode mode)
{
	switch (mode)
	{
		case LEDMode::NONE:
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
				(*colors)[i].__brightness = 0xff;
				(*colors)[i].r = 0;
				(*colors)[i].g = 0;
				(*colors)[i].b = 0;
			}
			break;
		case LEDMode::RED:
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0xf0;
					(*colors)[i].g = 0;
					(*colors)[i].b = 0;
			}
			break;
		case LEDMode::BLUE:
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0;
					(*colors)[i].g = 0;
					(*colors)[i].b = 0xf0;
			}
			break;
		case LEDMode::GREEN:
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0;
					(*colors)[i].g = 0xf0;
					(*colors)[i].b = 0;
			}
			break;
		case LEDMode::YELLOW:
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0xf0;
					(*colors)[i].g = 0xf0;
					(*colors)[i].b = 0;
			}
			break;
		case LEDMode::PURPLE:
			Resize(led_number);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = 0xf0;
					(*colors)[i].g = 0;
					(*colors)[i].b = 0xf0;
			}
			break;
		case LEDMode::PATRIOTIC:
			Resize(led_number * 2);
			increment = 1;
			for(unsigned i = 0; i < number; i++)
			{
					(*colors)[i].__brightness = 0xff;
					(*colors)[i].r = (i < number * 2 / 3)? 0xf0 : 0;
					(*colors)[i].g = (i > number / 3 && i < number * 2 / 3)? 0xf0 : 0;
					(*colors)[i].b = (i > number / 3)? 0xf0 : 0;
			}
			break;
		case LEDMode::GREEN_BLINK:
			Resize(led_number * 2);
			increment = led_number / 2;
			for (unsigned i = 0; i < number; i++)
			{
				(*colors)[i].__brightness = 0xff;
				(*colors)[i].r = 0;
				(*colors)[i].g = (i < led_number / 2 || (i > led_number && i < led_number * 3 / 2))? 0xf0 : 0;
				(*colors)[i].b = 0;
			}
			break;
		case LEDMode::YELLOW_BLINK:
			Resize(led_number * 2);
			increment = led_number / 2;
			for (unsigned i = 0; i < number; i++)
			{
				(*colors)[i].__brightness = 0xff;
				(*colors)[i].r = (i < led_number / 2 || (i > led_number && i < led_number * 3 / 2))? 0xf0 : 0;
				(*colors)[i].g = (i < led_number / 2 || (i > led_number && i < led_number * 3 / 2))? 0xf0 : 0;
				(*colors)[i].b = 0;
			}
			break;
	}
}

void LEDs::Refresh() {
	//fprintf(stderr, "refresh\n");
	if (cycle)
	{
		offset += increment;
		offset %= number;
	}
	struct color *c = colors->data();
//	for(unsigned i = 0; i < size; i += 128){
//		spi->Write(c + i, (unsigned char)std::min((unsigned)(size - i), (unsigned)128));
//	}
	fwrite("\x00\x00\x00\x00", 4, 1, spif);
	int a = 0, b = 0;
	if(number != offset) a = fwrite(c + offset, sizeof(struct color), number-offset, spif);
	if(offset != 0) b = fwrite(c, sizeof(struct color), offset, spif);
	//fprintf(stderr, "%d %d  %d %d %d\n", number, offset, a, b, a+b);

	fwrite("\xff\xff\xff\xff", 4, 1, spif);
	fflush(spif);
}

void LEDs::Resize(unsigned n){
	colors->resize(n);
	for(unsigned i = number; i < n; i++){
		(*colors)[i].__brightness = 0xff;
	}
	number = n;
}
